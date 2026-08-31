
// BACnet Device EmulatorDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "BACnet Device Emulator.h"
#include "BACnet Device EmulatorDlg.h"
#include "BACnetNetwork.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

extern BACnetNetwork mybn;  // BACnet Network- Global defined in "BACnet Device Emulator.cpp"

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CBACnetDeviceEmulatorDlg dialog



CBACnetDeviceEmulatorDlg::CBACnetDeviceEmulatorDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_BACNET_DEVICE_EMULATOR_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBACnetDeviceEmulatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATUS, m_status);
	DDX_Control(pDX, IDC_NET_TREE, m_net_tree);
	DDX_Control(pDX, IDC_NET_TREE_FOCUS, m_tree_focus);
	DDX_Control(pDX, IDC_STATUS_FOCUS, m_status_focus);
	DDX_Control(pDX, IDC_SELECT_IP, m_select_ip);
	DDX_Control(pDX, IDC_SELECT_NETWORK_ADAPTER_LABEL, m_select_network_adapter_label);
}

BEGIN_MESSAGE_MAP(CBACnetDeviceEmulatorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_TEST_BUTTON1, &CBACnetDeviceEmulatorDlg::OnBnClickedTestButton1)
	ON_BN_CLICKED(IDC_TEST_BUTTON2, &CBACnetDeviceEmulatorDlg::OnBnClickedTestButton2)
	ON_BN_CLICKED(IDC_READ_FILE, &CBACnetDeviceEmulatorDlg::OnBnClickedReadFile)
	ON_BN_CLICKED(IDC_SEND_IAM, &CBACnetDeviceEmulatorDlg::OnBnClickedSendIam)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_ADD_CONTROLLER, &CBACnetDeviceEmulatorDlg::OnBnClickedAddController)
	ON_BN_CLICKED(IDC_SAVE_FILE, &CBACnetDeviceEmulatorDlg::OnBnClickedSaveFile)
	ON_COMMAND(ID_FILE_OPENCONFIGFILE, &CBACnetDeviceEmulatorDlg::OnFileOpenconfigfile)
	ON_COMMAND(ID_FILE_SAVECONFIGFILE, &CBACnetDeviceEmulatorDlg::OnFileSaveconfigfile)
	ON_WM_DROPFILES()
	ON_CBN_SELCHANGE(IDC_SELECT_IP, &CBACnetDeviceEmulatorDlg::OnCbnSelchangeSelectIp)
	ON_BN_CLICKED(IDC_DEL_CONTROLLER, &CBACnetDeviceEmulatorDlg::OnBnClickedDelController)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_ADD_OBJECT, &CBACnetDeviceEmulatorDlg::OnBnClickedAddObject)
	ON_LBN_SELCHANGE(IDC_STATUS, &CBACnetDeviceEmulatorDlg::OnLbnSelchangeStatus)
END_MESSAGE_MAP()


// CBACnetDeviceEmulatorDlg message handlers

BOOL CBACnetDeviceEmulatorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CString cs1;
	char cc1[55] = {};

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	//CString cs1;
	m_status.AddString(L"NIST BACnet Device Emulator v0.1 BETA");
	m_status.AddString(L"Note: This program is in active development.");
	m_status.AddString(L"by Mike Galler * mikeg@nist.gov");
	BACfuncs::GetBACVersionString(cc1);
	cs1 = cc1;
	m_status.AddString(cs1);
	
	//TV_ITEM item;
	//TV_INSERTSTRUCT insert;
	//
	//item.mask = TVIF_CHILDREN | TVIF_HANDLE | TVIF_TEXT | TVIF_STATE;
	//item.stateMask = TVIS_EXPANDED;
	//item.state = 0;
	//item.cchTextMax = 40;
	//item.iImage = 0;
	//item.iSelectedImage = 0;
	//item.cChildren = 1;
	//item.lParam = 0;
	//insert.hParent = nullptr;
	//insert.hInsertAfter = TVI_LAST;
	//insert.item = item;
	//cs1 = "No Controllers";
	//insert.item.pszText = cs1.GetBuffer();
	//m_net_tree.InsertItem(&insert);

	SetTimer(1, 50, NULL);	// BACnet read timer
	SetTimer(10, 100, NULL);
	prevFocusID = 0;
	//UpdateNetworkTree(); // show host controller

	//mybn.temp

	// Set adapter selection
	char adapterIP[20] = {};
	int nac = BACfuncs::WPCInit();  // returns adapter count
	if (nac > 1) {
		for (int i = 0; i < nac; i++) {
			if (BACfuncs::GetAdapterIPSLI(i, adapterIP) == 1) {
				cs1 = adapterIP;
				m_select_ip.AddString(cs1);
			} else {
				m_select_ip.AddString(L"NA");
			}
		}
		m_select_ip.SetCurSel(BACfuncs::GetDefaultAdapter());
		// MAG TODO? add code to show default adapter (GetDefaultAdapter(void);)
	} else {
		m_select_ip.ShowWindow(0);
		m_select_network_adapter_label.ShowWindow(0);
	}

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CBACnetDeviceEmulatorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CBACnetDeviceEmulatorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CBACnetDeviceEmulatorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void 
CBACnetDeviceEmulatorDlg::UpdateNetworkTree() 
{
	TV_ITEM item;
	TV_INSERTSTRUCT insert;
	std::string ss1;
	std::string ss2;
	std::string spval;
	std::wstring ws1;
	size_t st = 0;
	size_t i = 0;
	size_t j = 0;
	size_t k = 0;
	HTREEITEM titem;
	//HTREEITEM ioitem;
	//HTREEITEM instanceitem;
	HTREEITEM objitem;
	wchar_t mtext[100] = {};
	CString cs1;
	CString cs2;
	CString objName;
	CString macString;
	BACTreeCtrl* tree = NULL;
	std::vector<BACvalue> objArr;  // object id array
	std::vector<int> snl; // sub net list
	std::vector<int> devl; // device list
	std::vector<HTREEITEM> htl;  // htree item list
	std::vector<std::string> stringList;  // property info strings
	BACvalue bvl = {};
	BACvalue pval = {};
	DevAddr myda = {};

	memset(&bvl, 0, sizeof(BACvalue));

	item.mask = TVIF_CHILDREN | TVIF_HANDLE | TVIF_TEXT | TVIF_STATE;
	item.stateMask = TVIS_EXPANDED;
	item.state = 0;
	item.cchTextMax = 40;
	item.iImage = 0;
	item.iSelectedImage = 0;
	item.cChildren = 1;
	item.lParam = 0;
	insert.hParent = nullptr;
	insert.hInsertAfter = TVI_LAST;
	insert.item = item;

	tree = &m_net_tree;
	SendMessage(IDC_NET_TREE, WM_SETREDRAW, FALSE);  // freeze redraw while updating
	tree->DeleteAllItems();
	tree->ModifyStyle(0, TVS_HASBUTTONS | TVS_HASLINES | TVS_LINESATROOT);

	// parse through subnets
	snl = mybn.GetSubnets();  // retrieve list of subnets
	for (i = 0; i < snl.size(); i++){
		cs1.Format(L"Subnet %d", snl[i]);
		insert.item.pszText = cs1.GetBuffer();
		titem = tree->InsertItem(&insert);
		htl.push_back(titem);
		mybn.SetSubnetTreepos(titem, snl[i]);
	}

	// devl, snl and htl used to place controllers
	//devl = mybn.GetDeviceIDs();
	for (i = 0; i < snl.size(); i++){
		// find htl item for dev list subnet
		devl = mybn.GetSubnetDevices(snl[i]);
		for (j = 0; j < devl.size(); j++) {
			if (mybn.GetControllerAddressInfo(devl[j], &myda)) {
				macString.Format(L"MAC: %S",myda.mac_device_pr);
			} else {
				macString = "";
			}

			if (mybn.GetControllerObjectProperty(devl[j], 8, devl[j], (int)BACenums::BACProp::en_MODEL_NAME, &bvl) == 1) {
				cs1.Format(L"DevId: %d %s Model Name: %S", devl[j], macString.GetString(), bvl.value.t);
			} else {
				cs1.Format(L"DevId: %d %s Model Name: NA", devl[j],macString.GetString());
			}
			if(mybn.IsTemplate(devl[j])) cs1 += L" (Template)";
			titem = tree->InsertItem(cs1, htl[i]);
			mybn.SetItemTreepos(titem, devl[j], -1, -1, -1, -1);

			// get object list info
			objArr = mybn.GetControllerObjectList(devl[j]);
			for (size_t k = 0; k < objArr.size(); k++){
				if (objArr[k].value.o.object < BAClabels::ObjectLabels.size()) {
					ss1 = BAClabels::ObjectLabels[objArr[k].value.o.object];
				} else {
					ss1 = "Custom Object";
				}
				if (mybn.GetControllerObjectProperty(devl[j], objArr[k].value.o.object, objArr[k].value.o.id, (int)BACenums::BACProp::en_PRESENT_VALUE, &pval) == 1) {
					spval = BACfuncs::BACvalueToString(&pval);
					cs2.Format(L" : pres val: %S", spval.c_str());
				} else cs2 = "";

				if (mybn.GetControllerObjectProperty(devl[j], objArr[k].value.o.object, objArr[k].value.o.id, (int)BACenums::BACProp::en_OBJECT_NAME, &bvl) == 1) {
					//cs1.Format(L"Object type %d Instance %d Object name: %S", objArr[k].value.o.object, objArr[k].value.o.id, bvl.value.t);
					cs1.Format(L"%S (%d:%d) : %S%s",ss1.c_str(), objArr[k].value.o.object, objArr[k].value.o.id, bvl.value.t,cs2.GetBuffer());
				} else {
					//cs1.Format(L"Object type %d Instance %d", objArr[k].value.o.object, objArr[k].value.o.id);
					cs1.Format(L"%S (%d:%d)%s", ss1.c_str(), objArr[k].value.o.object, objArr[k].value.o.id,cs2.GetBuffer());
				}
				objitem = tree->InsertItem(cs1, titem);
				mybn.SetItemTreepos(objitem, devl[j], objArr[k].value.o.object, objArr[k].value.o.id, -1, -1);

				// MAG 260610 disable for now, move to deparate function for controller focus tree
				//stringList = mybn.GetControllerObjectParameterList(devl[j], k);
				//for (size_t m = 0; m < stringList.size(); m++) {
				//	cs1.Format(L"%S", stringList[m].c_str());
				//	tree->InsertItem(cs1, objitem);
				//}
				//stringList.clear();
			}
			
			//stringList = mybn.GetControllerStrings(devl[j]);
			//for (k = 0; k < stringList.size(); k++){
			//	if (stringList[k].find("null") == std::string::npos) {  // if no "null"
			//		cs1.Format(L"%S", stringList[k].c_str());
			//		tree->InsertItem(cs1, titem);
			//	}
			//}
		}
	}

	SendMessage(IDC_NET_TREE, WM_SETREDRAW, TRUE);  // allow redraw after updating

	return;
}

// MAG 260610
// copied from UpdateNetworkTree
void CBACnetDeviceEmulatorDlg::UpdateFocusTree(int devID)
{
	TV_ITEM item;
	TV_INSERTSTRUCT insert;
	std::string ss1;
	std::string ss2;
	std::string spval;
	std::wstring ws1;
	size_t st = 0;
	size_t i = 0;
	size_t j = 0;
	size_t k = 0;
	HTREEITEM titem;
	HTREEITEM objitem;
	wchar_t mtext[100] = {};
	CString cs1;
	CString cs2;
	CString objName;
	BACTreeCtrl* tree = NULL;
	std::vector<BACvalue> objArr;  // object id array
	std::vector<int> obl; // object list
	//std::vector<int> devl; // device list
	std::vector<HTREEITEM> htl;  // htree item list
	std::vector<std::string> stringList;  // property info strings
	BACvalue bvl = {};
	BACvalue pval = {};
	static CTime lastCall = CTime::GetCurrentTime();  // NOTE only called the first time!
	static bool timerActive = 0;
	CTime tnow = CTime::GetCurrentTime();
	CTimeSpan onesecond = CTimeSpan(0, 0, 0, 1);

	// if devID is -1, just use last 
	if (devID < 0) devID = prevFocusID;

	// MAG 260706 limit redraws to one per second (adjust as necessary)
	if ((tnow - lastCall < onesecond)&&(devID == prevFocusID)) {
		if (timerActive) return;
		SetTimer(11, 1000,NULL);
		timerActive = true;
		return;
	}

	timerActive = false;
	lastCall = tnow;

	memset(&bvl, 0, sizeof(BACvalue));

	item.mask = TVIF_CHILDREN | TVIF_HANDLE | TVIF_TEXT | TVIF_STATE;
	item.stateMask = TVIS_EXPANDED;
	item.state = 0;
	item.cchTextMax = 40;
	item.iImage = 0;
	item.iSelectedImage = 0;
	item.cChildren = 1;
	item.lParam = 0;
	insert.hParent = nullptr;
	insert.hInsertAfter = TVI_LAST;
	insert.item = item;

	tree = &m_tree_focus;

	SendMessage(IDC_NET_TREE_FOCUS, WM_SETREDRAW, FALSE);  // freeze redraw while updating
	tree->DeleteAllItems();
	
	// Reset the treepos values in the previously shown tree
	mybn.ResetTreepos(prevFocusID);
	prevFocusID = devID;  // NOTE update even if ID is the same as values may have changed!

	tree->ModifyStyle(0, TVS_HASBUTTONS | TVS_HASLINES | TVS_LINESATROOT);

	cs1.Format(L"Display controller %d", devID);
	m_status_focus.AddString(cs1);

	// parse object list


	objArr = mybn.GetControllerObjectList(devID);
	for (size_t k = 0; k < objArr.size(); k++) {
		// Build Object display string
		if (objArr[k].value.o.object < BAClabels::ObjectLabels.size()) {
			ss1 = BAClabels::ObjectLabels[objArr[k].value.o.object];
		} else {
			ss1 = "Custom Object";
		}
		if (mybn.GetControllerObjectProperty(devID, objArr[k].value.o.object, objArr[k].value.o.id, (int)BACenums::BACProp::en_PRESENT_VALUE, &pval) == 1) {
			spval = BACfuncs::BACvalueToString(&pval);
			cs2.Format(L" : pres val: %S", spval.c_str());
		} else cs2 = "";

		if (mybn.GetControllerObjectProperty(devID, objArr[k].value.o.object, objArr[k].value.o.id, (int)BACenums::BACProp::en_OBJECT_NAME, &bvl) == 1) {
			//cs1.Format(L"Object type %d Instance %d Object name: %S", objArr[k].value.o.object, objArr[k].value.o.id, bvl.value.t);
			cs1.Format(L"%S (%d:%d) : %S%s", ss1.c_str(), objArr[k].value.o.object, objArr[k].value.o.id, bvl.value.t, cs2.GetBuffer());
		} else {
			//cs1.Format(L"Object type %d Instance %d", objArr[k].value.o.object, objArr[k].value.o.id);
			cs1.Format(L"%S (%d:%d)%s", ss1.c_str(), objArr[k].value.o.object, objArr[k].value.o.id, cs2.GetBuffer());
		}

		// insert object text to tree
		insert.item.pszText = cs1.GetBuffer();
		objitem = tree->InsertItem(&insert);
		//mybn.SetItemTreepos(objitem, devID, objArr[k].value.o.object, objArr[k].value.o.id, -1, -1); MAG NOT resetting object level treepos.

		// MAG 260610 disable for now, move to deparate function for controller focus tree
		stringList = mybn.GetControllerObjectParameterList(devID, k);
		for (size_t m = 0; m < stringList.size(); m++) {
			cs1.Format(L"%S", stringList[m].c_str());
			titem = tree->InsertItem(cs1, objitem);
			mybn.SetPropTreepos(titem, devID, objArr[k].value.o.object, objArr[k].value.o.id, m, -1); //MAG need to work out how to get property ID here
		}
		stringList.clear();
	}

	//stringList = mybn.GetControllerStrings(devl[j]);
	//for (k = 0; k < stringList.size(); k++){
	//	if (stringList[k].find("null") == std::string::npos) {  // if no "null"
	//		cs1.Format(L"%S", stringList[k].c_str());
	//		tree->InsertItem(cs1, titem);
	//	}
	//}

	SendMessage(IDC_NET_TREE_FOCUS, WM_SETREDRAW, TRUE);  // allow redraw after updating

	return;
}


// Add Subnet
void CBACnetDeviceEmulatorDlg::OnBnClickedTestButton1()
{
	// TODO: Add your control notification handler code here
	//BACnetController myDev(3101,11);  // create device with devid 3101 on subnet 11
	std::vector<std::string> objString;
	CString cs1;
	CString cs2;
	std::vector<int> subnetList = mybn.GetSubnets();
	int netcount = subnetList.size();
	int newnetType = 0;
	AddNewNet netWindow;
	HTREEITEM hti;

	cs1.Format(L"Current subnets: ");
	for (size_t i = 0; i < netcount; i++){
		cs2.Format(L"%d ", subnetList[i]);
		cs1 += cs2;
	}

	netWindow.inputMessage.push_back(cs1);
	netWindow.inputNets = subnetList;
	netWindow.netType = 0;

	if (netWindow.DoModal() == IDOK) {
		netcount = netWindow.newNet;  // NOTE reusing netcount as new net id
		newnetType = netWindow.netType;
		mybn.AddSubnet(netcount, newnetType);
		cs2.Format(L"Add subnet %d type '%S'",netcount, (newnetType == 0)?"MS/TP":"UDP/IP");
		m_status.AddString(cs2);
		UpdateNetworkTree();

		hti = mybn.GetSubnetTreepos(netcount);
		if (hti != 0) m_net_tree.Expand(hti, TVE_EXPAND);
	}

	//m_status.AddString(L"Creating AI Object");
	//myDev.AddObject(0);
	//m_status.AddString(L"Creating AO Object");
	//myDev.AddObject(1);
	//m_status.AddString(L"Creating AV Object");
	//myDev.AddObject(2);
	//
	//objString = myDev.GetObjectStrings();
	//m_status.AddString(L"Device info:");
	//for (size_t i = 0; i < objString.size(); i++)
	//{
	//	cs1.Format(L"%S",objString[i].c_str());
	//	m_status.AddString(cs1);
	//}
}


void CBACnetDeviceEmulatorDlg::OnBnClickedAddController()
{
	// TODO: Add your control notification handler code here
	AddNewController myAnc;
	int conType = 0;  // this is an index
	int subnetIndex = 0;
	int conID = 0;
	int conCount = 1;
	int addTemplate = 0;
	int msMAC = 0;  // MSTP MAC address
	CString cs1;
	std::string libName;
	std::vector<CString> objString;
	std::vector<int> subnetList = mybn.GetSubnets();
	std::vector<int> idList = mybn.GetControllerDeviceIDs();
	std::vector<std::string> templateNames = mybn.GetTemplateNames();
	std::vector<int> templateIDs = mybn.GetTemplateDevices();
	DevAddr myda = {};
	std::vector<std::string>	subMessages;
	size_t i = 0;

	// set subnet list
	myAnc.SetSubnetList(subnetList);

	// set controller id list
	myAnc.SetDeviceIDList(idList);

	// set template names
	myAnc.SetTemplateNames(templateNames);
	// set an input message
	//cs1.Format(L"Select controller ID, subnet, and type.");
	objString.push_back(L"Select controller ID, subnet, and type.");
	myAnc.SetInputMessage(objString);

	// set MAC lists
	for (i = 0; i < subnetList.size(); i++){
		//mybn.getcon
	}

	if (myAnc.DoModal() == IDOK) {
		conType = myAnc.controllerType;
		subnetIndex = myAnc.subnetSel;
		conID = myAnc.newDevID;
		addTemplate = myAnc.newIsTemplate;
		msMAC = myAnc.mstpMAC;
		libName = myAnc.libraryName;

		if (myAnc.multCheck == 1) conCount = myAnc.multcount;
		for (size_t i = 0; i < conCount; i++){
			if (mybn.AddController(conID+i, subnetList[subnetIndex])) {
				mybn.SetControllerTemplate(conID+i, templateIDs[ conType]);
				mybn.GetControllerAddressInfo(conID + i, &myda);
				myda.mac_device_dec = msMAC;
				myda.mac_device[0] = msMAC;
				myda.mac_device_len = 1;
				sprintf_s(myda.mac_device_pr, 14, "0x%02X", msMAC);
				mybn.SetControllerAddressInfo(conID + i, &myda);
				if (libName.size() > 5) mybn.SetLibrary(conID + i, libName);
				msMAC++;
			}
			if (addTemplate) {
				mybn.SetTemplate(conID + i, 1);
				cs1.Format(L"Add template ID %d type '%S' net %d", conID + i,templateNames[ conType].c_str(), subnetList[subnetIndex]);
			} else {
				cs1.Format(L"Add controller ID %d type '%S' net %d", conID + i, templateNames[conType].c_str(), subnetList[subnetIndex]);
			}
			m_status.AddString(cs1);
		}
		UpdateNetworkTree();

		// expand new controllers in tree
		HTREEITEM hti = mybn.GetSubnetTreepos(subnetList[subnetIndex]);
		if (hti != 0) m_net_tree.Expand(hti, TVE_EXPAND);

		subMessages = mybn.GetMessageStrings();
		for (size_t i = 0; i < subMessages.size(); i++){
			m_status.AddString(CA2T(subMessages[i].c_str()));
		}
	}
}  // end CBACnetDeviceEmulatorDlg::OnBnClickedAddController


void CBACnetDeviceEmulatorDlg::OnBnClickedTestButton2()
{
	// TODO: Add your control notification handler code here
	//BACnetNetwork mybn;
	std::vector<std::string> objString;
	CString cs1;
	BACvalue bv = {};
	std::vector<int> snets = { 41, 42, 43, 50, 51 };
	std::vector<int> ccounts = { 6, 6, 6, 6, 6 };
	DevAddr myDevAddr = {};

	int ii = 0;
	int cid = 0;

	m_status.AddString(L"Adding simulated subnets and controllers...");
	for (size_t i = 0; i < snets.size(); i++){
		ii = snets[i];
		cs1.Format(L"Adding subnet %d", ii);
		m_status.AddString(cs1);
		cid = ii * 100 + 01;
		mybn.AddSubnet(ii);
		mybn.AddController(cid, ii);  // AHU Note will have standard objects added
		memset(&bv, 0, sizeof(BACvalue));
		bv.type = 7;
		strcpy_s(bv.value.t, "Evilcorp AHU Type 1");
		bv.length = strlen(bv.value.t);
		mybn.SetControllerObjectProperty(cid, 8, ii * 100 + 01, (int)BACenums::BACProp::en_MODEL_NAME, &bv);
		// set MAC address on subnet
		mybn.GetControllerAddressInfo(cid, &myDevAddr);
		myDevAddr.mac_device[0] = i+1;
		myDevAddr.mac_device_len = 1;
		mybn.SetControllerAddressInfo(cid, &myDevAddr);

		for (size_t m = 1; m <= 8; m++) {
			mybn.AddControllerObject(cid, 0, m); // Add AI
			mybn.AddControllerObject(cid, 1, m); // Add AO
			mybn.AddControllerObject(cid, 2, m); // Add AV
			mybn.AddControllerObject(cid, 19, m); // Add MV

			bv.length = 4;
			sprintf_s(bv.value.t, 100, "AI%02d", m); mybn.SetControllerObjectProperty(cid, 0, m, (int)BACenums::BACProp::en_OBJECT_NAME, &bv);
			sprintf_s(bv.value.t, 100, "AO%02d", m); mybn.SetControllerObjectProperty(cid, 1, m, (int)BACenums::BACProp::en_OBJECT_NAME, &bv);
			sprintf_s(bv.value.t, 100, "AV%02d", m); mybn.SetControllerObjectProperty(cid, 2, m, (int)BACenums::BACProp::en_OBJECT_NAME, &bv);
			sprintf_s(bv.value.t, 100, "MV%02d", m); mybn.SetControllerObjectProperty(cid, 19, m, (int)BACenums::BACProp::en_OBJECT_NAME, &bv);
		}

		strcpy_s(bv.value.t, "Evilcorp VAV Type 1b");  // save model name to bv
		for (size_t k = 0; k < ccounts[i]; k++){
			cid = ii * 100 + 10 + k;
			cs1.Format(L"Adding controller %d:%d", ii,cid);
			m_status.AddString(cs1);
			if (!mybn.AddController(cid, ii)) {  // VAV Note will have standard objects added
				cs1.Format(L"ERROR adding controller!");
				continue;
			}

			mybn.GetControllerAddressInfo(cid, &myDevAddr);
			myDevAddr.mac_device[0] = 10+k;
			myDevAddr.mac_device_len = 1;
			mybn.SetControllerAddressInfo(cid, &myDevAddr);
		
			bv.length = strlen(bv.value.t); // set model name
			mybn.SetControllerObjectProperty(cid, 8, ii * 100 + 10+ k, (int)BACenums::BACProp::en_MODEL_NAME, &bv);
			
			for (size_t m = 1; m <= 5; m++){
				mybn.AddControllerObject(cid,  0, m); // Add AI
				mybn.AddControllerObject(cid,  1, m); // Add AO
				mybn.AddControllerObject(cid,  2, m); // Add AV
				mybn.AddControllerObject(cid, 19, m); // Add MV

				bv.length = 4;
				sprintf_s(bv.value.t, 100, "AI%02d", m); mybn.SetControllerObjectProperty(cid, 0, m, (int)BACenums::BACProp::en_OBJECT_NAME, &bv);
				sprintf_s(bv.value.t, 100, "AO%02d", m); mybn.SetControllerObjectProperty(cid, 1, m, (int)BACenums::BACProp::en_OBJECT_NAME, &bv);
				sprintf_s(bv.value.t, 100, "AV%02d", m); mybn.SetControllerObjectProperty(cid, 2, m, (int)BACenums::BACProp::en_OBJECT_NAME, &bv);
				sprintf_s(bv.value.t, 100, "MV%02d", m); mybn.SetControllerObjectProperty(cid,19, m, (int)BACenums::BACProp::en_OBJECT_NAME, &bv);
			}
			strcpy_s(bv.value.t, "Evilcorp VAV Type 1b");
			bv.length = strlen(bv.value.t);
			mybn.SetControllerObjectProperty(cid, 8, cid, (int)BACenums::BACProp::en_MODEL_NAME, &bv);
		}
		//mybn.AddDevice(ii*100+11, ii);  // Note will have standard objects added
		//mybn.AddDevice(ii*100+12, ii);  // Note will have standard objects added
		//mybn.AddDevice(ii*100+13, ii);  // Note will have standard objects added
		//mybn.AddDevice(ii*100+14, ii);  // Note will have standard objects added
		//mybn.AddDevice(ii*100+15, ii);  // Note will have standard objects added
		//mybn.AddDeviceObject(ii*100+01, 2, 1); // Add AV01
		//mybn.AddDeviceObject(ii*100+10, 2, 1); // Add AV01
		//mybn.AddDeviceObject(ii*100+11, 2, 1); // Add AV01
		//mybn.AddDeviceObject(ii*100+12, 2, 1); // Add AV01
		//mybn.AddDeviceObject(ii*100+13, 2, 1); // Add AV01
		//mybn.AddDeviceObject(ii*100+14, 2, 1); // Add AV01
		//mybn.AddDeviceObject(ii*100+15, 2, 1); // Add AV01

		//mybn.SetControllerObjectProperty(ii * 100 + 11, 8, ii * 100 + 11, (int)BACenums::BACProp::en_MODEL_NAME, &bv);
		//mybn.SetControllerObjectProperty(ii * 100 + 12, 8, ii * 100 + 12, (int)BACenums::BACProp::en_MODEL_NAME, &bv);
		//mybn.SetControllerObjectProperty(ii * 100 + 13, 8, ii * 100 + 13, (int)BACenums::BACProp::en_MODEL_NAME, &bv);
		//mybn.SetControllerObjectProperty(ii * 100 + 14, 8, ii * 100 + 14, (int)BACenums::BACProp::en_MODEL_NAME, &bv);
		//mybn.SetControllerObjectProperty(ii * 100 + 15, 8, ii * 100 + 15, (int)BACenums::BACProp::en_MODEL_NAME, &bv);
	}

	//objString = mybn.GetControllerStrings(3201);
	//m_status.AddString(L"Device 3201 info:");
	//for (size_t i = 0; i < objString.size(); i++)
	//{
	//	cs1.Format(L"%S",objString[i].c_str());
	//	m_status.AddString(cs1);
	//}
	//
	//objString = mybn.GetControllerStrings(3211);
	//m_status.AddString(L"Device 3211 info:");
	//for (size_t i = 0; i < objString.size(); i++)
	//{
	//	cs1.Format(L"%S", objString[i].c_str());
	//	m_status.AddString(cs1);
	//}

	//mybn.AddSubnet(33);
	//mybn.AddSubnet(34);
	//mybn.AddSubnet(35);
	//mybn.AddSubnet(36);

	UpdateNetworkTree();
	m_status.AddString(L"Finished adding subnets and controllers.");
}  // 


void CBACnetDeviceEmulatorDlg::OnBnClickedReadFile()
{
	// TODO: Add your control notification handler code here
	CString			pathName;
	std::wifstream	ofop;
	std::vector<std::string> sarr;  // string array

	CFileDialog fileDlg(TRUE, L"xml", pathName, OFN_FILEMUSTEXIST || OFN_READONLY, L"XML Files (*.xml)|*.xml||");

	try {
		if (fileDlg.DoModal() == IDOK) {
			pathName = fileDlg.GetPathName();
			CT2A path_str(pathName);

			theApp.ReadConfigFile(path_str.m_psz);

			//if (theApp.myFPTM.ReadFromFile(path_str.m_psz) == 1) {
			//	m_status.AddString(L"Config read from file (no error):");
			//	//m_status.AddString(b);
			//}
			//else {
			//	m_status.AddString(L"Error reading config file.");
			//}
		}
	}
	catch (const std::exception& e) {
		// Log the error message
		CString err;
		m_status.AddString(L"ERROR: Caught exception in OnFileReadfromfile!");
		err.Format(L"ERROR: %S", e.what());
		m_status.AddString(err);
	}
	catch (...) {
		m_status.AddString(L"Problem opening read file dialog- try again.");
	}
	
	UpdateNetworkTree();
	sarr = theApp.GetStatusStrings();
	for (size_t i = 0; i < sarr.size(); i++){
		pathName = sarr[i].c_str();
		m_status.AddString(pathName);
	}

}

void CBACnetDeviceEmulatorDlg::OnBnClickedSendIam()
{
	// TODO: Add your control notification handler code here
	std::string ss1;
	std::string ss2;
	std::wstring ws1;
	size_t st = 0;
	size_t i = 0;
	size_t j = 0;
	size_t k = 0;
	wchar_t mtext[100] = {};
	CString cs1;
	CString cs2;
	BACTreeCtrl* tree = NULL;
	std::vector<BACvalue> objArr;  // object id array
	std::vector<int> snl; // sub net list
	std::vector<int> devl; // device list
	std::vector<HTREEITEM> htl;  // htree item list
	std::vector<std::string> stringList;  // property info strings
	BACvalue bvl;
	int vendor = 0;
	int segsup = 1;
	int devID = 0;
	DevAddr myDevAddr;
	DevAddr rtrDevAddr = {};
	DevAddr nullAddr = {};
	
	memset(&bvl, 0, sizeof(BACvalue));

	SendMessage(IDC_NET_TREE, WM_SETREDRAW, FALSE);  // freeze redraw while updating

	// parse through subnets
	snl = mybn.GetSubnets();  // retrieve list of subnets

	// devl, snl and htl used to place controllers
	//devl = mybn.GetDeviceIDs();
	if (mybn.GetHostAddressInfo(&rtrDevAddr) == 0) {  // big problem!
		m_status.AddString(L"ERROR in SendIAm- no host controller!");
		return;  
	}
	//BACfuncs::SendIAMDev(&rtrDevAddr, &nullAddr, segsup, vendor);
	for (i = 1; i < snl.size(); i++) {
		// find htl item for dev list subnet
		devl = mybn.GetSubnetDevices(snl[i]);
		for (j = 0; j < devl.size(); j++) {
			// vendor
			if (mybn.GetControllerObjectProperty(devl[j], 8, devl[j], (int)BACenums::BACProp::en_VENDOR_IDENTIFIER, &bvl) == 1) {
				//cs1.Format(L"DevId: %d  Model Name: %S", devl[j], bvl.value.t);
				vendor = bvl.value.i;
			} else {
				//cs1.Format(L"DevId: %d  Model Name: NA", devl[j]);
				vendor = 1;
			}
			segsup = 1024;
			if (mybn.GetControllerAddressInfo(devl[j], &myDevAddr) == 1) {  // MAG TODO some devaddr are net filled out, call GetDeviceInfo to fill in
				BACfuncs::SendIAMDev(&myDevAddr, &rtrDevAddr, segsup, vendor);
			}
		}
	}
	
	SendMessage(IDC_NET_TREE, WM_SETREDRAW, TRUE);  // allow redraw after updating

	return;
} // end OnBnClickedSendIam


void CBACnetDeviceEmulatorDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default

	CDialogEx::OnTimer(nIDEvent);
	std::vector<std::string> sarr;
	CString cs1;

	switch (nIDEvent)
	{
	case 1: // BACnet timer
		mybn.CheckForBACnetMessages();
		mybn.SendBACnetMessages();

		sarr = theApp.GetStatusStrings();
		for (size_t i = 0; i < sarr.size(); i++) {
			cs1 = sarr[i].c_str();
			m_status.AddString(cs1);
		}

		UpdateMessageStrings();

		break;
	case 10: // one time call to add base controller and init tree display
		// MAG NOTE this is done in timer instead of Network init because the namespace variables are not initialized then.
		mybn.AddBaseController();  
		UpdateNetworkTree(); // show host/base controller
		KillTimer(10);  // only gets called once on startup
		break;
	case 11: // update FOCUS window, probably because of a write request
		KillTimer(11);
		UpdateFocusTree(-1); /// just update with last controller ID
		break;
	default:
		break;
	}
}

void 
CBACnetDeviceEmulatorDlg::UpdateMessageStrings()
{
	std::vector<std::string> sarr;  // string array
	CString			cmsg;
	int idx = 0;
	int cID = 0;

	sarr = mybn.GetMessageStrings();
	for (size_t i = 0; i < sarr.size(); i++) {
		cmsg = sarr[i].c_str();
		// MAG 260706 add check for internal messages
		// NOTE all write requests received will have this message
		if (cmsg.Left(2).Compare(L"##") == 0) {
			cmsg = sarr[i].erase(0, 2).c_str();  // remove leading "##"
			if (cmsg.Left(3).Compare(L"UPD") == 0) {
				idx = cmsg.Find(':');
				if (idx != -1) {
					idx++;
					cmsg = cmsg.Mid(idx);
					cID = _ttoi(cmsg);
					if (cID == prevFocusID) UpdateFocusTree(cID);
				}
			}
		}
		else {
			m_status.AddString(cmsg);  // normal string, just write to output
		}
	}

	return;
}


void CBACnetDeviceEmulatorDlg::OnBnClickedSaveFile()
{
	// TODO: Add your control notification handler code here
	CString			pathName;
	CString			cmsg;
	std::wifstream	ofop;
	std::vector<std::string> sarr;  // string array
	int idx = 0;
	int cID = 0;

	CFileDialog fileDlg(FALSE, L"xml", pathName, OFN_OVERWRITEPROMPT || OFN_OVERWRITEPROMPT , L"XML Files (*.xml)|*.xml||");

	try {
		if (fileDlg.DoModal() == IDOK) {
			pathName = fileDlg.GetPathName();
			CT2A path_str(pathName);

			theApp.SaveConfigFile(path_str.m_psz);

			UpdateMessageStrings();

			//if (theApp.myFPTM.ReadFromFile(path_str.m_psz) == 1) {
			//	m_status.AddString(L"Config read from file (no error):");
			//	//m_status.AddString(b);
			//}
			//else {
			//	m_status.AddString(L"Error reading config file.");
			//}
		}
	}
	catch (const std::exception& e) {
		// Log the error message
		CString err;
		m_status.AddString(L"ERROR: Caught exception in OnFileReadfromfile!");
		err.Format(L"ERROR: %S", e.what());
		m_status.AddString(err);
	}
	catch (...) {
		m_status.AddString(L"Problem opening read file dialog- try again.");
	}

	UpdateNetworkTree();
	sarr = theApp.GetStatusStrings();
	for (size_t i = 0; i < sarr.size(); i++) {
		pathName = sarr[i].c_str();
		m_status.AddString(pathName);
	}

}


// MAG 260608 add menu initiated version
// copied from OnBnClickedReadFile
void CBACnetDeviceEmulatorDlg::OnFileOpenconfigfile()
{
	// TODO: Add your command handler code here
	CString			pathName;
	std::wifstream	ofop;
	std::vector<std::string> sarr;  // string array

	CFileDialog fileDlg(TRUE, L"xml", pathName, OFN_FILEMUSTEXIST || OFN_READONLY, L"XML Files (*.xml)|*.xml||");

	try {
		if (fileDlg.DoModal() == IDOK) {
			pathName = fileDlg.GetPathName();
			CT2A path_str(pathName);

			theApp.ReadConfigFile(path_str.m_psz);
		}
	}
	catch (const std::exception& e) {
		// Log the error message
		CString err;
		m_status.AddString(L"ERROR: Caught exception in OnFileReadfromfile!");
		err.Format(L"ERROR: %S", e.what());
		m_status.AddString(err);
	}
	catch (...) {
		m_status.AddString(L"Problem opening read file dialog- try again.");
	}

	UpdateNetworkTree();
	sarr = theApp.GetStatusStrings();
	for (size_t i = 0; i < sarr.size(); i++) {
		pathName = sarr[i].c_str();
		m_status.AddString(pathName);
	}
}


// MAG 260608 add menu initiated version
// copied from OnBnClickedSaveFile
void CBACnetDeviceEmulatorDlg::OnFileSaveconfigfile()
{
	// TODO: Add your command handler code here
	CString			pathName;
	CString			cmsg;
	std::wifstream	ofop;
	std::vector<std::string> sarr;  // string array

	CFileDialog fileDlg(FALSE, L"xml", pathName, OFN_OVERWRITEPROMPT , L"XML Files (*.xml)|*.xml||");

	try {
		if (fileDlg.DoModal() == IDOK) {
			pathName = fileDlg.GetPathName();
			CT2A path_str(pathName);

			theApp.SaveConfigFile(path_str.m_psz);

			UpdateMessageStrings();
		}
	}
	catch (const std::exception& e) {
		// Log the error message
		CString err;
		m_status.AddString(L"ERROR: Caught exception in OnFileReadfromfile!");
		err.Format(L"ERROR: %S", e.what());
		m_status.AddString(err);
	}
	catch (...) {
		m_status.AddString(L"Problem opening read file dialog- try again.");
	}

	UpdateNetworkTree();
	sarr = theApp.GetStatusStrings();
	for (size_t i = 0; i < sarr.size(); i++) {
		pathName = sarr[i].c_str();
		m_status.AddString(pathName);
	}
}

void CBACnetDeviceEmulatorDlg::OnDropFiles(HDROP hDropInfo)
{
	// TODO: Add your message handler code here and/or call default
	int filecount = 0;
	int i = 0;
	int j = 0;
	TCHAR filename[MAX_PATH];
	char filename2[MAX_PATH];
	CString fb;
	std::vector<std::string> sarr;  // string array

	filecount = DragQueryFile(hDropInfo, 0xFFFFFFFF, filename, MAX_PATH);

	for (i = 0; i < filecount; i++) {
		j = DragQueryFile(hDropInfo, i, filename, MAX_PATH);

		WideCharToMultiByte(CP_ACP, 0, filename, MAX_PATH, filename2, MAX_PATH, NULL, NULL);
		j = theApp.ReadConfigFile(filename2);
		if (j != 1) {
			fb.Format(L"Error reading config file: %S", filename2);
			m_status.AddString(fb);
		} // nothing to do here if read properly, comments are added in subroutine
	}

	UpdateNetworkTree();
	sarr = theApp.GetStatusStrings();
	for (size_t i = 0; i < sarr.size(); i++) {
		fb = sarr[i].c_str();
		m_status.AddString(fb);
	}

	m_status.SetCurSel(m_status.GetCount() - 1);

	CDialogEx::OnDropFiles(hDropInfo);
}

void CBACnetDeviceEmulatorDlg::OnCbnSelchangeSelectIp()
{
	// TODO: Add your control notification handler code here
	CString cs1;
	CString cs2;
	int i = m_select_ip.GetCurSel();

	BACfuncs::SetDefaultAdapter(i);
	m_select_ip.GetLBText(i, cs2);
	cs1.Format(L"Change default adapter to %d:%s", i, cs2.GetString());
	m_status.AddString(cs1);

	// need to update default controller[0] address
	mybn.ResetDefaultControllerInfo();
}


void CBACnetDeviceEmulatorDlg::OnBnClickedDelController()
{
	// TODO: Add your control notification handler code here
	std::vector<int>		devIDList;
	int						delIndex; // index in devIDList of controller to delete
	DeleteControllerDialog	dcd;
	CString					cs1;

	devIDList = mybn.GetControllerDeviceIDs(1);
	for (size_t i = 0; i < devIDList.size(); i++){
		dcd.devList.push_back(devIDList[i]);
	}
	if (dcd.DoModal() == IDOK) {
		delIndex = dcd.selectedToDie;
		mybn.DelController(devIDList[delIndex]);
		cs1.Format(L"Selected for deletion: Device ID %d.", devIDList[delIndex]);
		m_status.AddString(cs1);
		UpdateNetworkTree();
	} else {
		m_status.AddString(L"Delete controller cancelled.");
	}
}

void CBACnetDeviceEmulatorDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	// MAG 260717 function not needed
/*	CRect myr;
	CRect treeRect;
	int vertPos = 0;

	// work off position of "add subnet" button   xxx bitmap holder
	CWnd* ptr = GetDlgItem(IDC_TEST_BUTTON1);// IDB_BITMAP_HOLDER);
	if (ptr == nullptr) return;
	ptr->GetWindowRect(&myr);
	ScreenToClient(&myr);

	vertPos = myr.top;
	m_net_tree.GetWindowRect(&treeRect);
	ScreenToClient(&treeRect);
//	m_net_tree.MoveWindow(treeRect.left, treeRect.top, treeRect.right, vertPos - 10, true);
*/
}

void CBACnetDeviceEmulatorDlg::OnBnClickedAddObject()
{
	// TODO: Add your control notification handler code here
	AddNewObject			myno;
	std::vector<CString>	listObjects;
	std::vector<int>		listIDs;
	CString					tobj;
	
	int						newIDIndex = 0;
	int						newObjIndex = 0;
	int						newInst = 0;
	int						newCount = 1;

	listIDs = mybn.GetControllerDeviceIDs();
	myno.devIDList = listIDs;

	for (size_t i = 0; i < BAClabels::ObjectLabels.size()-1; i++){// last entry is ERROR_OBJECT, do not include as option
		tobj = BAClabels::ObjectLabels[i].c_str();
		listObjects.push_back(tobj);
	}
	myno.objectLabelList = listObjects;

	if (myno.DoModal() != IDOK) return;

	newIDIndex = myno.selectedID;
	newObjIndex = myno.selectedObject;  // note this index is the same as object type as all objects are listed
	newInst = myno.selectedInstance;
	newCount = myno.selectedCount;

	if (newCount >= 500) {
		tobj.Format(L"Add to controller: %d Object: %S Count: %d", listIDs[newIDIndex], BAClabels::ObjectLabels[newObjIndex].c_str(), newCount);
		m_status.AddString(tobj);

	}
	for (size_t i = 0; i < newCount; i++){
		if (mybn.AddControllerObject(listIDs[newIDIndex], newObjIndex, newInst+i) == 1) {
			if (newCount < 500) {
				tobj.Format(L"Add to controller %d Object %S:%d", listIDs[newIDIndex], BAClabels::ObjectLabels[newObjIndex].c_str(), newInst + i);
				m_status.AddString(tobj);
			}
		} else {
			tobj.Format(L"ERROR: Could not add new object %d.",newInst+i);  // show errors regardless of newCount value
			m_status.AddString(tobj);
		}
	}
	
	UpdateNetworkTree();
	if (prevFocusID == listIDs[newIDIndex]) UpdateFocusTree(prevFocusID);  // only updates if modified controller is displayed
}

void CBACnetDeviceEmulatorDlg::OnLbnSelchangeStatus()
{
	// TODO: Add your control notification handler code here
	std::vector<std::string> wt;// window text
	CString lt; // line text
	std::string sst;
	int scount = m_status.GetCount();

	if (scount == 0) return;

	for (size_t i = 0; i < scount; i++){
		m_status.GetText(i, lt);
		sst = CT2CA( lt);
		wt.push_back(sst);
	}


	// second method
	// Get the standard Windows temporary directory path
	wchar_t tempPath[MAX_PATH];
	if (GetTempPathW(MAX_PATH, tempPath) == 0) {
		return ;
	}

	// Create a unique temporary filename
	wchar_t tempFile[MAX_PATH];
	if (GetTempFileNameW(tempPath, L"BDE", 0, tempFile) == 0) {
		return ;
	}

	// Write the vector contents to the temporary file
	std::ofstream outFile(tempFile);
	if (!outFile) {
		return ;
	}

	for (const auto& line : wt) {
		outFile << line << "\n";
	}
	outFile.close();

	// Construct the command to open Notepad with the file
	// Wrapping the path in quotes handles spaces safely
	std::wstring command = L"notepad.exe \"" + std::wstring(tempFile) + L"\"";

	// Prepare structures to launch the process safely
	STARTUPINFOW si = { sizeof(si) };
	PROCESS_INFORMATION pi;

	// Launch Notepad passing the file path as an argument
	if (CreateProcessW(
		nullptr,            // Application name
		&command[0],        // Command line arguments
		nullptr,            // Process attributes
		nullptr,            // Thread attributes
		FALSE,              // Inherit handles
		0,                  // Creation flags
		nullptr,            // Environment
		nullptr,            // Current directory
		&si,                // Startup info
		&pi                 // Process information
	))
	{
		// Clean up process handles (keeps Notepad running independently)
		//        CloseHandle(pi.hProcess);
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
	}
	// second method

	/* first method
	// Open clipboard and associate it with current process
	std::string combinedText = std::accumulate(
		std::next(wt.begin()), wt.end(), wt[0],
		[](const std::string& a, const std::string& b) {
			return a + "\r\n" + b;
		}
	);
	if (!OpenClipboard()) {
		return;
	}

	// Clear existing clipboard contents
	EmptyClipboard();

	// Allocate global memory for the joined string (including null terminator)
	HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, combinedText.size() + 1);
	if (!hMem) {
		CloseClipboard();
		return;
	}

	// Lock memory to get a pointer and copy the text
	char* pMem = static_cast<char*>(GlobalLock(hMem));
	if (pMem) {
		memcpy(pMem, combinedText.c_str(), combinedText.size() + 1);
	}
	GlobalUnlock(hMem);

	// Place the handle on the clipboard as standard text
	if (!SetClipboardData(CF_TEXT, hMem)) {
		GlobalFree(hMem);
		CloseClipboard();
		return;
	}

	// Close clipboard to make it available to other apps
	CloseClipboard();

	system("notepad.exe");
	*/


	return;
}
