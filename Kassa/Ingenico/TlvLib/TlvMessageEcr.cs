// =========================================================================================
// ====================================== T L V L I B ======================================
// =========================================================================================
//
//		Module: TlvLib
//		File  : TlvMessageEcr.cs
//		Author: rdem
//
//
//		Description:
//		Class for serialising/deserialising an ECR TLV message.
//
//
//		Last Modification:
//		$Id:
//
// ----------------------------------------------------------------------------------------- 
//		Modifications:
//		Date		Author	Issue	Comment
//		2017-08-28	rdem			Fixed error in SerialisationCallback() were the CRC32 was empty when the body was empty (CRC was not calculated when body was empty).
//
// =========================================================================================
// (C) Chess pT  2015-2017
// =========================================================================================


using System.Linq;
using Utilities;

namespace TlvLib
{
	/// <summary>
	/// Class for serialising/deserialising an ECR TLV message.
	/// </summary>
	public class TlvMessageEcr: TlvMessage
	{
		/// <summary>
		/// Default constructor.
		/// This constructor is usually used for creating an empty message to be filled by deserialising.
		/// </summary>
		public TlvMessageEcr(): base("P4Y-ECR!")
		{
			// Nothing here.
		}

		
		/// <summary>
		/// Constructor creating a ECR message for the given message type.
		/// The header, body and footer groups are created internally and the message type field is set in the header.
		/// This constructor is usually used to create a filled message to be serialised.
		/// </summary>
		/// <param name="messageType"The type of message to create (set in the header).></param>
		TlvMessageEcr(MessageType messageType): base("P4Y-ECR!", new TlvConstructed((uint)Tag.Group_Header), new TlvConstructed((uint)Tag.Group_Body), new TlvConstructed((uint)Tag.Group_Footer), (uint)Tag.Group_Root)
		{
			mHeaderGroup.AddTlvUInt32AsBcd((uint)Tag.MessageType, (uint)messageType);
		}


		/// <summary>
		/// Constructor with separated constructed TLVs for the header, body and footer groups. The root group is created during serialisation.
		/// This constructor is usually used to create a filled message to be serialised.
		/// </summary>
		/// <param name="pHeaderGroup">The constructed TLV containing the message header. </param>
		/// <param name="pBodyGroup">The constructed TLV containing the message body. </param>
		/// <param name="pFooterGroup">The constructed TLV containing the message footer. </param>
		public TlvMessageEcr(TlvConstructed headerGroup, TlvConstructed bodyGroup, TlvConstructed footerGroup): base("P4Y-ECR!", headerGroup, bodyGroup, footerGroup, (uint)Tag.Group_Root)
		{
			// Nothing here.
		}


		/// <summary>
		/// Function called during serialisation. Used for encrypting the body and/or calculating the MDC.
		///
		/// This function is called during serialisation with the purpose to encrypt the data and/or to calculate a MDC over the body.
		///
		/// The MDC must be calculated over the unencrypted body data excluding the tag and length.
		/// The calculated MDC is usually stored in the footer. 
		/// 
		/// The encrypted data must be stored in the input TLV (thus overwriting the unencrypted data). 
		/// The encrypted data could be bigger than the original data (e.g. because of padding).
		/// The encryption method/parameters to use are stored in the header.
		/// </summary>
		/// <param name="bodyTlv">The primitive TLV containing the body data.</param>
		protected override void SerialisationCallback(Tlv bodyTlv)
		{
			// Calculate the MDC over the unencrypted serialised body (excluding tag and length).
			byte[] bodyValue = bodyTlv.Value;
			byte[] crcCalculated = null;
			System.Security.Cryptography.HashAlgorithm hashAlgorithm = new CRC32();
			crcCalculated = hashAlgorithm.ComputeHash(bodyValue);

			// Create MDC tag if not already created.
			Tlv tlvCrc = mFooterGroup.FindTlv((uint)Tag.Mdc);
			if (tlvCrc == null)
			{
				tlvCrc = new Tlv((uint)Tag.Mdc);
				mFooterGroup.AddTlv(tlvCrc);
			}

			// Store the MDC in the footer as big-endian hex value.
			tlvCrc.Value = crcCalculated;

			// TODO: Apply encryption on the body data. Read the encryption parameters from the header.

		}


		/// <summary>
		/// Function called during deserialisation. Used for decrypting and/or checking MDC.
		///
		/// This function is called during deserialisation with the purpose of decrypting the data and/or to check the MDC.
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
		protected override bool DeserialisationCallback(Tlv bodyTlv)
		{
			// Retrieve the body value.
			byte[] bodyValue = bodyTlv.Value;

			if (bodyValue.Length == 0)
			{
				System.Diagnostics.Debug.WriteLine("TlvMessageEcr::DeserialisationCallback(): Empty body detected.");
			}

			// TODO: Apply decryption on the body data. Read the encryption parameters from the header.


			// Calculate the MDC over the unencrypted serialised body (including tag and length).
			System.Security.Cryptography.HashAlgorithm hashAlgorithm = new CRC32();
			byte[] crcCalculated = hashAlgorithm.ComputeHash(bodyValue);

			// Retrieve the MDC tag (code as big-ending hex value) from the footer.
			Tlv tlvCrc = mFooterGroup.FindTlv((uint)Tag.Mdc);
			if (tlvCrc == null)
			{
				// No MDC found to check.
				return false;
			}

			// Compare the calculated MDC with the one in the footer.
			return crcCalculated.SequenceEqual(tlvCrc.Value);
		}
	}
}
