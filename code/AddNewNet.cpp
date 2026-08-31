// AddNewNet.cpp : implementation file
//

#include "pch.h"
#include "BACnet Device Emulator.h"
#include "afxdialogex.h"
#include "AddNewNet.h"


// AddNewNet dialog

IMPLEMENT_DYNAMIC(AddNewNet, CDialogEx)

AddNewNet::AddNewNet(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_AddNewNet, pParent)
{
	newNet = 0;
	netType = 0;
}

AddNewNet::~AddNewNet()
{
}

void AddNewNet::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_NEWNET_STATUS, m_newnet_status);
	DDX_Control(pDX, IDC_NEW_NET_EDIT, m_new_net_edit);
	DDX_Control(pDX, IDOK, m_IDOK);
	DDX_Control(pDX, IDC_NETWORK_TYPE_SELECT, m_network_type_select);
}


BEGIN_MESSAGE_MAP(AddNewNet, CDialogEx)
	ON_EN_CHANGE(IDC_NEW_NET_EDIT, &AddNewNet::OnEnChangeNewNetEdit)
	ON_CBN_SELCHANGE(IDC_NETWORK_TYPE_SELECT, &AddNewNet::OnCbnSelchangeNetworkTypeSelect)
	ON_EN_KILLFOCUS(IDC_NEW_NET_EDIT, &AddNewNet::OnEnKillfocusNewNetEdit)
END_MESSAGE_MAP()


// AddNewNet message handlers

void AddNewNet::OnEnChangeNewNetEdit()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// MAG note- acts the same as killfocus, but with no messages
	CString netText;
	int		netID;

	m_new_net_edit.GetWindowText(netText);
	netID = _ttoi(netText);

	// Check range 1-65534
	if((netID <= 0) || (netID > 65534)){
		m_IDOK.EnableWindow(0); // disable window
		//m_newnet_status.AddString(L"ERROR: Network number must be in range 0-65534.");
		return;
	}

	auto it = std::find(inputNets.begin(), inputNets.end(), netID);
	if (it != inputNets.end()) { // net is in list, already exists
		m_IDOK.EnableWindow(0); // disable window
		//m_newnet_status.AddString(L"ERROR: Entered network number is in use.");
		return;
	}
	newNet = netID;
	m_IDOK.EnableWindow(1);
	//netText.Format(L"New network number changed to %d.", newNet);
	//m_newnet_status.AddString(netText);
}


void AddNewNet::OnEnKillfocusNewNetEdit()
{
	// TODO: Add your control notification handler code here
	CString netText;
	int		netID;

	m_new_net_edit.GetWindowText(netText);
	netID = _ttoi(netText);

	// Check range 1-65534
	if ((netID <= 0) || (netID > 65534)) {
		m_IDOK.EnableWindow(0); // disable window
		m_newnet_status.AddString(L"ERROR: Network number must be in range 0-65534.");
		return;
	}

	auto it = std::find(inputNets.begin(), inputNets.end(), netID);
	if (it != inputNets.end()) { // net is in list, already exists
		m_IDOK.EnableWindow(0); // disable window
		m_newnet_status.AddString(L"ERROR: Entered network number is in use.");
		return;
	}
	newNet = netID;
	m_IDOK.EnableWindow(1);
	netText.Format(L"Change network number to %d.", newNet);
	m_newnet_status.AddString(netText);
}


BOOL AddNewNet::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	for (size_t i = 0; i < inputMessage.size(); i++)
	{
		m_newnet_status.AddString(inputMessage[i]);
	}

	m_network_type_select.AddString(L"MS/TP");
	m_network_type_select.AddString(L"UDP/IP");
	m_network_type_select.SetCurSel(netType);

	m_new_net_edit.SetFocus();

	return FALSE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void AddNewNet::OnCbnSelchangeNetworkTypeSelect()
{
	// TODO: Add your control notification handler code here
	int i = m_network_type_select.GetCurSel();
	CString cs1;
	CString cs2;
	
	m_network_type_select.GetLBText(i, cs1);
	cs2.Format(L"Change network type to %s", cs1.GetString());
	m_newnet_status.AddString(cs2);
}

