//===============================================================================
//= Copyright (c) Ortus BVBA.  All rights reserved.
//= THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY
//= OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT
//= LIMITED TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
//= FITNESS FOR A PARTICULAR PURPOSE.
//===============================================================================
//EIDNative library functions

#if     _MSC_VER > 1000
#pragma once
#endif

// uit "eidstructures.hpp"

#if !defined( _EIDNATIVE_H_ )
#define _EIDNATIVE_H_

// uit "eidconstants.hpp"

// Maximum length of the card number field
#define EID_MAX_CARD_NUMBER_LEN                         0xc
// Maximum length of the chip number field
#define EID_MAX_CHIP_NUMBER_LEN                         0x20
// Maximum length of the begin date field
#define EID_MAX_DATE_BEGIN_LEN                          0xa
// Maximum length of the end date field
#define EID_MAX_DATE_END_LEN                            0xa
// Maximum length of the name of the devivery municipality
#define EID_MAX_DELIVERY_MUNICIPALITY_LEN               0x50
// Maximum length of the national number
#define EID_MAX_NATIONAL_NUMBER_LEN                     0xb
// Maximum length of the surname
#define EID_MAX_NAME_LEN                                0x6e
// Maximum length of the first name
#define EID_MAX_FIRST_NAME1_LEN                         0x5f
// Maximum length of the first name
#define EID_MAX_FIRST_NAME2_LEN                         0x3
// Maximum length of the nationality
#define EID_MAX_NATIONALITY_LEN                         0x55
// Maximum length of the birthplace
#define EID_MAX_BIRTHPLACE_LEN                          0x50
// Maximum length of the birthdate
#define EID_MAX_BIRTHDATE_LEN                           0xc
// Maximum length of the sex field
#define EID_MAX_SEX_LEN                                 0x1
// Maximum length of the noble condition field
#define EID_MAX_NOBLE_CONDITION_LEN                     0x32
// Maximum length of the document type field
#define EID_MAX_DOCUMENT_TYPE_LEN                       0x2
// Maximum length of the special status field
#define EID_MAX_SPECIAL_STATUS_LEN                      0x2
// Maximum length of the street name field
#define EID_MAX_STREET_LEN                              0x50
// Maximum length of the ZIP code field
#define EID_MAX_ZIP_LEN                                 0x4
// Maximum length of the municipality name field
#define EID_MAX_MUNICIPALITY_LEN                        0x43
// Maximum length of the picture data
#define EID_MAX_PICTURE_LEN                             0x1000
// Maximum length of the certificate data
#define EID_MAX_CERT_LEN                                0x800

// uit "siscard.hpp"

#ifdef __cplusplus
extern "C" {
#endif

// Maximum length of the surname field
#define SIS_MAX_NAME_LEN							0x30
// Maximum length of the first name field
#define SIS_MAX_FIRSTNAMES_LEN						0x18
// Maximum length of the initial field
#define SIS_MAX_INITIAL_LEN							0x1
// Maximum length of the sex field
#define SIS_MAX_SEX_LEN								0x1
// Maximum length of the card name field
#define SIS_MAX_CARDNAME_LEN						0x6
// Maximum length of the birth date field
#define SIS_FIELD_MAX_BIRTHDATE_LEN					0x8
// Maximum length of the capture date field
#define SIS_FIELD_MAX_CAPTUREDATE_LEN				0x8
// Maximum length of the start validity date field
#define SIS_FIELD_MAX_VALIDBEGIN_LEN				0x8
// Maximum length of the end validity date field
#define SIS_FIELD_MAX_VALIDEND_LEN					0x8
// Maximum length of the social security number field
#define SIS_FIELD_MAX_SOCIAL_SECURITY_NUMBER_LEN	0xb
// Maximum length of the car number field
#define SIS_FIELD_MAX_CARDNUMBER_LEN				0xa

//Public information stored on Belgian SIS card.
//The SIS card is the social security card of each Belgian resident
//(Belgian or foreigner)
struct SIS_RECORD
{
public:
    //Family name of the card owner
	char Name[SIS_MAX_NAME_LEN + 1];
    //First name of the card owner
	char FirstName[SIS_MAX_FIRSTNAMES_LEN + 1];
    //Initial of the card owner
	char Initial[SIS_MAX_INITIAL_LEN+ 1];
    //Sex of the card owner
	char Sex[SIS_MAX_SEX_LEN + 1];
    //Birth date of the card owner
	char BirthDate[SIS_FIELD_MAX_BIRTHDATE_LEN + 1];
    //Social security number of the card owner
	char SocialSecurityNumber[SIS_FIELD_MAX_SOCIAL_SECURITY_NUMBER_LEN + 1];
    //Date of issue
	char CaptureDate[SIS_FIELD_MAX_CAPTUREDATE_LEN + 1];
    //Card validity begin date
	char ValidityDateBegin[SIS_FIELD_MAX_VALIDBEGIN_LEN + 1];
    //Card validity end date
	char ValidityDateEnd[SIS_FIELD_MAX_VALIDEND_LEN + 1];
    //Card number
	char CardNumber[SIS_FIELD_MAX_CARDNUMBER_LEN + 1];
    //Name of the card
	char CardName[SIS_MAX_CARDNAME_LEN +1 ];
} ;

//Public information stored on Belgian SIS card.
//The SIS card is the social security card of each Belgian resident
//(Belgian or foreigner)
typedef SIS_RECORD  TSISRecordA;
//Public information stored on Belgian SIS card.
//The SIS card is the social security card of each Belgian resident
//(Belgian or foreigner)
typedef SIS_RECORD  TSISRecord;
//Public information stored on Belgian SIS card.
//The SIS card is the social security card of each Belgian resident
//(Belgian or foreigner)
typedef SIS_RECORD *PSISRecord;

#ifdef __cplusplus
}
#endif

// Identity information stored on EID card
struct EID_IDENTITY
{
public:
    // Electronic ID card number
	char cardNumber[EID_MAX_CARD_NUMBER_LEN+1];
    // Electronic ID card physical chip number
	char chipNumber[EID_MAX_CHIP_NUMBER_LEN+1];
    // Card validity start date 
	char validityDateBegin[EID_MAX_DATE_BEGIN_LEN+1];
    // Card validity end date
	char validityDateEnd[EID_MAX_DATE_END_LEN +1];
    // Card delivery municipality
	char municipality[EID_MAX_DELIVERY_MUNICIPALITY_LEN+1];
    // National number
	char nationalNumber[EID_MAX_NATIONAL_NUMBER_LEN+1];
    // Surname
	char name[EID_MAX_NAME_LEN+1];
    // First name (2 first given names)
	char firstName1[EID_MAX_FIRST_NAME1_LEN+1];
    // First name part 2 (first letter of the 3rd given name).
	char firstName2[EID_MAX_FIRST_NAME2_LEN+1];
    // Nationality
	char nationality[EID_MAX_NATIONALITY_LEN+1];
    // Birth location
	char birthLocation[EID_MAX_BIRTHPLACE_LEN+1];
    // Birth date
	char birthDate[EID_MAX_BIRTHDATE_LEN+1];
    // Sex
	char sex[EID_MAX_SEX_LEN+1];
    // Noble condition
	char nobleCondition[EID_MAX_NOBLE_CONDITION_LEN+1];
    // Document type code (Belgian citizen card, Kids Card, Foreigner card)
	int documentType;
    // White cane (blind people)
	BOOL whiteCane;
    // Yellow cane (partially sighted people)
	BOOL yellowCane;
    // Extended minority
	BOOL extendedMinority;
} ;

// Identity information stored on EID card
typedef EID_IDENTITY  TEIDIdentity;
// Identity information stored on EID card
typedef EID_IDENTITY *PEIDIdentity;

// EID address information, stored on the card
struct EID_Address
{
public:
    // Street name
	char street[EID_MAX_STREET_LEN+1];
    // ZIP code
	char zip[EID_MAX_ZIP_LEN+1];
    // Municipality
	char municipality[EID_MAX_MUNICIPALITY_LEN+1];
} ;

// EID address information, stored on the card
typedef EID_Address  TEIDAddress;
// EID address information, stored on the card
typedef EID_Address *PEIDAddress;

// Raw picture data from EID card
struct EID_Picture
{
public:
    // Picture raw data buffer
	char picture[EID_MAX_PICTURE_LEN+1];
    // Picture raw data buffer length
	int pictureLength;
} ;

// Raw picture data from EID card
typedef EID_Picture  TEIDPicture;
// Raw picture data from EID card
typedef EID_Picture *PEIDPicture;

// Certificate, stored on EID card
struct EID_Certificate
{
public:
    // Certificate raw data buffer
	char certificate[EID_MAX_CERT_LEN+1];
    // Certificate data length
	int certificateLength;
} ;

// Certificate, stored on EID card
typedef EID_Certificate  TEIDCertificate;
// Certificate, stored on EID card
typedef EID_Certificate *PEIDCertificate;


//Callback procedure for card events
typedef void ( __stdcall * TManagerProc)(void);
//Callback procedure for card error event
typedef void ( __stdcall * TManagerErrorProc)(unsigned ErrorCode);

//Data manager is used to pass the callback procedures pointers to EIDNative
struct TManagerData
{
public:
    // Card is inserted callback procedure
	TManagerProc CardInserted;
    // Card was activated callback procedure
	TManagerProc CardActive;
    // Card was removed from the reader  callback procedure
	TManagerProc CardRemoved;
    // Invalid card was inserted into the reader callback procedure
	TManagerProc CardInvalid;
    // There is no card in the reader and reader is waiting for the next operation
	TManagerProc ReaderWaiting;
    // Card operation error  callback procedure
	TManagerErrorProc Error;
} ;

//Data manager is used to pass the callback procedures pointers to EIDNative
typedef TManagerData *PManagerData;
//Data manager is used to pass the callback procedures pointers to EIDNative
typedef TManagerData MANAGER_DATA;

#ifdef EID_EXPORTS
#define EID_API __declspec(dllexport)
#else
#define EID_API __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C" {
#endif

// Summary:
//      Check if Belgian EID card is inserted into card reader
// Description:
//      If the card is inserted in the reader, this function performs the card
//      type check.
// Return Value:
//      Returns TRUE, if Belgian eID card is inserted in the reader. If there is
//      no card in the reader or the card of other type is inserted, returns FALSE
EID_API BOOL __stdcall IsEIDCard(void);

// Summary:
//      Check if Belgian SIS card is inserted into card reader
// Description:
//      If the card is inserted in the reader, this function performs the card
//      type check.
// Return Value:
//      Returns TRUE, if Belgian SIS card is inserted in the reader. If there is
//      no card in the reader or the card of other type is inserted, returns FALSE
EID_API BOOL __stdcall IsSISCard(void);

// Summary:
//      Work done. Finalize all references. This procedure must be called when you
//      finished your work with card reader.
// Description:
//      Call DoneReader if you use InitReader procedure. If you use InitReaderEx then
//      call DoneReaderEx
// Return Value:
//      None (procedure)
EID_API void __stdcall DoneReader(void);

// Summary:
//      Work done. Finalize all references. This procedure must be called when you
//      finished your work with card reader.
// Description:
//      Call DoneReader if you use InitReader procedure. If you use InitReaderEx then
//      call DoneReaderEx
// Return Value:
//      None (procedure)
EID_API void __stdcall DoneReaderEx(void);

// Summary:
//      Initialize smart card reader and setup callback functions (optional)
// Description:
//      This procedure must be called first before any other functions from
//      EIDNative library can be used. The procedure checks if the official
//      EID Middleware is installed and set access to the card through it,
//      acting like a proxy. If no Middleware is installed, the direct access
//      to the card will be used
// Arguments:
//      pData - The set of callback procedres used by EIDNative
//      If you do not plan to use callbacks then you can simply
//      pass nil as a value for pData
// Return Value:
//      None (procedure)
EID_API void __stdcall InitReader(PManagerData pData);

// Summary:
//      The same as InitReader, but without BEID middleware support. InitReaderEx
//      initializes the card reader and setup the callback functions (optional) 
// Description:
//      This procedure must be called first before any other functions from
//      EIDNative library can be used. The official EID Middleware will be
//      ignored and direct access to the card will be used.
// Arguments:
//      pData - The set of callback procedres used by EIDNative
//      If you do not plan to use callbacks then you can simply
//      pass nil as a value for pData
// Return Value:
//      None (procedure)
EID_API void __stdcall InitReaderEx(PManagerData pData);

// Summary:
//		Initializes selected reader and assigned the callback functions (optional).
// Arguments:
//      pData - The set of callback procedres used by EIDNative
//      If you do not plan to use callbacks then you can simply
//      pass nil as a value for pData
//		ReaderNumber - reader index, starting from 0
// Description:
//      This procedure must be called first before any other functions from
//      EIDNative library can be used. The procedure checks if the official
//      EID Middleware is installed and set access to the card through it,
//      acting like a proxy. If no Middleware is installed, the direct access
//      to the card will be used. If you have only one reader or want to use the 
//		first available reader you can call InitReader function instead.
// Return Value:
//      None (procedure)
EID_API void __stdcall InitSelectedReader(PManagerData pData, int ReaderNumber);

// Summary:
//		Initializes selected reader and assigned the callback functions (optional).
//		This procedure ignores Middleware and configure direct access to the card.
// Description:
//      This procedure must be called first before any other functions from
//      EIDNative library can be used. The official EID Middleware will be
//      ignored and direct access to the card will be used.
// Arguments:
//      pData : The set of callback procedres used by EIDNative
//      If you do not plan to use callbacks then you can simply
//      pass nil as a value for pData
//		ReaderNumber - reader number, starting from 0
// Return Value:
//      None (procedure)
EID_API void __stdcall InitSelectedReaderEx(PManagerData pData, int ReaderNumber);

// Summary:
//      When more than 1 reader connected, select the reader with specified number
//      The first reader has number 0
// Arguments:
//      Number - The reader index, starting from 0
// Return Value:
//      None (procedure)
EID_API void __stdcall SelectReader(int ReaderNumber);

// Summary:
//      Returns the index of the active smart card reader
// Return Value:
//      The number of the selected card reader. The first reader has number 0.
EID_API int  __stdcall GetSelectedReaderIndex(void);

// Summary:
//      Select active smart card reader by providing the reader name
// Arguments:
//      Reader Name - the name of the card reader
// Return Value:
//      None (procedure)
EID_API void __stdcall SelectReaderByName(char * ReaderName);

// Summary:
//      Read identity information from Belgian eID card
// Arguments:
//      pData - pointer to TEIDIdentity record
// Return value:
//      TRUE when information is successfully received from the card;
//      otherwise returns FALSE
EID_API BOOL __stdcall ReadIDData(PEIDIdentity pData);

// Summary:
//      Read Belgian SIS card.
//      The SIS card is the social security card of each Belgian resident
//      (Belgian or foreigner)
// Arguments:
//      pData - pointer to TSISRecord record
// Return value:
//      TRUE when information is successfully received from the card;
//      otherwise returns FALSE
EID_API BOOL __stdcall ReadSISCard(PSISRecord pData);

// Summary:
//      Read address information from Belgian eID card
// Arguments:
//      pData - pointer to TEIDAddress record
// Return value:
//      TRUE when information is successfully received from the card;
//      otherwise returns FALSE
EID_API BOOL __stdcall ReadAddress(PEIDAddress pData);

// Summary:
//      Read picture from Belgian eID card to the buffer
// Arguments:
//      pData - pointer to TEIDPicture record
// Return value:
//      TRUE when picture is successfully received from the card;
//      otherwise returns FALSE
EID_API BOOL __stdcall ReadPictureEx(PEIDPicture pData);

// Summary:
//      Save photo to the file. Introduced as Visual Basic 6 helper procedure
// Arguments:
//      AFileName - File name to store the photo. The photo is stored as
//      JPEG image
// Return Value:
//      None (procedure)
EID_API void __stdcall SavePhotoToFile(char * FileName);

// Summary:
//      Save the picture from the card as Bitmap
// Arguments:
//      AFileName - File name to store the photo
// Return Value:
//      None (procedure)
EID_API void __stdcall SavePhotoAsBitmap(char * FileName);

// Summary:
//      Save the picture from the card as JPG
// Arguments:
//      AFileName - File name to store the photo
// Return Value:
//      None (procedure)
EID_API void __stdcall SavePhotoAsJpeg(char * FileName);

// Summary:
//      Read picture from Belgian eID card to the buffer
// Arguments:
//      buf - pointer to allocated memory buffer
//      len - size of the buffer
// Return value:
//      TRUE when picture is successfully received from the card;
//      otherwise returns FALSE
EID_API int  __stdcall ReadPicture(void * buf, int len);

// Summary:
//      Verify PIN code
// Arguments:
//      PinValue - PIN code to verify
// Return value:
//      TRUE when the correct PIN code is provided;
//      otherwise returns FALSE
EID_API BOOL __stdcall VerifyPin(char * PinValue);

// Summary:
//      Reads the authentication certificate from Belgian eID card.
// Arguments:
// 	certificate - X.509v3 authentication certificate.
// Return Value:
// 	TRUE if certificate received from the card; otherwise, FALSE.
EID_API BOOL __stdcall ReadAuthenticationCertificate(PEIDCertificate pData);

// Summary:
//      Reads the CA certificate from Belgian eID card.
// Arguments:
// 	certificate - The certificate.
// Return Value:
// 	TRUE if certificate received from the card; otherwise, FALSE.
EID_API BOOL __stdcall ReadCaCertificate(PEIDCertificate pData);

// Summary:
//      Reads the non repudiation certificate from Belgian eID card.
// Arguments:
// 	certificate - X.509v3 qualified certificate. Can be used to produce
//                    digital signatures equivalent to handwritten signatures,
//                    cfr. European Directive 1999/93/EC
// Return Value:
// 	TRUE if certificate received from the card; otherwise, FALSE.
EID_API BOOL __stdcall ReadNonRepudiationCertificate(PEIDCertificate pData);

// Summary:
//      Reads the Root CA certificate from Belgian eID card
// Arguments:
// 	certificate - The certificate.
// Return Value:
// 	TRUE if certificate received from the card; otherwise, FALSE.
EID_API BOOL __stdcall ReadRootCaCertificate(PEIDCertificate pData);

// Summary:
// 	Reads the RRN certificate from Belgian eID card.
// Arguments:
// 	certificate - The certificate.
// Return Value:
// 	TRUE if certificate received from the card; otherwise, FALSE.
EID_API BOOL __stdcall ReadRrnCertificate(PEIDCertificate pData);

// Summary:
//      Save Authentication Certificate to a file
// Description:
//      Save Authentication Certificate to a file
// Arguments:
//      AFileName - File name to store the certificate
// Return Value:
// 	TRUE if certificate received from the card; otherwise, FALSE.
EID_API BOOL __stdcall SaveAuthenticationCertificate(char * AFileName);

// Summary:
// Save Ca Certificate to a file
// Description:
// Save Ca Certificate to a file
// Arguments:
//      AFileName - File name to store the certificate
// Return Value:
// 	TRUE if certificate received from the card; otherwise, FALSE.
EID_API BOOL __stdcall SaveCaCertificate(char * AFileName);

// Summary:
// Save Non Repudiation Certificate to a file
// Description:
// Save Non Repudiation Certificate to a file
// Arguments:
//      AFileName - File name to store the certificate
// Return Value:
// 	TRUE if certificate received from the card; otherwise, FALSE.
EID_API BOOL __stdcall SaveNonRepudiationCertificate(char * AFileName);

// Summary:
// Save Root Ca Certificate to a file
// Description:
// Save Root Ca Certificate to a file
// Arguments:
//      AFileName - File name to store the certificate
// Return Value:
// 	TRUE if certificate received from the card; otherwise, FALSE.
EID_API BOOL __stdcall SaveRootCaCertificate(char * AFileName);

// Summary:
// Save RRN Certificate to a file
// Description:
// Save RRN Certificate to a file
// Arguments:
//      AFileName - File name to store the certificate
// Return Value:
// 	TRUE if certificate received from the card; otherwise, FALSE.
EID_API BOOL __stdcall SaveRrnCertificate(char * AFileName);

// Summary:
//      Get number of card readers connected to PC
// Return Value:
//      The number of installed smart card readers
EID_API int  __stdcall GetReadersCount(void);

// Summary:
//      Check if the card is inserted to the reader
// Return Value:
//      TRUE if card is inserted in the reader and powered; otherwise FALSE
EID_API BOOL __stdcall ReaderConnectedToCard(void);

// Summary:
//      Establish the connection between the card and the reader
// Description:
//      When the card is already inserted in the reader you can use this
//      function to establish the connection between the reader and the card
//      When no card is inserted this procedure does nothing, so it's safe to call
//      it at any place in your code
// Return Value:
//      None (procedure)
EID_API void __stdcall ConnectReaderToCard(void);

// Summary:
//      Wait unil the card is inserted into reader or time-out occurs
//      The wait time is specified in seconds
// Return Value:
//      TRUE if card was inserted in the reader; otherwise false
EID_API bool __stdcall WaitForCard(int WaitTime);

// Summary:
//      Read eID card and save the identity information to CSV file
// Arguments:
//      FileName - File name to store information
// Return Value:
//      None (procedure)
EID_API void __stdcall SaveIDToCSV(char * FileName);

// Summary:
//      Read eID card and save the address of the person to CSV file
// Arguments:
//      FileName - File name to store information
// Return Value:
//      None (procedure)
EID_API void __stdcall SaveAddressToCSV(char * FileName);

// Summary:
//      Read eID card and save the identity information and address to CSV file
// Arguments:
//      FileName - File name to store information
// Return Value:
//      None (procedure)
EID_API void __stdcall SavePersonToCSV(char * FileName);

// Summary:
//      Read SIS card and save SIS record data to CSV file.
//      The SIS card is the social security card of each Belgian resident
//      (Belgian or foreigner)
// Arguments:
//      FileName - File name to store information
// Return Value:
//      None (procedure)
EID_API void __stdcall SaveSISDataToCSV(char * FileName);

// Summary:
//		Returns the name of the reader
// Arguments:
//		Index - index of the reader
//		Buf - allocated buffer
//		bufLen - size of the buffer
EID_API void __stdcall GetReaderName(int Index, char * Buf, int bufLen);

// Summary:
//		Returns the names of all installed card readers
// Arguments:
//		Buf - buffer
//		bufLen - size of the buffer
EID_API void __stdcall GetReadersList(char * Buf, int bufLen);

#ifdef __cplusplus
}
#endif

#endif