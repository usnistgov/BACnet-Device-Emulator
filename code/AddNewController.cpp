// AddNewController.cpp : implementation file
//

#include "pch.h"
#include "BACnet Device Emulator.h"
#include "afxdialogex.h"
#include "AddNewController.h"


// AddNewController dialog

IMPLEMENT_DYNAMIC(AddNewController, CDialogEx)

AddNewController::AddNewController(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_AddNewController, pParent)
{
	newDevID = 0;	// save value of new device ID here
	controllerType = 0; // 0=generic 1=AHU 2=VAV 3=Boiler 4=Chiller 5=Pump 6=misc i/o (10 AI&AO 20 AV 5 BI/BO 10 BV)
	subnetSel = 0;  // INDEX of selected subnet
	multCheck = 0;	// is multiple checked?
	multcount = 0;	// if multiple is checked, add this many
	newIsTemplate = 0;// 0=no, 1=yes
	mstpMAC = 1;	// MAC address on mstp network
}

AddNewController::~AddNewController()
{
}

void AddNewController::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATUS, m_status);
	DDX_Control(pDX, IDC_CONTROLLER_TYPE, m_controller_type);
	DDX_Control(pDX, IDC_CONTROLLER_NET, m_controller_net);
	DDX_Control(pDX, IDC_CONTROLLER_DEVID, m_controller_devid);
	DDX_Control(pDX, IDOK, m_IDOK);
	DDX_Control(pDX, IDC_MULTIPLE_CONTROLLERS, m_add_multiple);
	DDX_Control(pDX, IDC_CONTROLLER_COUNT, m_controller_count);
	DDX_Control(pDX, IDC_MULTIPLE_CONTROLLERS2, m_addAsTemplate);
	DDX_Control(pDX, IDC_CONTROLLER_MAC, m_controller_mac);
	DDX_Control(pDX, IDC_LIBRARY_NAME, m_library_name);
}


BEGIN_MESSAGE_MAP(AddNewController, CDialogEx)
	ON_EN_CHANGE(IDC_CONTROLLER_DEVID, &AddNewController::OnChangeControllerDevid)
	ON_BN_CLICKED(IDC_MULTIPLE_CONTROLLERS, &AddNewController::OnClickedMultipleControllers)
	ON_EN_CHANGE(IDC_CONTROLLER_COUNT, &AddNewController::OnChangeControllerCount)
	ON_BN_CLICKED(IDC_MULTIPLE_CONTROLLERS2, &AddNewController::OnBnClickedMultipleControllers2)
	ON_CBN_SELCHANGE(IDC_CONTROLLER_TYPE, &AddNewController::OnCbnSelchangeControllerType)
	ON_EN_CHANGE(IDC_CONTROLLER_MAC, &AddNewController::OnEnChangeControllerMac)
	ON_EN_KILLFOCUS(IDC_CONTROLLER_MAC, &AddNewController::OnEnKillfocusControllerMac)
	ON_EN_KILLFOCUS(IDC_CONTROLLER_DEVID, &AddNewController::OnEnKillfocusControllerDevid)
	ON_EN_KILLFOCUS(IDC_CONTROLLER_COUNT, &AddNewController::OnEnKillfocusControllerCount)
	ON_BN_CLICKED(IDC_LIBRARY_SELECT, &AddNewController::OnBnClickedLibrarySelect)
	ON_CBN_KILLFOCUS(IDC_ADD_OBJ_DEVID_LIST, &AddNewController::OnCbnKillfocusAddObjDevidList)
END_MESSAGE_MAP()


// AddNewController message handlers

BOOL AddNewController::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CString cs1;
	size_t i = 0;

	// TODO:  Add extra initialization here
	for (i = 0; i < inputMessage.size(); i++){
		m_status.AddString(inputMessage[i]);
	}

	for (i = 0; i < tNames.size(); i++) {
		m_controller_type.AddString(tNames[i]);
	}
	m_controller_type.SetCurSel(0);

	//m_controller_type.AddString(L"Generic");
	//m_controller_type.AddString(L"AHU");
	//m_controller_type.AddString(L"VAV");
	//m_controller_type.AddString(L"Boiler");
	//m_controller_type.AddString(L"Chiller");
	//m_controller_type.AddString(L"Pump");
	//m_controller_type.AddString(L"Misc I/O");
	//m_controller_type.SetCurSel(1);

	for (size_t i = 0; i < subnetList.size(); i++){
		cs1.Format(L"%d", subnetList[i]);
		m_controller_net.AddString(cs1);
	}
	m_controller_net.SetCurSel(subnetList.size() - 1);

	lastCountValue = "5";
	m_controller_count.SetWindowTextW(L"");  // set to "5" initially when active
	m_controller_mac.SetWindowTextW(L"0x01");

	m_controller_devid.SetFocus();

	return FALSE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


// MAG 260609 add this to consolidate functionality (it's used more than once)
// checks that the device id entered in box is not in devidList
int AddNewController::CheckDevID()
{
	CString netText;
	int		devID;

	m_controller_devid.GetWindowText(netText);
	if (netText.GetLength() == 0) return 0;
	devID = _ttoi(netText);

	// Check range 1-65534
	if ((devID < 0) || (devID > 4194302)) {
		//m_IDOK.EnableWindow(0); // disable window
		return 0;
	}

	// Check for unused device ID
	auto it = std::find(devidList.begin(), devidList.end(), devID);
	if (it != devidList.end()) { // device ID is in list, already exists
		//m_IDOK.EnableWindow(0); // disable window
		return 0;
	}

	return 1; /// a unique id is entered (and in range)
}


// MAG 260721 add this to consolidate functionality (it's used more than once)
// checks that the MAC entered in box is not in list for subnet
// Does not disable or enable windows
int AddNewController::CheckMAC()
{
	CString macText;
	int		macID = 0;
	int		snid = m_controller_net.GetCurSel();  // subnet index

	if (snid > devMACList.size()) return 1; // config error, so can't disable
	if (devMACList[snid].size() == 0) return 1; // nothing to compare, don't disable

	m_controller_mac.GetWindowText(macText);
	if (macText.GetLength() == 0) return 0;
	macID = std::stoul(macText.GetBuffer(), nullptr, 16);

	// Check range 1-254
	if ((macID < 0) || (macID > 254)) {
		return 0;
	}

	// Check for unused device ID
	auto it = std::find(devMACList[snid].begin(), devMACList[snid].end(), macID);
	if (it != devMACList[snid].end()) { // MAC ID is in list, already exists
		return 0;
	}

	return 1; /// a unique id is entered (and in range)
}


void AddNewController::OnChangeControllerDevid()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.


	CString netText;
	int		devID;

	m_controller_devid.GetWindowText(netText);
	devID = _ttoi(netText);

	//// Check range 1-65534
	//if ((devID < 0) || (devID > 4194302)) {
	//	m_IDOK.EnableWindow(0); // disable window
	//	return;
	//}
	//
	//// Check for unused device ID
	//auto it = std::find(devidList.begin(), devidList.end(), devID);
	//if (it != devidList.end()) { // device ID is in list, already exists
	//	m_IDOK.EnableWindow(0); // disable window
	//	return;
	//}
	if (CheckDevID() == 0) {
		m_IDOK.EnableWindow(0); // disable window
		return;
	}

	m_IDOK.EnableWindow(1); // enable window

	// update values to pass back to main
	subnetSel = m_controller_net.GetCurSel();
	controllerType = m_controller_type.GetCurSel();
	m_controller_devid.GetWindowText(netText);
	newDevID = _ttoi(netText);
	multCheck = (m_add_multiple.GetCheck() == BST_CHECKED)?1:0;
	m_controller_count.GetWindowText(netText);
	multcount = _ttoi(netText);
	newIsTemplate = (m_addAsTemplate.GetCheck() == BST_CHECKED) ? 1 : 0;

	newDevID = devID;
	m_IDOK.EnableWindow(1);

	//netText.Format(L"Change Device ID to %d.", newDevID);
	//m_status.AddString(netText);


	// TODO:  Add your control notification handler code here
}


void AddNewController::OnEnKillfocusControllerDevid()
{
	// TODO: Add your control notification handler code here
	CString devText;
	CString cs1;

	m_controller_devid.GetWindowText(devText);
	cs1.Format(L"Change Device ID to ");
	cs1 += devText;
	m_status.AddString(cs1);
}



void AddNewController::OnClickedMultipleControllers()
{
	// TODO: Add your control notification handler code here
	if (m_add_multiple.GetCheck() == 1) {
		m_status.AddString(L"Enable multiple controllers option.");
		m_controller_count.EnableWindow(1);
		multCheck = 1;
		m_controller_count.SetWindowTextW(lastCountValue);  // set to "1" when active
		m_controller_count.SetFocus();
	} else {
		m_status.AddString(L"Disable multiple controllers option.");
		m_controller_count.EnableWindow(0);
		multCheck = 0;
		m_controller_count.GetWindowText(lastCountValue);
		//m_controller_count.SetWindowTextW(L"");  // set to "1" when active
		m_controller_devid.SetFocus();
	}
}

void AddNewController::OnChangeControllerCount()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here

}

void AddNewController::OnEnKillfocusControllerCount()
{
	// TODO: Add your control notification handler code here
	BOOL trans = FALSE;
	CString cs1;
	
	if (CheckDevID() == 0) return;
	
	multcount = GetDlgItemInt(IDC_CONTROLLER_COUNT,&trans, TRUE);
	if ((multcount <= 0)||(multcount > 100)) {
		m_status.AddString(L"Multiple controller range 1-100");
		m_IDOK.EnableWindow(FALSE);
		m_controller_count.SetWindowText(L"5");
		multcount = 5;
	} else {
		m_IDOK.EnableWindow(TRUE);
		cs1.Format(L"Change multiple controller count to %d.", multcount);
		m_status.AddString(cs1);

	}
}


void 
AddNewController::SetTemplateNames(std::vector < std::string> nl)
{
	CString cs;

	for (size_t i = 0; i < nl.size(); i++){
		cs = nl[i].c_str();
		tNames.push_back(cs);
	}
}

// Checkbox for template
void AddNewController::OnBnClickedMultipleControllers2()
{
	// TODO: Add your control notification handler code here
	newIsTemplate = (m_addAsTemplate.GetCheck() == BST_CHECKED) ? 1 : 0;
	if (newIsTemplate) {
		m_controller_net.SetCurSel(0);  // set to subnet 0
		subnetSel = 0;
		m_controller_net.EnableWindow(0);
		m_add_multiple.EnableWindow(0);
		m_add_multiple.SetCheck(0);
		m_controller_count.EnableWindow(0);
		m_controller_count.SetWindowText(L"");
		m_status.AddString(L"New controller is set as template.");
	} else {
		m_controller_net.EnableWindow(1);
		m_add_multiple.EnableWindow(1);
		m_status.AddString(L"New controller is set as NOT template.");
	}


}

void AddNewController::OnCbnSelchangeControllerType()
{
	// TODO: Add your control notification handler code here
	CString cs1;
	CString cs2;

	controllerType = m_controller_type.GetCurSel();
	if (controllerType == 0) {
		m_controller_mac.SetWindowTextW(L"0x01");
		mstpMAC = 0x01;
	} else if (controllerType == 1) {
		m_controller_mac.SetWindowTextW(L"0x10");
		mstpMAC = 0x10;
	} else {
		m_controller_mac.SetWindowTextW(L"0x20");
		mstpMAC = 0x20;
	}

	m_controller_type.GetLBText(controllerType, cs2);
	cs1.Format(L"Change controller template to ");
	cs1 += cs2;
	m_status.AddString(cs1);

}

void AddNewController::OnEnChangeControllerMac()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}

void AddNewController::OnEnKillfocusControllerMac()
{
	// TODO: Add your control notification handler code here
	CString cs1;
	m_controller_mac.GetWindowText(cs1);
	if (cs1.Left(2).Compare(L"0x") == 0) {  // it's in hex, as expected
		_stscanf_s(cs1, _T("%x"), &mstpMAC);
	} else {  // probably removed leading 0x and it's in decimal
		mstpMAC = _ttoi(cs1);
	}

	if (CheckMAC() == 1) {
		m_IDOK.EnableWindow(1);
	} else {
		m_IDOK.EnableWindow(0);
	}
	cs1.Format(L"Change MS/TP MAC address to 0x%02X", mstpMAC);
	m_status.AddString(cs1);
}


void AddNewController::OnBnClickedLibrarySelect()
{
	// TODO: Add your control notification handler code here
	CString		pathName;
	CFileDialog fileDlg(TRUE, L"dll", pathName, OFN_FILEMUSTEXIST || OFN_READONLY, L"DLL Files (*.dll)|*.dll||");

	try {
		if (fileDlg.DoModal() == IDOK) {
			pathName = fileDlg.GetPathName();

			libraryName = std::string(CT2A(pathName));
			m_library_name.SetWindowText(pathName);
			m_status.AddString(L"Select library file:");
			m_status.AddString(pathName);
		}
	}
	catch (const std::exception& e) {
		// Log the error message
		CString err;
		m_status.AddString(L"ERROR: Caught exception in OnBnClickedLibrarySelect!");
		err.Format(L"ERROR: %S", e.what());
		m_status.AddString(err);
	}
	catch (...) {
		m_status.AddString(L"ERROR: Caught unknown exception in OnBnClickedLibrarySelect!");
	}


}

void AddNewController::OnCbnKillfocusAddObjDevidList()
{
	// TODO: Add your control notification handler code here

}
