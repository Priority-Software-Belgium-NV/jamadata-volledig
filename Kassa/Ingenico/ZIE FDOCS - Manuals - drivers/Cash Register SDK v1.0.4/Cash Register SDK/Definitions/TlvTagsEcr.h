//! Enum for the ECR tag values.
/*!
 * Tag where the first octet has bit 6 set is a constructed TLV (build from other TLVs).
 * Therefore the numbers here are not always the same as in the Cash Register Interface IDD document (also numbering reorganised to group related tags).
 * Tags 2x, 3x, 6x, 7x, Ax, Bx, Ex and Fx are group tags.
 * When bits 1-5 are all set (1F, 3F, 5F, 7F, 9F, BF, DF, FF), then the tag consists of more than one octet.
 */
struct Tag
{
	enum EnumType
	{
		// 1Fxx, 3Fxx, 5Fxx, 7Fxx, 9Fxx, BFxx, DFxx, FFxx ranges are multi-byte tags (FF could be also padding depending one use).

		// Header, body, footer primitive tags.
		TransactionStage				= 0x0E,
		StageMessage					= 0x0F,
		ProtocolId						= 0x10,
		MessageType						= 0x11,
		TerminalId						= 0x12,
		EcrId							= 0x13,
		SequenceNumber					= 0x14,
		KeepAliveReason					= 0x15,
		ResultCode						= 0x16,
		ByeReason						= 0x17,
		Language						= 0x18,
		TerminalState					= 0x19,
		TransactionId					= 0x1A,
		PrintResult						= 0x1B,
		Mdc								= 0x1C,
		MerchantText					= 0x1D,
		CancelReason					= 0x1E,

		// 1Fxx, 3Fxx multi-byte tags.
		// ...


		// Communication parameter group tags.
		IpAddress						= 0x40,
		PortNumber						= 0x41,


		// Connection parameters groups tags.
		ConnectionTimeout				= 0x47,
		ConnectionRetries				= 0x48,
		KeepAliveInterval				= 0x49,


		// Ticket data group tags.
		TicketType						= 0x4A,
		TicketHeader					= 0x4B,
		TicketBody						= 0x4C,
		TicketFooter					= 0x4D,


		// Print data group.
		PrintOrigin						= 0x4E,
		PaperWidth						= 0x4F,


		// Transaction (information) group tags.
		Amount							= 0x50,
		CurrencyCode					= 0x51,
		CurrencyExponent				= 0x52,	// Named Decimal in IDD.
		ProgressReportLanguage			= 0x53,
		TransactionType					= 0x54,
		MerchantTransactionReference	= 0x55,
		TransactionResult				= 0x56,
		TransactionDateTime				= 0x57,
		IntermediateResultMode			= 0x58,
		TransactionMode					= 0x59,
		AuthorisationCode				= 0x1F70,
		Token							= 0x1F71,

		// Settings (result) group.
		SettingId						= 0x5A,
		SettingType						= 0x5B,
		SettingValue					= 0x5C,
		SettingResult					= 0x5D,
		// 0x5E already used.

		// 5Fxx, 7Fxx multi-byte tags.
		// ...
		TotalsType						= 0x5F54,
		InfoType						= 0x5F55,

		// Version information tags.
		ApplicationId					= 0x80,
		LogicalId						= 0x81,
		SerialNumber					= 0x82,
		VersionNumber					= 0x83,
		VersionString					= 0x84,
		ExtraInformationName			= 0x85,
		ExtraInformationValue			= 0x86,
		ExtraInformationUnit			= 0x87,


		// 9Fxx multi-byte tags.
		// ...


		// Group tags.
		Group_EncryptionParameters		= 0xA0,
		Group_CommunicationParameters	= 0xA1,
		Group_SupportedLanguages		= 0xA2,
		Group_TransactionData			= 0xA3,
		Group_ConnectionParameters		= 0xA4,
		Group_PrintData					= 0xA5,
		Group_TicketData				= 0xA6,
		Group_ExtraInformation			= 0xA7,
		Group_TransactionInformation	= 0xA8,
		Group_TcpParameter				= 0xA9,
		Group_UsbParameters				= 0xAA,
		Group_SerialParameters			= 0xAB,
		Group_Settings					= 0xAC,
		Group_SettingsResult			= 0xAD,


		// BFxx, DFxx multi-byte tags.
		// ...


		// General group tags.
		Group_Header					= 0xE1,
		Group_Body						= 0xE2,
		Group_Footer					= 0xE3,
		Group_TableRecord				= 0xEF,	// Used for repeated fields. e.g. The ticket data tag contains for each ticket a table record tag.
		Group_Root						= 0xF0,


		/* Transparent Mode */

		// Transparent mode tags.
		TmTransparentMode				= 0x1F01,
		TmCardDetectionTimeout			= 0x1F02,
		TmCardUid						= 0x1F10,
		TmCardAtr						= 0x1F11,
		TmCardType						= 0x1F12,

		// Transparent mode UI Control tags.
		TmDisplayText					= 0x1F20,
		TmBeepType						= 0x1F21,
		TmLedControl					= 0x1F22,

		// Transparent mode authentication/read data/write data tags.
		TmKey							= 0x1F30,
		TmAddress						= 0x1F31,
		TmDataSize						= 0x1F32,
		TmData							= 0x1F33,

		// Transparent mode groups.
		Group_TmTransparentMode			= 0x3F01,
		Group_TmUiControl				= 0x3F02,

		RebootAndClearType				= 0xC1,
		SendOrDelete					= 0xC2, // used for pending messages : 1=send 2=delete

		Group_AcquirerList				= 0xE7, // group : AcquirerIdentifier=0xDF68,  AcquirerLabelName=0xDF69
		Group_SecuritySchemeList		= 0xBF01, // group : SecuritySchemeIdentifier=0xDF6A,  SecuritySchemeLabelName=0xDF6B

		CardholderLanguage				= 0xDF1A,
		Card_Brand_Identifier			= 0xDF5F, // format=4i, size=2

		SecuritySchemeIdentifier		= 0xDF8204,

		AcquirerIdentifier				= 0xDF68,
		AcquirerLabelName				= 0xDF69,
	};
};



//! Enum for message types (identifies the message body).
struct MessageType
{
	enum EnumType
	{
		HelloRequest					= 16,		//!< Request a connection with the ECR.
		HelloResponse					= 17,		//!< Result of the connection request.
		KeepAliveRequest				= 18,		//!< Notification of status and keep-alive.
		KeepAliveResponse				= 19,		//!< Result of the notification.
		ByeRequest						= 20,		//!< Request to terminate the connection.
		ByeResponse						= 21,		//!< Result of terminate connection request.

        AcquirerDownloadListRequest     = 30,       // The ECR Requests CTAP to give a list with available acquirers (used to select one for an acquirer download)
        AcquirerDownloadListResponse    = 31,       // CTAP sends the ECR a list of available acquirers (used to select one for an acquirer download)
        AcquirerDelMsgListRequest       = 32,       // The ECR Requests CTAP to give a list with available acquirers (used to select one for an acquirer download)
        AcquirerDelMsgListResponse      = 33,       // CTAP sends the ECR a list of available acquirers (used to select one for an acquirer download)
        AcquirerDelMsgRequest           = 34,       // The ECR Requests CTAP to give a list with available acquirers (used to select one for an acquirer download)
        AcquirerDelMsgResponse          = 35,       // CTAP sends the ECR a list of available acquirers (used to select one for an acquirer download)
        PerformAcqDownLoadRequest       = 36,
        PerformAcqDownLoadResponse      = 37,
        SecuritySchemeListRequest       = 38,       // The ECR Requests CTAP to give a list with available security-schemes (used to select one for an security-scheme download)
        SecuritySchemeListResponse      = 39,        // CTAP sends the ECR a list of available security-schemes (used to select one for an security-scheme download)
        PerformKeyLoadRequest           = 40,
        PerformKeyLoadResponse          = 41,

		PrintInfoRequest			= 46,
		PrintInfoResponse			= 47,
		TransactionRequest			= 48,		//!< Request to perform a transaction.
		TransactionResponse			= 49,		//!< Result of the transaction.
		TotalsRequest				= 50,		//!< Request an overview of the counters (print on terminal or send to ECR).
		TotalsResponse				= 51,		//!< Result of the totals request.
		LastTicketRequest			= 52,		//!< Request the last ticket (print on terminal or send to ECR). (Was called print request in IDD).
		LastTicketResponse			= 53,		//!< Result of the last ticket request. (Was called print response in IDD).
		CancelRequest				= 54,		//!< Request the cancellation of an on-going operation.
		CancelResponse				= 55,		//!< Result of the cancellation request.
		LastTransactionRequest		= 56,		//!< Request the result of the last transaction.
		LastTransactionResponse		= 57,		//!< Result of the last transaction request.
		PrintConfirmationRequest	= 64,		//!< Print confirmation from ECR to terminal when a card holder ticket must be printed on the ECR.
		PrintConfirmationResponse	= 65,		//!< Print confirmation from ECR to terminal when a card holder ticket must be printed on the ECR.
		PrintRequest				= 66,		//!< Request to print some data (e.g. ECR ticket) on the terminal printer. (ECR does not need a printer then) (this message is not in IDD).
		PrintResponse				= 67,		//!< Result of the print request (this message is not in IDD).
		IntermediateResultRequest	= 68,		//!< Request with the intermediate result.
		IntermediateResultResponse	= 69,		//!< Result of the intermediate result request (continue/abort transaction).
		InformationReport			= 80,		//!< Report the progress of a transaction and other information like merchant messages.
		SettingsRequest				= 82,		//!< Change one or more settings in the terminal.
		SettingsResponse			= 83,		//!< Result of the change settings request.
		VersionInformationRequest	= 90,		//!< Request the version of the terminal software
		VersionInformationResponse	= 91,		//!< Result of the version request.
		PerformTmsSessionReuqest	= 92,
		PerformTmsSessionResponse	= 93,
        RebootAndClearCtapDataBaseRequest = 100,    // there is no response on this command: the terminal will reboot

		// Transparent mode messages.
		TmTransparentModeRequest	= 1000,		//!< Request to start or stop transparent mode.
		TmTransparentModeResponse	= 1001,		//!< Result of the request to start or stop transparent mode.
		TmUiControlRequest			= 1002,		//!< Request to update the user interface (buzzer, display, LEDs) when in transparent mode.
		TmUiControlResponse			= 1003,		//!< Result of the UI request.
		TmAuthenticateRequest		= 1004,		//!< Request to authenticate to the card when in transparent mode.
		TmAuthenticateResponse		= 1005,		//!< Result of the authenticate request.
		TmReadCardDataRequest		= 1006,		//!< Request to read data from the card when in transparent mode.
		TmReadCardDataResponse		= 1007,		//!< Result of the read card data request.
		TmWriteCardDataRequest		= 1008,		//!< Request to write data to the card when in transparent mode.
		TmWriteCardDataResponse		= 1009,		//!< Result of the write card data request.
		TmStatusRequest				= 1010,		//!< Request the status of the transparent mode.
		TmStatusResponse			= 1011,		//!< Result of the status request.
	};
};


//! Enumeration specifying various error codes.
struct EcrResultCode
{
	enum EnumType
	{
		ResultOK					= 0,	//!< All OK, no problems.
		PrinterError				= 1,	//!< Printer problem.
		BatteryError				= 2,	//!< Battery problem (battery empty).
		ModemError					= 3,	//!< Modem problem (low signal).
		RdmBusy						= 4,	//!< RDM is busy. Try again later.
		TdrFull						= 5,	//!< There is no space for TDRs.
		Cancelled					= 10,	//!< The operation is cancelled.
		CancelFailed				= 11,	//!< Could not cancel operation.
		Rejected					= 12,	//!< The request was rejected.
		NotAvailable				= 13,	//!< The requested data was not available.
		LastTicketNotPrinted		= 14,	//!< The last ticket was not yet printed.
		NoPendingPrintRequest		= 15,	//!< Send in response to a print confirmation when there was no pending print request for a card holder, merchant or journal ticket.
		IncompatibleVersion			= 16,	//!< A message was received that is incompatible (e.g. the protocol version is not supported).
		CardNotRemoved				= 17,	//!< A card was not removed.
		ParameterMissing			= 18,	//!< One of the required parameters is missing.
		ParameterInvalid			= 19,	//!< One of the parameters was invalid (wrong length, invalid value).

		// C-TAP errors.
		CtapBocked					= 20,	//!< The terminal is blocked for payments.
		CtapInvalidAmount			= 21,	//!< The payment amount was not supported (e.g. too big).
		CtapInvalidCurrency			= 22,	//!< The selected currency was not supported.
		CtapCustomerAborted			= 23,	//!< The customer aborted.
		CtapMerchantAborted			= 24,	//!< The merchant aborted.
		CtapCardRemoved				= 25,	//!< The card was removed.
		CtapCardNotSupported		= 26,	//!< The card was not supported.
		CtapCardInvalid				= 27,	//!< The card was invalid.
		CtapCardProblem				= 28,	//!< Unknown card problem.
		CtapBusy					= 29,	//!< C-TAP is busy. Try again later.
		CtapError					= 30,	//!< Unspecified C-TAP error.

		// Transparent mode errors.
		TmError						= 1000,	//!< Unspecified transparent mode error.
		TmNotAvailable				= 1001,	//!< The transparent mode is not available/enabled on the terminal.
		TmTimeout					= 1002,	//!< A time-out occurred.
		TmNotInTransparentMode		= 1003,	//!< A transparent mode message was send while the terminal was not in transparent mode.
		TmAuthenticationFailed		= 1004,	//!< Failed to authenticate with the card.
		TmNotAuthenticated			= 1005,	//!< Request failed because authentication was not done.
		TmReadDataFailed			= 1006,	//!< Failed to read data from the card.
		TmWriteDataFailed			= 1007,	//!< Failed to write data to the card.
		TmAlreadyInTransparentMode	= 1008,	//!< The terminal was already in transparent mode.
	};
};


//! Enumeration for the terminal state. Indicates which actions are possible.
/*!
 * This is a bit field thus states can be combined. Thus states can be combined. If a bit is 0, the action is possible. If a bit is 1 it indicates an error.
 */
struct TerminalState
{
	enum
	{
		Transaction			= 0x0001,	//!< Payment transactions are possible.
		LastTransaction		= 0x0002,	//!< Retrieving the last transaction details is possible.
		LastTicket			= 0x0004,	//!< Retrieving/printing the last transaction ticket is possible.
		Totals				= 0x0008,	//!< Retrieving/printing the totals is possible.
		Bye					= 0x0010,	//!< Stopping the cash register interface is possible.
		BatteryLow			= 0x0020,	//!< When set the battery is low.
		Cancel				= 0x0040,	//!< Canceling the current operation is possible.
		Printer				= 0x0080,	//!< The terminal's printer is available.
	};
};


//! Enumeration to indicate the reason for stopping the cash register interface.
struct ByeReason
{
	enum EnumType
	{
		Deactivate		= 1,	//!< Deactivate the cash register interface (from ECR to terminal and from terminal to ECR).
		Shutdown		= 2,	//!< Terminal must do a shutdown (from ECR to terminal). Reconnect after reboot.
		Reboot			= 3,	//!< Terminal must do a reboot (from ECR to terminal) or is performing a reboot (from terminal to ECR when a software update is started). Reconnect after reboot.
		Reconnect		= 4,	//!< Terminal must reconnect (from ECR to terminal). Can be used to use new settings for a connection.
		BatteryEmpty	= 5,	//!< Terminal is performing a shutdown because of a low battery (from terminal to ECR).
	};
};


//! Enumeration for supported message protocols.
struct MessageProtocol
{
	enum EnumType
	{
		Protobuf	= 1,	//!< Use Google Protocol Buffers.
		Tlv			= 2,	//!< Use the TagLengthValue message protocol.
		Xml			= 3,	//!< Use the XML (XSD schema) message protocol.
	};
};


//! Enumeration for the keep-alive reason.
struct KeepAliveReasonTag
{
	enum EnumType
	{
		Timer	= 1,	//!< Keep-alive was sent because the timer triggered.
		Status	= 2,	//!< Keep-alive was sent because the terminal status changed.
	};
};


//! Enumeration for transaction type. See C-TAP 220 - Table 49 & C-TAP 200 - Table 14.
struct TransactionType
{
	enum EnumType
	{
		Payment							= 1,	//!< Payment (sale) transaction.
		CashAdvance						= 2,	//!< Cash advance transaction.
		PreAuthorization				= 3,	//!< Pre-authorisation (reservation) of funds.
		PaymentCompletion				= 4,	//!< Payment completion (after pre-authorisation) (sale after reservation of funds).
		CardValidityCheck				= 5,	//!< Card validity check.
		Refund							= 6,	//!< Refund transaction.
		DeferredPayment					= 7,	//!< Deferred payment (sale) transaction.
		Cancellation					= 9,	//!< Cancellation.
		CancellationPayment				= 10,	//!< Cancellation of payment transaction.
		CancellationCashAdvance			= 11,	//!< Cancellation of cash advance transaction.
		CancellationPreAuthorization	= 12,	//!< Cancellation of pre-authorisation transaction.
		CancellationPaymentCompletion	= 13,	//!< Cancellation of payment completion transaction.
		UpdatePreAuthorization			= 16,	//!< Update pre-authorization (reservation) of funds.
		OriginalCredit					= 17,	//!< OriginalCredit.
	};
};


//! Enum class for the transaction mode.
struct TransactionMode
{
	enum EnumType
	{
		Explicit 						= 0,	//!< Explicit transaction mode.
		Implicit 						= 1,	//!< Implicit transaction mode.
	};
};


//! Enumeration for intermediate result modes.
struct  IntermediateResultMode
{
	enum EnumType
	{
		None							= 0,	//!< Do not use intermediate result.
		IntermediateResult				= 1,	//!< Use intermediate result needing a response.
		IntermediateResultNoResponse	= 2,	//!! Use intermediate result that does not need a response.
	};
};


//! Enumeration for transaction result.
struct TransactionResult
{
	enum EnumType
	{
		Approved			= 0,	//!< The transaction succeeded.
		Error				= 1,	//!< The transaction failed (Returned in TransactionResponse). See ResultCode for reason.
		Declined			= 2,	//!< The transaction was declined (Returned in LastTransactionResponse).
		Stopped				= 3,	//!< The transaction was stopped (Returned in LastTransactionResponse).
		TechnicalProblem	= 4,	//!< The transaction had a technical problem (Returned in LastTransactionResponse).
		TransparentMode		= 5,	//!< A non-EMV card was presented and transparent mode was started.
	};
};


//! Enumeration for specifying where the printer output must go.
/*!
 * The values are chosen to form a bit-field (bit 1 = terminal, bit 2 = printer).
 */
struct PrintOrigin
{
	enum EnumType
	{
		Terminal				= 1,	//!< Print on the terminal.
		CashRegister			= 2,	//!< Print on the cash register.
		TerminalAndCashRegister	= 3,	//!< Print on the terminal and cash register.
	};
};


//! Enumeration for the ticket type.
struct TicketType
{
	enum EnumType
	{
		Merchant	= 1,	//!< Merchant ticket (e.g. with space for card holder signature). Often not generated.
		CardHolder	= 2,	//!< Card holder ticket. Always generated for a transaction.
		Journal		= 3,	//!< Journal ticket. Normally generated except when electronic journal is on and printing of journal is off.
		Totals		= 4,	//!< Totals ticket. Only generated when requesting totals.
	};
};


//! Enumeration for the transaction stage.
struct TransactionStageTag
{
	enum EnumType
	{
		None									= 0,	//!< The terminal is not in a transaction.
		WaitingForCard							= 1,	//!< The terminal is waiting for a card.
		WaitingForPin							= 2,	//!< The terminal is waiting for a PIN code.
		WaitingForTransaction					= 3,	//!< The terminal is performing a transaction.
		Finished								= 4,	//!< The terminal is finished with a transaction.
		WaitingForTipInput						= 5,	//!< The terminal is waiting for a card holder TIP input.
		WaitingForConfirmationService			= 6,	//!< The terminal is waiting for a card holder service confirmation.
		WaitingForConfirmationAmount			= 7,	//!< The terminal is waiting for a card holder amount confirmation.
		WaitingForConfirmationServiceAndAmount	= 8,	//!< The terminal is waiting for a card holder service and amount confirmation.
		WaitingForCardRemoval					= 9,	//!< The terminal is waiting till the card is removed.
		WaitingForLastTransactionResult			= 10,	//!< The terminal is displaying the last transaction information on the terminal.
		WaitingForApplicationSelection			= 11,	//!< The terminal is waiting for the application selection (e.g. selection between chipknip, Maestro).
		CardDetected							= 12,	//!< Send when the terminal detected a card (cless) or when a card was inserted/swiped.
		WaitingForIntermediateResult			= 13,	//!< The terminal is waiting for the intermediate result from the cash register.
		CardRemoved								= 14,	//!< The card was removed.
	};
};


//! Enumeration for cancellation reasons.
struct CancelReason
{
	enum EnumType
	{
		Manual		= 0,			//!< The cash register operator cancelled the operation.
		System		= 1,			//!< The cash register itself cancelled the operation.
	};
};


//! Enumeration for the print result from the ECR to the terminal.
struct PrintResult
{
	enum EnumType
	{
		ResultOK	= 0,			//!< Printing on the ECR succeeded.
		Failed		= 1,			//!< Printing on the ECR failed.
	};
};


//! The application IDs used for requesting version information.
struct ApplicationId
{
	enum EnumType
	{
		Sdk			= 0,			//!< The terminal SDK.
		Rdm			= 1,			//!< The terminal RDM application.
		Ctap		= 2,			//!< The terminal C-TAP application.
		Ecr			= 3,			//!< The terminal ECR application.
		Tsc			= 4,			//!< The TSC application.
		Mdb			= 5,			//!< The MDB application.
		Custom		= 6,			//!< The custom payment application.
	};
};


//! Enumeration for transparent mode beep types.
struct TmBeepType
{
	enum EnumType
	{
		Success		= 0,			//!< Three short success beeps.
		Failure		= 1,			//!< One long failure beep.
		Attention	= 2,			//!< One short attention beep.
	};
};


//! Enumeration for LED control (bit field).
struct TmLedControl
{
	enum EnumType
	{
		Led1		= 0x01,			//!< LED 1 (left most LED).
		Led2		= 0x02,			//!< LED 2.
		Led3		= 0x04,			//!< LED 3.
		Led4		= 0x08,			//!< LED 4 (right most LED).
	};
};


//! Enumeration for units.
struct Unit
{
	enum EnumType
	{
		None		= 0,	// No units.
		Bytes		= 1,	// Bytes.
		Seconds		= 2,	// Seconds.
		Bps			= 3,	// Bits/second.
	};
};


//! Enumeration for unit prefixes.
struct UnitPrefix
{
	enum EnumType
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
	};
};
