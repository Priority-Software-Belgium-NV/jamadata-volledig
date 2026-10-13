// =========================================================================================
// ======================== T E L I U M   C A S H   R E G I S T E R ========================
// =========================================================================================
//
//		Module: TlvCashRegisterLib
//		File  : ConnectionHandler.cs
//		Author: rdem
//
//
//		Description:
//		Class handling the serial connection with the terminal.
//
//
//		Last Modification:
//		$Id:
//
// ----------------------------------------------------------------------------------------- 
//		Modifications:
//		Date		Author	Issue	Comment
//		2016-06-28	rdem			Added serial connection parameters members (baud rate, data bits, parity, stop bits, flow control).
//		2016-03-22	rdem			The Close() function is now "locked" so only one can close it at the same time.
//									The Connect() method now retries to open the connection. When the COM port is openend inmediately after closing it, it is possible that it is not yyet ready.
//
// =========================================================================================
// (C) Chess pT  2015-2016
// =========================================================================================


using System;
using System.IO.Ports;


namespace ChessPt.TlvCashRegisterLib
{
	/// <summary>
	/// Class handling the serial connection with the terminal.
	/// </summary>
	public class SerialConnectionHandler: ConnectionHandler
	{

		// The connection parameters.
		private string mComPort;									// The com port to use.
		private int mBaudRate = 115200;								// The baud rate to use.
		private int mDataBits = 8;									// The number of data bits to use.
		private Parity mParity = Parity.None;						// The parity to use.
		private StopBits mStopBits = StopBits.One;					// The number of stop bits to use.
		private Handshake mFlowControl = Handshake.RequestToSend;	// The flow control method to use.

		// The serial port used.
		SerialPort mSerialPort = null;


		/// <summary>
		/// Constructor with connection parameters and the callback interface.
		/// </summary>
		/// <param name="comPort">The COM port to listen to.</param>
		/// <param name="baudRate">The baud rate to use for the connection.</param>
		/// <param name="dataBits">The number of data bits to use for the connection.</param>
		/// <param name="parity">The parity to use for the connection.</param>
		/// <param name="stopBits">The number of stop bits to use for the connection.</param>
		/// <param name="flowControl">The flow control to use for the connection.</param>
		/// <param name="messageHandler">The callback interface to call when a message is received.</param>
		public SerialConnectionHandler(string comPort, int baudRate, int dataBits, Parity parity, StopBits stopBits, Handshake flowControl, IMessageHandler messageHandler): base (messageHandler)
		{
			mComPort = comPort;
			mBaudRate = baudRate;
			mDataBits = dataBits;
			mParity = parity;
			mStopBits = stopBits;
			mFlowControl = flowControl;
		}


		/// <summary>
		/// Make a connection.
		/// </summary>
		public override void Connect()
		{
			// Create the serial port.
			mSerialPort = new SerialPort(mComPort, mBaudRate, mParity, mDataBits, mStopBits);
			mSerialPort.Handshake = mFlowControl;

			// Open the serial port. Sometimes when the serial port is openend right after it was closed, it can't be openend. In that case, retry.
			int retryCounter = 5;
			while (!mSerialPort.IsOpen)
			{
				try
				{
					// Open serial port.
					mSerialPort.Open();
				}
				catch (UnauthorizedAccessException)
				{
					// Serial port could not be openend
					if (retryCounter-- != 0)
					{
						// try again.
						System.Threading.Thread.Sleep(100);
					}
					else
					{
						// Out of retries, throw exception.
						throw;
					}
				}
			}

			// Retrieve the stream.
			mStream = mSerialPort.BaseStream;
		}


		/// <summary>
		/// Close the connection.
		/// </summary>
		public override void Close()
		{
			// Only one can close the connection at the time.
			lock (this)
			{
				// Close the connection.
				base.Close();

				// Close the TCP client.
				if (mSerialPort != null)
				{
					mSerialPort.Close();
					mSerialPort = null;
				}
			}
		}

	}
}
