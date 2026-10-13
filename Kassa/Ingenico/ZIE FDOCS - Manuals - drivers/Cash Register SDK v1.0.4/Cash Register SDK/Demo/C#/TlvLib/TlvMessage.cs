// =========================================================================================
// ====================================== T L V L I B ======================================
// =========================================================================================
//
//		Module: TlvLib
//		File  : TlvMessage.cs
//		Author: rdem
//
//
//		Description:
//		Class for serialising/deserialising a TLV message.
//
//
//		Last Modification:
//		$Id:
//
// ----------------------------------------------------------------------------------------- 
//		Modifications:
//		Date		Author  Issue	Comment
//
//
// =========================================================================================
// (C) Chess pT  2015-2016
// =========================================================================================


using System.IO;


namespace ChessPt.TlvLib
{
	/// <summary>
	/// Class for serialising/deserialising a TLV message.
	/// 
	/// A message contains (in order):
	/// - The total length (4 bytes, no short form as with TLV tags).
	/// - A couple of identification bytes:
	/// - C-TAP: 0x0A, 0x04, 0x00, 0x00, 0x00, 0x00.
	/// - Cash register interface: "P4Y-ECR!"
	/// - A constructed TLV (usually tag 0xF0) containing header, body and footer groups (for C-TAP the order is important).
	///   The header, body, footer are processed separately because the body can be encrypted and the foorter can contain a modification detection code (MDC).
	/// </summary>
	public class TlvMessage
	{
		/* Private data. */

		protected byte[] mMessageId = null;					//!< The identifier of the message written before the root group.
		protected uint mRootGroupTag = 0x0000;				//!< The tag to use for the root tag.
		protected TlvConstructed mHeaderGroup = null;		//!< The header of the message.
		protected TlvConstructed mBodyGroup = null;			//!< The body of the message.
		protected TlvConstructed mFooterGroup = null;		//!< The footer of the message.



		/* Public functionality. */

		/// <summary>
		/// Constructor with the message identifier.
		/// This constructor is usually used for creating an empty message to be filled by deserialising.
		/// </summary>
		/// <param name="messageId">The message ID used when (de)serialising the message.</param>
		public TlvMessage(byte[] messageId)
		{
			mMessageId = messageId;
		}


		/// <summary>
		/// Constructor with the message identifier (string version).
		/// This constructor is usually used for creating an empty message to be filled by deserialising.
		/// </summary>
		/// <param name="messageId">The message ID used when (de)serialising the message.</param>
		public TlvMessage(string messageId)
		{
			mMessageId = System.Text.Encoding.ASCII.GetBytes(messageId);
		}


		/// <summary>
		/// Constructor with the the message identifier and separated constructed TLVs for the header, body and footer groups. The root group is created during serialisation.
		/// This constructor is usually used to create a filled message to be serialised.
		/// </summary>
		/// <param name="messageId">The message ID used when (de)serialising the message.</param>
		/// <param name="headerGroup">The constructed TLV containing the message header. </param>
		/// <param name="bodyGroup">The constructed TLV containing the message body. </param>
		/// <param name="footerGroup">The constructed TLV containing the message footer. </param>
		/// <param name="rootGroupTag">The tag to use for the root group created during serailisation.</param>
		public TlvMessage(byte[] messageId, TlvConstructed headerGroup, TlvConstructed bodyGroup, TlvConstructed footerGroup, uint rootGroupTag)
		{
			mMessageId = messageId;
			mRootGroupTag = rootGroupTag;
			mHeaderGroup = headerGroup;
			mBodyGroup = bodyGroup;
			mFooterGroup = footerGroup;
		}


		/// <summary>
		/// Constructor with the the message identifier (string version) and separated constructed TLVs for the header, body and footer groups. The root group is created during serialisation.
		/// This constructor is usually used to create a filled message to be serialised.
		/// </summary>
		/// <param name="messageId">The message ID used when (de)serialising the message.</param>
		/// <param name="headerGroup">The constructed TLV containing the message header. </param>
		/// <param name="bodyGroup">The constructed TLV containing the message body. </param>
		/// <param name="footerGroup">The constructed TLV containing the message footer. </param>
		/// <param name="rootGroupTag">The tag to use for the root group created during serailisation.</param>
		public TlvMessage(string messageId, TlvConstructed headerGroup, TlvConstructed bodyGroup, TlvConstructed footerGroup, uint rootGroupTag)
		{
			mMessageId = System.Text.Encoding.ASCII.GetBytes(messageId);
			mRootGroupTag = rootGroupTag;
			mHeaderGroup = headerGroup;
			mBodyGroup = bodyGroup;
			mFooterGroup = footerGroup;
		}


		//! Clear the TLV data.
		protected void Clear()
		{
			mHeaderGroup = null;
			mBodyGroup = null;
			mFooterGroup = null;
		}


		/// <summary>
		/// Access the header group.
		/// </summary>
		public TlvConstructed Header
		{
			get
			{
				return mHeaderGroup;
			}
		}


		/// <summary>
		/// Access the body group.
		/// </summary>
		public TlvConstructed Body
		{
			get
			{
				return mBodyGroup;
			}
		}


		/// <summary>
		/// Access the footer group.
		/// </summary>
		public TlvConstructed Footer
		{
			get
			{
				return mFooterGroup;
			}
		}


		/// <summary>
		/// Serialise the message to a stream. 
		/// </summary>
		/// <param name="stream">The stream to serialise to.</param>
		/// <returns>The number of bytes written.</returns>
		public int Serialise(Stream stream)
		{
			// Because the body can be encrypted and/or a MDC must be calculated, we flatten the constructed TLV value to a primitive TLV value.
			Tlv body = new Tlv(mBodyGroup);

			// Call the serialisation callback that can encrypt the data and/or add a MDC tag to the footer tag.
			SerialisationCallback(body);

			// Determine the root group data size (header size + (encrypted) body size + footer size).
			int rootGroupSize = mHeaderGroup.GetTlvSize() + body.GetTlvSize() + mFooterGroup.GetTlvSize();
	
			// Determine the message size (message identifier + root group size + root group tag size + root group length size.
			int messageSize = mMessageId.Length + rootGroupSize + TlvUtils.DetermineTagLength(mRootGroupTag) + TlvUtils.DetermineLengthLength(rootGroupSize);

			// Write the message length.
			stream.Write(ChessPt.Utilities.Conversions.UInt32ToHex((uint)messageSize), 0, 4);
			int bytesWritten = 4;

			// Write the message identifier.
			stream.Write(mMessageId, 0, mMessageId.Length);
			bytesWritten += mMessageId.Length;

			// Write the root group tag and length.
			bytesWritten += TlvUtils.SerialiseTag(mRootGroupTag, stream);
			bytesWritten += TlvUtils.SerialiseLength(rootGroupSize, stream);

			// Write the message header, body and footer.
			bytesWritten += mHeaderGroup.Serialise(stream);
			bytesWritten += body.Serialise(stream);
			bytesWritten += mFooterGroup.Serialise(stream);

			// Return the number of bytes written.
			return bytesWritten;
		}


		/// <summary>
		/// Deserialise the message from a stream.
		/// </summary>
		/// <param name="stream">The stream to deserialise from.</param>
		/// <returns>The number of bytes read or 0 when error.</returns>
		public int Deserialise(Stream stream)
		{
			int bytesRead = 0;
	
			// Clear the old data.
			Clear();

			// Read until the header was detected.
			byte[] buffer = new byte[4 + mMessageId.Length];	// Buffer for the message length + header.
			if (!TlvUtils.ReadUntilHeaderDetected(stream, buffer, mMessageId))
			{
				System.Diagnostics.Debug.WriteLine("TlvMessage::Deserialise(): No header detected.");
				return 0;
			}

			// Extract the message length.
			bytesRead += buffer.Length;
			int expectedLength = (int)ChessPt.Utilities.Conversions.HexToUInt32(buffer) + 4;	// Plus 4 to include the length bytes.

			
			//// Read the total message length.
			//byte[] buffer = new byte[4];
			//if (!TlvUtils.Read(stream, buffer, 0, 4)) return 0;
			//int expectedLength = (int)Utilities.Conversions.HexToUInt32(buffer) + 4;	// Plus 4 to include the length bytes.
			//bytesRead += 4;

			//// Read the message identifier.
			//byte[] messageId = new byte[mMessageId.Length];
			//if (!TlvUtils.Read(stream, messageId, 0, messageId.Length)) return 0;
			//if (!messageId.SequenceEqual(mMessageId))
			//{
			//    // Message identifiers not as expected.
			//    System.Diagnostics.Debug.WriteLine("TlvMessage::Deserialise(): Message identifier not as expected.");
			//    return 0;
			//}
			//bytesRead += messageId.Length;

			// Read the root group tag and length.
			int rootLength;
			bytesRead += TlvUtils.DeserialiseTag(stream, out mRootGroupTag);
			bytesRead += TlvUtils.DeserialiseLength(stream, out rootLength);

			// Deserialise the header group.
			int bytesReadTmp;
			mHeaderGroup = TlvUtils.DeserialiseTlv(stream, out bytesReadTmp) as TlvConstructed;
			bytesRead += bytesReadTmp;

			// Deserialise the body group non-recursivly (thus a primitive TLV) because the value can be encrypted and/or a MDC must be calculated.
			Tlv bodyTlv = TlvUtils.DeserialiseTlvNonRecursive(stream, out bytesReadTmp);
			bytesRead += bytesReadTmp;

			// Deserialise the footer group.
			mFooterGroup = TlvUtils.DeserialiseTlv(stream, out bytesReadTmp) as TlvConstructed;
			bytesRead += bytesReadTmp;

			// Check the number of bytes read.
			if (expectedLength != bytesRead)
			{
				System.Diagnostics.Debug.WriteLine("TlvMessage::Deserialise(): Expected number of bytes != read bytes.");
				return 0;
			}

			// Because the body can be encrypted and a MDC must be calculated, call the Deserialisation callback.
			if (!DeserialisationCallback(bodyTlv))
			{
				// MDC not correct, exit.
				System.Diagnostics.Debug.WriteLine("TlvMessage::Deserialise(): MDC not correct.");
				return 0;
			}

			// Deserialise the body data. Deserialise the value of the tag and store it in a new constructed body tag.
			MemoryStream memoryStream = new MemoryStream(bodyTlv.Value, false);
			mBodyGroup = new TlvConstructed(bodyTlv.Tag);
			if (mBodyGroup.DeserialiseValue(memoryStream, bodyTlv.Length) != bodyTlv.Length)
			{
				// Deserialised size not as expected.
				System.Diagnostics.Debug.WriteLine("TlvMessage::Deserialise(): Deserialised size not as expected.");
				return 0;
			}

			// All OK.
			return bytesRead;
		}



		/* Functions to be overridden by derived classes. */


		/// <summary>
		/// Function called during serialisation. Used for encrypting the body and/or calculating the MDC.
		/// 
		/// This function is called during serialisation with the purpose to encrypt the data and/or to calculate a MDC over the body.
		/// This function must be overriden by derived classes to implement this functionality. The default implementation does nothing.
		/// 
		/// The MDC must be calculated over the unencrypted body data excluding the tag and length.
		/// The calculated MDC is usually stored in the footer. 
		/// 
		/// The encrypted data must be stored in the input TLV (thus overwriting the unencrypted data). 
		/// The encrypted data could be bigger than the original data (e.g. because of padding).
		/// The encryption method/parameters to use are stored in the header.
		/// </summary>
		/// <param name="bodyTlv">The primitive TLV containing the body data.</param>
		protected virtual void SerialisationCallback(Tlv bodyTlv)
		{
			// Nothing here.
		}


		/// <summary>
		/// Function called during deserialisation. Used for decrypting and/or checking MDC.
		///
		/// This function is called during deserialisation with the purpose of decrypting the data and/or to check the MDC.
		/// This function must be overridden by derived classes to implement this functionality. The default implementation does nothing.
		///
		/// If the data is encrypted must be derived from the encryption parameters in the header. 
		/// The decrypted data must be stored in the input TLV (thus overwriting the encrypted data).
		/// The size of the decrypted data can be smaller that the encrypted data (e.g. because of padding).
		/// 
		/// The MDC must be calculated over the unencrypted body data excluding the tag and length.
		/// The calculated MDC is usually compared with the MDC stored in the footer. When the MDC is not correct, false must be returned.
		/// </summary>
		/// <param name="bodyTlv">The primitive TLV containing the body data to decrypt and/or calculate the MDC over.</param>
		/// <returns>False when the MDC was incorrect.</returns>
		protected virtual bool DeserialisationCallback(Tlv bodyTlv)
		{
			return true;
		}

	}
}
