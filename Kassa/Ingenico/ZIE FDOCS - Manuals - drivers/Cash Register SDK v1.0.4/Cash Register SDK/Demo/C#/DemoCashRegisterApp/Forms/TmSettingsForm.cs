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
//		Form for transparent mode settings.
//
//
//		Last Modification:
//		$Id:
//
// -----------------------------------------------------------------------------------------
//		Modifications:
//		Date		Author	Issue	Comment
//		2017-10-13	rdem			Initial version.
//
// =========================================================================================
// (C) Chess pT  2015-2017
// =========================================================================================


using System;
using System.Windows.Forms;

namespace ChessPt.CashRegister.Forms
{
	public partial class TmSettingsForm : Form
	{
		public TmSettingsForm()
		{
			InitializeComponent();

			// Fill the card detection time-out.
			numCardDetectionTimeout.Value = Properties.Settings.Default.TmCardDetectionTimeout;

			// Fill the dealer ID.
			textboxDealerId.Text = Properties.Settings.Default.TmDealerId;

			// Fill the key generation secret.
			textboxKeyGenSecret.Text = Properties.Settings.Default.TmKeyGenSecret;

			// Fill the card keys.
			foreach (string entry in Properties.Settings.Default.TmCardKeys)
			{
				// Split the string in card UID and key.
				int index = entry.IndexOf(';');
				if (index > 0)
				{
					string cardUid = entry.Substring(0, index);
					string cardKey = entry.Substring(index + 1);

					datagridCardKeys.Rows.Add(cardUid, cardKey);
				}
			}
		}


		/// <summary>
		/// The "OK" button was clicked. Store settings.
		/// </summary>
		/// <param name="sender">The sender of the event.</param>
		/// <param name="e">The event arguments.</param>
		private void buttonOk_Click(object sender, EventArgs e)
		{
			string hexConversionErrorString = "Not a correct hex string";

			// Check secret.
			bool error = false;
			try
			{
				byte[] secret = Utilities.Conversions.HexStringToByteArray(textboxKeyGenSecret.Text);
				textboxKeyGenSecret.Text = Utilities.Conversions.ByteArrayToHexString(secret, "-");
				errorProvider.SetError(textboxKeyGenSecret, null);
			}
			catch (Exception)
			{
				errorProvider.SetError(textboxKeyGenSecret, hexConversionErrorString);
				error = true;
			}

			// Check the card UID/key pairs.
			DataGridViewRow lastRow = datagridCardKeys.Rows[datagridCardKeys.Rows.Count - 1];
			foreach (DataGridViewRow row in datagridCardKeys.Rows)
			{
				foreach (DataGridViewCell cell in row.Cells)
				{
					// Do not check the last row because it is the empty row the user can add.
					if (row == lastRow) continue;

					// Check all cells in the row.
					try
					{
						byte[] value = Utilities.Conversions.HexStringToByteArray(cell.Value as string);
						cell.Value = Utilities.Conversions.ByteArrayToHexString(value, "-");
						cell.ErrorText = null;
					}
					catch
					{
						cell.ErrorText = hexConversionErrorString;
						error = true;
					}
				}
			}

			// Exit if there were errors (do not close window).
			if (error) return;


			/* Store the data. */

			// Store the card UID/key pairs.
			System.Collections.Specialized.StringCollection collectionCardUidKey = new System.Collections.Specialized.StringCollection();
			foreach (DataGridViewRow row in datagridCardKeys.Rows)
			{
				// Do not check the last row because it is the empty row the user can add.
				if (row == lastRow) continue;

				collectionCardUidKey.Add((row.Cells[0].Value as string) + ";" + (row.Cells[1].Value as string));
			}
			Properties.Settings.Default.TmCardKeys = collectionCardUidKey;


			// Store the card detection time-out.
			Properties.Settings.Default.TmCardDetectionTimeout = (short)numCardDetectionTimeout.Value;

			// Store the dealer ID.
			Properties.Settings.Default.TmDealerId = textboxDealerId.Text;

			// Store the key generation secret.
			Properties.Settings.Default.TmKeyGenSecret = textboxKeyGenSecret.Text;

			// Save the settings and close the form.
			Properties.Settings.Default.Save();
			Close();
		}
	}
}
