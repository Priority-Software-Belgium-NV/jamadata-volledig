using System;
using System.Linq;
using System.IO;

namespace ChessPt.TlvLibTest
{
	class Program
	{
		static ushort sequenceNumber = 0;

		static bool CreateFile(TlvLib.TlvMessage msg, string fileName)
		{
			// Open file for writing.
			Stream stream = File.Open(fileName, FileMode.Create);
			
			// Serialise the message.
			int size = msg.Serialise(stream);
			stream.Close();

			Console.Out.WriteLine("Bytes written: {0}", size);
			return size != 0;
		}


		static bool ReadFile(TlvLib.TlvMessage msg, string fileName)
		{
			// Open file for reading.
			Stream stream = File.OpenRead(fileName);

			// Deserialise the message.
			int size = msg.Deserialise(stream);
			stream.Close();

			Console.Out.WriteLine("Bytes read: {0}", size);
			return size != 0;
		}


		static void FillHeader(TlvLib.TlvConstructed tlv, TlvLib.MessageType messageType)
		{
			tlv.AddTlvUInt32AsBcd((uint)TlvLib.Tag.ProtocolId, 0x0001);
			tlv.AddTlvUInt32AsBcd((uint)TlvLib.Tag.MessageType, (uint)messageType);
			tlv.AddTlvAsString((uint)TlvLib.Tag.TerminalId, "TerminalId");
			tlv.AddTlvAsString((uint)TlvLib.Tag.EcrId, "EcrId");
			tlv.AddTlvUInt16AsHex((uint)TlvLib.Tag.SequenceNumber, sequenceNumber);

			++sequenceNumber;
		}


		static void Main(string[] args)
		{
			// Create TLV file.
			{
				string header = "Header";
				string body = "body";
				string footer = "footer";

				TlvLib.Tlv tlvHeader = new TlvLib.Tlv(0xDF8148, header);
				TlvLib.Tlv tlvBody = new TlvLib.Tlv(0x9F1C, body);
				TlvLib.Tlv tlvFooter = new TlvLib.Tlv(0xC5, footer);

				TlvLib.TlvConstructed ctHeader = new TlvLib.TlvConstructed((uint)TlvLib.Tag.Group_Header);
				ctHeader.AddTlv(tlvHeader);

				TlvLib.TlvConstructed ctBody = new TlvLib.TlvConstructed((uint)TlvLib.Tag.Group_Body);
				ctBody.AddTlv(tlvBody);

				TlvLib.TlvConstructed ctFooter = new TlvLib.TlvConstructed((uint)TlvLib.Tag.Group_Footer);
				ctFooter.AddTlv(tlvFooter);

				TlvLib.TlvMessageEcr msg = new TlvLib.TlvMessageEcr(ctHeader, ctBody, ctFooter);

				CreateFile(msg, "test.bin");

				TlvLib.Tlv tlv = ctBody.FindTlv(0x9F1C);
				Console.Out.WriteLine("Value: {0}", tlv.GetValueFromString());
			}

			// Read TLV file.
			{
				TlvLib.TlvMessageEcr msg = new TlvLib.TlvMessageEcr();
				if (ReadFile(msg, "test.bin"))
				{
					// Write TLV file again for check.
					CreateFile(msg, "test2.bin");
				}
			}


			// Create hello request message.
			{
				TlvLib.TlvConstructed tlvHeader = new TlvLib.TlvConstructed((uint)TlvLib.Tag.Group_Header);
				TlvLib.TlvConstructed tlvBody = new TlvLib.TlvConstructed((uint)TlvLib.Tag.Group_Body);
				TlvLib.TlvConstructed tlvFooter = new TlvLib.TlvConstructed((uint)TlvLib.Tag.Group_Footer);
				TlvLib.TlvMessageEcr msg = new TlvLib.TlvMessageEcr(tlvHeader, tlvBody, tlvFooter);

				// Header of all messages the same except message type.
				FillHeader(tlvHeader, TlvLib.MessageType.HelloRequest);

				// Fill body.
				TlvLib.TlvConstructed tlvCommunicationParams = new TlvLib.TlvConstructed((uint)TlvLib.Tag.Group_CommunicationParameters);
					// No communication parameters filled (empty tag).
				tlvBody.AddTlv(tlvCommunicationParams);

				TlvLib.TlvConstructed tlvConnectionParams = new TlvLib.TlvConstructed((uint)TlvLib.Tag.Group_ConnectionParameters);
				tlvConnectionParams.AddTlvUInt32AsBcd((uint)TlvLib.Tag.KeepAliveInterval, 15);	// 15 seconds
				tlvBody.AddTlv(tlvConnectionParams);

				// Write to file.
				CreateFile(msg, "HelloRequest.msg");
			}

			// Create transaction request message.
			{
				TlvLib.TlvConstructed tlvHeader = new TlvLib.TlvConstructed((uint)TlvLib.Tag.Group_Header);
				TlvLib.TlvConstructed tlvBody = new TlvLib.TlvConstructed((uint)TlvLib.Tag.Group_Body);
				TlvLib.TlvConstructed tlvFooter = new TlvLib.TlvConstructed((uint)TlvLib.Tag.Group_Footer);
				TlvLib.TlvMessageEcr msg = new TlvLib.TlvMessageEcr(tlvHeader, tlvBody, tlvFooter);

				// Header of all messages the same except message type.
				FillHeader(tlvHeader, TlvLib.MessageType.TransactionRequest);

				// Fill body.
				TlvLib.TlvConstructed tlvTransactionData = new TlvLib.TlvConstructed((uint)TlvLib.Tag.Group_TransactionData);
				tlvTransactionData.AddTlvUInt8AsHex((uint)TlvLib.Tag.TransactionType, (byte)TlvLib.TransactionType.Payment);
				tlvTransactionData.AddTlvUInt32AsHex((uint)TlvLib.Tag.Amount, 199);	// 1.99 euro
				tlvBody.AddTlv(tlvTransactionData);

				TlvLib.TlvConstructed tlvPrintData = new TlvLib.TlvConstructed((uint)TlvLib.Tag.Group_PrintData);
				tlvTransactionData.AddTlvUInt8AsHex((uint)TlvLib.Tag.PrintOrigin, (byte)TlvLib.PrintOrigin.CashRegister);
				tlvBody.AddTlv(tlvPrintData);

				// Write to file.
				CreateFile(msg, "TransactionRequest.msg");
			}

		}


	}
}
