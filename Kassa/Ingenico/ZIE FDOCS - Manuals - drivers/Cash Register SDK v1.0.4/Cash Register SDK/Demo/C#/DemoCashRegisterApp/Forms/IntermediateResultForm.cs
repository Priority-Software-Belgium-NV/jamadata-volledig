// =========================================================================================
// ======================== T E L I U M   C A S H   R E G I S T E R ========================
// =========================================================================================
//
//		Module: Forms
//		File  : IntermediateResultForm.cs
//		Author: rdem
//
//
//		Description:
//		Form for handling the intermediate result.
//
//
//		Last Modification:
//		$Id:
//
// -----------------------------------------------------------------------------------------
//		Modifications:
//		Date		Author	Issue	Comment
//		2017-09-15	rdem			Added intermediate result mode handling.
//
// =========================================================================================
// (C) Chess pT  2015-2017
// =========================================================================================


using System;
using System.Windows.Forms;


namespace ChessPt.CashRegister.Forms
{
	/// <summary>
	/// Form for handling the intermediate result.
	/// </summary>
	public partial class IntermediateResultForm: System.Windows.Forms.Form
	{
		private uint mFinalTransactionAmount;

		/// <summary>
		/// Constructor with transaction result and authorised amount.
		/// </summary>
		/// <param name="transactionResult">The transaction result.</param>
		/// <param name="authorisedAmount">The authorised amount.</param>
		/// <param name="finalTransactionAmount">The initial final transaction amount.</param>
		internal IntermediateResultForm(TlvLib.TransactionResult transactionResult, uint authorisedAmount, uint finalTransactionAmount, TlvLib.IntermediateResultMode intermediateResultMode)
		{
			InitializeComponent();

			// Fill text boxes.
			textboxIntermediateResultMode.Text = intermediateResultMode.ToString();
			textboxIntermediateResult.Text = transactionResult.ToString();
			textboxAuthorisedAmount.Text = authorisedAmount.ToString();
			textboxFinalTransactionAmount.Text = finalTransactionAmount.ToString();

			// Disable OK button when intermediate result mode is "NoResponse".
			if (intermediateResultMode == TlvLib.IntermediateResultMode.IntermediateResultNoResponse)
			{
				buttonYes.Visible = false;
				labelContinueTransaction.Visible = false;
				buttonNo.Text = "OK";
			}

			// Deferred payment or regular payment with IntermediateResultForm result.
			if (authorisedAmount == 0)
			{
				textboxAuthorisedAmount.Visible = false;
				labelAuthorisedAmount.Visible = false;
				textboxFinalTransactionAmount.Visible = false;
				labelFinalTransactionAmount.Visible = false;
			}
		}


		/// <summary>
		/// Access the final transaction amount.
		/// </summary>
		public uint FinalTransactionAmount
		{
			get
			{
				return mFinalTransactionAmount;
			}
		}


		/// <summary>
		/// Called when the form is closing.
		/// Check the final transaction amount.
		/// </summary>
		/// <param name="sender">The sender of the event.</param>
		/// <param name="e">The event arguments.</param>
		private void IntermediateResultForm_FormClosing(object sender, FormClosingEventArgs e)
		{
			// When form is closign because of a cancel, exit.
			if (this.DialogResult == DialogResult.Cancel) return;

			uint finalTransactionAmount;
			if (UInt32.TryParse(textboxFinalTransactionAmount.Text, out finalTransactionAmount) == false)
			{
				errorProvider.SetError(textboxFinalTransactionAmount, "Invalid amount");
				e.Cancel = true;
			}
			else mFinalTransactionAmount = (uint)finalTransactionAmount;
		}


		/// <summary>
		/// Called when final transaction amount field is left.
		/// Check the final transaction amount.
		/// </summary>
		/// <param name="sender">The sender of the event.</param>
		/// <param name="e">The event arguments.</param>
		private void txtFinalTransactionAmount_Leave(object sender, EventArgs e)
		{
			uint finalTransactionAmount;
			if (UInt32.TryParse(textboxFinalTransactionAmount.Text, out finalTransactionAmount) == false)
			{
				errorProvider.SetError(textboxFinalTransactionAmount, "Invalid amount");
			}
		}
	}
}
