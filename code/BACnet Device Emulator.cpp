
// BACnet Device Emulator.cpp : Defines the class behaviors for the application.
//

/*
22.1.5 Minimum Device Requirements
A device that conforms to the BACnet protocol and contains an application layer shall:
(a) contain exactly one Device object,
(b) execute the ReadProperty service,
(c) execute the Who-Has and Who-Is services (and thus initiate the I-Have and I-Am services) unless the device is an MS/TP slave device,
(d) execute the WriteProperty service if the device executes the WritePropertyMultiple, AddListElement or RemoveListElement services,
(e) allow the WriteProperty service to modify any properties that are modifiable by the AddListElement or RemoveListElement services,
(f) execute the WriteProperty service if the device contains any objects with properties that are required to be writable, and
(g) have a configurable device instance that can take on any value across the range 0 .. 4194302.
*/



#include "pch.h"
#include "framework.h"
#include "BACnet Device Emulator.h"
#include "BACnet Device EmulatorDlg.h"
#include "BACnetNetwork.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BACnetNetwork mybn;  // BACnet Network- Global


// CBACnetDeviceEmulatorApp

BEGIN_MESSAGE_MAP(CBACnetDeviceEmulatorApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CBACnetDeviceEmulatorApp construction

CBACnetDeviceEmulatorApp::CBACnetDeviceEmulatorApp()
{
	// support Restart Manager
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CBACnetDeviceEmulatorApp object

CBACnetDeviceEmulatorApp theApp;


// CBACnetDeviceEmulatorApp initialization

BOOL CBACnetDeviceEmulatorApp::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	AfxEnableControlContainer();

	// Create the shell manager, in case the dialog contains
	// any shell tree view or shell list view controls.
	CShellManager *pShellManager = new CShellManager;

	// Activate "Windows Native" visual manager for enabling themes in MFC controls
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	CBACnetDeviceEmulatorDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "Warning: dialog creation failed, so application is terminating unexpectedly.\n");
		TRACE(traceAppMsg, 0, "Warning: if you are using MFC controls on the dialog, you cannot #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS.\n");
	}

	// Delete the shell manager created above.
	if (pShellManager != nullptr)
	{
		delete pShellManager;
	}

#if !defined(_AFXDLL) && !defined(_AFX_NO_MFC_CONTROLS_IN_DIALOGS)
	ControlBarCleanUp();
#endif

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}


// MAG 260423
// Purpose: read in controller, object, property, subnet data from xml file
// Enter data in format to fill out internal data structures.
// Returns: 1 on success, 0 on failure
//Format is: (... means multiple potential)
//<controllers>
//	<controller id= subnet= >...
//		<object type= label= instance= >... (note type is the BACnetObjectType array index, label is overriden if prop 77 object-name is present. treat as for user info.)
//  		<property type= label= >...		(note type is the BACnetPropertyIdentifier array index, label is informative i.e. for user)
//  			<value type= >...			(note type follows BACnet application tags per 20.2.1.4)
//</ end tags >
int
CBACnetDeviceEmulatorApp::ReadConfigFile(char* ipname)
{
	mxml filex;
	xml_element *xroot = NULL;
	xml_element* xdevice = NULL;
	xml_element* xcontrollers = NULL;
	xml_element* xobject = NULL;
	xml_element* xprop = NULL;
	xml_element* xvalue = NULL;
	xml_props* xp1 = NULL;
	char mschar[15] = {};// MAC string for conversion function
	int	devID = -1;
	int subnet = 0;
	int objType = 0;	// read from the <object /> node
	int objInst = 0;	// read from the <object /> node
	int propType = 0;
	int templateType = 0;
	BACvalue	bv;
	CString cs1;
	CString macString;
	DevAddr myda = {};
	std::string ss1;

	if (ipname == NULL) {
		statusStrings.push_back("Error: input name is NULL.");
		return 0;
	}

	cs1.Format(L"Reading file: '%S'", ipname);
	ss1 = (CStringA)cs1;
	statusStrings.push_back(ss1);

	if (filex.read_xml_file(ipname) == 0) {
		statusStrings.push_back("Error: Reading XML file.");
		return 0;
	}

	xroot = filex.getRoot();

	xcontrollers = filex.element_by_name(xroot, "controllers");	// preferred
	if (xcontrollers == NULL) xdevice = filex.element_by_name(xroot, "devices");
	if (xcontrollers == NULL) {
		statusStrings.push_back("Error: In XML file controllers/devices node not found.");
		//return 0;  MAG let this go for now in case it's an old format
		xcontrollers = xroot;
	}

	xdevice = filex.element_by_name(xcontrollers, "controller");	// preferred
	if(xdevice == NULL) xdevice = filex.element_by_name(xcontrollers, "device");
	if (xdevice == NULL) {
		statusStrings.push_back("Error: In XML file controller/device node not found.");
		return 0;
	}

	memset(&bv, 0, sizeof(BACvalue));

	// Loop through controller objects
	while (xdevice != NULL) {
		xp1 = filex.getprop(xdevice, "id");
		if (xp1 != NULL) {
			devID = std::stoi(xp1->data);
		}

		xp1 = filex.getprop(xdevice, "subnet");
		if (xp1 != NULL) {
			subnet = std::stoi(xp1->data);
		}

		if (subnet == mybn.GetHostNetwork()) {
			statusStrings.push_back("NOTE: Skip reading Host controller from config file.");
			xdevice = xdevice->next;
			continue;
		}

		xp1 = filex.getprop(xdevice, "templateType");
		if (xp1 != NULL) {
			templateType = std::stoi(xp1->data);
		}

		xp1 = filex.getprop(xdevice, "deviceMAC");
		if (xp1 != NULL) {
			macString = xp1->data.c_str();
		}

		if(templateType > 0){
			cs1.Format(L"Add template ID: %d", devID);
		} else {
			cs1.Format(L"Add controller: %d:%d", subnet, devID);
		}

		ss1 = (CStringA)cs1;
		statusStrings.push_back(ss1);

		// MAG 260723 TODO- add code to save and read logic library settings

		// MAG 260723 TODO- put flag to check for duplicate template controllers, 
		// add setting or pop-up to determine if config file or existing in app template to be kept.

		// Add Controller Here
		mybn.AddController(devID, subnet);
		if (templateType > 0) {
			mybn.SetTemplate(devID, templateType);
			templateType = 0;
		}

		// set MAC address if found
		if (macString.GetLength() > 0){
			sprintf_s(mschar, 15, "%S", macString.GetString());
			mybn.GetControllerAddressInfo(devID, &myda);  // retrieve whatever info is in addr
			BACfuncs::SetDeviceMAC(&myda, mschar);
			mybn.SetControllerAddressInfo(devID, &myda);  // send it back with updated MAC
		}

		xobject = filex.element_by_name(xdevice, "object");
		if(xobject == NULL){		// move to next device if no objects
			xdevice = xdevice->next;
			continue;
		}

		while (xobject != NULL) {
			// read object type and instance- both are required
			xp1 = filex.getprop(xobject, "type");
			if (xp1 != NULL) {
				objType = std::stoi(xp1->data);
			} else {		// go to next object
				xobject = xobject->next;
				continue;
			}

			xp1 = filex.getprop(xobject, "instance");
			if (xp1 != NULL) {
				objInst = std::stoi(xp1->data);
			} else {		// go to next object
				xobject = xobject->next;
				continue;
			}

			// debug
			//if (objInst == 0) {
			//	if (objType == 0) {
			//		cs1.Format(L"NOTE adding Controller %d object %d:%d", devID, objType, objInst); // breakpoint line
			//	}
			//}
			// Add the object being read in
			if (!mybn.AddControllerObject(devID, objType, objInst)) {
				cs1.Format(L"ERROR adding Controller %d object %d:%d", devID, objType, objInst);
			}

			// read object props
			xprop = filex.element_by_name(xobject, "property");
			while (xprop != NULL) {
				xp1 = filex.getprop(xprop, "type");
				if (xp1 == NULL) {
					xprop = xprop->next;
					continue;
				}

				propType = std::stoi(xp1->data);
				// debug
				//if ((objInst == 32)&&(propType == 77)) {
				//	cs1.Format(L"NOTE adding Controller %d object %d:%d", devID, objType, objInst);
				//}
				//if ((objInst == 97) && (propType == 77)) {
				//	cs1.Format(L"NOTE adding Controller %d object %d:%d", devID, objType, objInst);
				//}
				//if ((objInst == 32) && (objType == 5) && (propType == 75) && (devID == 3210)){
				//	cs1.Format(L"NOTE adding Controller %d object %d:%d", devID, objType, objInst);
				//}

				if (mybn.AddControllerObjectProperty(devID, objType, objInst, propType) == 0) {
					cs1.Format(L"ERROR adding Controller %d object %d:%d property %d", devID, objType, objInst,propType);
				}

				// check for error indicator in XML
				xp1 = filex.getprop(xprop, "readerr");
				if (xp1 != NULL) {	 // nothing else to read in this one
					xprop = xprop->next;
					continue;
				}

				xvalue = filex.element_by_name(xprop, "value");
				if (xvalue == NULL) {
					xprop = xprop->next;
					continue;
				}

				xp1 = filex.getprop(xvalue, "type");
				if(xp1 == NULL) {
					xprop = xprop->next;
					continue;
				}

				bv.type = std::stoi(xp1->data);
				if (BACfuncs::StringToBACvalue(xvalue->data.c_str(), &bv) == 1) {
					if (mybn.SetControllerObjectProperty(devID, objType, objInst, propType, &bv) == 0) {  // if prop doesn't exist, add it and then set value
						if (mybn.AddControllerObjectProperty(devID, objType, objInst, propType) == 1) {
							mybn.SetControllerObjectProperty(devID, objType, objInst, propType, &bv);
						} else {
							//error!
							cs1.Format(L"ERROR adding prop to %d obj %d inst %d prop %d ", devID, objType, objInst, propType);
							ss1 = (CStringA)cs1;
							statusStrings.push_back(ss1);
						}
					}
				}

				// keep at end
				xprop = xprop->next; // move to next prop
			}

			// keep at end
			xobject = xobject->next; // move to next object
		} 

		// keep at end
		xdevice = xdevice->next; // move to next device
	}
	cs1.Format(L"Finish reading file: '%S'", ipname);
	ss1 = (CStringA)cs1;
	statusStrings.push_back(ss1);

	return 1;
}  // end ReadConfigFile


// MAG 260423
// Purpose: read in controller, object, property, subnet data from xml file
// Enter data in format to fill out internal data structures.
// Returns: 1 on success, 0 on failure
//Format is: (... means multiple potential)
//<controllers>
//	<controller id= subnet= >...
//		<object type= label= instance= >... (note type is the BACnetObjectType array index, label is overriden if prop 77 object-name is present. treat as for user info.)
//  		<property type= label= >...		(note type is the BACnetPropertyIdentifier array index, label is informative i.e. for user)
//  			<value type= >...			(note type follows BACnet application tags per 20.2.1.4)
//</ end tags >
int
CBACnetDeviceEmulatorApp::SaveConfigFile(char* ipname)
{
	if (ipname == NULL) return 0;

	return mybn.SaveFile(ipname);
}  // end SaveConfigFile


std::vector<std::string> 
CBACnetDeviceEmulatorApp::GetStatusStrings()
{
	std::vector<std::string> rv;

	rv = statusStrings;
	statusStrings.clear();

	return rv;
}


// the tree has been clicked! (left buttton)
void 
CBACnetDeviceEmulatorApp::ReadClick(HTREEITEM hti)
{
	int rdevID = 0;
	int robject = 0;
	int roinst = 0;
	int rprop = 0;
	int rindx = 0;
	int isFocus = 0;
	BACvalue bv = {};
	CString cs1;
	std::stringstream ss1;
	
	mybn.FindTreeItem(hti, &rdevID, &robject, &roinst, &rprop, &rindx, &isFocus);
	//ss1 << "Select device " << rdevID;
	//if(robject > 0) ss1 << " object " << robject << ":" << roinst;
	//statusStrings.push_back(ss1.str());
	if((rdevID > 0)&&(robject == -1)) m_pMainWnd->UpdateFocusTree(rdevID);  // only display if controller is selected, not obj/prop
}


// returns type of controller in terms of does it have a different color on tree display
int 
CBACnetDeviceEmulatorApp::GetItemType(HTREEITEM hti)
{
	int devID = 0;
	int obj = 0;
	int inst = 0;
	int prop = 0; 
	int arrIndex = 0; 
	int isFocus = 0;;

	if (mybn.FindTreeItem(hti, &devID, &obj, &inst, &prop, &arrIndex, &isFocus)) {
		// check for template devices
		if (mybn.IsTemplate(devID))
			return 1;
		// check for host device, only one on subnet 10
		std::vector<int> locdev =  mybn.GetSubnetDevices(10);
		if (locdev[0] == devID)
			return 2;
		// add check for other colors/types here as needed
	}
	return 0;
}


// the focus tree has been clicked! (left buttton)
void
CBACnetDeviceEmulatorApp::ReadDblClick(HTREEITEM hti)
{
	ModifyPropValue myMPV;
	int rdevID = 0;
	int robject = 0;
	int roinst = 0;
	int rprop = 0;
	int rindx = 0;
	int isFocus = 0;
	BACvalue bv = {};
	CString cs1;
	CString cs2;
	CString pval;
	CString pval2;
	CString macString;
	std::string st1;
	std::stringstream ss1;
	BACvalue lbv;
	char edval[150] = {};
	CRect itemrect;
	HTREEITEM htio = 0;		// for object containing prop, if necessary
	HTREEITEM htiFocus = 0; // for focus window
	HTREEITEM htiNet = 0;	// for net window 
	DevAddr myda = {};

	mybn.FindTreeItem(hti, &rdevID, &robject, &roinst, &rprop, &rindx, &isFocus);
	//if(rdevID == 0) mybn.FindFocusTreeItem(hti, &rdevID, &robject, &roinst, &rprop, &rindx, &isFocus);

	if ((robject >= 0) && (rprop < 0)) {  // only two things to click on without a property- name or pv
		if (robject == 8) rprop = 77;  // name
		else rprop = 85;  // present value by default, probably clicked on NET tree
	}

	if ((rprop >= 0)) {
		//m_pMainWnd->UpdateFocusTree(rdevID);  // only display if controller is selected, not obj/prop
		CString cs1 = L"Double click item found!";

		// MAG 260723 TODO- restrict text box input based on type of value, i.e. text vs numeric only- add param to ModifyPropValue
		if (mybn.GetControllerObjectProperty(rdevID, robject, roinst, rprop, &lbv) == 1) {
			st1 = BACfuncs::BACvalueToString(&lbv);
			cs1.Format(L"%S", st1.c_str());
			myMPV.prevValue = cs1;
		}

		myMPV.devID = rdevID;
		myMPV.objID = robject;
		myMPV.objInst = roinst;
		myMPV.propID = rprop;
		myMPV.propLabel = BAClabels::PropertyLabels[rprop].c_str();
		
		INT_PTR nResponse = myMPV.DoModal();
		if (nResponse == IDOK) {
			// check that it's actually changed 
			if (myMPV.prevValue.Compare(myMPV.newValue) == 0) {
				m_pMainWnd->m_status_focus.AddString(L"Property value was not changed.");
				return;
			}
			sprintf_s(edval, 150, "%S", myMPV.newValue.GetBuffer());
			if (BACfuncs::StringToBACvalue(edval, &lbv) == 0) {
				m_pMainWnd->m_status_focus.AddString(L"Property value was not changed. Entered value is not compatible with type.");
				return;
			}
			mybn.GetControllerObjectProperty(rdevID, robject, roinst, rprop, &bv);  // save the before value in bv
			st1 = BACfuncs::BACvalueToString(&bv);
			pval2 = st1.c_str();

			if (mybn.SetControllerObjectProperty(rdevID, robject, roinst, rprop, &lbv) == 1) {
				// Update display elements:
				// Get handles for net and focus windows
				if (isFocus) {
					htiFocus = hti;
					htio = m_pMainWnd->m_tree_focus.GetParentItem(hti);  // htio is parent of focus window property listing
					htiNet = 0;  // set later if used
				} else {
					htiNet = hti;
					htiFocus = mybn.GetItemTreepos(rdevID, robject, roinst, rprop, -1);
					if (htiFocus != 0) htio = m_pMainWnd->m_tree_focus.GetParentItem(htiFocus);
					else htio = 0;
				}					
				// write out updated property value line in focus window
				cs1.Format(L"P%d: %S: %S", rprop, BAClabels::PropertyLabels[rprop].c_str(), edval);
				if (htiFocus != 0) {
					m_pMainWnd->m_tree_focus.SetItemText(htiFocus, cs1.GetString());
					m_pMainWnd->m_tree_focus.GetItemRect(htiFocus, &itemrect, 1);
					m_pMainWnd->m_tree_focus.InvalidateRect(&itemrect, FALSE);
				}

				// some properties are written in more than one place, check for and update
				switch (rprop) {
				case 85: // update object text for present_value
					// object listing has PV, same string in both windows
					mybn.GetControllerObjectProperty(rdevID, robject, roinst, 77, &lbv);
					cs1.Format(L"%S (%d:%d) : %S : pres val: %S", BAClabels::ObjectLabels[robject].c_str(), robject, roinst, lbv.value.t, edval);
					// Focus window object listing
					if (htio != 0) {
						m_pMainWnd->m_tree_focus.SetItemText(htio, cs1.GetString());
						m_pMainWnd->m_tree_focus.GetItemRect(htio, &itemrect, 1);
						m_pMainWnd->m_tree_focus.InvalidateRect(&itemrect, FALSE);
					}
					// Net window object listing
					htiNet = mybn.GetItemTreepos(rdevID, robject, roinst, -1, -1);  // get 
					m_pMainWnd->m_net_tree.SetItemText(htiNet, cs1.GetString());
					m_pMainWnd->m_net_tree.GetItemRect(htiNet, &itemrect, 1);
					m_pMainWnd->m_net_tree.InvalidateRect(&itemrect, FALSE);

					break;
				case 70: // model-name, only in a device object
					htio = mybn.GetItemTreepos(rdevID, -1, -1, -1, -1);  // get node in net window
					if (htio != 0) {
						if (mybn.GetControllerAddressInfo(rdevID, &myda)) {
							macString.Format(L"MAC: %S", myda.mac_device_pr);
						} else {
							macString = "";
						}

						cs1.Format(L"DevId: %d %s Model Name: %S", rdevID, macString.GetBuffer(), edval);
						if (mybn.IsTemplate(rdevID) == 1){
							cs1 += " (Template)";
						}
						m_pMainWnd->m_net_tree.SetItemText(htio, cs1.GetString());
						m_pMainWnd->m_net_tree.GetItemRect(htio, &itemrect, 1);
						m_pMainWnd->m_net_tree.InvalidateRect(&itemrect, FALSE);
					}
					break;
				case 77: // update object text for object_name
					mybn.GetControllerObjectProperty(rdevID, robject, roinst, 85, &lbv);
					st1 = BACfuncs::BACvalueToString(&lbv);
					cs1.Format(L"%S (%d:%d) : %S : pres val: %S", BAClabels::ObjectLabels[robject].c_str(), robject, roinst,edval, st1.c_str());
					// update object_name in focus window
					if (htio != 0) {
						m_pMainWnd->m_tree_focus.SetItemText(htio, cs1.GetString());
						m_pMainWnd->m_tree_focus.GetItemRect(htio, &itemrect, 1);
						m_pMainWnd->m_tree_focus.InvalidateRect(&itemrect, FALSE);
					}
					// update object_name in net window
					htiNet = mybn.GetItemTreepos(rdevID, robject, roinst, -1, -1);  // get 
					if (htiNet != 0) {
						m_pMainWnd->m_net_tree.SetItemText(htiNet, cs1.GetString());
						m_pMainWnd->m_net_tree.GetItemRect(htiNet, &itemrect, 1);
						m_pMainWnd->m_net_tree.InvalidateRect(&itemrect, FALSE);
					}

					//if (isFocus) {
					//	htio = m_pMainWnd->m_tree_focus.GetParentItem(hti);
					//	m_pMainWnd->m_tree_focus.SetItemText(htio, cs1.GetString());
					//	m_pMainWnd->m_tree_focus.GetItemRect(htio, &itemrect, 1);
					//	m_pMainWnd->m_tree_focus.InvalidateRect(&itemrect, FALSE);
					//
					//	htio = mybn.GetItemTreepos(rdevID, robject, roinst, -1, -1); // Update present value in left tree
					//	if (htio != 0) {
					//		m_pMainWnd->m_net_tree.SetItemText(htio, cs1.GetString());
					//		m_pMainWnd->m_net_tree.GetItemRect(htio, &itemrect, 1);
					//		m_pMainWnd->m_net_tree.InvalidateRect(&itemrect, FALSE);
					//	}
					//} else {  // update for Net tree
					//	m_pMainWnd->m_net_tree.SetItemText(htio, cs1.GetString());
					//	m_pMainWnd->m_net_tree.GetItemRect(htio, &itemrect, 1);
					//	m_pMainWnd->m_net_tree.InvalidateRect(&itemrect, FALSE);
					//	htio = mybn.GetItemTreepos(rdevID, robject, roinst, 77, -1); // Get prop location in focus tree 
					//	if (htio != 0) {
					//		cs1.Format(L"P%d: %S: %S", rprop, BAClabels::PropertyLabels[rprop].c_str(), edval);
					//		m_pMainWnd->m_tree_focus.SetItemText(htio, cs1.GetString());
					//		m_pMainWnd->m_tree_focus.GetItemRect(htio, &itemrect, 1);
					//		m_pMainWnd->m_tree_focus.InvalidateRect(&itemrect, FALSE);
					//	}
					//}

					break;
				}
				m_pMainWnd->m_tree_focus.UpdateWindow();
				cs1.Format(L"Change value: Device %d Obj %d:%d Prop %d from %s to %S", rdevID, robject, roinst, rprop, pval2.GetString(), edval);
				m_pMainWnd->m_status_focus.AddString(cs1);
				//m_pMainWnd->m_status_focus.AddString(L"Property value was changed.");
			} else {
				m_pMainWnd->m_status_focus.AddString(L"Property value was not changed.");
			}
		}
	}
}
