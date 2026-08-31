// FONT: COLOSSAL 
/*** 
 *    8888888 888b    888  .d8888b.  888     888     888 8888888b.  8888888888 .d8888b.  
 *      888   8888b   888 d88P  Y88b 888     888     888 888  "Y88b 888       d88P  Y88b 
 *      888   88888b  888 888    888 888     888     888 888    888 888       Y88b.      
 *      888   888Y88b 888 888        888     888     888 888    888 8888888    "Y888b.   
 *      888   888 Y88b888 888        888     888     888 888    888 888           "Y88b. 
 *      888   888  Y88888 888    888 888     888     888 888    888 888             "888 
 *      888   888   Y8888 Y88b  d88P 888     Y88b. .d88P 888  .d88P 888       Y88b  d88P 
 *    8888888 888    Y888  "Y8888P"  88888888 "Y88888P"  8888888P"  8888888888 "Y8888P"  
 *                                                                                       
 *                                                                                       
 *                                                                                       
 */
#ifndef BACnetPRODUCTIONS
#define BACnetPRODUCTIONS


#include "bacnet2012_enums.h"
#include "BACnetBitStrings.h"
/***
 *    .______        ___           _______. _______    .___________.____    ____ .______    _______      _______.
 *    |   _  \      /   \         /       ||   ____|   |           |\   \  /   / |   _  \  |   ____|    /       |
 *    |  |_)  |    /  ^  \       |   (----`|  |__      `---|  |----` \   \/   /  |  |_)  | |  |__      |   (----`
 *    |   _  <    /  /_\  \       \   \    |   __|         |  |       \_    _/   |   ___/  |   __|      \   \    
 *    |  |_)  |  /  _____  \  .----)   |   |  |____        |  |         |  |     |  |      |  |____ .----)   |   
 *    |______/  /__/     \__\ |_______/    |_______|       |__|         |__|     | _|      |_______||_______/    
 *                                                                                                               
 */

/*
NOTE- there is much material retained for backwards compatability
//
Tag Number: 
0 = Null
1 = Boolean 
2 = Unsigned Integer 
3 = Signed Integer (2's complement notation) 
4 = Real (ANSI/IEEE-754 floating point) 
5 = Double (ANSI/IEEE-754 double precision floating point) 
6 = Octet String 
7 = Character String 
8 = Bit String 
9 = Enumerated 
10 = Date 
11 = Time 
12 = BACnetObjectIdentifier
*/
/****This section should contain primitive types defined in 2010 Chapter 20.2.2 - 20.2.14/
 *    888888b.         d8888  .d8888b.  8888888888      88888888888 Y88b   d88P 8888888b.  8888888888 .d8888b.              d8888 888    d8P         d8888 
 *    888  "88b       d88888 d88P  Y88b 888                 888      Y88b d88P  888   Y88b 888       d88P  Y88b            d88888 888   d8P         d88888 
 *    888  .88P      d88P888 Y88b.      888                 888       Y88o88P   888    888 888       Y88b.                d88P888 888  d8P         d88P888 
 *    8888888K.     d88P 888  "Y888b.   8888888             888        Y888P    888   d88P 8888888    "Y888b.            d88P 888 888d88K         d88P 888 
 *    888  "Y88b   d88P  888     "Y88b. 888                 888         888     8888888P"  888           "Y88b.         d88P  888 8888888b       d88P  888 
 *    888    888  d88P   888       "888 888                 888         888     888        888             "888        d88P   888 888  Y88b     d88P   888 
 *    888   d88P d8888888888 Y88b  d88P 888                 888         888     888        888       Y88b  d88P       d8888888888 888   Y88b   d8888888888 
 *    8888888P" d88P     888  "Y8888P"  8888888888          888         888     888        8888888888 "Y8888P"       d88P     888 888    Y88b d88P     888 
 *                                                                                                                                                         
 *                                                                                                                                                         
 *                                                                                                                                                         
 */
// NOTE- Level X productions contain Level (X-1) productions, where X > 0
/***
 *    888      8888888888 888     888 8888888888 888            .d8888b.            .d8888b.   .d8888b.       8888888b.  8888888b.   .d88888b.  8888888b.  888     888  .d8888b. 88888888888 8888888 .d88888b.  888b    888  .d8888b.  
 *    888      888        888     888 888        888           d88P  Y88b          d88P  Y88b d88P  Y88b      888   Y88b 888   Y88b d88P" "Y88b 888  "Y88b 888     888 d88P  Y88b    888       888  d88P" "Y88b 8888b   888 d88P  Y88b 
 *    888      888        888     888 888        888           888    888          888    888 888    888      888    888 888    888 888     888 888    888 888     888 888    888    888       888  888     888 88888b  888 Y88b.      
 *    888      8888888    Y88b   d88P 8888888    888           888    888 888  888 888    888 888    888      888   d88P 888   d88P 888     888 888    888 888     888 888           888       888  888     888 888Y88b 888  "Y888b.   
 *    888      888         Y88b d88P  888        888           888    888 `Y8bd8P' 888    888 888    888      8888888P"  8888888P"  888     888 888    888 888     888 888           888       888  888     888 888 Y88b888     "Y88b. 
 *    888      888          Y88o88P   888        888           888    888   X88K   888    888 888    888      888        888 T88b   888     888 888    888 888     888 888    888    888       888  888     888 888  Y88888       "888 
 *    888      888           Y888P    888        888           Y88b  d88P .d8""8b. Y88b  d88P Y88b  d88P      888        888  T88b  Y88b. .d88P 888  .d88P Y88b. .d88P Y88b  d88P    888       888  Y88b. .d88P 888   Y8888 Y88b  d88P 
 *    88888888 8888888888     Y8P     8888888888 88888888       "Y8888P"  888  888  "Y8888P"   "Y8888P"       888        888   T88b  "Y88888P"  8888888P"   "Y88888P"   "Y8888P"     888     8888888 "Y88888P"  888    Y888  "Y8888P"  
 *                                                                                                                                                                                                                                     
 *                                                                                                                                                                                                                                     
 *                                                                                                                                                                                                                                     
 */

// 0 Null - nullptr is too overloaded to define.  Use a char set to 0x00 for all nullptr's

// 1 Boolean - use an unsigned char

// 2 Unsigned Integer
#define uint unsigned short
#define Unsigned8 unsigned char
#define Unsigned16 unsigned short int
#define Unsigned32 unsigned long int
// 3 Signed Integer - use int
// 4 Real - use float
// 5 Double - use double
// 6 Octet string
#define octet unsigned char

typedef struct tagOctet_String {
	octet	*value;
	int		length;
} Octet_String;

// 7 Character string
typedef struct tagChar_String {
	char	*value;
	int		length;
} Character_String;

// 8 Bit String
typedef struct tagBit_String {
	octet	*value;
	int		length;
} Bit_String;

// 9 Enumerated
#define Enumerated int

// 10 Date
typedef struct tagBACnetDate {  //each field is one octet to match encoding, 0xFF means unknown or don't care
	octet	year;								//year - 1900
	octet	month;            					//January = 1, 13=odd months, 14=even months (Add. H)
	octet	day_of_month;						// 32=last dom, 33=odd days, 34= even days (Add. H)
	octet	day_of_week;						//Sunday = 1
	} BACnetDate;

// 11 Time
typedef struct tagBACnetTime {
//each field is one octet to match encoding, 0xFF means unknown or don't care
	octet	hour;								//24 hr clock
	octet	minute;
	octet	second;
	octet	hundredths;
   } BACnetTime;

// 12 BACnetObjectIdentifier

#define byte unsigned char
#define dword unsigned long
#define word unsigned short

typedef struct tagBNObjId {
	word object:10;
	dword id:22;
} BNObjId;

typedef struct tagBACnetObjectIdentifier {
	struct tagObjectIdentifier	*next;
	dword					object_id;
} BACnetObjectIdentifier;

// MAG 06JUN14 moved from unsuitable location
typedef struct tagpropdescriptor2012{
	char	*PropertyName;
	dword	PropID;
	//word	StrucOffset;
	unsigned char	ParseType;
	unsigned char	PropGroup;
	word	PropET;
	int		PropFlags;  // MAG 22DEC11 changed from word
} propdescriptor2012;



/***
 *    888      8888888888 888     888 8888888888 888            .d8888b.            .d8888b.   d888        8888888b.  8888888b.   .d88888b.  8888888b.  888     888  .d8888b. 88888888888 8888888 .d88888b.  888b    888  .d8888b.  
 *    888      888        888     888 888        888           d88P  Y88b          d88P  Y88b d8888        888   Y88b 888   Y88b d88P" "Y88b 888  "Y88b 888     888 d88P  Y88b    888       888  d88P" "Y88b 8888b   888 d88P  Y88b 
 *    888      888        888     888 888        888           888    888          888    888   888        888    888 888    888 888     888 888    888 888     888 888    888    888       888  888     888 88888b  888 Y88b.      
 *    888      8888888    Y88b   d88P 8888888    888           888    888 888  888 888    888   888        888   d88P 888   d88P 888     888 888    888 888     888 888           888       888  888     888 888Y88b 888  "Y888b.   
 *    888      888         Y88b d88P  888        888           888    888 `Y8bd8P' 888    888   888        8888888P"  8888888P"  888     888 888    888 888     888 888           888       888  888     888 888 Y88b888     "Y88b. 
 *    888      888          Y88o88P   888        888           888    888   X88K   888    888   888        888        888 T88b   888     888 888    888 888     888 888    888    888       888  888     888 888  Y88888       "888 
 *    888      888           Y888P    888        888           Y88b  d88P .d8""8b. Y88b  d88P   888        888        888  T88b  Y88b. .d88P 888  .d88P Y88b. .d88P Y88b  d88P    888       888  Y88b. .d88P 888   Y8888 Y88b  d88P 
 *    88888888 8888888888     Y8P     8888888888 88888888       "Y8888P"  888  888  "Y8888P"  8888888      888        888   T88b  "Y88888P"  8888888P"   "Y88888P"   "Y8888P"     888     8888888 "Y88888P"  888    Y888  "Y8888P"  
 *                                                                                                                                                                                                                                  
 *                                                                                                                                                                                                                                  
 *                                                                                                                                                                                                                                  
 */
// These only use primitive data types.  If it has a Lvl 1 production in it, it's a Lvl 2 production.
//typedef struct tagBACnetPropertyValue;  // predeclaration

typedef struct tagTimeValue {
	struct tagTimeValue		*next;
	BACnetTime				time;
	enum ActionValueType	value_type;
	union {
		BACnetBinaryPV	bproperty_value; 	//binary value  MAG 03JAN12 removed enum keyword
		word			uproperty_value;	//unsigned word
		float			fproperty_value;	//float
	} av;
} BACnetTimeValue; 

typedef struct tagBACnetDateTime {
	BACnetDate date;
	BACnetTime time;
} BACnetDateTime;

union prop_value {			// 0 nullptr  MAG 05APR05 add nullptr
	char			b;		// 1 bool
	unsigned int	ui;		// 2 unsigned int
	int				i;		// 3 signed int
	float			r;		// 4 real
	double			d;		// 5 double
	octet			oc[255];// 6 octet[100]
	char			t[255];	// 7 char[100]
	octet			bt[255];// 8 bit string octet[100]
	unsigned int	en;		// 9 enumerated (unsigned int)
	BACnetDate		date;	// 10 BACnet Date
	BACnetTime		time;	// 11 BACnet Time
	BNObjId			o;		// 12 object id
};

/* moved to BitStrings
typedef struct tagBACnetStatusFlags{
	unsigned char in_alarm:1;
	unsigned char fault:1;
	unsigned char overridden:1;
	unsigned char out_of_service:1;
} BACnetStatusFlags;
*/
typedef struct tagBACnetAccumulatorRecord {
	BACnetDateTime		timestamp;
	unsigned			presentValue;
	unsigned			accumulatedValue;
	AccumulatorStatus	accumulatorStatus; // enum 0-normal 1-starting 2-recovered 3-abnormal 4-failed
} BACnetAccumulatorRecord;

typedef struct tagBACnetDateRange {
	BACnetDate start_date;
	BACnetDate end_date;
} BACnetDateRange;

typedef struct tagBACnetWeekNDay {
//each field is one octet to match encoding, 0xFF means unknown or don't care
	octet	month;								//January = 1
	octet	week;								//week 1 = days numbered 1-7 and so on
	octet	day;								//Monday = 1
} BACnetWeekNDay;


typedef struct tagBACnetAddress {
   word		network_number;
   octet	mac_address[8];
   word		address_size;
} BACnetAddress;

typedef struct tagRecipient {
	struct tagRecipient		*next;
	octet					choice;  //0 = device, 1 = address
	union {
		dword				device;
		BACnetAddress		address;
		}					u;
} BACnetRecipient;


typedef struct tagBACnetDeviceObjectPropertyReference {
   BACnetObjectIdentifier	Objid;
   dword					wPropertyid;
   word						ulIndex;
   BACnetObjectIdentifier   DeviceObj;
} BACnetDeviceObjectPropertyReference;      // Added Sep 18 2001

typedef struct tagListBitstringValue {
	struct tagListBitstringValue	*next;
	octet							bitstring_length;
	octet							bitstring_value[4];
} BACnetListBitstringValue;

union BACnetPropertyStates {  // these are all enums
   bool   boolean_value;
   BACnetBinaryPV						binary_value;
   BACnetEventType						event_type;
   BACnetPolarity						polarity;
   BACnetProgramRequest					program_change;
   BACnetProgramState					program_state;
   BACnetProgramError					reason_for_halt;
   BACnetReliability					reliability;
   BACnetEventState						state;
   BACnetDeviceStatus					system_status;
   BACnetEngineeringUnits				units;
   unsigned int							unsigned_value;
   BACnetLifeSafetyMode					life_safety_mode;
   BACnetLifeSafetyState				life_safety_state;
   BACnetRestartReason					restart_reason;
   BACnetDoorAlarmState					door_alarm_state;
   BACnetAction							action;
   BACnetDoorSecuredStatus				door_secured_status;
   BACnetDoorStatus						door_status;
   BACnetDoorValue						door_value;
   BACnetFileAccessMethod				file_access_method;
   BACnetLockStatus						lock_status;
   BACnetLifeSafetyOperation			life_safety_operation;
   BACnetMaintenance					maintenance;
   BACnetNodeType						node_type;
   BACnetNotifyType						notify_type;
   BACnetSecurityLevel					security_level;
   BACnetShedState						shed_state;
   BACnetSilencedState					silenced_state;
   BACnetAccessEvent					access_event;
   BACnetAccessZoneOccupancyState		zone_occupancy_state;
   BACnetAccessCredentialDisableReason	access_credential_disable_reason;
   BACnetAccessCredentialDisable		access_credential_disable;
   BACnetAuthenticationStatus			authentication_status;
   BACnetBackupState					backup_state;
}; //BACnetPropertyStates;

typedef struct tagPropertyReference {
	struct tagPropertyReference		*next;
	dword							property_id;
	word							pa_index;
} BACnetPropertyReference;

typedef struct tagObjectPropertyReference {
	struct tagObjectPropertyReference	*next;
	dword								object_id;
	dword								property_id;    
	word								pa_index;
} BACnetObjectPropertyReference;

// MAG 19DEC11 add BACnetScale
union BACnetScale {
	float		floatScale;
	int			integerScale;
};

// MAG 28MAY08 add BACnetShedLevel
union BACnetShedLevel{
	unsigned int	percent;
	unsigned int	level;
	float			amount;
};

/* moved to BitStrings
typedef struct tagBACnetLogStatus { // supposed to be a bit string
	bool	log_disabled;
	bool	buffer_purged;
	bool	log_interrupted;  // MAG 23MAY08 added for 2004B
} BACnetLogStatus;
*/

union BACnetOptionalReal {
	float	read_value;
	bool	default_value;
};


/* moved to BitStrings
typedef struct tagBACnetEventTransitionBits{ // supposed to be a bit string
	bool	to_offnormal;	// 0
	bool	to_fault;		// 1
	bool	to_normal;		// 2
} BACnetEventTransitionBits;
*/
typedef struct tagPropertyAccessError {  // MAG 13SEP05 this is used in ReadPropMult
	int	errorClass;
	int	errorCode;
} PropertyAccessError;

typedef struct tagDeviceObjectPropertyReference{
	BNObjId	objectId;			// struct with .object and .id
	octet	propertyIdentifier;	// might have several different props requested from one object
	octet	propertyArrayIndex; // optional
	BNObjId	deviceidentifier;	// optional
} BACnetDeviceObjectPropertyIdentifier;  // should identifier be reference? pp410.

typedef struct tagBACnetPropertyRef {
	int		propertyIdentifier;
	int		propertyArrayIndex;  // optional, -1 if not used
	//struct tagBACnetPropertyReference	*next;
} BACnetPropertyRef;

// MAG 16DEC11 hack to work with CharacterStrings
typedef struct tagCharacterString {
	char string[128];
} CharacterString;

/* moved to BitStrings
typedef struct tagBACnetDaysOfWeek {
   bool   monday;
   bool   tuesday;
   bool   wednesday;
   bool   thursday;
   bool   friday;
   bool   saturday;
   bool   sunday;
} BACnetDaysOfWeek;
*/

typedef struct tagBACnetKeyIdentifier {
	unsigned char algorithm;
	unsigned char key_id;
} BACnetKeyIdentifier;

typedef struct tagstreamAccessARFR {  // used in AtomicReadFile-Request::accessMethod
	int				fileStartPosition;
	unsigned int	requestedOctetCount;
} StreamAccessARFR;

typedef struct tagstreamAccessARFA {  // used in AtomicReadFile-ACK::accessMethod
	int				fileStartPosition;
	unsigned char	fileData[128];
} StreamAccessARFA;

typedef struct tagstreamAccessAWFR {  // used in AtomicWriteFile-Request::accessMethod
	int				fileStartPosition;
	unsigned char	fileData[128];
} StreamAccessAWFR;

typedef struct tagrecordAccessARFR {  // used in AtomicReadFile-Request::accessMethod
	int				fileStartRecord;
	unsigned int	requestedRecordCount;
} RecordAccessARFR;

typedef struct tagrecordAccessARFA {  // used in AtomicReadFile-ACK::accessMethod
	int				fileStartRecord;
	unsigned int	returnedRecordCount;
	unsigned char	fileData[128];
} RecordAccessARFA;

typedef struct tagrecordAccessAWFR {  // used in AtomicWriteFile-Request::accessMethod
   //unsigned int   requestedRecordCount;
   //char   *fileRecordData;
	int				fileStartRecord;
	unsigned int	recordCount;
   int				fileRecordDataLength;  // MAG added to keep track of fileRecordData
} RecordAccessAWFR ;

typedef struct tagNew_value {
	unsigned char	*changed_bits;
	int				changed_bitsLength;// MAG added
	float			changed_value;
} New_value;

typedef struct tagError {
   Error_class	error_class;
   Error_code	error_code;
} Error;

typedef struct tagCreateObject_Error {
  int    errorType;
  unsigned int    firstFailedElementNumber;
} CreateObject_Error;


union BACnetClientCOV {
   float	real_increment;
   int		default_increment;
}; //BACnetClientCOV;

typedef struct tagBACnet_SimpleACK_PDU {
   unsigned int   pdu_type;
   unsigned int   reserved;
   unsigned int   invokeID;
   BACnetConfirmedServiceChoice   service_ACK_choice;
} BACnet_SimpleACK_PDU;

typedef struct tagBACnet_SegmentACK_PDU {
   unsigned int		pdu_type;
   unsigned int		reserved;
   bool				negative_ACK;
   bool				server;
   unsigned int		original_invokeID;
   unsigned int		sequence_number;
   unsigned int		actual_window_size;
} BACnet_SegmentACK_PDU;

typedef struct tagBACnet_Reject_PDU {
   unsigned int			pdu_type;
   unsigned int			reserved;
   unsigned int			original_invokeID;
   BACnetRejectReason   reject_reason;
} BACnet_Reject_PDU;

typedef struct tagBACnet_Abort_PDU {
   unsigned int			pdu_type;
   unsigned int			reserved;
   bool					server;
   unsigned int			original_invokeID;
   BACnetAbortReason	abort_reason;
} BACnet_Abort_PDU;

typedef struct tagpriorityFilter {
   Unsigned8   minPriority;
   Unsigned8   maxPriority;
} PriorityFilter;

typedef struct tagGetEventInformation_Request {
   BACnetObjectIdentifier   lastReceivedObjectIdentifier;
} GetEventInformation_Request;

typedef struct tagLifeSafetyOperation_Request {
   unsigned long int			requestingProcessIdentifier;
   char							requestingSource;
   BACnetLifeSafetyOperation	request;
   BACnetObjectIdentifier		objectIdentifier;
} LifeSafetyOperation_Request;

typedef struct tagSubscribeCOV_Request {
   unsigned long int		subscriberProcessIdentifier;
   BACnetObjectIdentifier   monitoredObjectIdentifier;
   bool						issueConfirmedNotifications;
   unsigned int				lifetime;
} SubscribeCOV_Request;

typedef struct tagDeleteObject_Request {
   BACnetObjectIdentifier   objectIdentifier;
} DeleteObject_Request;

/* moved to BitStrings
typedef struct BACnetLimitEnable {
   boolean   lowLimitEnable;
   boolean   highLimitEnable;
} BACnetLimitEnable;
*/

typedef struct tagBACnetPrescale {
   unsigned int   multiplier;
   unsigned int   moduloDivide;
} BACnetPrescale;

typedef struct tagBACnetAuthenticationFactor {
   BACnetAuthenticationFactorType   format_type;
   unsigned int		format_class;
   unsigned char	*value;
   int				valueLength;  // MAG added
} BACnetAuthenticationFactor;

typedef struct tagBACnetAuthenticationFactorFormat {
   BACnetAuthenticationFactorType   format_type;
   Unsigned16   vendor_id;
   Unsigned16   vendor_format;
} BACnetAuthenticationFactorFormat;

typedef struct tagBACnetNetworkSecurityPolicy {
   Unsigned8   port_id;
   BACnetSecurityPolicy   security_level;
} BACnetNetworkSecurityPolicy;

typedef struct tagBACnetPortPermission {
   Unsigned8	port_id;
   bool			enabled;
} BACnetPortPermission;

typedef struct tagBACnetProcessIdSelection {
   unsigned long int	processIdentifier;
   char					nullValue;
} BACnetProcessIdSelection;

// MAG 180323 2012-ai
typedef struct tagBACnetFDTEntry {
	unsigned char	bacnetip_address[4];
	unsigned int	time_to_live;
	unsigned int	remaining_time_to_live;
} BACnetFDTEntry;

// MAG 180323 2012-ai
typedef struct tagBACnetHostAddress {
	union {
		unsigned char none;
		unsigned char ip_address[4];
		char			name[MAX_PATH];  // MAG could be longer, but use this for now
	};
} BACnetHostAddress;

/***
 *    888      8888888888 888     888 8888888888 888            .d8888b.            .d8888b.   .d8888b.       8888888b.  8888888b.   .d88888b.  8888888b.  888     888  .d8888b. 88888888888 8888888 .d88888b.  888b    888  .d8888b.  
 *    888      888        888     888 888        888           d88P  Y88b          d88P  Y88b d88P  Y88b      888   Y88b 888   Y88b d88P" "Y88b 888  "Y88b 888     888 d88P  Y88b    888       888  d88P" "Y88b 8888b   888 d88P  Y88b 
 *    888      888        888     888 888        888           888    888          888    888        888      888    888 888    888 888     888 888    888 888     888 888    888    888       888  888     888 88888b  888 Y88b.      
 *    888      8888888    Y88b   d88P 8888888    888           888    888 888  888 888    888      .d88P      888   d88P 888   d88P 888     888 888    888 888     888 888           888       888  888     888 888Y88b 888  "Y888b.   
 *    888      888         Y88b d88P  888        888           888    888 `Y8bd8P' 888    888  .od888P"       8888888P"  8888888P"  888     888 888    888 888     888 888           888       888  888     888 888 Y88b888     "Y88b. 
 *    888      888          Y88o88P   888        888           888    888   X88K   888    888 d88P"           888        888 T88b   888     888 888    888 888     888 888    888    888       888  888     888 888  Y88888       "888 
 *    888      888           Y888P    888        888           Y88b  d88P .d8""8b. Y88b  d88P 888"            888        888  T88b  Y88b. .d88P 888  .d88P Y88b. .d88P Y88b  d88P    888       888  Y88b. .d88P 888   Y8888 Y88b  d88P 
 *    88888888 8888888888     Y8P     8888888888 88888888       "Y8888P"  888  888  "Y8888P"  888888888       888        888   T88b  "Y88888P"  8888888P"   "Y88888P"   "Y8888P"     888     8888888 "Y88888P"  888    Y888  "Y8888P"  
 *                                                                                                                                                                                                                                     
 *                                                                                                                                                                                                                                     
 *                                                                                                                                                                                                                                     
 */
// ABSTRACT-SYNTAX.&Type
typedef struct tagBACvalue {
	char				type;		// tag number, see 20.2.1.3.2. set to 0 for nullptr
	int					length;		// for octet, char, or bit strings
	union prop_value	value;
} BACvalue;

typedef struct tagActionCommand {         
struct tagActionCommand *next;
	dword				device_id;
	dword				object_id;
	dword				property_id;
	word				pa_index;
	enum ActionValueType	value_type;
	union 
	{
		BACnetBinaryPV	bproperty_value; 	//binary value MAG 13JAN12 removed enum keyword
		word			uproperty_value;	//unsigned word
		float			fproperty_value;	//float
	}					av;
	octet				priority;
	word				post_delay;
	bool				quit_on_failure;
	bool				write_successful;
} BACnetActionCommand;

// same as in db.h
typedef struct tagBACnetTimeStamp
 {
   octet                choice;
   union
   {
	 BACnetTime			time;
	 dword				sequence_number;
	 BACnetDateTime		date_time;
   }					u;
 } BACnetTimeStamp;

typedef struct tagVTClassList{
	struct tagVTClassList	*next;
	BACnetVTClass		vtclass;
} BACnetVTClassList;

typedef struct tagVTSession {
	struct tagVTSession		*next;
	word				local_session_id;
	word				remote_session_id;
	BACnetAddress		remote_address;
} BACnetVTSession;

typedef struct tagSessionKey {
	struct tagSessionKey			*next;
	octet						session_key[8];
	BACnetAddress				peer_address;
} BACnetSessionKey;

typedef struct tagRecipientProcess {
	struct tagRecipientProcess		*next;
	BACnetRecipient				recipient;
	word						process_id;
} BACnetRecipientProcess;

// MAG 10APR08 added for use with Global Group object
typedef struct tagBACnetDeviceObjectPropertyReferenceArray {
	int count;
	BACnetDeviceObjectPropertyReference *members;
} BACnetDeviceObjectPropertyReferenceArray;

typedef struct tagReadAccessSpecification {
	struct tagReadAccessSpecification	*next;
	dword								object_id;
	BACnetPropertyReference		/*far*/	*list_of_prop_ref;
} BACnetReadAccessSpecification;

// MAG 03JAN2012 add this struct
typedef struct tagBACnetSetpointReference {
	BACnetObjectPropertyReference *setpointReference;
	int count;
} BACnetSetpointReference;

/*
// MAG update 06FEB12
// note similarity to BACnetNotificationParameters
union BACnetEventParameter{
	struct {
		unsigned		timeDelay;
		unsigned char	bitmask;
		float			timeChange;
	} changeOfBitstring;  // type 0
	struct {
		unsigned	timeDelay;
		BACnetPropertyStates	statusFlag;
	} changeOfState;  // type 1
	struct {
		int		newValueChoice;
		union	ValueChoice {
					octet	changedBits[50];
					float	changedValue;
		};
		octet	statusFlag;
	} changeOfValue;  // type 2
	struct {
		BACvalue	commandValue;
		octet		statusFlag;
		BACvalue	feedbackValue;
	} commandFailure;  // type 3
	struct {
		float	referenceValue;
		octet	statusFlag;
		float	setpointValue;
		float	errorLimit;
	} floatingLimit;  // type 4
	struct {
		float	exceedingValue;
		octet	statusFlag;
		float	deadband;
		float	exceededLimit;
	} outOfRange;  // type 5
	BACnetPropertyValue	complexEventType;  // type 6, this should probably be an array
	struct {
		octet	newState;
		octet	newMode;
		octet	statusFlag;
		octet	operationExpected;
	} changeOfLifeSafety;  // type 8
	struct {
		octet	vendorId;
		octet	extendedEventType;
		ParametersBNP	parameters;
		/*union	parameters {
					octet	Null;
					float	Real;
					int		Unsigned;
					octet	Bool;
					double	Double;
					octet	octetString[20];
					octet	bitString[20];
					octet	Enum;
		};* /
	} extended;  // type 9
	struct {
		BACnetDeviceObjectPropertyReference	bufferProperty;
		float								deadband;
		float								exceededLimit;
	} bufferReady;  // type 10
	struct {
		float	exceedingValue;
		octet	statusFlag;
		float	exceededLimit;
	} unsignedRange;  // type 11
};*/
/* MAG 06FEB13- this does not correspond to the BACnetEventParameter listed in the standard
typedef struct tagBACnetEventParameter {
	BACnetEventType					event_type;
	BACnetListBitstringValue		bitmask;
	BACnetListBitstringValue		*list_bitstring_value;
	BACnetPropertyStates			*list_of_value;
	bool							use_property_increment;
	float							ref_property_increment;
	word							time_delay;
	BACnetObjectPropertyReference	feed_prop_ref;
	BACnetObjectPropertyReference	setpoint_ref;
	float							deadband;
	float							high_diff_limit;
	float							low_diff_limit;
	float							high_limit;
	float							low_limit;
	word							notification_threshold;          //Added By Zhu Zhenhua, 2004-5-20
	dword							previous_notification_count;      //Added By Zhu Zhenhua, 2004-5-20
} BACnetEventParameter;
*/
typedef struct tagBACnetLogDataEnum{
	union					log_data {
		bool				boolean_value0;
		float				real_value1;
		int					enum_value2;
		unsigned int		unsigned_value3;
		int					signed_value4;
		unsigned int		bitstring_value5;
		char				null_value6;
		unsigned int		failure7;
		char				any_value8[4];  // this is optional
	};
	int					log_data_choice;
} BACnetLogDataEnum;

// MAG 31JAN12
// this parameters is used BACnetEventParameter::extended
union	ParametersBEP {
			octet	Null;
			float	Real;
			int		Integer;
			octet	Bool;
			double	Double;
			octet	octetString[20];
			octet	bitString[20];
			octet	Enum;
			BACnetDeviceObjectPropertyReference	reference;
};

typedef struct tagListOfResults { // NOTE: part of read access result, used for ReadPropMultiple, 
	int		propertyIdentifier;
	int		propertyArrayIndex;
	octet	isError; // 0- value in bv, 1-error filled in readResult
	union  {
		BACvalue			value;
		PropertyAccessError	error;
	} readResult;
	//struct tagListOfResults *next;
} ListOfResults;

typedef struct tagBACnetPriorityValue{
	union		value {
		char   null;
		float   real;
		enum   enumerated;
		unsigned int   unsigned_val;
		bool   boolean;
		int   signed_val;
		double   double_val;
		BACnetTime   time;
		char   characterString[128];
		unsigned char   octetString[128];
		unsigned char   bitString[128];
		BACnetDate   date;
		BACnetObjectIdentifier   objectid;
		unsigned char   constructedValue[128];
		BACnetDateTime   datetime;
	};
	int value_choice;
} BACnetPriorityValue;

typedef struct tagfault_extended {
	unsigned		vendor_id; // was Unsigned16
	unsigned int	extended_fault_type;
	union			parameters {
		char			null_var;
		float			real_var;
		unsigned int	unsigned_var;
		bool			boolean_var;
		int				integer_var;
		double			double_var;
		unsigned char	*octet_var;
		int				octetLength;  // MAG added
		char				*characterString;
		int				characterStringLength; // MAG added
		unsigned char	*bitstring;
		int				bitstringLength;  // MAG added
		unsigned char	*enum_var;
		int				enumLength;  // MAG added
		BACnetDate				date;
		BACnetTime				time;
		BACnetObjectIdentifier   objectIdentifier;
		BACnetDeviceObjectPropertyReference   reference;
	}; //parameters
}  Fault_extended;

typedef struct tagfault_characterstring {
   CharacterString   list_of_fault_values;
} Fault_characterstring;

typedef struct tagfault_life_safety {
   BACnetLifeSafetyState   list_of_fault_values;
   BACnetDeviceObjectPropertyReference   mode_property_reference;
} Fault_life_safety;

typedef struct tagfault_state {
   BACnetPropertyStates   list_of_fault_values;
} Fault_state;

typedef struct tagfault_status_flags {
   BACnetDeviceObjectPropertyReference   status_flags_reference;
} Fault_status_flags;

typedef struct tagWritePropertyMultiple_Error {
   Error   errorType;
   BACnetObjectPropertyReference   firstFailedWriteAttempt;
} WritePropertyMultiple_Error;

typedef struct tagChangeList_Error {
   Error   errorType;
   unsigned int   firstFailedElementNumber;
} ChangeList_Error;

typedef struct tagConfirmedPrivateTransfer_Error {
   Error   errorType;
   unsigned int   vendorID;
   unsigned int   serviceNumber;
   BACvalue   errorParameters;
} ConfirmedPrivateTransfer_Error;

typedef struct tagVTClose_Error {
   Error   errorType;
   Unsigned8   listOfVTSessionIdentifiers;
} VTClose_Error;

union BACnetCalendarEntry {
   BACnetDate		date;
   BACnetDateRange	dateRange;
   BACnetWeekNDay	weekNDay;
}; //BACnetCalendarEntry;

typedef struct tagGetAlarmSummary_ACK {
   BACnetObjectIdentifier   objectIdentifier;
   BACnetEventState   alarmState;
   BACnetEventTransitionBits   acknowledgedTransitions;
} GetAlarmSummary_ACK;

typedef struct tagGetEnrollmentSummary_ACK {
   BACnetObjectIdentifier   objectIdentifier;
   BACnetEventType   eventType;
   BACnetEventState   eventState;
   Unsigned8   priority;
   unsigned int   notificationClass;
} GetEnrollmentSummary_ACK;

typedef struct tagSubscribeCOVProperty_Request {
   unsigned long int   subscriberProcessIdentifier;
   BACnetObjectIdentifier   monitoredObjectIdentifier;
   bool   issueConfirmedNotifications;
   unsigned int   lifetime;
   BACnetPropertyReference   monitoredPropertyIdentifier;
   float   covIncrement;
} SubscribeCOVProperty_Request;

typedef struct tagAddressBinding {
	struct tagAddressBinding	*next;
	dword						device_object_id;
	BACnetAddress				device_address;
} BACnetAddressBinding;

typedef struct tagBACnetDeviceObjectReference {
   BACnetObjectIdentifier   deviceIdentifier;  // optional
   BACnetObjectIdentifier   objectIdentifier;
} BACnetDeviceObjectReference;

typedef struct tagBACnetAssignedAccessRights {
	BACnetObjectIdentifier	assigned_access_rights;
	unsigned char					enable;
} BACnetAssignedAccessRights;

typedef struct tagReadAccessSpec{
	BNObjId				objid;		// struct with .object and .id
	int					numprop;	// might have several different props requested from one object
	BACnetPropertyRef	props[10];
} ReadAccessSpecification;

typedef struct tagDestination {
	struct tagDestination	*next;
	octet				valid_days;
	BACnetTime			from_time;
	BACnetTime			to_time;
	BACnetRecipient		recipient;
	word				process_id;
	bool				notification;
	octet				transitions;
} BACnetDestination;

typedef struct tagBACnetDailySchedule{
	BACnetTimeValue * day_schedule;
	int count;
} BACnetDailySchedule;

typedef struct tagSpecialEvent {   //only one of date, date_range, weekNday, calendar_ref should be used at a time
	struct tagSpecialEvent	/*far*/	*next;
	octet					choice;
	union {
		BACnetDate				date;
		BACnetDateRange			date_range;
		BACnetWeekNDay			weekNday;
		BACnetObjectIdentifier	calendar_ref;
		}					u;
	BACnetTimeValue		/*far*/	*list_of_time_values;
	word					event_priority;
} BACnetSpecialEvent; 

typedef struct tagBACnetLogRecord {
   BACnetDateTime   timestamp;
   //CHOICE   logDatum;
   union {
	   BACnetLogStatus	log_status;
	   bool				boolean_value;
	   float			real_value;
	   unsigned int		enum_value;
	   unsigned int		unsigned_value;
	   int				signed_value;
	   unsigned char	bitstring_value;
	   unsigned char	null_value;
	   unsigned char	failure;
	   float			time_change;
	   BACvalue			any_value;
	} logDatum; //logDatum
   BACnetStatusFlags   statusFlags;
} BACnetLogRecord;

// MAG 19DEC11
typedef struct tagBACnetCredentialAuthenticationFactor {
	BACnetAccessAuthenticationFactorDisable disable;
	BACnetAuthenticationFactor				authentication_factor;
} BACnetCredentialAuthenticationFactor;

typedef struct tagBACnetSecurityKeySet {
   unsigned int   key_revision;
   BACnetDateTime   activation_time;
   BACnetDateTime   expiration_time;
   BACnetKeyIdentifier   key_ids;
} BACnetSecurityKeySet;

typedef struct tagBACnetEventNotificationSubscription {
   BACnetRecipient   recipient;
   unsigned long int   processIdentifier;
   bool   issueconfirmedNotifications;
   unsigned int   tinmeRemaining;
} BACnetEventNotificationSubscription;

// MAG 180323 2012-ai
typedef struct tagBACnetHostNPort {
	BACnetHostAddress	host;
	unsigned int		port;
} BACnetHostNPort;

/***
 *    888      8888888888 888     888 8888888888 888            .d8888b.            .d8888b.   .d8888b.       8888888b.  8888888b.   .d88888b.  8888888b.  888     888  .d8888b. 88888888888 8888888 .d88888b.  888b    888  .d8888b.  
 *    888      888        888     888 888        888           d88P  Y88b          d88P  Y88b d88P  Y88b      888   Y88b 888   Y88b d88P" "Y88b 888  "Y88b 888     888 d88P  Y88b    888       888  d88P" "Y88b 8888b   888 d88P  Y88b 
 *    888      888        888     888 888        888           888    888          888    888      .d88P      888    888 888    888 888     888 888    888 888     888 888    888    888       888  888     888 88888b  888 Y88b.      
 *    888      8888888    Y88b   d88P 8888888    888           888    888 888  888 888    888     8888"       888   d88P 888   d88P 888     888 888    888 888     888 888           888       888  888     888 888Y88b 888  "Y888b.   
 *    888      888         Y88b d88P  888        888           888    888 `Y8bd8P' 888    888      "Y8b.      8888888P"  8888888P"  888     888 888    888 888     888 888           888       888  888     888 888 Y88b888     "Y88b. 
 *    888      888          Y88o88P   888        888           888    888   X88K   888    888 888    888      888        888 T88b   888     888 888    888 888     888 888    888    888       888  888     888 888  Y88888       "888 
 *    888      888           Y888P    888        888           Y88b  d88P .d8""8b. Y88b  d88P Y88b  d88P      888        888  T88b  Y88b. .d88P 888  .d88P Y88b. .d88P Y88b  d88P    888       888  Y88b. .d88P 888   Y8888 Y88b  d88P 
 *    88888888 8888888888     Y8P     8888888888 88888888       "Y8888P"  888  888  "Y8888P"   "Y8888P"       888        888   T88b  "Y88888P"  8888888P"   "Y88888P"   "Y8888P"     888     8888888 "Y88888P"  888    Y888  "Y8888P"  
 *                                                                                                                                                                                                                                     
 *                                                                                                                                                                                                                                     
 *                                                                                                                                                                                                                                     
 */
// MAG 03JAN13 add this struct
typedef struct tagBACnetActionList {
	BACnetActionCommand *commands;
	int count;
} BACnetActionList;

typedef struct tagBACnetLogData{
	BACnetLogStatus		log_status;
	BACnetLogDataEnum	*log_data;
	int					*log_data_count;
	float				time_change;
} BACnetLogData;

typedef struct tagBACnetPropertyValue {
	int			propertyIdentifier;
	int			propertyArrayIndex;		// optional, -1 for not used
	BACvalue	value;
	int			priority;				// optional, -1 for not used
} BACnetPropertyValue;

typedef struct tagBACnetDeviceObjectPropertyValue {
   BACnetObjectIdentifier   deviceIdentifier;
   BACnetObjectIdentifier   objectIdentifier;
   BACnetPropertyIdentifier   propertyIdentifier;
   unsigned int   arrayIndex;
   BACvalue   value;
} BACnetDeviceObjectPropertyValue;

typedef struct tagBACnetPriorityArray{
	BACnetPriorityValue values[16];
}BACnetPriorityArray;

union BACnetOptionalCharacterString {
	unsigned char null;
	BACvalue characterString;  // must always be a string type (7)
};

union BACnetFaultParameter {
   //nullptr   none;
   CharacterString   fault_characterstring;
   Fault_extended   fault_extended;
   Fault_life_safety   fault_life_safety;
   Fault_state   fault_state;
   Fault_status_flags   fault_status_flags;
}; //BACnetFaultParameter;

typedef struct tagBACvalueList {
	BACvalue				value;
	struct tagBACvalueList	*next;
} BACvalueList;

// used in GetEventInformation-ACK
typedef struct taglistOfEventSummaries {
   BACnetObjectIdentifier   objectIdentifier;
   BACnetEventState   eventState;
   BACnetEventTransitionBits   acknowledgedTransitions;
   BACnetTimeStamp   eventTimeStamps[3];  // MAG modified
   BACnetNotifyType   notifyType;
   BACnetEventTransitionBits   eventEnable;
   unsigned int  eventPriorities[3];  // MAG modified
} ListOfEventSummaries;

union BACnet_Error {
   Error   acknowledgeAlarm;
   Error   confirmedCOVNotification;
   Error   confirmedEventNotification;
   Error   getAlarmSummary;
   Error   getEnrollmentSummary;
   Error   subscribeCOV;
   Error   atomicReadFile;
   Error   atomicWriteFile;
   ChangeList_Error   addListElement;
   ChangeList_Error   removeListElement;
   CreateObject_Error   createObject;
   Error   deleteObject;
   Error   readProperty;
   Error   readPropertyMultiple;
   Error   writeProperty;
   WritePropertyMultiple_Error   writePropertyMultiple;
   Error   deviceCommunicationControl;
   ConfirmedPrivateTransfer_Error   confirmedPrivateTransfer;
   Error   confirmedTextMessage;
   Error   reinitializeDevice;
   Error   vtOpen;
   VTClose_Error   vtClose;
   Error   vtData;
   Error   readRange;
   Error   lifeSafetyOperation;
   Error   subscribeCOVProperty;
   Error   getEventInformation;
}; //BACnet_Error;

typedef struct tagAcknowledgeAlarm_Request {
   unsigned long int   acknowledgingProcessIdentifier;
   BACnetObjectIdentifier   eventObjectIdentifier;
   BACnetEventState   eventStateAcknowledged;
   BACnetTimeStamp   timeStamp;
   char   acknowledgmentSource;
   BACnetTimeStamp   timeOfAcknowledgment;
} AcknowledgeAlarm_Request;

typedef struct tagGetEnrollmentSummary_Request {
   short int   acknowledgmentFilter;
   BACnetRecipientProcess   enrollmentFilter;
   short int   eventStateFilter;
   BACnetEventType   eventTypeFilter;
   PriorityFilter   priorityFilter;
   unsigned int   notificationClassFilter;
} GetEnrollmentSummary_Request;

typedef struct tagAddListElement_Request {
   BACnetObjectIdentifier   objectIdentifier;
   BACnetPropertyIdentifier   propertyIdentifier;
   unsigned int   propertyArrayIndex;
   BACvalue   listOfElements;
} AddListElement_Request;

typedef struct tagBACnetAccessRule {
	unsigned char						timeRangeSpecifier_enum; // enum 0-specified  1-always
	BACnetDeviceObjectPropertyReference timeRange;  // optional
	unsigned char						locationSpecifier_enum; // enum 0-specified  1-all
	BACnetDeviceObjectReference			location;  // optional
	bool								enable;
} BACnetAccessRule;

//Xiao Shiyuan 2002-7-23
typedef struct tagCOVSubscription {
	struct tagCOVSubscription		*next;
	BACnetRecipientProcess			recipient;
	BACnetObjectPropertyReference	monitoredPropertyReference;
	bool							notification;
	word							timeRemaining;
	float							covIncrement;
} BACnetCOVSubscription;

typedef struct tagReadAccessResult{
	BNObjId			objid;		// struct with .object and .id
	int				numprop;	// might have several different props requested from one object
	ListOfResults	props[10];
} ReadAccessResult;

typedef struct tagBACnetExceptionSchedule {
	word					size;
	BACnetSpecialEvent	/*far*/	*special_event;
} BACnetExceptionSchedule;

typedef struct tagBACnetAuthenticationRule {
   BACnetDeviceObjectReference   authentication_factor_input;
   unsigned int   authentication_factor_choice;
} BACnetAuthenticationRule;

// MAG 180323 2012-ai
typedef struct tagBACnetBDTEntry {
	BACnetHostNPort		bbmd_address;
	unsigned char		broadcast_mask[4];	// MAG guessing on length to match IP address
} BACnetBDTEntry;


/***
 *    888      8888888888 888     888 8888888888 888            .d8888b.            .d8888b.      d8888       8888888b.  8888888b.   .d88888b.  8888888b.  888     888  .d8888b. 88888888888 8888888 .d88888b.  888b    888  .d8888b.  
 *    888      888        888     888 888        888           d88P  Y88b          d88P  Y88b    d8P888       888   Y88b 888   Y88b d88P" "Y88b 888  "Y88b 888     888 d88P  Y88b    888       888  d88P" "Y88b 8888b   888 d88P  Y88b 
 *    888      888        888     888 888        888           888    888          888    888   d8P 888       888    888 888    888 888     888 888    888 888     888 888    888    888       888  888     888 88888b  888 Y88b.      
 *    888      8888888    Y88b   d88P 8888888    888           888    888 888  888 888    888  d8P  888       888   d88P 888   d88P 888     888 888    888 888     888 888           888       888  888     888 888Y88b 888  "Y888b.   
 *    888      888         Y88b d88P  888        888           888    888 `Y8bd8P' 888    888 d88   888       8888888P"  8888888P"  888     888 888    888 888     888 888           888       888  888     888 888 Y88b888     "Y88b. 
 *    888      888          Y88o88P   888        888           888    888   X88K   888    888 8888888888      888        888 T88b   888     888 888    888 888     888 888    888    888       888  888     888 888  Y88888       "888 
 *    888      888           Y888P    888        888           Y88b  d88P .d8""8b. Y88b  d88P       888       888        888  T88b  Y88b. .d88P 888  .d88P Y88b. .d88P Y88b  d88P    888       888  Y88b. .d88P 888   Y8888 Y88b  d88P 
 *    88888888 8888888888     Y8P     8888888888 88888888       "Y8888P"  888  888  "Y8888P"        888       888        888   T88b  "Y88888P"  8888888P"   "Y88888P"   "Y8888P"     888     8888888 "Y88888P"  888    Y888  "Y8888P"  
 *                                                                                                                                                                                                                                     
 *                                                                                                                                                                                                                                     
 *                                                                                                                                                                                                                                     
 */

// MAG 31JAN12
// this parameters is used BACnetNotificationParameters::extended
union	ParametersBNP {
			octet	Null;
			float	Real;
			int		Integer;
			octet	Bool;
			double	Double;
			octet	octetString[20];
			octet	bitString[20];
			octet	Enum;
			BACnetDeviceObjectPropertyValue	propertyValue;
};

// MAG 10APR08 2004 Add B. used in Global Group
typedef struct tagPropertyAccessResult {
	BACnetObjectIdentifier		objectIdentifier;
	BACnetPropertyIdentifier	propertyIdentifier;
	word						propertyArrayIndex; // optional-used only with array datatype- if omitted with an array then the entire array is referenced
	BACnetObjectIdentifier		deviceIdentifier;	// optional
	union accessResult {
		BACvalue	propertyValue;
		word		propertyAccessError;
	};
} BACnetPropertyAccessResult;  // MAG 30JAN12- this had a '2' on the end, removed it.

typedef struct tagBACnet_Error_PDU {
   unsigned int   pdu_type;
   unsigned int   reserved;
   unsigned int   original_invokeID;
   BACnetConfirmedServiceChoice   error_choice;
   BACnet_Error   error;
} BACnet_Error_PDU;

typedef struct tagWriteAccessSpec{
	BNObjId				objid;		// struct with .object and .id
	int					numprop;	// might have several different props requested from one object
	BACnetPropertyValue	props[10];
} WriteAccessSpecification;

/* Defined in API file as CreateObjectREQ
typedef struct tagCreateObject_Request {
   ObjectSpecifier   objectSpecifier;
   BACnetPropertyValue   listOfInitialValues;
} CreateObject_Request;
*/
typedef struct tagReadProperty_Request {
   BACnetObjectIdentifier   objectIdentifier;
   BACnetPropertyIdentifier   propertyIdentifier;
   unsigned int   propertyArrayIndex;
} ReadProperty_Request;

typedef struct tagReadProperty_ACK {
   BACnetObjectIdentifier   objectIdentifier;
   BACnetPropertyIdentifier   propertyIdentifier;
   unsigned int   propertyArrayIndex;
   BACvalue   propertyValue;
} ReadProperty_ACK;

union BACnetNotificationParameters{  // MAG added 12JAN06
	struct tchangeOfBitstring{
		octet	referencedBitstring[50];
		octet	statusFlag;
	} changeOfBitstring;  // type 0
	struct tchangeOfState {
		octet	newState;
		octet	statusFlag;
	} changeOfState;  // type 1
	struct tchangeOfValue {
		int		newValueChoice;
		union	ValueChoice {
					octet	changedBits[50];
					float	changedValue;
		};
		octet	statusFlag;
	} changeOfValue;  // type 2
	struct tcommandFailure {
		BACvalue	commandValue;
		octet		statusFlag;
		BACvalue	feedbackValue;
	} commandFailure;  // type 3
	struct tfloatingLimit{
		float	referenceValue;
		octet	statusFlag;
		float	setpointValue;
		float	errorLimit;
	} floatingLimit;  // type 4
	struct toutOfRange {
		float	exceedingValue;
		octet	statusFlag;
		float	deadband;
		float	exceededLimit;
	} outOfRange;  // type 5
	BACnetPropertyValue	complexEventType;  // type 6, this should probably be an array
	struct tchangeOfLifeSafety {
		octet	newState;
		octet	newMode;
		octet	statusFlag;
		octet	operationExpected;
	} changeOfLifeSafety;  // type 8
	struct textended {
		octet	vendorId;
		octet	extendedEventType;
		ParametersBNP	parameters;
		/*union	parameters {
					octet	Null;
					float	Real;
					int		Unsigned;
					octet	Bool;
					double	Double;
					octet	octetString[20];
					octet	bitString[20];
					octet	Enum;
		};*/
	} extended;  // type 9
	struct tbufferReady {
		BACnetDeviceObjectPropertyReference	bufferProperty;
		float								deadband;
		float								exceededLimit;
	} bufferReady;  // type 10
	struct tunsignedRange {
		float	exceedingValue;
		octet	statusFlag;
		float	exceededLimit;
	} unsignedRange;  // type 11
};

typedef struct tagBACnetLogMultipleRecord {
   BACnetDateTime   timestamp;
   BACnetLogData   log_data;	// MAG changed from logData in 2012-am
} BACnetLogMultipleRecord;

typedef struct tagBACnetAuthenticationPolicy {
	BACnetAuthenticationRule	*policy;
	unsigned char				order_enforced;	// boolean
	dword						timeout;  // go to your corner!
} BACnetAuthenticationPolicy;

// MAG moved from Level 02
// MAG update 06FEB12
// note similarity to BACnetNotificationParameters
union BACnetEventParameter{
	struct tchangeOfBitstring {
		unsigned		timeDelay;
		unsigned char	bitmask;
		float			timeChange;
	} changeOfBitstring;  // type 0
	struct tchangeOfState {
		unsigned	timeDelay;
		BACnetPropertyStates	statusFlag;
	} changeOfState;  // type 1
	struct tchangeOfValue {
		int		newValueChoice;
		union	ValueChoice {
					octet	changedBits[50];
					float	changedValue;
		};
		octet	statusFlag;
	} changeOfValue;  // type 2
	struct tcommandFailure {
		BACvalue	commandValue;
		octet		statusFlag;
		BACvalue	feedbackValue;
	} commandFailure;  // type 3
	struct tfloatingLimit {
		float	referenceValue;
		octet	statusFlag;
		float	setpointValue;
		float	errorLimit;
	} floatingLimit;  // type 4
	struct toutOfRange{
		float	exceedingValue;
		octet	statusFlag;
		float	deadband;
		float	exceededLimit;
	} outOfRange;  // type 5
	BACnetPropertyValue	complexEventType;  // type 6, this should probably be an array
	struct tchangeOfLifeSafety {
		octet	newState;
		octet	newMode;
		octet	statusFlag;
		octet	operationExpected;
	} changeOfLifeSafety;  // type 8
	struct textended {
		octet	vendorId;
		octet	extendedEventType;
		ParametersBNP	parameters;
		/*union	parameters {
					octet	Null;
					float	Real;
					int		Unsigned;
					octet	Bool;
					double	Double;
					octet	octetString[20];
					octet	bitString[20];
					octet	Enum;
		};*/
	} extended;  // type 9
	struct tbufferReady {
		BACnetDeviceObjectPropertyReference	bufferProperty;
		float								deadband;
		float								exceededLimit;
	} bufferReady;  // type 10
	struct tunsignedRange {
		float	exceedingValue;
		octet	statusFlag;
		float	exceededLimit;
	} unsignedRange;  // type 11
};

/***
 *    888      8888888888 888     888 8888888888 888            .d8888b.            .d8888b.  888888888       8888888b.  8888888b.   .d88888b.  8888888b.  888     888  .d8888b. 88888888888 8888888 .d88888b.  888b    888  .d8888b.  
 *    888      888        888     888 888        888           d88P  Y88b          d88P  Y88b 888             888   Y88b 888   Y88b d88P" "Y88b 888  "Y88b 888     888 d88P  Y88b    888       888  d88P" "Y88b 8888b   888 d88P  Y88b 
 *    888      888        888     888 888        888           888    888          888    888 888             888    888 888    888 888     888 888    888 888     888 888    888    888       888  888     888 88888b  888 Y88b.      
 *    888      8888888    Y88b   d88P 8888888    888           888    888 888  888 888    888 8888888b.       888   d88P 888   d88P 888     888 888    888 888     888 888           888       888  888     888 888Y88b 888  "Y888b.   
 *    888      888         Y88b d88P  888        888           888    888 `Y8bd8P' 888    888      "Y88b      8888888P"  8888888P"  888     888 888    888 888     888 888           888       888  888     888 888 Y88b888     "Y88b. 
 *    888      888          Y88o88P   888        888           888    888   X88K   888    888        888      888        888 T88b   888     888 888    888 888     888 888    888    888       888  888     888 888  Y88888       "888 
 *    888      888           Y888P    888        888           Y88b  d88P .d8""8b. Y88b  d88P Y88b  d88P      888        888  T88b  Y88b. .d88P 888  .d88P Y88b. .d88P Y88b  d88P    888       888  Y88b. .d88P 888   Y8888 Y88b  d88P 
 *    88888888 8888888888     Y8P     8888888888 88888888       "Y8888P"  888  888  "Y8888P"   "Y8888P"       888        888   T88b  "Y88888P"  8888888P"   "Y88888P"   "Y8888P"     888     8888888 "Y88888P"  888    Y888  "Y8888P"  
 *                                                                                                                                                                                                                                     
 *                                                                                                                                                                                                                                     
 *                                                                                                                                                                                                                                     
 */
// MAG 10APR08 add array version for Global Group object
typedef struct tagPropertyAccessResultArray {
	struct BACnetPropertyAccessResult *members;
	int count;
} BACnetPropertyAccessResultArray;

typedef struct tagConfirmedCOVNotification_Request {
	unsigned long int   subscriberProcessIdentifier;
	BACnetObjectIdentifier   initiatingDeviceIdentifier;
	BACnetObjectIdentifier   monitoredObjectIdentifier;
	unsigned int   timeRemaining;
	BACnetPropertyValue   listOfValues;
} ConfirmedCOVNotification_Request;

/*typedef struct tagConfirmedEventNotificationRequest {
	dword					processIdentifier;
	BACnetObjectIdentifier	initiatingDeviceIdentifier;
	BACnetObjectIdentifier	eventObjectIdentifier;
	BACnetTimeStamp			timeStamp;
	unsigned				notificationClass;
	unsigned char			priority;
	BACnetEventType			eventType;
	char					messageText[128];
	BACnetNotifyType		notifyType;
	bool					ackRequired;
	BACnetEventState		fromState;
	BACnetEventState		toState;
	BACnetNotificationParameters eventValues;// MAG 07APR08 NOTE- this struct is described on PP 2004-419..420.  Have fun.
} ConfirmedEventNotificationRequest;*/

typedef struct tagConfirmedEventNotification_Request {
	unsigned long int   processIdentifier;
	BACnetObjectIdentifier   initiatingDeviceIdentifier;
	BACnetObjectIdentifier   eventObjectIdentifier;
	BACnetTimeStamp   timeStamp;
	unsigned int   notificationClass;
	Unsigned8   priority;
	BACnetEventType   eventType;
	char   messageText[128];
	BACnetNotifyType   notifyType;
	unsigned char    ackRequired;// MAG 170522 changed type from BOOLEAN to this.  BOOLEAN was defined as BOOL, which was defined as "typedef unsigned char"
	BACnetEventState   fromState;
	BACnetEventState   toState;
	BACnetNotificationParameters   eventValues;
} ConfirmedEventNotification_Request;


/***
 *    888      8888888888 888     888 8888888888 888            .d8888b.           Y88b   d88P Y88b   d88P      8888888b.  8888888b.   .d88888b.  8888888b.  888     888  .d8888b. 88888888888 8888888 .d88888b.  888b    888  .d8888b.  
 *    888      888        888     888 888        888           d88P  Y88b           Y88b d88P   Y88b d88P       888   Y88b 888   Y88b d88P" "Y88b 888  "Y88b 888     888 d88P  Y88b    888       888  d88P" "Y88b 8888b   888 d88P  Y88b 
 *    888      888        888     888 888        888           888    888            Y88o88P     Y88o88P        888    888 888    888 888     888 888    888 888     888 888    888    888       888  888     888 88888b  888 Y88b.      
 *    888      8888888    Y88b   d88P 8888888    888           888    888 888  888    Y888P       Y888P         888   d88P 888   d88P 888     888 888    888 888     888 888           888       888  888     888 888Y88b 888  "Y888b.   
 *    888      888         Y88b d88P  888        888           888    888 `Y8bd8P'    d888b       d888b         8888888P"  8888888P"  888     888 888    888 888     888 888           888       888  888     888 888 Y88b888     "Y88b. 
 *    888      888          Y88o88P   888        888           888    888   X88K     d88888b     d88888b        888        888 T88b   888     888 888    888 888     888 888    888    888       888  888     888 888  Y88888       "888 
 *    888      888           Y888P    888        888           Y88b  d88P .d8""8b.  d88P Y88b   d88P Y88b       888        888  T88b  Y88b. .d88P 888  .d88P Y88b. .d88P Y88b  d88P    888       888  Y88b. .d88P 888   Y8888 Y88b  d88P 
 *    88888888 8888888888     Y8P     8888888888 88888888       "Y8888P"  888  888 d88P   Y88b d88P   Y88b      888        888   T88b  "Y88888P"  8888888P"   "Y88888P"   "Y8888P"     888     8888888 "Y88888P"  888    Y888  "Y8888P"  
 *                                                                                                                                                                                                                                       
 *                                                                                                                                                                                                                                       
 *                                                                                                                                                                                                                                       
 */
// LEVEL NOT YET DETERMINED, OR ABOVE 5
typedef struct tagBACnetEventLogRecord {
	BACnetDateTime	timestamp;
	octet			logDatumChoice;
	union {		// logDatum
		BACnetLogStatus						log_status;
		ConfirmedEventNotification_Request	notification;
		float								timeChange;
	} logDatum;
} BACnetEventLogRecord;

#endif // BACnetProductions














