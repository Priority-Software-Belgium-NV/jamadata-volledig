// =========================================================================================
// ======================== T E L I U M   C A S H   R E G I S T E R ========================
// =========================================================================================
//
//		Module: Forms
//		File  : TmUiControlForm.cs
//		Author: rdem
//
//
//		Description:
//		Form for handling the input of UI control settings in transparent mode.
//
//
//		Last Modification:
//		$Id:
//
// -----------------------------------------------------------------------------------------
//		Modifications:
//		Date		Author	Issue	Comment
//		2017-09-11	rdem			Initial version.
//
// =========================================================================================
// (C) Chess pT  2015-2017
// =========================================================================================


using System;
using System.Drawing;
using System.Windows.Forms;

namespace ChessPt.CashRegister.Forms
{
	/// <summary>
	/// Form for entering transparent mode UI control data.
	/// </summary>
	public partial class TmUiControlForm : Form
	{
		private string mDisplayText;
		private TlvLib.TmBeepType? mBeepType;
		private TlvLib.TmLedControl? mLedControl;

		public TmUiControlForm()
		{
			InitializeComponent();

			// Ensure the LED control checkbox is outside the LED control group box.
			if (checkboxLedControl.Parent == groupboxLedControl)
			{
				// Reparent the LED control checkbox so it's not in the LED control groupbox.
				groupboxLedControl.Parent.Controls.Add(checkboxLedControl);

				// Set the LED control checkbox position position.
				checkboxLedControl.Location = new Point(checkboxLedControl.Left + groupboxLedControl.Left, checkboxLedControl.Top + groupboxLedControl.Top);

				// Move the CheckBox to the top of the stacking order.
				checkboxLedControl.BringToFront();
			}

			// Set the LED control group box state.
			groupboxLedControl.Enabled = checkboxLedControl.Checked;
		}

		/// <summary>
		/// The form is closing. Store entered data.
		/// </summary>
		/// <param name="sender">The sender of the event.</param>
		/// <param name="e">The event arguments.</param>
		private void TmUiControlForm_FormClosing(object sender, FormClosingEventArgs e)
		{
			// Exit if dialog closed because of cancel button.
			if (this.DialogResult == DialogResult.Cancel) return;

			// Store the entered data.

			// Store diplay text (replace \r\n with \n).
			mDisplayText = textboxDisplayText.Text.Replace("\r\n", "\n"); ;

			// Store beep type.
			if (radiobuttonBeepType_None.Checked) mBeepType = null;
			else if (radiobuttonBeepType_Success.Checked) mBeepType = TlvLib.TmBeepType.Success;
			else if (radiobuttonBeepType_Failure.Checked) mBeepType = TlvLib.TmBeepType.Failure;
			else if (radiobuttonBeepType_Attention.Checked) mBeepType = TlvLib.TmBeepType.Attention;

			// Store LED control.
			mLedControl = null;
			if (checkboxLedControl.Checked)
			{
				mLedControl = TlvLib.TmLedControl.None;
				if (checkboxLedControl_Led1.Checked) mLedControl |= TlvLib.TmLedControl.Led1;
				if (checkboxLedControl_Led2.Checked) mLedControl |= TlvLib.TmLedControl.Led2;
				if (checkboxLedControl_Led3.Checked) mLedControl |= TlvLib.TmLedControl.Led3;
				if (checkboxLedControl_Led4.Checked) mLedControl |= TlvLib.TmLedControl.Led4;
			}
		}


		/// <summary>
		/// The LED control checkbox changed, enable other LED control controls.
		/// </summary>
		/// <param name="sender">The sender of the event.</param>
		/// <param name="e">The event arguments.</param>
		private void checkboxLedControl_CheckedChanged(object sender, EventArgs e)
		{
			groupboxLedControl.Enabled = checkboxLedControl.Checked;
		}

		/// <summary>
		/// Access the diplay text.
		/// </summary>
		public string DisplayText
		{
			get { return mDisplayText; }
		}


		/// <summary>
		/// Access the beep type.
		/// </summary>
		public TlvLib.TmBeepType? BeepType
		{
			get { return mBeepType; }
		}


		/// <summary>
		/// Access the LED control.
		/// </summary>
		public TlvLib.TmLedControl? LedControl
		{
			get { return mLedControl; }
		}


	}
}
