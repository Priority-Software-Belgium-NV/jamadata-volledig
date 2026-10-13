// =========================================================================================
// ====================================== T L V L I B ======================================
// =========================================================================================
//
//		Module: TlvLib
//		File  : TlvConstructed.cs
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
//
//
// =========================================================================================
// (C) Chess pT  2015-2016
// =========================================================================================


using System.IO;
using Utilities;
using TlvBaseList = System.Collections.Generic.List<TlvLib.TlvBase>;


namespace TlvLib
{
	public class TlvConstructed: TlvBase
	{
		/// <summary>
		/// List with TLV objects.
		/// </summary>
		private TlvBaseList mTlvList = new TlvBaseList();


		/// <summary>
		/// Default constructor.
		/// </summary>
		public TlvConstructed(): base()
		{
			// Nothing here.
		}


		/// <summary>
		/// Constructor with tag.
		/// </summary>
		/// <param name="tag">The tag of the new constructed TLV.</param>
		public TlvConstructed(uint tag): base(tag)
		{
			// Nothing here.   
		}


		/// <summary>
		/// Adds a TLV to the list. No copy!
		/// </summary>
		/// <param name="tlv">The TLV to add.</param>
		public void AddTlv(TlvBase tlv)
		{
			// Exit if no TLV or myself.
			if (tlv == null || tlv == this)
			{
				return;
			}

			// Add the TLV to the list.
			mTlvList.Add(tlv);
		}


		/// <summary>
		/// Add a TLV to the list with the value as 8-bit hex number.
		/// </summary>
		/// <param name="tag">The tag of the new TLV.</param>
		/// <param name="value">The value of the new TLV.</param>
		public void AddTlvUInt8AsHex(uint tag, byte value)
		{
			byte[] buffer = new byte[1];
			buffer[0] = value;

			mTlvList.Add(new Tlv(tag, buffer));
		}


		/// <summary>
		/// Add a TLV to the list with the value as 16-bit hex number.
		/// </summary>
		/// <param name="tag">The tag of the new TLV.</param>
		/// <param name="value">The value of the new TLV.</param>
		public void AddTlvUInt16AsHex(uint tag, ushort value)
		{
			mTlvList.Add(new Tlv(tag, Conversions.UInt16ToHex(value)));
		}


		/// <summary>
		/// Add a TLV to the list with the value as 32-bit hex number.
		/// </summary>
		/// <param name="tag">The tag of the new TLV.</param>
		/// <param name="value">The value of the new TLV.</param>
		public void AddTlvUInt32AsHex(uint tag, uint value)
		{
			mTlvList.Add(new Tlv(tag, Conversions.UInt32ToHex(value)));
		}


		/// <summary>
		/// Add a TLV to the list with the value as 64-bit hex number.
		/// </summary>
		/// <param name="tag">The tag of the new TLV.</param>
		/// <param name="value">The value of the new TLV.</param>
		public void AddTlvUInt64AsHex(uint tag, ulong value)
		{
			mTlvList.Add(new Tlv(tag, Conversions.UInt64ToHex(value)));
		}


		/// <summary>
		/// Add a TLV to the list with the value as 8-bit BCD number.
		/// </summary>
		/// <param name="tag">The tag of the new TLV.</param>
		/// <param name="value">The value of the new TLV.</param>
		public void AddTlvUInt8AsBcd(uint tag, byte value)
		{
			byte[] buffer = new byte[1];
			buffer[0] = Conversions.UInt8ToBcd(value);

			mTlvList.Add(new Tlv(tag, buffer));
		}

		
		/// <summary>
		/// Add a TLV to the list with the value as 16-bit BCD number.
		/// </summary>
		/// <param name="tag">The tag of the new TLV.</param>
		/// <param name="value">The value of the new TLV.</param>
		public void AddTlvUInt16AsBcd(uint tag, ushort value)
		{
			mTlvList.Add(new Tlv(tag, Conversions.UInt16ToBcd(value)));
		}


		/// <summary>
		/// Add a TLV to the list with the value as 32-bit BCD number.
		/// </summary>
		/// <param name="tag">The tag of the new TLV.</param>
		/// <param name="value">The value of the new TLV.</param>
		public void AddTlvUInt32AsBcd(uint tag, uint value)
		{
			mTlvList.Add(new Tlv(tag, Conversions.UInt32ToBcd(value)));
		}


		/// <summary>
		/// Add a TLV to the list with the value as 64-bit BCD number.
		/// </summary>
		/// <param name="tag">The tag of the new TLV.</param>
		/// <param name="value">The value of the new TLV.</param>
		public void AddTlvUInt64AsBcd(uint tag, ulong value)
		{
			mTlvList.Add(new Tlv(tag, Conversions.UInt64ToBcd(value)));
		}


		/// <summary>
		/// Add a TLV to the list with the value as 64-bit BCD number.
		/// </summary>
		/// <param name="tag">The tag of the new TLV.</param>
		/// <param name="value">The value of the new TLV.</param>
		public void AddTlvAsString(uint tag, string str)
		{
			mTlvList.Add(new Tlv(tag, str));
		}


		/// <summary>
		/// Access the size of the TLV-value.
		/// </summary>
		public override int Length
		{
			get
			{
				// Of all TLVs, add the TLV-data size (tag length, length length and data length).
				int size = 0;
				foreach (TlvBase tlv in mTlvList)
				{
					size += tlv.GetTlvSize();
				}

				// Return the calculated size.
				return size;
			}
		}


		/// <summary>
		/// Retrieve a reference to the TLV list.
		/// Can be used to iterate the TLVs e.g. in case the constructed TLV is a table containing only table records.
		/// </summary>
		/// <returns>The list with TLVs</returns>
		public TlvBaseList GetTlvList()
		{
			return mTlvList;
		}


		/// <summary>
		/// Serialise the TLV to a stream.
		/// </summary>
		/// <param name="stream">The stream to serialise to.</param>
		/// <returns>The number of bytes written.</returns>
		public override int Serialise(Stream stream)
		{
			int bytesWritten = 0;

			// Write the constructed tag.
			bytesWritten += TlvUtils.SerialiseTag(mTag, stream);

			// Write the constructed tag value size (length).
			bytesWritten += TlvUtils.SerialiseLength(Length, stream);

			// Write all TLVs in the constructed TLV.
			bytesWritten += SerialiseValue(stream);

			// Return the nuber of bytes written.
			return bytesWritten;
		}


		/// <summary>
		/// Serialise only the data of the TLV (no tag and value).
		/// </summary>
		/// <param name="stream">The stream to serailise to.</param>
		/// <returns>The number of bytes written.</returns>
		public int SerialiseValue(Stream stream)
		{
			int bytesWritten = 0;

			// Write all TLVs in the constructed TLV.
			foreach (TlvBase tlv in mTlvList)
			{
				bytesWritten += tlv.Serialise(stream);
			}

			return bytesWritten;
		}


		/// <summary>
		/// Deserialise the TLV from the stream (only length & value, the tag must be already read and set).
		/// </summary>
		/// <param name="stream">The stream to deserialise from.</param>
		/// <returns>The number of bytes read or 0 when error.</returns>
		public override int DeserialiseLengthValue(Stream stream)
		{
			// Deserialise the length.
			int length;
			int bytesRead = TlvUtils.DeserialiseLength(stream, out length);

			// Deserialise the data.
			if (length > 0)
			{
				length = DeserialiseValue(stream, length);
				if (length == 0)
				{
					return 0;
				}
			}

			// Return the number of bytes read.
			return bytesRead + length;
		}


		/// <summary>
		/// Deserialise the TLV from the stream (only value, the tag must be already read and set and the length must be passed).
		/// Used to deserialise the data after the data is processed for decryption and/or MDC calculation.
		/// </summary>
		/// <param name="stream">The stream to deserialise from.</param>
		/// <param name="length">The number of bytes to deserialise.</param>
		/// <returns>The number of bytes read or 0 when error.</returns>
		public int DeserialiseValue(Stream stream, int length)
		{
			// Process TLVs until all TLVs in the constructed TLV are read.
			int processedBytes = 0;
			while (processedBytes < length)
			{
				// Deserialise a tag.
				int size;
				TlvBase tlv = TlvUtils.DeserialiseTlv(stream, out size);

				// Add the read TLV to the list.
				if (tlv != null)
				{
					mTlvList.Add(tlv);
				}

				// Increment the number of bytes read.
				processedBytes += size;
			}

			// Check if the processed number of bytes is as expected.
			if (length != processedBytes)
			{
				return 0;
			}

			// All OK.
			return processedBytes;
		}


		/// <summary>
		/// Find the first TLV in the list by its tag (could be a primitive or constructed TLV).
		/// </summary>
		/// <param name="tag">The tag of the TLV to find.</param>
		/// <returns>Reference to the found TLV or NULL if not found.</returns>
		public TlvBase Find(uint tag)
		{
			return mTlvList.Find(item => item.Tag == tag);
		}


		/// <summary>
		/// Find a primitive TLV in the list by its tag.
		/// </summary>
		/// <param name="tag">The tag of the TLV to find.</param>
		/// <returns>Pointer to the found TLV or null if not found or not a primitive TLV.</returns>
		public Tlv FindTlv(uint tag)
		{
			// Find the TlvBase object by tag.
			TlvBase result = Find(tag);
			if (result == null)
			{
				return null;
			}

			// Check if the found TLV is a primitive TLV.
			if (result.IsConstructed())
			{
				return null;
			}

			// Found TLV was a primitive TLV, return it.
			return result as Tlv;
		}


		/// <summary>
		/// Find a constructed TLV in the list by its tag.
		/// </summary>
		/// <param name="tag">The tag of the TLV to find.</param>
		/// <returns>Pointer to the found TLV or null if not found or not a constructed TLV.</returns>
		public TlvConstructed FindTlvConstructed(uint tag)
		{
			// Find the TlvBase object by tag.
			TlvBase result = Find(tag);
			if (result == null)
			{
				return null;
			}

			// Check if the found TLV is a constructed TLV.
			if (!result.IsConstructed())
			{
				return null;
			}

			// Found TLV was a constructed TLV, return it.
			return result as TlvConstructed;
		}


		//! Find all TLVs in the list by its tag (the result list could contain primitive and/or constructed TLVs).
		/*!
		 * \param[in] tag		The tag of the TLV to find.
		 * \param[out] result	The TLV list to add the found TLVs to.
		 */
		public TlvBaseList FindAll(uint tag)
		{
			return mTlvList.FindAll(item => item.Tag == tag);
		}

	}
}

