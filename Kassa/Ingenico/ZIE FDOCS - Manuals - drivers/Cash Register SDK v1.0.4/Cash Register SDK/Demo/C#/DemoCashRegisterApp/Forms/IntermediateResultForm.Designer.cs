namespace ChessPt.CashRegister.Forms
{
    partial class IntermediateResultForm
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
			this.buttonYes = new System.Windows.Forms.Button();
			this.buttonNo = new System.Windows.Forms.Button();
			this.labelFinalTransactionAmount = new System.Windows.Forms.Label();
			this.textboxFinalTransactionAmount = new System.Windows.Forms.TextBox();
			this.labelIntermediateResult = new System.Windows.Forms.Label();
			this.textboxIntermediateResult = new System.Windows.Forms.TextBox();
			this.textboxAuthorisedAmount = new System.Windows.Forms.TextBox();
			this.labelAuthorisedAmount = new System.Windows.Forms.Label();
			this.labelContinueTransaction = new System.Windows.Forms.Label();
			this.errorProvider = new System.Windows.Forms.ErrorProvider(this.components);
			this.labelIntermediateResultMode = new System.Windows.Forms.Label();
			this.textboxIntermediateResultMode = new System.Windows.Forms.TextBox();
			((System.ComponentModel.ISupportInitialize)(this.errorProvider)).BeginInit();
			this.SuspendLayout();
			// 
			// buttonYes
			// 
			this.buttonYes.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
			this.buttonYes.DialogResult = System.Windows.Forms.DialogResult.Yes;
			this.buttonYes.Location = new System.Drawing.Point(175, 153);
			this.buttonYes.Name = "buttonYes";
			this.buttonYes.Size = new System.Drawing.Size(75, 23);
			this.buttonYes.TabIndex = 1;
			this.buttonYes.Text = "Yes";
			this.buttonYes.UseVisualStyleBackColor = true;
			// 
			// buttonNo
			// 
			this.buttonNo.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
			this.buttonNo.DialogResult = System.Windows.Forms.DialogResult.No;
			this.buttonNo.Location = new System.Drawing.Point(256, 153);
			this.buttonNo.Name = "buttonNo";
			this.buttonNo.Size = new System.Drawing.Size(75, 23);
			this.buttonNo.TabIndex = 2;
			this.buttonNo.Text = "No";
			this.buttonNo.UseVisualStyleBackColor = true;
			// 
			// labelFinalTransactionAmount
			// 
			this.labelFinalTransactionAmount.AutoSize = true;
			this.labelFinalTransactionAmount.Location = new System.Drawing.Point(8, 93);
			this.labelFinalTransactionAmount.Name = "labelFinalTransactionAmount";
			this.labelFinalTransactionAmount.Size = new System.Drawing.Size(122, 13);
			this.labelFinalTransactionAmount.TabIndex = 3;
			this.labelFinalTransactionAmount.Text = "Final transaction amount";
			// 
			// textboxFinalTransactionAmount
			// 
			this.textboxFinalTransactionAmount.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.textboxFinalTransactionAmount.Location = new System.Drawing.Point(138, 90);
			this.textboxFinalTransactionAmount.Name = "textboxFinalTransactionAmount";
			this.textboxFinalTransactionAmount.Size = new System.Drawing.Size(191, 20);
			this.textboxFinalTransactionAmount.TabIndex = 4;
			this.textboxFinalTransactionAmount.Leave += new System.EventHandler(this.txtFinalTransactionAmount_Leave);
			// 
			// labelIntermediateResult
			// 
			this.labelIntermediateResult.AutoSize = true;
			this.labelIntermediateResult.Location = new System.Drawing.Point(10, 41);
			this.labelIntermediateResult.Name = "labelIntermediateResult";
			this.labelIntermediateResult.Size = new System.Drawing.Size(93, 13);
			this.labelIntermediateResult.TabIndex = 5;
			this.labelIntermediateResult.Text = "Intermediate result";
			// 
			// textboxIntermediateResult
			// 
			this.textboxIntermediateResult.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.textboxIntermediateResult.Location = new System.Drawing.Point(138, 38);
			this.textboxIntermediateResult.Name = "textboxIntermediateResult";
			this.textboxIntermediateResult.ReadOnly = true;
			this.textboxIntermediateResult.Size = new System.Drawing.Size(191, 20);
			this.textboxIntermediateResult.TabIndex = 6;
			// 
			// textboxAuthorisedAmount
			// 
			this.textboxAuthorisedAmount.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.textboxAuthorisedAmount.Location = new System.Drawing.Point(138, 64);
			this.textboxAuthorisedAmount.Name = "textboxAuthorisedAmount";
			this.textboxAuthorisedAmount.ReadOnly = true;
			this.textboxAuthorisedAmount.Size = new System.Drawing.Size(191, 20);
			this.textboxAuthorisedAmount.TabIndex = 8;
			// 
			// labelAuthorisedAmount
			// 
			this.labelAuthorisedAmount.AutoSize = true;
			this.labelAuthorisedAmount.Location = new System.Drawing.Point(8, 67);
			this.labelAuthorisedAmount.Name = "labelAuthorisedAmount";
			this.labelAuthorisedAmount.Size = new System.Drawing.Size(95, 13);
			this.labelAuthorisedAmount.TabIndex = 7;
			this.labelAuthorisedAmount.Text = "Authorised amount";
			// 
			// labelContinueTransaction
			// 
			this.labelContinueTransaction.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
			this.labelContinueTransaction.AutoSize = true;
			this.labelContinueTransaction.Location = new System.Drawing.Point(8, 158);
			this.labelContinueTransaction.Name = "labelContinueTransaction";
			this.labelContinueTransaction.Size = new System.Drawing.Size(110, 13);
			this.labelContinueTransaction.TabIndex = 9;
			this.labelContinueTransaction.Text = "Continue transaction?";
			// 
			// errorProvider
			// 
			this.errorProvider.ContainerControl = this;
			// 
			// labelIntermediateResultMode
			// 
			this.labelIntermediateResultMode.AutoSize = true;
			this.labelIntermediateResultMode.Location = new System.Drawing.Point(10, 15);
			this.labelIntermediateResultMode.Name = "labelIntermediateResultMode";
			this.labelIntermediateResultMode.Size = new System.Drawing.Size(122, 13);
			this.labelIntermediateResultMode.TabIndex = 10;
			this.labelIntermediateResultMode.Text = "Intermediate result mode";
			// 
			// textboxIntermediateResultMode
			// 
			this.textboxIntermediateResultMode.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.textboxIntermediateResultMode.Location = new System.Drawing.Point(138, 12);
			this.textboxIntermediateResultMode.Name = "textboxIntermediateResultMode";
			this.textboxIntermediateResultMode.ReadOnly = true;
			this.textboxIntermediateResultMode.Size = new System.Drawing.Size(191, 20);
			this.textboxIntermediateResultMode.TabIndex = 11;
			// 
			// IntermediateResultForm
			// 
			this.AcceptButton = this.buttonYes;
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.CancelButton = this.buttonNo;
			this.ClientSize = new System.Drawing.Size(343, 188);
			this.Controls.Add(this.textboxIntermediateResultMode);
			this.Controls.Add(this.labelIntermediateResultMode);
			this.Controls.Add(this.labelContinueTransaction);
			this.Controls.Add(this.textboxAuthorisedAmount);
			this.Controls.Add(this.labelAuthorisedAmount);
			this.Controls.Add(this.textboxIntermediateResult);
			this.Controls.Add(this.labelIntermediateResult);
			this.Controls.Add(this.textboxFinalTransactionAmount);
			this.Controls.Add(this.labelFinalTransactionAmount);
			this.Controls.Add(this.buttonNo);
			this.Controls.Add(this.buttonYes);
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
			this.MaximizeBox = false;
			this.MinimizeBox = false;
			this.Name = "IntermediateResultForm";
			this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
			this.Text = "Intermediate Result Received";
			this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.IntermediateResultForm_FormClosing);
			((System.ComponentModel.ISupportInitialize)(this.errorProvider)).EndInit();
			this.ResumeLayout(false);
			this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button buttonYes;
        private System.Windows.Forms.Button buttonNo;
        private System.Windows.Forms.Label labelFinalTransactionAmount;
        private System.Windows.Forms.TextBox textboxFinalTransactionAmount;
        private System.Windows.Forms.Label labelIntermediateResult;
        private System.Windows.Forms.TextBox textboxIntermediateResult;
        private System.Windows.Forms.TextBox textboxAuthorisedAmount;
        private System.Windows.Forms.Label labelAuthorisedAmount;
        private System.Windows.Forms.Label labelContinueTransaction;
        private System.Windows.Forms.ErrorProvider errorProvider;
		private System.Windows.Forms.Label labelIntermediateResultMode;
		private System.Windows.Forms.TextBox textboxIntermediateResultMode;
	}
}