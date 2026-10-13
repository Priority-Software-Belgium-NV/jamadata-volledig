// =========================================================================
// =========================== U T I L I T I E S ===========================
// =========================================================================
//
//		Module: Utilities
//		File  : LuhnCheck.cs
//		Author: rdem
//
//
//		Description:
//		Class providing Luhn check functionality.
//
//
//		Last Modification:
//		$Id:
//
// ----------------------------------------------------------------------------------------- 
//		Modifications:
//		Date		Author	Issue	Comment
//		2017-06-02	rdem			Initial version.
//
// ==========================================================================================
// (C) Chess pT  2015-2017
// ==========================================================================================

using System;
using System.Linq;

namespace Utilities
{
	/// <summary>
	/// Class providing Luhn check functionality.
	/// https://en.wikipedia.org/wiki/Luhn_algorithm
	/// </summary>
	public static class LuhnCheck
	{

		/// <summary>
		/// Perform Luhn check (modulus 10 algorithm) on a numeric string.
		/// 
		/// 1)	From the rightmost digit, which is the check digit, and moving left, double the value of every second digit.
		///		If the result of this doubling operation is greater than 9 (e.g., 8 × 2 = 16),
		///		then add the digits of the product (e.g., 16: 1 + 6 = 7, 18: 1 + 8 = 9)
		///		or alternatively subtract 9 from the product (e.g., 16: 16 - 9 = 7, 18: 18 - 9 = 9).
		/// 2)	Take the sum of all the digits.
		/// 3)	If the total modulo 10 is equal to 0 (if the total ends in zero) then the number is valid according to the Luhn formula,
		///		else it is not valid.
		///
		/// Example (the rightmost number is the check digit):
		///
		/// Account number		7	9	9	2	7	3	9	8	7	1	3
		/// Double every other	7	18	9	4	7	6	9	16	7	2	3
		/// Sum digits			7	9	9	4	7	6	9	7	7	2	3
		///
		/// The sum = 70. Modulo 10 of 70 is 0 thus the check succeeds.
		/// </summary>
		/// <param name="code">The code to check.</param>
		/// <returns>True when the Luhn check is OK.</returns>
		public static bool LuhnCheckMod10(string code)
		{
			// Exit if the string length is less than 2.
			if (code.Length < 2) return false;

			return code
				.Where(c => Char.IsDigit(c))			// Select only digits.
				.Reverse()								// Reverse the sequence since we count from the right for doubling the even position digits.
				.Select((c, p) => c - '0' << (p & 1))	// Double the even position digits.
				.Select(n => n > 9 ? n - 9 : n)			// When digit became larger than 9, subtract it from 9.
				.Sum()									// Sum the digits.
				% 10 == 0;								// Code correct when divisible by 10 (sum ends with '0').
		}


		/// <summary>
		/// Perform +1 modified Luhn check (modulus 10 algorithm plus 1) on a numeric string.
		/// This is a modified Luhn check where the check digit is incremented by 1.
		/// </summary>
		/// <param name="code">The code to check.</param>
		/// <returns>True when the Luhn check is OK.</returns>
		public static bool LuhnCheckMod10Plus1(string code)
		{
			// Exit if one or more digits are not numeric.
			foreach (char c in code)
			{
				if (!Char.IsDigit(c)) return false;
			}

			// Since the check digit was increased, decrement the check digit (last digit) before passing it to the regular Luhn check.
			// When check digit is zero (thus subtracting results in -1), the modified check digit becomes 9.
			string checkDigit = code.Substring(code.Length - 1);
			string decrementedCode = code.Substring(0, code.Length - 1);
			decrementedCode += checkDigit != "0" ? (Int32.Parse(checkDigit) - 1).ToString() : "9";
			return LuhnCheckMod10(decrementedCode);
		}
	}
}
