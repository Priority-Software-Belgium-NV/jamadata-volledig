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
//		Form for handling the input of addresses in transparent mode.
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
using System.Windows.Forms;

namespace ChessPt.CashRegister.Forms
{
	public partial class TmAddressInputForm : Form
	{
		private ushort mAddress;
		private ushort mDataSize;


		/// <summary>
		/// Default constructor.
		/// </summary>
		public TmAddressInputForm()
		{
			InitializeComponent();
		}


		/// <summary>
		/// Access the address.
		/// </summary>
		public ushort Address
		{
			get { return mAddress; }
		}


		/// <summary>
		///  Access the data size.
		/// </summary>
		public ushort DataSize
		{
			get { return mDataSize;  }
		}


		/// <summary>
		/// The form is closing. Check the input.
		/// </summary>
		/// <param name="sender">The sender of the event.</param>
		/// <param name="e">The event arguments.</param>
		private void AddressInputForm_FormClosing(object sender, FormClosingEventArgs e)
		{
			// When form is closign because of a cancel, exit.
			if (this.DialogResult == DialogResult.Cancel) return;

			// Parse address.
			if (!UInt16.TryParse(textboxAddress.Text, out mAddress))
			{
				errorProvider.SetError(textboxAddress, "Can't parse 'address'");
				e.Cancel = true;
			}

			// Parse data size
			if (!UInt16.TryParse(textboxDataSize.Text, out mDataSize))
			{
				errorProvider.SetError(textboxDataSize, "Can't parse 'data size'");
				e.Cancel = true;
			}
		}
	}
}
