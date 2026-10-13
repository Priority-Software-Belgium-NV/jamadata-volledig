// =========================================================================================
// ======================== T E L I U M   C A S H   R E G I S T E R ========================
// =========================================================================================
//
//		Module: CashRegister.Forms
//		File  : SettingsForm.cs
//		Author: rdem
//
//		Description:
//		Settings form for the Telium Cash Register application.
//
//
//		Last Modification:
//		$Id:
//
// -------------------------------------------------------------------------
//		Modifications:
//		Date		Author	Issue	Comment
//		2017-10-20	rdem			Added manager password and transaction mode.
//		2017-08-30	rdem			Added auto-repeat interval.
//		2016-06-28	rdem			Added serial connection parameters (baud rate, data bits, parity, stop bits, flow control).
//		2016-03-02	rdem			Added keep-alive options (terminal determined, none, cash register determined).
//
//
// =========================================================================================
// (C) Chess pT  2015-2017
// =========================================================================================


using System;
using System.Windows.Forms;
using System.IO.Ports;

using ChessPt.TlvCashRegisterLib;


namespace ChessPt.CashRegister.Forms
{
	/// <summary>
	/// Settings form for the Telium Cash Register application.
	/// </summary>
	public partial class SettingsForm: Form
	{
		/// <summary>
		/// Default constructor.
		/// </summary>
		public SettingsForm()
		{
			InitializeComponent();

			// Get the current TCP/IP listen port.
			textboxListenPort.ValidatingType = typeof(UInt16);
			textboxListenPort.Text = Properties.Settings.Default.TcpPort.ToString();

			// Get the keep-alive interval.
			int keepAliveInterval = Properties.Settings.Default.KeepAliveInterval;
			if (keepAliveInterval < 0)
			{
				// Terminal defined.
				radiobuttonKeepAliveIntervalTerminal.Checked = true;
				numericUpDownKeepAliveInterval.Value = 5;
			}
			else if (keepAliveInterval == 0)
			{
				// No keep-alive.
				radiobuttonKeepAliveIntervalNone.Checked = true;
				numericUpDownKeepAliveInterval.Value = 5;
			}
			else
			{
				// Cash register determined.
				radiobuttonKeepAliveIntervalCashregister.Checked = true;
				numericUpDownKeepAliveInterval.Value = keepAliveInterval;
			}
			KeepAliveMethodChanged();

			// Get the list of connection types and set the selected one.
			comboboxConnectionType.Items.Add(ConnectionType.Tcp);
			comboboxConnectionType.Items.Add(ConnectionType.Serial);
			comboboxConnectionType.SelectedItem = (ConnectionType)Properties.Settings.Default.ConnectionType;

			// Get a list of available COM ports and select the current one.
			comboboxComPort.Items.AddRange(SerialPort.GetPortNames());
			comboboxComPort.SelectedItem = Properties.Settings.Default.ComPort;

			// Fill the baud rate options and set the selected one.
			comboboxBaudRate.Items.Add(300);
			comboboxBaudRate.Items.Add(1200);
			comboboxBaudRate.Items.Add(2400);
			comboboxBaudRate.Items.Add(4800);
			comboboxBaudRate.Items.Add(9600);
			comboboxBaudRate.Items.Add(19200);
			comboboxBaudRate.Items.Add(38400);
			comboboxBaudRate.Items.Add(57600);
			comboboxBaudRate.Items.Add(115200);
			comboboxBaudRate.SelectedItem = Properties.Settings.Default.BaudRate;

			// Fill the data bits options and set the selected one.
			comboboxDataBits.Items.Add(7);
			comboboxDataBits.Items.Add(8);
			comboboxDataBits.SelectedItem = Properties.Settings.Default.DataBits;

			// Fill the parity options and set the selected one.
			comboboxParity.Items.Add(Parity.None);
			comboboxParity.Items.Add(Parity.Odd);
			comboboxParity.Items.Add(Parity.Even);
			comboboxParity.SelectedItem = Properties.Settings.Default.Parity;

			// Fill the stop bits options and set the selected one.
			comboboxStopBits.Items.Add(StopBits.One);
			comboboxStopBits.Items.Add(StopBits.Two);
			comboboxStopBits.SelectedItem = Properties.Settings.Default.StopBits;

			// Fill the hand shake options and set the selected one.
			comboboxFlowControl.Items.Add(Handshake.None);
			comboboxFlowControl.Items.Add(Handshake.RequestToSend);
			comboboxFlowControl.SelectedItem = Properties.Settings.Default.FlowControl;

			// Fill auto-repeat interval.
			numericUpDownAutoRepeatInterval.Value = Properties.Settings.Default.AutoRepeatInterval;

			// Fill the transaction modes.
			comboboxTransactionMode.Items.Add("Determined by terminal");
			comboboxTransactionMode.Items.Add(TlvLib.TransactionMode.Explicit);
			comboboxTransactionMode.Items.Add(TlvLib.TransactionMode.Implicit);
			comboboxTransactionMode.SelectedIndex = Properties.Settings.Default.TransactionMode + 1;

			// Fill the manager code.
			textboxManagerPassword.Text = Properties.Settings.Default.ManagerPassword;
		}


		/// <summary>
		/// Set controls depending on the selected keep-alive method radio buttons.
		/// </summary>
		private void KeepAliveMethodChanged()
		{
			if (radiobuttonKeepAliveIntervalCashregister.Checked)
			{
				numericUpDownKeepAliveInterval.Enabled = true;
			}
			else
			{
				numericUpDownKeepAliveInterval.Enabled = false;
			}
		}


		/// <summary>
		/// The changes are accepted.
		/// </summary>
		/// <param name="sender">The sender of the event.</param>
		/// <param name="e">The event arguments.</param>
		private void btnOK_Click(object sender, System.EventArgs e)
		{
			// Check the data.
			ushort listenPort;
			if (!UInt16.TryParse(textboxListenPort.Text, out listenPort))
			{
				errorProvider.SetError(textboxListenPort, Properties.Resources.ErrorMessage_UInt16);
				return;
			}


			// Store the selected connection type.
			if (comboboxConnectionType.SelectedItem != null)
			{
				Properties.Settings.Default.ConnectionType = (int)comboboxConnectionType.SelectedItem;
			}

			// Store the TCP/IP listen port in the settings object.
			Properties.Settings.Default.TcpPort = listenPort;

			// Store the com port in the settings object.
			if (comboboxComPort.SelectedItem != null)
			{
				Properties.Settings.Default.ComPort = comboboxComPort.SelectedItem as string;
			}
			else
			{
				Properties.Settings.Default.ComPort = "";
			}


			// Store the baud rate.
			if (comboboxBaudRate.SelectedItem != null)
			{
				Properties.Settings.Default.BaudRate = (int)comboboxBaudRate.SelectedItem;
			}

			// Store the data bits.
			if (comboboxDataBits.SelectedItem != null)
			{
				Properties.Settings.Default.DataBits = (int)comboboxDataBits.SelectedItem;
			}

			// Store the parity.
			if (comboboxParity.SelectedItem != null)
			{
				Properties.Settings.Default.Parity = (Parity)comboboxParity.SelectedItem;
			}

			// Store the stop bits.
			if (comboboxStopBits.SelectedItem != null)
			{
				Properties.Settings.Default.StopBits = (StopBits)comboboxStopBits.SelectedItem;
			}

			// Store the flow control.
			if (comboboxFlowControl.SelectedItem != null)
			{
				Properties.Settings.Default.FlowControl = (Handshake)comboboxFlowControl.SelectedItem;
			}
			

			// Store the keep-alive interval.
			if (radiobuttonKeepAliveIntervalTerminal.Checked)
			{
				// Terminal determined keep-alive interval stored as negative value.
				Properties.Settings.Default.KeepAliveInterval = -1;
			}
			else if (radiobuttonKeepAliveIntervalNone.Checked)
			{
				// No keep-alive interval stored as zero.
				Properties.Settings.Default.KeepAliveInterval = 0;
			}
			else
			{
				// Cash register determined keep-alive interval.
				Properties.Settings.Default.KeepAliveInterval = (short)numericUpDownKeepAliveInterval.Value;
			}


			// Store auto-repeat interval.
			Properties.Settings.Default.AutoRepeatInterval = (int)numericUpDownAutoRepeatInterval.Value;


			// Store the transaction mode.
			Properties.Settings.Default.TransactionMode = comboboxTransactionMode.SelectedIndex - 1;


			// Store manager password.
			Properties.Settings.Default.ManagerPassword = textboxManagerPassword.Text;

			// Save the settings and close the form.
			Properties.Settings.Default.Save();
			Close();
		}


		/// <summary>
		/// The input of the TCP port is incorrect.
		/// </summary>
		/// <param name="sender">The sender of the event.</param>
		/// <param name="e">The event arguments.</param>
		private void txtListenPort_MaskInputRejected(object sender, MaskInputRejectedEventArgs e)
		{
			errorProvider.SetError(textboxListenPort, e.RejectionHint.ToString());
		}


		/// <summary>
		/// The input of the TCP port is validated.
		/// </summary>
		/// <param name="sender">The sender of the event.</param>
		/// <param name="e">The event arguments.</param>
		private void txtListenPort_TypeValidationCompleted(object sender, TypeValidationEventArgs e)
		{
			// Check the value.
			if (!e.IsValidInput)
			{
				errorProvider.SetError(textboxListenPort, Properties.Resources.ErrorMessage_UInt16);
			}
			else
			{
				errorProvider.SetError(textboxListenPort, null);
			}
		}


		/// <summary>
		/// A key is pressed in the TCP port field.
		/// </summary>
		/// <param name="sender">The sender of the event.</param>
		/// <param name="e">The event arguments.</param>
		private void txtListenPort_KeyDown(object sender, KeyEventArgs e)
		{
			// Clear the error.
			errorProvider.SetError(textboxListenPort, null);
		}


		/// <summary>
		/// A keep-alive radio button was changed.
		/// </summary>
		/// <param name="sender">The sender of the event.</param>
		/// <param name="e">The event arguments.</param>
		private void rbKeepAliveInterval_CheckedChanged(object sender, EventArgs e)
		{
			KeepAliveMethodChanged();
		}
	}
}
