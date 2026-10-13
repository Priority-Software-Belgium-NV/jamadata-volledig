namespace ChessPt.CashRegister.Forms
{
	partial class TmSettingsForm
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
			System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle1 = new System.Windows.Forms.DataGridViewCellStyle();
			this.datagridCardKeys = new System.Windows.Forms.DataGridView();
			this.columnCardUID = new System.Windows.Forms.DataGridViewTextBoxColumn();
			this.columnCardKey = new System.Windows.Forms.DataGridViewTextBoxColumn();
			this.buttonOk = new System.Windows.Forms.Button();
			this.buttonCancel = new System.Windows.Forms.Button();
			this.groupboxTransparentModeSettings = new System.Windows.Forms.GroupBox();
			this.textboxKeyGenSecret = new System.Windows.Forms.TextBox();
			this.labelKeyGenSecret = new System.Windows.Forms.Label();
			this.textboxDealerId = new System.Windows.Forms.TextBox();
			this.labelDealerId = new System.Windows.Forms.Label();
			this.labelCardDetectionTimeout = new System.Windows.Forms.Label();
			this.label2 = new System.Windows.Forms.Label();
			this.numCardDetectionTimeout = new System.Windows.Forms.NumericUpDown();
			this.groupboxCardKeys = new System.Windows.Forms.GroupBox();
			this.errorProvider = new System.Windows.Forms.ErrorProvider(this.components);
			((System.ComponentModel.ISupportInitialize)(this.datagridCardKeys)).BeginInit();
			this.groupboxTransparentModeSettings.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)(this.numCardDetectionTimeout)).BeginInit();
			this.groupboxCardKeys.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)(this.errorProvider)).BeginInit();
			this.SuspendLayout();
			// 
			// datagridCardKeys
			// 
			this.datagridCardKeys.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
			this.datagridCardKeys.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.columnCardUID,
            this.columnCardKey});
			dataGridViewCellStyle1.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleLeft;
			dataGridViewCellStyle1.BackColor = System.Drawing.SystemColors.Window;
			dataGridViewCellStyle1.Font = new System.Drawing.Font("Courier New", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			dataGridViewCellStyle1.ForeColor = System.Drawing.SystemColors.ControlText;
			dataGridViewCellStyle1.SelectionBackColor = System.Drawing.SystemColors.Highlight;
			dataGridViewCellStyle1.SelectionForeColor = System.Drawing.SystemColors.HighlightText;
			dataGridViewCellStyle1.WrapMode = System.Windows.Forms.DataGridViewTriState.False;
			this.datagridCardKeys.DefaultCellStyle = dataGridViewCellStyle1;
			this.datagridCardKeys.Dock = System.Windows.Forms.DockStyle.Fill;
			this.datagridCardKeys.Location = new System.Drawing.Point(3, 16);
			this.datagridCardKeys.Name = "datagridCardKeys";
			this.datagridCardKeys.Size = new System.Drawing.Size(1096, 365);
			this.datagridCardKeys.TabIndex = 0;
			// 
			// columnCardUID
			// 
			this.columnCardUID.HeaderText = "Card UID";
			this.columnCardUID.Name = "columnCardUID";
			this.columnCardUID.Width = 200;
			// 
			// columnCardKey
			// 
			this.columnCardKey.HeaderText = "Authorisation Key";
			this.columnCardKey.Name = "columnCardKey";
			this.columnCardKey.Width = 600;
			// 
			// buttonOk
			// 
			this.buttonOk.Location = new System.Drawing.Point(958, 519);
			this.buttonOk.Name = "buttonOk";
			this.buttonOk.Size = new System.Drawing.Size(75, 23);
			this.buttonOk.TabIndex = 1;
			this.buttonOk.Text = "OK";
			this.buttonOk.UseVisualStyleBackColor = true;
			this.buttonOk.Click += new System.EventHandler(this.buttonOk_Click);
			// 
			// buttonCancel
			// 
			this.buttonCancel.DialogResult = System.Windows.Forms.DialogResult.Cancel;
			this.buttonCancel.Location = new System.Drawing.Point(1039, 519);
			this.buttonCancel.Name = "buttonCancel";
			this.buttonCancel.Size = new System.Drawing.Size(75, 23);
			this.buttonCancel.TabIndex = 2;
			this.buttonCancel.Text = "Cancel";
			this.buttonCancel.UseVisualStyleBackColor = true;
			// 
			// groupboxTransparentModeSettings
			// 
			this.groupboxTransparentModeSettings.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.groupboxTransparentModeSettings.Controls.Add(this.textboxKeyGenSecret);
			this.groupboxTransparentModeSettings.Controls.Add(this.labelKeyGenSecret);
			this.groupboxTransparentModeSettings.Controls.Add(this.textboxDealerId);
			this.groupboxTransparentModeSettings.Controls.Add(this.labelDealerId);
			this.groupboxTransparentModeSettings.Controls.Add(this.labelCardDetectionTimeout);
			this.groupboxTransparentModeSettings.Controls.Add(this.label2);
			this.groupboxTransparentModeSettings.Controls.Add(this.numCardDetectionTimeout);
			this.groupboxTransparentModeSettings.Location = new System.Drawing.Point(12, 12);
			this.groupboxTransparentModeSettings.Name = "groupboxTransparentModeSettings";
			this.groupboxTransparentModeSettings.Size = new System.Drawing.Size(1102, 111);
			this.groupboxTransparentModeSettings.TabIndex = 3;
			this.groupboxTransparentModeSettings.TabStop = false;
			this.groupboxTransparentModeSettings.Text = "Transparent Mode Settings";
			// 
			// textboxKeyGenSecret
			// 
			this.textboxKeyGenSecret.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.textboxKeyGenSecret.Location = new System.Drawing.Point(128, 78);
			this.textboxKeyGenSecret.Name = "textboxKeyGenSecret";
			this.textboxKeyGenSecret.Size = new System.Drawing.Size(952, 20);
			this.textboxKeyGenSecret.TabIndex = 16;
			// 
			// labelKeyGenSecret
			// 
			this.labelKeyGenSecret.AutoSize = true;
			this.labelKeyGenSecret.Location = new System.Drawing.Point(6, 81);
			this.labelKeyGenSecret.Name = "labelKeyGenSecret";
			this.labelKeyGenSecret.Size = new System.Drawing.Size(110, 13);
			this.labelKeyGenSecret.TabIndex = 17;
			this.labelKeyGenSecret.Text = "Key generation secret";
			// 
			// textboxDealerId
			// 
			this.textboxDealerId.Location = new System.Drawing.Point(128, 52);
			this.textboxDealerId.Name = "textboxDealerId";
			this.textboxDealerId.Size = new System.Drawing.Size(129, 20);
			this.textboxDealerId.TabIndex = 4;
			// 
			// labelDealerId
			// 
			this.labelDealerId.AutoSize = true;
			this.labelDealerId.Location = new System.Drawing.Point(6, 52);
			this.labelDealerId.Name = "labelDealerId";
			this.labelDealerId.Size = new System.Drawing.Size(52, 13);
			this.labelDealerId.TabIndex = 15;
			this.labelDealerId.Text = "Dealer ID";
			// 
			// labelCardDetectionTimeout
			// 
			this.labelCardDetectionTimeout.AutoSize = true;
			this.labelCardDetectionTimeout.Location = new System.Drawing.Point(6, 26);
			this.labelCardDetectionTimeout.Name = "labelCardDetectionTimeout";
			this.labelCardDetectionTimeout.Size = new System.Drawing.Size(116, 13);
			this.labelCardDetectionTimeout.TabIndex = 14;
			this.labelCardDetectionTimeout.Text = "Card detection time-out";
			// 
			// label2
			// 
			this.label2.AutoSize = true;
			this.label2.Location = new System.Drawing.Point(210, 26);
			this.label2.Name = "label2";
			this.label2.Size = new System.Drawing.Size(47, 13);
			this.label2.TabIndex = 13;
			this.label2.Text = "seconds";
			// 
			// numCardDetectionTimeout
			// 
			this.numCardDetectionTimeout.Increment = new decimal(new int[] {
            5,
            0,
            0,
            0});
			this.numCardDetectionTimeout.Location = new System.Drawing.Point(128, 24);
			this.numCardDetectionTimeout.Maximum = new decimal(new int[] {
            3600,
            0,
            0,
            0});
			this.numCardDetectionTimeout.Name = "numCardDetectionTimeout";
			this.numCardDetectionTimeout.Size = new System.Drawing.Size(78, 20);
			this.numCardDetectionTimeout.TabIndex = 12;
			// 
			// groupboxCardKeys
			// 
			this.groupboxCardKeys.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.groupboxCardKeys.Controls.Add(this.datagridCardKeys);
			this.groupboxCardKeys.Location = new System.Drawing.Point(12, 129);
			this.groupboxCardKeys.Name = "groupboxCardKeys";
			this.groupboxCardKeys.Size = new System.Drawing.Size(1102, 384);
			this.groupboxCardKeys.TabIndex = 4;
			this.groupboxCardKeys.TabStop = false;
			this.groupboxCardKeys.Text = "Card Authorisation Keys";
			// 
			// errorProvider
			// 
			this.errorProvider.ContainerControl = this;
			// 
			// TmSettingsForm
			// 
			this.AcceptButton = this.buttonOk;
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.CancelButton = this.buttonCancel;
			this.ClientSize = new System.Drawing.Size(1126, 554);
			this.Controls.Add(this.groupboxCardKeys);
			this.Controls.Add(this.groupboxTransparentModeSettings);
			this.Controls.Add(this.buttonCancel);
			this.Controls.Add(this.buttonOk);
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
			this.MaximizeBox = false;
			this.MinimizeBox = false;
			this.Name = "TmSettingsForm";
			this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
			this.Text = "Transparent Mode Settings";
			((System.ComponentModel.ISupportInitialize)(this.datagridCardKeys)).EndInit();
			this.groupboxTransparentModeSettings.ResumeLayout(false);
			this.groupboxTransparentModeSettings.PerformLayout();
			((System.ComponentModel.ISupportInitialize)(this.numCardDetectionTimeout)).EndInit();
			this.groupboxCardKeys.ResumeLayout(false);
			((System.ComponentModel.ISupportInitialize)(this.errorProvider)).EndInit();
			this.ResumeLayout(false);

		}

		#endregion

		private System.Windows.Forms.DataGridView datagridCardKeys;
		private System.Windows.Forms.Button buttonOk;
		private System.Windows.Forms.Button buttonCancel;
		private System.Windows.Forms.GroupBox groupboxTransparentModeSettings;
		private System.Windows.Forms.Label labelDealerId;
		private System.Windows.Forms.Label labelCardDetectionTimeout;
		private System.Windows.Forms.Label label2;
		private System.Windows.Forms.NumericUpDown numCardDetectionTimeout;
		private System.Windows.Forms.TextBox textboxKeyGenSecret;
		private System.Windows.Forms.Label labelKeyGenSecret;
		private System.Windows.Forms.TextBox textboxDealerId;
		private System.Windows.Forms.GroupBox groupboxCardKeys;
		private System.Windows.Forms.ErrorProvider errorProvider;
		private System.Windows.Forms.DataGridViewTextBoxColumn columnCardUID;
		private System.Windows.Forms.DataGridViewTextBoxColumn columnCardKey;
	}
}