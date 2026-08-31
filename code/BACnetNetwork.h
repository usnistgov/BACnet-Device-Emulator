#pragma once

#include <algorithm> // for std::sort
#include "BACnetSubnet.h"
#include <BACnet_api.h>

// MAG 260421
// This is "The Network"
// Purpose: To hold data on all subnets and devices on the network. Coordinates info about devices on subnets.
// NOTE: BACnet requests will be handled by NetworkSupervisor class (maybe rename?) this just stores and reports.
class BACnetNetwork
{
private:
	std::vector<BACnetSubnet>		subnetList;
	std::vector<BACnetController>	controllerList;

	std::vector<std::string>		messageStrings; // used to save messages to be retrieved by calling function

	datatransfer					readdt[250];		// structs to hold incoming messages
	std::vector<datatransfer>		senddt;			// structs to hold outgoing messages
	datatransfer					toSend;			// used in subroutines to add to senddt
	
	std::vector<BACnetController>	controllerTemplateList;	// default implementation of each controller template with properties

	unsigned int					netType;		// 0=MS/TP, 1=UDP/IP
	unsigned int					hostNet;		// net number for local real network, default to 10 TODO add method for user to modify

	HTREEITEM						treepos;		// identifer for CTreeCtrl

	// MAG these work with mydt
	void eval_ConfREQ(int i);
	void eval_UnconfREQ(int i);
	void eval_ComplexACK(int i);


public:
	BACnetNetwork();
	int	AddSubnet(unsigned int newnet);
	int	AddSubnet(unsigned int newnet, unsigned int nType);
	std::vector<int>			GetSubnets();
	std::vector<int>			GetSubnetDevices(int sn);
	std::vector<int>			GetControllerDeviceIDs(int ignoreTemplate=0);
	std::vector<BACvalue>		GetControllerObjectList(int devID);
	std::vector<std::string>	GetControllerObjectParameterList(int devID, int objID);
	std::vector<int>			GetTemplateDevices();
	int							IsTemplate(int devID);
	int							SetHostNetwork(unsigned int nv) { if ((nv < 65534) && (nv > 0)) { hostNet = nv; return 1; } return 0; };  // if it's in range keep it.
	unsigned int				GetHostNetwork() { return hostNet; };
	void						SetTemplate(int devID, int tpl);

	HTREEITEM GetTreepos() { return treepos; }
	void SetTreepos(HTREEITEM rv) { treepos = rv; }
	int FindTreeItem(HTREEITEM findItem, int* devID, int* obj, int* inst, int* prop, int* arrIndex, int* isFocus);
	int SetItemTreepos(HTREEITEM hti, int devID, int obj, int inst, int prop, int arrIndex);
	int SetPropTreepos(HTREEITEM hti, int devID, int obj, int inst, int prop, int arrIndex); // Sets Prop treepos- NOTE PROP IS INDEX
	int SetSubnetTreepos(HTREEITEM hti, int snet);
	int ResetTreepos(int devID);  // Resets trepos IN PROPS ONLY, call when updating display in focus window to a different controller

	HTREEITEM GetSubnetTreepos(int snet);
	HTREEITEM GetItemTreepos(int devID, int obj, int inst, int prop, int arrIndex); // Gets Object or Prop treepos


	int AddBaseController();
	void ResetDefaultControllerInfo();
	
	int AddController(int devID, unsigned int newnet);
	int DelController(int devID);  // removed controller from list
	
	int AddControllerObject(int devID, int objectType, int objectInst);
	int AddControllerObjectProperty(int devID, int objectType, int objectInst, int propType);
	
	int SetControllerObjectProperty(int devID, int objectType, int objectInst, int propType, BACvalue *bv);
	int GetControllerObjectProperty(int devID, int objectType, int objectInst, int propType, BACvalue *bv);
	int SetControllerObjectProperty(int devID, int objectType, int objectInst, int propType, int idx, BACvalue* bv);	// version with property index
	int GetControllerObjectProperty(int devID, int objectType, int objectInst, int propType, int idx, BACvalue* bv);	// version with property index

	//int SetTemplate(int devID, int newtemplate);

	int SetControllerTemplate(int devID, int devTemplate);  // calls controller function SetTemplate 
	std::vector<std::string> GetTemplateNames();

	int GetDeviceFromNetInfo(DevAddr* inDev);  // for when the device id is not set due to being unknown from packet (i.e. most readProps)

	int GetControllerAddressInfo(int devID, DevAddr* rv);
	int SetControllerAddressInfo(int devID, DevAddr* rv);

	int SetNetType(int newType) { netType = (newType == 0) ? 0 : 1; return 1; };  // valid values are 0 or 1
	int GetNetType() { return netType; };
	
	int GetHostAddressInfo(DevAddr* rv);
	
	std::vector<std::string>	GetControllerStrings(int devID);
	std::vector<std::string>	GetMessageStrings();
	int SaveFile(char* opname);

	int CheckForBACnetMessages();  // MAG 260504 Checks for BACnet message from network, handles/routes them
	int SendBACnetMessages();		// MAG send the contents of senddt.

	int SetLibrary(int devID, std::string hLib);  // Finds controller devID and passes library name to it 
};

