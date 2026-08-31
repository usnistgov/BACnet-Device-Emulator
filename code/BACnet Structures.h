// MAG 260504 Holds struct and related definitions used to impleent BACnet.
// Mostly copied from BDS file BACnet_api.h andrelated.

// BACnet-Confirmed-Request-PDU
// MAG 09JAN2012 confirms to 2010
// NOTE- cryptic abbreviations should be changed to names on Chapter 21 to improve readability
// SEQUENCE
/*
typedef struct tagConfREQ {
	octet			seg;	// 0-unsegmented 1-segmented
	octet			mor;	// 0-no more segments follow 1-more segments follow
	octet			sa;		// 0-segments resp not accepted 1-accepted
	octet			maxSeg; // 0..7  2^n segments -  number of response segments accepted per 20.1.2.4
	octet			maxRes; // 0..15  size of max resp accepted per 20.1.2.5
	octet			invid;	// invoke id
	octet			seqNo;	// sequence number (if SEG=1)
	octet			wSize;	// window size (if SEG=1)
	int				choice;	// service-choice from BACnetConfirmedServiceChoice
	ConfREQtypes	service;// service-request
} ConfREQ;


union Packet {				// choice
	ConfREQ			confREQ;	// 0  confirmed-request
	UnconfREQ		uconfREQ;	// 1  unconfirmed-request
	SimpACK			simpACK;	// 2  simple-ACK
	CompACK			compACK;	// 3  complex-ACK
	SegmentACK		segmentACK;	// 4  segment-ACK
	ErrorPacket		errorPacket;// 5  error
	RejectPacket	rejPacket;  // 6  reject
	AbortPacket		abortPacket;// 7  abort
	NLM				networkmsg;	// 8  hack- use this to send network layer messages, instead of an APDU
};

typedef struct tagdatatransfer {  // designed to transfer data to and from the BACnet dll
	device			source;	// source device
	device			dest;	// destination device
	octet			priority;// B11-Life Safety B10-Critical Equipment B01-Urgent B00-Normal
	int				choice; //  Service choice 0-8 for packet structure
	Packet			packet; // select type of packet- this acts as the BACnetPDU type
	octet			invid;	// invoke id (when receiving) / set hop count (when transmitting)
	int				length; // MAG 17NOV05 length of original APDU (for recv packets)
} datatransfer;
*/