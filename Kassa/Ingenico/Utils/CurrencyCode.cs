// =========================================================================================
// =================================== U T I L I T I E S ===================================
// =========================================================================================
//
//		Module: ChessPt.Utilities
//		File  : CurrencyCode.cs
//		Author: Robert Demming
//
//		Description:
//		Enumeration for currency code and extension methods for the CurrencyCode enum.
//
//
//		Last Modification:
//		$Id: CurrencyCode.cs
//
// -------------------------------------------------------------------------
//		Modifications:
//		Date		Author	Issue	Comment
//		2016-06-15	rdem			Finished first version.
//
// =========================================================================================
// (C) Chess pT  2015-2017
// =========================================================================================



namespace Utilities
{
	/// <summary>
	/// Enumeration for currency code.
	/// </summary>
	public enum CurrencyCode
	{
		None,	// No currency given.
		JPY,	// Japanese Yen.
		GBP,	// Great Britain Pound.
		USD,	// United States Dollar.
		EUR,	// Euro.
	}


	/// <summary>
	/// Class providing currency code helper functions/extension methods.
	/// </summary>
	public static class CurrencyCodeExtensions
	{
		/// <summary>
		/// Create a currency code enum from an int value.
		/// </summary>
		/// <param name="code">The ISO currency code.</param>
		/// <returns>The currency code enum.</returns>
		public static CurrencyCode Create(ushort code)
		{
			switch (code)
			{
				case 0:
					return CurrencyCode.None;

				case 392:
					return CurrencyCode.JPY;

				case 826:
					return CurrencyCode.GBP;

				case 840:
					return CurrencyCode.USD;

				case 978:
					return CurrencyCode.EUR;

				default:
					return CurrencyCode.None;
			}
		}


		/// <summary>
		/// Convert currency enum to currency sign.
		/// </summary>
		/// <returns>The currency sign.</returns>
		public static string ToCurrencySign(this CurrencyCode currencyCode)
		{
			switch (currencyCode)
			{
				case CurrencyCode.None:
					return "";

				case CurrencyCode.JPY:
					return "¥";

				case CurrencyCode.GBP:
					return "£";

				case CurrencyCode.USD:
					return "$";

				case CurrencyCode.EUR:
					return "€";

				default:
					return "";
			}
		}

	}
}
