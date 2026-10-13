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
//		Base class for handling connections with the terminal.
//
//
//		Last Modification:
//		$Id:
//
// ----------------------------------------------------------------------------------------- 
//		Modifications:
//		Date		Author	Issue	Comment
//		2018-03-02	rdui			Added handling of totals response, security scheme list response, acquirer list response, acquirer delelete message response and perform TMS session response.
//		2017-10-05	rdem			Added handling of version information messages.
//		2017-09-12	rdem			Added handling of transparent mode messages.
//		2017-08-25	rdem			Added handling of InformationReport, LastTransactionStatusResponse and LastTransactionTicketResponse.
//		2017-08-09	rdem			Added handling of CancelResponse.
//		2017-06-29	lver			Added processing of SignalIntermediateResultRequest.
//
// =========================================================================================
// (C) Chess pT  2015-2018
// =========================================================================================


using System;
using System.IO;


namespace ChessPt.TlvCashRegisterLib
{
	// Enum for the connection type.
	public enum ConnectionType
	{
		Tcp		= 0,
		Serial	= 1,
		Usb		= 2,
	}


	/// <summary>
	/// Base class for handling connections with the terminal.
	/// </summary>
	public abstract class ConnectionHandler
	{
		// The function to call when a message was received.
		private IMessageHandler mMessageHandler = null;

		// The stream to use object.
		protected volatile Stream mStream = null;


		/// <summary>
		/// Constructor with the message callback interface.
		/// </summary>
		/// <param name="messageHandler">The callback interface to call when a message is received.</param>
		public ConnectionHandler(IMessageHandler messageHandler)
		{
			mMessageHandler = messageHandler;
		}


		/// <summary>
		/// Make a connection.
		/// </summary>
		public abstract void Connect();


		/// <summary>
		/// Close the connection.
		/// </summary>
		public virtual void Close()
		{
			if (mStream != null)
			{
				mStream.Close();
				mStream = null;
			}
		}


		/// <summary>
		/// Process the messages from the terminal.
		/// </summary>
		public bool ProcessMessages()
		{
			byte[] buffer = new byte[4];

			// Try reading incoming messages.
			try
			{
				bool keepProcessing = true;
				while (keepProcessing)
				{
					// Read a message from the stream.
					TlvLib.TlvMessageEcr msg = new TlvLib.TlvMessageEcr();
					int bytesRead = msg.Deserialise(mStream);
					if (bytesRead <= 0) return false;

					// Determine the message type and handle the message.
					TlvLib.Tlv tlvMessageId = msg.Header.FindTlv((uint)TlvLib.Tag.MessageType);
					if (tlvMessageId == null) continue;


					TlvLib.MessageType messageType = (TlvLib.MessageType)tlvMessageId.GetValueUInt32FromBcd();
					switch (messageType)
					{
						// Handle an incoming "hello request" message.
						case TlvLib.MessageType.HelloRequest:
						{
							keepProcessing = mMessageHandler.HandleHelloRequest(msg);
							ConnectionHandler.WriteToFile(msg, "HelloRequest.msg");
							break;
						}

						// Handle an incoming "keep-alive request" message.
						case TlvLib.MessageType.KeepAliveRequest:
						{
							keepProcessing = mMessageHandler.HandleKeepAliveRequest(msg.Body);
							ConnectionHandler.WriteToFile(msg, "KeepAliveRequest.msg");
							break;
						}

						// Handle an incoming "bye response" message.
						case TlvLib.MessageType.ByeResponse:
						{
							keepProcessing = mMessageHandler.HandleByeResponse(msg.Body);
							ConnectionHandler.WriteToFile(msg, "ByeResponse.msg");
							break;
						}

						// Handle an incoming "transaction response" message.
						case TlvLib.MessageType.TransactionResponse:
						{
							keepProcessing = mMessageHandler.HandleTransactionResponse(msg.Body);
							ConnectionHandler.WriteToFile(msg, "TransactionResponse.msg");
							break;
						}

						// Handle an incoming "intermediate result request" message.
						case TlvLib.MessageType.IntermediateResultRequest:
						{
							keepProcessing = mMessageHandler.HandleSignalIntermediateResultRequest(msg.Body);
							ConnectionHandler.WriteToFile(msg, "SignalIntermediateResultRequest.msg");
							break;
						}

						// Handle an incoming "cancel response" message.
						case TlvLib.MessageType.CancelResponse:
						{
							keepProcessing = mMessageHandler.HandleCancelResponse(msg.Body);
							ConnectionHandler.WriteToFile(msg, "CancelResponse.msg");
							break;
						}

						// Handle an incoming "information report" message.
						case TlvLib.MessageType.InformationReport:
						{
							keepProcessing = mMessageHandler.HandleInformationReport(msg.Body);
							ConnectionHandler.WriteToFile(msg, "InformationReport.msg");
							break;
						}

						// Handle an incoming "last transaction status response" message.
						case TlvLib.MessageType.LastTransactionStatusResponse:
						{
							keepProcessing = mMessageHandler.HandleLastTransactionStatusResponse(msg.Body);
							ConnectionHandler.WriteToFile(msg, "LastTransactionStatusResponse.msg");
							break;
						}

						// Handle an incoming "last transaction ticket response" message.
						case TlvLib.MessageType.LastTransactionTicketResponse:
						{
							keepProcessing = mMessageHandler.HandleLastTransactionTicketResponse(msg.Body);
							ConnectionHandler.WriteToFile(msg, "LastTransactionTicketResponse.msg");
							break;
						}

						// Handle an incoming "totals response" message.
						case TlvLib.MessageType.TotalsResponse:
						{
							keepProcessing = mMessageHandler.HandleTotalsResponse(msg.Body);
							ConnectionHandler.WriteToFile(msg, "TransactionResponse.msg");
							break;
						}

						// Handle an incoming "acquirer list response" message.
						case TlvLib.MessageType.AcquirerListResponse:
						{
							keepProcessing = mMessageHandler.HandleAcquirerListResponse(msg.Body);
							ConnectionHandler.WriteToFile(msg, "AcquirerListResponse.msg");
							break;
						}

						// Handle an incoming "acquirer del msg list response" message.
						case TlvLib.MessageType.AcquirerListPendingMessagesResponse:
						{
							keepProcessing = mMessageHandler.HandleAcquirerListPendingMessagesResponse(msg.Body);
							ConnectionHandler.WriteToFile(msg, "AcquirerDelMsgListResponse.msg");
							break;
						}

						// Handle an incoming "security scheme list response" message.
						case TlvLib.MessageType.SecuritySchemeListResponse:
						{
							keepProcessing = mMessageHandler.HandleSecuritySchemeListResponse(msg.Body);
							ConnectionHandler.WriteToFile(msg, "SecuritySchemeListResponse.msg");
							break;
						}

						// Handle an incoming "perform TMS session response" message.
						case TlvLib.MessageType.TmsSessionResponse:
						{
							keepProcessing = mMessageHandler.HandleTmsSessionResponse(msg.Body);
							ConnectionHandler.WriteToFile(msg, "TmsSessionResponse.msg");
							break;
						}

						// Handle an incoming "version information response" message.
						case TlvLib.MessageType.VersionInformationResponse:
						{
							keepProcessing = mMessageHandler.HandleVersionInformationResponse(msg.Body);
							ConnectionHandler.WriteToFile(msg, "VersionInformationResponse.msg");
							break;
						}

						// Handle an incoming "print info response" message.
						case TlvLib.MessageType.PrintInfoResponse:
						{
							keepProcessing = mMessageHandler.HandleTotalsResponse(msg.Body); // (mis)use HandleTotalsResponse to print the ticket
							ConnectionHandler.WriteToFile(msg, "PrintInfoResponse.msg");
							break;
						}


						// Transparent mode.

						// Handle an incoming "transparent mode" response message.
						case TlvLib.MessageType.TmTransparentModeResponse:
						{
							keepProcessing = mMessageHandler.HandleTmTransparentModeResponse(msg.Body);
							ConnectionHandler.WriteToFile(msg, "TmTransparentModeResponse.msg");
							break;
						}

						// Handle an incoming transparent mode "UI control" response message.
						case TlvLib.MessageType.TmUiControlResponse:
						{
							keepProcessing = mMessageHandler.HandleTmUiControlResponse(msg.Body);
							ConnectionHandler.WriteToFile(msg, "TmUiControlResponse.msg");
							break;
						}

						// Handle an incoming transparent mode "authenticate" response message.
						case TlvLib.MessageType.TmAuthenticateResponse:
						{
							keepProcessing = mMessageHandler.HandleTmAuthenticateResponse(msg.Body);
							ConnectionHandler.WriteToFile(msg, "TmAuthenticateResponse.msg");
							break;
						}

						// Handle an incoming transparent mode "read card data" response message.
						case TlvLib.MessageType.TmReadCardDataResponse:
						{
							keepProcessing = mMessageHandler.HandleTmReadCardDataResponse(msg.Body);
							ConnectionHandler.WriteToFile(msg, "TmUiReadCardDataResponse.msg");
							break;
						}

						// Unrecognised message received.
						default:
						{
//							mMessageHandler.HandleStringMessage(String.Format("Unrecognised message received: {0}.", command));
							keepProcessing = false;
							break;
						}
					}

				}
			}
			catch (Exception ex)
			{
//				mMessageHandler.HandleStringMessage(String.Format("Error occurred, stopping message processing.\n{0}", ex.Message));
				System.Diagnostics.Debug.WriteLine("ConnectionHandler::ProcessMessages(): Exception: {0}.", ex);
				return false;
			}
			finally
			{
				// Always close the connection.
				Close();
			}

			// All OK, just disconnected.
			return true;
		}

	  
		/// <summary>
		/// Send a message to the terminal.
		/// </summary>
		/// <param name="message">The message to send.</param>
		public void SendMessage(TlvLib.TlvMessageEcr message)
		{
			message.Serialise(mStream);
			mStream.Flush();
		}


		/// <summary>
		/// Send a message to the terminal (binary format, only for debugging messages).
		/// </summary>
		/// <param name="message">The message to send in binary format.</param>
		public void SendMessage(byte[] message)
		{
			mStream.Write(message, 0, message.Length);
			mStream.Flush();
		}


		/// <summary>
		/// Write a message to a file.
		/// </summary>
		/// <param name="msg">The message to write.</param>
		/// <param name="path">The path of the file to write to.</param>
		public static void WriteToFile(TlvLib.TlvMessageEcr msg, string path)
		{
			System.IO.FileStream s = System.IO.File.Open(path, FileMode.Create);
			msg.Serialise(s);
			s.Close();
		}
	}
}
