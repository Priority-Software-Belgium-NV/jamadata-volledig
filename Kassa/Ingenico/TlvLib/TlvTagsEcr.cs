// =========================================================================================
// ====================================== T L V L I B ======================================
// =========================================================================================
//
//		Module: TlvLib
//		File  : TlvTagsEcr.cs
//		Author: rdem
//
//
//		Description:
//		Enum for the ECR tag values.
//
//
//		Last Modification:
//		$Id:
//
// ----------------------------------------------------------------------------------------- 
//		Modifications:
//		Date		Author	Issue	Comment
//		2018-03-02	rdui			Added tags and message ID for security scheme and acquirer download, TMS session and print information.
//		2018-02-19	rdui			Added "TotalsType = 0x5F54" tag and TotalsType enum.
//		2017-11-20	rdem			Added TmStatusRequest and TmStatusResponse message types.
//		2017-10-23	rdem			Added ParameterMissing and ParameterInvalid error codes.
//		2017-10-19	rdem			Added TransactionMode tag, AutorisationCode tag, token tag and TransactionMode enum.
//		2017-10-05	rdem			Added version information message types, tags and enums.
//		2017-09-15	rdem			Added IntermediateResultMode enum.
//		2017-09-07	rdem			Added transparent mode tags.
//		2017-08-10	rdem			Added TransactionStage.CardDetected and TransactionStage.WaitingForIntermediateResult.
//		2017-06-29	lver			Added tag for UseIntermediateResult.
//
// =========================================================================================
// (C) Chess pT  2015-2018
// =========================================================================================


using System;

namespace TlvLib
{
	/// <summary>
	/// Enum for the ECR tag values.
	///
	/// Tag where the first octet has bit 6 set is a constructed TLV (build from other TLVs).
	/// Tags 2x, 3x, 6x, 7x, Ax, Bx, Ex and Fx are group tags.
	/// When bits 1-5 are all set (1F, 3F, 5F, 7F, 9F, BF, DF, FF), then the tag consists of more than one octet.
	/// </summary>
	public enum Tag: uint
	{
		// 1Fxx, 3Fxx, 5Fxx, 7Fxx, 9Fxx, BFxx, DFxx, FFxx ranges are multi-byte tags (FF could be also padding depending on use).

		// 0x primitive tags (general).
		TransactionStage				= 0x0E,			// InformationReport.
		StageMessage					= 0x0F,			// InformationReport.


		// 1x primitive tags (general).
		ProtocolId						= 0x10,			// Message header.
		MessageType						= 0x11,			// Message header.
		TerminalId						= 0x12,			// Message header.
		EcrId							= 0x13,			// Message header.
		SequenceNumber					= 0x14,			// Message header.
		KeepAliveReason					= 0x15,			// KeepAliveRequest/Response.
		ResultCode						= 0x16,			// General response.
		ByeReason						= 0x17,			// ByeRequest/Response.
		Language						= 0x18,			// HelloRequest/Response.
		TerminalState					= 0x19,			// General terminal state.
		TransactionId					= 0x1A,			// TransactionRequest/Response, InformationReport, LastTransactionTicketRequest/Response, LastTrasnactionStatusRequest/Response.
		PrintResult						= 0x1B,
		Mdc								= 0x1C,			// Message footer.
		MerchantText					= 0x1D,			// InformationReport.
		CancelReason					= 0x1E,			// CancelRequest/Response.

		// 1F0x multi-byte tags (Transparent mode).
		TmTransparentMode				= 0x1F01,
		TmCardDetectionTimeout			= 0x1F02,

		// 1F1x multi-byte tags (Transparent mode).
		TmCardUid						= 0x1F10,
		TmCardAtr						= 0x1F11,
		TmCardType						= 0x1F12,

		// 1F2x multi-byte tags (Transparent mode UI Control).
		TmDisplayText					= 0x1F20,
		TmBeepType						= 0x1F21,
		TmLedControl					= 0x1F22,

		// 1F3x multi-byte tags (Transparent mode authentication/read data/write data).
		TmKey							= 0x1F30,
		TmAddress						= 0x1F31,
		TmDataSize						= 0x1F32,
		TmData							= 0x1F33,

		// 1F7x multi-byte tags (additional transactiondata).
		AutorisationCode				= 0x1F70,		// Transaction data group.
		Token							= 0x1F71,		// Transaction data group.


		// 2x group tags.


		// 3x group tags.

		// 3F0x multi-byte group tags (Transparent mode groups).
		Group_TmTransparentMode			= 0x3F01,
		Group_TmUiControl				= 0x3F02,


		// 4x primitive tags (communication parameters, ticket data, print data).
		IpAddress						= 0x40,
		PortNumber						= 0x41,
		ConnectionTimeout				= 0x47,
		ConnectionRetries				= 0x48,
		KeepAliveInterval				= 0x49,			// HelloRequest/Response.
		TicketType						= 0x4A,			// Ticket data group.
		TicketHeader					= 0x4B,			// Ticket data group.
		TicketBody						= 0x4C,			// Ticket data group.
		TicketFooter					= 0x4D,			// Ticket data group.
		PrintOrigin						= 0x4E,			// Print data group.
		PaperWidth						= 0x4F,			// Print data group.


		// 5x primitive tags (transaction data, settings).
		Amount							= 0x50,			// Transaction data group, Transaction information group, IntermediateResultRequest/Response.
		CurrencyCode					= 0x51,			// Transaction data group, Transaction information group.
		CurrencyExponent				= 0x52,			// Transaction data group, Transaction information group.
		ProgressReportLanguage			= 0x53,			// Transaction data group, TotalsRequest.
		TransactionType					= 0x54,			// Transaction data group.
		MerchantTransactionReference	= 0x55,			// Transaction data group.
		TransactionResult				= 0x56,			// TransactionResponse, IntermediateResultRequest/Response, Transaction information group.
		TransactionDateTime				= 0x57,			// Transaction information group.
		IntermediateResultMode			= 0x58,			// Transaction data group, IntermediateResultRequest.
		TransactionMode					= 0x59,			// Transaction data group.
		SettingId						= 0x5A,
		SettingType						= 0x5B,
		SettingValue					= 0x5C,
		SettingResult					= 0x5D,

		// 5F5x multi-byte tags.
		TotalsType						= 0x5F54,		// TotalsRequest.
		PrintInfoType					= 0x5F55,		// PrintInfoRequest.


		// 6x group tags.


		// 7x group tags.
//		Multi-byte tag					= 0x7F,


		// 8x primitive tags.
		ApplicationId					= 0x80,			// VersionInformationRequest/Response.
		LogicalId						= 0x81,			// HelloRequest, VersionInformationResponse.
		SerialNumber					= 0x82,			// HelloRequest, VersionInformationResponse.
		VersionNumber					= 0x83,			// VersionInformationResponse.
		VersionString					= 0x84,			// VersionInformationResponse.
		ExtraInformationName			= 0x85,			// Extra information group.
		ExtraInformationValue			= 0x86,			// Extra information group.
		ExtraInformationUnit			= 0x87,			// Extra information group.


		// 9x primitive tags.
//		Multi-byte tag					= 0x9F,


		// Ax group tags.
		Group_EncryptionParameters		= 0xA0,			// Message header, HelloRequest/Response.
		Group_CommunicationParameters	= 0xA1,			// HelloRequest/Response.
		Group_SupportedLanguages		= 0xA2,			// HelloRequest.
		Group_TransactionData			= 0xA3,			// TransactionRequest.
		Group_ConnectionParameters		= 0xA4,			// HelloRequest/Response.
		Group_PrintData					= 0xA5,			// TransactionRequest, LastTransactionTicketRequest, TotalsRequest.
		Group_TicketData				= 0xA6,			// TransactionResponse, LastTransactionTicketResponse, TotalsResponse.
		Group_ExtraInformation			= 0xA7,			// VersionInformationResponse.
		Group_TransactionInformation	= 0xA8,			// LastTransactionTicketReponse.
		Group_TcpParameter				= 0xA9,
		Group_UsbParameters				= 0xAA,
		Group_SerialParameters			= 0xAB,
		Group_Settings					= 0xAC,
		Group_SettingsResult			= 0xAD,

		// Bx group tags.

		// BFxx multi-byte tags.
		Group_SecuritySchemeList		= 0xBF01,		// SecuritySchemeListResponse.


		// Cx primitive tags.
		RebootAndClearType				= 0xC1,			// RebootAndClearCtapDatabaseRequest.
		PendingMessagesOperation		= 0xC2,			// SendOrDeletePendingMessagesRequest.


		// Dx primitive tags.

		// DFxx multi-byte tags.
		CardHolderLanguage				= 0xDF1A,		// Transaction data group.
		CardBrandIdentifier				= 0xDF5F,		// TransactionResponse.
		AcquirerIdentifier				= 0xDF68,		// Acquirer list group, AcquirerDownloadRequest, SendOrDeletePendingMessagesRequest.
		AcquirerLabelName				= 0xDF69,		// Acquirer list group.

		// DF82xx multi-byte tags.
		SecuritySchemeIdentifier		= 0xDF8204,		// Security scheme list group, SecuritySchemeDownloadRequest.


		// Ex group tags (general group tags).
		Group_Header					= 0xE1,			// Header group.
		Group_Body						= 0xE2,			// Body group.
		Group_Footer					= 0xE3,			// Footer group.
		Group_AcquirerList				= 0xE7,			// AcquirerListResponse, AcquirerListPendingMessagesResponse.
		Group_TableRecord				= 0xEF,			// Used for repeated fields. e.g. The ticket data tag contains for each ticket a table record tag.


		// Fx group tags (root group tags).
		Group_Root						= 0xF0,
//		Multi-byte tag					= 0xFF,
	}


	/// <summary>
	/// Enum for message types (identifies the message body).
	/// </summary>
	public enum MessageType
	{
		HelloRequest							= 16,		// Request a connection with the ECR (terminal->ECR).
		HelloResponse							= 17,		// Result of the connection request (ECR->terminal).
		KeepAliveRequest						= 18,		// Notification of status and keep-alive (terminal->ECR).
		KeepAliveResponse						= 19,		// Result of the notification (ECR->terminal).
		ByeRequest								= 20,		// Request to terminate the connection (ECR->terminal, terminal->ECR).
		ByeResponse								= 21,		// Result of terminate connection request (terminal->ECR, ECR->terminal).

		AcquirerListRequest						= 30,		// Requests a list with available acquirers (used to select one for an acquirer download) (ECR->terminal).
		AcquirerListResponse					= 31,		// Result of the acquirer list request (terminal->ECR).
		AcquirerListPendingMessagesRequest		= 32,		// Requests a list with acquirers that have pending messages (used to select one for sending/deleting pending messages) (ECR->terminal).
		AcquirerListPendingMessagesResponse		= 33,		// Result of the acquirer list request (terminal->ECR).
		SendOrDeletePendingMessagesRequest		= 34,		// Request sending or deleting pending messages for the given acquirer (ECR->terminal).
		SendOrDeletePendingMessagesResponse		= 35,		// Not used.
		AcquirerDownLoadRequest					= 36,		// Request an acquirer download for the given acquirer (ECR->terminal).
		AcquirerDownLoadResponse				= 37,		// Not used.
		SecuritySchemeListRequest				= 38,		// Requests a list with available security-schemes (used to select one for an security-scheme download) (ECR->terminal).
		SecuritySchemeListResponse				= 39,		// Result of the security scheme list request (terminal->ECR).
		SecuritySchemeDownloadRequest			= 40,		// Request a keyload for the given acquirer (ECR->terminal).
		SecuritySchemeDownloadResponse			= 41,		// Not used.

		PrintInfoRequest						= 46,		// Request printing information.
		PrintInfoResponse						= 47,		// Result of the print information request.
		TransactionRequest						= 48,		// Request to perform a transaction (ECR->terminal).
		TransactionResponse						= 49,		// Result of the transaction (Terminal->ECR).
		TotalsRequest							= 50,		// Request an overview of the counters (print on terminal or send to ECR) (ECR->terminal).
		TotalsResponse							= 51,		// Result of the totals request (terminal->ECR).
		LastTransactionTicketRequest			= 52,		// Request the last ticket (print on terminal or send to ECR) (ECR->terminal).
		LastTransactionTicketResponse			= 53,		// Result of the last ticket request (terminal->ECR).
		CancelRequest							= 54,		// Request the cancellation of an on-going operation (ECR->terminal).
		CancelResponse							= 55,		// Result of the cancellation request (terminal->ECR).
		LastTransactionStatusRequest			= 56,		// Request the result of the last transaction (ECR->terminal).
		LastTransactionStatusResponse			= 57,		// Result of the last transaction request (terminal->ECR).
		PrintConfirmationRequest				= 64,		// Print confirmation from ECR to terminal when a card holder ticket must be printed on the ECR (ECR->terminal).
		PrintConfirmationResponse				= 65,		// Result of the print confirmation request (ECR->terminal).
		PrintRequest							= 66,		// Request to print some data (e.g. ECR ticket) on the terminal printer (ECR does not need a printer then) (ECR->terminal).
		PrintResponse							= 67,		// Result of the print request (terminal->ECR).
		IntermediateResultRequest				= 68,		// Request from ECR with the intermediate result (terminal->ECR).
		IntermediateResultResponse				= 69,		// Result of the intermediate result request (continue/abort transaction) (ECR->terminal).
		InformationReport						= 80,		// Report the progress of a transaction and other information like merchant messages (terminal-ECR).
		SettingsRequest							= 82,		// Change one or more settings in the terminal (ECR->terminal).
		SettingsResponse						= 83,		// Result of the change settings request (terminal->ECR).
		VersionInformationRequest				= 90,		// Request the version of the terminal software (ECR->terminal).
		VersionInformationResponse				= 91,		// Result of the version request (terminal->ECR).
		TmsSessionRequest						= 92,		// Request to perform a TMS session (ECR->terminal).
		TmsSessionResponse						= 93,		// Result of the TMS session request (terminal->ECR).
		RebootAndClearCtapDatabaseRequest		= 100,		// Reboot and clear the C-TAP database. There is no response on this command: the terminal will reboot.

		// Transparent mode messages.
		TmTransparentModeRequest				= 1000,		// Request to start or stop transparent mode (ECR->terminal).
		TmTransparentModeResponse				= 1001,		// Result of the request to start or stop transparent mode (terminal->ECR).
		TmUiControlRequest						= 1002,		// Request to update the user interface (buzzer, display, LEDs) when in transparent mode (ECR->terminal).
		TmUiControlResponse						= 1003,		// Result of the UI request (terminal->ECR).
		TmAuthenticateRequest					= 1004,		// Request to authenticate to the card when in transparent mode (ECR->terminal).
		TmAuthenticateResponse					= 1005,		// Result of the authenticate request (terminal->ECR).
		TmReadCardDataRequest					= 1006,		// Request to read data from the card when in transparent mode (ECR->terminal).
		TmReadCardDataResponse					= 1007,		// Result of the read card data request (terminal->ECR).
		TmWriteCardDataRequest					= 1008,		// Request to write data to the card when in transparent mode (ECR->terminal).
		TmWriteCardDataResponse					= 1009,		// Result of the write card data request (terminal->ECR).
		TmStatusRequest							= 1010,		//! Request the status of the transparent mode (ECR->terminal).
		TmStatusResponse						= 1011,		//! Result of the status request (terminal->ECR).
	}


	/// <summary>
	/// Enumeration specifying various error codes.
	/// </summary>
	public enum EcrResultCode
	{
		ResultOK					= 0,		// All OK, no problems.
		PrinterError				= 1,		// Printer problem.
		BatteryError				= 2,		// Battery problem (battery empty).
		NetworkError				= 3,		// There is no network connection (e.g. Ethernet cable unplugged, GPRS modem has low signal, no WiFi signal, etc.).
		RdmBusy						= 4,		// RDM is busy. Try again later.
		TdrFull						= 5,		// There is no space for TDRs.
		Cancelled					= 10,		// The operation is cancelled.
		CancelFailed				= 11,		// Could not cancel operation.
		Rejected					= 12,		// The request was rejected.
		NotAvailable				= 13,		// The requested data was not available.
		LastTicketNotPrinted		= 14,		// The last ticket was not yet printed.
		NoPendingPrintRequest		= 15,		// Send in response to a print confirmation when there was no pending print request for a card holder, merchant or journal ticket.
		IncompatibleVersion			= 16,		// A message was received that is incompatible (e.g. the protocol version is not supported).
		CardNotRemoved				= 17,		// A card was not removed.
		ParameterMissing			= 18,		// One of the required parameters is missing.
		ParameterInvalid			= 19,		// One of the parameters was invalid (wrong length, invalid value).

		// C-TAP errors.
		CtapBlocked					= 20,		// The terminal is blocked for payments.
		CtapInvalidAmount			= 21,		// The payment amount was not supported (e.g. too big).
		CtapInvalidCurrency			= 22,		// The selected currency was not supported.
		CtapCustomerAborted			= 23,		// The customer aborted.
		CtapMerchantAborted			= 24,		// The merchant aborted.
		CtapCardRemoved				= 25,		// The card was removed.
		CtapCardNotSupported		= 26,		// The card was not supported.
		CtapCardInvalid				= 27,		// The card was invalid.
		CtapCardProblem				= 28,		// Unknown card problem.
		CtapBusy					= 29,		// C-TAP is busy. Try again later.
		CtapError					= 30,		// Unspecified C-TAP error.

		// Transparent mode errors.
		TmError						= 1000,		// Unspecified transparent mode error.
		TmNotAvailable				= 1001,		// The transparent mode is not available/enabled on the terminal.
		TmTimeout					= 1002,		// A time-out occurred.
		TmNotInTransparentMode		= 1003,		// A transparent mode message was send while the terminal was not in transparent mode.
		TmAuthenticationFailed		= 1004,		// Failed to authenticate with the card.
		TmNotAuthenticated			= 1005,		// Request failed because authentication was not done.
		TmReadDataFailed			= 1006,		// Failed to read data from the card.
		TmWriteDataFailed			= 1007,		// Failed to write data to the card.
		TmAlreadyInTransparentMode	= 1008,		// The terminal was already in transparent mode.
	}


	/// <summary>
	/// Enumeration for the terminal state. Indicates which actions are possible.
	/// This is a bit field thus states can be combined. Thus states can be combined. If a bit is 0, the action is possible. If a bit is 1 it indicate an error.
	/// </summary>
	[Flags]
	public enum TerminalState
	{
		Transaction			= 0x0001,	// Payment transactions are possible.
		LastTransaction		= 0x0002,	// Retrieving the last transaction details is possible.
		LastTicket			= 0x0004,	// Retrieving/printing the last transaction ticket is possible.
		Totals				= 0x0008,	// Retrieving/printing the totals is possible.
		Bye					= 0x0010,	// Stopping the cash register interface is possible.
		BatteryLow			= 0x0020,	// When set the battery is low.
		Cancel				= 0x0040,	// Cancelling the current operation is possible.
		Printer				= 0x0080,	// The terminal's printer is available.
	}


	/// <summary>
	/// Enumeration to indicate the type of the totals request
	/// </summary>
	public enum TotalsType
	{
		X					= 1,	// X-totals.
		Z					= 2,	// Z-totals.
		PeriodCurrent		= 3,	// The current period totals.
		PeriodPrevious		= 4,	// The previous period totals.
		PeriodBoth			= 5,	// The previous and current period totals.
	};


	/// <summary>
	/// Enumeration to indicate the reason for stopping the cash register interface.
	/// </summary>
	public enum ByeReason
	{
		Deactivate		= 1,	// Deactivate the cash register interface (from ECR to terminal and from terminal to ECR).
		Shutdown		= 2,	// Terminal must do a shutdown (from ECR to terminal). Reconnect after reboot.
		Reboot			= 3,	// Terminal must do a reboot (from ECR to terminal) or is performing a reboot (from terminal to ECR when a software update is started). Reconnect after reboot.
		Reconnect		= 4,	// Terminal must reconnect (from ECR to terminal). Can be used to use new settings for a connection.
		BatteryEmpty	= 5,	// Terminal is performing a shutdown because of a low battery (from terminal to ECR).
	}


	/// <summary>
	/// Enumeration for supported message protocols.
	/// </summary>
	public enum MessageProtocol
	{
		Protobuf	= 1,	// Use Google Protocol Buffers.
		Tlv			= 2,	// Use the TagLengthValue message protocol.
		Xml			= 3,	// Use the XML (XSD schema) message protocol.
	}


	/// <summary>
	/// Enumeration for the keep-alive reason.
	/// </summary>
	public enum KeepAliveReason
	{
		Timer	= 1,	// Keep-alive was sent because the timer triggered.
		Status	= 2,	// Keep-alive was sent because the terminal status changed.
	}


	/// <summary>
	/// Enumeration for transaction type.
	/// See C-TAP 220 - Table 49 & C-TAP 200 - Table 14.
	/// </summary>
	public enum TransactionType
	{
		Payment							= 1,	// Payment (sale) transaction.
		CashAdvance						= 2,	// Cash advance transaction.
		PreAuthorization				= 3,	// Pre-authorisation (reservation) of funds.
		PaymentCompletion				= 4,	// Payment completion (after pre-authorisation) (sale after reservation of funds).
		CardValidityCheck				= 5,	// Card validity check.
		Refund							= 6,	// Refund transaction.
		DeferredPayment					= 7,	// Deferred payment (sale) transaction.
		Cancellation					= 9,	// Cancellation.
		CancellationPayment				= 10,	// Cancellation of payment transaction.
		CancellationCashAdvance			= 11,	// Cancellation of cash advance transaction.
		CancellationPreAuthorization	= 12,	// Cancellation of pre-authorisation transaction.
		CancellationPaymentCompletion	= 13,	// Cancellation of payment completion transaction.
		UpdatePreAuthorization			= 16,	// Update pre-authorization (reservation) of funds.
		OriginalCredit					= 17,	// OriginalCredit.
	}


	/// <summary>
	/// Enumeration for the transaction mode.
	/// </summary>
	public enum TransactionMode
	{
		Explicit						= 0,	// Explicit transaction mode.
		Implicit						= 1,	// Implicit transaction mode.
	};


	/// <summary>
	/// Enumeration for intermediate result modes.
	/// </summary>
	public enum IntermediateResultMode
	{
		None								= 0,	// Do not use intermediate result.
		IntermediateResult					= 1,	// Use intermediate result needing a response.
		IntermediateResultNoResponse		= 2,	// Use intermediate result that does not need a response.
	}


	/// <summary>
	/// Enumeration for transaction result.
	/// </summary>
	public enum TransactionResult
	{
		Approved			= 0,	// The transaction succeeded.
		Error				= 1,	// The transaction failed (Returned in TransactionResponse). See ResultCode for reason.
		Declined			= 2,	// The transaction was declined (Returned in LastTransactionResponse).
		Stopped				= 3,	// The transaction was stopped (Returned in LastTransactionResponse).
		TechnicalProblem	= 4,	// The transaction had a technical problem (Returned in LastTransactionResponse).
		TransparentMode		= 5,	//!< A non-EMV card was presented and transparent mode was started.
	}


	/// <summary>
	/// Enumeration for specifying where the printer output must go.
	/// The values are chosen to form a bit-field (bit 1 = terminal, bit 2 = printer).
	/// </summary>
	[Flags]
	public enum PrintOrigin
	{
		Terminal				= 1,	// Print on the terminal.
		CashRegister			= 2,	// Print on the cash register.
		TerminalAndCashRegister	= 3,	// Print on the terminal and cash register.
	}


	/// <summary>
	/// Enumeration for the ticket type.
	/// </summary>
	public enum TicketType
	{
		Merchant	= 1,		// Merchant ticket (e.g. with space for card holder signature). Often not generated.
		CardHolder	= 2,		// Card holder ticket. Always generated for a transaction.
		Journal		= 3,		// Journal ticket. Normally generated except when electronic journal is on and printing of journal is off.
		Totals		= 4,		// Totals ticket. Only generated when requesting totals.
	}
	

	/// <summary>
	/// Enumeration for the transaction stage.
	/// </summary>
	public enum TransactionStage
	{
		None									= 0,	// The terminal is not in a transaction.
		WaitingForCard							= 1,	// The terminal is waiting for a card.
		WaitingForPin							= 2,	// The terminal is waiting for a PIN code.
		WaitingForTransaction					= 3,	// The terminal is performing a transaction.
		Finished								= 4,	// The terminal is finished with a transaction.
		WaitingForTipInput						= 5,	// The terminal is waiting for a card holder TIP input.
		WaitingForConfirmationService			= 6,	// The terminal is waiting for a card holder service confirmation.
		WaitingForConfirmationAmount			= 7,	// The terminal is waiting for a card holder amount confirmation.
		WaitingForConfirmationServiceAndAmount	= 8,	// The terminal is waiting for a card holder service and amount confirmation.
		WaitingForCardRemoval					= 9,	// The terminal is waiting till the card is removed.
		WaitingForLastTransactionResult			= 10,	// The terminal is displaying the last transaction information on the terminal.
		WaitingForApplicationSelection			= 11,	// The terminal is waiting for the application selection (e.g. selection between chipknip, Maestro).
		CardDetected							= 12,	// Send when the terminal detected a card (cless) or when a card was inserted/swiped.
		WaitingForIntermediateResult			= 13,	// The terminal is waiting for the intermediate result from the cash register.
		CardRemoved								= 14,	// The card was removed.
	}


	/// <summary>
	/// Enumeration for cancellation reasons.
	/// </summary>
	public enum CancelReason
	{
		Manual		= 0,		// The cash register operator cancelled the operation.
		System		= 1,		// The cash register itself cancelled the operation.
	}
	

	/// <summary>
	/// Enumeration for the print result from the ECR to the terminal.
	/// </summary>
	public enum PrintResult
	{
		ResultOK	= 0,		// Printing on the ECR succeeded.
		Failed		= 1,		// Printing on the ECR failed.
	}


	/// <summary>
	/// Enumeration for the possible pending messages operations.
	/// </summary>
	public enum PendingMessagesOperation
	{
		Send		= 1,		// Send pending messages.
		Delete		= 2,		// Delete pending messages.
	}


	/// <summary>
	/// Enumeration for reboot and clear C-TAP database request.
	/// </summary>
	public enum RebootAndClearType
	{
		RebootOnly		= 0,	// Just reboot.
		PartialClear	= 1,	// Partially clear C-TAP database (acquirer data and totals are not deleted).
		FullClear		= 2,	// Fully clear the C-TAP database (only the totals are not deleted).
		Delete			= 3,	// Delete the C-TAP database and recreated it empty.
	}


	/// <summary>
	/// Enumeration to indicate the type of information to print.
	/// </summary>
	public enum PrintInfoType
	{
		CardBrandInfo	= 1,	// Print card brand information.
		CtapInfo		= 2,	// Print C-TAP information.
	};


	/// <summary>
	/// The application IDs used for requesting version information.
	/// </summary>
	public enum ApplicationId
	{
		Sdk		= 0,	// The terminal SDK.
		Rdm		= 1,	// The terminal RDM application.
		Ctap	= 2,	// The terminal C-TAP application.
		Ecr		= 3,	// The terminal ECR application.
		Tsc		= 4,	// The TSC application.
		Mdb		= 5,	// The MDB application.
		Custom	= 6,	// The custom payment application.
	}


	/// <summary>
	/// Enumeration for transparent mode beep types.
	/// </summary>
	public enum TmBeepType
	{
		Success		= 0,		// Three short success beeps.
		Failure		= 1,		// One long failure beep.
		Attention	= 2,		// One short attention beep.
	}


	/// <summary>
	/// Enumeration for LED control (bit field).
	/// </summary>
	[Flags]
	public enum TmLedControl
	{
		None		= 0x00,		// No LED.
		Led1		= 0x01,		// LED 1 (left most LED).
		Led2		= 0x02,		// LED 2.
		Led3		= 0x04,		// LED 3.
		Led4		= 0x08,		// LED 4 (right most LED).
		All			= 0x0F,		// All LEDs.
	};


	/// <summary>
	/// Enumeration for units.
	/// </summary>
	public enum Unit
	{
		None		= 0,	// No units.
		Bytes		= 1,	// Bytes.
		Seconds		= 2,	// Seconds.
		Bps			= 3,	// Bits/second.
	}


	/// <summary>
	/// Enumeration for unit prefixes.
	/// </summary>
	public enum UnitPrefix
	{
		Pico		= -12,
		Nano		= -9,
		Micro		= -6,
		Milli		= -3,
		Centi		= -2,
		Deci		= -1,
		None		= 0,
		Deca		= 1,
		Hecto		= 2,
		Kilo		= 3,
		Mega		= 6,
		Giga		= 9,
		Tera		= 12,
		Peta		= 15,
	}
}