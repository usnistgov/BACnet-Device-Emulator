#pragma once
#include "BACnetController.h"  // this will also include obect, properties, and everything else required
#include <algorithm> // for std::sort
// MAG 260416 Create class
// Purpose: to hold data on a BACnet subnet. Not a BBMD.
// Data is network number, connected networks, and a list of device id's 
class BACnetSubnet
{
private:
	unsigned int		subnet_id;		// subnet number, 0 for not set range is 1-0xFFFE (65534)
	std::vector<int>	device_id_list; // device id of each device on network
	std::vector<int>	connected_net;	// connected subnets-  (not sure if this will be useful!)
	int					highMAC;		// highest instance of MS/TP MAC address implemented
	uint				treeState;		// Use with CTreeCtrl::GetItemState and SetItemState to preserve state (open/closed) between redraws
	HTREEITEM			treepos;		// Position on NET tree (left tree) not focus tree
	int					isReal;			// set to 1 for scanned subnets, 0 for virtual subnets. Real subnets can not have virtual controllers added.
										// NOTE "real" subnets may be virtual on a remote device, but that is not our concern.
public:
	BACnetSubnet();
	BACnetSubnet(unsigned int subid);

	int SetSubnet(unsigned int subid);
	int GetSubnet();

	void SetReal(int rv) { if (rv == 1) isReal = 1; else isReal = 0; };
	int GetReal() { return isReal; };

	int GetHighMAC() { return highMAC; };
	void IncrementHighMAC() { highMAC++; };
	void ResetHighMAC() { highMAC = 0; };

	int HasDevice(int devid);
	int AddDevice(int devid);
	int DelDevice(int devid);
	std::vector<int> GetDeviceList();

	HTREEITEM GetTreepos() { return treepos; }
	void SetTreepos(HTREEITEM rv) { treepos = rv; }

	void	SetTreeState(uint tsin) { treeState = tsin; };
	uint	GetTreeState() { return treeState; };

	bool operator<(const BACnetSubnet& other) const {
		return subnet_id < other.subnet_id;
	}
	bool operator<=(const BACnetSubnet& other) const {
		return subnet_id <= other.subnet_id;
	}

	bool operator>(const BACnetSubnet& other) const {
		return subnet_id > other.subnet_id;
	}
	bool operator>=(const BACnetSubnet& other) const {
		return subnet_id >= other.subnet_id;
	}

	bool operator==(const BACnetSubnet& other) const {
		return subnet_id == other.subnet_id;
	}

};

