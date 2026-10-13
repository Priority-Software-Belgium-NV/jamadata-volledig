// =========================================================================================
// ====================================== T L V L I B ======================================
// =========================================================================================
//
//		Module: TlvLib
//		File  : Tlv.cs
//		Author: rdem
//
//
//		Description:
//		Class representing a primitive TLV.
//
//
//		Last Modification:
//		$Id:
//
// ----------------------------------------------------------------------------------------- 
//		Modifications:
//		Date		Author	Issue	Comment
//		2017-11-01	rdem			The Length property checks if value is null.
//									The Serialise() function checks if the value is null.
//		2017-08-29	rdem			Added GetValueFromDateTime().
//
// =========================================================================================
// (C) Chess pT  2015-2017
// =========================================================================================


using System.IO;
using Utilities;

namespace TlvLib
{
	/// <summary>
	/// Class representing a primitive TLV.
	/// </summary>
	public class Tlv: TlvBase
	{

		/* Private data. */

		/// <summary>
		/// The value of the TLV.
		/// </summary>
		private byte[] mValue = null;


		/// <summary>
		/// Constructor with tag.
		/// Usually used when creating a tag of which the value will be filled by deserialisation.
		/// </summary>
		/// <param name="tag">The tag of the new TLV.</param>
		public Tlv(uint tag): base(tag)
		{
			// Nothing here.
		}


		/// <summary>
		/// Constructor with tag and value as byte array.
		/// </summary>
		/// <param name="tag">The tag of the new TLV.</param>
		/// <param name="value">The value of the new TLV.</param>
		public Tlv(uint tag, byte[] value): base(tag)
		{
			mValue = value;
		}


		/// <summary>
		/// Constructor with tag and value as string.
		/// </summary>
		/// <param name="tag">The tag of the new TLV.</param>
		/// <param name="value">The value of the new TLV.</param>
		public Tlv(uint tag, string value): base(tag)
		{
			mValue = System.Text.Encoding.ASCII.GetBytes(value);
		}


		/// <summary>
		/// Constructor that flattens a constructed TLV into a primitive TLV.
		/// The TLVs inside the constructed TLV are serialised and the serialised data becomes the value of the new Tlv.
		/// Used when the data of the TLV must be processed before serialisation (e.g. encryption and/or MDC calculation).
		/// </summary>
		/// <param name="tlv">The constructed TLV to "flatten".</param>
		public Tlv(TlvConstructed tlv): base(tlv.Tag)
		{
			// Serialise the data of the constructed TLV to a memory buffer.
			MemoryStream stream = new MemoryStream();
			tlv.SerialiseValue(stream);

			// Put the serialised data in the TLV value.
			mValue = stream.ToArray();
		}


		/// <summary>
		/// Copy constructor.
		/// </summary>
		/// <param name="source">The TLV to copy.</param>
		public Tlv(Tlv source): base(source)
		{
			source.mValue.CopyTo(mValue, 0);
		}


		/// <summary>
		/// Access the size of the TLV-value.
		/// </summary>
		public override int Length
		{
			get
			{
				// When null, length is 0.
				return mValue != null ? mValue.Length : 0;
			}
		}


		/// <summary>
		/// Access the value of the TLV.
		/// </summary>
		public virtual byte[] Value
		{
			get
			{
				return mValue;
			}

			set
			{
				mValue = value;
			}
		}

		
		/// <summary>
		/// Get the value from a 8-bit hex number.
		/// </summary>
		/// <returns>The value from 8-bit hex number.</returns>
		public byte GetValueUInt8FromHex()
		{
			return mValue[0];
		}


		/// <summary>
		/// Get the value from a 16-bit hex number.
		/// </summary>
		/// <returns>The value from 16-bit hex number.</returns>
		public ushort GetValueUInt16FromHex()
		{
			return Conversions.HexToUInt16(mValue);
		}


		/// <summary>
		/// Get the value from a 32-bit hex number.
		/// </summary>
		/// <returns>The value from 32-bit hex number.</returns>
		public uint GetValueUInt32FromHex()
		{
			return Conversions.HexToUInt32(mValue);
		}


		/// <summary>
		/// Get the value from a 64-bit hex number.
		/// </summary>
		/// <returns>The value from 64-bit hex number.</returns>
		public ulong GetValueUInt64FromHex()
		{
			return Conversions.HexToUInt64(mValue);
		}


		/// <summary>
		/// Get the value from a 8-bit BCD number.
		/// </summary>
		/// <returns>The value from 8-bit BCD number.</returns>
		public byte GetValueUInt8FromBcd()
		{
			return Conversions.BcdToUInt8(mValue[0]);
		}


		/// <summary>
		/// Get the value from a 16-bit BCD number.
		/// </summary>
		/// <returns>The value from 16-bit BCD number.</returns>
		public ushort GetValueUInt16FromBcd()
		{
			return Conversions.BcdToUInt16(mValue);
		}


		/// <summary>
		/// Get the value from a 32-bit BCD number.
		/// </summary>
		/// <returns>The value from 32-bit BCD number.</returns>
		public uint GetValueUInt32FromBcd()
		{
			return Conversions.BcdToUInt32(mValue);
		}


		/// <summary>
		/// Get the value from a 64-bit BCD number.
		/// </summary>
		/// <returns>The value from 64-bit BCD number.</returns>
		public ulong GetValueUInt64FromBcd()
		{
			return Conversions.BcdToUInt64(mValue);
		}


		/// <summary>
		/// Get the value from a string.
		/// </summary>
		/// <returns>The value from a string.</returns>
		public string GetValueFromString()
		{
			return System.Text.Encoding.ASCII.GetString(mValue);
		}


		/// <summary>
		/// Get the value from a date/time.
		/// Internalformat: YYYYMMDDhhmmss (7 BCD bytes).
		/// </summary>
		/// <returns>The date/time value.</returns>
		/// <exception cref="FormatException">The format is wrong (not the correct number of data bytes).</exception>
		/// <exception cref="ArgumentOutOfRangeException">The date/time values are out of range e.g. 0 for day number.</exception>
		public System.DateTime GetValueFromDateTime()
		{
			return Conversions.BcdToDateTime(mValue);
		}


		/// <summary>
		/// Serialise the TLV to a stream.
		/// </summary>
		/// <param name="stream">The stream to serialise to.</param>
		/// <returns>The number of bytes written.</returns>
		public override int Serialise(Stream stream)
		{
			int bytesWritten = 0;
			bytesWritten += TlvUtils.SerialiseTag(mTag, stream);
			bytesWritten += TlvUtils.SerialiseLength(mValue != null ? mValue.Length: 0, stream);
			if (mValue != null && mValue.Length != 0)
			{
				stream.Write(mValue, 0, mValue.Length); 
				bytesWritten += mValue.Length;
			}
			return bytesWritten;
		}


		/// <summary>
		/// Deserialise the TLV from the stream (only length & value, the tag must be already read and set).
		/// Used to deserialised the TLV after the tag was read to determine the TLV type (primitive or constructed).
		/// </summary>
		/// <param name="stream">The stream to deserialise from.</param>
		/// <returns>The number of bytes read.</returns>
		public override int DeserialiseLengthValue(Stream stream)
		{
			// Deserialise the length.
			int length;
			int bytesRead = TlvUtils.DeserialiseLength(stream, out length);

			// Read the data.
			mValue = new byte[length];
			if (length > 0)
			{
				if (!TlvUtils.Read(stream, mValue, 0, length)) return 0;
			}

			// Return the number of bytes read.
			return bytesRead + length;
		}
	}


}	// End of namespace TlvLib.