using System;
using System.Diagnostics;
using System.IO;
using System.Reflection;
using System.Threading;
using System.Windows.Forms;
using ingenico.Forms;
using TlvLib;

namespace ingenico
{
    class Program
    {
        protected static ushort sequenceNumber = 0;

        static bool CreateFile(TlvMessage msg, string fileName)
        {
            // Open file for writing.
            Stream stream = File.Open(fileName, FileMode.Create);

            // Serialise the message.
            int size = msg.Serialise(stream);
            stream.Close();

            Console.Out.WriteLine("Bytes written: {0}", size);
            return size != 0;
        }


        static bool ReadFile(TlvMessage msg, string fileName)
        {
            // Open file for reading.
            Stream stream = File.OpenRead(fileName);

            // Deserialise the message.
            int size = msg.Deserialise(stream);
            stream.Close();

            Console.Out.WriteLine("Bytes read: {0}", size);
            return size != 0;
        }


        static void FillHeader(TlvConstructed tlv, MessageType messageType)
        {
            tlv.AddTlvUInt32AsBcd((uint)Tag.ProtocolId, 0x0001);
            tlv.AddTlvUInt32AsBcd((uint)Tag.MessageType, (uint)messageType);
            tlv.AddTlvAsString((uint)Tag.TerminalId, "TerminalId");
            tlv.AddTlvAsString((uint)Tag.EcrId, "EcrId");
            tlv.AddTlvUInt16AsHex((uint)Tag.SequenceNumber, sequenceNumber);

            ++sequenceNumber;
        }

        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        public static void Main()
        {
            Mutex mutex = new Mutex(false, "Ingenico");
            try
            {
                if (mutex.WaitOne(0, false))
                {
                    Application.ThreadException += new ThreadExceptionEventHandler(CustomExceptionHandler);


                    CreateTLV();

                    Application.EnableVisualStyles();
                    Application.SetCompatibleTextRenderingDefault(false);
                    Application.Run(new Form1());
                }
            }
            finally
            {
                mutex.Close();
            }
        }

        static void CustomExceptionHandler(object sender, ThreadExceptionEventArgs e)
        {

        }

        // Create TLV file.
        public static bool CreateTLV()
        {
            bool result = false;
            string header = "Header";
            string body = "body";
            string footer = "footer";

            Tlv tlvHeader = new Tlv(0xDF8148, header);
            Tlv tlvBody = new Tlv(0x9F1C, body);
            Tlv tlvFooter = new Tlv(0xC5, footer);

            TlvConstructed ctHeader = new TlvConstructed((uint)Tag.Group_Header);
            ctHeader.AddTlv(tlvHeader);

            TlvConstructed ctBody = new TlvConstructed((uint)Tag.Group_Body);
            ctBody.AddTlv(tlvBody);

            TlvConstructed ctFooter = new TlvConstructed((uint)Tag.Group_Footer);
            ctFooter.AddTlv(tlvFooter);

            TlvMessageEcr msg = new TlvMessageEcr(ctHeader, ctBody, ctFooter);

            result = CreateFile(msg, "test.bin");

            Tlv tlv = ctBody.FindTlv(0x9F1C);
            Console.Out.WriteLine("Value: {0}", tlv.GetValueFromString());

            return result;
        }

        // Create hello request message.
        public static bool CreateHelloRequestMessage()
        {
            TlvConstructed tlvHeader = new TlvConstructed((uint)Tag.Group_Header);
            TlvConstructed tlvBody = new TlvConstructed((uint)Tag.Group_Body);
            TlvConstructed tlvFooter = new TlvConstructed((uint)Tag.Group_Footer);
            TlvMessageEcr msg = new TlvMessageEcr(tlvHeader, tlvBody, tlvFooter);

            // Header of all messages the same except message type.
            FillHeader(tlvHeader, MessageType.HelloRequest);

            // Fill body.
            TlvConstructed tlvCommunicationParams = new TlvConstructed((uint)Tag.Group_CommunicationParameters);
            // No communication parameters filled (empty tag).
            tlvBody.AddTlv(tlvCommunicationParams);

            TlvConstructed tlvConnectionParams = new TlvConstructed((uint)Tag.Group_ConnectionParameters);
            tlvConnectionParams.AddTlvUInt32AsBcd((uint)Tag.KeepAliveInterval, 15);	// 15 seconds
            tlvBody.AddTlv(tlvConnectionParams);

            // Write to file.
            return CreateFile(msg, "HelloRequest.msg");
        }

        // Create transaction request message.
        public static bool CreateTransactionrequestMessage()
        {
            TlvConstructed tlvHeader = new TlvConstructed((uint)Tag.Group_Header);
            TlvConstructed tlvBody = new TlvConstructed((uint)Tag.Group_Body);
            TlvConstructed tlvFooter = new TlvConstructed((uint)Tag.Group_Footer);
            TlvMessageEcr msg = new TlvMessageEcr(tlvHeader, tlvBody, tlvFooter);

            // Header of all messages the same except message type.
            FillHeader(tlvHeader, MessageType.TransactionRequest);

            // Fill body.
            TlvConstructed tlvTransactionData = new TlvConstructed((uint)Tag.Group_TransactionData);
            tlvTransactionData.AddTlvUInt8AsHex((uint)Tag.TransactionType, (byte)TransactionType.Payment);
            tlvTransactionData.AddTlvUInt32AsHex((uint)Tag.Amount, 199);	// 1.99 euro
            tlvBody.AddTlv(tlvTransactionData);

            TlvConstructed tlvPrintData = new TlvConstructed((uint)Tag.Group_PrintData);
            tlvTransactionData.AddTlvUInt8AsHex((uint)Tag.PrintOrigin, (byte)PrintOrigin.CashRegister);
            tlvBody.AddTlv(tlvPrintData);

            // Write to file.
            return CreateFile(msg, "TransactionRequest.msg");
        }




    }
}
