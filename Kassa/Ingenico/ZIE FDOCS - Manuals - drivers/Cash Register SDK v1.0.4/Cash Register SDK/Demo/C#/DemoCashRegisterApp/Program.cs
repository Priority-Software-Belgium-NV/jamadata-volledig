// =========================================================================================
// ======================== T E L I U M   C A S H   R E G I S T E R ========================
// =========================================================================================
//
//		Module: CashRegister
//		File  : Program.cs
//		Author: rdem
//
//
//		Description:
//		Entry point of the cash register application.
//
//
//		Last Modification:
//		$Id:
//
// ----------------------------------------------------------------------------------------- 
//		Modifications:
//		Date		Author	Issue	Comment
//
//
// ==========================================================================================
// (C) Chess pT  2015-2017
// ==========================================================================================


using System;
using System.Windows.Forms;

namespace ChessPt.CashRegister
{
	/// <summary>
	/// Entry point of the cash register application.
	/// </summary>
	static class Program
	{
		/// <summary>
		/// The main entry point for the application.
		/// </summary>
		[STAThread]
		static void Main()
		{
			// Upgrade settings in case of new version of the application (The program runs for the first time).
			Properties.Settings.Default.UpgradeSettings();

			Application.EnableVisualStyles();
			Application.SetCompatibleTextRenderingDefault(false);
			Application.Run(new Forms.MainForm());
		}
	}
}
