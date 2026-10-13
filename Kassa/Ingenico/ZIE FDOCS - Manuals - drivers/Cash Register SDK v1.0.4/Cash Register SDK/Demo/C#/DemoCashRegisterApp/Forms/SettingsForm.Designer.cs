namespace ChessPt.CashRegister.Forms
{
    partial class SettingsForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
			this.components = new System.ComponentModel.Container();
			this.labelListenPort = new System.Windows.Forms.Label();
			this.btnCancel = new System.Windows.Forms.Button();
			this.btnOK = new System.Windows.Forms.Button();
			this.textboxListenPort = new System.Windows.Forms.MaskedTextBox();
			this.errorProvider = new System.Windows.Forms.ErrorProvider(this.components);
			this.groupboxTcpConnection = new System.Windows.Forms.GroupBox();
			this.labelComPort = new System.Windows.Forms.Label();
			this.comboboxComPort = new System.Windows.Forms.ComboBox();
			this.groupboxSerialConnection = new System.Windows.Forms.GroupBox();
			this.comboboxBaudRate = new System.Windows.Forms.ComboBox();
			this.labelBaudRate = new System.Windows.Forms.Label();
			this.comboboxFlowControl = new System.Windows.Forms.ComboBox();
			this.labelFlowControl = new System.Windows.Forms.Label();
			this.comboboxStopBits = new System.Windows.Forms.ComboBox();
			this.labelStopBits = new System.Windows.Forms.Label();
			this.comboboxParity = new System.Windows.Forms.ComboBox();
			this.labelParity = new System.Windows.Forms.Label();
			this.comboboxDataBits = new System.Windows.Forms.ComboBox();
			this.labelDataBits = new System.Windows.Forms.Label();
			this.labelConnectionType = new System.Windows.Forms.Label();
			this.comboboxConnectionType = new System.Windows.Forms.ComboBox();
			this.groupboxConnection = new System.Windows.Forms.GroupBox();
			this.groupboxKeepAliveInterval = new System.Windows.Forms.GroupBox();
			this.label2 = new System.Windows.Forms.Label();
			this.radiobuttonKeepAliveIntervalCashregister = new System.Windows.Forms.RadioButton();
			this.radiobuttonKeepAliveIntervalNone = new System.Windows.Forms.RadioButton();
			this.radiobuttonKeepAliveIntervalTerminal = new System.Windows.Forms.RadioButton();
			this.numericUpDownKeepAliveInterval = new System.Windows.Forms.NumericUpDown();
			this.groupboxOther = new System.Windows.Forms.GroupBox();
			this.labelAutoRepeatInterval = new System.Windows.Forms.Label();
			this.labelAutoRepeatIntervalMiliseconds = new System.Windows.Forms.Label();
			this.numericUpDownAutoRepeatInterval = new System.Windows.Forms.NumericUpDown();
			this.labelTransactionMode = new System.Windows.Forms.Label();
			this.comboboxTransactionMode = new System.Windows.Forms.ComboBox();
			this.labelManagerpassword = new System.Windows.Forms.Label();
			this.textboxManagerPassword = new System.Windows.Forms.TextBox();
			((System.ComponentModel.ISupportInitialize)(this.errorProvider)).BeginInit();
			this.groupboxTcpConnection.SuspendLayout();
			this.groupboxSerialConnection.SuspendLayout();
			this.groupboxConnection.SuspendLayout();
			this.groupboxKeepAliveInterval.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)(this.numericUpDownKeepAliveInterval)).BeginInit();
			this.groupboxOther.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)(this.numericUpDownAutoRepeatInterval)).BeginInit();
			this.SuspendLayout();
			// 
			// labelListenPort
			// 
			this.labelListenPort.AutoSize = true;
			this.labelListenPort.Location = new System.Drawing.Point(8, 22);
			this.labelListenPort.Name = "labelListenPort";
			this.labelListenPort.Size = new System.Drawing.Size(56, 13);
			this.labelListenPort.TabIndex = 0;
			this.labelListenPort.Text = "Listen port";
			// 
			// btnCancel
			// 
			this.btnCancel.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
			this.btnCancel.DialogResult = System.Windows.Forms.DialogResult.Cancel;
			this.btnCancel.Location = new System.Drawing.Point(314, 542);
			this.btnCancel.Name = "btnCancel";
			this.btnCancel.Size = new System.Drawing.Size(75, 23);
			this.btnCancel.TabIndex = 4;
			this.btnCancel.Text = "Cancel";
			this.btnCancel.UseVisualStyleBackColor = true;
			// 
			// btnOK
			// 
			this.btnOK.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
			this.btnOK.Location = new System.Drawing.Point(233, 542);
			this.btnOK.Name = "btnOK";
			this.btnOK.Size = new System.Drawing.Size(75, 23);
			this.btnOK.TabIndex = 5;
			this.btnOK.Text = "OK";
			this.btnOK.UseVisualStyleBackColor = true;
			this.btnOK.Click += new System.EventHandler(this.btnOK_Click);
			// 
			// textboxListenPort
			// 
			this.textboxListenPort.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.textboxListenPort.BeepOnError = true;
			this.textboxListenPort.HidePromptOnLeave = true;
			this.textboxListenPort.Location = new System.Drawing.Point(125, 19);
			this.textboxListenPort.Mask = "99999";
			this.textboxListenPort.Name = "textboxListenPort";
			this.textboxListenPort.Size = new System.Drawing.Size(230, 20);
			this.textboxListenPort.TabIndex = 6;
			this.textboxListenPort.MaskInputRejected += new System.Windows.Forms.MaskInputRejectedEventHandler(this.txtListenPort_MaskInputRejected);
			this.textboxListenPort.TypeValidationCompleted += new System.Windows.Forms.TypeValidationEventHandler(this.txtListenPort_TypeValidationCompleted);
			this.textboxListenPort.KeyDown += new System.Windows.Forms.KeyEventHandler(this.txtListenPort_KeyDown);
			// 
			// errorProvider
			// 
			this.errorProvider.ContainerControl = this;
			// 
			// groupboxTcpConnection
			// 
			this.groupboxTcpConnection.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.groupboxTcpConnection.Controls.Add(this.labelListenPort);
			this.groupboxTcpConnection.Controls.Add(this.textboxListenPort);
			this.groupboxTcpConnection.Location = new System.Drawing.Point(6, 56);
			this.groupboxTcpConnection.Name = "groupboxTcpConnection";
			this.groupboxTcpConnection.Size = new System.Drawing.Size(365, 51);
			this.groupboxTcpConnection.TabIndex = 10;
			this.groupboxTcpConnection.TabStop = false;
			this.groupboxTcpConnection.Text = "TCP Connection settings";
			// 
			// labelComPort
			// 
			this.labelComPort.AutoSize = true;
			this.labelComPort.Location = new System.Drawing.Point(6, 22);
			this.labelComPort.Name = "labelComPort";
			this.labelComPort.Size = new System.Drawing.Size(49, 13);
			this.labelComPort.TabIndex = 2;
			this.labelComPort.Text = "Com port";
			// 
			// comboboxComPort
			// 
			this.comboboxComPort.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.comboboxComPort.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
			this.comboboxComPort.FormattingEnabled = true;
			this.comboboxComPort.Location = new System.Drawing.Point(125, 19);
			this.comboboxComPort.Name = "comboboxComPort";
			this.comboboxComPort.Size = new System.Drawing.Size(230, 21);
			this.comboboxComPort.TabIndex = 3;
			// 
			// groupboxSerialConnection
			// 
			this.groupboxSerialConnection.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.groupboxSerialConnection.Controls.Add(this.comboboxBaudRate);
			this.groupboxSerialConnection.Controls.Add(this.labelBaudRate);
			this.groupboxSerialConnection.Controls.Add(this.comboboxFlowControl);
			this.groupboxSerialConnection.Controls.Add(this.labelFlowControl);
			this.groupboxSerialConnection.Controls.Add(this.comboboxStopBits);
			this.groupboxSerialConnection.Controls.Add(this.labelStopBits);
			this.groupboxSerialConnection.Controls.Add(this.comboboxParity);
			this.groupboxSerialConnection.Controls.Add(this.labelParity);
			this.groupboxSerialConnection.Controls.Add(this.comboboxDataBits);
			this.groupboxSerialConnection.Controls.Add(this.labelDataBits);
			this.groupboxSerialConnection.Controls.Add(this.comboboxComPort);
			this.groupboxSerialConnection.Controls.Add(this.labelComPort);
			this.groupboxSerialConnection.Location = new System.Drawing.Point(6, 113);
			this.groupboxSerialConnection.Name = "groupboxSerialConnection";
			this.groupboxSerialConnection.Size = new System.Drawing.Size(365, 186);
			this.groupboxSerialConnection.TabIndex = 9;
			this.groupboxSerialConnection.TabStop = false;
			this.groupboxSerialConnection.Text = "Serial Connection Settings";
			// 
			// comboboxBaudRate
			// 
			this.comboboxBaudRate.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.comboboxBaudRate.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
			this.comboboxBaudRate.FormattingEnabled = true;
			this.comboboxBaudRate.Location = new System.Drawing.Point(125, 46);
			this.comboboxBaudRate.Name = "comboboxBaudRate";
			this.comboboxBaudRate.Size = new System.Drawing.Size(230, 21);
			this.comboboxBaudRate.TabIndex = 13;
			// 
			// labelBaudRate
			// 
			this.labelBaudRate.AutoSize = true;
			this.labelBaudRate.Location = new System.Drawing.Point(6, 49);
			this.labelBaudRate.Name = "labelBaudRate";
			this.labelBaudRate.Size = new System.Drawing.Size(53, 13);
			this.labelBaudRate.TabIndex = 12;
			this.labelBaudRate.Text = "Baud rate";
			// 
			// comboboxFlowControl
			// 
			this.comboboxFlowControl.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.comboboxFlowControl.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
			this.comboboxFlowControl.FormattingEnabled = true;
			this.comboboxFlowControl.Location = new System.Drawing.Point(125, 154);
			this.comboboxFlowControl.Name = "comboboxFlowControl";
			this.comboboxFlowControl.Size = new System.Drawing.Size(230, 21);
			this.comboboxFlowControl.TabIndex = 11;
			// 
			// labelFlowControl
			// 
			this.labelFlowControl.AutoSize = true;
			this.labelFlowControl.Location = new System.Drawing.Point(6, 157);
			this.labelFlowControl.Name = "labelFlowControl";
			this.labelFlowControl.Size = new System.Drawing.Size(64, 13);
			this.labelFlowControl.TabIndex = 10;
			this.labelFlowControl.Text = "Flow control";
			// 
			// comboboxStopBits
			// 
			this.comboboxStopBits.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.comboboxStopBits.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
			this.comboboxStopBits.FormattingEnabled = true;
			this.comboboxStopBits.Location = new System.Drawing.Point(125, 127);
			this.comboboxStopBits.Name = "comboboxStopBits";
			this.comboboxStopBits.Size = new System.Drawing.Size(230, 21);
			this.comboboxStopBits.TabIndex = 9;
			// 
			// labelStopBits
			// 
			this.labelStopBits.AutoSize = true;
			this.labelStopBits.Location = new System.Drawing.Point(6, 130);
			this.labelStopBits.Name = "labelStopBits";
			this.labelStopBits.Size = new System.Drawing.Size(48, 13);
			this.labelStopBits.TabIndex = 8;
			this.labelStopBits.Text = "Stop bits";
			// 
			// comboboxParity
			// 
			this.comboboxParity.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.comboboxParity.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
			this.comboboxParity.FormattingEnabled = true;
			this.comboboxParity.Location = new System.Drawing.Point(125, 100);
			this.comboboxParity.Name = "comboboxParity";
			this.comboboxParity.Size = new System.Drawing.Size(230, 21);
			this.comboboxParity.TabIndex = 7;
			// 
			// labelParity
			// 
			this.labelParity.AutoSize = true;
			this.labelParity.Location = new System.Drawing.Point(6, 103);
			this.labelParity.Name = "labelParity";
			this.labelParity.Size = new System.Drawing.Size(33, 13);
			this.labelParity.TabIndex = 6;
			this.labelParity.Text = "Parity";
			// 
			// comboboxDataBits
			// 
			this.comboboxDataBits.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.comboboxDataBits.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
			this.comboboxDataBits.FormattingEnabled = true;
			this.comboboxDataBits.Location = new System.Drawing.Point(125, 73);
			this.comboboxDataBits.Name = "comboboxDataBits";
			this.comboboxDataBits.Size = new System.Drawing.Size(230, 21);
			this.comboboxDataBits.TabIndex = 5;
			// 
			// labelDataBits
			// 
			this.labelDataBits.AutoSize = true;
			this.labelDataBits.Location = new System.Drawing.Point(6, 76);
			this.labelDataBits.Name = "labelDataBits";
			this.labelDataBits.Size = new System.Drawing.Size(49, 13);
			this.labelDataBits.TabIndex = 4;
			this.labelDataBits.Text = "Data bits";
			// 
			// labelConnectionType
			// 
			this.labelConnectionType.AutoSize = true;
			this.labelConnectionType.Location = new System.Drawing.Point(6, 32);
			this.labelConnectionType.Name = "labelConnectionType";
			this.labelConnectionType.Size = new System.Drawing.Size(84, 13);
			this.labelConnectionType.TabIndex = 11;
			this.labelConnectionType.Text = "Connection type";
			// 
			// comboboxConnectionType
			// 
			this.comboboxConnectionType.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.comboboxConnectionType.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
			this.comboboxConnectionType.FormattingEnabled = true;
			this.comboboxConnectionType.Location = new System.Drawing.Point(131, 29);
			this.comboboxConnectionType.Name = "comboboxConnectionType";
			this.comboboxConnectionType.Size = new System.Drawing.Size(240, 21);
			this.comboboxConnectionType.TabIndex = 12;
			// 
			// groupboxConnection
			// 
			this.groupboxConnection.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.groupboxConnection.Controls.Add(this.groupboxKeepAliveInterval);
			this.groupboxConnection.Controls.Add(this.comboboxConnectionType);
			this.groupboxConnection.Controls.Add(this.groupboxTcpConnection);
			this.groupboxConnection.Controls.Add(this.labelConnectionType);
			this.groupboxConnection.Controls.Add(this.groupboxSerialConnection);
			this.groupboxConnection.Location = new System.Drawing.Point(12, 12);
			this.groupboxConnection.Name = "groupboxConnection";
			this.groupboxConnection.Size = new System.Drawing.Size(377, 412);
			this.groupboxConnection.TabIndex = 13;
			this.groupboxConnection.TabStop = false;
			this.groupboxConnection.Text = "Connection";
			// 
			// groupboxKeepAliveInterval
			// 
			this.groupboxKeepAliveInterval.Controls.Add(this.label2);
			this.groupboxKeepAliveInterval.Controls.Add(this.radiobuttonKeepAliveIntervalCashregister);
			this.groupboxKeepAliveInterval.Controls.Add(this.radiobuttonKeepAliveIntervalNone);
			this.groupboxKeepAliveInterval.Controls.Add(this.radiobuttonKeepAliveIntervalTerminal);
			this.groupboxKeepAliveInterval.Controls.Add(this.numericUpDownKeepAliveInterval);
			this.groupboxKeepAliveInterval.Location = new System.Drawing.Point(6, 305);
			this.groupboxKeepAliveInterval.Name = "groupboxKeepAliveInterval";
			this.groupboxKeepAliveInterval.Size = new System.Drawing.Size(365, 96);
			this.groupboxKeepAliveInterval.TabIndex = 13;
			this.groupboxKeepAliveInterval.TabStop = false;
			this.groupboxKeepAliveInterval.Text = "Keep-alive Interval";
			// 
			// label2
			// 
			this.label2.AutoSize = true;
			this.label2.Location = new System.Drawing.Point(272, 69);
			this.label2.Name = "label2";
			this.label2.Size = new System.Drawing.Size(47, 13);
			this.label2.TabIndex = 11;
			this.label2.Text = "seconds";
			// 
			// radiobuttonKeepAliveIntervalCashregister
			// 
			this.radiobuttonKeepAliveIntervalCashregister.AutoSize = true;
			this.radiobuttonKeepAliveIntervalCashregister.Location = new System.Drawing.Point(11, 67);
			this.radiobuttonKeepAliveIntervalCashregister.Name = "radiobuttonKeepAliveIntervalCashregister";
			this.radiobuttonKeepAliveIntervalCashregister.Size = new System.Drawing.Size(118, 17);
			this.radiobuttonKeepAliveIntervalCashregister.TabIndex = 10;
			this.radiobuttonKeepAliveIntervalCashregister.TabStop = true;
			this.radiobuttonKeepAliveIntervalCashregister.Text = "Set by cash register";
			this.radiobuttonKeepAliveIntervalCashregister.UseVisualStyleBackColor = true;
			this.radiobuttonKeepAliveIntervalCashregister.CheckedChanged += new System.EventHandler(this.rbKeepAliveInterval_CheckedChanged);
			// 
			// radiobuttonKeepAliveIntervalNone
			// 
			this.radiobuttonKeepAliveIntervalNone.AutoSize = true;
			this.radiobuttonKeepAliveIntervalNone.Location = new System.Drawing.Point(11, 43);
			this.radiobuttonKeepAliveIntervalNone.Name = "radiobuttonKeepAliveIntervalNone";
			this.radiobuttonKeepAliveIntervalNone.Size = new System.Drawing.Size(96, 17);
			this.radiobuttonKeepAliveIntervalNone.TabIndex = 9;
			this.radiobuttonKeepAliveIntervalNone.TabStop = true;
			this.radiobuttonKeepAliveIntervalNone.Text = "No keep-alives";
			this.radiobuttonKeepAliveIntervalNone.UseVisualStyleBackColor = true;
			this.radiobuttonKeepAliveIntervalNone.CheckedChanged += new System.EventHandler(this.rbKeepAliveInterval_CheckedChanged);
			// 
			// radiobuttonKeepAliveIntervalTerminal
			// 
			this.radiobuttonKeepAliveIntervalTerminal.AutoSize = true;
			this.radiobuttonKeepAliveIntervalTerminal.Location = new System.Drawing.Point(11, 20);
			this.radiobuttonKeepAliveIntervalTerminal.Name = "radiobuttonKeepAliveIntervalTerminal";
			this.radiobuttonKeepAliveIntervalTerminal.Size = new System.Drawing.Size(132, 17);
			this.radiobuttonKeepAliveIntervalTerminal.TabIndex = 8;
			this.radiobuttonKeepAliveIntervalTerminal.TabStop = true;
			this.radiobuttonKeepAliveIntervalTerminal.Text = "Determined by terminal";
			this.radiobuttonKeepAliveIntervalTerminal.UseVisualStyleBackColor = true;
			this.radiobuttonKeepAliveIntervalTerminal.CheckedChanged += new System.EventHandler(this.rbKeepAliveInterval_CheckedChanged);
			// 
			// numericUpDownKeepAliveInterval
			// 
			this.numericUpDownKeepAliveInterval.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.numericUpDownKeepAliveInterval.Increment = new decimal(new int[] {
            5,
            0,
            0,
            0});
			this.numericUpDownKeepAliveInterval.Location = new System.Drawing.Point(135, 67);
			this.numericUpDownKeepAliveInterval.Maximum = new decimal(new int[] {
            3600,
            0,
            0,
            0});
			this.numericUpDownKeepAliveInterval.Name = "numericUpDownKeepAliveInterval";
			this.numericUpDownKeepAliveInterval.Size = new System.Drawing.Size(131, 20);
			this.numericUpDownKeepAliveInterval.TabIndex = 7;
			// 
			// groupboxOther
			// 
			this.groupboxOther.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.groupboxOther.Controls.Add(this.textboxManagerPassword);
			this.groupboxOther.Controls.Add(this.labelManagerpassword);
			this.groupboxOther.Controls.Add(this.comboboxTransactionMode);
			this.groupboxOther.Controls.Add(this.labelTransactionMode);
			this.groupboxOther.Controls.Add(this.labelAutoRepeatInterval);
			this.groupboxOther.Controls.Add(this.labelAutoRepeatIntervalMiliseconds);
			this.groupboxOther.Controls.Add(this.numericUpDownAutoRepeatInterval);
			this.groupboxOther.Location = new System.Drawing.Point(12, 430);
			this.groupboxOther.Name = "groupboxOther";
			this.groupboxOther.Size = new System.Drawing.Size(377, 106);
			this.groupboxOther.TabIndex = 14;
			this.groupboxOther.TabStop = false;
			this.groupboxOther.Text = "Other";
			// 
			// labelAutoRepeatInterval
			// 
			this.labelAutoRepeatInterval.AutoSize = true;
			this.labelAutoRepeatInterval.Location = new System.Drawing.Point(6, 21);
			this.labelAutoRepeatInterval.Name = "labelAutoRepeatInterval";
			this.labelAutoRepeatInterval.Size = new System.Drawing.Size(99, 13);
			this.labelAutoRepeatInterval.TabIndex = 14;
			this.labelAutoRepeatInterval.Text = "Auto-repeat interval";
			// 
			// labelAutoRepeatIntervalMiliseconds
			// 
			this.labelAutoRepeatIntervalMiliseconds.AutoSize = true;
			this.labelAutoRepeatIntervalMiliseconds.Location = new System.Drawing.Point(268, 21);
			this.labelAutoRepeatIntervalMiliseconds.Name = "labelAutoRepeatIntervalMiliseconds";
			this.labelAutoRepeatIntervalMiliseconds.Size = new System.Drawing.Size(61, 13);
			this.labelAutoRepeatIntervalMiliseconds.TabIndex = 13;
			this.labelAutoRepeatIntervalMiliseconds.Text = "miliseconds";
			// 
			// numericUpDownAutoRepeatInterval
			// 
			this.numericUpDownAutoRepeatInterval.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.numericUpDownAutoRepeatInterval.Increment = new decimal(new int[] {
            500,
            0,
            0,
            0});
			this.numericUpDownAutoRepeatInterval.Location = new System.Drawing.Point(131, 19);
			this.numericUpDownAutoRepeatInterval.Maximum = new decimal(new int[] {
            3600000,
            0,
            0,
            0});
			this.numericUpDownAutoRepeatInterval.Name = "numericUpDownAutoRepeatInterval";
			this.numericUpDownAutoRepeatInterval.Size = new System.Drawing.Size(131, 20);
			this.numericUpDownAutoRepeatInterval.TabIndex = 12;
			// 
			// labelTransactionMode
			// 
			this.labelTransactionMode.AutoSize = true;
			this.labelTransactionMode.Location = new System.Drawing.Point(6, 48);
			this.labelTransactionMode.Name = "labelTransactionMode";
			this.labelTransactionMode.Size = new System.Drawing.Size(93, 13);
			this.labelTransactionMode.TabIndex = 15;
			this.labelTransactionMode.Text = "Transaction Mode";
			// 
			// comboboxTransactionMode
			// 
			this.comboboxTransactionMode.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.comboboxTransactionMode.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
			this.comboboxTransactionMode.FormattingEnabled = true;
			this.comboboxTransactionMode.Location = new System.Drawing.Point(131, 45);
			this.comboboxTransactionMode.Name = "comboboxTransactionMode";
			this.comboboxTransactionMode.Size = new System.Drawing.Size(240, 21);
			this.comboboxTransactionMode.TabIndex = 16;
			// 
			// labelManagerpassword
			// 
			this.labelManagerpassword.AutoSize = true;
			this.labelManagerpassword.Location = new System.Drawing.Point(6, 75);
			this.labelManagerpassword.Name = "labelManagerpassword";
			this.labelManagerpassword.Size = new System.Drawing.Size(98, 13);
			this.labelManagerpassword.TabIndex = 17;
			this.labelManagerpassword.Text = "Manager Password";
			// 
			// textboxManagerPassword
			// 
			this.textboxManagerPassword.Location = new System.Drawing.Point(131, 72);
			this.textboxManagerPassword.Name = "textboxManagerPassword";
			this.textboxManagerPassword.Size = new System.Drawing.Size(240, 20);
			this.textboxManagerPassword.TabIndex = 18;
			// 
			// SettingsForm
			// 
			this.AcceptButton = this.btnOK;
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.CancelButton = this.btnCancel;
			this.ClientSize = new System.Drawing.Size(401, 577);
			this.Controls.Add(this.groupboxOther);
			this.Controls.Add(this.groupboxConnection);
			this.Controls.Add(this.btnOK);
			this.Controls.Add(this.btnCancel);
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
			this.MaximizeBox = false;
			this.MinimizeBox = false;
			this.Name = "SettingsForm";
			this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
			this.Text = "Configure settings";
			((System.ComponentModel.ISupportInitialize)(this.errorProvider)).EndInit();
			this.groupboxTcpConnection.ResumeLayout(false);
			this.groupboxTcpConnection.PerformLayout();
			this.groupboxSerialConnection.ResumeLayout(false);
			this.groupboxSerialConnection.PerformLayout();
			this.groupboxConnection.ResumeLayout(false);
			this.groupboxConnection.PerformLayout();
			this.groupboxKeepAliveInterval.ResumeLayout(false);
			this.groupboxKeepAliveInterval.PerformLayout();
			((System.ComponentModel.ISupportInitialize)(this.numericUpDownKeepAliveInterval)).EndInit();
			this.groupboxOther.ResumeLayout(false);
			this.groupboxOther.PerformLayout();
			((System.ComponentModel.ISupportInitialize)(this.numericUpDownAutoRepeatInterval)).EndInit();
			this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Label labelListenPort;
        private System.Windows.Forms.Button btnCancel;
        private System.Windows.Forms.Button btnOK;
        private System.Windows.Forms.MaskedTextBox textboxListenPort;
        private System.Windows.Forms.ErrorProvider errorProvider;
        private System.Windows.Forms.GroupBox groupboxTcpConnection;
        private System.Windows.Forms.GroupBox groupboxSerialConnection;
        private System.Windows.Forms.ComboBox comboboxComPort;
        private System.Windows.Forms.Label labelComPort;
        private System.Windows.Forms.ComboBox comboboxConnectionType;
        private System.Windows.Forms.Label labelConnectionType;
        private System.Windows.Forms.GroupBox groupboxConnection;
        private System.Windows.Forms.GroupBox groupboxKeepAliveInterval;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.RadioButton radiobuttonKeepAliveIntervalCashregister;
        private System.Windows.Forms.RadioButton radiobuttonKeepAliveIntervalNone;
        private System.Windows.Forms.RadioButton radiobuttonKeepAliveIntervalTerminal;
        private System.Windows.Forms.NumericUpDown numericUpDownKeepAliveInterval;
        private System.Windows.Forms.ComboBox comboboxBaudRate;
        private System.Windows.Forms.Label labelBaudRate;
        private System.Windows.Forms.ComboBox comboboxFlowControl;
        private System.Windows.Forms.Label labelFlowControl;
        private System.Windows.Forms.ComboBox comboboxStopBits;
        private System.Windows.Forms.Label labelStopBits;
        private System.Windows.Forms.ComboBox comboboxParity;
        private System.Windows.Forms.Label labelParity;
        private System.Windows.Forms.ComboBox comboboxDataBits;
        private System.Windows.Forms.Label labelDataBits;
		private System.Windows.Forms.GroupBox groupboxOther;
		private System.Windows.Forms.Label labelAutoRepeatInterval;
		private System.Windows.Forms.Label labelAutoRepeatIntervalMiliseconds;
		private System.Windows.Forms.NumericUpDown numericUpDownAutoRepeatInterval;
		private System.Windows.Forms.TextBox textboxManagerPassword;
		private System.Windows.Forms.Label labelManagerpassword;
		private System.Windows.Forms.ComboBox comboboxTransactionMode;
		private System.Windows.Forms.Label labelTransactionMode;
	}
}