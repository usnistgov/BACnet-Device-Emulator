#include "pch.h"
#include "BACnetSubnet.h"

BACnetSubnet::BACnetSubnet()
{
	subnet_id = 0;
	highMAC = 0;
	treeState = 0;
	treepos = 0;
	isReal = 0;
}

BACnetSubnet::BACnetSubnet(unsigned int subid)
{
	if (subid > 0xFFFE) {
		subnet_id = 1;
		return;
	}
	subnet_id = subid;
	highMAC = 0;
	treeState = 0;
	treepos = 0;
	isReal = 0;
}


int 
BACnetSubnet::SetSubnet(unsigned int subid) 
{
	if (subid > 0xFFFE) {
		subnet_id = 1;
		return 0;
	}
	subnet_id = subid;

	return 1;
}


int 
BACnetSubnet::GetSubnet()
{
	return subnet_id;
}


// Returns 1 if the device is found, 0 if the device requested is out of range or not found
// Acts like bool, does not return index
int 
BACnetSubnet::HasDevice(int devid)
{
	if (devid < 0) return 0;

	auto it = std::find(device_id_list.begin(), device_id_list.end(), devid);
	if (it != device_id_list.end()) return 1;
	//for (size_t i = 0; i < device_id_list.size(); i++)
	//{
	//	if (device_id_list[i] == devid) return 1;
	//}
	return 0;
}


//Returns 1 if device id is inserted, 0 if fails- out of range or is already in list
int
BACnetSubnet::AddDevice(int devid)
{
	if (devid < 0) return 0;

	// add to end of list...
	device_id_list.push_back(devid);
	// sort list
	std::sort(device_id_list.begin(), device_id_list.end());

	return 0;
}


// Purpose: deletes device from subnet indicated by devid
// Returns: 1 if deleted
//			0 if it could not be deleted: devid out of range or devid not in list
int 
BACnetSubnet::DelDevice(int devid){
	if (devid < 0) return 0;
	//if (devid >= device_id_list.size()) return 0; it's not an index

	auto it = std::find(device_id_list.begin(), device_id_list.end(), devid);
	if (it != device_id_list.end()) {
		device_id_list.erase(it);
		return 1;
	}

	return 0;  // not found or deleted
}

std::vector<int> 
BACnetSubnet::GetDeviceList()
{
	return device_id_list;
}