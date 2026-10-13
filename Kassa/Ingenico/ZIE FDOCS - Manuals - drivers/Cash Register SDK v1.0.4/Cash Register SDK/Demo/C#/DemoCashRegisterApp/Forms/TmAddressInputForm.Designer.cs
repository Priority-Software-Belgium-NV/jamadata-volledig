namespace ChessPt.CashRegister.Forms
{
	partial class TmAddressInputForm
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
			this.labelAddress = new System.Windows.Forms.Label();
			this.labelDataSize = new System.Windows.Forms.Label();
			this.textboxAddress = new System.Windows.Forms.TextBox();
			this.textboxDataSize = new System.Windows.Forms.TextBox();
			this.buttonOk = new System.Windows.Forms.Button();
			this.buttonCancel = new System.Windows.Forms.Button();
			this.errorProvider = new System.Windows.Forms.ErrorProvider(this.components);
			((System.ComponentModel.ISupportInitialize)(this.errorProvider)).BeginInit();
			this.SuspendLayout();
			// 
			// labelAddress
			// 
			this.labelAddress.AutoSize = true;
			this.labelAddress.Location = new System.Drawing.Point(12, 19);
			this.labelAddress.Name = "labelAddress";
			this.labelAddress.Size = new System.Drawing.Size(45, 13);
			this.labelAddress.TabIndex = 0;
			this.labelAddress.Text = "Address";
			// 
			// labelDataSize
			// 
			this.labelDataSize.AutoSize = true;
			this.labelDataSize.Location = new System.Drawing.Point(12, 45);
			this.labelDataSize.Name = "labelDataSize";
			this.labelDataSize.Size = new System.Drawing.Size(51, 13);
			this.labelDataSize.TabIndex = 1;
			this.labelDataSize.Text = "Data size";
			// 
			// textboxAddress
			// 
			this.textboxAddress.Location = new System.Drawing.Point(78, 16);
			this.textboxAddress.Name = "textboxAddress";
			this.textboxAddress.Size = new System.Drawing.Size(115, 20);
			this.textboxAddress.TabIndex = 2;
			this.textboxAddress.Text = "0";
			// 
			// textboxDataSize
			// 
			this.textboxDataSize.Location = new System.Drawing.Point(78, 42);
			this.textboxDataSize.Name = "textboxDataSize";
			this.textboxDataSize.Size = new System.Drawing.Size(115, 20);
			this.textboxDataSize.TabIndex = 3;
			this.textboxDataSize.Text = "16";
			// 
			// buttonOk
			// 
			this.buttonOk.DialogResult = System.Windows.Forms.DialogResult.OK;
			this.buttonOk.Location = new System.Drawing.Point(37, 98);
			this.buttonOk.Name = "buttonOk";
			this.buttonOk.Size = new System.Drawing.Size(75, 23);
			this.buttonOk.TabIndex = 4;
			this.buttonOk.Text = "OK";
			this.buttonOk.UseVisualStyleBackColor = true;
			// 
			// buttonCancel
			// 
			this.buttonCancel.DialogResult = System.Windows.Forms.DialogResult.Cancel;
			this.buttonCancel.Location = new System.Drawing.Point(118, 98);
			this.buttonCancel.Name = "buttonCancel";
			this.buttonCancel.Size = new System.Drawing.Size(75, 23);
			this.buttonCancel.TabIndex = 5;
			this.buttonCancel.Text = "Cancel";
			this.buttonCancel.UseVisualStyleBackColor = true;
			// 
			// errorProvider
			// 
			this.errorProvider.ContainerControl = this;
			// 
			// AddressInputForm
			// 
			this.AcceptButton = this.buttonOk;
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.CancelButton = this.buttonCancel;
			this.ClientSize = new System.Drawing.Size(205, 128);
			this.Controls.Add(this.buttonCancel);
			this.Controls.Add(this.buttonOk);
			this.Controls.Add(this.textboxDataSize);
			this.Controls.Add(this.textboxAddress);
			this.Controls.Add(this.labelDataSize);
			this.Controls.Add(this.labelAddress);
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
			this.MaximizeBox = false;
			this.MinimizeBox = false;
			this.Name = "AddressInputForm";
			this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
			this.Text = "Enter adress/size";
			this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.AddressInputForm_FormClosing);
			((System.ComponentModel.ISupportInitialize)(this.errorProvider)).EndInit();
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.Label labelAddress;
		private System.Windows.Forms.Label labelDataSize;
		private System.Windows.Forms.TextBox textboxAddress;
		private System.Windows.Forms.TextBox textboxDataSize;
		private System.Windows.Forms.Button buttonOk;
		private System.Windows.Forms.Button buttonCancel;
		private System.Windows.Forms.ErrorProvider errorProvider;
	}
}