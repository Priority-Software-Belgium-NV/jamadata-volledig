// =========================================================================================
// ====================================== T L V L I B ======================================
// =========================================================================================
//
//		Module: TlvLib
//		File  : TlvBase.cs
//		Author: rdem
//
//
//		Description:
//		Abstract base class for TLV data.
//		The TlvLib is an implementation of BER-TLV format: https://en.wikipedia.org/wiki/X.690#BER_encoding
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


namespace ChessPt.TlvLib
{
	/// <summary>
	/// Abstract base class for TLV data.
	/// The TlvLib is an implementation of BER-TLV format: https://en.wikipedia.org/wiki/X.690#BER_encoding
	/// </summary>
	public abstract class TlvBase
	{
		/// <summary>
		/// The tag of the TLV (1..4 bytes).
		/// </summary>
		protected uint mTag = 0;


		/// <summary>
		/// Default constructor.
		/// </summary>
		public TlvBase()
		{
			// Nothing here.
		}


		/// <summary>
		/// Constructor with tag.
		/// </summary>
		/// <param name="tag">The tag of the new TLV.</param>
		public TlvBase(uint tag)
		{
			mTag = tag;
		}


		/// <summary>
		/// Copy constructor.
		/// </summary>
		/// <param name="source">The object to copy.</param>
		public TlvBase(TlvBase source)
		{
			mTag = source.mTag;
		}


		/// <summary>
		/// Access the tag of the TLV.
		/// </summary>
		public uint Tag
		{
			get
			{
				return mTag;
			}
		}


		/// <summary>
		/// Retrieve the size of the complete TLV-data (tag size + length size + value size).
		/// </summary>
		/// <returns>The TLV-data size.</returns>
		public int GetTlvSize()
		{
			int tlvLength = Length;
			return TlvUtils.DetermineTagLength(mTag) + TlvUtils.DetermineLengthLength(tlvLength) + tlvLength;
		}


		/// <summary>
		/// Determine if the TLV is a constructed TLV (bit 6 of first tag octet set).
		/// </summary>
		/// <returns>True if the TLV is a constructed TLV.</returns>
		public bool IsConstructed()
		{
			return TlvUtils.IsConstructed(mTag);
		}


		
		/* Abstract function to be implemented by derived classes. */

		/// <summary>
		/// Access the size of the TLV-value.
		/// </summary>
		public abstract int Length
		{
			get;
		}


		/// <summary>
		/// Serialise the TLV to a stream.
		/// </summary>
		/// <param name="stream">The stream to serialise to.</param>
		/// <returns>The number of bytes written.</returns>
		public abstract int Serialise(Stream stream);


		/// <summary>
		/// Deserialise the TLV from the stream (only length & value, the tag must be already read and set).
		/// </summary>
		/// <param name="stream">The stream to deserialise from.</param>
		/// <returns>The number of bytes read or 0 if error.</returns>
		public abstract int DeserialiseLengthValue(Stream stream);
	}

}	// End of namespace TlvLib.


