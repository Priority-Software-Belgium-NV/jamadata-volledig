// =========================================================================================
// =================================== U T I L I T I E S ===================================
// =========================================================================================
//
//		Module: Utilities.Forms
//		File  : InputDialog.cs
//		Author: rdem
//
//
//		Description:
//		Generic input dialog.
//
//
//		Last Modification:
//		$Id:
//
// -----------------------------------------------------------------------------------------
//		Modifications:
//		Date		Author	Issue	Comment
//
// =========================================================================================
// (C) Chess pT  2015-2017
// =========================================================================================

using System.Windows.Forms;

namespace ChessPt.Utilities.Forms
{
	/// <summary>
	/// Generic input dialog.
	/// </summary>
	public partial class InputDialog : Form
	{
		/// <summary>
		/// Show the input dialog.
		/// </summary>
		/// <param name="message">The message in the dialog.</param>
		/// <param name="title">The title of the dialog.</param>
		/// <param name="input">The dialog input.</param>
		/// <returns>The dialog result.</returns>
		public static DialogResult Show(string message, string title, out string input)
		{
			// Create the dialog and show it.
			InputDialog dlg = new InputDialog(message, title);
			DialogResult result = dlg.ShowDialog();

			// Get the entered text if OK was pressed.
			if (result == DialogResult.OK)
			{
				input = dlg.txtInput.Text;
			}
			else
			{
				input = "";
			}

			return result;
		}


		/// <summary>
		/// Create the input dialog box.
		/// </summary>
		/// <param name="message">The </param>
		/// <param name="title"></param>
		public InputDialog(string message, string title)
		{
			InitializeComponent();

			// Set the dialog title and message text.
			lblMessage.Text = message;
			this.Text = title;
		}


	}
}
