// =========================================================================================
// ====================================== T L V L I B ======================================
// =========================================================================================
//
//		Module: TlvLib
//		File  : TlvUtils.cs
//		Author: rdem
//
//
//		Description:
//		Static class with TLV utilities.
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
// =========================================================================================
// (C) Chess pT  2015-2016
// =========================================================================================


using System.IO;

namespace TlvLib
{
	/// <summary>
	/// Static class with TLV utilities.
	/// </summary>
	public static class TlvUtils
	{
		/// <summary>
		/// Determine if the tag indicates a constructed tag (bit 6 of first octet set).
		/// </summary>
		/// <param name="tag">The tag to check.</param>
		/// <returns>True if the tag indicated a constructed TLV.</returns>
		public static bool IsConstructed(uint tag)
		{
			// Shift the octets until only the first (left most) octet is left.
			while (tag >= 0x100)
			{
				tag >>= 8;
			}

			// Bit 6 from the first octet indicates constructed (1) or primitive (0).
			return ( (tag & 0x20) == 0x20);
		}


		/// <summary>
		/// Determine the length of the tag octets when serialised.
		/// </summary>
		/// <param name="tag">The tag octets to determine the length of.</param>
		/// <returns>The length of the tag octect when serialised.</returns>
		public static int DetermineTagLength(uint tag)
		{
			// A tag never contains a 0 octet. Count the number of octets by shifting the octets till tag is 0.
			int numberOfBytes = 0;
			while (tag != 0)
			{
				tag >>= 8;
				++numberOfBytes;
			}

			return numberOfBytes;
		}


		/// <summary>
		/// Determine the length of the length octets when serialised.
		/// 
		/// The length is coded in a variable number of octets. 
		/// If the length is smaller than 0x80, then the length is written as one byte with bit 8 set to zero.
		/// If the length is bigger than 0x80, then the first byte has bit 8 set and bits 1..7 indicate the number of bytes that follow that contain the length.
		/// </summary>
		/// <param name="length">The length octets to determine the length of.</param>
		/// <returns>The length of the length octets when serialised.</returns>
		public static int DetermineLengthLength(int length)
		{
			// When smaller than 0x80, one length byte.
			if (length < 0x80) return 1;

			// When smaller than 0x100, one 'octets' byte and one length byte.
			if (length < 0x100) return 2;

			// When smaller than 0x10000, one 'octets' byte and two length bytes.
			if (length < 0x10000) return 3;

			// When smaller than 0x1000000, one 'octets' byte and three length bytes.
			if (length < 0x1000000) return 4;

			// Bigger or equal to 0x1000000, write one 'octets' byte and three length bytes.
			return 5;
		}


		/// <summary>
		/// Serialise the tag of a TLV to a stream.
		/// </summary>
		/// <param name="tag">The tag to serialise.</param>
		/// <param name="stream">The stream to serialise to.</param>
		/// <returns>The number of bytes written.</returns>
		internal static int SerialiseTag(uint tag, Stream stream)
		{
			// Write one '0'
			if (tag == 0)
			{
				stream.WriteByte(0x00);
				return 1;
			}

			// Write only the non-zero bytes of the tag. A tag never contains a 0 octet.
			int numberOfBytes = 0;
			byte[] buffer = new byte[4];
			int i = 4;
			while (tag != 0)
			{
				buffer[--i] = (byte)(tag & 0xFF);
				tag >>= 8;
				++numberOfBytes;
			}
			stream.Write(buffer, i, numberOfBytes);
			return numberOfBytes;
		}


		/// <summary>
		/// Serialise the length of a TLV to a stream.
		///
		/// The length is coded in a variable number of octets. 
		/// If the length is smaller than 0x80, then the length is written as one byte with bit 8 set to zero.
		/// If the length is bigger than 0x80, then the first byte has bit 8 set and bits 1..7 indicate the number of bytes that follow that contain the length.
		/// </summary>
		/// <param name="length">The length to serialise.</param>
		/// <param name="stream">The stream to serialise to.</param>
		/// <returns>The number of bytes written.</returns>
		internal static int SerialiseLength(int length, Stream stream)
		{
			// When smaller than 0x80, write one length byte.
			if (length < 0x80)
			{
				stream.WriteByte((byte)length);
				return 1;
			}

			// When smaller than 0x100, write one 'octets' byte and one length byte.
			if (length < 0x100)
			{
				stream.WriteByte((byte)0x81);
				stream.WriteByte((byte)length);
				return 2;
			}

			// When smaller than 0x10000, write one 'octets' byte and two length bytes.
			if (length < 0x10000)
			{
				stream.WriteByte((byte)0x82);
				stream.WriteByte((byte)(length >> 8));
				stream.WriteByte((byte)length);
				return 3;
			}

			// When smaller than 0x1000000, write one 'octets' byte and three length bytes.
			if (length < 0x1000000)
			{
				stream.WriteByte((byte)0x83);
				stream.WriteByte((byte)(length >> 16));
				stream.WriteByte((byte)(length >> 8));
				stream.WriteByte((byte)length);
				return 4;
			}

			// Bigger or equal to 0x1000000, write one 'octets' byte and three length bytes.
			else
			{
				stream.WriteByte((byte)0x84);
				stream.WriteByte((byte)(length >> 24));
				stream.WriteByte((byte)(length >> 16));
				stream.WriteByte((byte)(length >> 8));
				stream.WriteByte((byte)length);
				return 5;
			}
		}


		/// <summary>
		/// Deserialise the tag of a TLV from a stream. 
		///
		/// The first octet of a tag is defined as follows:
		/// bit 7,8: The class of tag (not used as such in ECR/C-TAP):
		///          - 00:
		///          - 01:
		///          - 10:
		///          - 11:
		/// bit 6:   Primitive (0) or constrcuted (1) tag.
		/// bit 1-5: Tag number or when 11111 (31 / 0x1F), then additional tag octets.
		///
		/// When additional tag octets.
		/// - Bit 8:    Set to one except the last one.
		/// - Bits 1-7: Tag number.
		///
		/// </summary>
		/// <param name="stream">The stream to read from.</param>
		/// <param name="outTag">Set to the read tag.</param>
		/// <returns>The number of bytes read or 0 if an error occurred.</returns>
		internal static int DeserialiseTag(Stream stream, out uint outTag)
		{
			byte[] octet = new byte[1];
			uint tag;
			outTag = 0;

			// TODO: According to ISO 7816-4:1995, page 42. there could be 0x00 or 0xFF padding bytes due to erased/modified TLV tags.
			// But this means 0x00 and 0xFF could not be valid tags while it seems these could be valid TLV tags. Must check it.
			// Section 5.2.2 states 0x00 is invalid as first tag octet.
			// Section 5.2.2.1 states 0x00 is a padding value but 0xFF could be a padding value for certain applications.

			// Read the first octet.
			if (!TlvUtils.Read(stream, octet, 0, 1)) return 0;
			tag = octet[0];

			// Check if the tag has more bytes (bits 1..5 set to one).
			int numberOfBytes = 1;
			if ( (octet[0] & 0x1F) == 0x1F)
			{
				// Read additional tag octets.
				do
				{
					// Read octet.
					if (!TlvUtils.Read(stream, octet, 0, 1)) return 0;
			
					// Bit 1-7 may not be zero. According to section 5.2.2.1 it is only for the first additional octet.
					if ((octet[0] & 0x7F) == 0) return 0;

					// Merge it with the tag value already read.
					tag <<= 8;
					tag |= octet[0];

					++numberOfBytes;
				}
				while ((octet[0] & 0x80) == 0x80);	// Read additional octets until bit 8 is set to one.
			}

			// Return the number of bytes read.
			outTag = tag;
			return numberOfBytes;
		}	


		/// <summary>
		/// Deserialise the length of a TLV from a stream.
		/// </summary>
		/// <param name="stream">The stream to read from.</param>
		/// <param name="outLength">Set to the read length.</param>
		/// <returns>The number of bytes read.</returns>
		internal static int DeserialiseLength(Stream stream, out int outLength)
		{
			outLength = 0;
			byte[] octet = new byte[1];

			// Read the first length octet.
			if (!TlvUtils.Read(stream, octet, 0, 1)) return 0;

			// Check if multi-octet length.
			if ((octet[0] & 0x80) == 0x80)
			{
				// Multi octet length. Interpret octet as number of length octets.
				int length = 0;
				int numberOfOctets = (octet[0] & 0x7F);
				for (int i = 0; i != numberOfOctets; ++i)
				{
					// Read the next length octet.
					if (!TlvUtils.Read(stream, octet, 0, 1)) return 0;

					length <<= 8;
					length |= octet[0];
				}

				// Return the length.
				outLength = length;
				return 1 + numberOfOctets;
			}
			else
			{
				// One octet length.
				outLength = octet[0];
				return 1;
			}
		}


		/// <summary>
		/// Deserialise a TLV from the stream (recursive). The TLV returned is an instance of Tlv or TlvConstructed.
		/// This deserialisation is recursive. Thus in case of constructed TLV, the value is deserialised as well.
		/// </summary>
		/// <param name="stream">The stream to deserialise from.</param>
		/// <param name="outBytesRead">Set to the number of bytes read.</param>
		/// <returns>The created TLV object (instance of Tlv of TlvConstructed class).</returns>
		internal static TlvBase DeserialiseTlv(Stream stream, out int outBytesRead)
		{
			outBytesRead = 0;

			// Read the tag.
			int bytesRead = 0;
			uint tag;
			bytesRead += TlvUtils.DeserialiseTag(stream, out tag);

			// Check if the tag indicates a primitive or constructed TLV.
			TlvBase tlv = null;
			if (IsConstructed(tag))
			{
				// Constructed TLV.
				tlv = new TlvConstructed(tag);
			}
			else
			{
				// Primitive TLV.
				tlv = new Tlv(tag);
			}

			// Deserialise the length/value of the TLV.
			bytesRead += tlv.DeserialiseLengthValue(stream);

			// Set the number of bytes read.
			outBytesRead = bytesRead;

			// Return the created TLV.
			return tlv;
		}


		/// <summary>
		/// Deserialise a TLV from the stream (non-recursive). The TLV returned is an instance of Tlv even the tag indicates it is a constructed TLV.
		/// This deserialisation is non-recursive. Thus in case of constructed TLV, the value is not deserialised. 
		/// Use this in case the value must be processed before deserialised further (e.g. for MDC calculation).
		/// </summary>
		/// <param name="stream">The stream to deserialise from.</param>
		/// <param name="outBytesRead">Set to the number of bytes read.</param>
		/// <returns>The created TLV object (instance of Tlv of TlvConstructed class).</returns>
		internal static Tlv DeserialiseTlvNonRecursive(Stream stream, out int outBytesRead)
		{
			// Read the tag.
			int bytesRead = 0;
			uint tag;
			bytesRead += TlvUtils.DeserialiseTag(stream, out tag);

			// Always create a primitive TLV even if the tag indicates a constructed TLV.
			Tlv tlv = new Tlv(tag);

			// Deserialise the length/value of the TLV.
			bytesRead += tlv.DeserialiseLengthValue(stream);

			// Set the number of bytes read.
			outBytesRead = bytesRead;

			// Return the created TLV.
			return tlv;
		}


		/// <summary>
		/// Read data into the buffer until the header is completely read.
		/// The header bytes are checked against the end of the buffer. Thus the buffer can be larger than the header to detect so the previous bytes are stored as well.
		/// </summary>
		/// <param name="stream">The stream to read from.</param>
		/// <param name="buffer">The buffer to fill.</param>
		/// <param name="header">The header to detect.</param>
		/// <returns>False when error occurred.</returns>
		internal static bool ReadUntilHeaderDetected(Stream stream, byte[] buffer, byte[] header)
		{
			// The header can not be larger than the buffer.
			if (header.Length > buffer.Length)
			{
				return false;
			}

			// Start with filling the buffer.
			if (!TlvUtils.Read(stream, buffer, 0, buffer.Length))
			{
				return false;
			}

			// Detect the header. If not detected move all data in the buffer 1 byte to the left and read next byte.
			while (!TlvUtils.DetectHeader(buffer, header))
			{
				// Move the data in the buffer.
				System.Array.Copy(buffer, 1, buffer, 0, buffer.Length - 1);

				// Read one byte at the end of the buffer.
				if (!TlvUtils.Read(stream, buffer, buffer.Length - 1, 1))
				{
					return false;
				}
			}

			// Header detected.
			return true;
		}


		/// <summary>
		/// Check if the header is in the last part of the buffer.
		/// </summary>
		/// <param name="buffer">The buffer to detect the header in.</param>
		/// <param name="header">The header to detect in the buffer.</param>
		/// <returns>True if the header was detected.</returns>
		private static bool DetectHeader(byte[] buffer, byte[] header)
		{
			// Check if the header is in the last part of the buffer.
			int offset = buffer.Length - header.Length;
			for (int i = 0; i != header.Length; ++i)
			{
				if (header[i] != buffer[i + offset])
				{
					return false;
				}
			}

			// The header was completely found.
			return true;
		}


		/// <summary>
		/// Read exactly the 'count' number of bytes from the stream.
		/// </summary>
		/// <param name="stream">The stream to read from.</param>
		/// <param name="buffer">The buffer to write.</param>
		/// <param name="offset">The offset in the buffer.</param>
		/// <param name="count">The number of bytes to read.</param>
		/// <returns>False when an error occurred.</returns>
		internal static bool Read(Stream stream, byte[] buffer, int offset, int count)
		{
			// Repeat reading until all bytes read.
			int bytesLeft = count;
			int bytesRead = 0;
			while (bytesLeft > 0)
			{
				// Read some data from the stream. Error if no data is read.
				bytesRead = stream.Read(buffer, offset, bytesLeft);
				if (bytesRead <= 0) return false;

				// Update the number of bytes left and the offset in the buffer.
				bytesLeft -= bytesRead;
				offset += bytesRead;
			}

			// The expected number of bytes is read.
			return true;
		}
	}
}
