#pragma once

#include "BACnetObject.h"
#include "SequenceInterface.h"
#include <algorithm> // for std::sort

// MAG 260717 StateMap holds mapping information for the state arrays. Each (obj, inst) pair is mapped to a index in the state array (map);
class StateMap
{
public:
	StateMap() { obj = 0; inst = 0; map = 0; };
	int obj;
	int inst;
	int map;
};



class BACnetController
{
private:
	std::vector<BACnetObject>	objectList;	// NOTE public functions never reference this by index. All function parameters are device ID.
	// MAG use controllerAddr.device
	// int						devID;		// shortcut to Device Object instance ID for convenience. Not settable externally.
	int							isTemplate; // 0=not a template, >0 is a template DEVICE ID this is never an index!

	// MAG not positive this will be best way moving forward, feel free to change
	// MAG NOTE use controllerAddr.net, do not duplicate data
	//unsigned int				subnetOn;			// Network subnet device is on, 0 for not set range is 1-0xFFFE (65534)
	//int						subnetConnected;	// Network subnet device is connected to
	DevAddr						controllerAddr;		// info for this device
	DevAddr						controllerRouter;	// info for router, if needed

	uint						treeState;		// Use with CTreeCtrl::GetItemState and SetItemState to preserve state (open/closed) between redraws
	HTREEITEM					treepos;
	std::vector<std::string>	messageStrings; // used to collect status strings to pass to calling network object

	// MAG 260717 add sequence of operations logic (DLL) and associated code
	SequenceInterface			localSeq;
	std::vector<StateMap>		mapStateIn;
	std::vector<StateMap>		mapStateOut;

	// when adding networking add BACdev or similar!
public:
	BACnetController();// { subnetOn = 0; devID = -1; }
	BACnetController(unsigned int devid) { SetSubnet(0); controllerAddr.device_id = devid; isTemplate = 0;  treepos = 0; treeState = 0; };
	BACnetController(int devid, unsigned int nsn);
	int AddObject(int objType);  // return instance of the object added, or -1 for error
	int AddObject(int objType, int objInst); // return instance of the object added, or -1 for error
	
	int AddObjectProperty(int objType, int objInst, int propType); // Returns 1 for success 0 for error
	//int AddObjectProperty(int objType, int objInst, int propType, int propArr); // NOTE can't add as index, can only add to array end xxxReturns 1 for success 0 for error
	int SetObjectPropertyValue(int objType, int objInst, int propType, BACvalue* bv);  // Returns 1 for success 0 for error
	int GetObjectPropertyValue(int objType, int objInst, int propType, BACvalue* bv);  // Returns 1 for success 0 for error

	int SetObjectPropertyValue(int objType, int objInst, int propType, int idx, BACvalue* bv);  // Returns 1 for success 0 for error
	int GetObjectPropertyValue(int objType, int objInst, int propType, int idx, BACvalue* bv);  // Returns 1 for success 0 for error

	int SetTemplate(int devTemplate); // MAG 260526 Intent is to add objects to match template for AHU, VAV, or other equipment.
	int IsTemplate() { return isTemplate; }; // MAG 260526 Intent is to add objects to match template for AHU, VAV, or other equipment.

	void ResetObjectIdentiferList();  // Resets the device object property object_list to match the contents of objectList

	HTREEITEM GetTreepos() { return treepos; }
	HTREEITEM GetItemTreepos(int obj, int inst, int prop, int arrIndex);
	void SetTreepos(HTREEITEM rv) { treepos = rv; }
	int FindTreeItem(HTREEITEM findItem, int* obj, int* inst, int* prop, int *arrIndex);  // finds object/prop by HTREEITEM
	int SetItemTreepos(HTREEITEM hti, int obj, int inst, int prop, int arrIndex);
	int SetPropTreepos(HTREEITEM hti, int obj, int inst, int prop, int arrIndex);
	int ResetTreepos();

	int FindFocusTreeItem(HTREEITEM findItem, int* obj, int* inst, int* prop, int* arrIndex);  // finds object/prop by HTREEITEM

	void	SetTreeState(uint tsin) { treeState = tsin; };
	uint	GetTreeState() { return treeState; };

	int GetDeviceObjectID() const { return controllerAddr.device_id; };	// should be same as requesting property (Device Object, Instance) i.e. Object Identifier
	std::vector<BACvalue>	GetObjectListIdentifiers();  // Returns object-identifier pair for all objects in controller

	int SetSubnet(unsigned int nsn);
	unsigned int GetSubnet() const { return controllerAddr.net; };

	std::vector<std::string> GetObjectStrings();			// scans ALL objects in controller
	std::vector<std::string> GetObjectStrings(int objID);	// only scans objectList[objID]
	std::vector<std::string> GetXMLString();				// saves values in XML format

	std::vector<std::string> GetMessageStrings();			// Passes messageStrings to calling network object

	// There is a continual battle between the length of a subroutine name and the clarity of the name.
	int GetControllerAddressInfo(DevAddr *rv);
	int SetControllerAddressInfo(DevAddr* rv);
	int GetControllerRouterAddressInfo(DevAddr* rv);
	int SetControllerRouterAddressInfo(DevAddr* rv);

	void ClearObjectPropertyValue(int objType, int objInst, int propType);

	int ConnectLibrary(CString libName); // Name of sequence library to load
	int ConnectLibrary(std::string libName); // Name of sequence library to load
	std::string GetLibraryName() { return localSeq.GetDLLName(); };

	bool operator<(const BACnetController& other) const {
		return controllerAddr.device_id < other.controllerAddr.device_id;
	}
	bool operator<=(const BACnetController& other) const {
		return controllerAddr.device_id <= other.controllerAddr.device_id;
	}

	bool operator>(const BACnetController& other) const {
		return controllerAddr.device_id > other.controllerAddr.device_id;
	}
	bool operator>=(const BACnetController& other) const {
		return controllerAddr.device_id >= other.controllerAddr.device_id;
	}

	bool operator==(const BACnetController& other) const {
		return controllerAddr.device_id == other.controllerAddr.device_id;
	}

};

