namespace ChessPt.CashRegister.Forms
{
    partial class MainForm
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
			this.groupBox1 = new System.Windows.Forms.GroupBox();
			this.comboboxTransactionMode = new System.Windows.Forms.ComboBox();
			this.labelIntermediateResultMode = new System.Windows.Forms.Label();
			this.btnCancel = new System.Windows.Forms.Button();
			this.txtReference = new System.Windows.Forms.TextBox();
			this.label1 = new System.Windows.Forms.Label();
			this.checkboxEnableTransparentMode = new System.Windows.Forms.CheckBox();
			this.cbAutoRepeatTransaction = new System.Windows.Forms.CheckBox();
			this.cbAutoIncrementAmount = new System.Windows.Forms.CheckBox();
			this.lblTransactionType = new System.Windows.Forms.Label();
			this.cbTransactionType = new System.Windows.Forms.ComboBox();
			this.txtAmount = new System.Windows.Forms.TextBox();
			this.tableLayoutPanel1 = new System.Windows.Forms.TableLayoutPanel();
			this.btnOK = new System.Windows.Forms.Button();
			this.btnZero = new System.Windows.Forms.Button();
			this.btnCorrection = new System.Windows.Forms.Button();
			this.btnNine = new System.Windows.Forms.Button();
			this.btnEight = new System.Windows.Forms.Button();
			this.btnSeven = new System.Windows.Forms.Button();
			this.btnSix = new System.Windows.Forms.Button();
			this.btnFive = new System.Windows.Forms.Button();
			this.btnFour = new System.Windows.Forms.Button();
			this.btnThree = new System.Windows.Forms.Button();
			this.btnTwo = new System.Windows.Forms.Button();
			this.bntOne = new System.Windows.Forms.Button();
			this.statusStrip = new System.Windows.Forms.StatusStrip();
			this.lblStatus = new System.Windows.Forms.ToolStripStatusLabel();
			this.lblStatus_KeepAlive = new System.Windows.Forms.ToolStripStatusLabel();
			this.lblStatus_StatusUpdates = new System.Windows.Forms.ToolStripStatusLabel();
			this.groupBox2 = new System.Windows.Forms.GroupBox();
			this.tableLayoutPanel2 = new System.Windows.Forms.TableLayoutPanel();
			this.lblCardHolderTicket = new System.Windows.Forms.Label();
			this.txtJournalTicket = new System.Windows.Forms.TextBox();
			this.lblJournalTicket = new System.Windows.Forms.Label();
			this.txtMerchantTicket = new System.Windows.Forms.TextBox();
			this.lblMerchantTicket = new System.Windows.Forms.Label();
			this.txtCardholderTicket = new System.Windows.Forms.TextBox();
			this.listViewMessages = new System.Windows.Forms.ListView();
			this.chDateTime = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
			this.chMessages = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
			this.contextMenuMessages = new System.Windows.Forms.ContextMenuStrip(this.components);
			this.cmMessagesClear = new System.Windows.Forms.ToolStripMenuItem();
			this.btnDeleteOpenMessages = new System.Windows.Forms.Button();
			this.btnSendOpenMessages = new System.Windows.Forms.Button();
			this.btnTmsSession = new System.Windows.Forms.Button();
			this.btnParameterDownload = new System.Windows.Forms.Button();
			this.btnKeyLoad = new System.Windows.Forms.Button();
			this.btnDisconnect = new System.Windows.Forms.Button();
			this.gbAcquirerMessages = new System.Windows.Forms.GroupBox();
			this.gbTotals = new System.Windows.Forms.GroupBox();
			this.btnClosePeriodTotals = new System.Windows.Forms.Button();
			this.btnCurrentPreviousPeriodTotals = new System.Windows.Forms.Button();
			this.btnPreviousPeriodTotals = new System.Windows.Forms.Button();
			this.btnCurrentPeriodTotals = new System.Windows.Forms.Button();
			this.btnZTotals = new System.Windows.Forms.Button();
			this.btnXTotals = new System.Windows.Forms.Button();
			this.gbOther = new System.Windows.Forms.GroupBox();
			this.btnCtapInfo = new System.Windows.Forms.Button();
			this.btnCardBrandInfo = new System.Windows.Forms.Button();
			this.btnTerminalInformation = new System.Windows.Forms.Button();
			this.btnReconnect = new System.Windows.Forms.Button();
			this.btnLastTransactionTicket = new System.Windows.Forms.Button();
			this.btnClearCtapDatabase = new System.Windows.Forms.Button();
			this.btnLastTransactionStatus = new System.Windows.Forms.Button();
			this.menuStrip = new System.Windows.Forms.MenuStrip();
			this.menuSettings = new System.Windows.Forms.ToolStripMenuItem();
			this.menuSettings_Configure = new System.Windows.Forms.ToolStripMenuItem();
			this.menuSettings_TransparentMode = new System.Windows.Forms.ToolStripMenuItem();
			this.menuProduceErrors = new System.Windows.Forms.ToolStripMenuItem();
			this.menuProduceErrors_SendInvalid3F00 = new System.Windows.Forms.ToolStripMenuItem();
			this.menuProduceErrors_SendPrimitiveAsGroup1F7F = new System.Windows.Forms.ToolStripMenuItem();
			this.menuProduceErrors_SendGroupAsPrimitiveA6 = new System.Windows.Forms.ToolStripMenuItem();
			this.menuProduceErrors_SendOptionalTagWithWorngLength53 = new System.Windows.Forms.ToolStripMenuItem();
			this.menuProduceErrors_SendRequiredTagWithWorngLength50 = new System.Windows.Forms.ToolStripMenuItem();
			this.menuProduceErrors_SkipMandatoryTag50 = new System.Windows.Forms.ToolStripMenuItem();
			this.menuHelp = new System.Windows.Forms.ToolStripMenuItem();
			this.menuHelp_About = new System.Windows.Forms.ToolStripMenuItem();
			this.gbTransparentMode = new System.Windows.Forms.GroupBox();
			this.buttonTmAuthenticate = new System.Windows.Forms.Button();
			this.buttonTmReadCardData = new System.Windows.Forms.Button();
			this.buttonTmUiControl = new System.Windows.Forms.Button();
			this.buttonTmStartStopTransparentMode = new System.Windows.Forms.Button();
			this.lblMerchantMessage = new System.Windows.Forms.Label();
			this.groupBox1.SuspendLayout();
			this.tableLayoutPanel1.SuspendLayout();
			this.statusStrip.SuspendLayout();
			this.groupBox2.SuspendLayout();
			this.tableLayoutPanel2.SuspendLayout();
			this.contextMenuMessages.SuspendLayout();
			this.gbAcquirerMessages.SuspendLayout();
			this.gbTotals.SuspendLayout();
			this.gbOther.SuspendLayout();
			this.menuStrip.SuspendLayout();
			this.gbTransparentMode.SuspendLayout();
			this.SuspendLayout();
			// 
			// groupBox1
			// 
			this.groupBox1.Controls.Add(this.comboboxTransactionMode);
			this.groupBox1.Controls.Add(this.labelIntermediateResultMode);
			this.groupBox1.Controls.Add(this.btnCancel);
			this.groupBox1.Controls.Add(this.txtReference);
			this.groupBox1.Controls.Add(this.label1);
			this.groupBox1.Controls.Add(this.checkboxEnableTransparentMode);
			this.groupBox1.Controls.Add(this.cbAutoRepeatTransaction);
			this.groupBox1.Controls.Add(this.cbAutoIncrementAmount);
			this.groupBox1.Controls.Add(this.lblTransactionType);
			this.groupBox1.Controls.Add(this.cbTransactionType);
			this.groupBox1.Controls.Add(this.txtAmount);
			this.groupBox1.Controls.Add(this.tableLayoutPanel1);
			this.groupBox1.Location = new System.Drawing.Point(12, 27);
			this.groupBox1.Name = "groupBox1";
			this.groupBox1.Size = new System.Drawing.Size(205, 520);
			this.groupBox1.TabIndex = 0;
			this.groupBox1.TabStop = false;
			// 
			// comboboxTransactionMode
			// 
			this.comboboxTransactionMode.FormattingEnabled = true;
			this.comboboxTransactionMode.Location = new System.Drawing.Point(69, 411);
			this.comboboxTransactionMode.Name = "comboboxTransactionMode";
			this.comboboxTransactionMode.Size = new System.Drawing.Size(130, 21);
			this.comboboxTransactionMode.TabIndex = 13;
			// 
			// labelIntermediateResultMode
			// 
			this.labelIntermediateResultMode.AutoSize = true;
			this.labelIntermediateResultMode.Location = new System.Drawing.Point(6, 415);
			this.labelIntermediateResultMode.Name = "labelIntermediateResultMode";
			this.labelIntermediateResultMode.Size = new System.Drawing.Size(65, 13);
			this.labelIntermediateResultMode.TabIndex = 12;
			this.labelIntermediateResultMode.Text = "Intermediate";
			// 
			// btnCancel
			// 
			this.btnCancel.Font = new System.Drawing.Font("Arial Narrow", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.btnCancel.Location = new System.Drawing.Point(6, 322);
			this.btnCancel.Name = "btnCancel";
			this.btnCancel.Size = new System.Drawing.Size(193, 30);
			this.btnCancel.TabIndex = 11;
			this.btnCancel.Text = "Cancel";
			this.btnCancel.UseVisualStyleBackColor = true;
			this.btnCancel.Click += new System.EventHandler(this.btnCancel_Click);
			// 
			// txtReference
			// 
			this.txtReference.Location = new System.Drawing.Point(69, 385);
			this.txtReference.Name = "txtReference";
			this.txtReference.Size = new System.Drawing.Size(130, 20);
			this.txtReference.TabIndex = 9;
			// 
			// label1
			// 
			this.label1.AutoSize = true;
			this.label1.Location = new System.Drawing.Point(6, 388);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(57, 13);
			this.label1.TabIndex = 8;
			this.label1.Text = "Reference";
			// 
			// checkboxEnableTransparentMode
			// 
			this.checkboxEnableTransparentMode.AutoSize = true;
			this.checkboxEnableTransparentMode.Location = new System.Drawing.Point(9, 489);
			this.checkboxEnableTransparentMode.Name = "checkboxEnableTransparentMode";
			this.checkboxEnableTransparentMode.Size = new System.Drawing.Size(144, 17);
			this.checkboxEnableTransparentMode.TabIndex = 7;
			this.checkboxEnableTransparentMode.Text = "Enable transparent mode";
			this.checkboxEnableTransparentMode.UseVisualStyleBackColor = true;
			// 
			// cbAutoRepeatTransaction
			// 
			this.cbAutoRepeatTransaction.AutoSize = true;
			this.cbAutoRepeatTransaction.Location = new System.Drawing.Point(9, 466);
			this.cbAutoRepeatTransaction.Name = "cbAutoRepeatTransaction";
			this.cbAutoRepeatTransaction.Size = new System.Drawing.Size(136, 17);
			this.cbAutoRepeatTransaction.TabIndex = 5;
			this.cbAutoRepeatTransaction.Text = "Auto repeat transaction";
			this.cbAutoRepeatTransaction.UseVisualStyleBackColor = true;
			// 
			// cbAutoIncrementAmount
			// 
			this.cbAutoIncrementAmount.AutoSize = true;
			this.cbAutoIncrementAmount.Location = new System.Drawing.Point(9, 443);
			this.cbAutoIncrementAmount.Name = "cbAutoIncrementAmount";
			this.cbAutoIncrementAmount.Size = new System.Drawing.Size(135, 17);
			this.cbAutoIncrementAmount.TabIndex = 4;
			this.cbAutoIncrementAmount.Text = "Auto increment amount";
			this.cbAutoIncrementAmount.UseVisualStyleBackColor = true;
			// 
			// lblTransactionType
			// 
			this.lblTransactionType.AutoSize = true;
			this.lblTransactionType.Location = new System.Drawing.Point(6, 361);
			this.lblTransactionType.Name = "lblTransactionType";
			this.lblTransactionType.Size = new System.Drawing.Size(31, 13);
			this.lblTransactionType.TabIndex = 3;
			this.lblTransactionType.Text = "Type";
			// 
			// cbTransactionType
			// 
			this.cbTransactionType.FormattingEnabled = true;
			this.cbTransactionType.Location = new System.Drawing.Point(69, 358);
			this.cbTransactionType.Name = "cbTransactionType";
			this.cbTransactionType.Size = new System.Drawing.Size(130, 21);
			this.cbTransactionType.TabIndex = 2;
			// 
			// txtAmount
			// 
			this.txtAmount.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.txtAmount.Font = new System.Drawing.Font("Microsoft Sans Serif", 18F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.txtAmount.Location = new System.Drawing.Point(9, 19);
			this.txtAmount.Name = "txtAmount";
			this.txtAmount.ReadOnly = true;
			this.txtAmount.Size = new System.Drawing.Size(187, 35);
			this.txtAmount.TabIndex = 1;
			this.txtAmount.Text = "€ 0.00";
			this.txtAmount.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
			// 
			// tableLayoutPanel1
			// 
			this.tableLayoutPanel1.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.tableLayoutPanel1.ColumnCount = 3;
			this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 33.33333F));
			this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 33.33333F));
			this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 33.33333F));
			this.tableLayoutPanel1.Controls.Add(this.btnOK, 2, 3);
			this.tableLayoutPanel1.Controls.Add(this.btnZero, 1, 3);
			this.tableLayoutPanel1.Controls.Add(this.btnCorrection, 0, 3);
			this.tableLayoutPanel1.Controls.Add(this.btnNine, 2, 2);
			this.tableLayoutPanel1.Controls.Add(this.btnEight, 1, 2);
			this.tableLayoutPanel1.Controls.Add(this.btnSeven, 0, 2);
			this.tableLayoutPanel1.Controls.Add(this.btnSix, 2, 1);
			this.tableLayoutPanel1.Controls.Add(this.btnFive, 1, 1);
			this.tableLayoutPanel1.Controls.Add(this.btnFour, 0, 1);
			this.tableLayoutPanel1.Controls.Add(this.btnThree, 2, 0);
			this.tableLayoutPanel1.Controls.Add(this.btnTwo, 1, 0);
			this.tableLayoutPanel1.Controls.Add(this.bntOne, 0, 0);
			this.tableLayoutPanel1.Location = new System.Drawing.Point(6, 60);
			this.tableLayoutPanel1.Name = "tableLayoutPanel1";
			this.tableLayoutPanel1.RowCount = 4;
			this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 25F));
			this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 25F));
			this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 25F));
			this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 25F));
			this.tableLayoutPanel1.Size = new System.Drawing.Size(193, 256);
			this.tableLayoutPanel1.TabIndex = 0;
			// 
			// btnOK
			// 
			this.btnOK.Dock = System.Windows.Forms.DockStyle.Fill;
			this.btnOK.Font = new System.Drawing.Font("Arial Narrow", 18F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.btnOK.Location = new System.Drawing.Point(131, 195);
			this.btnOK.Name = "btnOK";
			this.btnOK.Size = new System.Drawing.Size(59, 58);
			this.btnOK.TabIndex = 11;
			this.btnOK.Text = "OK";
			this.btnOK.UseVisualStyleBackColor = true;
			this.btnOK.Click += new System.EventHandler(this.btnOK_Click);
			// 
			// btnZero
			// 
			this.btnZero.Dock = System.Windows.Forms.DockStyle.Fill;
			this.btnZero.Font = new System.Drawing.Font("Arial Narrow", 18F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.btnZero.Location = new System.Drawing.Point(67, 195);
			this.btnZero.Name = "btnZero";
			this.btnZero.Size = new System.Drawing.Size(58, 58);
			this.btnZero.TabIndex = 10;
			this.btnZero.Text = "0";
			this.btnZero.UseVisualStyleBackColor = true;
			this.btnZero.Click += new System.EventHandler(this.NumericButtonClick);
			// 
			// btnCorrection
			// 
			this.btnCorrection.Dock = System.Windows.Forms.DockStyle.Fill;
			this.btnCorrection.Font = new System.Drawing.Font("Arial Narrow", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.btnCorrection.Location = new System.Drawing.Point(3, 195);
			this.btnCorrection.Name = "btnCorrection";
			this.btnCorrection.Size = new System.Drawing.Size(58, 58);
			this.btnCorrection.TabIndex = 9;
			this.btnCorrection.Text = "CORR";
			this.btnCorrection.UseVisualStyleBackColor = true;
			this.btnCorrection.Click += new System.EventHandler(this.btnCorrection_Click);
			// 
			// btnNine
			// 
			this.btnNine.Dock = System.Windows.Forms.DockStyle.Fill;
			this.btnNine.Font = new System.Drawing.Font("Arial Narrow", 18F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.btnNine.Location = new System.Drawing.Point(131, 131);
			this.btnNine.Name = "btnNine";
			this.btnNine.Size = new System.Drawing.Size(59, 58);
			this.btnNine.TabIndex = 8;
			this.btnNine.Text = "9";
			this.btnNine.UseVisualStyleBackColor = true;
			this.btnNine.Click += new System.EventHandler(this.NumericButtonClick);
			// 
			// btnEight
			// 
			this.btnEight.Dock = System.Windows.Forms.DockStyle.Fill;
			this.btnEight.Font = new System.Drawing.Font("Arial Narrow", 18F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.btnEight.Location = new System.Drawing.Point(67, 131);
			this.btnEight.Name = "btnEight";
			this.btnEight.Size = new System.Drawing.Size(58, 58);
			this.btnEight.TabIndex = 7;
			this.btnEight.Text = "8";
			this.btnEight.UseVisualStyleBackColor = true;
			this.btnEight.Click += new System.EventHandler(this.NumericButtonClick);
			// 
			// btnSeven
			// 
			this.btnSeven.Dock = System.Windows.Forms.DockStyle.Fill;
			this.btnSeven.Font = new System.Drawing.Font("Arial Narrow", 18F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.btnSeven.Location = new System.Drawing.Point(3, 131);
			this.btnSeven.Name = "btnSeven";
			this.btnSeven.Size = new System.Drawing.Size(58, 58);
			this.btnSeven.TabIndex = 6;
			this.btnSeven.Text = "7";
			this.btnSeven.UseVisualStyleBackColor = true;
			this.btnSeven.Click += new System.EventHandler(this.NumericButtonClick);
			// 
			// btnSix
			// 
			this.btnSix.Dock = System.Windows.Forms.DockStyle.Fill;
			this.btnSix.Font = new System.Drawing.Font("Arial Narrow", 18F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.btnSix.Location = new System.Drawing.Point(131, 67);
			this.btnSix.Name = "btnSix";
			this.btnSix.Size = new System.Drawing.Size(59, 58);
			this.btnSix.TabIndex = 5;
			this.btnSix.Text = "6";
			this.btnSix.UseVisualStyleBackColor = true;
			this.btnSix.Click += new System.EventHandler(this.NumericButtonClick);
			// 
			// btnFive
			// 
			this.btnFive.Dock = System.Windows.Forms.DockStyle.Fill;
			this.btnFive.Font = new System.Drawing.Font("Arial Narrow", 18F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.btnFive.Location = new System.Drawing.Point(67, 67);
			this.btnFive.Name = "btnFive";
			this.btnFive.Size = new System.Drawing.Size(58, 58);
			this.btnFive.TabIndex = 4;
			this.btnFive.Text = "5";
			this.btnFive.UseVisualStyleBackColor = true;
			this.btnFive.Click += new System.EventHandler(this.NumericButtonClick);
			// 
			// btnFour
			// 
			this.btnFour.Dock = System.Windows.Forms.DockStyle.Fill;
			this.btnFour.Font = new System.Drawing.Font("Arial Narrow", 18F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.btnFour.Location = new System.Drawing.Point(3, 67);
			this.btnFour.Name = "btnFour";
			this.btnFour.Size = new System.Drawing.Size(58, 58);
			this.btnFour.TabIndex = 3;
			this.btnFour.Text = "4";
			this.btnFour.UseVisualStyleBackColor = true;
			this.btnFour.Click += new System.EventHandler(this.NumericButtonClick);
			// 
			// btnThree
			// 
			this.btnThree.Dock = System.Windows.Forms.DockStyle.Fill;
			this.btnThree.Font = new System.Drawing.Font("Arial Narrow", 18F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.btnThree.Location = new System.Drawing.Point(131, 3);
			this.btnThree.Name = "btnThree";
			this.btnThree.Size = new System.Drawing.Size(59, 58);
			this.btnThree.TabIndex = 2;
			this.btnThree.Text = "3";
			this.btnThree.UseVisualStyleBackColor = true;
			this.btnThree.Click += new System.EventHandler(this.NumericButtonClick);
			// 
			// btnTwo
			// 
			this.btnTwo.Dock = System.Windows.Forms.DockStyle.Fill;
			this.btnTwo.Font = new System.Drawing.Font("Arial Narrow", 18F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.btnTwo.Location = new System.Drawing.Point(67, 3);
			this.btnTwo.Name = "btnTwo";
			this.btnTwo.Size = new System.Drawing.Size(58, 58);
			this.btnTwo.TabIndex = 1;
			this.btnTwo.Text = "2";
			this.btnTwo.UseVisualStyleBackColor = true;
			this.btnTwo.Click += new System.EventHandler(this.NumericButtonClick);
			// 
			// bntOne
			// 
			this.bntOne.Dock = System.Windows.Forms.DockStyle.Fill;
			this.bntOne.Font = new System.Drawing.Font("Arial Narrow", 18F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.bntOne.Location = new System.Drawing.Point(3, 3);
			this.bntOne.Name = "bntOne";
			this.bntOne.Size = new System.Drawing.Size(58, 58);
			this.bntOne.TabIndex = 0;
			this.bntOne.Text = "1";
			this.bntOne.UseVisualStyleBackColor = true;
			this.bntOne.Click += new System.EventHandler(this.NumericButtonClick);
			// 
			// statusStrip
			// 
			this.statusStrip.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.lblStatus,
            this.lblStatus_KeepAlive,
            this.lblStatus_StatusUpdates});
			this.statusStrip.Location = new System.Drawing.Point(0, 764);
			this.statusStrip.Name = "statusStrip";
			this.statusStrip.Size = new System.Drawing.Size(1176, 24);
			this.statusStrip.TabIndex = 2;
			this.statusStrip.Text = "statusStrip1";
			// 
			// lblStatus
			// 
			this.lblStatus.Name = "lblStatus";
			this.lblStatus.Size = new System.Drawing.Size(1007, 19);
			this.lblStatus.Spring = true;
			this.lblStatus.Text = "Status label";
			this.lblStatus.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
			// 
			// lblStatus_KeepAlive
			// 
			this.lblStatus_KeepAlive.BorderSides = ((System.Windows.Forms.ToolStripStatusLabelBorderSides)((((System.Windows.Forms.ToolStripStatusLabelBorderSides.Left | System.Windows.Forms.ToolStripStatusLabelBorderSides.Top) 
            | System.Windows.Forms.ToolStripStatusLabelBorderSides.Right) 
            | System.Windows.Forms.ToolStripStatusLabelBorderSides.Bottom)));
			this.lblStatus_KeepAlive.BorderStyle = System.Windows.Forms.Border3DStyle.SunkenInner;
			this.lblStatus_KeepAlive.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text;
			this.lblStatus_KeepAlive.Name = "lblStatus_KeepAlive";
			this.lblStatus_KeepAlive.Size = new System.Drawing.Size(66, 19);
			this.lblStatus_KeepAlive.Text = "Keep-alive";
			// 
			// lblStatus_StatusUpdates
			// 
			this.lblStatus_StatusUpdates.BorderSides = ((System.Windows.Forms.ToolStripStatusLabelBorderSides)((((System.Windows.Forms.ToolStripStatusLabelBorderSides.Left | System.Windows.Forms.ToolStripStatusLabelBorderSides.Top) 
            | System.Windows.Forms.ToolStripStatusLabelBorderSides.Right) 
            | System.Windows.Forms.ToolStripStatusLabelBorderSides.Bottom)));
			this.lblStatus_StatusUpdates.BorderStyle = System.Windows.Forms.Border3DStyle.SunkenInner;
			this.lblStatus_StatusUpdates.Name = "lblStatus_StatusUpdates";
			this.lblStatus_StatusUpdates.Size = new System.Drawing.Size(88, 19);
			this.lblStatus_StatusUpdates.Text = "Status updates";
			// 
			// groupBox2
			// 
			this.groupBox2.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.groupBox2.Controls.Add(this.tableLayoutPanel2);
			this.groupBox2.Location = new System.Drawing.Point(223, 27);
			this.groupBox2.Name = "groupBox2";
			this.groupBox2.Size = new System.Drawing.Size(637, 520);
			this.groupBox2.TabIndex = 3;
			this.groupBox2.TabStop = false;
			// 
			// tableLayoutPanel2
			// 
			this.tableLayoutPanel2.ColumnCount = 3;
			this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 33.33333F));
			this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 33.33334F));
			this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 33.33334F));
			this.tableLayoutPanel2.Controls.Add(this.lblCardHolderTicket, 0, 0);
			this.tableLayoutPanel2.Controls.Add(this.txtJournalTicket, 2, 1);
			this.tableLayoutPanel2.Controls.Add(this.lblJournalTicket, 2, 0);
			this.tableLayoutPanel2.Controls.Add(this.txtMerchantTicket, 1, 1);
			this.tableLayoutPanel2.Controls.Add(this.lblMerchantTicket, 1, 0);
			this.tableLayoutPanel2.Controls.Add(this.txtCardholderTicket, 0, 1);
			this.tableLayoutPanel2.Dock = System.Windows.Forms.DockStyle.Fill;
			this.tableLayoutPanel2.Location = new System.Drawing.Point(3, 16);
			this.tableLayoutPanel2.Name = "tableLayoutPanel2";
			this.tableLayoutPanel2.RowCount = 2;
			this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle());
			this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 100F));
			this.tableLayoutPanel2.Size = new System.Drawing.Size(631, 501);
			this.tableLayoutPanel2.TabIndex = 18;
			// 
			// lblCardHolderTicket
			// 
			this.lblCardHolderTicket.Dock = System.Windows.Forms.DockStyle.Top;
			this.lblCardHolderTicket.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblCardHolderTicket.Location = new System.Drawing.Point(3, 0);
			this.lblCardHolderTicket.Name = "lblCardHolderTicket";
			this.lblCardHolderTicket.Size = new System.Drawing.Size(204, 16);
			this.lblCardHolderTicket.TabIndex = 13;
			this.lblCardHolderTicket.Text = "Card  holder ticket";
			// 
			// txtJournalTicket
			// 
			this.txtJournalTicket.Dock = System.Windows.Forms.DockStyle.Fill;
			this.txtJournalTicket.Font = new System.Drawing.Font("Courier New", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.txtJournalTicket.Location = new System.Drawing.Point(423, 19);
			this.txtJournalTicket.Multiline = true;
			this.txtJournalTicket.Name = "txtJournalTicket";
			this.txtJournalTicket.ScrollBars = System.Windows.Forms.ScrollBars.Both;
			this.txtJournalTicket.Size = new System.Drawing.Size(205, 479);
			this.txtJournalTicket.TabIndex = 16;
			this.txtJournalTicket.WordWrap = false;
			// 
			// lblJournalTicket
			// 
			this.lblJournalTicket.Dock = System.Windows.Forms.DockStyle.Top;
			this.lblJournalTicket.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblJournalTicket.Location = new System.Drawing.Point(423, 0);
			this.lblJournalTicket.Name = "lblJournalTicket";
			this.lblJournalTicket.Size = new System.Drawing.Size(205, 16);
			this.lblJournalTicket.TabIndex = 17;
			this.lblJournalTicket.Text = "Journal/totals ticket";
			// 
			// txtMerchantTicket
			// 
			this.txtMerchantTicket.Dock = System.Windows.Forms.DockStyle.Fill;
			this.txtMerchantTicket.Font = new System.Drawing.Font("Courier New", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.txtMerchantTicket.Location = new System.Drawing.Point(213, 19);
			this.txtMerchantTicket.Multiline = true;
			this.txtMerchantTicket.Name = "txtMerchantTicket";
			this.txtMerchantTicket.ScrollBars = System.Windows.Forms.ScrollBars.Both;
			this.txtMerchantTicket.Size = new System.Drawing.Size(204, 479);
			this.txtMerchantTicket.TabIndex = 14;
			this.txtMerchantTicket.WordWrap = false;
			// 
			// lblMerchantTicket
			// 
			this.lblMerchantTicket.Dock = System.Windows.Forms.DockStyle.Top;
			this.lblMerchantTicket.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblMerchantTicket.Location = new System.Drawing.Point(213, 0);
			this.lblMerchantTicket.Name = "lblMerchantTicket";
			this.lblMerchantTicket.Size = new System.Drawing.Size(204, 16);
			this.lblMerchantTicket.TabIndex = 15;
			this.lblMerchantTicket.Text = "Merchant ticket";
			// 
			// txtCardholderTicket
			// 
			this.txtCardholderTicket.Dock = System.Windows.Forms.DockStyle.Fill;
			this.txtCardholderTicket.Font = new System.Drawing.Font("Courier New", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.txtCardholderTicket.Location = new System.Drawing.Point(3, 19);
			this.txtCardholderTicket.Multiline = true;
			this.txtCardholderTicket.Name = "txtCardholderTicket";
			this.txtCardholderTicket.ScrollBars = System.Windows.Forms.ScrollBars.Both;
			this.txtCardholderTicket.Size = new System.Drawing.Size(204, 479);
			this.txtCardholderTicket.TabIndex = 12;
			this.txtCardholderTicket.WordWrap = false;
			// 
			// listViewMessages
			// 
			this.listViewMessages.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.listViewMessages.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.chDateTime,
            this.chMessages});
			this.listViewMessages.ContextMenuStrip = this.contextMenuMessages;
			this.listViewMessages.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.listViewMessages.FullRowSelect = true;
			this.listViewMessages.HeaderStyle = System.Windows.Forms.ColumnHeaderStyle.Nonclickable;
			this.listViewMessages.Location = new System.Drawing.Point(12, 633);
			this.listViewMessages.Name = "listViewMessages";
			this.listViewMessages.Size = new System.Drawing.Size(1152, 130);
			this.listViewMessages.TabIndex = 3;
			this.listViewMessages.UseCompatibleStateImageBehavior = false;
			this.listViewMessages.View = System.Windows.Forms.View.Details;
			this.listViewMessages.SizeChanged += new System.EventHandler(this.listView_SizeChanged);
			// 
			// chDateTime
			// 
			this.chDateTime.Text = "Date/Time";
			this.chDateTime.Width = 129;
			// 
			// chMessages
			// 
			this.chMessages.Text = "Messages";
			this.chMessages.Width = 492;
			// 
			// contextMenuMessages
			// 
			this.contextMenuMessages.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.cmMessagesClear});
			this.contextMenuMessages.Name = "contextMenuMessages";
			this.contextMenuMessages.Size = new System.Drawing.Size(156, 26);
			// 
			// cmMessagesClear
			// 
			this.cmMessagesClear.Name = "cmMessagesClear";
			this.cmMessagesClear.Size = new System.Drawing.Size(155, 22);
			this.cmMessagesClear.Text = "Clear messages";
			this.cmMessagesClear.Click += new System.EventHandler(this.cmMessagesClear_Click);
			// 
			// btnDeleteOpenMessages
			// 
			this.btnDeleteOpenMessages.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.btnDeleteOpenMessages.Location = new System.Drawing.Point(6, 106);
			this.btnDeleteOpenMessages.Name = "btnDeleteOpenMessages";
			this.btnDeleteOpenMessages.Size = new System.Drawing.Size(130, 23);
			this.btnDeleteOpenMessages.TabIndex = 8;
			this.btnDeleteOpenMessages.Text = "Delete Open Messages";
			this.btnDeleteOpenMessages.UseVisualStyleBackColor = true;
			this.btnDeleteOpenMessages.Click += new System.EventHandler(this.btnDeleteOpenMessages_Click);
			// 
			// btnSendOpenMessages
			// 
			this.btnSendOpenMessages.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.btnSendOpenMessages.Location = new System.Drawing.Point(6, 77);
			this.btnSendOpenMessages.Name = "btnSendOpenMessages";
			this.btnSendOpenMessages.Size = new System.Drawing.Size(130, 23);
			this.btnSendOpenMessages.TabIndex = 7;
			this.btnSendOpenMessages.Text = "Send Open Messages";
			this.btnSendOpenMessages.UseVisualStyleBackColor = true;
			this.btnSendOpenMessages.Click += new System.EventHandler(this.btnSendOpenMessages_Click);
			// 
			// btnTmsSession
			// 
			this.btnTmsSession.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.btnTmsSession.Location = new System.Drawing.Point(6, 19);
			this.btnTmsSession.Name = "btnTmsSession";
			this.btnTmsSession.Size = new System.Drawing.Size(130, 23);
			this.btnTmsSession.TabIndex = 6;
			this.btnTmsSession.Text = "TMS Session";
			this.btnTmsSession.UseVisualStyleBackColor = true;
			this.btnTmsSession.Click += new System.EventHandler(this.btnTmsSession_Click);
			// 
			// btnParameterDownload
			// 
			this.btnParameterDownload.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.btnParameterDownload.Location = new System.Drawing.Point(6, 48);
			this.btnParameterDownload.Name = "btnParameterDownload";
			this.btnParameterDownload.Size = new System.Drawing.Size(130, 23);
			this.btnParameterDownload.TabIndex = 5;
			this.btnParameterDownload.Text = "Parameter Download";
			this.btnParameterDownload.UseVisualStyleBackColor = true;
			this.btnParameterDownload.Click += new System.EventHandler(this.btnParameterDownload_Click);
			// 
			// btnKeyLoad
			// 
			this.btnKeyLoad.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.btnKeyLoad.Location = new System.Drawing.Point(6, 19);
			this.btnKeyLoad.Name = "btnKeyLoad";
			this.btnKeyLoad.Size = new System.Drawing.Size(130, 23);
			this.btnKeyLoad.TabIndex = 4;
			this.btnKeyLoad.Text = "Key Load";
			this.btnKeyLoad.UseVisualStyleBackColor = true;
			this.btnKeyLoad.Click += new System.EventHandler(this.btnKeyLoad_Click);
			// 
			// btnDisconnect
			// 
			this.btnDisconnect.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.btnDisconnect.Location = new System.Drawing.Point(6, 476);
			this.btnDisconnect.Name = "btnDisconnect";
			this.btnDisconnect.Size = new System.Drawing.Size(130, 23);
			this.btnDisconnect.TabIndex = 2;
			this.btnDisconnect.Text = "Disconnect";
			this.btnDisconnect.UseVisualStyleBackColor = true;
			this.btnDisconnect.Click += new System.EventHandler(this.btnDisconnect_Click);
			// 
			// gbAcquirerMessages
			// 
			this.gbAcquirerMessages.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
			this.gbAcquirerMessages.Controls.Add(this.btnParameterDownload);
			this.gbAcquirerMessages.Controls.Add(this.btnDeleteOpenMessages);
			this.gbAcquirerMessages.Controls.Add(this.btnKeyLoad);
			this.gbAcquirerMessages.Controls.Add(this.btnSendOpenMessages);
			this.gbAcquirerMessages.Location = new System.Drawing.Point(866, 27);
			this.gbAcquirerMessages.Name = "gbAcquirerMessages";
			this.gbAcquirerMessages.Size = new System.Drawing.Size(146, 139);
			this.gbAcquirerMessages.TabIndex = 9;
			this.gbAcquirerMessages.TabStop = false;
			this.gbAcquirerMessages.Text = "Acquirer Messages";
			// 
			// gbTotals
			// 
			this.gbTotals.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
			this.gbTotals.Controls.Add(this.btnClosePeriodTotals);
			this.gbTotals.Controls.Add(this.btnCurrentPreviousPeriodTotals);
			this.gbTotals.Controls.Add(this.btnPreviousPeriodTotals);
			this.gbTotals.Controls.Add(this.btnCurrentPeriodTotals);
			this.gbTotals.Controls.Add(this.btnZTotals);
			this.gbTotals.Controls.Add(this.btnXTotals);
			this.gbTotals.Location = new System.Drawing.Point(866, 172);
			this.gbTotals.Name = "gbTotals";
			this.gbTotals.Size = new System.Drawing.Size(146, 193);
			this.gbTotals.TabIndex = 10;
			this.gbTotals.TabStop = false;
			this.gbTotals.Text = "Totals";
			// 
			// btnClosePeriodTotals
			// 
			this.btnClosePeriodTotals.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.btnClosePeriodTotals.Enabled = false;
			this.btnClosePeriodTotals.Location = new System.Drawing.Point(6, 164);
			this.btnClosePeriodTotals.Name = "btnClosePeriodTotals";
			this.btnClosePeriodTotals.Size = new System.Drawing.Size(130, 23);
			this.btnClosePeriodTotals.TabIndex = 10;
			this.btnClosePeriodTotals.Text = "Close Period";
			this.btnClosePeriodTotals.UseVisualStyleBackColor = true;
			this.btnClosePeriodTotals.Visible = false;
			this.btnClosePeriodTotals.Click += new System.EventHandler(this.btnClosePeriodTotals_Click);
			// 
			// btnCurrentPreviousPeriodTotals
			// 
			this.btnCurrentPreviousPeriodTotals.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.btnCurrentPreviousPeriodTotals.Location = new System.Drawing.Point(6, 135);
			this.btnCurrentPreviousPeriodTotals.Name = "btnCurrentPreviousPeriodTotals";
			this.btnCurrentPreviousPeriodTotals.Size = new System.Drawing.Size(130, 23);
			this.btnCurrentPreviousPeriodTotals.TabIndex = 9;
			this.btnCurrentPreviousPeriodTotals.Text = "Current && Previous";
			this.btnCurrentPreviousPeriodTotals.UseVisualStyleBackColor = true;
			this.btnCurrentPreviousPeriodTotals.Click += new System.EventHandler(this.btnCurrentPreviousPeriodTotals_Click);
			// 
			// btnPreviousPeriodTotals
			// 
			this.btnPreviousPeriodTotals.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.btnPreviousPeriodTotals.Location = new System.Drawing.Point(6, 106);
			this.btnPreviousPeriodTotals.Name = "btnPreviousPeriodTotals";
			this.btnPreviousPeriodTotals.Size = new System.Drawing.Size(130, 23);
			this.btnPreviousPeriodTotals.TabIndex = 8;
			this.btnPreviousPeriodTotals.Text = "Previous Period";
			this.btnPreviousPeriodTotals.UseVisualStyleBackColor = true;
			this.btnPreviousPeriodTotals.Click += new System.EventHandler(this.btnPreviousPeriodTotals_Click);
			// 
			// btnCurrentPeriodTotals
			// 
			this.btnCurrentPeriodTotals.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.btnCurrentPeriodTotals.Location = new System.Drawing.Point(6, 77);
			this.btnCurrentPeriodTotals.Name = "btnCurrentPeriodTotals";
			this.btnCurrentPeriodTotals.Size = new System.Drawing.Size(130, 23);
			this.btnCurrentPeriodTotals.TabIndex = 7;
			this.btnCurrentPeriodTotals.Text = "Current Period";
			this.btnCurrentPeriodTotals.UseVisualStyleBackColor = true;
			this.btnCurrentPeriodTotals.Click += new System.EventHandler(this.btnCurrentPeriodTotals_Click);
			// 
			// btnZTotals
			// 
			this.btnZTotals.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.btnZTotals.Location = new System.Drawing.Point(6, 48);
			this.btnZTotals.Name = "btnZTotals";
			this.btnZTotals.Size = new System.Drawing.Size(130, 23);
			this.btnZTotals.TabIndex = 6;
			this.btnZTotals.Text = "Z-Totals";
			this.btnZTotals.UseVisualStyleBackColor = true;
			this.btnZTotals.Click += new System.EventHandler(this.btnZTotals_Click);
			// 
			// btnXTotals
			// 
			this.btnXTotals.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.btnXTotals.Location = new System.Drawing.Point(6, 19);
			this.btnXTotals.Name = "btnXTotals";
			this.btnXTotals.Size = new System.Drawing.Size(130, 23);
			this.btnXTotals.TabIndex = 5;
			this.btnXTotals.Text = "X-Totals";
			this.btnXTotals.UseVisualStyleBackColor = true;
			this.btnXTotals.Click += new System.EventHandler(this.btnXTotals_Click);
			// 
			// gbOther
			// 
			this.gbOther.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
			this.gbOther.Controls.Add(this.btnCtapInfo);
			this.gbOther.Controls.Add(this.btnCardBrandInfo);
			this.gbOther.Controls.Add(this.btnTerminalInformation);
			this.gbOther.Controls.Add(this.btnReconnect);
			this.gbOther.Controls.Add(this.btnLastTransactionTicket);
			this.gbOther.Controls.Add(this.btnClearCtapDatabase);
			this.gbOther.Controls.Add(this.btnLastTransactionStatus);
			this.gbOther.Controls.Add(this.btnTmsSession);
			this.gbOther.Controls.Add(this.btnDisconnect);
			this.gbOther.Location = new System.Drawing.Point(1018, 27);
			this.gbOther.Name = "gbOther";
			this.gbOther.Size = new System.Drawing.Size(146, 517);
			this.gbOther.TabIndex = 11;
			this.gbOther.TabStop = false;
			this.gbOther.Text = "Other";
			// 
			// btnCtapInfo
			// 
			this.btnCtapInfo.Location = new System.Drawing.Point(6, 222);
			this.btnCtapInfo.Name = "btnCtapInfo";
			this.btnCtapInfo.Size = new System.Drawing.Size(130, 23);
			this.btnCtapInfo.TabIndex = 13;
			this.btnCtapInfo.Text = "C-TAP Info";
			this.btnCtapInfo.UseVisualStyleBackColor = true;
			this.btnCtapInfo.Click += new System.EventHandler(this.btnCtapInfo_Click);
			// 
			// btnCardBrandInfo
			// 
			this.btnCardBrandInfo.Location = new System.Drawing.Point(6, 193);
			this.btnCardBrandInfo.Name = "btnCardBrandInfo";
			this.btnCardBrandInfo.Size = new System.Drawing.Size(130, 23);
			this.btnCardBrandInfo.TabIndex = 12;
			this.btnCardBrandInfo.Text = "Card Brand Info";
			this.btnCardBrandInfo.UseVisualStyleBackColor = true;
			this.btnCardBrandInfo.Click += new System.EventHandler(this.btnCardBrandInfo_Click);
			// 
			// btnTerminalInformation
			// 
			this.btnTerminalInformation.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.btnTerminalInformation.Location = new System.Drawing.Point(6, 164);
			this.btnTerminalInformation.Name = "btnTerminalInformation";
			this.btnTerminalInformation.Size = new System.Drawing.Size(130, 23);
			this.btnTerminalInformation.TabIndex = 11;
			this.btnTerminalInformation.Text = "Terminal Information";
			this.btnTerminalInformation.UseVisualStyleBackColor = true;
			this.btnTerminalInformation.Click += new System.EventHandler(this.btnTerminalInformation_Click);
			// 
			// btnReconnect
			// 
			this.btnReconnect.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.btnReconnect.Location = new System.Drawing.Point(6, 447);
			this.btnReconnect.Name = "btnReconnect";
			this.btnReconnect.Size = new System.Drawing.Size(130, 23);
			this.btnReconnect.TabIndex = 10;
			this.btnReconnect.Text = "Reconnect";
			this.btnReconnect.UseVisualStyleBackColor = true;
			this.btnReconnect.Click += new System.EventHandler(this.btnReconnect_Click);
			// 
			// btnLastTransactionTicket
			// 
			this.btnLastTransactionTicket.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.btnLastTransactionTicket.Location = new System.Drawing.Point(6, 77);
			this.btnLastTransactionTicket.Name = "btnLastTransactionTicket";
			this.btnLastTransactionTicket.Size = new System.Drawing.Size(130, 23);
			this.btnLastTransactionTicket.TabIndex = 9;
			this.btnLastTransactionTicket.Text = "Last Ticket";
			this.btnLastTransactionTicket.UseVisualStyleBackColor = true;
			this.btnLastTransactionTicket.Click += new System.EventHandler(this.btnLastTransactionTicket_Click);
			// 
			// btnClearCtapDatabase
			// 
			this.btnClearCtapDatabase.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.btnClearCtapDatabase.Location = new System.Drawing.Point(6, 106);
			this.btnClearCtapDatabase.Name = "btnClearCtapDatabase";
			this.btnClearCtapDatabase.Size = new System.Drawing.Size(130, 23);
			this.btnClearCtapDatabase.TabIndex = 8;
			this.btnClearCtapDatabase.Text = "Clear C-TAP DB";
			this.btnClearCtapDatabase.UseVisualStyleBackColor = true;
			this.btnClearCtapDatabase.Click += new System.EventHandler(this.btnClearCtapDatabase_Click);
			// 
			// btnLastTransactionStatus
			// 
			this.btnLastTransactionStatus.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.btnLastTransactionStatus.Location = new System.Drawing.Point(6, 48);
			this.btnLastTransactionStatus.Name = "btnLastTransactionStatus";
			this.btnLastTransactionStatus.Size = new System.Drawing.Size(130, 23);
			this.btnLastTransactionStatus.TabIndex = 7;
			this.btnLastTransactionStatus.Text = "Last Transaction";
			this.btnLastTransactionStatus.UseVisualStyleBackColor = true;
			this.btnLastTransactionStatus.Click += new System.EventHandler(this.btnLastTransactionStatus_Click);
			// 
			// menuStrip
			// 
			this.menuStrip.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.menuSettings,
            this.menuProduceErrors,
            this.menuHelp});
			this.menuStrip.Location = new System.Drawing.Point(0, 0);
			this.menuStrip.Name = "menuStrip";
			this.menuStrip.Size = new System.Drawing.Size(1176, 24);
			this.menuStrip.TabIndex = 12;
			this.menuStrip.Text = "menuStrip1";
			// 
			// menuSettings
			// 
			this.menuSettings.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.menuSettings_Configure,
            this.menuSettings_TransparentMode});
			this.menuSettings.Name = "menuSettings";
			this.menuSettings.Size = new System.Drawing.Size(61, 20);
			this.menuSettings.Text = "&Settings";
			// 
			// menuSettings_Configure
			// 
			this.menuSettings_Configure.Name = "menuSettings_Configure";
			this.menuSettings_Configure.Size = new System.Drawing.Size(170, 22);
			this.menuSettings_Configure.Text = "&Configure";
			this.menuSettings_Configure.Click += new System.EventHandler(this.menuSettings_Configure_Click);
			// 
			// menuSettings_TransparentMode
			// 
			this.menuSettings_TransparentMode.Name = "menuSettings_TransparentMode";
			this.menuSettings_TransparentMode.Size = new System.Drawing.Size(170, 22);
			this.menuSettings_TransparentMode.Text = "&Transparent Mode";
			this.menuSettings_TransparentMode.Click += new System.EventHandler(this.menuSettings_TransparentMode_Click);
			// 
			// menuProduceErrors
			// 
			this.menuProduceErrors.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.menuProduceErrors_SendInvalid3F00,
            this.menuProduceErrors_SendPrimitiveAsGroup1F7F,
            this.menuProduceErrors_SendGroupAsPrimitiveA6,
            this.menuProduceErrors_SendOptionalTagWithWorngLength53,
            this.menuProduceErrors_SendRequiredTagWithWorngLength50,
            this.menuProduceErrors_SkipMandatoryTag50});
			this.menuProduceErrors.Name = "menuProduceErrors";
			this.menuProduceErrors.Size = new System.Drawing.Size(96, 20);
			this.menuProduceErrors.Text = "&Produce errors";
			// 
			// menuProduceErrors_SendInvalid3F00
			// 
			this.menuProduceErrors_SendInvalid3F00.Name = "menuProduceErrors_SendInvalid3F00";
			this.menuProduceErrors_SendInvalid3F00.Size = new System.Drawing.Size(282, 22);
			this.menuProduceErrors_SendInvalid3F00.Text = "Send invalid group tag 3F00";
			this.menuProduceErrors_SendInvalid3F00.Click += new System.EventHandler(this.menuProduceErrors_SendInvalid3F00_Click);
			// 
			// menuProduceErrors_SendPrimitiveAsGroup1F7F
			// 
			this.menuProduceErrors_SendPrimitiveAsGroup1F7F.Name = "menuProduceErrors_SendPrimitiveAsGroup1F7F";
			this.menuProduceErrors_SendPrimitiveAsGroup1F7F.Size = new System.Drawing.Size(282, 22);
			this.menuProduceErrors_SendPrimitiveAsGroup1F7F.Text = "Send primitive as group 1F7F";
			this.menuProduceErrors_SendPrimitiveAsGroup1F7F.Click += new System.EventHandler(this.menuProduceErrors_SendPrimitiveAsGroup1F7F_Click);
			// 
			// menuProduceErrors_SendGroupAsPrimitiveA6
			// 
			this.menuProduceErrors_SendGroupAsPrimitiveA6.Name = "menuProduceErrors_SendGroupAsPrimitiveA6";
			this.menuProduceErrors_SendGroupAsPrimitiveA6.Size = new System.Drawing.Size(282, 22);
			this.menuProduceErrors_SendGroupAsPrimitiveA6.Text = "Send group as primitive A6";
			this.menuProduceErrors_SendGroupAsPrimitiveA6.Click += new System.EventHandler(this.menuProduceErrors_SendGroupAsPrimitiveA6_Click);
			// 
			// menuProduceErrors_SendOptionalTagWithWorngLength53
			// 
			this.menuProduceErrors_SendOptionalTagWithWorngLength53.AutoSize = false;
			this.menuProduceErrors_SendOptionalTagWithWorngLength53.Name = "menuProduceErrors_SendOptionalTagWithWorngLength53";
			this.menuProduceErrors_SendOptionalTagWithWorngLength53.Size = new System.Drawing.Size(282, 22);
			this.menuProduceErrors_SendOptionalTagWithWorngLength53.Text = "Send optional tag with wrong length 53";
			this.menuProduceErrors_SendOptionalTagWithWorngLength53.Click += new System.EventHandler(this.menuProduceErrors_SendOptionalTagWithWrongLength1F70_Click);
			// 
			// menuProduceErrors_SendRequiredTagWithWorngLength50
			// 
			this.menuProduceErrors_SendRequiredTagWithWorngLength50.Name = "menuProduceErrors_SendRequiredTagWithWorngLength50";
			this.menuProduceErrors_SendRequiredTagWithWorngLength50.Size = new System.Drawing.Size(282, 22);
			this.menuProduceErrors_SendRequiredTagWithWorngLength50.Text = "Send required tag with wrong length 50";
			this.menuProduceErrors_SendRequiredTagWithWorngLength50.Click += new System.EventHandler(this.menuProduceErrors_SendRequiredTagWithWorngLength50_Click);
			// 
			// menuProduceErrors_SkipMandatoryTag50
			// 
			this.menuProduceErrors_SkipMandatoryTag50.Name = "menuProduceErrors_SkipMandatoryTag50";
			this.menuProduceErrors_SkipMandatoryTag50.Size = new System.Drawing.Size(282, 22);
			this.menuProduceErrors_SkipMandatoryTag50.Text = "Skip mandatory tag 50";
			this.menuProduceErrors_SkipMandatoryTag50.Click += new System.EventHandler(this.menuProduceErrors_SkipMandatoryTag53_Click);
			// 
			// menuHelp
			// 
			this.menuHelp.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.menuHelp_About});
			this.menuHelp.Name = "menuHelp";
			this.menuHelp.Size = new System.Drawing.Size(44, 20);
			this.menuHelp.Text = "&Help";
			// 
			// menuHelp_About
			// 
			this.menuHelp_About.Name = "menuHelp_About";
			this.menuHelp_About.Size = new System.Drawing.Size(107, 22);
			this.menuHelp_About.Text = "&About";
			this.menuHelp_About.Click += new System.EventHandler(this.menuHelp_About_Click);
			// 
			// gbTransparentMode
			// 
			this.gbTransparentMode.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
			this.gbTransparentMode.Controls.Add(this.buttonTmAuthenticate);
			this.gbTransparentMode.Controls.Add(this.buttonTmReadCardData);
			this.gbTransparentMode.Controls.Add(this.buttonTmUiControl);
			this.gbTransparentMode.Controls.Add(this.buttonTmStartStopTransparentMode);
			this.gbTransparentMode.Location = new System.Drawing.Point(866, 371);
			this.gbTransparentMode.Name = "gbTransparentMode";
			this.gbTransparentMode.Size = new System.Drawing.Size(146, 173);
			this.gbTransparentMode.TabIndex = 13;
			this.gbTransparentMode.TabStop = false;
			this.gbTransparentMode.Text = "Transparent Mode";
			// 
			// buttonTmAuthenticate
			// 
			this.buttonTmAuthenticate.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.buttonTmAuthenticate.Location = new System.Drawing.Point(6, 48);
			this.buttonTmAuthenticate.Name = "buttonTmAuthenticate";
			this.buttonTmAuthenticate.Size = new System.Drawing.Size(130, 23);
			this.buttonTmAuthenticate.TabIndex = 9;
			this.buttonTmAuthenticate.Text = "Authenticate";
			this.buttonTmAuthenticate.UseVisualStyleBackColor = true;
			this.buttonTmAuthenticate.Click += new System.EventHandler(this.buttonTmAuthenticate_Click);
			// 
			// buttonTmReadCardData
			// 
			this.buttonTmReadCardData.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.buttonTmReadCardData.Location = new System.Drawing.Point(6, 77);
			this.buttonTmReadCardData.Name = "buttonTmReadCardData";
			this.buttonTmReadCardData.Size = new System.Drawing.Size(130, 23);
			this.buttonTmReadCardData.TabIndex = 8;
			this.buttonTmReadCardData.Text = "Read Card Data";
			this.buttonTmReadCardData.UseVisualStyleBackColor = true;
			this.buttonTmReadCardData.Click += new System.EventHandler(this.buttonTmReadCardData_Click);
			// 
			// buttonTmUiControl
			// 
			this.buttonTmUiControl.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.buttonTmUiControl.Location = new System.Drawing.Point(6, 106);
			this.buttonTmUiControl.Name = "buttonTmUiControl";
			this.buttonTmUiControl.Size = new System.Drawing.Size(130, 23);
			this.buttonTmUiControl.TabIndex = 7;
			this.buttonTmUiControl.Text = "UI Control";
			this.buttonTmUiControl.UseVisualStyleBackColor = true;
			this.buttonTmUiControl.Click += new System.EventHandler(this.buttonTmUiControl_Click);
			// 
			// buttonTmStartStopTransparentMode
			// 
			this.buttonTmStartStopTransparentMode.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.buttonTmStartStopTransparentMode.Location = new System.Drawing.Point(6, 19);
			this.buttonTmStartStopTransparentMode.Name = "buttonTmStartStopTransparentMode";
			this.buttonTmStartStopTransparentMode.Size = new System.Drawing.Size(130, 23);
			this.buttonTmStartStopTransparentMode.TabIndex = 6;
			this.buttonTmStartStopTransparentMode.Text = "Start/Stop";
			this.buttonTmStartStopTransparentMode.UseVisualStyleBackColor = true;
			this.buttonTmStartStopTransparentMode.Click += new System.EventHandler(this.buttonTmStartStopTransparentMode_Click);
			// 
			// lblMerchantMessage
			// 
			this.lblMerchantMessage.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.lblMerchantMessage.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
			this.lblMerchantMessage.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.lblMerchantMessage.Location = new System.Drawing.Point(12, 550);
			this.lblMerchantMessage.Name = "lblMerchantMessage";
			this.lblMerchantMessage.Size = new System.Drawing.Size(1152, 80);
			this.lblMerchantMessage.TabIndex = 15;
			this.lblMerchantMessage.Text = "--- No message ---";
			this.lblMerchantMessage.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
			// 
			// MainForm
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(1176, 788);
			this.Controls.Add(this.lblMerchantMessage);
			this.Controls.Add(this.gbTransparentMode);
			this.Controls.Add(this.groupBox2);
			this.Controls.Add(this.gbTotals);
			this.Controls.Add(this.gbOther);
			this.Controls.Add(this.listViewMessages);
			this.Controls.Add(this.gbAcquirerMessages);
			this.Controls.Add(this.statusStrip);
			this.Controls.Add(this.menuStrip);
			this.Controls.Add(this.groupBox1);
			this.MainMenuStrip = this.menuStrip;
			this.Name = "MainForm";
			this.Text = "Telium Cash Register";
			this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.MainForm_FormClosing);
			this.Load += new System.EventHandler(this.MainForm_Load);
			this.groupBox1.ResumeLayout(false);
			this.groupBox1.PerformLayout();
			this.tableLayoutPanel1.ResumeLayout(false);
			this.statusStrip.ResumeLayout(false);
			this.statusStrip.PerformLayout();
			this.groupBox2.ResumeLayout(false);
			this.tableLayoutPanel2.ResumeLayout(false);
			this.tableLayoutPanel2.PerformLayout();
			this.contextMenuMessages.ResumeLayout(false);
			this.gbAcquirerMessages.ResumeLayout(false);
			this.gbTotals.ResumeLayout(false);
			this.gbOther.ResumeLayout(false);
			this.menuStrip.ResumeLayout(false);
			this.menuStrip.PerformLayout();
			this.gbTransparentMode.ResumeLayout(false);
			this.ResumeLayout(false);
			this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1;
        private System.Windows.Forms.Button btnOK;
        private System.Windows.Forms.Button btnZero;
        private System.Windows.Forms.Button btnCorrection;
        private System.Windows.Forms.Button btnNine;
        private System.Windows.Forms.Button btnEight;
        private System.Windows.Forms.Button btnSeven;
        private System.Windows.Forms.Button btnSix;
        private System.Windows.Forms.Button btnFive;
        private System.Windows.Forms.Button btnFour;
        private System.Windows.Forms.Button btnThree;
        private System.Windows.Forms.Button btnTwo;
        private System.Windows.Forms.Button bntOne;
        private System.Windows.Forms.TextBox txtAmount;
        private System.Windows.Forms.StatusStrip statusStrip;
        private System.Windows.Forms.ToolStripStatusLabel lblStatus;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.Button btnDisconnect;
        private System.Windows.Forms.ListView listViewMessages;
        private System.Windows.Forms.ColumnHeader chMessages;
        private System.Windows.Forms.Label lblTransactionType;
        private System.Windows.Forms.ComboBox cbTransactionType;
        private System.Windows.Forms.Button btnKeyLoad;
        private System.Windows.Forms.Button btnParameterDownload;
        private System.Windows.Forms.Button btnTmsSession;
        private System.Windows.Forms.Button btnDeleteOpenMessages;
        private System.Windows.Forms.Button btnSendOpenMessages;
        private System.Windows.Forms.CheckBox cbAutoIncrementAmount;
        private System.Windows.Forms.CheckBox cbAutoRepeatTransaction;
        private System.Windows.Forms.GroupBox gbOther;
        private System.Windows.Forms.GroupBox gbTotals;
        private System.Windows.Forms.Button btnClosePeriodTotals;
        private System.Windows.Forms.Button btnCurrentPreviousPeriodTotals;
        private System.Windows.Forms.Button btnPreviousPeriodTotals;
        private System.Windows.Forms.Button btnCurrentPeriodTotals;
        private System.Windows.Forms.Button btnZTotals;
        private System.Windows.Forms.GroupBox gbAcquirerMessages;
        private System.Windows.Forms.TextBox txtCardholderTicket;
        private System.Windows.Forms.Label lblCardHolderTicket;
        private System.Windows.Forms.Button btnClearCtapDatabase;
        private System.Windows.Forms.Button btnLastTransactionStatus;
        private System.Windows.Forms.Button btnLastTransactionTicket;
        private System.Windows.Forms.Button btnReconnect;
        private System.Windows.Forms.Label lblJournalTicket;
        private System.Windows.Forms.TextBox txtJournalTicket;
        private System.Windows.Forms.Label lblMerchantTicket;
        private System.Windows.Forms.TextBox txtMerchantTicket;
        private System.Windows.Forms.Button btnTerminalInformation;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel2;
        private System.Windows.Forms.ContextMenuStrip contextMenuMessages;
        private System.Windows.Forms.ToolStripMenuItem cmMessagesClear;
        private System.Windows.Forms.MenuStrip menuStrip;
        private System.Windows.Forms.ToolStripMenuItem menuSettings;
        private System.Windows.Forms.ToolStripMenuItem menuSettings_Configure;
        private System.Windows.Forms.ToolStripMenuItem menuHelp;
        private System.Windows.Forms.ToolStripMenuItem menuHelp_About;
        private System.Windows.Forms.CheckBox checkboxEnableTransparentMode;
        private System.Windows.Forms.ToolStripStatusLabel lblStatus_KeepAlive;
        private System.Windows.Forms.TextBox txtReference;
        private System.Windows.Forms.Label label1;
		private System.Windows.Forms.Button btnCancel;
		private System.Windows.Forms.Button btnXTotals;
		private System.Windows.Forms.GroupBox gbTransparentMode;
		private System.Windows.Forms.Button buttonTmReadCardData;
		private System.Windows.Forms.Button buttonTmUiControl;
		private System.Windows.Forms.Button buttonTmStartStopTransparentMode;
		private System.Windows.Forms.ComboBox comboboxTransactionMode;
		private System.Windows.Forms.Label labelIntermediateResultMode;
		private System.Windows.Forms.Button buttonTmAuthenticate;
		private System.Windows.Forms.ToolStripMenuItem menuSettings_TransparentMode;
		private System.Windows.Forms.ToolStripMenuItem menuProduceErrors;
		private System.Windows.Forms.ToolStripMenuItem menuProduceErrors_SendInvalid3F00;
		private System.Windows.Forms.ToolStripMenuItem menuProduceErrors_SendPrimitiveAsGroup1F7F;
		private System.Windows.Forms.ToolStripMenuItem menuProduceErrors_SendGroupAsPrimitiveA6;
		private System.Windows.Forms.ToolStripMenuItem menuProduceErrors_SendOptionalTagWithWorngLength53;
		private System.Windows.Forms.ToolStripMenuItem menuProduceErrors_SkipMandatoryTag50;
		private System.Windows.Forms.ToolStripMenuItem menuProduceErrors_SendRequiredTagWithWorngLength50;
		private System.Windows.Forms.ToolStripStatusLabel lblStatus_StatusUpdates;
		private System.Windows.Forms.ColumnHeader chDateTime;
		private System.Windows.Forms.Label lblMerchantMessage;
        private System.Windows.Forms.Button btnCtapInfo;
        private System.Windows.Forms.Button btnCardBrandInfo;
    }
}

