namespace ChessPt.CashRegister.Forms
{
	partial class TmUiControlForm
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
			this.labelDisplayText = new System.Windows.Forms.Label();
			this.textboxDisplayText = new System.Windows.Forms.TextBox();
			this.groupboxBeepType = new System.Windows.Forms.GroupBox();
			this.radiobuttonBeepType_None = new System.Windows.Forms.RadioButton();
			this.radiobuttonBeepType_Failure = new System.Windows.Forms.RadioButton();
			this.radiobuttonBeepType_Attention = new System.Windows.Forms.RadioButton();
			this.radiobuttonBeepType_Success = new System.Windows.Forms.RadioButton();
			this.groupboxLedControl = new System.Windows.Forms.GroupBox();
			this.checkboxLedControl = new System.Windows.Forms.CheckBox();
			this.checkboxLedControl_Led2 = new System.Windows.Forms.CheckBox();
			this.checkboxLedControl_Led3 = new System.Windows.Forms.CheckBox();
			this.checkboxLedControl_Led4 = new System.Windows.Forms.CheckBox();
			this.checkboxLedControl_Led1 = new System.Windows.Forms.CheckBox();
			this.buttonCancel = new System.Windows.Forms.Button();
			this.buttonOk = new System.Windows.Forms.Button();
			this.groupboxBeepType.SuspendLayout();
			this.groupboxLedControl.SuspendLayout();
			this.SuspendLayout();
			// 
			// labelDisplayText
			// 
			this.labelDisplayText.AutoSize = true;
			this.labelDisplayText.Location = new System.Drawing.Point(12, 9);
			this.labelDisplayText.Name = "labelDisplayText";
			this.labelDisplayText.Size = new System.Drawing.Size(61, 13);
			this.labelDisplayText.TabIndex = 0;
			this.labelDisplayText.Text = "Display text";
			// 
			// textboxDisplayText
			// 
			this.textboxDisplayText.Location = new System.Drawing.Point(79, 6);
			this.textboxDisplayText.Multiline = true;
			this.textboxDisplayText.Name = "textboxDisplayText";
			this.textboxDisplayText.Size = new System.Drawing.Size(199, 63);
			this.textboxDisplayText.TabIndex = 1;
			this.textboxDisplayText.Text = "Hello World\r\nLine 2\r\nLine 3\r\nLine 4";
			// 
			// groupboxBeepType
			// 
			this.groupboxBeepType.Controls.Add(this.radiobuttonBeepType_None);
			this.groupboxBeepType.Controls.Add(this.radiobuttonBeepType_Failure);
			this.groupboxBeepType.Controls.Add(this.radiobuttonBeepType_Attention);
			this.groupboxBeepType.Controls.Add(this.radiobuttonBeepType_Success);
			this.groupboxBeepType.Location = new System.Drawing.Point(12, 75);
			this.groupboxBeepType.Name = "groupboxBeepType";
			this.groupboxBeepType.Size = new System.Drawing.Size(266, 120);
			this.groupboxBeepType.TabIndex = 2;
			this.groupboxBeepType.TabStop = false;
			this.groupboxBeepType.Text = "Beep type";
			// 
			// radiobuttonBeepType_None
			// 
			this.radiobuttonBeepType_None.AutoSize = true;
			this.radiobuttonBeepType_None.Checked = true;
			this.radiobuttonBeepType_None.Location = new System.Drawing.Point(6, 19);
			this.radiobuttonBeepType_None.Name = "radiobuttonBeepType_None";
			this.radiobuttonBeepType_None.Size = new System.Drawing.Size(51, 17);
			this.radiobuttonBeepType_None.TabIndex = 7;
			this.radiobuttonBeepType_None.TabStop = true;
			this.radiobuttonBeepType_None.Text = "None";
			this.radiobuttonBeepType_None.UseVisualStyleBackColor = true;
			// 
			// radiobuttonBeepType_Failure
			// 
			this.radiobuttonBeepType_Failure.AutoSize = true;
			this.radiobuttonBeepType_Failure.Location = new System.Drawing.Point(6, 65);
			this.radiobuttonBeepType_Failure.Name = "radiobuttonBeepType_Failure";
			this.radiobuttonBeepType_Failure.Size = new System.Drawing.Size(56, 17);
			this.radiobuttonBeepType_Failure.TabIndex = 6;
			this.radiobuttonBeepType_Failure.Text = "Failure";
			this.radiobuttonBeepType_Failure.UseVisualStyleBackColor = true;
			// 
			// radiobuttonBeepType_Attention
			// 
			this.radiobuttonBeepType_Attention.AutoSize = true;
			this.radiobuttonBeepType_Attention.Location = new System.Drawing.Point(6, 88);
			this.radiobuttonBeepType_Attention.Name = "radiobuttonBeepType_Attention";
			this.radiobuttonBeepType_Attention.Size = new System.Drawing.Size(67, 17);
			this.radiobuttonBeepType_Attention.TabIndex = 5;
			this.radiobuttonBeepType_Attention.Text = "Attention";
			this.radiobuttonBeepType_Attention.UseVisualStyleBackColor = true;
			// 
			// radiobuttonBeepType_Success
			// 
			this.radiobuttonBeepType_Success.AutoSize = true;
			this.radiobuttonBeepType_Success.Location = new System.Drawing.Point(6, 42);
			this.radiobuttonBeepType_Success.Name = "radiobuttonBeepType_Success";
			this.radiobuttonBeepType_Success.Size = new System.Drawing.Size(66, 17);
			this.radiobuttonBeepType_Success.TabIndex = 4;
			this.radiobuttonBeepType_Success.Text = "Success";
			this.radiobuttonBeepType_Success.UseVisualStyleBackColor = true;
			// 
			// groupboxLedControl
			// 
			this.groupboxLedControl.Controls.Add(this.checkboxLedControl);
			this.groupboxLedControl.Controls.Add(this.checkboxLedControl_Led2);
			this.groupboxLedControl.Controls.Add(this.checkboxLedControl_Led3);
			this.groupboxLedControl.Controls.Add(this.checkboxLedControl_Led4);
			this.groupboxLedControl.Controls.Add(this.checkboxLedControl_Led1);
			this.groupboxLedControl.Location = new System.Drawing.Point(12, 201);
			this.groupboxLedControl.Name = "groupboxLedControl";
			this.groupboxLedControl.Size = new System.Drawing.Size(266, 121);
			this.groupboxLedControl.TabIndex = 3;
			this.groupboxLedControl.TabStop = false;
			// 
			// checkboxLedControl
			// 
			this.checkboxLedControl.AutoSize = true;
			this.checkboxLedControl.Location = new System.Drawing.Point(6, 0);
			this.checkboxLedControl.Name = "checkboxLedControl";
			this.checkboxLedControl.Size = new System.Drawing.Size(83, 17);
			this.checkboxLedControl.TabIndex = 8;
			this.checkboxLedControl.Text = "LED Control";
			this.checkboxLedControl.UseVisualStyleBackColor = true;
			this.checkboxLedControl.CheckedChanged += new System.EventHandler(this.checkboxLedControl_CheckedChanged);
			// 
			// checkboxLedControl_Led2
			// 
			this.checkboxLedControl_Led2.AutoSize = true;
			this.checkboxLedControl_Led2.Location = new System.Drawing.Point(17, 46);
			this.checkboxLedControl_Led2.Name = "checkboxLedControl_Led2";
			this.checkboxLedControl_Led2.Size = new System.Drawing.Size(56, 17);
			this.checkboxLedControl_Led2.TabIndex = 7;
			this.checkboxLedControl_Led2.Text = "LED 2";
			this.checkboxLedControl_Led2.UseVisualStyleBackColor = true;
			// 
			// checkboxLedControl_Led3
			// 
			this.checkboxLedControl_Led3.AutoSize = true;
			this.checkboxLedControl_Led3.Location = new System.Drawing.Point(17, 69);
			this.checkboxLedControl_Led3.Name = "checkboxLedControl_Led3";
			this.checkboxLedControl_Led3.Size = new System.Drawing.Size(56, 17);
			this.checkboxLedControl_Led3.TabIndex = 6;
			this.checkboxLedControl_Led3.Text = "LED 3";
			this.checkboxLedControl_Led3.UseVisualStyleBackColor = true;
			// 
			// checkboxLedControl_Led4
			// 
			this.checkboxLedControl_Led4.AutoSize = true;
			this.checkboxLedControl_Led4.Location = new System.Drawing.Point(17, 92);
			this.checkboxLedControl_Led4.Name = "checkboxLedControl_Led4";
			this.checkboxLedControl_Led4.Size = new System.Drawing.Size(56, 17);
			this.checkboxLedControl_Led4.TabIndex = 5;
			this.checkboxLedControl_Led4.Text = "LED 4";
			this.checkboxLedControl_Led4.UseVisualStyleBackColor = true;
			// 
			// checkboxLedControl_Led1
			// 
			this.checkboxLedControl_Led1.AutoSize = true;
			this.checkboxLedControl_Led1.Location = new System.Drawing.Point(17, 23);
			this.checkboxLedControl_Led1.Name = "checkboxLedControl_Led1";
			this.checkboxLedControl_Led1.Size = new System.Drawing.Size(56, 17);
			this.checkboxLedControl_Led1.TabIndex = 4;
			this.checkboxLedControl_Led1.Text = "LED 1";
			this.checkboxLedControl_Led1.UseVisualStyleBackColor = true;
			// 
			// buttonCancel
			// 
			this.buttonCancel.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
			this.buttonCancel.DialogResult = System.Windows.Forms.DialogResult.Cancel;
			this.buttonCancel.Location = new System.Drawing.Point(203, 336);
			this.buttonCancel.Name = "buttonCancel";
			this.buttonCancel.Size = new System.Drawing.Size(75, 23);
			this.buttonCancel.TabIndex = 7;
			this.buttonCancel.Text = "Cancel";
			this.buttonCancel.UseVisualStyleBackColor = true;
			// 
			// buttonOk
			// 
			this.buttonOk.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
			this.buttonOk.DialogResult = System.Windows.Forms.DialogResult.OK;
			this.buttonOk.Location = new System.Drawing.Point(122, 336);
			this.buttonOk.Name = "buttonOk";
			this.buttonOk.Size = new System.Drawing.Size(75, 23);
			this.buttonOk.TabIndex = 6;
			this.buttonOk.Text = "OK";
			this.buttonOk.UseVisualStyleBackColor = true;
			// 
			// TmUiControlForm
			// 
			this.AcceptButton = this.buttonOk;
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.CancelButton = this.buttonCancel;
			this.ClientSize = new System.Drawing.Size(290, 371);
			this.Controls.Add(this.buttonCancel);
			this.Controls.Add(this.buttonOk);
			this.Controls.Add(this.groupboxLedControl);
			this.Controls.Add(this.groupboxBeepType);
			this.Controls.Add(this.textboxDisplayText);
			this.Controls.Add(this.labelDisplayText);
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
			this.MaximizeBox = false;
			this.MinimizeBox = false;
			this.Name = "TmUiControlForm";
			this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
			this.Text = "UI Control";
			this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.TmUiControlForm_FormClosing);
			this.groupboxBeepType.ResumeLayout(false);
			this.groupboxBeepType.PerformLayout();
			this.groupboxLedControl.ResumeLayout(false);
			this.groupboxLedControl.PerformLayout();
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.Label labelDisplayText;
		private System.Windows.Forms.TextBox textboxDisplayText;
		private System.Windows.Forms.GroupBox groupboxBeepType;
		private System.Windows.Forms.RadioButton radiobuttonBeepType_Failure;
		private System.Windows.Forms.RadioButton radiobuttonBeepType_Attention;
		private System.Windows.Forms.RadioButton radiobuttonBeepType_Success;
		private System.Windows.Forms.GroupBox groupboxLedControl;
		private System.Windows.Forms.CheckBox checkboxLedControl_Led2;
		private System.Windows.Forms.CheckBox checkboxLedControl_Led3;
		private System.Windows.Forms.CheckBox checkboxLedControl_Led4;
		private System.Windows.Forms.CheckBox checkboxLedControl_Led1;
		private System.Windows.Forms.Button buttonCancel;
		private System.Windows.Forms.Button buttonOk;
		private System.Windows.Forms.RadioButton radiobuttonBeepType_None;
		private System.Windows.Forms.CheckBox checkboxLedControl;
	}
}