// =========================================================================================
// =================================== U T I L I T I E S ===================================
// =========================================================================================
//
//		Module: Utilities
//		File  : Conversions.cs
//		Author: rdem
//
//		Description:
//		Class with numeric conversion functions.
//
//
//		Last Modification:
//		$Id:
//
// -------------------------------------------------------------------------
//		Modifications:
//		Date		Author	Issue	Comment
//		2017-10-12	rdem			Added HexStringToByteArray() and ByteArrayToHexString() functions.
//		2017-08-29	rdem			Fixed BcdToUInt32() and BcdToUInt64() that were returing 16-bit integers.
//
// =========================================================================================
// (C) Chess pT  2015-2017
// =========================================================================================


namespace ChessPt.Utilities
{
	/// <summary>
	/// Class with numeric conversion functions.
	/// </summary>
	public static class Conversions
	{
		// -- Integer type to big-endian coded integer conversions ---

		/// <summary>
		/// Convert a 16-bit unsigned integer into a number of bytes stored into an array (big endian coded).
		/// </summary>
		/// <param name="value">The integer to convert [0, 0xFF FF].</param>
		/// <param name="size">Number of bytes to use in buffer [0, 2]. No problem if longer (prepends additional 0x00 bytes).</param>
		/// <returns>The resulting byte array.</returns>
		public static byte[] UInt16ToHex(ushort value, int size = 2)
		{
			// Delegate to Uint64 version.
			return UInt64ToHex(value, size);
		}


		/// <summary>
		/// Convert a 32-bit unsigned integer into a number of bytes stored into an array (big endian coded).
		/// </summary>
		/// <param name="value">The integer to convert [0, 0xFF FF FF FF].</param>
		/// <param name="size">Number of bytes to use in buffer [0, 4]. No problem if longer (prepends additional 0x00 bytes).</param>
		/// <returns>The resulting byte array.</returns>
		public static byte[] UInt32ToHex(uint value, int size = 4)
		{
			// Delegate to Uint64 version.
			return UInt64ToHex(value, size);
		}

		
		/// <summary>
		/// Convert a 64-bit unsigned integer into a number of bytes stored into an array (big endian coded).
		/// </summary>
		/// <param name="value">The integer to convert [0, 0xFF FF FF FF FF FF FF FF].</param>
		/// <param name="size">Number of bytes to use in buffer [0, 8]. No problem if longer (prepends additional 0x00 bytes).</param>
		/// <returns>The resulting byte array.</returns>
		public static byte[] UInt64ToHex(ulong value, int size = 8)
		{
			byte[] result = new byte[size];
			for (int i = size - 1; i >= 0; --i)
			{
				result[i] = (byte)value;	// Store the last 8 bits from the value in the buffer.
				value >>= 8;				// Next 8 bits byte from the value.
			}

			return result;
		}


		/// <summary>
		/// Convert a number of bytes (big endian coded) into a 16-bit unsigned integer. 
		/// When the given size is too big it will be truncated to the max possible number of bytes (2).
		/// </summary>
		/// <param name="data">Array of bytes containing the input.</param>
		/// <param name="size">The number of bytes from the buffer to convert [0, 2].</param>
		/// <returns>The resulting 16-bit integer [0, 0xFF FF].</returns>
		public static ushort HexToUInt16(byte[] data, int size = 2)
		{
			// Limit size to 2.
			if (size > 2)
			{
				size = 2;
			}

			ushort result = 0;
			for (int i = 0; i != size; ++i)
			{
				result <<= 8;
				result |= (ushort)(data[i] & 0xFF); // The & 0xFF is to remove sign extension.
			}
			return result;
		}


		/// <summary>
		/// Convert a number of bytes (big endian coded) into a 32-bit unsigned integer. 
		/// When the given size is too big it will be truncated to the max possible number of bytes (4).
		/// </summary>
		/// <param name="data">Array of bytes containing the input.</param>
		/// <param name="size">The number of bytes from the buffer to convert [0, 4].</param>
		/// <returns>The resulting 32-bit integer [0, 0xFF FF FF FF].</returns>
		public static uint HexToUInt32(byte[] data, int size = 4)
		{
			// Limit size to 4.
			if (size > 4)
			{
				size = 4;
			}

			uint result = 0;
			for (int i = 0; i != size; ++i)
			{
				result <<= 8;
				result |= (uint)(data[i] & 0xFF); // The & 0xFF is to remove sign extension.
			}
			return result;
		}


		/// <summary>
		/// Convert a number of bytes (big endian coded) into a 64-bit unsigned integer. 
		/// When the given size is too big it will be truncated to the max possible number of bytes (8).
		/// </summary>
		/// <param name="data">Array of bytes containing the input.</param>
		/// <param name="size">The number of bytes from the buffer to convert [0, 8].</param>
		/// <returns>The resulting 64-bit integer [0, 0xFF FF FF FF FF FF FF FF].</returns>
		public static ulong HexToUInt64(byte[] data, int size = 8)
		{
			// Limit size to 8.
			if (size > 8)
			{
				size = 8;
			}

			ulong result = 0;
			for (int i = 0; i != size; ++i)
			{
				result <<= 8;
				result |= (ulong)(data[i] & 0xFF); // The & 0xFF is to remove sign extension.
			}
			return result;
		}


		// --- Integer type to big-endian BCD coded number conversions ---


		/// <summary>
		/// Convert a regular 8-bit integer (byte) value [0, 99] into a BCD coded byte.
		/// BCD value is where the last digit of a decimal value is stored in bits [3..0] (least significant nibble)
		/// and the second last is stored in bits [7..4] (most significant nibble).
		/// </summary>
		/// <param name="value">The regular 8-bit integer value [0, 99].</param>
		/// <returns>BCD coded byte [0x00, 0x99] excluding A-F values.</returns>
		public static byte UInt8ToBcd(byte value)
		{
			// Value must be in the range [0, 99].
			if (value >= 100)
			{
				value = 0;
			}

			byte bcd = 0x00;
			bcd |= (byte)(((value / 10) << 4) & 0xF0);	// Set the most significant nibble.
			bcd |= (byte)((value % 10) & 0x0F);			// Set the least significant nibble.

			return bcd;
		}


		/// <summary>
		/// Convert a regular 16-bit integer value [0, 9999] into a number of bytes stored into an array (BCD coded).
		/// BCD value is where the last digit of a decimal value is stored in bits [3..0] (least significant nibble)
		/// and the second last is stored in bits [7..4] (most significant nibble).
		/// </summary>
		/// <param name="value">The regular 16-bit integer value [0, 9999].</param>
		/// <param name="size">Number of bytes to use in buffer [0, 3]. No problem if longer (prepends additional 0x00 bytes).</param>
		/// <returns>The resulting byte array.</returns>
		public static byte[] UInt16ToBcd(ushort value, int size = 2)
		{
			// Delegate to UInt64 version.
			return UInt64ToBcd(value, size);
		}


		/// <summary>
		/// Convert a regular 32-bit integer value [0, 99999999] into a number of bytes stored into an array (BCD coded).
		/// BCD value is where the last digit of a decimal value is stored in bits [3..0] (least significant nibble)
		/// and the second last is stored in bits [7..4] (most significant nibble).
		/// </summary>
		/// <param name="value">The regular 32-bit integer value [0, 99999999].</param>
		/// <param name="size">Number of bytes to use in buffer [0, 7]. No problem if longer (prepends additional 0x00 bytes).</param>
		/// <returns>The resulting byte array.</returns>
		public static byte[] UInt32ToBcd(uint value, int size = 4)
		{
			// Delegate to UInt64 version.
			return UInt64ToBcd(value, size);
		}

		
		/// <summary>
		/// Convert a regular 32-bit integer value [0, 9999999999999999] into a number of bytes stored into an array (BCD coded).
		/// BCD value is where the last digit of a decimal value is stored in bits [3..0] (least significant nibble)
		/// and the second last is stored in bits [7..4] (most significant nibble).
		/// </summary>
		/// <param name="value">The regular 64-bit integer value [0, 9999999999999999].</param>
		/// <param name="size">Number of bytes to use in buffer [0, 15]. No problem if longer (prepends additional 0x00 bytes).</param>
		/// <returns>The resulting byte array.</returns>
		public static byte[] UInt64ToBcd(ulong value, int size = 8)
		{
			byte[] result = new byte[size];

			// Iterate the buffer from the back.
			for (int i = size - 1; i >=0; --i)
			{
				result[i] = UInt8ToBcd((byte)(value % 100));
				value /= 100;
			}

			return result;
		}

		// TODO: public static byte[] DateTimeToBcd(System.DateTime dateTime)


		// --- Big-endian coded BCD number to integer type conversions ---

		/// <summary>
		/// Convert a BCD coded byte [0x00, 0x99] into a regular 8-bit integer (byte) [0, 99]. 
		/// BCD value is where the last digit of a decimal value is stored in bits [3, 0] (least significant nibble)
		/// and the second last is stored in bits [7, 4] (most significant nibble).
		/// No check for invalid BCD!
		/// </summary>
		/// <param name="bcd">The BCD coded byte [0x00, 0x99] excluding A-F values.</param>
		/// <returns>The regular 8-bit integer [0, 99].</returns>
		public static byte BcdToUInt8(byte bcd)
		{
			int msNibble = ((bcd >> 4) & 0x0F);
			int lsNibble = (bcd & 0x0F);

			return (byte)(msNibble * 10 + lsNibble);
		}


		/// <summary>
		/// Convert a number of bytes (BCD coded) [0x0000, 0x9999] into a regular 16-bit integer [0, 9999].
		/// 
		/// BCD value is where the last digit of a decimal value is stored in bits [0, 3] (least significant nibble)
		/// and the second last is stored in bits [3, 7] (most significant nibble).
		/// No check for invalid BCD!
		/// </summary>
		/// <param name="data">Array of bytes containing the BCD coded input [0x0000, 0x9999].</param>
		/// <param name="size">The number of bytes from the buffer to convert [0, 2].</param>
		/// <returns>Resulting 16-bit integer [0, 9999].</returns>
		public static ushort BcdToUInt16(byte[] data, int size = 2)
		{
			ushort result = 0;

			// Limit the size.
			if (size > 2)
			{
				size = 2;
			}

			// Process each byte in the buffer.
			for (int i = 0; i != size; ++i)
			{
				result *= 100;
				result += BcdToUInt8(data[i]);
			}

			return result;
		}


		/// <summary>
		/// Convert a number of bytes (BCD coded) [0x00000000, 0x99999999] into a regular 32-bit integer [0, 99999999].
		/// 
		/// BCD value is where the last digit of a decimal value is stored in bits [0, 3] (least significant nibble)
		/// and the second last is stored in bits [3, 7] (most significant nibble).
		/// No check for invalid BCD!
		/// </summary>
		/// <param name="data">Array of bytes containing the BCD coded input [0x00000000, 0x99999999].</param>
		/// <param name="size">The number of bytes from the buffer to convert [0, 4].</param>
		/// <returns>Resulting 32-bit integer [0, 99999999].</returns>
		public static uint BcdToUInt32(byte[] data, int size = 4)
		{
			uint result = 0;

			// Limit the size.
			if (size > 4)
			{
				size = 4;
			}

			// Process each byte in the buffer.
			for (int i = 0; i != size; ++i)
			{
				result *= 100;
				result += BcdToUInt8(data[i]);
			}

			return result;
		}


		/// <summary>
		/// Convert a number of bytes (BCD coded) [0x0000000000000000, 0x9999999999999999] into a regular 64-bit integer [0, 9999999999999999].
		/// 
		/// BCD value is where the last digit of a decimal value is stored in bits [0, 3] (least significant nibble)
		/// and the second last is stored in bits [3, 7] (most significant nibble).
		/// No check for invalid BCD!
		/// </summary>
		/// <param name="data">Array of bytes containing the BCD coded input [0x0000000000000000, 0x9999999999999999].</param>
		/// <param name="size">The number of bytes from the buffer to convert [0, 8].</param>
		/// <returns>Resulting 32-bit integer [0, 9999999999999999].</returns>
		public static ulong BcdToUInt64(byte[] data, int size = 8)
		{
			ulong result = 0;

			// Limit the size.
			if (size > 8)
			{
				size = 8;
			}

			// Process each byte in the buffer.
			for (int i = 0; i != size; ++i)
			{
				result *= 100;
				result += BcdToUInt8(data[i]);
			}

			return result;
		}


		/// <summary>
		/// Get a DateTime object from a BCD coded date/time (YYYYMMDDhhmmss (7 BCD bytes)).
		/// </summary>
		/// <param name="data">Array of bytes containing the BCD coded date (YYYYMMDDhhmmss (7 BCD bytes)).</param>
		/// <returns>The date/time value.</returns>
		/// <exception cref="FormatException">The format is wrong (not the correct number of data bytes).</exception>
		/// <exception cref="ArgumentOutOfRangeException">The date/time values are out of range e.g. 0 for day number.</exception>
		public static System.DateTime BcdToDateTime(byte[] data)
		{
			// Check data length.
			if (data.Length != 7)
			{
				throw new System.FormatException("Wrong length");
			}

			// Convert BCD values to date/time components.
			int second = ((data[6] & 0xF0) >> 4) * 10 + (data[6] & 0x0F);
			int minute = ((data[5] & 0xF0) >> 4) * 10 + (data[5] & 0x0F);
			int hour = ((data[4] & 0xF0) >> 4) * 10 + (data[4] & 0x0F);
			int day = ((data[3] & 0xF0) >> 4) * 10 + (data[3] & 0x0F);
			int month = ((data[2] & 0xF0) >> 4) * 10 + (data[2] & 0x0F);
			int year = ((data[0] & 0xF0) >> 4) * 1000 + (data[0] & 0x0F) * 100 + ((data[1] & 0xF0) >> 4) * 10 + (data[1] & 0x0F);

			// Create date/time object.
			return new System.DateTime(year, month, day, hour, minute, second);
		}


		/// <summary>
		/// Convert a string with hex values to a byte array
		/// </summary>
		/// <param name="hex">The string with hex values.</param>
		/// <returns>The array of bytes.</returns>
		public static byte[] HexStringToByteArray(string hex)
		{
			// Remove unwanted characters from the string.
			hex = hex.Replace("-", "");
			hex = hex.Replace("0x", "");
			hex = hex.Replace(",", "");
			hex = hex.Replace(" ", "");

			// The number of bytes is half the string length.
			int numberOfChars = hex.Length;
			byte[] bytes = new byte[numberOfChars / 2];

			// Convert each 2 characters to a byte.
			for (int i = 0; i < numberOfChars; i += 2)
			{
				bytes[i / 2] = System.Convert.ToByte(hex.Substring(i, 2), 16);
			}

			// Return the result.
			return bytes;
		}


		/// <summary>
		/// Convert a byte array to a string with hex values.
		/// </summary>
		/// <param name="bytes">The bytes to convert to hex string.</param>
		/// <param name="separator">The separator in the output between each byte.</param>
		/// <returns>The string with hex values.</returns>
		public static string ByteArrayToHexString(byte[] bytes, string separator = "")
		{
			return System.BitConverter.ToString(bytes).Replace("-", separator);
		}
	}
}
