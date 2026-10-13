// =========================================================================================
// ======================== T E L I U M   C A S H   R E G I S T E R ========================
// =========================================================================================
//
//		Module: CashRegister.Forms
//		File  : MainForm.cs
//		Author: rdem
//
//
//		Description:
//		Main form for the Telium Cash Register application.
//
//
//		Last Modification:
//		$Id:
//
// ----------------------------------------------------------------------------------------- 
//		Modifications:
//		Date		Author	Issue	Comment
//		2018-03-02	rdui			Added processing of totals, security scheme and acquirer messages, clear C-TAP database, TMS session and print information.
//		2018-02-05	rdem			Added distiction between status update keep-alives and timed keep-alives.
//									Added date/time to messages.
//									Added merchant text label. Information report stage message are displayed in list and merchant text label.
//		2017-11-01	rdem			Added sending of messages with spec errors.
//		2017-10-20	rdem			Added processing of transaction mode, authorisation code and token.
//									Enabled other transaction types.
//		2017-10-13	rdem			Parameterised transparent mode settings.
//		2017-10-05	rdem			Added handling of version information messages.
//		2017-09-15	rdem			Added handling of new intermediate rsult mode (no response needed mode).
//		2017-09-12	rdem			Added handling of transparent mode messages.
//		2017-08-30	rdem			Auto amount increment moved to "TransactionResponse" and only incremented when transaction result was not "CtapBusy".
//									Auto-repeat now started via timer to have a variable delay.
//		2017-08-29	rdem			The HandleLastTransactionStatusResponse() handles invalid date/time.
//		2017-08-25	rdem			Added sending/handling of last transaction status.
//		2017-08-25	rdem			Added sending/handling of last transaction ticket.
//		2017-08-25	rdem			Added handling of InformationReport.
//		2017-08-09	rdem			Added cancel button and handling of CancelResponse.
//		2017-07-27	rdem			The HandleSignalIntermediateResultRequest() used wrong size for amount.
//									The DisplayIntermediateResult() now uses BeginInvoke() since displaying a dialog blocks the message handler thread thus missing keep-alives.
//		2017-06-29	lver			Implemented intermediate result.
//		2016-06-28	rdem			Serial connection parameters taken from settings (baud rate, data bits, parity, stop bits, flow control).
//		2016-03-09	rdem			Added support for keep-alive.
//		2016-03-02	rdem			Fixed reading the transaction response result code. Was 8-bit int, must be 16-bit int.
//
// ==========================================================================================
// (C) Chess pT  2015-2018
// ==========================================================================================


using ChessPt.TlvCashRegisterLib;
using System;
using System.Drawing;
using System.Linq;
using System.Threading;
using System.Windows.Forms;


namespace ChessPt.CashRegister.Forms
{
	/// <summary>
	/// Main form for the Telium Cash Register application.
	/// </summary>
	public partial class MainForm: System.Windows.Forms.Form, IMessageHandler
	{
		private uint mAmount = 0;											// The entered amount (in cents).
		private ulong mTransactionId = 0;									// The transaction ID send to the terminal. Incremented after each transaction.

		private volatile Thread mThread = null;								// The thread runing the connection handler.
		private volatile ConnectionHandler mConnectionHandler = null;		// The connection handler that processes the messages to/from the terminal.

		// Connection data.
		private string mTerminalId;											// The terminal ID is stored here in the hello request.
		private string mLogicalId;											// The terminal logical ID is stored here in the hello request(same as terminal ID).
		private string mSerialNumber;										// The terminal serial number is stored here in the hello request.
		private string mCashRegisterId = "TestECR";							// The ECR ID sent to the terminal.
		private ushort mSentMessageSequenceNr = 0;							// The sequence number for sending messages.

		// The keep-alive timer and related variables.
		private System.Timers.Timer mKeepAliveTimer = null;
		private ushort mKeepAliveInterval = 0;								// The keep-alive interval the terminal uses.
		private ulong mCounterKeepAlive = 0;								// The number of keep-alives received.
		private ulong mCounterStatusUpdate = 0;								// The number of status updates received.
		private DateTime mKeepAliveTimeLast;								// The last keep-alive time.
		private DateTime mKeepAliveTimeCurrent;								// The current keep-alive time.

		private System.Windows.Forms.Timer mAutoRepeatTimer = new System.Windows.Forms.Timer();

		// Transparent mode variables.
		private bool mTransparentModeState = false;							// True when in transparent mode.
		private byte[] mTransparantModeCardUid;								// The UID of the last read card. Needed to calculate key.

		private TlvLib.PendingMessagesOperation mPendingMessagesOperation;	// Used to determine if open messages should be sent or delete after the list op acquires is retrieved.


		//		// HENK related variables.
		//		private HenkManager mHenkManager = new HenkManager(Properties.Settings.Default.HenkComPort, Properties.Settings.Default.HenkCardSequence);    // The HENK manager object.
		//		private volatile System.Timers.Timer mHenkTimer = new System.Timers.Timer();                      // The HENK timer.

		/// <summary>
		/// Function called by the keep-alive timer.
		/// As long as keep-alive messages arrive, the timer will be reset and this function won't be called.
		/// </summary>
		/// <param name="sender">The sender of the event.</param>
		/// <param name="e">The event arguments.</param>
		private void KeepAliveTime_Elapsed(object sender, EventArgs e)
		{
			// Stop the timer.
			if (mKeepAliveTimer != null) mKeepAliveTimer.Stop();
			mKeepAliveTimer = null;

			// Display connection lost message.
			this.Invoke(new Action(() => { lblStatus.Text = "Terminal offline."; lblMerchantMessage.Text = "Connection was lost (keep-alive time-out)"; }));
			AddMessage(lblMerchantMessage.Text, true, Color.Red);

			// Stop the communication.
			mConnectionHandler.Close();
		}


		/// <summary>
		/// Function called by the auto-repeat timer.
		/// </summary>
		/// <param name="sender">The sender of the event.</param>
		/// <param name="e">The event arguments.</param>
		private void AutoRepeatTime_Elapsed(object sender, EventArgs e)
		{
			mAutoRepeatTimer.Stop();
			StartTransaction();
		}


		/// <summary>
		/// Default constructor.
		/// </summary>
		public MainForm()
		{
			InitializeComponent();

			// Set the title.
			this.Text = ChessPt.Utilities.Forms.AboutBox.AssemblyProduct + " v" + ChessPt.Utilities.Forms.AboutBox.AssemblyVersion;

			// Display the initial amount and disable buttons not applicable when not connected.
			FormatAmount();
			EnableControls(false, false);

			chMessages.Width = listViewMessages.Width - 24;

			// Fill the transaction types.
			cbTransactionType.Items.Add(TlvLib.TransactionType.Payment);
			cbTransactionType.Items.Add(TlvLib.TransactionType.DeferredPayment);
//			cbTransactionType.Items.Add(TlvLib.TransactionType.CashAdvance);
			cbTransactionType.Items.Add(TlvLib.TransactionType.PreAuthorization);
			cbTransactionType.Items.Add(TlvLib.TransactionType.UpdatePreAuthorization);
			cbTransactionType.Items.Add(TlvLib.TransactionType.PaymentCompletion);
			cbTransactionType.Items.Add(TlvLib.TransactionType.CardValidityCheck);
			cbTransactionType.Items.Add(TlvLib.TransactionType.Refund);
			cbTransactionType.Items.Add(TlvLib.TransactionType.Cancellation);
			cbTransactionType.Items.Add(TlvLib.TransactionType.CancellationPayment);
			cbTransactionType.Items.Add(TlvLib.TransactionType.CancellationCashAdvance);
			cbTransactionType.Items.Add(TlvLib.TransactionType.CancellationPreAuthorization);
			cbTransactionType.Items.Add(TlvLib.TransactionType.CancellationPaymentCompletion);
			cbTransactionType.Items.Add(TlvLib.TransactionType.OriginalCredit);
			cbTransactionType.SelectedIndex = 0;

			//			txtCardholderTicket.Text = "123456789012345678901234";

			// Fill the transaction mode.
			comboboxTransactionMode.Items.Add(TlvLib.IntermediateResultMode.None);
			comboboxTransactionMode.Items.Add(TlvLib.IntermediateResultMode.IntermediateResult);
			comboboxTransactionMode.Items.Add(TlvLib.IntermediateResultMode.IntermediateResultNoResponse);
			comboboxTransactionMode.SelectedIndex = 0;

			// Set the auto-repeat timer handler.
			mAutoRepeatTimer.Tick += AutoRepeatTime_Elapsed;
		}


		/// <summary>
		/// The form is loaded.
		/// </summary>
		/// <param name="sender">The sender of the event.</param>
		/// <param name="e">The event arguments.</param>
		private void MainForm_Load(object sender, EventArgs e)
		{
			// Start waiting for client thread.
			mThread = new Thread(ThreadFunction);
			mThread.IsBackground = false;
			mThread.Start();
		}


		/// <summary>
		/// Thread function managing waiting for a connection with the terminal
		/// and processing messages from the terminal.
		/// </summary>
		private void ThreadFunction()
		{
			try
			{
				// Keep waiting for clients also after one disconnected.
				while (mThread != null)
				{
					mCounterKeepAlive = 0;
					mCounterStatusUpdate = 0;
					mKeepAliveTimeLast = DateTime.MinValue;

					// Wait for a connection, exit when there was an error.
					if (!WaitForClient()) break;

					// Client connected, process incoming messages.
					if (mConnectionHandler != null)
					{
						// Process incoming message until disconnected.
						if (mConnectionHandler.ProcessMessages() == false)
						{
							SetStatusMessage("Terminal disconnected unexpected.");
						}

						// Client disconnected, disable keep-alive timer.
						if (mKeepAliveTimer != null)
						{
							mKeepAliveTimer.Stop();
							mKeepAliveTimer = null;
						}
						mConnectionHandler = null;
						ClientDisconnected();
					}
				}
			}
			catch (Exception)
			{
				AddMessage("Exception in connection handler thread, connection lost.");
			}
		}


		/// <summary>
		/// Wait for a connection with a terminal.
		/// </summary>
		/// <returns>True when connection, False when error occurred.</returns>
		private bool WaitForClient()
		{
			DisplayKeepAlive();

			// Wait for client connection.
			try
			{
				// Determine the connection type and create it.
				switch ((ConnectionType)Properties.Settings.Default.ConnectionType)
				{
					case ConnectionType.Tcp:
						{
							// Retrieve the port to use from the settings.
							int port = Properties.Settings.Default.TcpPort;
							SetStatusMessage(String.Format("Waiting for terminal on TCP port {0}", port));
							mConnectionHandler = new TcpConnectionHandler(port, this);
							break;
						}

					case ConnectionType.Serial:
						{
							// Retrieve the connection parameters from the settings.
							string comPort = Properties.Settings.Default.ComPort;
							int baudRate = Properties.Settings.Default.BaudRate;
							int dataBits = Properties.Settings.Default.DataBits;
							System.IO.Ports.Parity parity = Properties.Settings.Default.Parity;
							System.IO.Ports.StopBits stopBits = Properties.Settings.Default.StopBits;
							System.IO.Ports.Handshake flowControl = Properties.Settings.Default.FlowControl;

							// Open a connection
							SetStatusMessage(String.Format("Waiting for terminal on serial port {0}. Connection settings: [baud rate: {1}, data bits: {2}, parity: {3}, stop bits: {4}, flow control: {5}]", comPort, baudRate, dataBits, parity, stopBits, flowControl));
							mConnectionHandler = new SerialConnectionHandler(comPort, baudRate, dataBits, parity, stopBits, flowControl, this);
							break;
						}
				}

				// Make a connection.
				mConnectionHandler.Connect();
				ClientConnected();
			}
			catch (Exception ex)
			{
				// An error occurred.
				SetStatusMessage(String.Format("Exception: " + ex.Message));
				mConnectionHandler = null;
				return false;
			}

			// All OK.
			return true;
		}


		/// <summary>
		/// Enable/disable controls depending on the connection state (can be called from non GUI threads).
		/// </summary>
		/// <param name="enable">True when the controls should be enabled.</param>
		/// <param name="enableCancel">True when the cancel button should be enabled.</param>
		private void EnableControls(bool enable, bool enableCancel)
		{
			// Check if the current thread is the GUI thread.
			if (this.InvokeRequired)
			{
				// Execute this method on the control's thread
				this.Invoke(new Action( () => EnableControls(enable, enableCancel) ));
			}
			else
			{
				btnOK.Enabled = enable;
				btnCancel.Enabled = enableCancel;

				gbAcquirerMessages.Enabled = enable;
				gbTotals.Enabled = enable;
				gbOther.Enabled = enable;
				gbTransparentMode.Enabled = enable || mTransparentModeState;

				buttonTmAuthenticate.Enabled = mTransparentModeState;
				buttonTmReadCardData.Enabled = mTransparentModeState;
				buttonTmUiControl.Enabled = mTransparentModeState;
			}
		}


		/// <summary>
		/// The form is closing. Send disconnect message to terminal.
		/// </summary>
		/// <param name="sender">The sender of the event.</param>
		/// <param name="e">The event arguments.</param>
		private void MainForm_FormClosing(object sender, FormClosingEventArgs e)
		{
			// Remember the thread handle for sending a cancellation if it is in a blocking call.
			Thread thread = mThread;

			// The thread must stop itself after receiving response.
			mThread = null;

			// Send disconnect message only if there is an connection.
			if (mConnectionHandler != null)
			{
				// Send disconnect message to terminal.
				//				mConnectionHandler.SendDisconnect(true);

				mConnectionHandler.Close();
			}

			// Interrupt a blocking call in the thread so it can exit.
			//			thread.Interrupt();
			Thread.Sleep(500);
			Application.DoEvents();
			thread.Join(1000);
		}


		/// <summary>
		/// The size of the list view changed. Adjust column widths.
		/// </summary>
		/// <param name="sender">The sender of the event.</param>
		/// <param name="e">The event arguments</param>
		private void listView_SizeChanged(object sender, EventArgs e)
		{
			chMessages.Width = listViewMessages.Width - 24;
		}


		/// <summary>
		/// Clear the ticket text boxes.
		/// </summary>
		private void ClearTickets()
		{
			txtCardholderTicket.Clear();
			txtMerchantTicket.Clear();
			txtJournalTicket.Clear();
		}


		#region GUI functions called from the message handler functions.


		/// <summary>
		/// Display a message (can be called from non GUI threads).
		/// Displays it in list view.
		/// </summary>
		/// <param name="msg">The message to display.</param>
		public void AddMessage(string msg, bool bold = false, Color backgroundColor = new Color(), Color textColor = new Color())
		{
			// Check if the current thread is the GUI thread.
			if (this.InvokeRequired)
			{
				// Execute this method on the control's thread
				this.Invoke(new Action( () => AddMessage(msg, bold, backgroundColor, textColor) ));
			}
			else
			{
				// Current thread was the GUI thread, add the text. 
				ListViewItem item = listViewMessages.Items.Add(msg != null ? String.Format("{0:yyyy-MM-dd hh:mm:ss}", DateTime.Now) : "");
				item.SubItems.Add(msg);

				// Set the bold state of the text.
				if (bold)
				{
					item.Font = new Font(item.Font, FontStyle.Bold);
				}

				// Set the items background color.
				if (!backgroundColor.IsEmpty)
				{
					item.BackColor = backgroundColor;
				}

				// Set the items text color.
				if (!textColor.IsEmpty)
				{
					item.ForeColor = textColor;
				}

				// Make sure the item is visible.
				item.EnsureVisible();
			}
		}


		/// <summary>
		/// Display the keep-alive status.
		/// </summary>
		public void DisplayKeepAlive()
		{
			// Check if the current thread is the GUI thread.
			if (this.InvokeRequired)
			{
				// Execute this method on the control's thread
				this.Invoke(new Action( () => DisplayKeepAlive() ));
			}
			else
			{
				// Display status update counter.
				if (mCounterStatusUpdate != 0)
				{
					lblStatus_StatusUpdates.Text = String.Format("Received status updates: {0}", mCounterStatusUpdate);
				}
				else
				{
					lblStatus_StatusUpdates.Text = "Waiting for status updates...";
				}

				// Display keep-alive counter.
				if (mCounterKeepAlive == 0)
				{
					lblStatus_KeepAlive.Text = "Waiting for keep-alive...";
				}
				else if (mKeepAliveTimeLast == DateTime.MinValue)
				{
					lblStatus_KeepAlive.Text = String.Format("Received keep-alives: {0}", mCounterKeepAlive);
				}
				else
				{
					lblStatus_KeepAlive.Text = String.Format("Received keep-alives: {0} [Interval: {1:f2} s.]", mCounterKeepAlive, (mKeepAliveTimeCurrent - mKeepAliveTimeLast).TotalSeconds);
				}
			}
		}


		/// <summary>
		/// Display a ticket (can be called from non GUI threads).
		/// </summary>
		/// <param name="cardholderTicket">The cardholder ticket to display or null if no ticket.</param>
		/// <param name="merchantTicket">The merchant ticket to display or null if no ticket.</param>
		/// <param name="journalTicket">The journal ticket to display or null if no ticket.</param>
		public void DisplayTickets(string cardholderTicket, string merchantTicket, string journalTicket)
		{
			// Check if the current thread is the GUI thread.
			if (this.InvokeRequired)
			{
				// Execute this method on the control's thread
				this.Invoke(new Action( () => DisplayTickets(cardholderTicket, merchantTicket, journalTicket) ));
			}
			else
			{
				// Current thread was the GUI thread, add the text. 
				if (cardholderTicket != null) txtCardholderTicket.Text = FixLineEndings(cardholderTicket);
				if (merchantTicket != null) txtMerchantTicket.Text = FixLineEndings(merchantTicket);
				if (journalTicket != null) txtJournalTicket.Text = FixLineEndings(journalTicket);
			}
		}


		/// <summary>
		/// Fix the line endings to \r\n.
		/// </summary>
		/// <param name="str">The string to fix.</param>
		/// <returns>The fixed string.</returns>
		private string FixLineEndings(string str)
		{
			// Replace "\n" with "\r\n".
			str = str.Replace("\n", "\r\n");

			// Replace "\r\r" with "\r" in case the string already had "\r\n".
			str = str.Replace("\r\r", "\r");

			return str;
		}


		/// <summary>
		/// Set the status message (can be called from non GUI threads).
		/// </summary>
		/// <param name="msg">The message to display.</param>
		private void SetStatusMessage(string msg)
		{
			// Check if the current thread is the GUI thread.
			if (this.InvokeRequired)
			{
				// Execute this method on the control's thread
				this.Invoke(new Action( () => SetStatusMessage(msg) ));
			}
			else
			{
				// Current thread was the GUI thread, update status label and add to list.
				lblStatus.Text = msg;
				AddMessage(msg, false, Color.FromArgb(255, 200, 200));
			}
		}


		/// <summary>
		/// Set the status message (can be called from non GUI threads).
		/// </summary>
		/// <param name="msg">The message to display.</param>
		private void SetMerchantMessage(string msg)
		{
			// Check if the current thread is the GUI thread.
			if (this.InvokeRequired)
			{
				// Execute this method on the control's thread
				this.Invoke(new Action(() => SetMerchantMessage(msg)));
			}
			else
			{
				// Current thread was the GUI thread, update status label and add to list.
				lblMerchantMessage.Text = msg;
				AddMessage(msg, false, Color.White, Color.DarkGreen);
			}
		}


		/// <summary>
		/// Display the intermediate result and send back confirmation/rejection to terminal (can be called from non GUI threads).
		/// </summary>
		/// <param name="transactionResult">The intermediate transaction result.</param>
		/// <param name="authorisedAmount">The authorised amount from the host.</param>
		/// <param name="mode">The intermediate result mode.</param>
		private void DisplayIntermediateResult(TlvLib.TransactionResult transactionResult, uint authorisedAmount, TlvLib.IntermediateResultMode mode)
		{
			// Check if the current thread is the GUI thread.
			if (this.InvokeRequired)
			{
				// Execute this method on the control's thread.
				// Since a blocking dialog is opened BeginInvoke() is used. Invoke() will block until complete and thus result in keep-alive time-out.
				this.BeginInvoke(new Action( () => DisplayIntermediateResult(transactionResult, authorisedAmount, mode) ));
			}
			else
			{
				// Current thread was the GUI thread.

				// Display result and ask for confirmation.
				IntermediateResultForm frm = new IntermediateResultForm(transactionResult, authorisedAmount, authorisedAmount == 0 ? 0 : mAmount, mode);
				DialogResult result = frm.ShowDialog();

				// No response needed when IntermediateResultNoResponse mode.
				if (mode == TlvLib.IntermediateResultMode.IntermediateResultNoResponse) return;

				// Send response when in intermediate result mode or when deferred sale (authorised amount set).
				if (result == DialogResult.Yes)
				{
					if (mode == TlvLib.IntermediateResultMode.IntermediateResult || authorisedAmount != 0)
					{
						SendSignalIntermediateResultReply(true, frm.FinalTransactionAmount);
					}
				}
				else
				{
					if (mode == TlvLib.IntermediateResultMode.IntermediateResult || authorisedAmount != 0)
					{
						SendSignalIntermediateResultReply(false, 0);
					}
				}
			}
		}


		/// <summary>
		/// A client has connected (can be called from non GUI threads).
		/// Enables additional controls.
		/// </summary>
		private void ClientConnected()
		{
			// Check if the current thread is the GUI thread.
			if (this.InvokeRequired)
			{
				// Execute this method on the control's thread
				this.Invoke(new Action( () => ClientConnected() ));
			}
			else
			{
				// Current thread was the GUI thread.
				SetStatusMessage("Connection open. Now listening.");
			}
		}


		/// <summary>
		/// A client has connected (can be called from non GUI threads).
		/// Disables additional controls.
		/// </summary>
		private void ClientDisconnected()
		{
			// Check if the current thread is the GUI thread.
			if (this.InvokeRequired)
			{
				// Execute this method on the control's thread.
				this.Invoke(new Action( () => ClientDisconnected() ));
			}
			else
			{
				// Current thread was the GUI thread.
				SetStatusMessage("Client disconnected.");
				mTransparentModeState = false;
				EnableControls(false, false);
			}
		}


		#endregion


		#region Menu Handlers


		/// <summary>
		/// Show the settings dialog box.
		/// </summary>
		/// <param name="sender">The sender of the event.</param>
		/// <param name="e">The event arguments.</param>
		private void menuSettings_Configure_Click(object sender, EventArgs e)
		{
			Forms.SettingsForm frmSettings = new Forms.SettingsForm();
			frmSettings.ShowDialog();
		}


		/// <summary>
		/// Show the transparent mode settings dialog box.
		/// </summary>
		/// <param name="sender">The sender of the event.</param>
		/// <param name="e">The event arguments.</param>
		private void menuSettings_TransparentMode_Click(object sender, EventArgs e)
		{
			Forms.TmSettingsForm frmSettings = new Forms.TmSettingsForm();
			frmSettings.ShowDialog();
		}


		/// <summary>
		/// Show the about box. 
		/// </summary>
		/// <param name="sender">The sender of the event.</param>
		/// <param name="e">The event arguments.</param>
		private void menuHelp_About_Click(object sender, EventArgs e)
		{
			ChessPt.Utilities.Forms.AboutBox frmAbout = new ChessPt.Utilities.Forms.AboutBox();
			frmAbout.ShowDialog();
		}


		/// <summary>
		/// The clear message context menu item was clicked.
		/// </summary>
		/// <param name="sender">The sender of the event.</param>
		/// <param name="e">The event arguments.</param>
		private void cmMessagesClear_Click(object sender, EventArgs e)
		{
			listViewMessages.Items.Clear();
		}


		#endregion


		#region Handle the transaction related button clicks and supporting functionality.


		/// <summary>
		/// Format the amount with currency symbol and dots.
		/// </summary>
		private void FormatAmount()
		{
			// Format the amount and place in the amount text box.
			txtAmount.Text = String.Format("{0:C}", mAmount / 100.0);
		}


		/// <summary>
		/// A "numeric" button was pressed.
		/// Adapt the amount.
		/// </summary>
		/// <param name="sender">The sender of the event.</param>
		/// <param name="e">The event arguments.</param>
		private void NumericButtonClick(object sender, EventArgs e)
		{
			// Increase the amount with the selected digit.
			uint value = UInt32.Parse((sender as Button).Text);
			uint amount = mAmount * 10 + value;

			// Set new amount if not too big.
			if (amount < 1000000)
			{
				mAmount = amount;
				FormatAmount();
			}
		}


		/// <summary>
		/// The "correction" button was pressed. Reset the amount to zero.
		/// </summary>
		/// <param name="sender">The sender of the event.</param>
		/// <param name="e">The event arguments.</param>
		private void btnCorrection_Click(object sender, EventArgs e)
		{
			// Reset the amount.
			mAmount = 0;
			FormatAmount();
		}


		/// <summary>
		/// The "OK" button was pressed. Send the amount to the terminal.
		/// </summary>
		/// <param name="sender">The sender of the event.</param>
		/// <param name="e">The event arguments.</param>
		private void btnOK_Click(object sender, EventArgs e)
		{
			StartTransaction();
		}


		/// <summary>
		/// The "Cancel" button was clicked. Send cancel request.
		/// </summary>
		/// <param name="sender">The sender of the event.</param>
		/// <param name="e">The event arguments.</param>
		private void btnCancel_Click(object sender, EventArgs e)
		{
			// Create request message.
			TlvLib.TlvMessageEcr requestMessage = CreateMessage(TlvLib.MessageType.CancelRequest);

			// Fill the reason.
			requestMessage.Body.AddTlvUInt8AsHex((uint)TlvLib.Tag.CancelReason, (byte)TlvLib.CancelReason.Manual);

			// Send the message.
			try
			{
				mConnectionHandler.SendMessage(requestMessage);
				ConnectionHandler.WriteToFile(requestMessage, "CancelRequest.msg");
			}
			catch (Exception ex)
			{
				AddMessage(String.Format("Error sending cancel request: {0)", ex.Message), true, Color.White, Color.Red);
			}
		}


		/// <summary>
		/// Start a transaction (can be called from non GUI threads).
		/// </summary>
		private void StartTransaction()
		{
			// Check if the current thread is the GUI thread.
			if (this.InvokeRequired)
			{
				// Execute this method on the control's thread.
				this.Invoke(new Action( () => StartTransaction() ));
			}
			else
			{
				// Current thread was the GUI thread.
				mTransparantModeCardUid = null;

				// Retrieve the transaction type to determine if an authorisation code or token should be asked.
				TlvLib.TransactionType transactionType = (TlvLib.TransactionType)cbTransactionType.SelectedItem;

				// Process manager password.
				if (!ProcessManagerPassword(transactionType)) return;

				// Process the authorisation code.
				string authorisationCode;
				if (!ProcessAuthorisationCode(transactionType, out authorisationCode)) return;

				// Process the token.
				string token;
				if (!ProcessToken(transactionType, out token)) return;

				// Disable the controls (till transaction reply).
				EnableControls(false, true);

				// Empty the ticket text boxes.
				ClearTickets();

				// Set initial message.
				lblMerchantMessage.Text = "Transaction started...";
				AddMessage(null);
				AddMessage(lblMerchantMessage.Text, true, Color.OliveDrab, Color.White);

				// Create request message.
				TlvLib.TlvMessageEcr requestMessage = CreateMessage(TlvLib.MessageType.TransactionRequest);

				// TODO: Determine transaction language.

				// Create transaction data.
				TlvLib.TlvConstructed tlvTransactionData = new TlvLib.TlvConstructed((uint)TlvLib.Tag.Group_TransactionData);
				tlvTransactionData.AddTlvUInt32AsBcd((uint)TlvLib.Tag.Amount, mAmount);
				tlvTransactionData.AddTlvUInt16AsBcd((uint)TlvLib.Tag.CurrencyCode, 978);		// Euro.
				tlvTransactionData.AddTlvUInt8AsBcd((uint)TlvLib.Tag.CurrencyExponent, 2);		// Cents.
				tlvTransactionData.AddTlvAsString((uint)TlvLib.Tag.MerchantTransactionReference, txtReference.Text);
				tlvTransactionData.AddTlvUInt8AsHex((uint)TlvLib.Tag.TransactionType, (byte)transactionType);
				tlvTransactionData.AddTlvUInt8AsHex((uint)TlvLib.Tag.IntermediateResultMode, (byte)(TlvLib.IntermediateResultMode)comboboxTransactionMode.SelectedItem);

				// As there currently is no GUI to set the initial card holder language for a transaction, 
				// we temporary derive the initial card holder language from the cents part of the transaction amount.
				// TODO: make GUI for selecting the initial card holder language.
				uint cents = mAmount % 100;
				switch (cents)
				{
					case 14:
						tlvTransactionData.AddTlvAsString((uint)TlvLib.Tag.CardHolderLanguage, "nl");
						break;
					case 15:
						tlvTransactionData.AddTlvAsString((uint)TlvLib.Tag.CardHolderLanguage, "en");
						break;
					case 16:
						tlvTransactionData.AddTlvAsString((uint)TlvLib.Tag.CardHolderLanguage, "de");
						break;
					case 17:
						tlvTransactionData.AddTlvAsString((uint)TlvLib.Tag.CardHolderLanguage, "fr");
						break;
					default:
						break;
				}

				if (Properties.Settings.Default.TransactionMode != -1)
				{
					tlvTransactionData.AddTlvUInt8AsHex((uint)TlvLib.Tag.TransactionMode, (byte)Properties.Settings.Default.TransactionMode);
				}
				if (authorisationCode != null)
				{
					tlvTransactionData.AddTlvAsString((uint)TlvLib.Tag.AutorisationCode, authorisationCode);
				}
				if (token != null)
				{
					tlvTransactionData.AddTlvAsString((uint)TlvLib.Tag.Token, token);
				}
				requestMessage.Body.AddTlv(tlvTransactionData);

				// Create print data.
				// As there currently in no GUI to set the print origin & paper width,
				// we temporary derive the print origin from the cents part of the transaction amount.
				// TODO: Create GUI to enter the print origin and paper width.
				TlvLib.TlvConstructed tlvPrintData = new TlvLib.TlvConstructed((uint)TlvLib.Tag.Group_PrintData);
				if (cents == 19)
				{
					tlvPrintData.AddTlvUInt8AsHex((uint)TlvLib.Tag.PrintOrigin, (byte)TlvLib.PrintOrigin.Terminal);
				}
				else
				{
					tlvPrintData.AddTlvUInt8AsHex((uint)TlvLib.Tag.PrintOrigin, (byte)TlvLib.PrintOrigin.CashRegister);
				}
				tlvPrintData.AddTlvUInt8AsBcd((uint)TlvLib.Tag.PaperWidth, (byte)36);
				requestMessage.Body.AddTlv(tlvPrintData);

				// Set transaction ID.
				requestMessage.Body.AddTlvUInt64AsHex((uint)TlvLib.Tag.TransactionId, mTransactionId++);

				// Add transparent mode group.
				if (checkboxEnableTransparentMode.Checked)
				{
					TlvLib.TlvConstructed tlvGroupTransparentMode = new TlvLib.TlvConstructed((uint)TlvLib.Tag.Group_TmTransparentMode);
					tlvGroupTransparentMode.AddTlvUInt8AsHex((uint)TlvLib.Tag.TmTransparentMode, 1);
					requestMessage.Body.AddTlv(tlvGroupTransparentMode);
				}

				// Send the message.
				try
				{
					mConnectionHandler.SendMessage(requestMessage);
					ConnectionHandler.WriteToFile(requestMessage, "TransactionRequest.msg");
				}
				catch (Exception ex)
				{
					AddMessage(String.Format("Error sending transaction request: {0}", ex.Message), true, Color.White, Color.Red);
				}

			}
		}


		/// <summary>
		/// Process the entry of the manager password.
		/// Some transaction types like refund need a password.
		/// </summary>
		/// <param name="transactionType">The type of the transaction.</param>
		/// <returns>True if transaction allowed by manager.</returns>
		bool ProcessManagerPassword(TlvLib.TransactionType transactionType)
		{
			// When cancellation or refund, ask for manager code.
			if (transactionType == TlvLib.TransactionType.Cancellation ||
				transactionType == TlvLib.TransactionType.CancellationPayment ||
				transactionType == TlvLib.TransactionType.CancellationCashAdvance ||
				transactionType == TlvLib.TransactionType.CancellationPreAuthorization ||
				transactionType == TlvLib.TransactionType.CancellationPaymentCompletion ||
				transactionType == TlvLib.TransactionType.Refund)
			{
				// Ask for manager password until correct or cancelled.
				string managerPassword;
				while (true)
				{
					// Ask for manager password.
					if (ChessPt.Utilities.Forms.InputDialog.Show("This transaction type requires confirmation using manager password. Enter manager password:", "Manager Password", out managerPassword) != DialogResult.OK)
					{
						// Exit when no manager password was entered.
						return false;
					}

					// Exit loop when entered code is correct.
					if (managerPassword == Properties.Settings.Default.ManagerPassword) break;
					else
					{
						// Show error dialog, exit when cancelled.
						if (MessageBox.Show("Wrong manager password", "Wrong Password", MessageBoxButtons.RetryCancel, MessageBoxIcon.Error) == DialogResult.Cancel)
						{
							return false;
						}
					}
				}
			}

			// Password OK or no need for password, continue.
			return true;
		}


		/// <summary>
		/// Process the entry of an authorisation code.
		/// Cancellation transaction types need an authorisation code.
		/// </summary>
		/// <param name="transactionType">The type of the transaction.</param>
		/// <param name="authorisationCode">The entered authorisation code.</param>
		/// <returns>True if transaction allowed by manager.</returns>
		bool ProcessAuthorisationCode(TlvLib.TransactionType transactionType, out string authorisationCode)
		{
			// Initially no authorisation code.
			authorisationCode = null;

			// When cancellation, ask for authorisation code.
			if (transactionType == TlvLib.TransactionType.Cancellation ||
				transactionType == TlvLib.TransactionType.CancellationPayment ||
				transactionType == TlvLib.TransactionType.CancellationCashAdvance ||
				transactionType == TlvLib.TransactionType.CancellationPreAuthorization ||
				transactionType == TlvLib.TransactionType.CancellationPaymentCompletion)
			{
				if (ChessPt.Utilities.Forms.InputDialog.Show("Enter the authorisation code of the transaction to cancel:", "Authorisation code", out authorisationCode) != DialogResult.OK)
				{
					// Exit when no authorisation code was entered.
					return false;
				}
			}

			// When payment completion, ask for authorisation code.
			if (transactionType == TlvLib.TransactionType.PaymentCompletion)
			{
				if (ChessPt.Utilities.Forms.InputDialog.Show("Enter the authorisation code of the transaction to complete:", "Authorisation code", out authorisationCode) != DialogResult.OK)
				{
					// Exit when no authorisation code was entered.
					return false;
				}
			}

			// When update pre-authorisation, ask for authorisation code.
			if (transactionType == TlvLib.TransactionType.UpdatePreAuthorization)
			{
				if (ChessPt.Utilities.Forms.InputDialog.Show("Enter the authorisation code of the transaction to complete:", "Authorisation code", out authorisationCode) != DialogResult.OK)
				{
					// Exit when no authorisation code was entered.
					return false;
				}
			}

			// Authorisation code entered or no authorisation code needed, continue.
			return true;
		}


		/// <summary>
		/// Process the entry of a token code.
		/// Update pre-authorisation, payment completion and cancallation of pre-authorisation transaction types need a token.
		/// </summary>
		/// <param name="transactionType">The type of the transaction.</param>
		/// <param name="token">The entered token code.</param>
		/// <returns>True if transaction allowed by manager.</returns>
		bool ProcessToken(TlvLib.TransactionType transactionType, out string token)
		{
			// Initially no token.
			token = null;

			// When pre-authorisation, ask for token.
			if (transactionType == TlvLib.TransactionType.UpdatePreAuthorization ||
				transactionType == TlvLib.TransactionType.PaymentCompletion ||
				transactionType == TlvLib.TransactionType.CancellationPreAuthorization)
			{
				// Ask for the token until it satisfies the Luhn check.
				bool tokenValid = false;
				while (!tokenValid)
				{
					if (ChessPt.Utilities.Forms.InputDialog.Show("Enter the token of the pre-authorisation:", "Token", out token) != DialogResult.OK)
					{
						// Exit when no authorisation code was entered.
						return false;
					}

					// Check the token in case one was entered.
					tokenValid = token.Length != 0 ? ChessPt.Utilities.LuhnCheck.LuhnCheckMod10Plus1(token) : true;
					if (!tokenValid)
					{
						if (MessageBox.Show("Invalid token. Try again.", "Error", MessageBoxButtons.RetryCancel, MessageBoxIcon.Error) == DialogResult.Cancel)
						{
							return false;
						}
					}
				}
			}

			// Token entered or no token required, continue.
			return true;
		}


		#endregion


		#region Handle the acquirer messages button clicks.

		/// <summary>
		/// The "key load" button was clicked.
		/// </summary>
		/// <param name="sender">The sender of the event.</param>
		/// <param name="e">The event arguments.</param>
		private void btnKeyLoad_Click(object sender, EventArgs e)
		{
			// Disable the controls.
			EnableControls(false, false);

			// Empty the ticket text boxes.
			ClearTickets();

			// Set initial message.
			lblMerchantMessage.Text = "Requesting SchemeList...";
			AddMessage(null);
			AddMessage(lblMerchantMessage.Text, true, Color.OliveDrab);

			// Create request message.
			TlvLib.TlvMessageEcr requestMessage = CreateMessage(TlvLib.MessageType.SecuritySchemeListRequest);

			// Send the message.
			try
			{
				mConnectionHandler.SendMessage(requestMessage);
				ConnectionHandler.WriteToFile(requestMessage, "SchemeListRequest.msg");
			}
			catch (Exception ex)
			{
				AddMessage(String.Format("Error sending SchemeList request: {0)", ex.Message), true, Color.White, Color.Red);
			}
		}


		/// <summary>
		/// The "parameter download" button was clicked.
		/// </summary>
		/// <param name="sender">The sender of the event.</param>
		/// <param name="e">The event arguments.</param>
		private void btnParameterDownload_Click(object sender, EventArgs e)
		{
			// Disable the controls.
			EnableControls(false, false);

			// Empty the ticket text boxes.
			ClearTickets();

			// Set initial message.
			lblMerchantMessage.Text = "Requesting ParameterDownload...";
			AddMessage(null);
			AddMessage(lblMerchantMessage.Text, true, Color.OliveDrab);

			// Create request message.
			TlvLib.TlvMessageEcr requestMessage = CreateMessage(TlvLib.MessageType.AcquirerListRequest);

			// Send the message.
			try
			{
				mConnectionHandler.SendMessage(requestMessage);
				ConnectionHandler.WriteToFile(requestMessage, "AcquirerListRequest.msg");
			}
			catch (Exception ex)
			{
				AddMessage(String.Format("Error sending AcquirerList request: {0)", ex.Message), true, Color.White, Color.Red);
			}
		}


		/// <summary>
		/// The "send open messages" button was clicked.
		/// </summary>
		/// <param name="sender">The sender of the event.</param>
		/// <param name="e">The event arguments.</param>
		private void btnSendOpenMessages_Click(object sender, EventArgs e)
		{
			// Disable the controls.
			EnableControls(false, false);

			// Empty the ticket text boxes.
			ClearTickets();

			// Set initial message.
			lblMerchantMessage.Text = "Requesting OpenMessages...";
			AddMessage(null);
			AddMessage(lblMerchantMessage.Text, true, Color.OliveDrab);

			mPendingMessagesOperation = TlvLib.PendingMessagesOperation.Send;

			// Create request message.
			TlvLib.TlvMessageEcr requestMessage = CreateMessage(TlvLib.MessageType.AcquirerListPendingMessagesRequest);

			// Send the message.
			try
			{
				mConnectionHandler.SendMessage(requestMessage);
				ConnectionHandler.WriteToFile(requestMessage, "AcquirerListForOpenMessagesRequest.msg");
			}
			catch (Exception ex)
			{
				AddMessage(String.Format("Error sending AcquirerListForOpenMessages request: {0)", ex.Message), true, Color.White, Color.Red);
			}
		}


		/// <summary>
		/// The "delete open messages" button was clicked.
		/// </summary>
		/// <param name="sender">The sender of the event.</param>
		/// <param name="e">The event arguments.</param>
		private void btnDeleteOpenMessages_Click(object sender, EventArgs e)
		{
			// Disable the controls.
			EnableControls(false, false);

			// Empty the ticket text boxes.
			ClearTickets();

			// Set initial message.
			lblMerchantMessage.Text = "Requesting OpenMessages...";
			AddMessage(null);
			AddMessage(lblMerchantMessage.Text, true, Color.OliveDrab);

			mPendingMessagesOperation = TlvLib.PendingMessagesOperation.Delete;

			// Create request message.
			TlvLib.TlvMessageEcr requestMessage = CreateMessage(TlvLib.MessageType.AcquirerListPendingMessagesRequest);

			// Send the message.
			try
			{
				mConnectionHandler.SendMessage(requestMessage);
				ConnectionHandler.WriteToFile(requestMessage, "AcquirerListForOpenMessagesRequest.msg");
			}
			catch (Exception ex)
			{
				AddMessage(String.Format("Error sending AcquirerListForOpenMessages request: {0)", ex.Message), true, Color.White, Color.Red);
			}
		}


		#endregion


		#region Handle the totals messages button clicks


		/// <summary>
		/// The "X-totals" button was clicked.
		/// </summary>
		/// <param name="sender">The sender of the event.</param>
		/// <param name="e">The event arguments.</param>
		private void btnXTotals_Click(object sender, EventArgs e)
		{
			// Disable the controls.
			EnableControls(false, false);

			// Empty the ticket text boxes.
			ClearTickets();

			lblMerchantMessage.Text = "Requesting X-Totals...";
			AddMessage(null);
			AddMessage(lblMerchantMessage.Text, true, Color.OliveDrab);

			// Create request message.
			TlvLib.TlvMessageEcr requestMessage = CreateMessage(TlvLib.MessageType.TotalsRequest);

			requestMessage.Body.AddTlvUInt8AsBcd((uint)TlvLib.Tag.TotalsType, (byte)TlvLib.TotalsType.X);

			// Create print data.
			TlvLib.TlvConstructed tlvPrintData = new TlvLib.TlvConstructed((uint)TlvLib.Tag.Group_PrintData);
			tlvPrintData.AddTlvUInt8AsHex((uint)TlvLib.Tag.PrintOrigin, (byte)TlvLib.PrintOrigin.CashRegister);
			requestMessage.Body.AddTlv(tlvPrintData);

			// Send the message.
			try
			{
				mConnectionHandler.SendMessage(requestMessage);
				ConnectionHandler.WriteToFile(requestMessage, "TotalsRequest.msg");
			}
			catch (Exception ex)
			{
				AddMessage(String.Format("Error sending Totals request: {0)", ex.Message), true, Color.White, Color.Red);
			}
		}


		/// <summary>
		/// The "Z-totals" button was clicked.
		/// </summary>
		/// <param name="sender">The sender of the event.</param>
		/// <param name="e">The event arguments.</param>
		private void btnZTotals_Click(object sender, EventArgs e)
		{
			// Disable the controls.
			EnableControls(false, false);

			// Empty the ticket text boxes.
			ClearTickets();

			lblMerchantMessage.Text = "Requesting Z-Totals...";
			AddMessage(null);
			AddMessage(lblMerchantMessage.Text, true, Color.OliveDrab);

			// Create request message.
			TlvLib.TlvMessageEcr requestMessage = CreateMessage(TlvLib.MessageType.TotalsRequest);

			requestMessage.Body.AddTlvUInt8AsBcd((uint)TlvLib.Tag.TotalsType, (byte)TlvLib.TotalsType.Z);

			// Create print data.
			TlvLib.TlvConstructed tlvPrintData = new TlvLib.TlvConstructed((uint)TlvLib.Tag.Group_PrintData);
			tlvPrintData.AddTlvUInt8AsHex((uint)TlvLib.Tag.PrintOrigin, (byte)TlvLib.PrintOrigin.CashRegister);
			requestMessage.Body.AddTlv(tlvPrintData);

			// Send the message.
			try
			{
				mConnectionHandler.SendMessage(requestMessage);
				ConnectionHandler.WriteToFile(requestMessage, "TotalsRequest.msg");
			}
			catch (Exception ex)
			{
				AddMessage(String.Format("Error sending Totals request: {0)", ex.Message), true, Color.White, Color.Red);
			}
		}


		/// <summary>
		/// The "current period totals" button was clicked.
		/// </summary>
		/// <param name="sender">The sender of the event.</param>
		/// <param name="e">The event arguments.</param>
		private void btnCurrentPeriodTotals_Click(object sender, EventArgs e)
		{
			// Disable the controls.
			EnableControls(false, false);

			// Empty the ticket text boxes.
			ClearTickets();

			lblMerchantMessage.Text = "Requesting Current Period Totals...";
			AddMessage(null);
			AddMessage(lblMerchantMessage.Text, true, Color.OliveDrab);

			// Create request message.
			TlvLib.TlvMessageEcr requestMessage = CreateMessage(TlvLib.MessageType.TotalsRequest);

			requestMessage.Body.AddTlvUInt8AsBcd((uint)TlvLib.Tag.TotalsType, (byte)TlvLib.TotalsType.PeriodCurrent);

			// Create print data.
			TlvLib.TlvConstructed tlvPrintData = new TlvLib.TlvConstructed((uint)TlvLib.Tag.Group_PrintData);
			tlvPrintData.AddTlvUInt8AsHex((uint)TlvLib.Tag.PrintOrigin, (byte)TlvLib.PrintOrigin.CashRegister);
			requestMessage.Body.AddTlv(tlvPrintData);

			// Send the message.
			try
			{
				mConnectionHandler.SendMessage(requestMessage);
				ConnectionHandler.WriteToFile(requestMessage, "TotalsRequest.msg");
			}
			catch (Exception ex)
			{
				AddMessage(String.Format("Error sending Totals request: {0)", ex.Message), true, Color.White, Color.Red);
			}
		}


		/// <summary>
		/// The "previous period totals" button was clicked.
		/// </summary>
		/// <param name="sender">The sender of the event.</param>
		/// <param name="e">The event arguments.</param>
		private void btnPreviousPeriodTotals_Click(object sender, EventArgs e)
		{
			// Disable the controls.
			EnableControls(false, false);

			// Empty the ticket text boxes.
			ClearTickets();

			lblMerchantMessage.Text = "Previous Period Totals...";
			AddMessage(null);
			AddMessage(lblMerchantMessage.Text, true, Color.OliveDrab);

			// Create request message.
			TlvLib.TlvMessageEcr requestMessage = CreateMessage(TlvLib.MessageType.TotalsRequest);

			requestMessage.Body.AddTlvUInt8AsBcd((uint)TlvLib.Tag.TotalsType, (byte)TlvLib.TotalsType.PeriodPrevious);

			// Create print data.
			TlvLib.TlvConstructed tlvPrintData = new TlvLib.TlvConstructed((uint)TlvLib.Tag.Group_PrintData);
			tlvPrintData.AddTlvUInt8AsHex((uint)TlvLib.Tag.PrintOrigin, (byte)TlvLib.PrintOrigin.CashRegister);
			requestMessage.Body.AddTlv(tlvPrintData);

			// Send the message.
			try
			{
				mConnectionHandler.SendMessage(requestMessage);
				ConnectionHandler.WriteToFile(requestMessage, "TotalsRequest.msg");
			}
			catch (Exception ex)
			{
				AddMessage(String.Format("Error sending Totals request: {0)", ex.Message), true, Color.White, Color.Red);
			}
		}


		/// <summary>
		/// The "Current/previous period totals" button was clicked.
		/// </summary>
		/// <param name="sender">The sender of the event.</param>
		/// <param name="e">The event arguments.</param>
		private void btnCurrentPreviousPeriodTotals_Click(object sender, EventArgs e)
		{
			// Disable the controls.
			EnableControls(false, false);

			// Empty the ticket text boxes.
			ClearTickets();

			lblMerchantMessage.Text = "Previous and Current Period Totals...";
			AddMessage(null);
			AddMessage(lblMerchantMessage.Text, true, Color.OliveDrab);

			// Create request message.
			TlvLib.TlvMessageEcr requestMessage = CreateMessage(TlvLib.MessageType.TotalsRequest);

			requestMessage.Body.AddTlvUInt8AsBcd((uint)TlvLib.Tag.TotalsType, (byte)TlvLib.TotalsType.PeriodBoth);

			// Create print data.
			TlvLib.TlvConstructed tlvPrintData = new TlvLib.TlvConstructed((uint)TlvLib.Tag.Group_PrintData);
			tlvPrintData.AddTlvUInt8AsHex((uint)TlvLib.Tag.PrintOrigin, (byte)TlvLib.PrintOrigin.CashRegister);
			requestMessage.Body.AddTlv(tlvPrintData);

			// Send the message.
			try
			{
				mConnectionHandler.SendMessage(requestMessage);
				ConnectionHandler.WriteToFile(requestMessage, "TotalsRequest.msg");
			}
			catch (Exception ex)
			{
				AddMessage(String.Format("Error sending Totals request: {0)", ex.Message), true, Color.White, Color.Red);
			}
		}


		/// <summary>
		/// The "close period" button was clicked.
		/// </summary>
		/// <param name="sender">The sender of the event.</param>
		/// <param name="e">The event arguments.</param>
		private void btnClosePeriodTotals_Click(object sender, EventArgs e)
		{
			// Disable the controls.
			EnableControls(false, false);

			// Empty the ticket text boxes.
			ClearTickets();

			//try
			//{
			//    mConnectionHandler.SendTotalsRequest(TotalsType.ClosePeriod);
			//}
			//catch (Exception)
			//{
			//    DisplayMessage("Connection broken.");
			//}
		}


		#endregion


		#region Handle the other functionality button clicks.


		/// <summary>
		/// The "TMS session" button was clicked.
		/// </summary>
		/// <param name="sender">The sender of the event.</param>
		/// <param name="e">The event arguments.</param>
		private void btnTmsSession_Click(object sender, EventArgs e)
		{
			// Disable the controls.
			EnableControls(false, false);

			// Empty the ticket text boxes.
			ClearTickets();

			lblMerchantMessage.Text = "Forcing TMS session...";
			AddMessage(null);
			AddMessage(lblMerchantMessage.Text, true, Color.OliveDrab, Color.White);

			// Create request message.
			TlvLib.TlvMessageEcr requestMessage = CreateMessage(TlvLib.MessageType.TmsSessionRequest);

			// Send the message.
			try
			{
				mConnectionHandler.SendMessage(requestMessage);
				ConnectionHandler.WriteToFile(requestMessage, "TmsSessionRequest.msg");
			}
			catch (Exception ex)
			{
				AddMessage(String.Format("Error forcing TMS session: {0)", ex.Message), true, Color.White, Color.Red);
			}
		}


		/// <summary>
		/// The "last transaction status" button was pressed.
		/// </summary>
		/// <param name="sender">The sender of the event.</param>
		/// <param name="e">The event arguments.</param>
		private void btnLastTransactionStatus_Click(object sender, EventArgs e)
		{
			// Disable the controls.
			EnableControls(false, false);

			// Empty the ticket text boxes.
			ClearTickets();

			// Set initial message.
			lblMerchantMessage.Text = "Requesting last transaction information...";
			AddMessage(null);
			AddMessage(lblMerchantMessage.Text, true, Color.OliveDrab);

			// Create request message.
			TlvLib.TlvMessageEcr requestMessage = CreateMessage(TlvLib.MessageType.LastTransactionStatusRequest);

			// Optionally fill in the transaction ID.
//			requestMessage.Body.AddTlvUInt64AsHex((uint)TlvLib.Tag.TransactionId, mTransactionId - 1);

			// Send the message.
			try
			{
				mConnectionHandler.SendMessage(requestMessage);
				ConnectionHandler.WriteToFile(requestMessage, "LastTransactionStatusRequest.msg");
			}
			catch (Exception ex)
			{
				AddMessage(String.Format("Error sending last transaction status request: {0)", ex.Message), true, Color.White, Color.Red);
			}
		}


		/// <summary>
		/// The "last transaction ticket" button was pressed.
		/// </summary>
		/// <param name="sender">The sender of the event.</param>
		/// <param name="e">The event arguments.</param>
		private void btnLastTransactionTicket_Click(object sender, EventArgs e)
		{
			// Disable the controls.
			EnableControls(false, false);

			// Empty the ticket text boxes.
			ClearTickets();

			lblMerchantMessage.Text = "Requesting last ticket...";
			AddMessage(null);
			AddMessage(lblMerchantMessage.Text, true, Color.OliveDrab);

			// Create request message.
			TlvLib.TlvMessageEcr requestMessage = CreateMessage(TlvLib.MessageType.LastTransactionTicketRequest);

			// Create print data.
			TlvLib.TlvConstructed tlvPrintData = new TlvLib.TlvConstructed((uint)TlvLib.Tag.Group_PrintData);
			tlvPrintData.AddTlvUInt8AsHex((uint)TlvLib.Tag.PrintOrigin, (byte)TlvLib.PrintOrigin.CashRegister);
			requestMessage.Body.AddTlv(tlvPrintData);

			// Optionally fill in the transaction ID.
//			requestMessage.Body.AddTlvUInt64AsHex((uint)TlvLib.Tag.TransactionId, mTransactionId - 1);

			// Send the message.
			try
			{
				mConnectionHandler.SendMessage(requestMessage);
				ConnectionHandler.WriteToFile(requestMessage, "LastTransactionTicketRequest.msg");
			}
			catch (Exception ex)
			{
				AddMessage(String.Format("Error sending last transaction ticket request: {0)", ex.Message), true, Color.White, Color.Red);
			}
		}


		/// <summary>
		/// The "clear C-TAP database" button was pressed.
		/// </summary>
		/// <param name="sender">The sender of the event.</param>
		/// <param name="e">The event arguments.</param>
		private void btnClearCtapDatabase_Click(object sender, EventArgs e)
		{
			// Empty the ticket text boxes.
			ClearTickets();

			try
			{
				// Disable the controls.
				EnableControls(false, false);

				// Empty the ticket text boxes.
				ClearTickets();

				lblMerchantMessage.Text = "Clearing CTAP Database...";
				AddMessage(null);
				AddMessage(lblMerchantMessage.Text, true, Color.OliveDrab);

				// TODO: Choose a reboot/clear type.
				TlvLib.RebootAndClearType clearType = TlvLib.RebootAndClearType.FullClear;

				// Create request message.
				TlvLib.TlvMessageEcr requestMessage = CreateMessage(TlvLib.MessageType.RebootAndClearCtapDatabaseRequest);
				requestMessage.Body.AddTlvUInt8AsBcd((uint)TlvLib.Tag.RebootAndClearType, (byte)clearType);

				// Send the message.
				try
				{
					mConnectionHandler.SendMessage(requestMessage);
					ConnectionHandler.WriteToFile(requestMessage, "ClearCtapDatabaseRequest.msg");
				}
				catch (Exception ex)
				{
					AddMessage(String.Format("Error Clearing C-TAP Database: {0)", ex.Message), true, Color.White, Color.Red);
				}
			}

			catch (Exception)
			{
				//DisplayMessage("Connection broken.");
			}
			EnableControls(true, false);
		}


		#endregion


		#region Handle the information button clicks.


		/// <summary>
		/// The "terminal information" button was pressed.
		/// </summary>
		/// <param name="sender">The sender of the event.</param>
		/// <param name="e">The event arguments.</param>
		private void btnTerminalInformation_Click(object sender, EventArgs e)
		{
			SendVersionInformationRequest(TlvLib.ApplicationId.Sdk);
			SendVersionInformationRequest(TlvLib.ApplicationId.Tsc);
			SendVersionInformationRequest(TlvLib.ApplicationId.Rdm);
			SendVersionInformationRequest(TlvLib.ApplicationId.Ctap);
			SendVersionInformationRequest(TlvLib.ApplicationId.Ecr);
			SendVersionInformationRequest(TlvLib.ApplicationId.Mdb);
		}


		/// <summary>
		/// The "card brand information" button was pressed.
		/// </summary>
		/// <param name="sender">The sender of the event.</param>
		/// <param name="e">The event arguments.</param>
		private void btnCardBrandInfo_Click(object sender, EventArgs e)
		{
			// Disable the controls.
			EnableControls(false, false);

			// Empty the ticket text boxes.
			ClearTickets();

			lblMerchantMessage.Text = "Requesting Card Brand Info...";
			AddMessage(null);
			AddMessage(lblMerchantMessage.Text, true, Color.OliveDrab);

			// Create request message.
			TlvLib.TlvMessageEcr requestMessage = CreateMessage(TlvLib.MessageType.PrintInfoRequest);

			requestMessage.Body.AddTlvUInt8AsBcd((uint)TlvLib.Tag.PrintInfoType, (byte)TlvLib.PrintInfoType.CardBrandInfo);

			// Create print data.
			TlvLib.TlvConstructed tlvPrintData = new TlvLib.TlvConstructed((uint)TlvLib.Tag.Group_PrintData);
			tlvPrintData.AddTlvUInt8AsHex((uint)TlvLib.Tag.PrintOrigin, (byte)TlvLib.PrintOrigin.CashRegister);
			requestMessage.Body.AddTlv(tlvPrintData);

			// Send the message.
			try
			{
				mConnectionHandler.SendMessage(requestMessage);
				ConnectionHandler.WriteToFile(requestMessage, "PrintCardBrandInfoRequest.msg");
			}
			catch (Exception ex)
			{
				AddMessage(String.Format("Error sending PrintCardBrandInfo request: {0)", ex.Message), true, Color.White, Color.Red);
			}
		}


		/// <summary>
		/// The "C-TAP information" button was pressed.
		/// </summary>
		/// <param name="sender">The sender of the event.</param>
		/// <param name="e">The event arguments.</param>
		private void btnCtapInfo_Click(object sender, EventArgs e)
		{
			// Disable the controls.
			EnableControls(false, false);

			// Empty the ticket text boxes.
			ClearTickets();

			lblMerchantMessage.Text = "Requesting C-TAP Info...";
			AddMessage(null);
			AddMessage(lblMerchantMessage.Text, true, Color.OliveDrab);

			// Create request message.
			TlvLib.TlvMessageEcr requestMessage = CreateMessage(TlvLib.MessageType.PrintInfoRequest);

			requestMessage.Body.AddTlvUInt8AsBcd((uint)TlvLib.Tag.PrintInfoType, (byte)TlvLib.PrintInfoType.CtapInfo);

			// Create print data.
			TlvLib.TlvConstructed tlvPrintData = new TlvLib.TlvConstructed((uint)TlvLib.Tag.Group_PrintData);
			tlvPrintData.AddTlvUInt8AsHex((uint)TlvLib.Tag.PrintOrigin, (byte)TlvLib.PrintOrigin.CashRegister);
			requestMessage.Body.AddTlv(tlvPrintData);

			// Send the message.
			try
			{
				mConnectionHandler.SendMessage(requestMessage);
				ConnectionHandler.WriteToFile(requestMessage, "PrintCtapInfoRequest.msg");
			}
			catch (Exception ex)
			{
				AddMessage(String.Format("Error sending PrintCtapInfo request: {0)", ex.Message), true, Color.White, Color.Red);
			}
		}


		#endregion


		#region Handle the reconnect/disconnect button clicks.


		/// <summary>
		/// The "reconnect" button was pressed. Send disconnect message to terminal with reconnect argument.
		/// </summary>
		/// <param name="sender">The sender of the event.</param>
		/// <param name="e">The event arguments.</param>
		private void btnReconnect_Click(object sender, EventArgs e)
		{
			// Empty the ticket text boxes.
			ClearTickets();
			SendByeRequest(TlvLib.ByeReason.Reconnect);
			EnableControls(false, false);
		}


		/// <summary>
		/// The "disconnect" button was pressed. Send disconnect message to terminal.
		/// </summary>
		/// <param name="sender">The sender of the event.</param>
		/// <param name="e">The event arguments.</param>
		private void btnDisconnect_Click(object sender, EventArgs e)
		{
			ClearTickets();
			SendByeRequest(TlvLib.ByeReason.Deactivate);
			EnableControls(false, false);
		}


		#endregion


		#region Handle the transparant mode button clicks.

		// Transparent mode.

		/// <summary>
		/// The start/stop transparent mode button was clicked.
		/// </summary>
		/// <param name="sender">The sender of the event.</param>
		/// <param name="e">The event arguments.</param>
		private void buttonTmStartStopTransparentMode_Click(object sender, EventArgs e)
		{
			// Create request message.
			TlvLib.TlvMessageEcr tlvRequestMessage = CreateMessage(TlvLib.MessageType.TmTransparentModeRequest);

			// Fill the transparent mode state.
			if (!mTransparentModeState)
			{
				// Detect custom card and switch to transparent mode.
				mTransparantModeCardUid = null;
				tlvRequestMessage.Body.AddTlvUInt8AsHex((uint)TlvLib.Tag.TmTransparentMode, 1);

				// Create UI control group TLV.
				TlvLib.TlvConstructed tlvUiControl = new TlvLib.TlvConstructed((uint)TlvLib.Tag.Group_TmUiControl);
				tlvUiControl.AddTlvAsString((uint)TlvLib.Tag.TmDisplayText, "PRESENT CARD");
				tlvUiControl.AddTlvUInt8AsHex((uint)TlvLib.Tag.TmBeepType, (byte)TlvLib.TmBeepType.Attention);
				tlvUiControl.AddTlvUInt8AsHex((uint)TlvLib.Tag.TmLedControl, (byte)TlvLib.TmLedControl.Led1);
				tlvRequestMessage.Body.AddTlv(tlvUiControl);

				EnableControls(false, true);
			}
			else
			{
				// Turn off transparent mode.
				tlvRequestMessage.Body.AddTlvUInt8AsHex((uint)TlvLib.Tag.TmTransparentMode, 0);

				// Create UI control group TLV.
				TlvLib.TlvConstructed tlvUiControl = new TlvLib.TlvConstructed((uint)TlvLib.Tag.Group_TmUiControl);
				tlvUiControl.AddTlvAsString((uint)TlvLib.Tag.TmDisplayText, "REMOVE CARD");
				tlvUiControl.AddTlvUInt8AsHex((uint)TlvLib.Tag.TmBeepType, (byte)TlvLib.TmBeepType.Success);
				tlvUiControl.AddTlvUInt8AsHex((uint)TlvLib.Tag.TmLedControl, (byte)TlvLib.TmLedControl.All);
				tlvRequestMessage.Body.AddTlv(tlvUiControl);
			}

			// Fill the card detection time-out.
			tlvRequestMessage.Body.AddTlvUInt16AsHex((uint)TlvLib.Tag.TmCardDetectionTimeout, (ushort)Properties.Settings.Default.TmCardDetectionTimeout);

			// Send the message.
			try
			{
				mConnectionHandler.SendMessage(tlvRequestMessage);
				ConnectionHandler.WriteToFile(tlvRequestMessage, "TmTransparentModeRequest.msg");
			}
			catch (Exception ex)
			{
				AddMessage(String.Format("Error sending transparent mode request: {0)", ex.Message), true, Color.White, Color.Red);
			}

		}


		/// <summary>
		/// The "Authenticate" button was clicked.
		/// </summary>
		/// <param name="sender">The sender of the event.</param>
		/// <param name="e">The event arguments.</param>
		private void buttonTmAuthenticate_Click(object sender, EventArgs e)
		{
			// Check if in transparent mode.
			if (!mTransparentModeState)
			{
				MessageBox.Show("Not in transparent mode", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
				return;
			}

			// Check if card was presented.
			if (mTransparantModeCardUid == null)
			{
				MessageBox.Show("No Card Presented with UID", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
				return;
			}

			// Send the authentication request.
			SendAuthenticationRequest(mTransparantModeCardUid);
		}


		/// <summary>
		/// Send authentication request.
		/// </summary>
		/// <param name="cardUid">The card UID.</param>
		void SendAuthenticationRequest(byte[] cardUid)
		{
			// Create list with key generation data with initial capacity for serial number (8), secret (20), dealer ID (8), card UID (16), keylen (1).
			System.Collections.Generic.List<byte> keyGenData = new System.Collections.Generic.List<byte>(8 + 20 + 8 + 16 + 1);

			// Add terminal serial number to keygen data (8 bytes).
			keyGenData.AddRange(System.Text.Encoding.ASCII.GetBytes(mSerialNumber.Substring(mSerialNumber.Length - 8)));

			// Add secret to keygen data (currently 20 bytes).
			keyGenData.AddRange(Utilities.Conversions.HexStringToByteArray(Properties.Settings.Default.TmKeyGenSecret));

			// Add dealer ID to keygen data (8 bytes).
			string dealerIdString = Properties.Settings.Default.TmDealerId;
			if (dealerIdString.Length > 8)
			{
				// Dealer ID too long, make it smaller (take last part).
				dealerIdString = dealerIdString.Substring(dealerIdString.Length - 8, 8);
			}
			else if (dealerIdString.Length < 8)
			{
				// Dealer ID too small, prepend zeros.
				dealerIdString = new String('0', 8 - dealerIdString.Length) + dealerIdString;
			}
			keyGenData.AddRange(System.Text.Encoding.ASCII.GetBytes(dealerIdString));

			// Add card UID to keygen data (16 bytes), trailing 0xFF.
			keyGenData.AddRange(cardUid);
			int nrTrailingBytes = 16 - cardUid.Length;
			if (nrTrailingBytes > 0)
			{
				for (int i = 0; i != nrTrailingBytes; ++i) keyGenData.Add(0xFF);
			}

			// Add requested key length to keygen data.
			keyGenData.Add(32);

			// Create Sha256 of keygen data.
			System.Security.Cryptography.SHA256 sha256 = new System.Security.Cryptography.SHA256Managed();
			byte[] hash = sha256.ComputeHash(keyGenData.ToArray<byte>());

			// Run dialog asynchronously else keep-alives are not processed.
			DialogResult result = DialogResult.Yes;
			System.Threading.Tasks.Task task = new System.Threading.Tasks.Task
			(
				new Action(() =>
				{
					result = MessageBox.Show("Use correct authorisation key for card?", "Question", MessageBoxButtons.YesNo, MessageBoxIcon.Question);
				}
			));
			task.Start(); task.Wait();

			// Determine the authorisation key.
			byte[] authorisationKey = null;
			if (result == DialogResult.Yes)
			{
				// User wanted correct key, look it up.
				foreach (string entry in Properties.Settings.Default.TmCardKeys)
				{
					// Split the string in card UID and key.
					int index = entry.IndexOf(';');
					if (index > 0)
					{
						byte[] uid = Utilities.Conversions.HexStringToByteArray(entry.Substring(0, index));
						byte[] key = Utilities.Conversions.HexStringToByteArray(entry.Substring(index + 1));

						if (Enumerable.SequenceEqual(cardUid, uid))
						{
							// Card UID found, fill the key.
							authorisationKey = key;
							break;
						}
					}
				}

				// Exit if no key found.
				if (authorisationKey == null)
				{
					// Show dialog in thread else keep-alive will not be processed.
					task = new System.Threading.Tasks.Task
					(
						new Action(() =>
						{
							MessageBox.Show("Unknown card UID", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
						}
					));
					task.Start(); task.Wait();
					return;
				}
			}
			else
			{
				// User wanted wrong authorisation key, just use zero's.
				authorisationKey = new byte[] { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
			}


			// Encrypt authorisation key.
			System.Security.Cryptography.Aes aes = new System.Security.Cryptography.AesManaged();
			aes.Key = hash;
			aes.IV = new byte[]
			{
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
			};
			System.Security.Cryptography.ICryptoTransform encryptor = aes.CreateEncryptor();
			System.IO.MemoryStream msEncrypt = new System.IO.MemoryStream();
			System.Security.Cryptography.CryptoStream csEncrypt = new System.Security.Cryptography.CryptoStream(msEncrypt, encryptor, System.Security.Cryptography.CryptoStreamMode.Write);
			csEncrypt.Write(authorisationKey, 0, authorisationKey.Length);
			byte[] encryptedAuthoristionKey = msEncrypt.ToArray();
			csEncrypt.Close();
			msEncrypt.Close();

			// Create request message.
			TlvLib.TlvMessageEcr tlvRequestMessage = CreateMessage(TlvLib.MessageType.TmAuthenticateRequest);

			// Fill the authorisation key.
			tlvRequestMessage.Body.AddTlv(new TlvLib.Tlv((uint)TlvLib.Tag.TmKey, encryptedAuthoristionKey));

			// Send the message.
			try
			{
				mConnectionHandler.SendMessage(tlvRequestMessage);
				ConnectionHandler.WriteToFile(tlvRequestMessage, "TmAutheticateRequest.msg");
			}
			catch (Exception ex)
			{
				AddMessage(String.Format("Error sending authenticate request: {0)", ex.Message), true, Color.White, Color.Red);
			}

		}


		/// <summary>
		/// The "read card data" button was clicked.
		/// </summary>
		/// <param name="sender">The sender of the event.</param>
		/// <param name="e">The event arguments.</param>
		private void buttonTmReadCardData_Click(object sender, EventArgs e)
		{
			// Check if in transparent mode.
			if (!mTransparentModeState)
			{
				MessageBox.Show("Not in transparent mode", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
				return;
			}

			// Show address input dialog.
			TmAddressInputForm frm = new TmAddressInputForm();
			if (frm.ShowDialog() != DialogResult.OK)
			{
				return;
			}

			// Create request message.
			TlvLib.TlvMessageEcr tlvRequestMessage = CreateMessage(TlvLib.MessageType.TmReadCardDataRequest);

			// Fill memory address and data size.
			tlvRequestMessage.Body.AddTlvUInt16AsHex((uint)TlvLib.Tag.TmAddress, frm.Address);
			tlvRequestMessage.Body.AddTlvUInt16AsHex((uint)TlvLib.Tag.TmDataSize, frm.DataSize);

			// Send the message.
			try
			{
				mConnectionHandler.SendMessage(tlvRequestMessage);
				ConnectionHandler.WriteToFile(tlvRequestMessage, "TmTransparentModeRequest.msg");
			}
			catch (Exception ex)
			{
				AddMessage(String.Format("Error sending read card data request: {0)", ex.Message), true, Color.White, Color.Red);
			}

		}


		/// <summary>
		/// The transparent modeUI control button was clicked.
		/// </summary>
		/// <param name="sender">The sender of the event.</param>
		/// <param name="e">The event arguments.</param>
		private void buttonTmUiControl_Click(object sender, EventArgs e)
		{
			// Check if in transparent mode.
			if (!mTransparentModeState)
			{
				MessageBox.Show("Not in transparent mode", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
				return;
			}

			// Show UI control input dialog.
			TmUiControlForm frm = new TmUiControlForm();
			if (frm.ShowDialog() != DialogResult.OK)
			{
				return;
			}

			// Create request message.
			TlvLib.TlvMessageEcr tlvRequestMessage = CreateMessage(TlvLib.MessageType.TmUiControlRequest);

			// Fill UI control data (display text, beep type, LED control.
			if (frm.DisplayText != null) tlvRequestMessage.Body.AddTlvAsString((uint)TlvLib.Tag.TmDisplayText, frm.DisplayText);
			if (frm.BeepType != null) tlvRequestMessage.Body.AddTlvUInt8AsHex((uint)TlvLib.Tag.TmBeepType, (byte)frm.BeepType);
			if (frm.LedControl != null) tlvRequestMessage.Body.AddTlvUInt8AsHex((uint)TlvLib.Tag.TmLedControl, (byte)frm.LedControl);

			// Send the message.
			try
			{
				mConnectionHandler.SendMessage(tlvRequestMessage);
				ConnectionHandler.WriteToFile(tlvRequestMessage, "TmUiControlRequest.msg");
			}
			catch (Exception ex)
			{
				AddMessage(String.Format("Error sending read card data request: {0)", ex.Message), true, Color.White, Color.Red);
			}

		}


		#endregion


		#region Send message functionality.

		/// <summary>
		/// Create a TLV message and fill the header.
		/// </summary>
		/// <param name="messageType">The type of the message to create.</param>
		/// <returns>The created message.</returns>
		TlvLib.TlvMessageEcr CreateMessage(TlvLib.MessageType messageType)
		{
			// Create and fill header.
			TlvLib.TlvConstructed tlvHeader = new TlvLib.TlvConstructed((uint)TlvLib.Tag.Group_Header);
			tlvHeader.AddTlvUInt32AsBcd((uint)TlvLib.Tag.ProtocolId, 0x0001);
			tlvHeader.AddTlvUInt32AsBcd((uint)TlvLib.Tag.MessageType, (uint)messageType);
			tlvHeader.AddTlvAsString((uint)TlvLib.Tag.TerminalId, mTerminalId);
			tlvHeader.AddTlvAsString((uint)TlvLib.Tag.EcrId, mCashRegisterId);
			tlvHeader.AddTlvUInt16AsHex((uint)TlvLib.Tag.SequenceNumber, ++mSentMessageSequenceNr);

			// Create body and footer. CRC in footer will be set when sending.
			TlvLib.TlvConstructed tlvBody = new TlvLib.TlvConstructed((uint)TlvLib.Tag.Group_Body);
			TlvLib.TlvConstructed tlvFooter = new TlvLib.TlvConstructed((uint)TlvLib.Tag.Group_Footer);

			return new TlvLib.TlvMessageEcr(tlvHeader, tlvBody, tlvFooter);
		}


		/// <summary>
		/// Send an intermediate result response (vending result).
		/// </summary>
		/// <param name="productDelivered">True if the product was delivered and the transaction should be finalised.</param>
		/// <param name="finalTransactionAmount">The final transaction amount (deferred sale).</param>
		private void SendSignalIntermediateResultReply(bool productDelivered, uint finalTransactionAmount)
		{
			// Create response message.
			TlvLib.TlvMessageEcr tlvResponseMessage = CreateMessage(TlvLib.MessageType.IntermediateResultResponse);

			// Fill the product delivery status.
			tlvResponseMessage.Body.AddTlvUInt8AsHex((uint)TlvLib.Tag.TransactionResult, (productDelivered ? (byte)TlvLib.TransactionResult.Approved : (byte)TlvLib.TransactionResult.Error));

			// Fill the final amount.
			tlvResponseMessage.Body.AddTlvUInt32AsBcd((uint)TlvLib.Tag.Amount, finalTransactionAmount);

			// Send the message.
			try
			{
				mConnectionHandler.SendMessage(tlvResponseMessage);
				ConnectionHandler.WriteToFile(tlvResponseMessage, "IntermediateResultResponse.msg");
			}
			catch (Exception ex)
			{
				AddMessage(String.Format("Error sending Intermediate Result response: {0)", ex.Message), true, Color.White, Color.Red);
			}
		}


		/// <summary>
		/// Send a bye request message.
		/// </summary>
		/// <param name="reason">The bye reason to send.</param>
		private void SendByeRequest(TlvLib.ByeReason reason)
		{
			// Create request message.
			TlvLib.TlvMessageEcr requestMessage = CreateMessage(TlvLib.MessageType.ByeRequest);

			// Fill the reason.
			requestMessage.Body.AddTlvUInt8AsHex((uint)TlvLib.Tag.ByeReason, (byte)reason);

			// Send the message.
			try
			{
				mConnectionHandler.SendMessage(requestMessage);
				ConnectionHandler.WriteToFile(requestMessage, "ByeRequest.msg");
			}
			catch (Exception ex)
			{
				AddMessage(String.Format("Error sending bye request: {0)", ex.Message), true, Color.White, Color.Red);
			}
		}


		/// <summary>
		/// Send a version information request message.
		/// </summary>
		/// <param name="reason">The bye reason to send.</param>
		private void SendVersionInformationRequest(TlvLib.ApplicationId applicationId)
		{
			// Create request message.
			TlvLib.TlvMessageEcr requestMessage = CreateMessage(TlvLib.MessageType.VersionInformationRequest);

			// Fill the application ID.
			requestMessage.Body.AddTlvUInt8AsHex((uint)TlvLib.Tag.ApplicationId, (byte)applicationId);

			// Send the message.
			try
			{
				mConnectionHandler.SendMessage(requestMessage);
				ConnectionHandler.WriteToFile(requestMessage, "VersionInformationRequest.msg");
			}
			catch (Exception ex)
			{
				AddMessage(String.Format("Error sending version information request: {0)", ex.Message), true, Color.White, Color.Red);
			}
		}

		#endregion


		#region Implementation of the IMessageHandler interface.


		/// <summary>
		/// Handle an incoming "hello request" message.
		/// </summary>
		/// <param name="tlvRequestMessage">The hello request message.</param>
		/// <return>True if message processing should continue. False if message processing should stop and the connection closed.</return>
		bool IMessageHandler.HandleHelloRequest(TlvLib.TlvMessageEcr tlvRequestMessage)
		{
			EnableControls(true, false);

			// Reset sent sequence numnber and store the terminal ID.
			mSentMessageSequenceNr = 0;
			TlvLib.Tlv tlvTerminalId = tlvRequestMessage.Header.FindTlv((uint)TlvLib.Tag.TerminalId);
			if (tlvTerminalId != null) mTerminalId = tlvTerminalId.GetValueFromString();
			TlvLib.Tlv tlvSerialNumber = tlvRequestMessage.Body.FindTlv((uint)TlvLib.Tag.SerialNumber);
			if (tlvSerialNumber != null) mSerialNumber = tlvSerialNumber.GetValueFromString();
			TlvLib.Tlv tlvLogicalId = tlvRequestMessage.Body.FindTlv((uint)TlvLib.Tag.LogicalId);
			if (tlvLogicalId != null) mLogicalId = tlvLogicalId.GetValueFromString();
			mTransparentModeState = false;

			// Process the connection parameters.
			ushort requestedKeepAliveInterval = 0;
			TlvLib.TlvConstructed tlvConnectionParameters = tlvRequestMessage.Body.FindTlvConstructed((uint)TlvLib.Tag.Group_ConnectionParameters);
			if (tlvConnectionParameters != null)
			{
				TlvLib.Tlv tlvKeepAliveInterval = tlvConnectionParameters.FindTlv((uint)TlvLib.Tag.KeepAliveInterval);
				if (tlvKeepAliveInterval != null) requestedKeepAliveInterval = tlvKeepAliveInterval.GetValueUInt16FromBcd();
			}

			// Determine the keep-alive interval to use.
			if (Properties.Settings.Default.KeepAliveInterval < 0)
			{
				// Terminal determined keep-alive interval.
				mKeepAliveInterval = requestedKeepAliveInterval;
			}
			else if (Properties.Settings.Default.KeepAliveInterval == 0)
			{
				// No keep alive interval.
				mKeepAliveInterval = 0;
			}
			else
			{
				// Cash register determined keep-alive interval.
				mKeepAliveInterval = (ushort)Properties.Settings.Default.KeepAliveInterval;
			}
			SetMerchantMessage("Terminal connected.");
			AddMessage(String.Format("Hello request received from: {0} [{1}], Requested keep-alive interval: {2}, Used keep-alive interval: {3}", mTerminalId, mSerialNumber, requestedKeepAliveInterval, mKeepAliveInterval));

			// Start the keep-alive timer. As long as keep-alive messages arrive, the timer will be reset and will never fire.
			if (mKeepAliveInterval > 0)
			{
				mKeepAliveTimer = new System.Timers.Timer(2 * mKeepAliveInterval * 1000);   // Times 2 for margin.
				mKeepAliveTimer.Elapsed += KeepAliveTime_Elapsed;
				mKeepAliveTimer.AutoReset = false;
				mKeepAliveTimer.Start();
			}

			// Create response message.
			TlvLib.TlvMessageEcr tlvResponseMessage = CreateMessage(TlvLib.MessageType.HelloResponse);

			// Fill the body.

			// Set result code.
			tlvResponseMessage.Body.AddTlvUInt16AsHex((uint)TlvLib.Tag.ResultCode, (ushort)TlvLib.EcrResultCode.ResultOK);

			// Add connection parameters with keep-alive interval.
			{
				TlvLib.TlvConstructed connectionParameters = new TlvLib.TlvConstructed((uint)TlvLib.Tag.Group_ConnectionParameters);
				connectionParameters.AddTlvUInt16AsBcd((uint)TlvLib.Tag.KeepAliveInterval, mKeepAliveInterval);
				tlvResponseMessage.Body.AddTlv(connectionParameters);
			}

			// Send the message.
			try
			{
				mConnectionHandler.SendMessage(tlvResponseMessage);
				ConnectionHandler.WriteToFile(tlvResponseMessage, "HelloResponse.msg");
			}
			catch (Exception ex)
			{
				AddMessage(String.Format("Error sending hello response: {0)", ex.Message), true, Color.White, Color.Red);
			}

			return true;
		}


		/// <summary>
		/// Handle an incoming "keep-alive request" message.
		/// </summary>
		/// <param name="tlvRequestMessage">The keep-alive request body.</param>
		/// <return>True if message processing should continue. False if message processing should stop and the connection closed.</return>
		bool IMessageHandler.HandleKeepAliveRequest(TlvLib.TlvConstructed tlvRequestMessage)
		{
			// Stop the keep-alive timer.
			mKeepAliveTimer.Stop();

			TlvLib.KeepAliveReason keepAliveReason = (TlvLib.KeepAliveReason)tlvRequestMessage.FindTlv((uint)TlvLib.Tag.KeepAliveReason).GetValueUInt8FromHex();
			
			// Create response message.
			TlvLib.TlvMessageEcr tlvResponseMessage = CreateMessage(TlvLib.MessageType.KeepAliveResponse);

			// Fill the body.

			// Set result code and echo reason.
			tlvResponseMessage.Body.AddTlvUInt8AsHex((uint)TlvLib.Tag.KeepAliveReason, (byte)keepAliveReason);
			tlvResponseMessage.Body.AddTlvUInt16AsHex((uint)TlvLib.Tag.ResultCode, (ushort)TlvLib.EcrResultCode.ResultOK);

			// Send the message.
			try
			{
				mConnectionHandler.SendMessage(tlvResponseMessage);
				ConnectionHandler.WriteToFile(tlvResponseMessage, "KeepAliveResponse.msg");
			}
			catch (Exception ex)
			{
				AddMessage(String.Format("Error sending keep-alive response: {0)", ex.Message), true, Color.White, Color.Red);
			}

			// Status update or keep-alive.
			if (keepAliveReason == TlvLib.KeepAliveReason.Status)
			{
				// Process status update, increment update counter.
				++mCounterStatusUpdate;
			}
			else
			{
				// Process keep-alive, incremente kee-alive counter and store the time.
				++mCounterKeepAlive;
				mKeepAliveTimeLast = mKeepAliveTimeCurrent;
				mKeepAliveTimeCurrent = DateTime.Now;
			}

			// Display the keep-alive counter.
			DisplayKeepAlive();

			// Start the keep-alive timer again.
			mKeepAliveTimer.Start();

			return true;
		}


		/// <summary>
		/// Handle an incoming "bye response" message.
		/// </summary>
		/// <param name="tlvResponseMessage">The bye response body.</param>
		/// <return>True if message processing should continue. False if message processing should stop and the connection closed.</return>
		bool IMessageHandler.HandleByeResponse(TlvLib.TlvConstructed tlvResponseMessage)
		{
			TlvLib.EcrResultCode resultCode = (TlvLib.EcrResultCode)tlvResponseMessage.FindTlv((uint)TlvLib.Tag.ResultCode).GetValueUInt16FromHex();
			if (resultCode == TlvLib.EcrResultCode.ResultOK)
			{
				SetMerchantMessage(String.Format("Terminal disconnected. Bye reason: {0}", (TlvLib.ByeReason)tlvResponseMessage.FindTlv((uint)TlvLib.Tag.ByeReason).GetValueUInt8FromHex()));
			}
			else
			{
				SetMerchantMessage(String.Format("Terminal diconnection failed: {0}", resultCode));
			}

			return false;
		}


		/// <summary>
		/// Handle an incoming "transaction response" message.
		/// </summary>
		/// <param name="tlvResponseMessage">The transaction response body.</param>
		/// <return>True if message processing should continue. False if message processing should stop and the connection closed.</return>
		bool IMessageHandler.HandleTransactionResponse(TlvLib.TlvConstructed tlvResponseMessage)
		{
			this.Invoke(new Action(() =>
			{
				string cardholderTicket = "";
				string merchantTicket = "";
				string journalTicket = "";

				// Extract ticket data.
				TlvLib.TlvConstructed tlvTicketData = tlvResponseMessage.FindTlvConstructed((uint)TlvLib.Tag.Group_TicketData);
				foreach (TlvLib.TlvConstructed tlvTicket in tlvTicketData.FindAll((uint)TlvLib.Tag.Group_TableRecord))
				{
					switch ((TlvLib.TicketType)tlvTicket.FindTlv((uint)TlvLib.Tag.TicketType).GetValueUInt8FromHex())
					{
						case TlvLib.TicketType.CardHolder:
							{
								cardholderTicket = tlvTicket.FindTlv((uint)TlvLib.Tag.TicketBody).GetValueFromString();
								break;
							}

						case TlvLib.TicketType.Merchant:
							{
								merchantTicket = tlvTicket.FindTlv((uint)TlvLib.Tag.TicketBody).GetValueFromString();
								break;
							}

						case TlvLib.TicketType.Journal:
							{
								journalTicket = tlvTicket.FindTlv((uint)TlvLib.Tag.TicketBody).GetValueFromString();
								break;
							}
					}
				}

				// Display the tickets.
				DisplayTickets(cardholderTicket, merchantTicket, journalTicket);

				// Display result.
				TlvLib.TransactionResult transactionResult = (TlvLib.TransactionResult)tlvResponseMessage.FindTlv((uint)TlvLib.Tag.TransactionResult).GetValueUInt8FromHex();
				TlvLib.EcrResultCode resultCode = (TlvLib.EcrResultCode)tlvResponseMessage.FindTlv((uint)TlvLib.Tag.ResultCode).GetValueUInt16FromHex();
				SetMerchantMessage(String.Format("Transaction result received: {0} [Result code: {1}]", transactionResult, resultCode));

				if (transactionResult == TlvLib.TransactionResult.TransparentMode)
				{
					mTransparentModeState = true;
					EnableControls(false, false);

					// Retrieve UID.
					TlvLib.TlvConstructed tlvGroupTransparentMode = tlvResponseMessage.FindTlvConstructed((uint)TlvLib.Tag.Group_TmTransparentMode);
					if (tlvGroupTransparentMode != null)
					{
						TlvLib.Tlv tlvUid = tlvGroupTransparentMode.FindTlv((uint)TlvLib.Tag.TmCardUid);
						if (tlvUid != null)
						{
							mTransparantModeCardUid = tlvUid.Value;
							AddMessage(String.Format("Switched to transparent mode. Card UID: {0} [{1}]", BitConverter.ToString(tlvUid.Value), tlvUid.Length));
						}
						else
						{
							AddMessage(String.Format("Switched to transparent mode. No Card UID"));
						}
					}
				}
				else
				{
					// Optionally increment the amount (only when result was not busy).
					if (cbAutoIncrementAmount.Checked && resultCode != TlvLib.EcrResultCode.CtapBusy)
					{
						mAmount += 1;
						FormatAmount();
					}

					// Start a new transaction if requested.
					if (cbAutoRepeatTransaction.Checked)
					{
						mAutoRepeatTimer.Interval = Properties.Settings.Default.AutoRepeatInterval;
						mAutoRepeatTimer.Start();
						AddMessage(String.Format("Auto-starting transaction in {0} seconds", mAutoRepeatTimer.Interval / 1000.0), false, Color.White, Color.DarkGreen);
					}
					else
					{
						// Enable the controls again when no new transaction is done.
						EnableControls(true, false);
					}
				}

			}));

			return true;
		}


		/// <summary>
		/// Handle the "signal intermediate result request" message.
		/// </summary>
		/// <param name="tlvRequestMessage">The intermediate result request body.</param>
		/// <return>True if message processing should continue. False if message processing should stop and the connection closed.</return>
		bool IMessageHandler.HandleSignalIntermediateResultRequest(TlvLib.TlvConstructed tlvRequestMessage)
		{
			// Display result.
			TlvLib.TransactionResult transactionResult = (TlvLib.TransactionResult)tlvRequestMessage.FindTlv((uint)TlvLib.Tag.TransactionResult).GetValueUInt8FromHex();
			uint authorisedAmount = (uint)tlvRequestMessage.FindTlv((uint)TlvLib.Tag.Amount).GetValueUInt32FromBcd();
			TlvLib.Tlv tlvIntermediateResultMode = tlvRequestMessage.FindTlv((uint)TlvLib.Tag.IntermediateResultMode);
			TlvLib.IntermediateResultMode mode = tlvIntermediateResultMode != null ? (TlvLib.IntermediateResultMode)tlvIntermediateResultMode.GetValueUInt8FromHex() : TlvLib.IntermediateResultMode.None;
			DisplayIntermediateResult(transactionResult, authorisedAmount, mode);
			return true;
		}


		/// <summary>
		/// Handle an incoming "cancel response" message.
		/// </summary>
		/// <param name="tlvResponseMessage">The cancel response body.</param>
		/// <return>True if message processing should continue. False if message processing should stop and the connection closed.</return>
		bool IMessageHandler.HandleCancelResponse(TlvLib.TlvConstructed tlvResponseMessage)
		{
			TlvLib.EcrResultCode result = (TlvLib.EcrResultCode)tlvResponseMessage.FindTlv((uint)TlvLib.Tag.ResultCode).GetValueUInt16FromHex();
			switch (result)
			{
				case TlvLib.EcrResultCode.ResultOK:
				{
					AddMessage("Cancellation request acknowledged.");
					break;
				}

				case TlvLib.EcrResultCode.Rejected:
				{
					AddMessage("Cancellation request rejected.", false, Color.Red);
					break;
				}

				case TlvLib.EcrResultCode.CancelFailed:
				{
					AddMessage("Cancellation request rejected.", false, Color.Red);
					break;
				}

				default:
				{
					AddMessage(String.Format("Cancellation request error: {0}" + result));
					break;
				}

			}

			return true;
		}


		/// <summary>
		/// Handle an incoming "information report" message.
		/// </summary>
		/// <param name="tlvReportMessage">The information report body.</param>
		/// <return>True if message processing should continue. False if message processing should stop and the connection closed.</return>
		bool IMessageHandler.HandleInformationReport(TlvLib.TlvConstructed tlvReportMessage)
		{
			// Process the "information report" on the GUI thread (Lamda function).
			// Since a blocking dialog is opened BeginInvoke() is used. Invoke() will block until complete and thus result in keep-alive time-out.
			this.BeginInvoke(new Action(() =>
			{
//				// Process the terminal state.
//				ProcessTerminalState((TerminalState)message.TerminalState);

				// Get the transaction stage.
				TlvLib.TransactionStage transactionStage = (TlvLib.TransactionStage)tlvReportMessage.FindTlv((uint)TlvLib.Tag.TransactionStage).GetValueUInt8FromHex();

				// Print stage message.
				TlvLib.Tlv stageMessage = tlvReportMessage.FindTlv((uint)TlvLib.Tag.StageMessage);
				if (stageMessage != null)
				{
					SetMerchantMessage(String.Format(" [{0}]\n {1}", transactionStage, stageMessage.GetValueFromString()));
				}

				// Display merchant text in dialog.
				TlvLib.Tlv merchantText = tlvReportMessage.FindTlv((uint)TlvLib.Tag.MerchantText);
				if (merchantText != null)
				{
					AddMessage(merchantText.GetValueFromString(), false, Color.Orange);

					// In .NET MessageBox.Show() does not block the GUI thread for Invoke() calls.
					// Therefore we need to sync the auto repeat else a transaction is repeated before the dialog is closed.
//					mMessageBoxOpen = true;
					MessageBox.Show(merchantText.GetValueFromString(), "Merchant text", MessageBoxButtons.OK, MessageBoxIcon.Warning);
//					mMessageBoxOpen = false;
//					if (mProcessInfoMustStartNewTransaction)
//					{
//						mProcessInfoMustStartNewTransaction = false;
//						StartTransaction();
//					}

				}

			}));

			// Continue message processing.
			return true;
		}


		/// <summary>
		/// Handle an incoming "TMS session response" message.
		/// </summary>
		/// <param name="tlvResponseMessage">The "TMS session" response body.</param>
		/// <returns>True if message processing should continue. False if message processing should stop and the connection closed.</returns>
		bool IMessageHandler.HandleTmsSessionResponse(TlvLib.TlvConstructed tlvResponseMessage)
		{
			// Process the "TMS session response" on the GUI thread (Lambda function).
			this.Invoke(new Action(() =>
			{
				SetMerchantMessage("TMS session finished");
			}));

			// Enable the controls again.
			EnableControls(true, false);

			// Continue message processing.
			return true;
		}


		/// <summary>
		/// Handle an incoming "last transaction status response" message.
		/// </summary>
		/// <param name="tlvResponseMessage">The last transaction status response body.</param>
		/// <return>True if message processing should continue. False if message processing should stop and the connection closed.</return>
		bool IMessageHandler.HandleLastTransactionStatusResponse(TlvLib.TlvConstructed tlvResponseMessage)
		{
			// Process the "last transaction response" on the GUI thread (Lambda function).
			// Since a blocking dialog is opened BeginInvoke() is used. Invoke() will block until complete and thus result in keep-alive time-out.
			this.BeginInvoke(new Action(() =>
			{
//				// Process the terminal state.
//				ProcessTerminalState((TerminalState)message.TerminalState);

				// Display result code.
				TlvLib.EcrResultCode resultCode = (TlvLib.EcrResultCode)tlvResponseMessage.FindTlv((uint)TlvLib.Tag.ResultCode).GetValueUInt16FromHex();
				SetMerchantMessage(String.Format("Last transaction status response: {0}", resultCode));

				// Extract transaction info.
				TlvLib.TlvConstructed tlvTransactionInformation = tlvResponseMessage.FindTlvConstructed((uint)TlvLib.Tag.Group_TransactionInformation);

				// Display transaction data.
				if (resultCode == TlvLib.EcrResultCode.ResultOK && tlvTransactionInformation != null)
				{
					// Retrieve amount & currency exponent.
					TlvLib.Tlv tlvAmount = tlvTransactionInformation.FindTlv((uint)TlvLib.Tag.Amount);
					TlvLib.Tlv tlvCurrencyExponent = tlvTransactionInformation.FindTlv((uint)TlvLib.Tag.CurrencyExponent);

					// Calculate the amount.
					double amount = tlvAmount.GetValueUInt32FromBcd() / Math.Pow(10.0, tlvCurrencyExponent.GetValueUInt8FromBcd());

					// Build message.
					string msg = "";

					// Transaction ID.
					TlvLib.Tlv tlvTransactionId = tlvResponseMessage.FindTlv((uint)TlvLib.Tag.TransactionId);
					if (tlvTransactionId != null)
					{
						msg += String.Format("Transaction ID: {0}\n", tlvTransactionId.GetValueUInt64FromHex());
					}
					else
					{
						msg += "Transaction ID: [no ID given]\n";
					}

					// Transaction reference.
					TlvLib.Tlv tlvReference = tlvTransactionInformation.FindTlv((uint)TlvLib.Tag.MerchantTransactionReference);
					if (tlvReference != null)
					{
						msg += String.Format("Reference: {0}\n", tlvReference.GetValueFromString());
					}
					else
					{
						msg += "Reference: [no reference given]\n";
					}

					// Amount.
					TlvLib.Tlv tlvCurrency = tlvTransactionInformation.FindTlv((uint)TlvLib.Tag.CurrencyCode);
					ChessPt.Utilities.CurrencyCode currency = ChessPt.Utilities.CurrencyCodeExtensions.Create(tlvCurrency.GetValueUInt16FromBcd());
					msg += String.Format("Amount: {0} {1}\n", ChessPt.Utilities.CurrencyCodeExtensions.ToCurrencySign(currency), amount);

					// Transaction date/time.
					TlvLib.Tlv tlvTransactionDateTime = tlvTransactionInformation.FindTlv((uint)TlvLib.Tag.TransactionDateTime);
					try
					{
						msg += String.Format("DateTime: {0}\n", tlvTransactionDateTime.GetValueFromDateTime());
					}
					catch (Exception)
					{
						msg += String.Format("DateTime: [no (correct) date/time given]\n");
					}

					// Transaction result.
					TlvLib.TransactionResult transactionResult = (TlvLib.TransactionResult)tlvTransactionInformation.FindTlv((uint)TlvLib.Tag.TransactionResult).GetValueUInt8FromHex();
					msg += String.Format("Transaction result: {0}\n", transactionResult);

					// Show the message.
					MessageBox.Show(msg, "Last Transaction", MessageBoxButtons.OK, MessageBoxIcon.Information);
				}
				else
				{
					// No transaction data.
					AddMessage("No transaction information! (transaction ID not found?)", false, Color.Orange);
				}

				// Enable the controls again.
				EnableControls(true, false);
			}));

			// Continue message processing.
			return true;
		}


		/// <summary>
		/// Handle an incoming "last transaction ticket response" message.
		/// </summary>
		/// <param name="tlvResponseMessage">The last transaction ticket response body.</param>
		/// <return>True if message processing should continue. False if message processing should stop and the connection closed.</return>
		bool IMessageHandler.HandleLastTransactionTicketResponse(TlvLib.TlvConstructed tlvResponseMessage)
		{
			// Process the "last ticket response" on the GUI thread (Lambda function).
			this.Invoke(new Action(() =>
			{
//				// Process the terminal state.
//				ProcessTerminalState((TerminalState)message.TerminalState);

				string cardholderTicket = "";
				string merchantTicket = "";
				string journalTicket = "";

				// Extract ticket data.
				int ticketCount = 0;
				TlvLib.TlvConstructed tlvTicketData = tlvResponseMessage.FindTlvConstructed((uint)TlvLib.Tag.Group_TicketData);
				foreach (TlvLib.TlvConstructed tlvTicket in tlvTicketData.FindAll((uint)TlvLib.Tag.Group_TableRecord))
				{
					++ticketCount;
					switch ((TlvLib.TicketType)tlvTicket.FindTlv((uint)TlvLib.Tag.TicketType).GetValueUInt8FromHex())
					{
						case TlvLib.TicketType.CardHolder:
						{
							cardholderTicket = tlvTicket.FindTlv((uint)TlvLib.Tag.TicketBody).GetValueFromString();
							break;
						}

						case TlvLib.TicketType.Merchant:
						{
							merchantTicket = tlvTicket.FindTlv((uint)TlvLib.Tag.TicketBody).GetValueFromString();
							break;
						}

						case TlvLib.TicketType.Journal:
						{
							journalTicket = tlvTicket.FindTlv((uint)TlvLib.Tag.TicketBody).GetValueFromString();
							break;
						}
					}
				}

				// Display the tickets.
				DisplayTickets(cardholderTicket, merchantTicket, journalTicket);

				// Display result code.
				TlvLib.EcrResultCode resultCode = (TlvLib.EcrResultCode)tlvResponseMessage.FindTlv((uint)TlvLib.Tag.ResultCode).GetValueUInt16FromHex();
				SetMerchantMessage(String.Format("Last ticket response: {0}", resultCode));

				// No ticket?
				if (ticketCount == 0)
				{
					SetMerchantMessage("No ticket information! (transaction ID not found?)");
				}

				// Enable the controls again.
				EnableControls(true, false);
			}));

			// Continue message processing.
			return true;
		}


		/// <summary>
		/// Handle an incoming "totals response" message.
		/// </summary>
		/// <param name="tlvResponseMessage">The transaction response body.</param>
		/// <return>True if message processing should continue. False if message processing should stop and the connection closed.</return>
		bool IMessageHandler.HandleTotalsResponse(TlvLib.TlvConstructed tlvResponseMessage)
		{
			this.Invoke(new Action(() =>
			{
				string cardholderTicket = "";
				string merchantTicket = "";
				string journalTicket = "";

				// Extract ticket data.
				TlvLib.TlvConstructed tlvTicketData = tlvResponseMessage.FindTlvConstructed((uint)TlvLib.Tag.Group_TicketData);
				foreach (TlvLib.TlvConstructed tlvTicket in tlvTicketData.FindAll((uint)TlvLib.Tag.Group_TableRecord))
				{
					switch ((TlvLib.TicketType)tlvTicket.FindTlv((uint)TlvLib.Tag.TicketType).GetValueUInt8FromHex())
					{
						case TlvLib.TicketType.Totals:
						{
							journalTicket = tlvTicket.FindTlv((uint)TlvLib.Tag.TicketBody).GetValueFromString();
							break;
						}
					}
				}

				// Display the tickets.
				DisplayTickets(cardholderTicket, merchantTicket, journalTicket);

				// Display result.
				TlvLib.TransactionResult transactionResult = (TlvLib.TransactionResult)tlvResponseMessage.FindTlv((uint)TlvLib.Tag.ResultCode).GetValueUInt8FromHex();
				SetMerchantMessage(String.Format("Transaction result received: {0}", transactionResult));

				// Enable the controls again when no new transaction is done.
				EnableControls(true, false);
			}));

			// Continue message processing.
			return true;
		}


		#endregion


		#region Implementation of the IMessageHandler interface for security scheme/acquirer download.


		/// <summary>
		/// Handle an incoming "security scheme list response" message.
		/// </summary>
		/// <param name="tlvResponseMessage">The transaction response body.</param>
		/// <return>True if message processing should continue. False if message processing should stop and the connection closed.</return>
		bool IMessageHandler.HandleSecuritySchemeListResponse(TlvLib.TlvConstructed tlvResponseMessage)
		{
			// Extract SecuritySchemeList data.
			TlvLib.TlvConstructed tlvSchemeListData = tlvResponseMessage.FindTlvConstructed((uint)TlvLib.Tag.Group_SecuritySchemeList);
			bool fDo = false;
			if (tlvSchemeListData != null)
			{
				int i = tlvSchemeListData.GetTlvSize();
				if (i > 0)
				{
					fDo = true;
				}
			}
			int numberOfSchemes = 0;
			if (fDo)
			{
				foreach (TlvLib.TlvConstructed tlvScheme in tlvSchemeListData.FindAll((uint)TlvLib.Tag.Group_TableRecord))
				{
					numberOfSchemes++;
				}
			}
			System.Collections.Generic.List<SecurityScheme> securitySchemes = new System.Collections.Generic.List<SecurityScheme>(numberOfSchemes);

			if (fDo)
			{
				foreach (TlvLib.TlvConstructed tlvScheme in tlvSchemeListData.FindAll((uint)TlvLib.Tag.Group_TableRecord))
				{
					uint SecSchemeID = (uint)tlvScheme.FindTlv((uint)TlvLib.Tag.SecuritySchemeIdentifier).GetValueUInt32FromHex();
					SecurityScheme scheme = new SecurityScheme();
					scheme.SecurityId = (int)SecSchemeID;
					scheme.Name = SecSchemeID.ToString("X");  // Gives you hexadecimal
															  //scheme.Name = SecSchemeID.ToString();
					securitySchemes.Add(scheme);
				}
			}

			SetMerchantMessage(String.Format("List with {0} security scheme(s) received.", securitySchemes.Count));

			PerformSecuritySchemeDownload(securitySchemes);

			// Continue message processing.
			return true;
		}


		/// <summary>
		/// Start a security scheme download (key load) using one of the security schemes in the list (can be called from non GUI threads).
		/// </summary>
		/// <param name="securitySchemes">The list of security schemes to choose from.</param>
		private void PerformSecuritySchemeDownload(System.Collections.Generic.List<SecurityScheme> securitySchemes)
		{
			// Check if the current thread is the GUI thread.
			if (this.InvokeRequired)
			{
				// Execute this method on the control's thread
				// Since a blocking dialog is opened BeginInvoke() is used. Invoke() will block until complete and thus result in keep-alive time-out.
				this.BeginInvoke(new Action(() => PerformSecuritySchemeDownload(securitySchemes)));
			}
			else
			{
				try
				{
					// Choose a scheme and start the key load.
					TeliumCashRegister.Forms.SelectFromListForm frm = new TeliumCashRegister.Forms.SelectFromListForm(securitySchemes);
					if (frm.ShowDialog() == DialogResult.OK)
					{
						// Send "perform key load" request message.
						// Create request message.
						TlvLib.TlvMessageEcr requestMessage = CreateMessage(TlvLib.MessageType.SecuritySchemeDownloadRequest);
						requestMessage.Body.AddTlvUInt32AsHex((uint)TlvLib.Tag.SecuritySchemeIdentifier, (uint)frm.SelectedId);
						// Send the message.
						try
						{
							mConnectionHandler.SendMessage(requestMessage);
							ConnectionHandler.WriteToFile(requestMessage, "SecuritySchemeDownloadRequest.msg");
						}
						catch (Exception ex)
						{
							AddMessage(String.Format("Error sending SecuritySchemeDownload request: {0)", ex.Message), true, Color.White, Color.Red);
						}
					}
					EnableControls(true, false);
				}
				catch (Exception)
				{
					AddMessage("Connection broken.", true, Color.White, Color.Red);
				}
			}
		}


		/// <summary>
		/// Handle an incoming "acquirer list response" message.
		/// </summary>
		/// <param name="tlvResponseMessage">The transaction response body.</param>
		/// <return>True if message processing should continue. False if message processing should stop and the connection closed.</return>
		bool IMessageHandler.HandleAcquirerListResponse(TlvLib.TlvConstructed tlvResponseMessage)
		{
			//lblMerchantMessage.Text = "Selecting Security Scheme...";
			//AddMessage(null);
			//AddMessage(lblMerchantMessage.Text, true, Color.OliveDrab);

			// Extract SecuritySchemeList data.
			TlvLib.TlvConstructed tlvAcqListData = tlvResponseMessage.FindTlvConstructed((uint)TlvLib.Tag.Group_AcquirerList);
			bool fDo = false;
			if (tlvAcqListData != null)
			{
				int i = tlvAcqListData.GetTlvSize();
				if (i > 0)
				{
					fDo = true;
				}
			}
			int numberOfAcq = 0;

			if (fDo)
			{
				foreach (TlvLib.TlvConstructed tlvScheme in tlvAcqListData.FindAll((uint)TlvLib.Tag.Group_TableRecord))
				{
					numberOfAcq++;
				}
			}
			System.Collections.Generic.List<Acquirer> Acquirers = new System.Collections.Generic.List<Acquirer>(numberOfAcq);

			if (fDo)
			{
				foreach (TlvLib.TlvConstructed tlvAcq in tlvAcqListData.FindAll((uint)TlvLib.Tag.Group_TableRecord))
				{
					Acquirer ACQ = new Acquirer();
					ACQ.AcquirerId = (int)tlvAcq.FindTlv((uint)TlvLib.Tag.AcquirerIdentifier).GetValueUInt32FromHex();
					ACQ.Name = tlvAcq.FindTlv((uint)TlvLib.Tag.AcquirerLabelName).GetValueFromString();
					Acquirers.Add(ACQ);
				}
			}
			SetMerchantMessage(String.Format("List with {0} acquirer(s) received.", Acquirers.Count));

			PerformAcquirerDownload(Acquirers);

			// Continue message processing.
			return true;
		}


		/// <summary>
		/// Start an acquirer download using one of the acquirers in the list (can be called from non GUI threads).
		/// </summary>
		/// <param name="acquirers">The list of acquirers to choose from.</param>
		private void PerformAcquirerDownload(System.Collections.Generic.List<Acquirer> acquirers)
		{
			// Check if the current thread is the GUI thread.
			if (this.InvokeRequired)
			{
				// Execute this method on the control's thread
				// Since a blocking dialog is opened BeginInvoke() is used. Invoke() will block until complete and thus result in keep-alive time-out.
				this.BeginInvoke(new Action(() => PerformAcquirerDownload(acquirers)));
			}
			else
			{
				try
				{
					// Choose a scheme and start the key load.
					TeliumCashRegister.Forms.SelectFromListForm frm = new TeliumCashRegister.Forms.SelectFromListForm(acquirers);
					if (frm.ShowDialog() == DialogResult.OK)
					{
						// Send "perform key load" request message.
						// Create request message.
						TlvLib.TlvMessageEcr requestMessage = CreateMessage(TlvLib.MessageType.AcquirerDownLoadRequest);
						requestMessage.Body.AddTlvUInt32AsHex((uint)TlvLib.Tag.AcquirerIdentifier, (uint)frm.SelectedId);
						// Send the message.
						try
						{
							mConnectionHandler.SendMessage(requestMessage);
							ConnectionHandler.WriteToFile(requestMessage, "AcquirerDownLoadRequest.msg");
						}
						catch (Exception ex)
						{
							AddMessage(String.Format("Error sending AcquirerDownLoad request: {0)", ex.Message), true, Color.White, Color.Red);
						}
					}
					EnableControls(true, false);
				}
				catch (Exception)
				{
					AddMessage("Connection broken.", true, Color.White, Color.Red);
				}
			}
		}


		/// <summary>
		/// Handle an incoming "acquirer list pending messages response" message.
		/// </summary>
		/// <param name="tlvResponseMessage">The transaction response body.</param>
		/// <return>True if message processing should continue. False if message processing should stop and the connection closed.</return>
		bool IMessageHandler.HandleAcquirerListPendingMessagesResponse(TlvLib.TlvConstructed tlvResponseMessage)
		{
			//lblMerchantMessage.Text = "Selecting Security Scheme...";
			//AddMessage(null);
			//AddMessage(lblMerchantMessage.Text, true, Color.OliveDrab);

			// Extract SecuritySchemeList data.
			TlvLib.TlvConstructed tlvAcqListData = tlvResponseMessage.FindTlvConstructed((uint)TlvLib.Tag.Group_AcquirerList);
			bool fDo = false;
			if (tlvAcqListData != null)
			{
				int i = tlvAcqListData.GetTlvSize();
				if (i > 0)
				{
					fDo = true;
				}
			}
			int numberOfAcq = 0;
			if (fDo)
			{
				foreach (TlvLib.TlvConstructed tlvScheme in tlvAcqListData.FindAll((uint)TlvLib.Tag.Group_TableRecord))
				{
					numberOfAcq++;
				}
			}

			System.Collections.Generic.List<Acquirer> Acquirers = new System.Collections.Generic.List<Acquirer>(numberOfAcq);

			if (fDo)
			{
				foreach (TlvLib.TlvConstructed tlvAcq in tlvAcqListData.FindAll((uint)TlvLib.Tag.Group_TableRecord))
				{
					Acquirer ACQ = new Acquirer();
					ACQ.AcquirerId = (int)tlvAcq.FindTlv((uint)TlvLib.Tag.AcquirerIdentifier).GetValueUInt32FromHex();
					ACQ.Name = tlvAcq.FindTlv((uint)TlvLib.Tag.AcquirerLabelName).GetValueFromString();
					Acquirers.Add(ACQ);
				}
			}
			SetMerchantMessage(String.Format("List with {0} acquirer(s) received.", Acquirers.Count));

			PerformSendOrDeletePendingMessages(Acquirers);

			// Continue message processing.
			return true;
		}


		/// <summary>
		/// Send or delete pending messages for one of the acquirers in the list (can be called from non GUI threads).
		/// </summary>
		/// <param name="acquirers">The list of acquirers to choose from.</param>
		private void PerformSendOrDeletePendingMessages(System.Collections.Generic.List<Acquirer> acquirers)
		{
			// Check if the current thread is the GUI thread.
			if (this.InvokeRequired)
			{
				// Execute this method on the control's thread
				// Since a blocking dialog is opened BeginInvoke() is used. Invoke() will block until complete and thus result in keep-alive time-out.
				this.BeginInvoke(new Action(() => PerformSendOrDeletePendingMessages(acquirers)));
			}
			else
			{
				try
				{
					// Choose a scheme and start the key load.
					TeliumCashRegister.Forms.SelectFromListForm frm = new TeliumCashRegister.Forms.SelectFromListForm(acquirers);
					if (frm.ShowDialog() == DialogResult.OK)
					{
						// Send "perform key load" request message.
						// Create request message.
						TlvLib.TlvMessageEcr requestMessage = CreateMessage(TlvLib.MessageType.SendOrDeletePendingMessagesRequest);
						requestMessage.Body.AddTlvUInt8AsHex((uint)TlvLib.Tag.PendingMessagesOperation, (byte)mPendingMessagesOperation);
						requestMessage.Body.AddTlvUInt32AsHex((uint)TlvLib.Tag.AcquirerIdentifier, (uint)frm.SelectedId);

						// Send the message.
						try
						{
							mConnectionHandler.SendMessage(requestMessage);
							ConnectionHandler.WriteToFile(requestMessage, "SendOrDeletePendingMessagesRequest.msg");
						}
						catch (Exception ex)
						{
							AddMessage(String.Format("Error sending SendOrDeletePendingMessages request: {0)", ex.Message), true, Color.White, Color.Red);
						}
					}
					EnableControls(true, false);
				}
				catch (Exception)
				{
					AddMessage("Connection broken.", true, Color.White, Color.Red);
				}
			}
		}


		#endregion


		#region Implementation of the IMessageHandler interface for version information.


		/// <summary>
		/// Handle an incoming "version information" response message.
		/// </summary>
		/// <param name="tlvResponseMessage">The "version information" response body.</param>
		/// <return>True if message processing should continue. False if message processing should stop and the connection closed.</return>
		bool IMessageHandler.HandleVersionInformationResponse(TlvLib.TlvConstructed tlvResponseMessage)
		{
			// Process the "version information" on the GUI thread (Lambda function).
			this.Invoke(new Action(() =>
			{
				// Extract application ID.
				TlvLib.ApplicationId applicationId = (TlvLib.ApplicationId)tlvResponseMessage.FindTlv((uint)TlvLib.Tag.ApplicationId).GetValueUInt8FromHex();

				// Extract result.
				TlvLib.EcrResultCode resultCode = (TlvLib.EcrResultCode)tlvResponseMessage.FindTlv((uint)TlvLib.Tag.ResultCode).GetValueUInt16FromHex();
				AddMessage(String.Format("Version information response: {0} [{1}]", resultCode, applicationId), true, Color.LightGreen);

				// Extract logical ID and serialnumber.
				string logicalId = tlvResponseMessage.FindTlv((uint)TlvLib.Tag.LogicalId).GetValueFromString();
				string serialNumber = tlvResponseMessage.FindTlv((uint)TlvLib.Tag.SerialNumber).GetValueFromString();
				AddMessage(String.Format("Logical ID: {0}, Serial number: {1}", logicalId, serialNumber));

				// Extract version information.
				string versionString = tlvResponseMessage.FindTlv((uint)TlvLib.Tag.VersionString).GetValueFromString();
				TlvLib.Tlv tlvVersionNumber = tlvResponseMessage.FindTlv((uint)TlvLib.Tag.VersionNumber);
				byte versionMajor = Utilities.Conversions.BcdToUInt8(tlvVersionNumber.Value[0]);
				byte versionMinor = Utilities.Conversions.BcdToUInt8(tlvVersionNumber.Value[1]);
				byte versionBuild = Utilities.Conversions.BcdToUInt8(tlvVersionNumber.Value[2]);
				byte versionRevision = Utilities.Conversions.BcdToUInt8(tlvVersionNumber.Value[3]);
				AddMessage(String.Format("{0} - Version: {1}.{2}.{3}.{4}", applicationId, versionMajor, versionMinor, versionBuild, versionRevision));
				AddMessage(String.Format("Version string: {0}", versionString));

				// Extract extra information.
				TlvLib.TlvConstructed tlvExtraInformation = tlvResponseMessage.FindTlvConstructed((uint)TlvLib.Tag.Group_ExtraInformation);
				if (tlvExtraInformation != null)
				{
					foreach (TlvLib.TlvConstructed tlvInformationData in tlvExtraInformation.FindAll((uint)TlvLib.Tag.Group_TableRecord))
					{
						string name = tlvInformationData.FindTlv((uint)TlvLib.Tag.ExtraInformationName).GetValueFromString();
						string value = tlvInformationData.FindTlv((uint)TlvLib.Tag.ExtraInformationValue).GetValueFromString();
						string unit = FormatUnit(tlvInformationData.FindTlv((uint)TlvLib.Tag.ExtraInformationUnit).Value);
						AddMessage(String.Format("- {0}: {1}{2}", name, value, unit));
					}
				}
			}));

			// Continue message processing.
			return true;
		}


		/// <summary>
		/// Format the units (including first space).
		/// </summary>
		/// <param name="unitBytes">The unit bytes form the TLV.</param>
		/// <returns>The formatted unit string.</returns>
		string FormatUnit(byte[] unitBytes)
		{
			// Split unit in unit and unit prefix.
			TlvLib.UnitPrefix unitPrefix = (TlvLib.UnitPrefix)(sbyte)unitBytes[0];
			TlvLib.Unit unit = (TlvLib.Unit)unitBytes[1];

			// Format unit depending on the unit and unit prefix given.
			if (unit == TlvLib.Unit.None)
			{
				// No unit given, return empty string.
				return "";
			}
			if (unitPrefix != TlvLib.UnitPrefix.None)
			{
				// Prefix given, format unit with prefix.
				return String.Format(" {0}{1}", unitPrefix, unit.ToString().ToLower());
			}
			else
			{
				// No prefix given only unit, just return unit.
				return " " + unit.ToString();
			}
		}


		#endregion


		#region Implementation of the IMessageHandler interface for Transparant Mode.


		/// <summary>
		/// Handle an incoming "transparent mode" response message.
		/// </summary>
		/// <param name="tlvResponseMessage">The "transparent mode" response body.</param>
		/// <return>True if message processing should continue. False if message processing should stop and the connection closed.</return>
		bool IMessageHandler.HandleTmTransparentModeResponse(TlvLib.TlvConstructed tlvResponseMessage)
		{
			// Get the transparent mode state.
			byte transparentModeState = tlvResponseMessage.FindTlv((uint)TlvLib.Tag.TmTransparentMode).GetValueUInt8FromHex();
			mTransparentModeState = transparentModeState == 0 ? false : true;

			// Retrieve result code.
			TlvLib.EcrResultCode resultCode = (TlvLib.EcrResultCode)tlvResponseMessage.FindTlv((uint)TlvLib.Tag.ResultCode).GetValueUInt16FromHex();

			// Retrieve UID.
			TlvLib.Tlv tlvUid = tlvResponseMessage.FindTlv((uint)TlvLib.Tag.TmCardUid);
			if (tlvUid != null)
			{
				mTransparantModeCardUid = tlvUid.Value;
				AddMessage(String.Format("TransparentMode result: {0}, Result code: {1}, UID: {2} [{3}]", mTransparentModeState, resultCode, BitConverter.ToString(tlvUid.Value), tlvUid.Length));
			}
			else
			{
				AddMessage(String.Format("TransparentMode result: {0}, Result code: {1}", mTransparentModeState, resultCode));
			}

			// Update GUI when card detected.
			if (mTransparentModeState)
			{
				// Create request message.
				TlvLib.TlvMessageEcr tlvRequestMessage = CreateMessage(TlvLib.MessageType.TmUiControlRequest);

				// Fill UI control data (display text, beep type, LED control.
				tlvRequestMessage.Body.AddTlvAsString((uint)TlvLib.Tag.TmDisplayText, "Processing\nPlease Wait...");
				tlvRequestMessage.Body.AddTlvUInt8AsHex((uint)TlvLib.Tag.TmBeepType, (byte)TlvLib.TmBeepType.Attention);
				tlvRequestMessage.Body.AddTlvUInt8AsHex((uint)TlvLib.Tag.TmLedControl, (byte)TlvLib.TmLedControl.All);

				// Send the message.
				try
				{
					mConnectionHandler.SendMessage(tlvRequestMessage);
				}
				catch (Exception ex)
				{
					AddMessage(String.Format("Error sending transparent mode request: {0)", ex.Message), true, Color.White, Color.Red);
				}

			}

			// Enable controls again.
			if (mTransparentModeState)	EnableControls(false, false);
			else EnableControls(true, false);

			// Continue processing messages.
			return true;
		}


		/// <summary>
		/// Handle an incoming transparent mode "UI control" response message.
		/// </summary>
		/// <param name="tlvResponseMessage">The transparent mode "UI control" response body.</param>
		/// <return>True if message processing should continue. False if message processing should stop and the connection closed.</return>
		bool IMessageHandler.HandleTmUiControlResponse(TlvLib.TlvConstructed tlvResponseMessage)
		{
			// Retrieve result code.
			TlvLib.EcrResultCode resultCode = (TlvLib.EcrResultCode)tlvResponseMessage.FindTlv((uint)TlvLib.Tag.ResultCode).GetValueUInt16FromHex();

			AddMessage(String.Format("UI Control result code: {0}", resultCode));

			// Continue processing messages.
			return true;
		}


		/// <summary>
		/// Handle an incoming transparent mode "authenticate" response message.
		/// </summary>
		/// <param name="tlvResponseMessage">The transparent mode "authenticate" response body.</param>
		/// <return>True if message processing should continue. False if message processing should stop and the connection closed.</return>
		bool IMessageHandler.HandleTmAuthenticateResponse(TlvLib.TlvConstructed tlvResponseMessage)
		{
			// Retrieve result code.
			TlvLib.EcrResultCode resultCode = (TlvLib.EcrResultCode)tlvResponseMessage.FindTlv((uint)TlvLib.Tag.ResultCode).GetValueUInt16FromHex();

			AddMessage(String.Format("Authenticate result code: {0}", resultCode));

			// Continue processing messages.
			return true;
		}


		/// <summary>
		/// Handle an incoming transparent mode "read card data" response message.
		/// </summary>
		/// <param name="tlvResponseMessage">The transparent mode "read card data" response body.</param>
		/// <return>True if message processing should continue. False if message processing should stop and the connection closed.</return>
		bool IMessageHandler.HandleTmReadCardDataResponse(TlvLib.TlvConstructed tlvResponseMessage)
		{
			// Retrieve result code.
			TlvLib.EcrResultCode resultCode = (TlvLib.EcrResultCode)tlvResponseMessage.FindTlv((uint)TlvLib.Tag.ResultCode).GetValueUInt16FromHex();

			// Read the card data.
			TlvLib.Tlv tlvData = tlvResponseMessage.FindTlv((uint)TlvLib.Tag.TmData);
			if (tlvData != null)
			{
				AddMessage(String.Format("Read card data result code: {0}, data length: {1}, data: {2}", resultCode, tlvData.Length, BitConverter.ToString(tlvData.Value)));
				System.Diagnostics.Debug.WriteLine("Card data: {0}", new object[] { BitConverter.ToString(tlvData.Value) });
			}
			else
			{ 
				AddMessage(String.Format("Read card data result code: {0}", resultCode));
			}

			// Continue processing messages.
			return true;
		}


		#endregion


		#region Generate error functionality.


		enum ErrorType
		{
			InvalidGroup3F00,
			PrimitiveAsGroup1F7F,
			GroupAsPrimitiveA6,
			OptionalTagWrongLength53,
			RequiredTagWrongLength50,
			SkipMandatoryTag50,
		}

		/// <summary>
		/// Start a transaction with an invalid message.
		/// </summary>
		private void StartTransactionWithError(ErrorType errorType)
		{
			// Current thread was the GUI thread.
			mTransparantModeCardUid = null;

			// Disable the controls (till transaction reply).
			EnableControls(false, true);

			// Empty the ticket text boxes.
			ClearTickets();

			// Set initial message.
			lblMerchantMessage.Text = "Transaction started...";
			AddMessage(null);
			AddMessage(lblMerchantMessage.Text, true, Color.OliveDrab, Color.White);

			// Create request message.
			TlvLib.TlvMessageEcr requestMessage = CreateMessage(TlvLib.MessageType.TransactionRequest);

			// TODO: Determine transaction language.

			// Create transaction data.
			TlvLib.TlvConstructed tlvTransactionData = new TlvLib.TlvConstructed((uint)TlvLib.Tag.Group_TransactionData);
			if (errorType != ErrorType.SkipMandatoryTag50)
			{
				if (errorType == ErrorType.RequiredTagWrongLength50)
				{
					// Invalid length.
					tlvTransactionData.AddTlvUInt64AsBcd((uint)TlvLib.Tag.Amount, mAmount);
				}
				else
				{
					// Correct length.
					tlvTransactionData.AddTlvUInt32AsBcd((uint)TlvLib.Tag.Amount, mAmount);
				}
			}
			tlvTransactionData.AddTlvUInt16AsBcd((uint)TlvLib.Tag.CurrencyCode, 978);   // Euro.
			tlvTransactionData.AddTlvUInt8AsBcd((uint)TlvLib.Tag.CurrencyExponent, 2);  // Cents.
			tlvTransactionData.AddTlvAsString((uint)TlvLib.Tag.MerchantTransactionReference, txtReference.Text);
			tlvTransactionData.AddTlvUInt8AsHex((uint)TlvLib.Tag.TransactionType, (byte)TlvLib.TransactionType.Payment);
			tlvTransactionData.AddTlvUInt8AsHex((uint)TlvLib.Tag.IntermediateResultMode, (byte)(TlvLib.IntermediateResultMode)comboboxTransactionMode.SelectedItem);
			requestMessage.Body.AddTlv(tlvTransactionData);

			// Inject error in message.
			switch (errorType)
			{
				// Inject invalid group tag to body.
				case ErrorType.InvalidGroup3F00:
				{
					TlvLib.TlvConstructed tlvGroup = new TlvLib.TlvConstructed(0x3F00);
					tlvGroup.AddTlvAsString((uint)0x1F20, "Test");
					requestMessage.Body.AddTlv(tlvGroup);
					break;
				}
				
				// Inject primitive as group tag to body.
				case ErrorType.PrimitiveAsGroup1F7F:
				{
					TlvLib.TlvConstructed tlvGroup = new TlvLib.TlvConstructed(0x1F7F);
					tlvGroup.AddTlvAsString((uint)0x1F7F, "Test");
					requestMessage.Body.AddTlv(tlvGroup);
					break;
				}

				// Inject group as primitive tag to body.
				case ErrorType.GroupAsPrimitiveA6:
				{
					requestMessage.Body.AddTlvAsString((uint)0xA6, "Test");
					break;
				}

				// Inject optional tag with wrong length to transaction data.
				case ErrorType.OptionalTagWrongLength53:
				{
					tlvTransactionData.AddTlvAsString((uint)0x53, "1234");
					break;
				}
			}


			// Create print data.
			TlvLib.TlvConstructed tlvPrintData = new TlvLib.TlvConstructed((uint)TlvLib.Tag.Group_PrintData);
			tlvPrintData.AddTlvUInt8AsHex((uint)TlvLib.Tag.PrintOrigin, (byte)TlvLib.PrintOrigin.CashRegister);
			requestMessage.Body.AddTlv(tlvPrintData);

			// Set transaction ID.
			requestMessage.Body.AddTlvUInt64AsHex((uint)TlvLib.Tag.TransactionId, mTransactionId++);


			// Send the message.
			try
			{
				mConnectionHandler.SendMessage(requestMessage);
				ConnectionHandler.WriteToFile(requestMessage, "TransactionRequestError.msg");
			}
			catch (Exception ex)
			{
				AddMessage(String.Format("Error sending transaction request: {0}", ex.Message), true, Color.White, Color.Red);
			}
		}


		private void menuProduceErrors_SendInvalid3F00_Click(object sender, EventArgs e)
		{
			StartTransactionWithError(ErrorType.InvalidGroup3F00);
		}

		private void menuProduceErrors_SendPrimitiveAsGroup1F7F_Click(object sender, EventArgs e)
		{
			StartTransactionWithError(ErrorType.PrimitiveAsGroup1F7F);
		}

		private void menuProduceErrors_SendGroupAsPrimitiveA6_Click(object sender, EventArgs e)
		{
			StartTransactionWithError(ErrorType.GroupAsPrimitiveA6);
		}

		private void menuProduceErrors_SendOptionalTagWithWrongLength1F70_Click(object sender, EventArgs e)
		{
			StartTransactionWithError(ErrorType.OptionalTagWrongLength53);
		}


		private void menuProduceErrors_SendRequiredTagWithWorngLength50_Click(object sender, EventArgs e)
		{
			StartTransactionWithError(ErrorType.RequiredTagWrongLength50);
		}

		private void menuProduceErrors_SkipMandatoryTag53_Click(object sender, EventArgs e)
		{
			StartTransactionWithError(ErrorType.SkipMandatoryTag50);
		}


		#endregion


	}
}
