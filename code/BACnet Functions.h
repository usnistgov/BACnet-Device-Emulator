// MAG 260420 add file
// Purpose: hold namespace used to list BACnet DLL functions
#pragma once
#include <vector>
#include <string>
#include <BACnet_api.h>

// MAG 260428
// copied from BACnet_api.h
// If any mods are needed change there too!
//typedef struct tagdevAddr { // Holds all network address info for a source, dest, or router
//	unsigned char	mac_device[6];		// mac of device (raw, not printable chars)
//	int				mac_device_len;		// length of mac_device, in octets
//	int				mac_device_dec;		// mac of device in decimal (if possible, or 0)
//	char			mac_device_pr[15];	// mac of device (in printable chars, might include 0x and \n)
//	unsigned char	ip[4];				// ip address of this device
//	int				ip_port;			// should be 0xBAC0 (47808) by default
//	char			ip_or_eth;			// ip = 1, eth = 0, both = 3
//	int				net;				// network device is on
//	int				device_id;			// MAG 260213 add this. Device object ID, unique on network.
//} DevAddr;

namespace BACfuncs {
	extern "C" __declspec(dllexport) int __stdcall WPCInit(void);
	extern "C" __declspec(dllimport) int GetAdapterIPSLI(int i, char* label);
	extern "C" __declspec(dllimport) int GetDefaultAdapter(void);
	extern "C" __declspec(dllexport) int SetDefaultAdapter(int i);
	
	extern "C" __declspec(dllexport) std::string BACvalueToString(BACvalue* bv);
	extern "C" __declspec(dllexport) int StringToBACvalue(const char* cp, BACvalue* bv);
	extern "C" __declspec(dllexport) int SendIAM(int devid, int subnet, int segsup, int vendor);

	//extern "C" __declspec(dllexport) int GetDefaultAdapter(void);
	extern "C" __declspec(dllexport) int GetDefaultAdapterInfo(DevAddr* rv);
	extern "C" __declspec(dllexport) std::vector<std::string> GetErrorDetails();

	extern "C" __declspec(dllexport) int SendIAMDev(DevAddr* controller, DevAddr* router, int segsup, int vendor);

	extern "C" __declspec(dllexport) int fnBACdllGetBAC(datatransfer* mydata);
	extern "C" __declspec(dllexport) int SendBACnetUDPIP(datatransfer* mydata, int count);
	extern "C" __declspec(dllexport) int SetDeviceMAC(DevAddr* rv, char* hexmac);
	extern "C" __declspec(dllexport) void GetBACVersionString(char *rv);
}
