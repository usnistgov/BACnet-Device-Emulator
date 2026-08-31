#include "pch.h"
#include "BACnetNetwork.h"


BACnetNetwork::BACnetNetwork()
{
	// add Host controller
	netType = 0;
	treepos = 0;
	hostNet = 10;
}


// MAG 260609 
// Purpose: Indicate the structure referenced by findItem- could be controller, object, property. 
// Lower level parameters than found structure should be set to -1 (i.e. if it's a controller set obj, inst, prop to -1.
int 
BACnetNetwork::FindTreeItem(HTREEITEM findItem, int* devID, int* obj, int* inst, int* prop, int* arrIndex, int* isFocus)
{
	int rv = 0;

	*devID = *obj = *inst = *prop = *arrIndex = -1;
	if (findItem == treepos) { // it's me!
		return 1;
	}

	for (size_t i = 0; i < controllerList.size(); i++){
		if(findItem == controllerList[i].GetTreepos()) {
			*devID = controllerList[i].GetDeviceObjectID();
			*isFocus = 0;
			return 1;
		}
		if (controllerList[i].FindTreeItem(findItem, obj, inst, prop, arrIndex) == 1) {
			*devID = controllerList[i].GetDeviceObjectID();
			//if (prop >= 0) *isFocus = 1;
			//else 
			*isFocus = 0;
			return 1;
		}
		if (controllerList[i].FindFocusTreeItem(findItem, obj, inst, prop, arrIndex) == 1) {
			*devID = controllerList[i].GetDeviceObjectID();
			*isFocus = 1;
			return 1;
		}
	}

	return 0;
}


int 
BACnetNetwork::SetItemTreepos(HTREEITEM hti, int devID, int obj, int inst, int prop, int arrIndex)
{

	if (devID <=  0) return 0;

	// loop through controllers
	for (size_t i = 0; i < controllerList.size(); i++){
		// check if it's the controller
		if (controllerList[i].GetDeviceObjectID() != devID) continue; // not finding it in this loop
		
		if (obj == -1) {  // set as controller only if we're not looking for an object/property
			controllerList[i].SetTreepos(hti);
			return 1;
		} else {	// check if it's under the controller
			return controllerList[i].SetItemTreepos(hti, obj, inst, prop, arrIndex);
		}
	}
	// didn't find it- nothing to do just exit
	return 0;
}


// Sets Prop treepos- NOTE PROP IS INDEX
// Based on SetItemTreepos
int
BACnetNetwork::SetPropTreepos(HTREEITEM hti, int devID, int obj, int inst, int prop, int arrIndex)
{

	if (devID <= 0) return 0;
	if (obj < 0) return 0;
	if (prop < 0) return 0;
	if (obj >= (int)BACenums::BACObj::ERROR_OBJECT) return 0;
	if (prop >= (int)BACenums::BACProp::en_ERROR_PROP) return 0;

	// loop through controllers
	for (size_t i = 0; i < controllerList.size(); i++) {
		// check if it's the controller
		//if (controllerList[i].GetDeviceObjectID() != devID) continue; // not finding it in this loop

		//if (obj == -1) {  // set as controller only if we're not looking for an object/property
		//	controllerList[i].SetTreepos(hti);
		//	return 1;
		//}
		//else {	// check if it's under the controller
		if(devID == controllerList[i].GetDeviceObjectID()) 
			if (controllerList[i].SetPropTreepos(hti, obj, inst, prop, arrIndex) == 1) 
				return 1;
		//}
	}
	// didn't find it- nothing to do just exit
	return 0;
}


int 
BACnetNetwork::SetSubnetTreepos(HTREEITEM hti, int snet)
{
	for (size_t i = 0; i < subnetList.size(); i++){
		if (snet == subnetList[i].GetSubnet()) {
			subnetList[i].SetTreepos(hti);
			return 1;
		}
	}

	return 0;
}


HTREEITEM 
BACnetNetwork::GetSubnetTreepos(int snet)
{
	for (size_t i = 0; i < subnetList.size(); i++) {
		if (snet == subnetList[i].GetSubnet()) {
			return subnetList[i].GetTreepos();
		}
	}

	return 0;
}


// Gets Object or Prop treepos
HTREEITEM 
BACnetNetwork::GetItemTreepos(int devID, int obj, int inst, int prop, int arrIndex)
{
	HTREEITEM htret = 0;

	if (devID <= 0) return 0;
	//if (obj < 0) return 0;
	//if (prop < 0) return 0;
	if (obj >= (int)BACenums::BACObj::ERROR_OBJECT) return 0;
	if (prop >= (int)BACenums::BACProp::en_ERROR_PROP) return 0;

	// loop through controllers
	for (size_t i = 0; i < controllerList.size(); i++) {
		// check if it's the controller
		if ((obj < 0)&&(controllerList[i].GetDeviceObjectID() == devID)) return controllerList[i].GetTreepos();

		// check objects?
		if (obj <  0) continue;  // no need to check this
		if (devID != controllerList[i].GetDeviceObjectID()) continue;
		htret = controllerList[i].GetItemTreepos(obj, inst, prop, arrIndex);
		if (htret != 0) return htret;
	}

	return 0;
}


void 
BACnetNetwork::ResetDefaultControllerInfo()
{ 
	DevAddr myda;
	int i = 0;

	myda.ip[2] * 1000 + myda.ip[3];  //i.e. turn 129.6.172.100 to 172100
	BACfuncs::GetDefaultAdapterInfo(&myda);
	myda.device_id = i;
	myda.net = 10;  // default local network
	controllerList[0].SetControllerAddressInfo(&myda);
}


int
BACnetNetwork::AddBaseController()
{
	DevAddr myda;
	int i = 0;
	int devID = 0;
	BACvalue bv;
	std::vector<std::string> sv1;

	BACfuncs::GetDefaultAdapterInfo(&myda);
	sv1 = BACfuncs::GetErrorDetails();
	messageStrings.insert(messageStrings.end(), sv1.begin(), sv1.end());

	i = myda.ip[2] * 1000 + myda.ip[3];  //i.e. turn 129.6.172.100 to 172100
	// add top level controller/router/..
	AddController(i, 10);
	myda.device_id = i;
	myda.net = 10;  // default local network
	controllerList[0].SetControllerAddressInfo(&myda);

	memset(&bv, 0, sizeof(BACvalue));
	bv.type = 7; // text
	strcpy_s(bv.value.t, "Host System");
	controllerList[0].SetObjectPropertyValue(8, i, (int)BACenums::BACProp::en_MODEL_NAME, &bv);

	netType = 0;	// default to MS/TP

	// add generic template controllers
	devID = 100000;
	AddController(devID, 0);
	controllerList[1].SetTemplate(1); // set that it is a template
	bv.type = 7;
	strcpy_s(bv.value.t, "Generic AHU");
	controllerList[1].SetObjectPropertyValue(8, devID, (int)BACenums::BACProp::en_MODEL_NAME, &bv);
	// AInputs
	for (i = 1; i <= 12; i++) controllerList[1].AddObject(0, i);
	// AOutputs
	for (i = 1; i <= 8; i++) controllerList[1].AddObject(1, i);
	// AValues
	for (i = 1; i <= 15; i++) controllerList[1].AddObject(2, i);
	// BInputs
	for (i = 1; i <= 5; i++) controllerList[1].AddObject(3, i);
	// BOutputs
	for (i = 1; i <= 5; i++) controllerList[1].AddObject(4, i);
	// BValues
	for (i = 1; i <= 10; i++) controllerList[1].AddObject(5, i);

	devID = 200000;
	AddController(devID,0);
	controllerList[2].SetTemplate(1); // set that it is a template
	bv.type = 7;
	strcpy_s(bv.value.t, "Generic VAV");
	controllerList[2].SetObjectPropertyValue(8, devID, (int)BACenums::BACProp::en_MODEL_NAME, &bv);
	// AInputs
	for (i = 1; i <= 5; i++) controllerList[2].AddObject(0, i);
	// AOutputs
	for (i = 1; i <= 2; i++) controllerList[2].AddObject(1, i);
	// AValues
	for (i = 1; i <= 15; i++) controllerList[2].AddObject(2, i);
	// BInputs
	for (i = 1; i <= 2; i++) controllerList[2].AddObject(3, i);
	// BOutputs
	for (i = 1; i <= 2; i++) controllerList[2].AddObject(4, i);
	// BValues
	for (i = 1; i <= 10; i++) controllerList[2].AddObject(5, i);


	return 1;
}


int
BACnetNetwork::AddSubnet(unsigned int newnet, unsigned int nType)
{
	if(AddSubnet(newnet) == 0)
		return 0;
	
	SetNetType(netType);

	return 1;
}


int	
BACnetNetwork::AddSubnet(unsigned int newnet)
{
	BACnetSubnet mysub;

	if (newnet > 0xFFFE) return 0;

	if (subnetList.size() == 0) {
		subnetList.push_back(newnet);
		return 1;
	}

	// check that it's not already there
	auto it = std::find(subnetList.begin(), subnetList.end(), newnet);
	if (it != subnetList.end()) return 0;  // already exists

	// it's a new subnet, now add and sort

	mysub.SetSubnet(newnet);
	subnetList.push_back(mysub);
	if (subnetList.size() > 1) std::sort(subnetList.begin(), subnetList.end());

	return 1;
}


//int 
//BACnetNetwork::SetTemplate(int devID, int newtemplate) {
//	// check if device id already exists
//	//auto it = std::find(controllerList.begin(), controllerList.end(), devID);
//	//if (it <= controllerList.end()) {
//	//	it->SetTemplate(newtemplate);
//	//	return 1;  // it's already in the list
//	//}
//
//	for (size_t i = 0; i < controllerList.size(); i++){
//		if(devID == controllerList[i].GetDeviceObjectID()) {
//			controllerList[i].SetTemplate(newtemplate);
//			return 1;  // it's already in the list
//		}
//	}
//
//	return 0;
//}


int	
BACnetNetwork::AddController(int devID, unsigned int newnet)
{
	BACnetController mydev;
	DevAddr		conAddr;	// controller address info
	DevAddr		rtAddr;		// used to config ETH mac address if needed
	//char		macAddr[20];
	CString		cs1;

	// check if device id already exists
	auto it = std::find(controllerList.begin(), controllerList.end(), devID);
	if (it != controllerList.end()) return 0;  // it's already in the list

	// NOTE subnet 0 is local subnet
	if(newnet >= 0) AddSubnet(newnet);  // will just return 0 if it already exists
	mydev = BACnetController(devID, newnet);

	//configure network info- guessing at valid values
	memset(&conAddr, 0, sizeof(DevAddr));
	conAddr.device_id = devID;
	//conAddr.ip_or_eth = 0;  // eth
	conAddr.net = newnet;
	//conAddr.ip_port = 0xBAC0; leave as zero, set if needed
	//if (newnet != 10) { // carve out for default local network
	//	conAddr.mac_device_dec = devID - newnet*100;
	//	conAddr.mac_device_len = 1;
	//} else {
	//	conAddr.mac_device_dec = 0;  // UDPIP controller, MAC will be set later
	//	conAddr.mac_device_len = 0;
	//}

	auto itsub = std::find(subnetList.begin(), subnetList.end(), newnet);
	if (itsub != subnetList.end()) {
		itsub->AddDevice(devID);
		if (itsub->GetSubnet() != 10) {  // set up for MS/TP MAC address, length 1
			conAddr.mac_device[0] = itsub->GetHighMAC() + 1;
			itsub->IncrementHighMAC();
			conAddr.mac_device_len = 1;
			sprintf_s(conAddr.mac_device_pr, "0x%02X", conAddr.mac_device[0]);
			conAddr.mac_device_dec = conAddr.mac_device[0];
		} else {	// set up for ETH MAC address, length 6
			// get host MAC
			if (controllerList.size() > 0) {  // note controller 0 is configured elsewhere
				controllerList[0].GetControllerAddressInfo(&rtAddr);
				// increment ETH MAC address by one
				if (rtAddr.mac_device[5] == 0x0F) { // check for high value in this location
					rtAddr.mac_device[4]++;
					rtAddr.mac_device[5] = 0;
					rtAddr.mac_device_pr[6]++;
					rtAddr.mac_device_pr[7] = '0';
				} else {
					rtAddr.mac_device[5]++;
					rtAddr.mac_device_pr[7]++;
				}
			}
		}
	}

	mydev.SetControllerAddressInfo(&conAddr);
	controllerList.push_back(mydev);

	return 1;
}


int
BACnetNetwork::DelController(int devID)
{
	int subid = 0;

	if (devID == 0) return 0;
	for (size_t i = 0; i < controllerList.size(); i++) {
		if (devID == controllerList[i].GetDeviceObjectID()) {
			subid = controllerList[i].GetSubnet();
			controllerList.erase(controllerList.begin() + i);

			// delete from subnet list
			for (size_t j = 0; j < subnetList.size(); j++){
				if (subnetList[j] == subid) subnetList[j].DelDevice(devID);
			} 
			
			return 1;
		}
	}

	return 0;
}


// Resets trepos IN PROPS ONLY, call when updating display in focus window to a different controller
int 
BACnetNetwork::ResetTreepos(int devID)
{
	if (devID == 0) return 0;
	for (size_t i = 0; i < controllerList.size(); i++) {
		if (devID == controllerList[i].GetDeviceObjectID()) {
			controllerList[i].ResetTreepos();
			return 1;
		}
	}

	return 0;
}


int
BACnetNetwork::AddControllerObject(int devID, int objectType, int objectInst=-1)
{
	BACnetController mydev;

	// check if device id already exists
	// NOTE this method is elegant but it doesn't work as the 'other' object is not init correctly
	//auto it = std::find(deviceList.begin(), deviceList.end(), devID);
	//if (it == deviceList.end()) return 0;  // it's not in the list
	//it->AddObject(objectType, objectInst);

	// Not as elegant but it works.
	for (size_t i = 0; i < controllerList.size(); i++){
		if (devID == controllerList[i].GetDeviceObjectID())
			return controllerList[i].AddObject(objectType, objectInst);
	}

	return 0; // controller was not found!
}


// MAG 260422
// Returns 1 for success 0 for error
int 
BACnetNetwork::AddControllerObjectProperty(int devID, int objectType, int objectInst, int propType)
{
	// find if devID is known
	//return it->AddObjectProperty(objectType, objectInst, propType);
	//auto it = std::find(deviceList.begin(), deviceList.end(), devID);
	//if(it == deviceList.end()) return 0;

	for (size_t i = 0; i < controllerList.size(); i++) {
		if (devID == controllerList[i].GetDeviceObjectID()) {
			return controllerList[i].AddObjectProperty(objectType, objectInst, propType);
		}
	}

	return 0;

}


// MAG 260422
// Returns 1 for success 0 for error
int
BACnetNetwork::SetControllerObjectProperty(int devID, int objectType, int objectInst, int propType, BACvalue *bv)
{
	// find if devID is known
	//auto it = std::find(deviceList.begin(), deviceList.end(), devID);
	//if (it == deviceList.end()) return 0;
	//return it->SetObjectPropertyValue(objectType, objectInst, propType, &bv);
	if (bv == NULL) return 0;
	if (objectType < 0) return 0;
	if (objectType >= BAClabels::ObjectLabels.size()) return 0;
	if (objectInst < 0) return 0;
	if (propType < 0) return 0;
	if (propType >= BAClabels::PropertyLabels.size()) return 0;

	for (size_t i = 0; i < controllerList.size(); i++){
		if (devID == controllerList[i].GetDeviceObjectID()) {
			return controllerList[i].SetObjectPropertyValue(objectType, objectInst, propType, bv);
		}
	}

	return 0;
}


// MAG 260422
// Returns 1 for success 0 for error
int
BACnetNetwork::SetControllerObjectProperty(int devID, int objectType, int objectInst, int propType, int idx, BACvalue* bv)
{
	// find if devID is known
	//auto it = std::find(deviceList.begin(), deviceList.end(), devID);
	//if (it == deviceList.end()) return 0;
	//return it->SetObjectPropertyValue(objectType, objectInst, propType, &bv);
	if (bv == NULL) return 0;
	if (objectType < 0) return 0;
	if (objectType >= BAClabels::ObjectLabels.size()) return 0;
	if (objectInst < 0) return 0;
	if (propType < 0) return 0;
	if (propType >= BAClabels::PropertyLabels.size()) return 0;
	if (idx < -1) return 0;

	for (size_t i = 0; i < controllerList.size(); i++) {
		if (devID == controllerList[i].GetDeviceObjectID()) {
			return controllerList[i].SetObjectPropertyValue(objectType, objectInst, propType, idx, bv);
		}
	}

	return 0;
}


// MAG 260430
// Purpose: return address info for host controller (shortcut)
int
BACnetNetwork::GetHostAddressInfo(DevAddr* rv)
{
	if (controllerList.size() == 0) return 0;
	if (rv == NULL) return 0;
	return controllerList[0].GetControllerAddressInfo(rv);
}


int
BACnetNetwork::GetControllerAddressInfo(int devID, DevAddr* rv)
{
	if (rv == NULL) return 0;
	if (devID < 0) return 0;
	
	if (controllerList.size() == 0) return 0;  // this shouldn't ever happen, but have to check
	// find if devID is known
	////auto it = std::find(controllerList.begin(), controllerList.end(), devID);
	//auto it = std::find_if(controllerList.begin(), controllerList.end(), [devID](const BACnetController& c) {
	//	return c.GetDeviceObjectID() == devID;
	//	});
	//if (it == controllerList.end()) return 0; // didn't find it. sad face.
	//return it->GetControllerAddressInfo(rv);
	for (size_t i = 0; i < controllerList.size(); i++){
		if (controllerList[i].GetDeviceObjectID() == devID) {
			return controllerList[i].GetControllerAddressInfo(rv);  // found it!
		}
	}

	return 0;  // didn't find it
}


int
BACnetNetwork::SetControllerAddressInfo(int devID, DevAddr* rv)
{
	if (rv == NULL) return 0;
	if (devID < 0) return 0;

	if (controllerList.size() == 0) return 0;  // this shouldn't ever happen, but have to check
	// find if devID is known
	for (size_t i = 0; i < controllerList.size(); i++) {
		if (controllerList[i].GetDeviceObjectID() == devID) {
			return controllerList[i].SetControllerAddressInfo(rv);  // found it!
		}
	}

	return 0;  // didn't find it
}


// MAG 260422
// Returns 1 for success 0 for error
int
BACnetNetwork::GetControllerObjectProperty(int devID, int objectType, int objectInst, int propType, BACvalue *bv) 
{
	// find if devID is known
	//auto it = std::find(deviceList.begin(), deviceList.end(), devID);
	//if (it == deviceList.end()) return 0;
	//return it->GetObjectPropertyValue(objectType, objectInst, propType, bv);
	if (bv == NULL) return 0;
	if (objectType < 0) return 0;
	if (objectType >= BAClabels::ObjectLabels.size()) return 0;
	if (objectInst < 0) return 0;
	if (propType < 0) return 0;
	if (propType >= BAClabels::PropertyLabels.size()) return 0;

	for (size_t i = 0; i < controllerList.size(); i++) {
		if (devID == controllerList[i].GetDeviceObjectID())
			return controllerList[i].GetObjectPropertyValue(objectType, objectInst,propType,bv);
	}

	return 0;
}


// for when the device id is not set due to being unknown from packet (i.e. most readProps)
// Compares subnet and MAC print from input to controllerList members to find a match, sets Device ID in inDev.
int 
BACnetNetwork::GetDeviceFromNetInfo(DevAddr* inDev)
{
	DevAddr mydeva = {};

	if (strlen(inDev->mac_device_pr) == 0) {
		strcpy_s(inDev->mac_device_pr, "0x");
		for (size_t i = 0; i < inDev->mac_device_len; i++){
			sprintf_s(&inDev->mac_device_pr[(i+1) * 2],4, "%02X", inDev->mac_device[i]);
		}
	}

	for (size_t i = 0; i < controllerList.size(); i++) {
		if (controllerList[i].GetSubnet() == inDev->net) {
			controllerList[i].GetControllerAddressInfo(&mydeva);
			if (memcmp(inDev->mac_device, mydeva.mac_device,inDev->mac_device_len) == 0) {
				inDev->device_id = controllerList[i].GetDeviceObjectID();
				return 1;
			}
		}
	}
	return 0;
}


// MAG 260422
// Returns 1 for success 0 for error
int
BACnetNetwork::GetControllerObjectProperty(int devID, int objectType, int objectInst, int propType, int idx, BACvalue* bv)
{
	// find if devID is known
	//auto it = std::find(deviceList.begin(), deviceList.end(), devID);
	//if (it == deviceList.end()) return 0;
	//return it->GetObjectPropertyValue(objectType, objectInst, propType, bv);
	if (bv == NULL) return 0;
	if (objectType < 0) return 0;
	if (objectType >= BAClabels::ObjectLabels.size()) return 0;
	if (objectInst < 0) return 0;
	if (propType < 0) return 0;
	if (propType >= BAClabels::PropertyLabels.size()) return 0;
	if (idx < -1) return 0;
	if (idx == -1) return GetControllerObjectProperty(devID, objectType, objectInst, propType, bv);  // this will be common

	for (size_t i = 0; i < controllerList.size(); i++) {
		if (devID == controllerList[i].GetDeviceObjectID())
			return controllerList[i].GetObjectPropertyValue(objectType, objectInst, propType, idx, bv);
	}

	return 0;
}


int 
BACnetNetwork::SaveFile(char *opname)
{
	BACvalue	bv = {};
	CString		cs1;
	std::stringstream ss1;
	std::string		st1;
	std::vector<std::string> rv;
	std::vector<std::string> rv2;
	std::ofstream ofs;

	if (opname == NULL) {
		messageStrings.push_back("Error: save name is NULL.");
		return 0;
	}

	ofs = std::ofstream(opname);
	if (!ofs.is_open()) {
		ss1 << "Error opening save file!" << std::endl;
		messageStrings.push_back(ss1.str());
		return 0;
	}

	cs1.Format(L"Saving file: '%S'", opname);
	st1 = (CStringA)cs1;
	messageStrings.push_back(st1);
	rv.push_back("<?xml version=\"1.0\" encoding=\"ISO - 8859 - 1\" ?>");
	rv.push_back("<controllers>");

	for (size_t ic = 0; ic < controllerList.size(); ic++){
		rv2 = controllerList[ic].GetXMLString();
		rv.insert(rv.end(), rv2.begin(), rv2.end());
		rv2.clear();
	}
	rv.push_back("</controllers>");

	for (size_t opi = 0; opi < rv.size(); opi++) {
		ofs << rv[opi] << std::endl;
	}
	
	ofs.close();
	messageStrings.push_back("Output file has been saved.");

	return 1;
}


// MAG 260609 Copies content of template contrlller into new conroller
int
BACnetNetwork::SetControllerTemplate(int devID, int devTemplate)
{
	int srcindx = -1;
	int dstindx = -1;
	int j = 0;
	int prevsn = 0;  // previous subnet
	BACvalue dobjID = {};
	DevAddr myda = {};
	DevAddr mydr = {};


	for (size_t i = 0; i < controllerList.size(); i++){
		j = controllerList[i].GetDeviceObjectID();
		if (devID == j) dstindx = i;
		if (devTemplate == j) srcindx = i;
	}
	if (dstindx == srcindx) return 0;
	if (srcindx == -1) return 0;
	if (dstindx == -1) return 0;

	j = controllerList[dstindx].GetDeviceObjectID();
	prevsn = controllerList[dstindx].GetSubnet();
	controllerList[dstindx].GetObjectPropertyValue(8, j, (int)BACenums::BACProp::en_OBJECT_IDENTIFIER, &dobjID);  // save object identifier data
	controllerList[dstindx].GetControllerAddressInfo(&myda);
	controllerList[dstindx].GetControllerRouterAddressInfo(&mydr);

	controllerList[dstindx] = controllerList[srcindx];
	
	controllerList[dstindx].SetObjectPropertyValue(8, controllerList[srcindx].GetDeviceObjectID(), (int)BACenums::BACProp::en_OBJECT_IDENTIFIER, &dobjID);
	controllerList[dstindx].SetControllerAddressInfo(&myda);
	controllerList[dstindx].SetControllerRouterAddressInfo(&mydr);
	controllerList[dstindx].SetSubnet(prevsn);
	controllerList[dstindx].SetTemplate(0);
	controllerList[dstindx].SetTreepos(0);
	
	//for (size_t i = 0; i < controllerList.size(); i++) {
	//	if (devID == controllerList[i].GetDeviceObjectID())
	//		return controllerList[i].SetTemplate(devTemplate);
	//}

	return 0;
}


std::vector<std::string> 
BACnetNetwork::GetTemplateNames() 
{
	std::vector<std::string> rv;
	std::string st1;
	std::stringstream ss1;
	BACvalue bv = {};

	for (size_t i = 0; i < controllerList.size(); i++){
		if (controllerList[i].IsTemplate()) {
			controllerList[i].GetObjectPropertyValue(8, controllerList[i].GetDeviceObjectID(), (int)BACenums::BACProp::en_MODEL_NAME, &bv);
			ss1 << controllerList[i].GetDeviceObjectID() << ":" << bv.value.t;
			st1 = ss1.str();
			rv.push_back(st1);
			ss1.str("");
		}
	}

	return rv;
}


std::vector<std::string> 
BACnetNetwork::GetMessageStrings()
{
	std::vector<std::string> rv;

	// get strings from controllers
	for (size_t i = 0; i < controllerList.size(); i++){
		rv = controllerList[i].GetMessageStrings();
		if (rv.size() > 0)
			messageStrings.insert(messageStrings.end(), rv.begin(), rv.end());
	}

	rv = messageStrings;
	messageStrings.clear();

	return rv;
}


std::vector<std::string> 
BACnetNetwork::GetControllerStrings(int devID)
{
	std::vector<std::string> rv;

	//auto it = std::find(deviceList.begin(), deviceList.end(), devID);
	//if (it == deviceList.end()) return rv;

	for (size_t i = 0; i < controllerList.size(); i++){
		if (devID == controllerList[i].GetDeviceObjectID())
			return controllerList[i].GetObjectStrings();
	}

	return rv;
}


std::vector<int> 
BACnetNetwork::GetSubnets()
{
	std::vector<int> rv;

	for (size_t i = 0; i < subnetList.size(); i++){
		if(subnetList[i].GetReal() == 0)  // only virtual subnets can have controllers added
			rv.push_back(subnetList[i].GetSubnet());
	}

	return rv;
}


std::vector<int>
BACnetNetwork::GetSubnetDevices(int sn)
{
	std::vector<int> rv;

	for (size_t i = 0; i < subnetList.size(); i++) {
		if (sn == subnetList[i].GetSubnet()) {
			rv = subnetList[i].GetDeviceList();
			return rv;
		}
	}

	return rv;
}


std::vector<int> 
BACnetNetwork::GetTemplateDevices()
{
	std::vector<int> rv;

	for (size_t i = 0; i < controllerList.size(); i++){
		if (controllerList[i].IsTemplate()) {
			rv.push_back(controllerList[i].GetDeviceObjectID());
		}
	}

	return rv;
}


// Sets the value of the isTemplate parameter
void
BACnetNetwork::SetTemplate(int devID, int tpl)
{
	for (size_t i = 0; i < controllerList.size(); i++) {
		if (controllerList[i].GetDeviceObjectID() == devID) {
			controllerList[i].SetTemplate(tpl);  // note return value not checked.
			return ;
		}
	}
}


// Returns the value of the isTemplate parameter
int
BACnetNetwork::IsTemplate(int devID)
{
	for (size_t i = 0; i < controllerList.size(); i++) {
		if (controllerList[i].GetDeviceObjectID() == devID) {
			return controllerList[i].IsTemplate();  // note return value not checked.
		}
	}

	return 0;
}


// Set parameter ignoreTemplate to 1 to not report template and host system
std::vector<int>
BACnetNetwork::GetControllerDeviceIDs(int ignoreTemplate)
{
	std::vector<int> rv;

	for (size_t i = 0; i < controllerList.size(); i++) {
		if (ignoreTemplate) {
			if (controllerList[i].IsTemplate() == 1) continue;
			if (controllerList[i].GetSubnet() == 10) continue;
		}
		rv.push_back(controllerList[i].GetDeviceObjectID());
	}

	return rv;
}


std::vector<BACvalue>	
BACnetNetwork::GetControllerObjectList(int devID)
{
	std::vector<BACvalue> rv;
	//BACvalue rv1;
	
	//rv1.type = 12;
	//auto it = std::find(controllerList.begin(), controllerList.end(), devID);
	//if (it != controllerList.end()) {
	//	rv = it->GetObjectListIdentifiers();
	//}

	for (size_t i = 0; i < controllerList.size(); i++){
		if (controllerList[i].GetDeviceObjectID() == devID) {
			rv = controllerList[i].GetObjectListIdentifiers();
			return rv;
		}
	}
	
	return rv;
}


std::vector<std::string>
BACnetNetwork::GetControllerObjectParameterList(int devID, int objID)
{
	std::vector<std::string> rv;
	//BACvalue rv1;

	//rv1.type = 12;
	//auto it = std::find(controllerList.begin(), controllerList.end(), devID);
	//if (it != controllerList.end()) {
	//	rv = it->GetObjectListIdentifiers();
	//}

	for (size_t i = 0; i < controllerList.size(); i++) {
		if (controllerList[i].GetDeviceObjectID() == devID) {
			rv = controllerList[i].GetObjectStrings(objID);  // found the correct controller
			return rv;
		}
	}

	return rv;
}


// MAG 260504 Checks for BACnet message from network, handles/routes them
// based on bds3::check_for_BACnet()
// returns: Number of BACnet messages, or -1 on error
int 
BACnetNetwork::CheckForBACnetMessages()
{
	int i = 0;
	int counter = 0;//ret, 
	int packetcount = 0;
	//unsigned int ui, uk;
	wchar_t junk[500] = {};
	//int k = 0, LLC_len;//id;	//unsigned char *cp;	//char recvmac[20], *cp2;
	//octet *oct;
	//int hasdnet, hassnet, hasmtype, unitdata, priority;	//int res, apdu_len, snet;	//struct pcap_pkthdr *header;
	//char target[14], sender[14], //, host[14];	//char bacstring[50];//*bnm, recvmessg[200];
	//char notebook[14], laptop[14];//, router[14];
	char update_data = 0;
	char update_info = 0;  // will we need to update data or info displays when done reading packets?
	//device *senddev;	//float status=0;
	CStringA cs1;

	//strcpy_s(notebook,"00E0C90041F0");
	//strcpy_s(laptop,"00065BE09E5C");
	//if (dplist.list.size() != 0) {
	//	swprintf(junk, 100, L"dplist count too high");
	//}

	//datatransfer mydt[250];
	try {
		packetcount = BACfuncs::fnBACdllGetBAC(readdt);
	}
	catch (const std::exception& e) {
		messageStrings.push_back("ERROR: Catch exception in while reading BACnet packets.");
		messageStrings.push_back(e.what());
		return 0;
	}
	catch (...) {
		AfxMessageBox(L"Error caught while reading BACnet packets.");
		return 0;
	}
	//if (num_twa != 0) {
	//	swprintf(junk, 100, L"TWA ERROR!");
	//}

	//#ifdef _DEBUG
	//if ((packetcount > 0) && (settings.quietBACnet == 0)) {
	//	swprintf(junk, 100, L"RECV PACKET(s) count %d", packetcount);
	//	statusString(junk);
	//}
	//#endif
	if (packetcount < 1) return(0);
	if (packetcount > 250) {
		//statusString("ERROR- too many BACnet packets returned- continuing...");
		packetcount = 250;
	}
	counter = packetcount;
	
	try {
		for (i = 0;i < packetcount;i++) {
			//if (num_twa != 0) {
			//	swprintf(junk, 100, L"TWA ERROR!");
			//}
			if (readdt[i].source.devAddr.mac_device_len == 0) continue; // MAG 13SEP05  getting empty packets from winpcap
			//if (settings.quietBACnet == 0) { // if not checked
				//swprintf(junk, 100, L" PACKET %d is type %d", i, mydt[i].choice);
			//cs1.Format(" RECV PACKET %d type %d", i, readdt[i].choice);
			//messageStrings.push_back(cs1.GetBuffer());
			//}
			//if ((mydt[i].source.devRouter.mac_device_len > 0) && (mydt[i].source.devRouter.ip_or_eth == 1)) {
			//	// i.e. BACnet/IP router, still ignored when not using UDP
			//	if (settings.useUDP == 0) continue;
			//}
			//if (mydt[i].source.devAddr.ip_or_eth == 1) {
			//	if (settings.useUDP == 0) continue;
			//	swprintf(junk, 100, L"found BACnet/ip packet (breakpoint)");
			//}
			//else {
			//	if (settings.useETH == 0) continue;
			//}

			// MAG 260504 TODO: See if anything needs to be done with minimally handled cases below...
			switch (readdt[i].choice) {
				case 0:  // confirmed-request
					eval_ConfREQ(i);
					break;
				case 1:  // unconfirmed-request
					eval_UnconfREQ(i);
					break;
				case 2:  // simpleACK
					break;
				case 3:  // complexACK
					eval_ComplexACK(i);
					update_data = 1;
					break;
				case 4:  // segmentACK
					//if (settings.quietBACnet == 0) statusString("RECV: BACnet-SegmentACK");
					break;
				case 5:  // error
					//if (settings.quietBACnet == 0) statusString("RECV: BACnet-ERROR");
					//swprintf(junk, 100, L"choice %d, class %d, code %d", mydt[i].packet.errorPacket.errorChoice, mydt[i].packet.errorPacket.errorClass, mydt[i].packet.errorPacket.errorCode);
					//statusString(junk);
					//eval_Error(i);
					break;
				case 6:  // reject
					//if (settings.quietBACnet == 0) statusString("RECV: BACnet-Reject");
					break;
				case 7:  // abort
					break;
				//case 8: break; there is no 8
				default: break;
			}
			memset(&readdt[i], 0, sizeof(datatransfer));

		}
	}
	catch (const std::exception& e) {
		// Log the error message
		CStringA err;
		messageStrings.push_back("ERROR: Caught exception in CheckForBACnetMessages!");
		//err.Format("ERROR: %S", e.what());
		messageStrings.push_back(e.what());
	}
	catch (...) {
		AfxMessageBox(L"Caught error in CheckForBACnetMessages!");
		return 0;
	}


	// MAG update display stuff here
	//if (update_data) {
	//	m_show_this.GetWindowText(junk, 5);
	//	i = _ttoi(junk);
	//	UpdateInfoLabels(i);
	//	UpdateDataspinner();
	//}

	//if (num_twa != 0) {
	//	swprintf(junk, 100, L"TWA ERROR!");
	//}

	return(counter);
}  // end BACnetNetwork::CheckForBACnetMessages


// MAG 260504 Checks for BACnet message from network, handles/routes them
// based on bds3::check_for_BACnet()
// returns: Number of BACnet messages, or -1 on error
int
BACnetNetwork::SendBACnetMessages()
{
	int cID = 0;
	int cObject = 0;
	int cObjInst = 0;
	int cProp = 0;
	int cPIndex = 0;
	CStringA csa;
	std::string ss1;
	DevAddr	mydeva = {};

	if (senddt.size() == 0) return 1;

	for (size_t index = 0; index < senddt.size(); index++){
		int cID = senddt[index].dest.devAddr.device_id;
		int cObject = senddt[index].packet.confREQ.service.readProp.objid.object;
		int cObjInst = senddt[index].packet.confREQ.service.readProp.objid.id;
		int cProp = senddt[index].packet.confREQ.service.readProp.prop;
		int cPIndex = senddt[index].packet.confREQ.service.readProp.index;
		if (cObject == 8) cID = cObjInst;

		if (cID <= 0) {
			GetDeviceFromNetInfo(&senddt[index].dest.devAddr);
			GetDeviceFromNetInfo(&senddt[index].source.devAddr);
			//// TODO find cID from subnet/mac
			//for (size_t i = 0; i < controllerList.size(); i++) {
			//	if (controllerList[i].GetSubnet() == senddt[index].dest.devAddr.net) {
			//		controllerList[i].GetControllerAddressInfo(&mydeva);
			//		if (strcmp(senddt[index].dest.devAddr.mac_device_pr, mydeva.mac_device_pr) == 0) {
			//			cID = controllerList[i].GetDeviceObjectID();
			//			senddt[index].dest.devAddr.device_id = cID;
			//		}
			//	}
			//}
		}
		//ss1 = BACfuncs::BACvalueToString(&senddt[index].packet.compACK.service.readProp.value);
 		//csa.Format("SEND addr: %d:%s COMPACK::READPROP obj: %d inst: %d prop: %d value: %S",
		//	senddt[index].dest.devAddr.net, 
		//	senddt[index].dest.devAddr.mac_device_pr, 
		//	cObject, cObjInst, cProp,ss1.c_str());
		//messageStrings.push_back(csa.GetBuffer());
	}

	try {
		BACfuncs::SendBACnetUDPIP(senddt.data(), senddt.size());
		senddt.clear();
		return 0;
	}
	catch (const std::exception& e) {
		// Log the error message
		CStringA err;
		messageStrings.push_back("ERROR: Caught exception in SendBACnetMessages!");
		//err.Format("ERROR: %s", e.what());
		messageStrings.push_back(e.what());
		return 0;
	}
	catch (...) {
		messageStrings.push_back("ERROR: Caught exception in SendBACnetMessages!");
		return 0;
	}

	return 1;
} // end BACnetNetwork::SendBACnetMessages


// Finds controller devID and passes library name to it 
int 
BACnetNetwork::SetLibrary(int devID, std::string hLib)
{
	if (devID < 0) return 0;
	if (hLib.size() < 5) return 0;  // min size with ".dll" extension, should someone use "a.dll" or similar

	for (size_t i = 0; i < controllerList.size(); i++){
		if (controllerList[i].GetDeviceObjectID() == devID) {
			 return controllerList[i].ConnectLibrary(hLib);
		}
	}

	return 0; // didn't find the controller!
}

void 
BACnetNetwork::eval_ConfREQ(int index)
{
	datatransfer* dtran = NULL;//, dtr24;
	Packet* mypack = NULL;
	DevAddr localAddr = {};
	BACvalue lbv = {};
	int fstat = 0;
	int cID = 0;		// controller device id
	int cObject = 0;	// object requested
	int cObjInst = 0;	// instance of said object requested
	int cProp = 0;		// prop of said object
	int cPIndex = 0;	// optinal index of property
	int spc = 0;		// send packet count for multi prop read/write
	CStringA csa;		// for adding to message strings

	dtran = &readdt[index];
	mypack = &readdt[index].packet;
	
	//if (strlen(readdt[index].source.devAddr.mac_device_pr) == 0) {
	//	mybd.hextostring(readdt[index].source.devAddr.mac_device, readdt[index].source.devAddr.mac_device_pr, readdt[index].source.devAddr.mac_device_len);
	//}
	//if (strlen(readdt[index].dest.devAddr.mac_device_pr) == 0) {
	//	mybd.hextostring(readdt[index].dest.devAddr.mac_device, readdt[index].dest.devAddr.mac_device_pr, readdt[index].dest.devAddr.mac_device_len);
	//}
	controllerList[0].GetControllerAddressInfo(&localAddr);

	// Check that ROUTER info is valid, then compare dest ROUTER address vs local machine 
	if ((readdt[index].dest.devRouter.ip_or_eth == 1)&&(strcmp(readdt[index].dest.devRouter.mac_device_pr, localAddr.mac_device_pr) != 0)) {
		return;	// it's not to me
	}
	cID = readdt[index].dest.devAddr.device_id;
	if (cID <= 0) {
		if (GetDeviceFromNetInfo(&readdt[index].dest.devAddr) == 1) {
			cID = readdt[index].dest.devAddr.device_id;
		} else {
			csa.Format("ERR could not determine device id.");
		}
	}

	// Selection of BACnetConfirmedServiceChoice ::= ENUMERATED
	try {
		switch (dtran->packet.confREQ.choice) {
		case 12: // readProperty- looking for readprop/device object/object list/(index)

			//cID = readdt[index].dest.devAddr.device_id;
			cObject = readdt[index].packet.confREQ.service.readProp.objid.object;
			cObjInst = readdt[index].packet.confREQ.service.readProp.objid.id;
			cProp = readdt[index].packet.confREQ.service.readProp.prop;
			cPIndex = readdt[index].packet.confREQ.service.readProp.index;
			if (cObject == 8) cID = cObjInst;
			csa.Format("RECV addr: %d:%s CONFREQ::READPROP obj: %d inst: %d prop: %d",dtran->source.devAddr.net, dtran->source.devAddr.mac_device_pr, cObject, cObjInst, cProp);
			messageStrings.push_back(csa.GetBuffer());
			fstat = GetControllerObjectProperty(cID, cObject, cObjInst, cProp, cPIndex, &lbv);
			if (fstat == 1) {  // craft return packet
				toSend.choice = 3;  // complex ACK
				toSend.packet.compACK.choice = 12; // read property
				toSend.packet.compACK.service.readProp.objid.object = cObject;
				toSend.packet.compACK.service.readProp.objid.id = cObjInst;
				toSend.packet.compACK.service.readProp.index = cPIndex;
				toSend.packet.compACK.service.readProp.prop = cProp;
				memcpy(&toSend.packet.compACK.service.readProp.value, &lbv, sizeof(BACvalue));
				// set network parameters
				toSend.dest = dtran->source;
				toSend.source = dtran->dest;
				toSend.priority = 16;
				toSend.length = 0;
				toSend.invid = 0;
				//toSend.packet.compACK.
				
				senddt.push_back(toSend);
			} else {
				// MAG 260504 TODO craft error packet
			}
			break;
		case 14: // readPropertyMultiple NOTE based on readprop, but in a loop
			//cID = readdt[index].dest.devAddr.device_id;
			//if (cID <= 0) {
			//	if (GetDeviceFromNetInfo(&readdt[index].dest.devAddr) == 1) {
			//		cID = readdt[index].dest.devAddr.device_id;
			//	} else {
			//		break;
			//	}
			//}
			for (size_t rpmi = 0; rpmi < readdt[index].packet.confREQ.service.readPropM.count; rpmi++) {
				cObject = readdt[index].packet.confREQ.service.readPropM.request[rpmi].objid.object;
				cObjInst = readdt[index].packet.confREQ.service.readPropM.request[rpmi].objid.id;
				for (size_t rppr = 0; rppr < readdt[index].packet.confREQ.service.readPropM.request[rpmi].numprop; rppr++){
					cProp = readdt[index].packet.confREQ.service.readPropM.request[rpmi].props[rppr].propertyIdentifier;
					cPIndex = readdt[index].packet.confREQ.service.readPropM.request[rpmi].props[rppr].propertyArrayIndex;
					if (cObject == 8) cID = cObjInst;
					csa.Format("RECV addr: %d:%s CONFREQ::READPROPM obj: %d inst: %d prop: %d", dtran->source.devAddr.net, dtran->source.devAddr.mac_device_pr, cObject, cObjInst, cProp);
					messageStrings.push_back(csa.GetBuffer());
					fstat = GetControllerObjectProperty(cID, cObject, cObjInst, cProp, cPIndex, &lbv);
					if (fstat == 1) {  // craft return packet
						toSend.choice = 3;  // complex ACK
						toSend.packet.compACK.choice = 14; // read property multiple
						toSend.packet.compACK.service.readPropM.values[spc].objid.object = cObject;
						toSend.packet.compACK.service.readPropM.values[spc].objid.id = cObjInst;
						toSend.packet.compACK.service.readPropM.values[spc].props[0].propertyArrayIndex = cPIndex;
						toSend.packet.compACK.service.readPropM.values[spc].props[0].propertyIdentifier = cProp;
						toSend.packet.compACK.service.readPropM.values[spc].numprop = 1;
						memcpy(&toSend.packet.compACK.service.readPropM.values[spc].props->readResult.value, &lbv, sizeof(BACvalue));
						toSend.packet.compACK.service.readPropM.count++;
						spc++;
					} else {
						csa.Format("ERR: did not find property.");
						// MAG 260504 TODO craft error packet
					}
				}	// end rppr
			}		// end rpmi
			// set network parameters
			toSend.dest = dtran->source;
			toSend.source = dtran->dest;
			toSend.priority = 16;
			toSend.length = 0;
			toSend.invid = 0;
			//toSend.packet.compACK.

			senddt.push_back(toSend);
			memset(&toSend, 0, sizeof(datatransfer));

			break; // end case 14 read property multiple
		case 15: // write property
			//cID = readdt[index].dest.devAddr.device_id;
			cObject = readdt[index].packet.confREQ.service.writeProp.objid.object;
			cObjInst = readdt[index].packet.confREQ.service.writeProp.objid.id;
			cProp = readdt[index].packet.confREQ.service.writeProp.prop;
			cPIndex = readdt[index].packet.confREQ.service.writeProp.index;
			//readdt[index].packet.confREQ.service.writeProp.value
			if (cObject == 8) cID = cObjInst;
			csa.Format("RECV addr: %d:%s CONFREQ::WRITEPROP obj: %d inst: %d prop: %d", dtran->source.devAddr.net, dtran->source.devAddr.mac_device_pr, cObject, cObjInst, cProp);
			messageStrings.push_back(csa.GetBuffer());
			if (cPIndex == -1) {
				fstat = SetControllerObjectProperty(cID, cObject, cObjInst, cProp, &readdt[index].packet.confREQ.service.writeProp.value);
			} else {
				fstat = SetControllerObjectProperty(cID, cObject, cObjInst, cProp, cPIndex, &readdt[index].packet.confREQ.service.writeProp.value);
			}
			if (fstat == 1) {  // craft return packet
				toSend.choice = 2;  // simple ACK
				toSend.packet.simpACK.choice = 15;
				toSend.packet.simpACK.invid = readdt[index].invid;
			} else {
				// MAG 260504 TODO craft error packet, work on getting accurate error messages
				toSend.choice = 5;  // ERROR!
				toSend.packet.errorPacket.error4.writeProperty.error_class = 5;
				toSend.packet.errorPacket.error4.writeProperty.error_code = 0x28; // write-access-denied
				toSend.packet.errorPacket.errorChoice = 11; // write property
				toSend.packet.errorPacket.errorClass = 5; // property
				toSend.packet.simpACK.invid = readdt[index].invid;
			}
			// set network parameters
			toSend.dest = dtran->source;
			toSend.source = dtran->dest;
			toSend.priority = 16;
			toSend.length = 0;
			toSend.invid = 0;
			senddt.push_back(toSend);

			// indicate to check if display needs to be updated
			csa.Format("##UPD:%d", cID);  // update
			messageStrings.push_back(csa.GetBuffer());

			break;
		case 16: // write property multiple
		default: return;
		}  // end switch
	} // end try
	catch (const std::exception& e) {
		messageStrings.push_back("ERROR: Catch exception in eval_ConfREQ.");
		messageStrings.push_back(e.what());
		return;
	}
	catch (...) {
		//m_status.AddString(L"Caught error in eval_ConfREQ()");
		return;
	}

	return;
}  // end BACnetNetwork::eval_ConfREQ


void 
BACnetNetwork::eval_UnconfREQ(int index)
{
	datatransfer* dtran = NULL;//, dtr24;
	Packet* mypack = NULL;
	DevAddr localAddr = {};
	DevAddr rtrAddr = {};
	BACvalue lbv = {};
	int fstat = 0;
	int cID = 0;		// controller device id
	int cObject = 0;	// object requested
	int cObjInst = 0;	// instance of said object requested
	int cProp = 0;		// prop of said object
	int cPIndex = 0;	// optinal index of property
	CStringA csa;		// for adding to message strings

	int wiLow = -1;
	int wiHigh = -1;
	int vendor = 0;
	int iamCount = 0;
	//char testMAC[20] = {};
	size_t i = 0;
	std::vector<int> snl; // sub net list

	dtran = &readdt[index];
	mypack = &readdt[index].packet;
	controllerList[0].GetControllerAddressInfo(&localAddr);

	// Check that ROUTER info is valid, then compare dest ROUTER address vs local machine 
	if ((readdt[index].dest.devRouter.ip_or_eth == 1) && (strcmp(readdt[index].dest.devRouter.mac_device_pr, localAddr.mac_device_pr) != 0)) {

		//strcpy_s(testMAC, 8, readdt[index].dest.devRouter.mac_device_pr);  //
		csa = readdt[index].dest.devRouter.mac_device_pr;
		if (csa.Find("FFFFFF") == -1) {
			return;
		}
		////csa = csa.Left(8);
		////if (strncmp(testMAC, "0xFFFFFF",8) != 0){  // allow broadcast
		//if(csa.Compare("0xFFFFFF") != 0){
		//	return;	// it's not to me
		//}
		////testMAC[6] = 0;
		//csa = csa.Left(8);
		////if (strncmp(testMAC, "FFFFFF", 6) != 0) {  // allow broadcast without leading 0x in print version
		//if(csa.Compare("FFFFFF") != 0){
		//	return;	// it's not to me
		//}
	}
	// Selection of BACnetUnconfirmedServiceChoice ::= ENUMERATED
	try {
		switch (dtran->packet.uconfREQ.choice) {
			case 0: //i - Am
				// ok that's nice not much to do here
				break;
			case 1: //i - Have
				break;
			case 2: //unconfirmedCOVNotification
				break;
			case 3: //unconfirmedEventNotification
				break;
			case 4: //unconfirmedPrivateTransfer
				break;
			case 5: //unconfirmedTextMessage
				break;
			case 6: //timeSynchronization
				// Maybe add controller time if needed?
				break;
			case 7: //who - Has
				break;
			case 8: //who - Is
				// respond to whois
				wiLow = dtran->packet.uconfREQ.service.whoIs.low;
				wiHigh = dtran->packet.uconfREQ.service.whoIs.high;
				if (wiHigh < wiLow) {
					messageStrings.push_back("RECV Who-Is request with malformed range. Remove range and respond.");
					wiLow = -1;  // default values
					wiHigh = -1;
					//break;
				}
				//if ((wiLow == 0) && (wiHigh == 0)) {
				//	wiLow = wiHigh = -1;
				//}
				controllerList[0].GetControllerAddressInfo(&rtrAddr);
				for (i = 1; i < controllerList.size(); i++) {  // send an i-am for each controller unless range is specified
					// check range
					if (wiLow > 0) { // if there is a range...
						if ((controllerList[i].GetDeviceObjectID() < wiLow) || (controllerList[i].GetDeviceObjectID() > wiHigh)) {
							//csa.Format("RECV Who-Is request out of range %d - %d", wiLow, wiHigh);
							//messageStrings.push_back(csa.GetBuffer());
							//break;  // and this controller is out of the requested range...
							continue;
						}
					}
					
					// vendor
					if (controllerList[i].GetObjectPropertyValue(8, 0, (int)BACenums::BACProp::en_VENDOR_IDENTIFIER, &lbv) == 1) {
						//cs1.Format(L"DevId: %d  Model Name: %S", devl[j], bvl.value.t);
						vendor = lbv.value.i;
					} else {
						//cs1.Format(L"DevId: %d  Model Name: NA", devl[j]);
						vendor = 1;
					}
					if (controllerList[i].GetControllerAddressInfo(&localAddr) == 1) {
						BACfuncs::SendIAMDev(&localAddr, &rtrAddr, 1024, vendor);
						iamCount++;
					}
				}
				if (wiLow >= 0) {
					csa.Format("RECV Who-Is request.");
				} else {
					csa.Format("RECV Who-Is request range %d - %d", wiLow, wiHigh);
				}
				messageStrings.push_back(csa.GetBuffer());
				csa.Format("Sent %d I-Am responses.", iamCount);
				messageStrings.push_back(csa.GetBuffer());
				break;
			case 9: //utcTimeSynchronization
				break;
			case 10: //writeGroup
				break;
			default: return;
		}
	}
	catch (const std::exception& e) {
		messageStrings.push_back("ERROR: Catch exception in eval_UnconfREQ.");
		messageStrings.push_back(e.what());
		return;
	}
	catch (...) {
		//m_status.AddString(L"Caught error in eval_ConfREQ()");
		return;
	}
	return;
}  // end BACnetNetwork::eval_UnconfREQ


void BACnetNetwork::eval_ComplexACK(int index) {
	datatransfer* dtran = NULL;//, dtr24;
	Packet* mypack = NULL;
	DevAddr localAddr = {};
	BACvalue lbv = {};
	int fstat = 0;
	int cID = 0;		// controller device id
	int cObject = 0;	// object requested
	int cObjInst = 0;	// instance of said object requested
	int cProp = 0;		// prop of said object
	int cPIndex = 0;	// optinal index of property
	CStringA csa;		// for adding to message strings

	dtran = &readdt[index];
	mypack = &readdt[index].packet;
	controllerList[0].GetControllerAddressInfo(&localAddr);

	// Check that ROUTER info is valid, then compare dest ROUTER address vs local machine 
	if ((readdt[index].dest.devRouter.ip_or_eth == 1) && (strcmp(readdt[index].dest.devRouter.mac_device_pr, localAddr.mac_device_pr) != 0)) {
		return;	// it's not to me
	}
	// Selection of BACnetConfirmedServiceChoice ::= ENUMERATED
	try {
		switch (dtran->packet.compACK.choice) {
		}
	}
	catch (const std::exception& e) {
		messageStrings.push_back("ERROR: Catch exception in eval_ConfREQ.");
		messageStrings.push_back(e.what());
		return;
	}
	catch (...) {
		messageStrings.push_back("ERROR: Catch exception in eval_ConfREQ.");
		//m_status.AddString(L"Caught error in eval_ConfREQ()");
		return;
	}

}

// MAG 260608 reads in template file. Uses standard function to read in controllres,
// but copies templates to template array.
//int 
//BACnetNetwork::ReadTemplateFile()
//{
//	int  clsize = controllerList.size();
//
//	// read in template file
//	th
//
//}
