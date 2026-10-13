namespace ingenico.Forms
{
    partial class Form1
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.groupBoxConnection = new System.Windows.Forms.GroupBox();
            this.connectionIndicator = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.groupBoxkeepAliveInterval = new System.Windows.Forms.GroupBox();
            this.label2 = new System.Windows.Forms.Label();
            this.numericUpDownKeepAliveInterval = new System.Windows.Forms.NumericUpDown();
            this.radioButtonKeepAliveIntervalCashregister = new System.Windows.Forms.RadioButton();
            this.radioButtonKeepAliveIntervalNone = new System.Windows.Forms.RadioButton();
            this.radioButtonKeepAliveIntervalTerminal = new System.Windows.Forms.RadioButton();
            this.groupBoxSerialConnection = new System.Windows.Forms.GroupBox();
            this.labelFlowControl = new System.Windows.Forms.Label();
            this.labelStopBits = new System.Windows.Forms.Label();
            this.labelParity = new System.Windows.Forms.Label();
            this.labelDataBits = new System.Windows.Forms.Label();
            this.labelBaudRate = new System.Windows.Forms.Label();
            this.labelComPort = new System.Windows.Forms.Label();
            this.comboBoxFlowControl = new System.Windows.Forms.ComboBox();
            this.comboBoxStopBits = new System.Windows.Forms.ComboBox();
            this.comboBoxParity = new System.Windows.Forms.ComboBox();
            this.comboBoxDataBits = new System.Windows.Forms.ComboBox();
            this.comboBoxBaudrate = new System.Windows.Forms.ComboBox();
            this.comboBoxComPort = new System.Windows.Forms.ComboBox();
            this.groupBoxTcpConnection = new System.Windows.Forms.GroupBox();
            this.labelListenPort = new System.Windows.Forms.Label();
            this.textboxListenPort = new System.Windows.Forms.MaskedTextBox();
            this.comboBoxConnectionType = new System.Windows.Forms.ComboBox();
            this.groupBoxOther = new System.Windows.Forms.GroupBox();
            this.labelAutoRepeatIntervalMiliseconds = new System.Windows.Forms.Label();
            this.labelManagerpassword = new System.Windows.Forms.Label();
            this.labelTransactionMode = new System.Windows.Forms.Label();
            this.labelAutoRepeatInterval = new System.Windows.Forms.Label();
            this.textBoxmanagerPassword = new System.Windows.Forms.TextBox();
            this.numericUpDownAutoRepeatInterval = new System.Windows.Forms.NumericUpDown();
            this.comboBoxTransactionMode = new System.Windows.Forms.ComboBox();
            this.btnOK = new System.Windows.Forms.Button();
            this.btnCancel = new System.Windows.Forms.Button();
            this.listViewMessages = new System.Windows.Forms.ListView();
            this.chDateTime = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.chMessages = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.btnTestConnection = new System.Windows.Forms.Button();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.btnTransparentModeUIControl = new System.Windows.Forms.Button();
            this.btnTransparentModeAuthenticate = new System.Windows.Forms.Button();
            this.btnTransparentModeReadCard = new System.Windows.Forms.Button();
            this.btnTransparentModeStartStop = new System.Windows.Forms.Button();
            this.btnCancelTransaction = new System.Windows.Forms.Button();
            this.btnRefund = new System.Windows.Forms.Button();
            this.btnSendPayment = new System.Windows.Forms.Button();
            this.btnTerminalInfo = new System.Windows.Forms.Button();
            this.btnDisconnect = new System.Windows.Forms.Button();
            this.btnRestart = new System.Windows.Forms.Button();
            this.btnToggleLoggingHide = new System.Windows.Forms.Button();
            this.btnToggleLoggingView = new System.Windows.Forms.Button();
            this.groupBoxConnection.SuspendLayout();
            this.groupBoxkeepAliveInterval.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownKeepAliveInterval)).BeginInit();
            this.groupBoxSerialConnection.SuspendLayout();
            this.groupBoxTcpConnection.SuspendLayout();
            this.groupBoxOther.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownAutoRepeatInterval)).BeginInit();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.SuspendLayout();
            // 
            // groupBoxConnection
            // 
            this.groupBoxConnection.Controls.Add(this.connectionIndicator);
            this.groupBoxConnection.Controls.Add(this.label1);
            this.groupBoxConnection.Controls.Add(this.groupBoxkeepAliveInterval);
            this.groupBoxConnection.Controls.Add(this.groupBoxSerialConnection);
            this.groupBoxConnection.Controls.Add(this.groupBoxTcpConnection);
            this.groupBoxConnection.Controls.Add(this.comboBoxConnectionType);
            this.groupBoxConnection.Location = new System.Drawing.Point(12, 12);
            this.groupBoxConnection.Name = "groupBoxConnection";
            this.groupBoxConnection.Size = new System.Drawing.Size(377, 412);
            this.groupBoxConnection.TabIndex = 0;
            this.groupBoxConnection.TabStop = false;
            this.groupBoxConnection.Text = "Connection";
            // 
            // connectionIndicator
            // 
            this.connectionIndicator.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.connectionIndicator.ForeColor = System.Drawing.SystemColors.WindowText;
            this.connectionIndicator.Location = new System.Drawing.Point(270, 0);
            this.connectionIndicator.MaxLength = 8;
            this.connectionIndicator.Name = "connectionIndicator";
            this.connectionIndicator.Size = new System.Drawing.Size(100, 20);
            this.connectionIndicator.TabIndex = 5;
            this.connectionIndicator.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.connectionIndicator.TextChanged += new System.EventHandler(this.connectionIndicator_TextChanged);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(6, 32);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(84, 13);
            this.label1.TabIndex = 4;
            this.label1.Text = "Connection type";
            // 
            // groupBoxkeepAliveInterval
            // 
            this.groupBoxkeepAliveInterval.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.groupBoxkeepAliveInterval.Controls.Add(this.label2);
            this.groupBoxkeepAliveInterval.Controls.Add(this.numericUpDownKeepAliveInterval);
            this.groupBoxkeepAliveInterval.Controls.Add(this.radioButtonKeepAliveIntervalCashregister);
            this.groupBoxkeepAliveInterval.Controls.Add(this.radioButtonKeepAliveIntervalNone);
            this.groupBoxkeepAliveInterval.Controls.Add(this.radioButtonKeepAliveIntervalTerminal);
            this.groupBoxkeepAliveInterval.Location = new System.Drawing.Point(6, 305);
            this.groupBoxkeepAliveInterval.Name = "groupBoxkeepAliveInterval";
            this.groupBoxkeepAliveInterval.Size = new System.Drawing.Size(365, 96);
            this.groupBoxkeepAliveInterval.TabIndex = 3;
            this.groupBoxkeepAliveInterval.TabStop = false;
            this.groupBoxkeepAliveInterval.Text = "Keep-alive Interval";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(272, 69);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(47, 13);
            this.label2.TabIndex = 13;
            this.label2.Text = "seconds";
            // 
            // numericUpDownKeepAliveInterval
            // 
            this.numericUpDownKeepAliveInterval.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.numericUpDownKeepAliveInterval.Location = new System.Drawing.Point(135, 67);
            this.numericUpDownKeepAliveInterval.Maximum = new decimal(new int[] {
            3600,
            0,
            0,
            0});
            this.numericUpDownKeepAliveInterval.Name = "numericUpDownKeepAliveInterval";
            this.numericUpDownKeepAliveInterval.Size = new System.Drawing.Size(131, 20);
            this.numericUpDownKeepAliveInterval.TabIndex = 3;
            // 
            // radioButtonKeepAliveIntervalCashregister
            // 
            this.radioButtonKeepAliveIntervalCashregister.AutoSize = true;
            this.radioButtonKeepAliveIntervalCashregister.Location = new System.Drawing.Point(11, 67);
            this.radioButtonKeepAliveIntervalCashregister.Name = "radioButtonKeepAliveIntervalCashregister";
            this.radioButtonKeepAliveIntervalCashregister.Size = new System.Drawing.Size(118, 17);
            this.radioButtonKeepAliveIntervalCashregister.TabIndex = 2;
            this.radioButtonKeepAliveIntervalCashregister.TabStop = true;
            this.radioButtonKeepAliveIntervalCashregister.Text = "Set by cash register";
            this.radioButtonKeepAliveIntervalCashregister.UseVisualStyleBackColor = true;
            // 
            // radioButtonKeepAliveIntervalNone
            // 
            this.radioButtonKeepAliveIntervalNone.AutoSize = true;
            this.radioButtonKeepAliveIntervalNone.Location = new System.Drawing.Point(11, 43);
            this.radioButtonKeepAliveIntervalNone.Name = "radioButtonKeepAliveIntervalNone";
            this.radioButtonKeepAliveIntervalNone.Size = new System.Drawing.Size(96, 17);
            this.radioButtonKeepAliveIntervalNone.TabIndex = 1;
            this.radioButtonKeepAliveIntervalNone.TabStop = true;
            this.radioButtonKeepAliveIntervalNone.Text = "No keep-alives";
            this.radioButtonKeepAliveIntervalNone.UseVisualStyleBackColor = true;
            // 
            // radioButtonKeepAliveIntervalTerminal
            // 
            this.radioButtonKeepAliveIntervalTerminal.AutoSize = true;
            this.radioButtonKeepAliveIntervalTerminal.Location = new System.Drawing.Point(11, 20);
            this.radioButtonKeepAliveIntervalTerminal.Name = "radioButtonKeepAliveIntervalTerminal";
            this.radioButtonKeepAliveIntervalTerminal.Size = new System.Drawing.Size(132, 17);
            this.radioButtonKeepAliveIntervalTerminal.TabIndex = 0;
            this.radioButtonKeepAliveIntervalTerminal.TabStop = true;
            this.radioButtonKeepAliveIntervalTerminal.Text = "Determined by terminal";
            this.radioButtonKeepAliveIntervalTerminal.UseVisualStyleBackColor = true;
            // 
            // groupBoxSerialConnection
            // 
            this.groupBoxSerialConnection.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.groupBoxSerialConnection.Controls.Add(this.labelFlowControl);
            this.groupBoxSerialConnection.Controls.Add(this.labelStopBits);
            this.groupBoxSerialConnection.Controls.Add(this.labelParity);
            this.groupBoxSerialConnection.Controls.Add(this.labelDataBits);
            this.groupBoxSerialConnection.Controls.Add(this.labelBaudRate);
            this.groupBoxSerialConnection.Controls.Add(this.labelComPort);
            this.groupBoxSerialConnection.Controls.Add(this.comboBoxFlowControl);
            this.groupBoxSerialConnection.Controls.Add(this.comboBoxStopBits);
            this.groupBoxSerialConnection.Controls.Add(this.comboBoxParity);
            this.groupBoxSerialConnection.Controls.Add(this.comboBoxDataBits);
            this.groupBoxSerialConnection.Controls.Add(this.comboBoxBaudrate);
            this.groupBoxSerialConnection.Controls.Add(this.comboBoxComPort);
            this.groupBoxSerialConnection.Location = new System.Drawing.Point(6, 113);
            this.groupBoxSerialConnection.Name = "groupBoxSerialConnection";
            this.groupBoxSerialConnection.Size = new System.Drawing.Size(365, 186);
            this.groupBoxSerialConnection.TabIndex = 2;
            this.groupBoxSerialConnection.TabStop = false;
            this.groupBoxSerialConnection.Text = "Serial Connection Settings";
            // 
            // labelFlowControl
            // 
            this.labelFlowControl.AutoSize = true;
            this.labelFlowControl.Location = new System.Drawing.Point(6, 157);
            this.labelFlowControl.Name = "labelFlowControl";
            this.labelFlowControl.Size = new System.Drawing.Size(64, 13);
            this.labelFlowControl.TabIndex = 12;
            this.labelFlowControl.Text = "Flow control";
            // 
            // labelStopBits
            // 
            this.labelStopBits.AutoSize = true;
            this.labelStopBits.Location = new System.Drawing.Point(6, 130);
            this.labelStopBits.Name = "labelStopBits";
            this.labelStopBits.Size = new System.Drawing.Size(48, 13);
            this.labelStopBits.TabIndex = 11;
            this.labelStopBits.Text = "Stop bits";
            // 
            // labelParity
            // 
            this.labelParity.AutoSize = true;
            this.labelParity.Location = new System.Drawing.Point(6, 103);
            this.labelParity.Name = "labelParity";
            this.labelParity.Size = new System.Drawing.Size(33, 13);
            this.labelParity.TabIndex = 10;
            this.labelParity.Text = "Parity";
            // 
            // labelDataBits
            // 
            this.labelDataBits.AutoSize = true;
            this.labelDataBits.Location = new System.Drawing.Point(6, 76);
            this.labelDataBits.Name = "labelDataBits";
            this.labelDataBits.Size = new System.Drawing.Size(49, 13);
            this.labelDataBits.TabIndex = 9;
            this.labelDataBits.Text = "Data bits";
            // 
            // labelBaudRate
            // 
            this.labelBaudRate.AutoSize = true;
            this.labelBaudRate.Location = new System.Drawing.Point(6, 49);
            this.labelBaudRate.Name = "labelBaudRate";
            this.labelBaudRate.Size = new System.Drawing.Size(53, 13);
            this.labelBaudRate.TabIndex = 8;
            this.labelBaudRate.Text = "Baud rate";
            // 
            // labelComPort
            // 
            this.labelComPort.AutoSize = true;
            this.labelComPort.Location = new System.Drawing.Point(6, 22);
            this.labelComPort.Name = "labelComPort";
            this.labelComPort.Size = new System.Drawing.Size(49, 13);
            this.labelComPort.TabIndex = 7;
            this.labelComPort.Text = "Com port";
            // 
            // comboBoxFlowControl
            // 
            this.comboBoxFlowControl.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxFlowControl.FormattingEnabled = true;
            this.comboBoxFlowControl.Location = new System.Drawing.Point(125, 154);
            this.comboBoxFlowControl.Name = "comboBoxFlowControl";
            this.comboBoxFlowControl.Size = new System.Drawing.Size(230, 21);
            this.comboBoxFlowControl.TabIndex = 5;
            // 
            // comboBoxStopBits
            // 
            this.comboBoxStopBits.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxStopBits.FormattingEnabled = true;
            this.comboBoxStopBits.Location = new System.Drawing.Point(125, 127);
            this.comboBoxStopBits.Name = "comboBoxStopBits";
            this.comboBoxStopBits.Size = new System.Drawing.Size(230, 21);
            this.comboBoxStopBits.TabIndex = 4;
            // 
            // comboBoxParity
            // 
            this.comboBoxParity.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxParity.FormattingEnabled = true;
            this.comboBoxParity.Location = new System.Drawing.Point(125, 100);
            this.comboBoxParity.Name = "comboBoxParity";
            this.comboBoxParity.Size = new System.Drawing.Size(230, 21);
            this.comboBoxParity.TabIndex = 3;
            // 
            // comboBoxDataBits
            // 
            this.comboBoxDataBits.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxDataBits.FormattingEnabled = true;
            this.comboBoxDataBits.Location = new System.Drawing.Point(125, 73);
            this.comboBoxDataBits.Name = "comboBoxDataBits";
            this.comboBoxDataBits.Size = new System.Drawing.Size(230, 21);
            this.comboBoxDataBits.TabIndex = 2;
            // 
            // comboBoxBaudrate
            // 
            this.comboBoxBaudrate.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxBaudrate.FormattingEnabled = true;
            this.comboBoxBaudrate.Location = new System.Drawing.Point(125, 45);
            this.comboBoxBaudrate.Name = "comboBoxBaudrate";
            this.comboBoxBaudrate.Size = new System.Drawing.Size(230, 21);
            this.comboBoxBaudrate.TabIndex = 1;
            // 
            // comboBoxComPort
            // 
            this.comboBoxComPort.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxComPort.FormattingEnabled = true;
            this.comboBoxComPort.Location = new System.Drawing.Point(125, 19);
            this.comboBoxComPort.Name = "comboBoxComPort";
            this.comboBoxComPort.Size = new System.Drawing.Size(230, 21);
            this.comboBoxComPort.Sorted = true;
            this.comboBoxComPort.TabIndex = 0;
            // 
            // groupBoxTcpConnection
            // 
            this.groupBoxTcpConnection.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.groupBoxTcpConnection.Controls.Add(this.labelListenPort);
            this.groupBoxTcpConnection.Controls.Add(this.textboxListenPort);
            this.groupBoxTcpConnection.Location = new System.Drawing.Point(6, 56);
            this.groupBoxTcpConnection.Name = "groupBoxTcpConnection";
            this.groupBoxTcpConnection.Size = new System.Drawing.Size(365, 51);
            this.groupBoxTcpConnection.TabIndex = 1;
            this.groupBoxTcpConnection.TabStop = false;
            this.groupBoxTcpConnection.Text = "TCP Connection settings";
            // 
            // labelListenPort
            // 
            this.labelListenPort.AutoSize = true;
            this.labelListenPort.Location = new System.Drawing.Point(8, 22);
            this.labelListenPort.Name = "labelListenPort";
            this.labelListenPort.Size = new System.Drawing.Size(56, 13);
            this.labelListenPort.TabIndex = 6;
            this.labelListenPort.Text = "Listen port";
            // 
            // textboxListenPort
            // 
            this.textboxListenPort.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.textboxListenPort.Location = new System.Drawing.Point(125, 19);
            this.textboxListenPort.Mask = "99999";
            this.textboxListenPort.Name = "textboxListenPort";
            this.textboxListenPort.Size = new System.Drawing.Size(230, 20);
            this.textboxListenPort.TabIndex = 0;
            // 
            // comboBoxConnectionType
            // 
            this.comboBoxConnectionType.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.comboBoxConnectionType.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxConnectionType.FormattingEnabled = true;
            this.comboBoxConnectionType.Location = new System.Drawing.Point(131, 29);
            this.comboBoxConnectionType.Name = "comboBoxConnectionType";
            this.comboBoxConnectionType.Size = new System.Drawing.Size(240, 21);
            this.comboBoxConnectionType.TabIndex = 0;
            // 
            // groupBoxOther
            // 
            this.groupBoxOther.Controls.Add(this.labelAutoRepeatIntervalMiliseconds);
            this.groupBoxOther.Controls.Add(this.labelManagerpassword);
            this.groupBoxOther.Controls.Add(this.labelTransactionMode);
            this.groupBoxOther.Controls.Add(this.labelAutoRepeatInterval);
            this.groupBoxOther.Controls.Add(this.textBoxmanagerPassword);
            this.groupBoxOther.Controls.Add(this.numericUpDownAutoRepeatInterval);
            this.groupBoxOther.Controls.Add(this.comboBoxTransactionMode);
            this.groupBoxOther.Location = new System.Drawing.Point(12, 430);
            this.groupBoxOther.Name = "groupBoxOther";
            this.groupBoxOther.Size = new System.Drawing.Size(377, 106);
            this.groupBoxOther.TabIndex = 1;
            this.groupBoxOther.TabStop = false;
            this.groupBoxOther.Text = "Other";
            // 
            // labelAutoRepeatIntervalMiliseconds
            // 
            this.labelAutoRepeatIntervalMiliseconds.AutoSize = true;
            this.labelAutoRepeatIntervalMiliseconds.Location = new System.Drawing.Point(268, 21);
            this.labelAutoRepeatIntervalMiliseconds.Name = "labelAutoRepeatIntervalMiliseconds";
            this.labelAutoRepeatIntervalMiliseconds.Size = new System.Drawing.Size(61, 13);
            this.labelAutoRepeatIntervalMiliseconds.TabIndex = 14;
            this.labelAutoRepeatIntervalMiliseconds.Text = "miliseconds";
            // 
            // labelManagerpassword
            // 
            this.labelManagerpassword.AutoSize = true;
            this.labelManagerpassword.Location = new System.Drawing.Point(6, 75);
            this.labelManagerpassword.Name = "labelManagerpassword";
            this.labelManagerpassword.Size = new System.Drawing.Size(98, 13);
            this.labelManagerpassword.TabIndex = 16;
            this.labelManagerpassword.Text = "Manager Password";
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
            // labelAutoRepeatInterval
            // 
            this.labelAutoRepeatInterval.AutoSize = true;
            this.labelAutoRepeatInterval.Location = new System.Drawing.Point(6, 21);
            this.labelAutoRepeatInterval.Name = "labelAutoRepeatInterval";
            this.labelAutoRepeatInterval.Size = new System.Drawing.Size(99, 13);
            this.labelAutoRepeatInterval.TabIndex = 14;
            this.labelAutoRepeatInterval.Text = "Auto-repeat interval";
            // 
            // textBoxmanagerPassword
            // 
            this.textBoxmanagerPassword.Location = new System.Drawing.Point(131, 72);
            this.textBoxmanagerPassword.Name = "textBoxmanagerPassword";
            this.textBoxmanagerPassword.Size = new System.Drawing.Size(240, 20);
            this.textBoxmanagerPassword.TabIndex = 8;
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
            this.numericUpDownAutoRepeatInterval.TabIndex = 7;
            // 
            // comboBoxTransactionMode
            // 
            this.comboBoxTransactionMode.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxTransactionMode.FormattingEnabled = true;
            this.comboBoxTransactionMode.Location = new System.Drawing.Point(131, 45);
            this.comboBoxTransactionMode.Name = "comboBoxTransactionMode";
            this.comboBoxTransactionMode.Size = new System.Drawing.Size(240, 21);
            this.comboBoxTransactionMode.TabIndex = 6;
            // 
            // btnOK
            // 
            this.btnOK.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.btnOK.Location = new System.Drawing.Point(208, 542);
            this.btnOK.Name = "btnOK";
            this.btnOK.Size = new System.Drawing.Size(75, 23);
            this.btnOK.TabIndex = 2;
            this.btnOK.Text = "Opslaan";
            this.btnOK.UseVisualStyleBackColor = true;
            this.btnOK.Click += new System.EventHandler(this.btnOK_Click);
            // 
            // btnCancel
            // 
            this.btnCancel.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.btnCancel.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            this.btnCancel.Location = new System.Drawing.Point(289, 542);
            this.btnCancel.Name = "btnCancel";
            this.btnCancel.Size = new System.Drawing.Size(100, 23);
            this.btnCancel.TabIndex = 3;
            this.btnCancel.Text = "Reset settings";
            this.btnCancel.UseVisualStyleBackColor = true;
            this.btnCancel.Click += new System.EventHandler(this.btnCancel_Click);
            // 
            // listViewMessages
            // 
            this.listViewMessages.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.listViewMessages.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.chDateTime,
            this.chMessages});
            this.listViewMessages.HeaderStyle = System.Windows.Forms.ColumnHeaderStyle.Nonclickable;
            this.listViewMessages.HideSelection = false;
            this.listViewMessages.LabelEdit = true;
            this.listViewMessages.Location = new System.Drawing.Point(395, 18);
            this.listViewMessages.Name = "listViewMessages";
            this.listViewMessages.Size = new System.Drawing.Size(450, 406);
            this.listViewMessages.TabIndex = 4;
            this.listViewMessages.UseCompatibleStateImageBehavior = false;
            this.listViewMessages.View = System.Windows.Forms.View.Details;
            // 
            // chDateTime
            // 
            this.chDateTime.Text = "Date/Time";
            this.chDateTime.Width = 65;
            // 
            // chMessages
            // 
            this.chMessages.Text = "Messages";
            this.chMessages.Width = 1000;
            // 
            // btnTestConnection
            // 
            this.btnTestConnection.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.btnTestConnection.Location = new System.Drawing.Point(6, 15);
            this.btnTestConnection.Name = "btnTestConnection";
            this.btnTestConnection.Size = new System.Drawing.Size(100, 23);
            this.btnTestConnection.TabIndex = 5;
            this.btnTestConnection.Text = "Reconnect";
            this.btnTestConnection.UseVisualStyleBackColor = true;
            this.btnTestConnection.Click += new System.EventHandler(this.btnReconnect_Click);
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.groupBox2);
            this.groupBox1.Controls.Add(this.btnCancelTransaction);
            this.groupBox1.Controls.Add(this.btnRefund);
            this.groupBox1.Controls.Add(this.btnSendPayment);
            this.groupBox1.Controls.Add(this.btnTerminalInfo);
            this.groupBox1.Controls.Add(this.btnDisconnect);
            this.groupBox1.Controls.Add(this.btnTestConnection);
            this.groupBox1.Location = new System.Drawing.Point(395, 431);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(450, 105);
            this.groupBox1.TabIndex = 6;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Tests";
            // 
            // groupBox2
            // 
            this.groupBox2.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.groupBox2.Controls.Add(this.btnTransparentModeUIControl);
            this.groupBox2.Controls.Add(this.btnTransparentModeAuthenticate);
            this.groupBox2.Controls.Add(this.btnTransparentModeReadCard);
            this.groupBox2.Controls.Add(this.btnTransparentModeStartStop);
            this.groupBox2.Location = new System.Drawing.Point(220, 15);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(230, 90);
            this.groupBox2.TabIndex = 11;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Transparent mode";
            // 
            // btnTransparentModeUIControl
            // 
            this.btnTransparentModeUIControl.Location = new System.Drawing.Point(113, 60);
            this.btnTransparentModeUIControl.Name = "btnTransparentModeUIControl";
            this.btnTransparentModeUIControl.Size = new System.Drawing.Size(100, 23);
            this.btnTransparentModeUIControl.TabIndex = 3;
            this.btnTransparentModeUIControl.Text = "UI control";
            this.btnTransparentModeUIControl.UseVisualStyleBackColor = true;
            this.btnTransparentModeUIControl.Click += new System.EventHandler(this.btnTransparentModeUIControl_Click);
            // 
            // btnTransparentModeAuthenticate
            // 
            this.btnTransparentModeAuthenticate.Location = new System.Drawing.Point(113, 30);
            this.btnTransparentModeAuthenticate.Name = "btnTransparentModeAuthenticate";
            this.btnTransparentModeAuthenticate.Size = new System.Drawing.Size(100, 23);
            this.btnTransparentModeAuthenticate.TabIndex = 2;
            this.btnTransparentModeAuthenticate.Text = "Authenticate";
            this.btnTransparentModeAuthenticate.UseVisualStyleBackColor = true;
            this.btnTransparentModeAuthenticate.Click += new System.EventHandler(this.btnTransparentModeAuthenticate_Click);
            // 
            // btnTransparentModeReadCard
            // 
            this.btnTransparentModeReadCard.Location = new System.Drawing.Point(7, 60);
            this.btnTransparentModeReadCard.Name = "btnTransparentModeReadCard";
            this.btnTransparentModeReadCard.Size = new System.Drawing.Size(100, 23);
            this.btnTransparentModeReadCard.TabIndex = 1;
            this.btnTransparentModeReadCard.Text = "Read card data";
            this.btnTransparentModeReadCard.UseVisualStyleBackColor = true;
            this.btnTransparentModeReadCard.Click += new System.EventHandler(this.btnTransparentModeReadCard_Click);
            // 
            // btnTransparentModeStartStop
            // 
            this.btnTransparentModeStartStop.Location = new System.Drawing.Point(7, 30);
            this.btnTransparentModeStartStop.Name = "btnTransparentModeStartStop";
            this.btnTransparentModeStartStop.Size = new System.Drawing.Size(100, 23);
            this.btnTransparentModeStartStop.TabIndex = 0;
            this.btnTransparentModeStartStop.Text = "Start/Stop";
            this.btnTransparentModeStartStop.UseVisualStyleBackColor = true;
            this.btnTransparentModeStartStop.Click += new System.EventHandler(this.btnTransparentModeStartStop_Click);
            // 
            // btnCancelTransaction
            // 
            this.btnCancelTransaction.Location = new System.Drawing.Point(113, 75);
            this.btnCancelTransaction.Name = "btnCancelTransaction";
            this.btnCancelTransaction.Size = new System.Drawing.Size(100, 23);
            this.btnCancelTransaction.TabIndex = 10;
            this.btnCancelTransaction.Text = "Cancel";
            this.btnCancelTransaction.UseVisualStyleBackColor = true;
            this.btnCancelTransaction.Click += new System.EventHandler(this.btnCancelTransaction_Click);
            // 
            // btnRefund
            // 
            this.btnRefund.Location = new System.Drawing.Point(113, 45);
            this.btnRefund.Name = "btnRefund";
            this.btnRefund.Size = new System.Drawing.Size(100, 23);
            this.btnRefund.TabIndex = 9;
            this.btnRefund.Text = "Send refund";
            this.btnRefund.UseVisualStyleBackColor = true;
            this.btnRefund.Click += new System.EventHandler(this.btnRefund_Click);
            // 
            // btnSendPayment
            // 
            this.btnSendPayment.Location = new System.Drawing.Point(113, 15);
            this.btnSendPayment.Name = "btnSendPayment";
            this.btnSendPayment.Size = new System.Drawing.Size(100, 23);
            this.btnSendPayment.TabIndex = 8;
            this.btnSendPayment.Text = "Send payment";
            this.btnSendPayment.UseVisualStyleBackColor = true;
            this.btnSendPayment.Click += new System.EventHandler(this.btnSendPayment_Click);
            // 
            // btnTerminalInfo
            // 
            this.btnTerminalInfo.Location = new System.Drawing.Point(7, 75);
            this.btnTerminalInfo.Name = "btnTerminalInfo";
            this.btnTerminalInfo.Size = new System.Drawing.Size(100, 23);
            this.btnTerminalInfo.TabIndex = 7;
            this.btnTerminalInfo.Text = "Terminal info";
            this.btnTerminalInfo.UseVisualStyleBackColor = true;
            this.btnTerminalInfo.Click += new System.EventHandler(this.btnTerminalInfo_Click);
            // 
            // btnDisconnect
            // 
            this.btnDisconnect.Location = new System.Drawing.Point(6, 45);
            this.btnDisconnect.Name = "btnDisconnect";
            this.btnDisconnect.Size = new System.Drawing.Size(100, 23);
            this.btnDisconnect.TabIndex = 6;
            this.btnDisconnect.Text = "Disconnect";
            this.btnDisconnect.UseVisualStyleBackColor = true;
            this.btnDisconnect.Click += new System.EventHandler(this.btnDisconnect_Click);
            // 
            // btnRestart
            // 
            this.btnRestart.Location = new System.Drawing.Point(118, 542);
            this.btnRestart.Name = "btnRestart";
            this.btnRestart.Size = new System.Drawing.Size(75, 23);
            this.btnRestart.TabIndex = 7;
            this.btnRestart.Text = "Restart";
            this.btnRestart.UseVisualStyleBackColor = true;
            this.btnRestart.Click += new System.EventHandler(this.btnRestart_Click);
            // 
            // btnToggleLoggingHide
            // 
            this.btnToggleLoggingHide.Location = new System.Drawing.Point(12, 542);
            this.btnToggleLoggingHide.Name = "btnToggleLoggingHide";
            this.btnToggleLoggingHide.Size = new System.Drawing.Size(100, 23);
            this.btnToggleLoggingHide.TabIndex = 9;
            this.btnToggleLoggingHide.Text = "Hide logging";
            this.btnToggleLoggingHide.UseVisualStyleBackColor = true;
            this.btnToggleLoggingHide.Visible = false;
            this.btnToggleLoggingHide.Click += new System.EventHandler(this.btnToggleLoggingHide_Click);
            // 
            // btnToggleLoggingView
            // 
            this.btnToggleLoggingView.Location = new System.Drawing.Point(12, 542);
            this.btnToggleLoggingView.Name = "btnToggleLoggingView";
            this.btnToggleLoggingView.Size = new System.Drawing.Size(100, 23);
            this.btnToggleLoggingView.TabIndex = 10;
            this.btnToggleLoggingView.Text = "View Logging";
            this.btnToggleLoggingView.UseVisualStyleBackColor = true;
            this.btnToggleLoggingView.Click += new System.EventHandler(this.btnToggleLoggingView_Click);
            // 
            // Form1
            // 
            this.AcceptButton = this.btnOK;
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.CancelButton = this.btnCancel;
            this.ClientSize = new System.Drawing.Size(861, 587);
            this.Controls.Add(this.btnToggleLoggingView);
            this.Controls.Add(this.btnToggleLoggingHide);
            this.Controls.Add(this.btnRestart);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.listViewMessages);
            this.Controls.Add(this.btnCancel);
            this.Controls.Add(this.btnOK);
            this.Controls.Add(this.groupBoxOther);
            this.Controls.Add(this.groupBoxConnection);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "Form1";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Ingenico Settings";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.MainForm_FormClosing);
            this.Load += new System.EventHandler(this.Form1_Load);
            this.groupBoxConnection.ResumeLayout(false);
            this.groupBoxConnection.PerformLayout();
            this.groupBoxkeepAliveInterval.ResumeLayout(false);
            this.groupBoxkeepAliveInterval.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownKeepAliveInterval)).EndInit();
            this.groupBoxSerialConnection.ResumeLayout(false);
            this.groupBoxSerialConnection.PerformLayout();
            this.groupBoxTcpConnection.ResumeLayout(false);
            this.groupBoxTcpConnection.PerformLayout();
            this.groupBoxOther.ResumeLayout(false);
            this.groupBoxOther.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownAutoRepeatInterval)).EndInit();
            this.groupBox1.ResumeLayout(false);
            this.groupBox2.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox groupBoxConnection;
        private System.Windows.Forms.GroupBox groupBoxkeepAliveInterval;
        private System.Windows.Forms.GroupBox groupBoxSerialConnection;
        private System.Windows.Forms.GroupBox groupBoxTcpConnection;
        private System.Windows.Forms.ComboBox comboBoxConnectionType;
        private System.Windows.Forms.GroupBox groupBoxOther;
        private System.Windows.Forms.ComboBox comboBoxTransactionMode;
        private System.Windows.Forms.MaskedTextBox textboxListenPort;
        private System.Windows.Forms.NumericUpDown numericUpDownKeepAliveInterval;
        private System.Windows.Forms.RadioButton radioButtonKeepAliveIntervalCashregister;
        private System.Windows.Forms.RadioButton radioButtonKeepAliveIntervalNone;
        private System.Windows.Forms.RadioButton radioButtonKeepAliveIntervalTerminal;
        private System.Windows.Forms.ComboBox comboBoxFlowControl;
        private System.Windows.Forms.ComboBox comboBoxStopBits;
        private System.Windows.Forms.ComboBox comboBoxParity;
        private System.Windows.Forms.ComboBox comboBoxDataBits;
        private System.Windows.Forms.ComboBox comboBoxBaudrate;
        private System.Windows.Forms.ComboBox comboBoxComPort;
        private System.Windows.Forms.TextBox textBoxmanagerPassword;
        private System.Windows.Forms.NumericUpDown numericUpDownAutoRepeatInterval;
        private System.Windows.Forms.Button btnOK;
        private System.Windows.Forms.Button btnCancel;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label labelFlowControl;
        private System.Windows.Forms.Label labelStopBits;
        private System.Windows.Forms.Label labelParity;
        private System.Windows.Forms.Label labelDataBits;
        private System.Windows.Forms.Label labelBaudRate;
        private System.Windows.Forms.Label labelComPort;
        private System.Windows.Forms.Label labelListenPort;
        private System.Windows.Forms.Label labelAutoRepeatIntervalMiliseconds;
        private System.Windows.Forms.Label labelManagerpassword;
        private System.Windows.Forms.Label labelTransactionMode;
        private System.Windows.Forms.Label labelAutoRepeatInterval;
        private System.Windows.Forms.ListView listViewMessages;
        private System.Windows.Forms.Button btnTestConnection;
        private System.Windows.Forms.ColumnHeader chDateTime;
        private System.Windows.Forms.ColumnHeader chMessages;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Button btnCancelTransaction;
        private System.Windows.Forms.Button btnRefund;
        private System.Windows.Forms.Button btnSendPayment;
        private System.Windows.Forms.Button btnTerminalInfo;
        private System.Windows.Forms.Button btnDisconnect;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.Button btnTransparentModeUIControl;
        private System.Windows.Forms.Button btnTransparentModeAuthenticate;
        private System.Windows.Forms.Button btnTransparentModeReadCard;
        private System.Windows.Forms.Button btnTransparentModeStartStop;
        private System.Windows.Forms.Button btnRestart;
        private System.Windows.Forms.Button btnToggleLoggingHide;
        private System.Windows.Forms.Button btnToggleLoggingView;
        private System.Windows.Forms.TextBox connectionIndicator;
    }
}

