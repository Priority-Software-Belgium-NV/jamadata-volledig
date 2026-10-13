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
//		Class handling the network connection with the terminal.
//
//
//		Last Modification:
//		$Id:
//
// ----------------------------------------------------------------------------------------- 
//		Modifications:
//		Date		Author	Issue	Comment
//		2016-03-22	rdem			The Close() function is now "locked" so only one can close it at the same time.
//
// =========================================================================================
// (C) Chess pT  2015-2016
// =========================================================================================


using System.Net;
using System.Net.Sockets;

namespace ingenico.ConnectionHandler
{
    /// <summary>
    /// Class handling the network connection with the terminal.
    /// </summary>
    public class TcpConnectionHandler : ConnectionHandler
    {

        // The port to listen to.
        int mPort = 0;

        // The TCP listener waiting for a connection.
        private volatile TcpListener mTcpListener = null;

        // The TcpClient object doing the connection with the terminal.
        private volatile TcpClient mClient = null;


        /// <summary>
        /// Constructor with connection parameters and the callback interface.
        /// </summary>
        /// <param name="port">The port to listen to.</param>
        /// <param name="messageHandler">The callback interface to call when a message is received.</param>
        public TcpConnectionHandler(int port, IMessageHandler messageHandler)
            : base(messageHandler)
        {
            mPort = port;
        }


        /// <summary>
        /// Make a connection.
        /// </summary>
        public override void Connect()
        {
            try
            {
                // Start TCP listener.
                mTcpListener = new TcpListener(IPAddress.Any, mPort);
                mTcpListener.Start(1);

                // Wait for client.
                mClient = mTcpListener.AcceptTcpClient();
                mTcpListener.Stop();

                // Retrieve the network stream.
                mStream = mClient.GetStream();
            }
            finally
            {
                mTcpListener = null;
            }
        }


        /// <summary>
        /// Close the connection.
        /// </summary>
        public override void Close()
        {
            // Only one can close the connection at the time.
            lock (this)
            {

                // Stop the listener in case it is still listening.
                if (mTcpListener != null)
                {
                    mTcpListener.Stop();
                }

                // Close the connection.
                base.Close();

                // Close the TCP client.
                if (mClient != null)
                {
                    mClient.Close();
                    mClient = null;
                }
            }
        }
    }

}
