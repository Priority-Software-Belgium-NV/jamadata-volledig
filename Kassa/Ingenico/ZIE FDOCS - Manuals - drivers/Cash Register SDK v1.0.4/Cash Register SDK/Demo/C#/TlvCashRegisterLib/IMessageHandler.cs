// =========================================================================================
// ======================== T E L I U M   C A S H   R E G I S T E R ========================
// =========================================================================================
//
//		Module: TlvCashRegisterLib
//		File  : IMessageHandler.cs
//		Author: rdem
//
//
//		Description:
//		Interface to handle incoming messages.
//
//
//		Last Modification:
//		$Id:
//
// ----------------------------------------------------------------------------------------- 
//		Modifications:
//		Date		Author	Issue	Comment
//		2018-03-02	rdui			Added HandleTotalsResponse, HandleSecuritySchemeListResponse, HandleAcquirerListResponse and HandleAcquirerDelMsgListResponse.
//		2017-10-05	rdem			Added HandleVersionInformationResponse.
//		2017-09-12	rdem			Added handling of transparent mode messages.
//		2017-08-25	rdem			Added HandleInformationReport(), HandleLastTransactionStatusResponse() & HandleLastTransactionTicketResponse().
//		2017-08-09	rdem			Added HandleCancelResponse().
//		2017-06-29	lver			Added HandleSignalIntermediateResultRequest().
//
// ==========================================================================================
// (C) Chess pT  2015-2018
// ==========================================================================================


namespace ChessPt.TlvCashRegisterLib
{
	/// <summary>
	/// Simple class for security scheme data.
	/// </summary>
	public class SecurityScheme
	{
		public int SecurityId;
		public string Name;
	}


	/// <summary>
	/// Simple class for acquirer data.
	/// </summary>
	public class Acquirer
	{
		public int AcquirerId;
		public string Name;
	}


	/// <summary>
	/// Interface to handle incoming messages.
	/// </summary>
	public interface IMessageHandler
	{
		bool HandleHelloRequest(TlvLib.TlvMessageEcr tlvMessage);
		bool HandleKeepAliveRequest(TlvLib.TlvConstructed tlvMessage);
		bool HandleByeResponse(TlvLib.TlvConstructed tlvMessage);
		bool HandleTransactionResponse(TlvLib.TlvConstructed tlvMessage);
		bool HandleSignalIntermediateResultRequest(TlvLib.TlvConstructed tlvMessage);
		bool HandleCancelResponse(TlvLib.TlvConstructed tlvMessage);
		bool HandleInformationReport(TlvLib.TlvConstructed tlvMessage);
		bool HandleTmsSessionResponse(TlvLib.TlvConstructed tlvMessage);
		bool HandleLastTransactionStatusResponse(TlvLib.TlvConstructed tlvMessage);
		bool HandleLastTransactionTicketResponse(TlvLib.TlvConstructed tlvMessage);
		bool HandleTotalsResponse(TlvLib.TlvConstructed tlvMessage);
		bool HandleSecuritySchemeListResponse(TlvLib.TlvConstructed tlvMessage);
		bool HandleAcquirerListResponse(TlvLib.TlvConstructed tlvMessage);
		bool HandleAcquirerListPendingMessagesResponse(TlvLib.TlvConstructed tlvMessage);
		bool HandleVersionInformationResponse(TlvLib.TlvConstructed tlvMessage);

		//		bool HandleDisconnectMessage();
		//		bool HandleStringMessage(string message);

		// Transparent mode.
		bool HandleTmTransparentModeResponse(TlvLib.TlvConstructed tlvMessage);
		bool HandleTmUiControlResponse(TlvLib.TlvConstructed tlvMessage);
		bool HandleTmAuthenticateResponse(TlvLib.TlvConstructed tlvMessage);
		bool HandleTmReadCardDataResponse(TlvLib.TlvConstructed tlvMessage);
	}
}
