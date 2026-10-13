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


using TlvLib;

namespace ingenico.ConnectionHandler
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
        bool HandleHelloRequest(TlvMessageEcr tlvMessage);
        bool HandleKeepAliveRequest(TlvConstructed tlvMessage);
        bool HandleByeResponse(TlvConstructed tlvMessage);
        bool HandleTransactionResponse(TlvConstructed tlvMessage);
        bool HandleSignalIntermediateResultRequest(TlvConstructed tlvMessage);
        bool HandleCancelResponse(TlvConstructed tlvMessage);
        bool HandleInformationReport(TlvConstructed tlvMessage);
        bool HandleTmsSessionResponse(TlvConstructed tlvMessage);
        bool HandleLastTransactionStatusResponse(TlvConstructed tlvMessage);
        bool HandleLastTransactionTicketResponse(TlvConstructed tlvMessage);
        bool HandleTotalsResponse(TlvConstructed tlvMessage);
        ////bool HandleSecuritySchemeListResponse(ChessPt.TlvLib.TlvConstructed tlvMessage);
        ////bool HandleAcquirerListResponse(ChessPt.TlvLib.TlvConstructed tlvMessage);
        ////bool HandleAcquirerListPendingMessagesResponse(ChessPt.TlvLib.TlvConstructed tlvMessage);
        bool HandleVersionInformationResponse(TlvConstructed tlvMessage);

        //		bool HandleDisconnectMessage();
        //		bool HandleStringMessage(string message);

        // Transparent mode.
        bool HandleTmTransparentModeResponse(TlvConstructed tlvMessage);
        bool HandleTmUiControlResponse(TlvConstructed tlvMessage);
        bool HandleTmAuthenticateResponse(TlvConstructed tlvMessage);
        bool HandleTmReadCardDataResponse(TlvConstructed tlvMessage);
    }

    
}
