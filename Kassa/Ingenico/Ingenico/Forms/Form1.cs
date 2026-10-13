using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.IO;
using System.IO.Ports;
using System.Linq;
using System.Net.Sockets;
using System.Text.RegularExpressions;
using System.Threading;
using System.Windows.Forms;
using ingenico.ConnectionHandler;
using TlvLib;
using Utilities;
using ApplicationId = TlvLib.ApplicationId;

namespace ingenico.Forms
{
    public partial class Form1 : Form, IMessageHandler
    {
        #region Variables

        //protected uint mAmount = 0;											// The entered amount (in cents).
        protected ulong mTransactionId = 0;									// The transaction ID send to the terminal. Incremented after each transaction.

        protected volatile Thread mThread = null;								// The thread runing the connection handler.
        protected volatile ConnectionHandler.ConnectionHandler mConnectionHandler = null;		// The connection handler that processes the messages to/from the terminal.

        // Connection data.
        protected string mTerminalId;											// The terminal ID is stored here in the hello request.
        protected string mLogicalId;											// The terminal logical ID is stored here in the hello request(same as terminal ID).
        protected string mSerialNumber;										// The terminal serial number is stored here in the hello request.
        protected string mCashRegisterId = "TestECR";							// The ECR ID sent to the terminal.
        protected ushort mSentMessageSequenceNr = 0;							// The sequence number for sending messages.

        // The keep-alive timer and related variables.
        protected System.Timers.Timer mKeepAliveTimer = null;
        protected ushort mKeepAliveInterval = 0;								// The keep-alive interval the terminal uses.
        protected ulong mCounterKeepAlive = 0;								// The number of keep-alives received.
        protected ulong mCounterStatusUpdate = 0;								// The number of status updates received.
        protected DateTime mKeepAliveTimeLast;								// The last keep-alive time.
        protected DateTime mKeepAliveTimeCurrent;								// The current keep-alive time.

        protected System.Windows.Forms.Timer mAutoRepeatTimer = new System.Windows.Forms.Timer();

        // Transparent mode variables.
        protected bool mTransparentModeState = false;							// True when in transparent mode.
        protected byte[] mTransparantModeCardUid;								// The UID of the last read card. Needed to calculate key.

        protected PendingMessagesOperation mPendingMessagesOperation;	// Used to determine if open messages should be sent or delete after the list op acquires is retrieved.

        private bool mEnabledSettings = true; //reversed because the first thing we do is reverse this

        #endregion

        #region Form

        public Form1()
        {
            InitializeComponent();
            InitializeComponentExtra();
            OpenSocket("127.0.0.1", 4999);
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            toggleLoggingView(false);

            if (Settings.Default.ManagerPassword == "0000")
            {
                btnRestart.Text = @"Start";
            }
            else
            {
                ToggleEnableSettings(); //disables settings
                restartThread(true); // start connecting automatically
            }
        }

        /// <summary>
        /// The form is closing. Send disconnect message to terminal.
        /// </summary>
        /// <param name="sender">The sender of the event.</param>
        /// <param name="e">The event arguments.</param>
        private void MainForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            // Send disconnect message only if there is an connection.
            if (mConnectionHandler != null)
            {
                // Send disconnect message to terminal.
                //				mConnectionHandler.SendDisconnect(true);

                mConnectionHandler.Close();
            }

            restartThread(false); //closes the keepalive thread

        }

        private void restartThread(bool restart)
        {
            if (mThread != null)
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
                int tries = 1;
                while (thread.ThreadState != ThreadState.Aborted)
                {
                    if (restart)
                    {
                        AddMessage("Aborting thread ... " + tries + " attempts ... " + thread.ThreadState.ToString(), false, Color.Yellow);
                        DisplayConnectionIndicator(Color.Yellow, "Reconnecting");
                    }
                    else
                    {
                        AddMessage("Closing application ... " + tries + " attempts ... " + thread.ThreadState.ToString(), false, Color.Yellow);
                        DisplayConnectionIndicator(Color.Yellow, "Closing");
                    }
                    thread.Interrupt();

                    if (tries < 5)
                    {
                        thread.Join(5 * 1000); // X seconds
                    }
                    else if (tries > 5 || thread.ThreadState == ThreadState.Stopped)
                    {
                        try
                        {
                            thread.Abort();

                            if (tries > 10)
                            {
                                break;
                            }
                        }
                        catch (Exception ex)
                        {
                            AddMessage("Error: " + ex.Message, true, Color.Red);
                            // I had to
                        }
                    }
                    tries++;
                }
                thread = null;
            }

            if (restart)
            {
                AddMessage("Restarting connection thread ...", false, Color.Yellow);
                btnRestart.Text = @"Restart";

                mThread = new Thread(ThreadFunction);
                mThread.IsBackground = false;
                mThread.Start();
            }
        }

        private void InitializeComponentExtra()
        {
            // Get the current TCP/IP listen port.
            textboxListenPort.ValidatingType = typeof(UInt16);
            textboxListenPort.Text = Settings.Default.TcpPort.ToString();

            // Get the keep-alive interval.
            int keepAliveInterval = Settings.Default.KeepAliveInterval;
            if (keepAliveInterval < 0)
            {
                // Terminal defined.
                radioButtonKeepAliveIntervalTerminal.Checked = true;
                numericUpDownKeepAliveInterval.Value = 5;
            }
            else if (keepAliveInterval == 0)
            {
                // No keep-alive.
                radioButtonKeepAliveIntervalNone.Checked = true;
                numericUpDownKeepAliveInterval.Value = 5;
            }
            else
            {
                // Cash register determined.
                radioButtonKeepAliveIntervalCashregister.Checked = true;
                numericUpDownKeepAliveInterval.Value = keepAliveInterval;
            }
            KeepAliveMethodChanged();

            // Get the list of connection types and set the selected one.
            comboBoxConnectionType.Items.Clear();
            comboBoxConnectionType.Items.Add(ConnectionType.Tcp);
            comboBoxConnectionType.Items.Add(ConnectionType.Serial);
            comboBoxConnectionType.SelectedItem = (ConnectionType)Settings.Default.ConnectionType;

            // Get a list of available COM ports and select the current one.
            comboBoxComPort.Items.Clear();
            comboBoxComPort.Items.AddRange(SerialPort.GetPortNames());
            comboBoxComPort.SelectedItem = Settings.Default.ComPort;

            // Fill the baud rate options and set the selected one.
            comboBoxBaudrate.Items.Clear();
            comboBoxBaudrate.Items.Add(300);
            comboBoxBaudrate.Items.Add(1200);
            comboBoxBaudrate.Items.Add(2400);
            comboBoxBaudrate.Items.Add(4800);
            comboBoxBaudrate.Items.Add(9600);
            comboBoxBaudrate.Items.Add(19200);
            comboBoxBaudrate.Items.Add(38400);
            comboBoxBaudrate.Items.Add(57600);
            comboBoxBaudrate.Items.Add(115200);
            comboBoxBaudrate.SelectedItem = Settings.Default.BaudRate;

            // Fill the data bits options and set the selected one.
            comboBoxDataBits.Items.Clear();
            comboBoxDataBits.Items.Add(7);
            comboBoxDataBits.Items.Add(8);
            comboBoxDataBits.SelectedItem = Settings.Default.DataBits;

            // Fill the parity options and set the selected one.
            comboBoxParity.Items.Clear();
            comboBoxParity.Items.Add(Parity.None);
            comboBoxParity.Items.Add(Parity.Odd);
            comboBoxParity.Items.Add(Parity.Even);
            comboBoxParity.SelectedItem = Settings.Default.Parity;

            // Fill the stop bits options and set the selected one.
            comboBoxStopBits.Items.Clear();
            comboBoxStopBits.Items.Add(StopBits.One);
            comboBoxStopBits.Items.Add(StopBits.Two);
            comboBoxStopBits.SelectedItem = Settings.Default.StopBits;

            // Fill the hand shake options and set the selected one.
            comboBoxFlowControl.Items.Clear();
            comboBoxFlowControl.Items.Add(Handshake.None);
            comboBoxFlowControl.Items.Add(Handshake.RequestToSend);
            comboBoxFlowControl.SelectedItem = Settings.Default.FlowControl;

            // Fill auto-repeat interval.
            numericUpDownAutoRepeatInterval.Value = Settings.Default.AutoRepeatInterval;

            // Fill the transaction modes.
            comboBoxTransactionMode.Items.Clear();
            comboBoxTransactionMode.Items.Add("Determined by terminal");
            comboBoxTransactionMode.Items.Add(TransactionMode.Explicit);
            comboBoxTransactionMode.Items.Add(TransactionMode.Implicit);
            comboBoxTransactionMode.SelectedIndex = Settings.Default.TransactionMode + 1;

            // Fill the manager code.
            textBoxmanagerPassword.Text = Settings.Default.ManagerPassword;

            if (Settings.Default.ManagerPassword != "0000")
            {
                //Minimize to task bar
                this.WindowState = FormWindowState.Minimized;
            }
        }

        private void KeepAliveMethodChanged()
        {
            if (radioButtonKeepAliveIntervalCashregister.Checked)
            {
                numericUpDownKeepAliveInterval.Enabled = true;
            }
            else
            {
                numericUpDownKeepAliveInterval.Enabled = false;
            }
        }

        public void AddMessage(string msg, bool bold = false, Color backgroundColor = new Color(), Color textColor = new Color())
        {
            // Check if the current thread is the GUI thread.
            if (this.InvokeRequired)
            {
                try
                {
                    // Execute this method on the control's thread
                    this.Invoke(new Action(() => AddMessage(msg, bold, backgroundColor, textColor)));
                }
                catch (ObjectDisposedException ex)
                {
                    AddMessage("Error: " + ex.Message, true, Color.Red);
                    // zucht
                }
                catch (Exception ex)
                {
                    AddMessage("Error: " + ex.Message, true, Color.Red);
                    //tfuck?
                }
            }
            else
            {
                if (!string.IsNullOrWhiteSpace(msg))
                {
                    // Current thread was the GUI thread, add the text. 
                    ListViewItem item = listViewMessages.Items.Add(String.Format("{0: HH:mm:ss}", DateTime.Now));
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

#if !DEBUG
                    if (listViewMessages.Items.Count > 50)
                    {
                        listViewMessages.Items[0].Remove();
                    }
#endif

                }
            }
        }

        private void SetMerchantMessage(string msg)
        {
            AddMessage(msg, false, Color.White, Color.DarkGreen);
        }

        private void EnableControls(bool enable, bool enableCancel)
        {
            //btnOK.Enabled = enable;
            //btnCancel.Enabled = enableCancel;

            //gbAcquirerMessages.Enabled = enable;
            //gbTotals.Enabled = enable;
            //gbOther.Enabled = enable;
            //gbTransparentMode.Enabled = enable || mTransparentModeState;

            //buttonTmAuthenticate.Enabled = mTransparentModeState;
            //buttonTmReadCardData.Enabled = mTransparentModeState;
            //buttonTmUiControl.Enabled = mTransparentModeState;
        }

        TlvMessageEcr CreateMessage(MessageType messageType)
        {
            // Create and fill header.
            TlvConstructed tlvHeader = new TlvConstructed((uint)TlvLib.Tag.Group_Header);
            tlvHeader.AddTlvUInt32AsBcd((uint)TlvLib.Tag.ProtocolId, 0x0001);
            tlvHeader.AddTlvUInt32AsBcd((uint)TlvLib.Tag.MessageType, (uint)messageType);
            tlvHeader.AddTlvAsString((uint)TlvLib.Tag.TerminalId, mTerminalId);
            tlvHeader.AddTlvAsString((uint)TlvLib.Tag.EcrId, mCashRegisterId);
            tlvHeader.AddTlvUInt16AsHex((uint)TlvLib.Tag.SequenceNumber, ++mSentMessageSequenceNr);

            // Create body and footer. CRC in footer will be set when sending.
            TlvConstructed tlvBody = new TlvConstructed((uint)TlvLib.Tag.Group_Body);
            TlvConstructed tlvFooter = new TlvConstructed((uint)TlvLib.Tag.Group_Footer);

            return new TlvMessageEcr(tlvHeader, tlvBody, tlvFooter);
        }

        private void KeepAliveTime_Elapsed(object sender, EventArgs e)
        {
            // Stop the timer.
            if (mKeepAliveTimer != null) mKeepAliveTimer.Stop();
            mKeepAliveTimer = null;

            // Display connection lost message.
            AddMessage("Terminal offline. Connection was lost (keep-alive time-out)", true, Color.Red);
            DisplayConnectionIndicator(Color.OrangeRed, "0");

            ////// Stop the communication.
            ////if (mConnectionHandler != null)
            ////{
            ////    mConnectionHandler.Close();
            ////    mConnectionHandler.Connect();
            ////}
        }

        public void DisplayKeepAlive()
        {
            // Check if the current thread is the GUI thread.
            if (this.InvokeRequired)
            {
                try
                {
                    // Execute this method on the control's thread
                    this.Invoke(new Action(() => DisplayKeepAlive()));
                }
                catch (ObjectDisposedException ex)
                {
                    AddMessage("Error: " + ex.Message, true, Color.Red);
                    // zucht
                }
                catch (Exception ex)
                {
                    AddMessage("Error: " + ex.Message, true, Color.Red);
                    //tfuck?
                }
            }
            else
            {
                // Display status update counter.
                if (mCounterStatusUpdate != 0)
                {
                    AddMessage(String.Format("Received status updates: {0}", mCounterStatusUpdate));
                }
                else
                {
                    AddMessage("Waiting for status updates...");
                }

                // Display keep-alive counter.
                if (mCounterKeepAlive == 0)
                {
                    AddMessage("Waiting for keep-alive...");
                }
                else if (mKeepAliveTimeLast == DateTime.MinValue)
                {
                    AddMessage(String.Format("Received keep-alives: {0}", mCounterKeepAlive));
                    DisplayConnectionIndicator(Color.Yellow, mCounterKeepAlive.ToString() + "/3");
                }
                else
                {
                    AddMessage(String.Format("Received keep-alives: {0} [Interval: {1:f2} s.]", mCounterKeepAlive, (mKeepAliveTimeCurrent - mKeepAliveTimeLast).TotalSeconds));
                    if (mCounterKeepAlive == 3)
                    {
                        DisplayConnectionIndicator(Color.LightGreen, mCounterKeepAlive.ToString() + "/3");

#if !DEBUG
                        //makes the terminal beep to signal ok
                        StartTransaction(TransactionType.Payment, "", IntermediateResultMode.None, false, "0"); // in eurocent
                        Thread.Sleep(1000);
                        CancelTransaction();
#endif
                    }
                    else if (mCounterKeepAlive > 3)
                    {
                        DisplayConnectionIndicator(Color.LightGreen, "Connected!");
                    }
                    else
                    {
                        DisplayConnectionIndicator(Color.Yellow, mCounterKeepAlive.ToString() + "/3");
                    }
                }
            }
        }

        public void ToggleEnableSettings()
        {
            mEnabledSettings = !mEnabledSettings; // toggle the value

            comboBoxConnectionType.Enabled = mEnabledSettings;

            textboxListenPort.Enabled = mEnabledSettings;

            comboBoxComPort.Enabled = mEnabledSettings;
            comboBoxBaudrate.Enabled = mEnabledSettings;
            comboBoxDataBits.Enabled = mEnabledSettings;
            comboBoxParity.Enabled = mEnabledSettings;
            comboBoxStopBits.Enabled = mEnabledSettings;
            comboBoxFlowControl.Enabled = mEnabledSettings;

            radioButtonKeepAliveIntervalTerminal.Enabled = mEnabledSettings;
            radioButtonKeepAliveIntervalNone.Enabled = mEnabledSettings;
            radioButtonKeepAliveIntervalCashregister.Enabled = mEnabledSettings;
            numericUpDownKeepAliveInterval.Enabled = mEnabledSettings;

            numericUpDownAutoRepeatInterval.Enabled = mEnabledSettings;
            comboBoxTransactionMode.Enabled = mEnabledSettings;
            textBoxmanagerPassword.Enabled = mEnabledSettings;

            groupBox1.Visible = mEnabledSettings;
            btnOK.Visible = mEnabledSettings;
            btnCancel.Visible = mEnabledSettings;
        }

        #endregion

        #region Button clicks

        private void btnOK_Click(object sender, EventArgs e)
        {
            // Check the data.
            ushort listenPort;
            if (!UInt16.TryParse(textboxListenPort.Text, out listenPort))
            {
                AddMessage("port error");
                return;
            }


            // Store the selected connection type.
            if (comboBoxConnectionType.SelectedItem != null)
            {
                Settings.Default.ConnectionType = (int)comboBoxConnectionType.SelectedItem;
            }

            // Store the TCP/IP listen port in the settings object.
            Settings.Default.TcpPort = listenPort;

            // Store the com port in the settings object.
            if (comboBoxComPort.SelectedItem != null)
            {
                Settings.Default.ComPort = comboBoxComPort.SelectedItem as string;
            }
            else
            {
                Settings.Default.ComPort = "";
            }


            // Store the baud rate.
            if (comboBoxBaudrate.SelectedItem != null)
            {
                Settings.Default.BaudRate = (int)comboBoxBaudrate.SelectedItem;
            }

            // Store the data bits.
            if (comboBoxDataBits.SelectedItem != null)
            {
                Settings.Default.DataBits = (int)comboBoxDataBits.SelectedItem;
            }

            // Store the parity.
            if (comboBoxParity.SelectedItem != null)
            {
                Settings.Default.Parity = (Parity)comboBoxParity.SelectedItem;
            }

            // Store the stop bits.
            if (comboBoxStopBits.SelectedItem != null)
            {
                Settings.Default.StopBits = (StopBits)comboBoxStopBits.SelectedItem;
            }

            // Store the flow control.
            if (comboBoxFlowControl.SelectedItem != null)
            {
                Settings.Default.FlowControl = (Handshake)comboBoxFlowControl.SelectedItem;
            }


            // Store the keep-alive interval.
            if (radioButtonKeepAliveIntervalTerminal.Checked)
            {
                // Terminal determined keep-alive interval stored as negative value.
                Settings.Default.KeepAliveInterval = -1;
            }
            else if (radioButtonKeepAliveIntervalNone.Checked)
            {
                // No keep-alive interval stored as zero.
                Settings.Default.KeepAliveInterval = 0;
            }
            else
            {
                // Cash register determined keep-alive interval.
                Settings.Default.KeepAliveInterval = (short)numericUpDownKeepAliveInterval.Value;
            }


            // Store auto-repeat interval.
            Settings.Default.AutoRepeatInterval = (int)numericUpDownAutoRepeatInterval.Value;


            // Store the transaction mode.
            Settings.Default.TransactionMode = comboBoxTransactionMode.SelectedIndex - 1;


            // Store manager password.
            Settings.Default.ManagerPassword = textBoxmanagerPassword.Text;

            // Save the settings and close the form.
            Settings.Default.Save();
            ////Close();

            AddMessage("Saved", false, Color.LightGreen);

            if (mEnabledSettings)
            {
                //disable the settings again
                ToggleEnableSettings();
            }

            restartThread(true); // start connecting automatically
        }

        private void btnCancel_Click(object sender, EventArgs e)
        {
            InitializeComponentExtra();
            AddMessage("Reset the input fields to last save");
        }

        private void btnReconnect_Click(object sender, EventArgs e)
        {
            SendByeRequest(ByeReason.Reconnect);
        }

        private void btnDisconnect_Click(object sender, EventArgs e)
        {
            SendByeRequest(ByeReason.Deactivate);
        }

        private void btnTerminalInfo_Click(object sender, EventArgs e)
        {
            SendVersionInformationRequest(ApplicationId.Sdk);
            SendVersionInformationRequest(ApplicationId.Tsc);
            SendVersionInformationRequest(ApplicationId.Rdm);
            SendVersionInformationRequest(ApplicationId.Ctap);
            SendVersionInformationRequest(ApplicationId.Ecr);
            SendVersionInformationRequest(ApplicationId.Mdb);
            AddMessage("--- end ---", true);
        }

        private void btnSendPayment_Click(object sender, EventArgs e)
        {
            StartTransaction(TransactionType.Payment, "", IntermediateResultMode.None, false, "1"); // in eurocent
        }

        private void btnRefund_Click(object sender, EventArgs e)
        {
            StartTransaction(TransactionType.Refund, "", IntermediateResultMode.None, false, "1"); // in eurocent
        }

        private void btnCancelTransaction_Click(object sender, EventArgs e)
        {
            CancelTransaction();
        }

        private void btnTransparentModeStartStop_Click(object sender, EventArgs e)
        {
            StartStopTransparentMode();
        }

        private void btnTransparentModeAuthenticate_Click(object sender, EventArgs e)
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

        private void btnTransparentModeReadCard_Click(object sender, EventArgs e)
        {

        }

        private void btnTransparentModeUIControl_Click(object sender, EventArgs e)
        {

        }

        private void btnRestart_Click(object sender, EventArgs e)
        {
            try
            {
                restartThread(true);
                //restartApp();
            }
            catch (Exception ex)
            {
                AddMessage("restart failed: " + ex.Message, false, Color.Red);
            }
        }

        private void btnToggleLoggingHide_Click(object sender, EventArgs e)
        {
            toggleLoggingView(false);
        }

        private void btnToggleLoggingView_Click(object sender, EventArgs e)
        {
            toggleLoggingView(true);
        }

        #endregion

        #region requests

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
                            AddMessage("Terminal disconnected unexpected.", true);
                            DisplayConnectionIndicator(Color.OrangeRed, "0");
                            Thread.Sleep(500);
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
            catch (Exception ex)
            {
                AddMessage("Exception in connection handler thread, connection lost.", true, Color.Red);
                AddMessage(ex.Message, true, Color.Red);
                DisplayConnectionIndicator(Color.OrangeRed, "0");
            }
        }

        private bool WaitForClient()
        {
            DisplayKeepAlive();

            // Wait for client connection.
            try
            {
                ConnectionType oType = (ConnectionType)Settings.Default.ConnectionType;
                // Determine the connection type and create it.
                switch (oType)
                {
                    case ConnectionType.Tcp:
                        {
                            // Retrieve the port to use from the settings.
                            int port = Settings.Default.TcpPort;
                            AddMessage(String.Format("Waiting for terminal on TCP port {0}", port));
                            mConnectionHandler = new TcpConnectionHandler(port, this);
                            break;
                        }

                    case ConnectionType.Serial:
                        {
                            // Retrieve the connection parameters from the settings.
                            string comPort = Settings.Default.ComPort;
                            int baudRate = Settings.Default.BaudRate;
                            int dataBits = Settings.Default.DataBits;
                            System.IO.Ports.Parity parity = Settings.Default.Parity;
                            System.IO.Ports.StopBits stopBits = Settings.Default.StopBits;
                            System.IO.Ports.Handshake flowControl = Settings.Default.FlowControl;

                            // Open a connection
                            AddMessage(String.Format("Waiting for terminal on serial port {0}. Connection settings: [baud rate: {1}, data bits: {2}, parity: {3}, stop bits: {4}, flow control: {5}]", comPort, baudRate, dataBits, parity, stopBits, flowControl));
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
                AddMessage(String.Format("Exception: " + ex.Message));
                DisplayConnectionIndicator(Color.Red, "ERROR! see logging");
                mConnectionHandler = null;
                return false;
            }

            // All OK.
            return true;
        }

        private void ClientConnected()
        {
            // Check if the current thread is the GUI thread.
            if (this.InvokeRequired)
            {
                try
                {
                    // Execute this method on the control's thread
                    this.Invoke(new Action(() => ClientConnected()));
                }
                catch (ObjectDisposedException ex)
                {
                    AddMessage("Error: " + ex.Message, true, Color.Red);
                    // zucht
                }
                catch (Exception ex)
                {
                    AddMessage("Error: " + ex.Message, true, Color.Red);
                    //tfuck?
                }
            }
            else
            {
                // Current thread was the GUI thread.
                AddMessage("Connection open. Now listening.");
            }
        }

        private void ClientDisconnected()
        {
            // Check if the current thread is the GUI thread.
            if (this.InvokeRequired)
            {
                try
                {
                    // Execute this method on the control's thread.
                    this.Invoke(new Action(() => ClientDisconnected()));
                }
                catch (ObjectDisposedException ex)
                {
                    AddMessage("Error: " + ex.Message, true, Color.Red);
                    // zucht
                }
                catch (Exception ex)
                {
                    AddMessage("Error: " + ex.Message, true, Color.Red);
                    //tfuck?
                }
            }
            else
            {
                // Current thread was the GUI thread.
                AddMessage("Client disconnected.");
                mTransparentModeState = false;
                EnableControls(false, false);
            }
        }

        private void SendByeRequest(ByeReason reason)
        {
            // Create request message.
            TlvMessageEcr requestMessage = CreateMessage(MessageType.ByeRequest);

            // Fill the reason.
            requestMessage.Body.AddTlvUInt8AsHex((uint)TlvLib.Tag.ByeReason, (byte)reason);

            // Send the message.
            try
            {
                mConnectionHandler.SendMessage(requestMessage);
                ConnectionHandler.ConnectionHandler.WriteToFile(requestMessage, "ByeRequest.msg");
            }
            catch (Exception ex)
            {
                AddMessage(String.Format("Error sending bye request: {0}", ex.Message), true, Color.White, Color.Red);
                WaitForClient();
            }
        }

        /// <summary>
        /// Send a version information request message.
        /// </summary>
        /// <param name="reason">The bye reason to send.</param>
        private void SendVersionInformationRequest(ApplicationId applicationId)
        {
            // Create request message.
            TlvMessageEcr requestMessage = CreateMessage(MessageType.VersionInformationRequest);

            // Fill the application ID.
            requestMessage.Body.AddTlvUInt8AsHex((uint)TlvLib.Tag.ApplicationId, (byte)applicationId);

            // Send the message.
            try
            {
                mConnectionHandler.SendMessage(requestMessage);
                ConnectionHandler.ConnectionHandler.WriteToFile(requestMessage, "VersionInformationRequest.msg");
            }
            catch (Exception ex)
            {
                AddMessage(String.Format("Error sending version information request: {0)", ex.Message), true, Color.White, Color.Red);
            }
        }

        /// <summary>
        /// Start a transaction (can be called from non GUI threads).
        /// </summary>
        private void StartTransaction(TransactionType transactionType, string reference, IntermediateResultMode intermediateResultMode, bool enableTransparentMode, string amountInEurocent)
        {
            // Check if the current thread is the GUI thread.
            if (this.InvokeRequired)
            {
                try
                {
                    // Execute this method on the control's thread.
                    this.Invoke(new Action(() => StartTransaction(transactionType, reference, intermediateResultMode, enableTransparentMode, amountInEurocent)));
                }
                catch (ObjectDisposedException ex)
                {
                    AddMessage("Error: " + ex.Message, true, Color.Red);
                    // zucht
                }
                catch (Exception ex)
                {
                    AddMessage("Error: " + ex.Message, true, Color.Red);
                    //tfuck?
                }
            }
            else
            {
                uint mAmount = 0;
                if (!uint.TryParse(amountInEurocent, out mAmount)) return;

                // Current thread was the GUI thread.
                mTransparantModeCardUid = null;

                // Retrieve the transaction type to determine if an authorisation code or token should be asked.
                //ChessPt.TlvLib.TransactionType transactionType = (ChessPt.TlvLib.TransactionType)cbTransactionType.SelectedItem;

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
                //ClearTickets();

                // Set initial message
                AddMessage("Transaction started...", true, Color.OliveDrab, Color.White);

                // Create request message.
                TlvMessageEcr requestMessage = CreateMessage(MessageType.TransactionRequest);

                // TODO: Determine transaction language.

                // Create transaction data.
                TlvConstructed tlvTransactionData = new TlvConstructed((uint)TlvLib.Tag.Group_TransactionData);
                tlvTransactionData.AddTlvUInt32AsBcd((uint)TlvLib.Tag.Amount, mAmount);
                tlvTransactionData.AddTlvUInt16AsBcd((uint)TlvLib.Tag.CurrencyCode, 978);		// Euro.
                tlvTransactionData.AddTlvUInt8AsBcd((uint)TlvLib.Tag.CurrencyExponent, 2);		// Cents.
                tlvTransactionData.AddTlvAsString((uint)TlvLib.Tag.MerchantTransactionReference, reference);
                tlvTransactionData.AddTlvUInt8AsHex((uint)TlvLib.Tag.TransactionType, (byte)transactionType);
                tlvTransactionData.AddTlvUInt8AsHex((uint)TlvLib.Tag.IntermediateResultMode, (byte)intermediateResultMode);

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

                if (Settings.Default.TransactionMode != -1)
                {
                    tlvTransactionData.AddTlvUInt8AsHex((uint)TlvLib.Tag.TransactionMode, (byte)Settings.Default.TransactionMode);
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
                TlvConstructed tlvPrintData = new TlvConstructed((uint)TlvLib.Tag.Group_PrintData);
                if (cents == 19)
                {
                    tlvPrintData.AddTlvUInt8AsHex((uint)TlvLib.Tag.PrintOrigin, (byte)PrintOrigin.Terminal);
                }
                else
                {
                    tlvPrintData.AddTlvUInt8AsHex((uint)TlvLib.Tag.PrintOrigin, (byte)PrintOrigin.CashRegister);
                }
                tlvPrintData.AddTlvUInt8AsBcd((uint)TlvLib.Tag.PaperWidth, (byte)36);
                requestMessage.Body.AddTlv(tlvPrintData);

                // Set transaction ID.
                requestMessage.Body.AddTlvUInt64AsHex((uint)TlvLib.Tag.TransactionId, mTransactionId++);

                // Add transparent mode group.
                if (enableTransparentMode)
                {
                    TlvConstructed tlvGroupTransparentMode = new TlvConstructed((uint)TlvLib.Tag.Group_TmTransparentMode);
                    tlvGroupTransparentMode.AddTlvUInt8AsHex((uint)TlvLib.Tag.TmTransparentMode, 1);
                    requestMessage.Body.AddTlv(tlvGroupTransparentMode);
                }

                // Send the message.
                try
                {
                    mConnectionHandler.SendMessage(requestMessage);
                    ConnectionHandler.ConnectionHandler.WriteToFile(requestMessage, "TransactionRequest.msg");
                }
                catch (Exception ex)
                {
                    AddMessage(String.Format("Error sending transaction request: {0}", ex.Message), true, Color.White, Color.Red);
                }

            }
        }

        private void CancelTransaction()
        {
            // Create request message.
            TlvMessageEcr requestMessage = CreateMessage(MessageType.CancelRequest);

            // Fill the reason.
            requestMessage.Body.AddTlvUInt8AsHex((uint)TlvLib.Tag.CancelReason, (byte)CancelReason.Manual);

            // Send the message.
            try
            {
                mConnectionHandler.SendMessage(requestMessage);
                ConnectionHandler.ConnectionHandler.WriteToFile(requestMessage, "CancelRequest.msg");
            }
            catch (Exception ex)
            {
                AddMessage(String.Format("Error sending cancel request: {0)", ex.Message), true, Color.White, Color.Red);
            }
        }

        private void StartStopTransparentMode()
        {
            // Create request message.
            TlvMessageEcr tlvRequestMessage = CreateMessage(MessageType.TmTransparentModeRequest);

            // Fill the transparent mode state.
            if (!mTransparentModeState)
            {
                // Detect custom card and switch to transparent mode.
                mTransparantModeCardUid = null;
                tlvRequestMessage.Body.AddTlvUInt8AsHex((uint)TlvLib.Tag.TmTransparentMode, 1);

                // Create UI control group TLV.
                TlvConstructed tlvUiControl = new TlvConstructed((uint)TlvLib.Tag.Group_TmUiControl);
                tlvUiControl.AddTlvAsString((uint)TlvLib.Tag.TmDisplayText, "PRESENT CARD");
                tlvUiControl.AddTlvUInt8AsHex((uint)TlvLib.Tag.TmBeepType, (byte)TmBeepType.Attention);
                tlvUiControl.AddTlvUInt8AsHex((uint)TlvLib.Tag.TmLedControl, (byte)TmLedControl.Led1);
                tlvRequestMessage.Body.AddTlv(tlvUiControl);

                EnableControls(false, true);
            }
            else
            {
                // Turn off transparent mode.
                tlvRequestMessage.Body.AddTlvUInt8AsHex((uint)TlvLib.Tag.TmTransparentMode, 0);

                // Create UI control group TLV.
                TlvConstructed tlvUiControl = new TlvConstructed((uint)TlvLib.Tag.Group_TmUiControl);
                tlvUiControl.AddTlvAsString((uint)TlvLib.Tag.TmDisplayText, "REMOVE CARD");
                tlvUiControl.AddTlvUInt8AsHex((uint)TlvLib.Tag.TmBeepType, (byte)TmBeepType.Success);
                tlvUiControl.AddTlvUInt8AsHex((uint)TlvLib.Tag.TmLedControl, (byte)TmLedControl.All);
                tlvRequestMessage.Body.AddTlv(tlvUiControl);
            }

            // Fill the card detection time-out.
            tlvRequestMessage.Body.AddTlvUInt16AsHex((uint)TlvLib.Tag.TmCardDetectionTimeout, (ushort)Settings.Default.TmCardDetectionTimeout);

            // Send the message.
            try
            {
                mConnectionHandler.SendMessage(tlvRequestMessage);
                ConnectionHandler.ConnectionHandler.WriteToFile(tlvRequestMessage, "TmTransparentModeRequest.msg");
            }
            catch (Exception ex)
            {
                AddMessage(String.Format("Error sending transparent mode request: {0)", ex.Message), true, Color.White, Color.Red);
            }
        }

        private void TransparentModeReadCard()
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
            TlvMessageEcr tlvRequestMessage = CreateMessage(MessageType.TmReadCardDataRequest);

            // Fill memory address and data size.
            tlvRequestMessage.Body.AddTlvUInt16AsHex((uint)TlvLib.Tag.TmAddress, frm.Address);
            tlvRequestMessage.Body.AddTlvUInt16AsHex((uint)TlvLib.Tag.TmDataSize, frm.DataSize);

            // Send the message.
            try
            {
                mConnectionHandler.SendMessage(tlvRequestMessage);
                ConnectionHandler.ConnectionHandler.WriteToFile(tlvRequestMessage, "TmTransparentModeRequest.msg");
            }
            catch (Exception ex)
            {
                AddMessage(String.Format("Error sending read card data request: {0)", ex.Message), true, Color.White, Color.Red);
            }
        }

        private void restartApp()
        {
            System.Diagnostics.Process.Start(Application.ExecutablePath); // to start new instance of application
            Thread.Sleep(1000); // 1 second of sleep
            this.Close();
        }

        private void toggleLoggingView(bool show)
        {
            if (show)
            {
                this.Width = 867;
                btnToggleLoggingHide.Visible = true;
                btnToggleLoggingView.Visible = false;
            }
            else
            {
                this.Width = 400;
                btnToggleLoggingHide.Visible = false;
                btnToggleLoggingView.Visible = true;
            }
        }

        private void DisplayConnectionIndicator(Color color, string text)
        {
            if (this.InvokeRequired)
            {
                try
                {
                    // Execute this method on the control's thread
                    this.Invoke(new Action(() => DisplayConnectionIndicator(color, text)));
                }
                catch (ObjectDisposedException ex)
                {
                    AddMessage("Error: " + ex.Message, true, Color.Red);
                    // zucht
                }
                catch (Exception ex)
                {
                    AddMessage("Error: " + ex.Message, true, Color.Red);
                    //tfuck?
                }
            }
            else
            {
                connectionIndicator.BackColor = color;
                connectionIndicator.Text = text;

                if (color == Color.Red || color == Color.OrangeRed)
                {
                    connectionIndicator.ForeColor = Color.White;
                }
                else
                {
                    connectionIndicator.ForeColor = Color.Black;
                }

                if (color != Color.LightGreen && text == "0")
                {
                    connectionIndicator.Text = DateTime.Now.ToString("HH':'mm':'ss");
                }
            }
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
            keyGenData.AddRange(Conversions.HexStringToByteArray(Settings.Default.TmKeyGenSecret));

            // Add dealer ID to keygen data (8 bytes).
            string dealerIdString = Settings.Default.TmDealerId;
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
                foreach (string entry in Settings.Default.TmCardKeys)
                {
                    // Split the string in card UID and key.
                    int index = entry.IndexOf(';');
                    if (index > 0)
                    {
                        byte[] uid = Conversions.HexStringToByteArray(entry.Substring(0, index));
                        byte[] key = Conversions.HexStringToByteArray(entry.Substring(index + 1));

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
            TlvMessageEcr tlvRequestMessage = CreateMessage(MessageType.TmAuthenticateRequest);

            // Fill the authorisation key.
            tlvRequestMessage.Body.AddTlv(new Tlv((uint)TlvLib.Tag.TmKey, encryptedAuthoristionKey));

            // Send the message.
            try
            {
                mConnectionHandler.SendMessage(tlvRequestMessage);
                ConnectionHandler.ConnectionHandler.WriteToFile(tlvRequestMessage, "TmAutheticateRequest.msg");
            }
            catch (Exception ex)
            {
                AddMessage(String.Format("Error sending authenticate request: {0)", ex.Message), true, Color.White, Color.Red);
            }

        }

        /// <summary>
        /// Process the entry of the manager password.
        /// Some transaction types like refund need a password.
        /// </summary>
        /// <param name="transactionType">The type of the transaction.</param>
        /// <returns>True if transaction allowed by manager.</returns>
        bool ProcessManagerPassword(TransactionType transactionType)
        {
            // When cancellation or refund, ask for manager code.
            if (transactionType == TransactionType.Cancellation ||
                transactionType == TransactionType.CancellationPayment ||
                transactionType == TransactionType.CancellationCashAdvance ||
                transactionType == TransactionType.CancellationPreAuthorization ||
                transactionType == TransactionType.CancellationPaymentCompletion ||
                transactionType == TransactionType.Refund)
            {
                // Ask for manager password until correct or cancelled.
                string managerPassword;
                while (true)
                {
                    // Ask for manager password.
                    if (InputDialog.Show("This transaction type requires confirmation using manager password. Enter manager password:", "Manager Password", out managerPassword) != DialogResult.OK)
                    {
                        // Exit when no manager password was entered.
                        return false;
                    }

                    // Exit loop when entered code is correct.
                    if (managerPassword == Settings.Default.ManagerPassword) break;
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
        bool ProcessAuthorisationCode(TransactionType transactionType, out string authorisationCode)
        {
            // Initially no authorisation code.
            authorisationCode = null;

            // When cancellation, ask for authorisation code.
            if (transactionType == TransactionType.Cancellation ||
                transactionType == TransactionType.CancellationPayment ||
                transactionType == TransactionType.CancellationCashAdvance ||
                transactionType == TransactionType.CancellationPreAuthorization ||
                transactionType == TransactionType.CancellationPaymentCompletion)
            {
                if (InputDialog.Show("Enter the authorisation code of the transaction to cancel:", "Authorisation code", out authorisationCode) != DialogResult.OK)
                {
                    // Exit when no authorisation code was entered.
                    return false;
                }
            }

            // When payment completion, ask for authorisation code.
            if (transactionType == TransactionType.PaymentCompletion)
            {
                if (InputDialog.Show("Enter the authorisation code of the transaction to complete:", "Authorisation code", out authorisationCode) != DialogResult.OK)
                {
                    // Exit when no authorisation code was entered.
                    return false;
                }
            }

            // When update pre-authorisation, ask for authorisation code.
            if (transactionType == TransactionType.UpdatePreAuthorization)
            {
                if (InputDialog.Show("Enter the authorisation code of the transaction to complete:", "Authorisation code", out authorisationCode) != DialogResult.OK)
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
        bool ProcessToken(TransactionType transactionType, out string token)
        {
            // Initially no token.
            token = null;

            // When pre-authorisation, ask for token.
            if (transactionType == TransactionType.UpdatePreAuthorization ||
                transactionType == TransactionType.PaymentCompletion ||
                transactionType == TransactionType.CancellationPreAuthorization)
            {
                // Ask for the token until it satisfies the Luhn check.
                bool tokenValid = false;
                while (!tokenValid)
                {
                    if (InputDialog.Show("Enter the token of the pre-authorisation:", "Token", out token) != DialogResult.OK)
                    {
                        // Exit when no authorisation code was entered.
                        return false;
                    }

                    // Check the token in case one was entered.
                    tokenValid = token.Length != 0 ? LuhnCheck.LuhnCheckMod10Plus1(token) : true;
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

        #region Implementation of the IMessageHandler interface.

        /// <summary>
        /// Handle an incoming "hello request" message.
        /// </summary>
        /// <param name="tlvRequestMessage">The hello request message.</param>
        /// <return>True if message processing should continue. False if message processing should stop and the connection closed.</return>
        bool IMessageHandler.HandleHelloRequest(TlvMessageEcr tlvRequestMessage)
        {
            EnableControls(true, false);

            // Reset sent sequence numnber and store the terminal ID.
            mSentMessageSequenceNr = 0;
            Tlv tlvTerminalId = tlvRequestMessage.Header.FindTlv((uint)TlvLib.Tag.TerminalId);
            if (tlvTerminalId != null) mTerminalId = tlvTerminalId.GetValueFromString();
            Tlv tlvSerialNumber = tlvRequestMessage.Body.FindTlv((uint)TlvLib.Tag.SerialNumber);
            if (tlvSerialNumber != null) mSerialNumber = tlvSerialNumber.GetValueFromString();
            Tlv tlvLogicalId = tlvRequestMessage.Body.FindTlv((uint)TlvLib.Tag.LogicalId);
            if (tlvLogicalId != null) mLogicalId = tlvLogicalId.GetValueFromString();
            mTransparentModeState = false;

            // Process the connection parameters.
            ushort requestedKeepAliveInterval = 0;
            TlvConstructed tlvConnectionParameters = tlvRequestMessage.Body.FindTlvConstructed((uint)TlvLib.Tag.Group_ConnectionParameters);
            if (tlvConnectionParameters != null)
            {
                Tlv tlvKeepAliveInterval = tlvConnectionParameters.FindTlv((uint)TlvLib.Tag.KeepAliveInterval);
                if (tlvKeepAliveInterval != null) requestedKeepAliveInterval = tlvKeepAliveInterval.GetValueUInt16FromBcd();
            }

            // Determine the keep-alive interval to use.
            if (Settings.Default.KeepAliveInterval < 0)
            {
                // Terminal determined keep-alive interval.
                mKeepAliveInterval = requestedKeepAliveInterval;
            }
            else if (Settings.Default.KeepAliveInterval == 0)
            {
                // No keep alive interval.
                mKeepAliveInterval = 0;
            }
            else
            {
                // Cash register determined keep-alive interval.
                mKeepAliveInterval = (ushort)Settings.Default.KeepAliveInterval;
            }
            SetMerchantMessage("Terminal connected.");
            DisplayConnectionIndicator(Color.Yellow, "!");
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
            TlvMessageEcr tlvResponseMessage = CreateMessage(MessageType.HelloResponse);

            // Fill the body.

            // Set result code.
            tlvResponseMessage.Body.AddTlvUInt16AsHex((uint)TlvLib.Tag.ResultCode, (ushort)EcrResultCode.ResultOK);

            // Add connection parameters with keep-alive interval.
            {
                TlvConstructed connectionParameters = new TlvConstructed((uint)TlvLib.Tag.Group_ConnectionParameters);
                connectionParameters.AddTlvUInt16AsBcd((uint)TlvLib.Tag.KeepAliveInterval, mKeepAliveInterval);
                tlvResponseMessage.Body.AddTlv(connectionParameters);
            }

            // Send the message.
            try
            {
                mConnectionHandler.SendMessage(tlvResponseMessage);
                ConnectionHandler.ConnectionHandler.WriteToFile(tlvResponseMessage, "HelloResponse.msg");
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
        bool IMessageHandler.HandleKeepAliveRequest(TlvConstructed tlvRequestMessage)
        {
            // Stop the keep-alive timer.
            mKeepAliveTimer.Stop();

            KeepAliveReason keepAliveReason = (KeepAliveReason)tlvRequestMessage.FindTlv((uint)TlvLib.Tag.KeepAliveReason).GetValueUInt8FromHex();

            // Create response message.
            TlvMessageEcr tlvResponseMessage = CreateMessage(MessageType.KeepAliveResponse);

            // Fill the body.

            // Set result code and echo reason.
            tlvResponseMessage.Body.AddTlvUInt8AsHex((uint)TlvLib.Tag.KeepAliveReason, (byte)keepAliveReason);
            tlvResponseMessage.Body.AddTlvUInt16AsHex((uint)TlvLib.Tag.ResultCode, (ushort)EcrResultCode.ResultOK);

            // Send the message.
            try
            {
                mConnectionHandler.SendMessage(tlvResponseMessage);
                ConnectionHandler.ConnectionHandler.WriteToFile(tlvResponseMessage, "KeepAliveResponse.msg");
            }
            catch (Exception ex)
            {
                AddMessage(String.Format("Error sending keep-alive response: {0)", ex.Message), true, Color.White, Color.Red);
            }

            // Status update or keep-alive.
            if (keepAliveReason == KeepAliveReason.Status)
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
        bool IMessageHandler.HandleByeResponse(TlvConstructed tlvResponseMessage)
        {
            EcrResultCode resultCode = (EcrResultCode)tlvResponseMessage.FindTlv((uint)TlvLib.Tag.ResultCode).GetValueUInt16FromHex();
            if (resultCode == EcrResultCode.ResultOK)
            {
                SetMerchantMessage(String.Format("Terminal disconnected. Bye reason: {0}", (ByeReason)tlvResponseMessage.FindTlv((uint)TlvLib.Tag.ByeReason).GetValueUInt8FromHex()));
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
        bool IMessageHandler.HandleTransactionResponse(TlvConstructed tlvResponseMessage)
        {
            this.Invoke(new Action(() =>
            {
                string cardholderTicket = "";
                string merchantTicket = "";
                string journalTicket = "";

                // Extract ticket data.
                TlvConstructed tlvTicketData = tlvResponseMessage.FindTlvConstructed((uint)TlvLib.Tag.Group_TicketData);
                foreach (TlvConstructed tlvTicket in tlvTicketData.FindAll((uint)TlvLib.Tag.Group_TableRecord))
                {
                    switch ((TicketType)tlvTicket.FindTlv((uint)TlvLib.Tag.TicketType).GetValueUInt8FromHex())
                    {
                        case TicketType.CardHolder:
                            {
                                cardholderTicket = tlvTicket.FindTlv((uint)TlvLib.Tag.TicketBody).GetValueFromString();
                                ParsePaymentResponseMessage(cardholderTicket);
                                break;
                            }

                        case TicketType.Merchant:
                            {
                                merchantTicket = tlvTicket.FindTlv((uint)TlvLib.Tag.TicketBody).GetValueFromString();
                                break;
                            }

                        case TicketType.Journal:
                            {
                                journalTicket = tlvTicket.FindTlv((uint)TlvLib.Tag.TicketBody).GetValueFromString();
                                break;
                            }
                    }
                }

                ////// Display the tickets.
                ////DisplayTickets(cardholderTicket, merchantTicket, journalTicket);

                // Display result.
                TransactionResult transactionResult = (TransactionResult)tlvResponseMessage.FindTlv((uint)TlvLib.Tag.TransactionResult).GetValueUInt8FromHex();
                EcrResultCode resultCode = (EcrResultCode)tlvResponseMessage.FindTlv((uint)TlvLib.Tag.ResultCode).GetValueUInt16FromHex();
                SetMerchantMessage(String.Format("Transaction result received: {0} [Result code: {1}]", transactionResult, resultCode));

                //get message to KASSA
                SendMessageToClient(transactionResult,resultCode);

                if (transactionResult == TransactionResult.TransparentMode)
                {
                    mTransparentModeState = true;
                    EnableControls(false, false);

                    // Retrieve UID.
                    TlvConstructed tlvGroupTransparentMode = tlvResponseMessage.FindTlvConstructed((uint)TlvLib.Tag.Group_TmTransparentMode);
                    if (tlvGroupTransparentMode != null)
                    {
                        Tlv tlvUid = tlvGroupTransparentMode.FindTlv((uint)TlvLib.Tag.TmCardUid);
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
                    ////// Optionally increment the amount (only when result was not busy).
                    if (resultCode != EcrResultCode.CtapBusy)
                    {
                        ////if (cbAutoIncrementAmount.Checked && resultCode != ChessPt.TlvLib.EcrResultCode.CtapBusy)
                        ////{
                        ////    mAmount += 1;
                        ////    FormatAmount();
                        ////}

                        ////// Start a new transaction if requested.
                        ////if (cbAutoRepeatTransaction.Checked)
                        ////{
                        mAutoRepeatTimer.Interval = Settings.Default.AutoRepeatInterval;
                        mAutoRepeatTimer.Start();
                        AddMessage(String.Format("Auto-starting transaction in {0} seconds", mAutoRepeatTimer.Interval / 1000.0), false, Color.White, Color.DarkGreen);
                        ////}
                        ////else
                        ////{
                        ////    // Enable the controls again when no new transaction is done.
                        ////    EnableControls(true, false);
                        ////}
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
        bool IMessageHandler.HandleSignalIntermediateResultRequest(TlvConstructed tlvRequestMessage)
        {
            // Display result.
            TransactionResult transactionResult = (TransactionResult)tlvRequestMessage.FindTlv((uint)TlvLib.Tag.TransactionResult).GetValueUInt8FromHex();
            uint authorisedAmount = (uint)tlvRequestMessage.FindTlv((uint)TlvLib.Tag.Amount).GetValueUInt32FromBcd();
            Tlv tlvIntermediateResultMode = tlvRequestMessage.FindTlv((uint)TlvLib.Tag.IntermediateResultMode);
            IntermediateResultMode mode = tlvIntermediateResultMode != null ? (IntermediateResultMode)tlvIntermediateResultMode.GetValueUInt8FromHex() : IntermediateResultMode.None;
            ////DisplayIntermediateResult(transactionResult, authorisedAmount, mode);
            return true;
        }


        /// <summary>
        /// Handle an incoming "cancel response" message.
        /// </summary>
        /// <param name="tlvResponseMessage">The cancel response body.</param>
        /// <return>True if message processing should continue. False if message processing should stop and the connection closed.</return>
        bool IMessageHandler.HandleCancelResponse(TlvConstructed tlvResponseMessage)
        {
            EcrResultCode result = (EcrResultCode)tlvResponseMessage.FindTlv((uint)TlvLib.Tag.ResultCode).GetValueUInt16FromHex();
            switch (result)
            {
                case EcrResultCode.ResultOK:
                    {
                        AddMessage("Cancellation request acknowledged.");
                        break;
                    }

                case EcrResultCode.Rejected:
                    {
                        AddMessage("Cancellation request rejected.", false, Color.Red);
                        break;
                    }

                case EcrResultCode.CancelFailed:
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
        bool IMessageHandler.HandleInformationReport(TlvConstructed tlvReportMessage)
        {
            // Process the "information report" on the GUI thread (Lamda function).
            // Since a blocking dialog is opened BeginInvoke() is used. Invoke() will block until complete and thus result in keep-alive time-out.
            this.BeginInvoke(new Action(() =>
            {
                //				// Process the terminal state.
                //				ProcessTerminalState((TerminalState)message.TerminalState);

                // Get the transaction stage.
                TransactionStage transactionStage = (TransactionStage)tlvReportMessage.FindTlv((uint)TlvLib.Tag.TransactionStage).GetValueUInt8FromHex();

                // Print stage message.
                Tlv stageMessage = tlvReportMessage.FindTlv((uint)TlvLib.Tag.StageMessage);
                if (stageMessage != null)
                {
                    SetMerchantMessage(String.Format(" [{0}]\n {1}", transactionStage, stageMessage.GetValueFromString()));
                }

                // Display merchant text in dialog.
                Tlv merchantText = tlvReportMessage.FindTlv((uint)TlvLib.Tag.MerchantText);
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
        bool IMessageHandler.HandleTmsSessionResponse(TlvConstructed tlvResponseMessage)
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
        bool IMessageHandler.HandleLastTransactionStatusResponse(TlvConstructed tlvResponseMessage)
        {
            // Process the "last transaction response" on the GUI thread (Lambda function).
            // Since a blocking dialog is opened BeginInvoke() is used. Invoke() will block until complete and thus result in keep-alive time-out.
            this.BeginInvoke(new Action(() =>
            {
                //				// Process the terminal state.
                //				ProcessTerminalState((TerminalState)message.TerminalState);

                // Display result code.
                EcrResultCode resultCode = (EcrResultCode)tlvResponseMessage.FindTlv((uint)TlvLib.Tag.ResultCode).GetValueUInt16FromHex();
                SetMerchantMessage(String.Format("Last transaction status response: {0}", resultCode));

                // Extract transaction info.
                TlvConstructed tlvTransactionInformation = tlvResponseMessage.FindTlvConstructed((uint)TlvLib.Tag.Group_TransactionInformation);

                // Display transaction data.
                if (resultCode == EcrResultCode.ResultOK && tlvTransactionInformation != null)
                {
                    // Retrieve amount & currency exponent.
                    Tlv tlvAmount = tlvTransactionInformation.FindTlv((uint)TlvLib.Tag.Amount);
                    Tlv tlvCurrencyExponent = tlvTransactionInformation.FindTlv((uint)TlvLib.Tag.CurrencyExponent);

                    // Calculate the amount.
                    double amount = tlvAmount.GetValueUInt32FromBcd() / Math.Pow(10.0, tlvCurrencyExponent.GetValueUInt8FromBcd());

                    // Build message.
                    string msg = "";

                    // Transaction ID.
                    Tlv tlvTransactionId = tlvResponseMessage.FindTlv((uint)TlvLib.Tag.TransactionId);
                    if (tlvTransactionId != null)
                    {
                        msg += String.Format("Transaction ID: {0}\n", tlvTransactionId.GetValueUInt64FromHex());
                    }
                    else
                    {
                        msg += "Transaction ID: [no ID given]\n";
                    }

                    // Transaction reference.
                    Tlv tlvReference = tlvTransactionInformation.FindTlv((uint)TlvLib.Tag.MerchantTransactionReference);
                    if (tlvReference != null)
                    {
                        msg += String.Format("Reference: {0}\n", tlvReference.GetValueFromString());
                    }
                    else
                    {
                        msg += "Reference: [no reference given]\n";
                    }

                    // Amount.
                    Tlv tlvCurrency = tlvTransactionInformation.FindTlv((uint)TlvLib.Tag.CurrencyCode);
                    CurrencyCode currency = CurrencyCodeExtensions.Create(tlvCurrency.GetValueUInt16FromBcd());
                    msg += String.Format("Amount: {0} {1}\n", CurrencyCodeExtensions.ToCurrencySign(currency), amount);

                    // Transaction date/time.
                    Tlv tlvTransactionDateTime = tlvTransactionInformation.FindTlv((uint)TlvLib.Tag.TransactionDateTime);
                    try
                    {
                        msg += String.Format("DateTime: {0}\n", tlvTransactionDateTime.GetValueFromDateTime());
                    }
                    catch (Exception)
                    {
                        msg += String.Format("DateTime: [no (correct) date/time given]\n");
                    }

                    // Transaction result.
                    TransactionResult transactionResult = (TransactionResult)tlvTransactionInformation.FindTlv((uint)TlvLib.Tag.TransactionResult).GetValueUInt8FromHex();
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
        bool IMessageHandler.HandleLastTransactionTicketResponse(TlvConstructed tlvResponseMessage)
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
                TlvConstructed tlvTicketData = tlvResponseMessage.FindTlvConstructed((uint)TlvLib.Tag.Group_TicketData);
                foreach (TlvConstructed tlvTicket in tlvTicketData.FindAll((uint)TlvLib.Tag.Group_TableRecord))
                {
                    ++ticketCount;
                    switch ((TicketType)tlvTicket.FindTlv((uint)TlvLib.Tag.TicketType).GetValueUInt8FromHex())
                    {
                        case TicketType.CardHolder:
                            {
                                cardholderTicket = tlvTicket.FindTlv((uint)TlvLib.Tag.TicketBody).GetValueFromString();
                                break;
                            }

                        case TicketType.Merchant:
                            {
                                merchantTicket = tlvTicket.FindTlv((uint)TlvLib.Tag.TicketBody).GetValueFromString();
                                break;
                            }

                        case TicketType.Journal:
                            {
                                journalTicket = tlvTicket.FindTlv((uint)TlvLib.Tag.TicketBody).GetValueFromString();
                                break;
                            }
                    }
                }

                // Display the tickets.
                ////DisplayTickets(cardholderTicket, merchantTicket, journalTicket);

                // Display result code.
                EcrResultCode resultCode = (EcrResultCode)tlvResponseMessage.FindTlv((uint)TlvLib.Tag.ResultCode).GetValueUInt16FromHex();
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
        bool IMessageHandler.HandleTotalsResponse(TlvConstructed tlvResponseMessage)
        {
            this.Invoke(new Action(() =>
            {
                //string cardholderTicket = "";
                //string merchantTicket = "";
                string journalTicket = "";

                // Extract ticket data.
                TlvConstructed tlvTicketData = tlvResponseMessage.FindTlvConstructed((uint)TlvLib.Tag.Group_TicketData);
                foreach (TlvConstructed tlvTicket in tlvTicketData.FindAll((uint)TlvLib.Tag.Group_TableRecord))
                {
                    switch ((TicketType)tlvTicket.FindTlv((uint)TlvLib.Tag.TicketType).GetValueUInt8FromHex())
                    {
                        case TicketType.Totals:
                            {
                                journalTicket = tlvTicket.FindTlv((uint)TlvLib.Tag.TicketBody).GetValueFromString();
                                break;
                            }
                    }
                }

                // Display the tickets.
                ////DisplayTickets(cardholderTicket, merchantTicket, journalTicket);

                // Display result.
                TransactionResult transactionResult = (TransactionResult)tlvResponseMessage.FindTlv((uint)TlvLib.Tag.ResultCode).GetValueUInt8FromHex();
                SetMerchantMessage(String.Format("Transaction result received: {0}", transactionResult));

                // Enable the controls again when no new transaction is done.
                EnableControls(true, false);
            }));

            // Continue message processing.
            return true;
        }


        #endregion

        #region Implementation of the IMessageHandler interface for version information.


        /// <summary>
        /// Handle an incoming "version information" response message.
        /// </summary>
        /// <param name="tlvResponseMessage">The "version information" response body.</param>
        /// <return>True if message processing should continue. False if message processing should stop and the connection closed.</return>
        bool IMessageHandler.HandleVersionInformationResponse(TlvConstructed tlvResponseMessage)
        {
            // Process the "version information" on the GUI thread (Lambda function).
            this.Invoke(new Action(() =>
            {
                // Extract application ID.
                ApplicationId applicationId = (ApplicationId)tlvResponseMessage.FindTlv((uint)TlvLib.Tag.ApplicationId).GetValueUInt8FromHex();

                // Extract result.
                EcrResultCode resultCode = (EcrResultCode)tlvResponseMessage.FindTlv((uint)TlvLib.Tag.ResultCode).GetValueUInt16FromHex();
                AddMessage(String.Format("Version information response: {0} [{1}]", resultCode, applicationId), true, Color.LightGreen);

                // Extract logical ID and serialnumber.
                string logicalId = tlvResponseMessage.FindTlv((uint)TlvLib.Tag.LogicalId).GetValueFromString();
                string serialNumber = tlvResponseMessage.FindTlv((uint)TlvLib.Tag.SerialNumber).GetValueFromString();
                AddMessage(String.Format("Logical ID: {0}, Serial number: {1}", logicalId, serialNumber));

                // Extract version information.
                string versionString = tlvResponseMessage.FindTlv((uint)TlvLib.Tag.VersionString).GetValueFromString();
                Tlv tlvVersionNumber = tlvResponseMessage.FindTlv((uint)TlvLib.Tag.VersionNumber);
                byte versionMajor = Conversions.BcdToUInt8(tlvVersionNumber.Value[0]);
                byte versionMinor = Conversions.BcdToUInt8(tlvVersionNumber.Value[1]);
                byte versionBuild = Conversions.BcdToUInt8(tlvVersionNumber.Value[2]);
                byte versionRevision = Conversions.BcdToUInt8(tlvVersionNumber.Value[3]);
                AddMessage(String.Format("{0} - Version: {1}.{2}.{3}.{4}", applicationId, versionMajor, versionMinor, versionBuild, versionRevision));
                AddMessage(String.Format("Version string: {0}", versionString));

                // Extract extra information.
                TlvConstructed tlvExtraInformation = tlvResponseMessage.FindTlvConstructed((uint)TlvLib.Tag.Group_ExtraInformation);
                if (tlvExtraInformation != null)
                {
                    foreach (TlvConstructed tlvInformationData in tlvExtraInformation.FindAll((uint)TlvLib.Tag.Group_TableRecord))
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
            UnitPrefix unitPrefix = (UnitPrefix)(sbyte)unitBytes[0];
            Unit unit = (Unit)unitBytes[1];

            // Format unit depending on the unit and unit prefix given.
            if (unit == Unit.None)
            {
                // No unit given, return empty string.
                return "";
            }
            if (unitPrefix != UnitPrefix.None)
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
        bool IMessageHandler.HandleTmTransparentModeResponse(TlvConstructed tlvResponseMessage)
        {
            // Get the transparent mode state.
            byte transparentModeState = tlvResponseMessage.FindTlv((uint)TlvLib.Tag.TmTransparentMode).GetValueUInt8FromHex();
            mTransparentModeState = transparentModeState == 0 ? false : true;

            // Retrieve result code.
            EcrResultCode resultCode = (EcrResultCode)tlvResponseMessage.FindTlv((uint)TlvLib.Tag.ResultCode).GetValueUInt16FromHex();

            // Retrieve UID.
            Tlv tlvUid = tlvResponseMessage.FindTlv((uint)TlvLib.Tag.TmCardUid);
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
                TlvMessageEcr tlvRequestMessage = CreateMessage(MessageType.TmUiControlRequest);

                // Fill UI control data (display text, beep type, LED control.
                tlvRequestMessage.Body.AddTlvAsString((uint)TlvLib.Tag.TmDisplayText, "Processing\nPlease Wait...");
                tlvRequestMessage.Body.AddTlvUInt8AsHex((uint)TlvLib.Tag.TmBeepType, (byte)TmBeepType.Attention);
                tlvRequestMessage.Body.AddTlvUInt8AsHex((uint)TlvLib.Tag.TmLedControl, (byte)TmLedControl.All);

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
            if (mTransparentModeState) EnableControls(false, false);
            else EnableControls(true, false);

            // Continue processing messages.
            return true;
        }


        /// <summary>
        /// Handle an incoming transparent mode "UI control" response message.
        /// </summary>
        /// <param name="tlvResponseMessage">The transparent mode "UI control" response body.</param>
        /// <return>True if message processing should continue. False if message processing should stop and the connection closed.</return>
        bool IMessageHandler.HandleTmUiControlResponse(TlvConstructed tlvResponseMessage)
        {
            // Retrieve result code.
            EcrResultCode resultCode = (EcrResultCode)tlvResponseMessage.FindTlv((uint)TlvLib.Tag.ResultCode).GetValueUInt16FromHex();

            AddMessage(String.Format("UI Control result code: {0}", resultCode));

            // Continue processing messages.
            return true;
        }


        /// <summary>
        /// Handle an incoming transparent mode "authenticate" response message.
        /// </summary>
        /// <param name="tlvResponseMessage">The transparent mode "authenticate" response body.</param>
        /// <return>True if message processing should continue. False if message processing should stop and the connection closed.</return>
        bool IMessageHandler.HandleTmAuthenticateResponse(TlvConstructed tlvResponseMessage)
        {
            // Retrieve result code.
            EcrResultCode resultCode = (EcrResultCode)tlvResponseMessage.FindTlv((uint)TlvLib.Tag.ResultCode).GetValueUInt16FromHex();

            AddMessage(String.Format("Authenticate result code: {0}", resultCode));

            // Continue processing messages.
            return true;
        }


        /// <summary>
        /// Handle an incoming transparent mode "read card data" response message.
        /// </summary>
        /// <param name="tlvResponseMessage">The transparent mode "read card data" response body.</param>
        /// <return>True if message processing should continue. False if message processing should stop and the connection closed.</return>
        bool IMessageHandler.HandleTmReadCardDataResponse(TlvConstructed tlvResponseMessage)
        {
            // Retrieve result code.
            EcrResultCode resultCode = (EcrResultCode)tlvResponseMessage.FindTlv((uint)TlvLib.Tag.ResultCode).GetValueUInt16FromHex();

            // Read the card data.
            Tlv tlvData = tlvResponseMessage.FindTlv((uint)TlvLib.Tag.TmData);
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

        #region SocketForKassa

        StreamWriter clientOut = null;
        public void OpenSocket(string ip, int port)
        {
            var worker = new BackgroundWorker();
            worker.WorkerReportsProgress = true;
            worker.WorkerSupportsCancellation = true;

            worker.ProgressChanged += (s, args) =>
            {
                AddMessage(args.UserState.ToString(), false, Color.LightGray);
            };

            worker.DoWork += (s, args) =>
            {
                // startup the server on localhost 
                var ipAddress = System.Net.IPAddress.Parse(ip);
                TcpListener server = new TcpListener(ipAddress, port);
                server.Start();

                while (!worker.CancellationPending)
                {

                    try
                    {
                        AddMessage(
                            string.Format("The terminal socket is waiting on {0}:{1}...", ipAddress.ToString(),
                                port.ToString()), false, Color.LightGray);

                        // as long as we're not pending a cancellation, let's keep accepting requests 
                        TcpClient attachedClient = server.AcceptTcpClient();

                        StreamReader clientIn = new StreamReader(attachedClient.GetStream());
                        clientOut = new StreamWriter(attachedClient.GetStream());
                        clientOut.AutoFlush = true;

                        string msg;
                        while ((msg = clientIn.ReadLine()) != null)
                        {
                            if (mCounterKeepAlive < 1)
                            {
                                //connection is not kept alive, restart
                                restartThread(true);
                            }

                            if (msg != "?")
                            {
                                AddMessage(string.Format("The terminal socket received: {0}", msg), false,
                                    Color.LightGray);
                                //SendMessageToClient(msg,true);

                                if (msg.StartsWith("*") && msg.EndsWith("B")) //bedrag te betalen
                                {
                                    string bedrag = Regex.Replace(msg, "[^0-9,.+-]", "").Replace(",", ".");
                                    if (HowManyDecimals(bedrag) > 0 && HowManyDecimals(bedrag) < 2)
                                    {
                                        bedrag = bedrag + "0";
                                    }
                                    else if (HowManyDecimals(bedrag) == 2)
                                    {
                                        bedrag = bedrag.Replace(".", ""); // remove comma to put it in eurocents
                                        if (bedrag.Contains("-"))
                                        {
                                            // negative amount, so refund
                                            bedrag = bedrag.Replace("-",
                                                ""); // remove negative indicator. Flag 'Refund' handles it
                                            StartTransaction(TransactionType.Refund, "",
                                                IntermediateResultMode.None, false,
                                                bedrag); // in eurocent
                                            SendToKassa("!LOCK");
                                            SendToKassa("-Wacht op kaart/PIN...");
                                        }
                                        else
                                        {
                                            // payment
                                            StartTransaction(TransactionType.Payment, "",
                                                IntermediateResultMode.None, false,
                                                bedrag); // in eurocent
                                            SendToKassa("!LOCK");
                                            SendToKassa("-Wacht op kaart/PIN...");
                                        }
                                    }
                                }
                            }
                        }
                    }
                    catch (System.IO.IOException ex)
                    {
                        AddMessage("Socket lost: " + ex.Message, true, Color.LightGray, Color.Red);
                        AddMessage("Attempting reconnect... ", true, Color.LightGray, Color.Red);
                    }
                    catch (Exception ex)
                    {
                        AddMessage("General Exception occured " + ex.Message, true, Color.LightGray, Color.Red);
                    }
                }
            };

            worker.RunWorkerAsync();
        }

        private int HowManyDecimals(string input)
        {
            int result = 0;
            if (input.IndexOf(".") != -1)
            {
                result = input.Length - (input.IndexOf(".") + 1);
            }
            return result;
        }

        private void SendToKassa(string msg)
        {
            try
            {
                if (clientOut != null && !string.IsNullOrWhiteSpace(msg))
                {
                    clientOut.WriteLine(msg);
                }
            }
            catch (Exception ex)
            {
                AddMessage("Could not send message to client: " + ex.Message, false, Color.Red);
            }
        }

        private void SendMessageToClient(TransactionResult transactionResult, EcrResultCode resultCode)
        {
            // message for register?
            // %    message for printer follows
            // -    ??
            // #    OK
            // ***  NOT OK
            if (transactionResult == TransactionResult.Approved)
            {
                //SendMessageToClient("OK!", true);
                SendToKassa("!UNLOCK");
                SendToKassa("Betaling uitgevoerd!");
                SendToKassa("#"); // "ok" message for register
            }
            else if (transactionResult == TransactionResult.Error)
            {
                //SendMessageToClient("Fout!", true);
                SendToKassa("!UNLOCK");
                if(resultCode==EcrResultCode.CtapInvalidAmount) SendToKassa("Ongeldig bedrag ...");
                else if (resultCode == EcrResultCode.CtapCustomerAborted) SendToKassa("Betaling gestopt ...");
                else if (resultCode == EcrResultCode.CtapMerchantAborted) SendToKassa("Betaling gestopt ...");
                else if (resultCode == EcrResultCode.CtapCardRemoved) SendToKassa("Kaart uitgetrokken ...");
                else if (resultCode == EcrResultCode.CtapCardNotSupported) SendToKassa("Kaart niet toegelaten ...");
                else if (resultCode == EcrResultCode.CtapCardInvalid) SendToKassa("Ongeldige kaart ...");
                else if (resultCode == EcrResultCode.CtapCardProblem) SendToKassa("Kaartprobleem ...");
                else SendToKassa("Terminalprobleem ...");
                SendToKassa("***"); // "NOT ok" message for register
            }
            else if (transactionResult == TransactionResult.Declined)
            {
                //SendMessageToClient("Kaart geweigerd!", true);
                SendToKassa("!UNLOCK");
                SendToKassa("Transactie geweigerd ...");
                SendToKassa("***"); // "NOT ok" message for register
            }
            else if (transactionResult == TransactionResult.Stopped)
            {
                //SendMessageToClient("Gestopt!", true);
                SendToKassa("!UNLOCK");
                SendToKassa("Transactie gestopt ...");
                SendToKassa("***"); // "NOT ok" message for register
            }
            else if (transactionResult == TransactionResult.TechnicalProblem)
            {
                //SendMessageToClient("Technische fout!", true);
                SendToKassa("!UNLOCK");
                SendToKassa("Transmissie fout ...");
                SendToKassa("***"); // "NOT ok" message for register
            }
        }

        private void ParsePaymentResponseMessage(String input)
        {
            if (!string.IsNullOrWhiteSpace(input))
            {
                String result = "";
                bool printSmall = true;

                List<string> lines = new List<string>();
                string text = input;

                if (text.Contains("\n"))
                {
                    //while (text.Contains("  "))
                    //{
                    //    //dubbele spate, dus splits op
                    //    text = text.Replace("  ", "\n");
                    //    //we cutten de dubbele \n hieronder toch af, dus komt goed!
                    //}
                    while (text.Contains("\n\n"))
                    {
                        text = text.Replace("\n\n", "\n");
                    }

                    while (text.Contains("\n"))
                    {
                        string line = text.Substring(0, text.IndexOf("\n") + 1);
                        text = text.Substring(text.IndexOf("\n") + 1);
                        line = line.Replace("\n", "");
                        //line = line.Trim();

                        if (line.Length > 0)
                        {
                            lines.Add(line);
                        }
                    }
                }
                else
                {
                    lines.Add(text);
                }

                string cardtype = "";
                string testline = "", alt_cardtype="";
                for (int i = 0; i < lines.Count; i++)
                {
                    testline = lines[i].ToUpper(); 
                    if (testline.Contains("MAESTRO")) alt_cardtype="MAESTRO";
                    else if (testline.Contains("MASTERCARD")) alt_cardtype = "MASTERCARD";
                    else if (testline.Contains("VISA")) alt_cardtype = "VISA";
                    else if (testline.Contains("V PAY")) alt_cardtype = "V PAY";
                    else if (testline.Contains("MONIZZE")) alt_cardtype = "MONIZZE";
                    else if (testline.Contains("SODEXO")) alt_cardtype = "SODEXO CARD";
                    if (lines[i].Contains("Transactie:"))
                    {
                        //cardtype staat op de volgende lijn
                        cardtype = lines[i + 1];
                    }
                }
                if(alt_cardtype!="") cardtype=alt_cardtype;
                switch (cardtype.ToUpper())
                {
                    case "BANCONTACT":
                    case "BANCONTACT EMV":
                        printSmall = true;
                        result = "#" + 1;
                        break;
                    case "MAESTRO":
                    case "MASTERCARD":
                    case "EC/MASTERCARD":
                        printSmall = true;
                        result = "#" + 2;
                        break;
                    case "V PAY":
                    case "V-PAY":
                    case "CREDIT VISA":
                    case "VISA":
                    case "VISA VPAY":
                    case "JBC":
                        printSmall = false;
                        result = "#" + 2;
                        break;
                    case "MOBIEL":
                        printSmall = false;
                        result = "#" + 3;
                        break;
                    case "SODEXO CARD":
                    case "SODEXO EPASS":
                        printSmall = false;
                        result = "#" + 4;
                        break;
                    case "EDENRED":
                        printSmall = false;
                        result = "#" + 5;
                        break;
                    case "MONIZZE":
                    case "PAYFAIR":
                        printSmall = false;
                        result = "#" + 6;
                        break;
                    case "RES":
                    case "ORES":
                        printSmall = false;
                        result = "#" + 7;
                        break;
                    case "AMERICAN EXPRESS":
                    case "DINERS":
                    case "AURORA":
                    default:
                        printSmall = false;
                        result = "#" + 1;
                        break;
                }

                result += cardtype; // ???

                string lineBreaker = "";
                for (int i = 0; i < 40; i++)
                {
                    lineBreaker += "-";
                }

                SendToKassa("Betaling uitgevoerd:");
                SendToKassa("%" + lineBreaker);

                if (printSmall)
                {
                    for (int i = 0; i < lines.Count; i++)
                    {
                        if (lines[i].ToLower().StartsWith("terminal:")
                            || lines[i].ToLower().StartsWith("kaart:")
                            || lines[i].ToLower().StartsWith("totaal:"))
                        {
                            SendToKassa("%" + lines[i]);
                        }
                        else if (lines[i].ToLower().StartsWith("transactie:"))
                        {
                            SendToKassa("%" + cardtype);
                        }
                    }
                }
                else
                {
                    for (int i = 0; i < lines.Count; i++)
                    {
                        SendToKassa("%" + lines[i]);
                    }
                }

                SendToKassa("%" + lineBreaker);

                SendToKassa(result); //eindresultaat, sluit de kassa transmissie af
            }
        }

        #endregion

        private void connectionIndicator_TextChanged(object sender, EventArgs e)
        {
            if (connectionIndicator.Text == @"s3cr3t")
            {
                if (!mEnabledSettings)
                {
                    connectionIndicator.Text = @"Unlocking";
                    ToggleEnableSettings();
                }
                else
                {
                    connectionIndicator.Text = @"Unlocked";
                }
            }
        }
    }
}
