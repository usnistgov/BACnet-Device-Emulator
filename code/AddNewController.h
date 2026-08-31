#pragma once
#include "afxdialogex.h"


// AddNewController dialog

class AddNewController : public CDialogEx
{
	DECLARE_DYNAMIC(AddNewController)

public:
	AddNewController(CWnd* pParent = nullptr);   // standard constructor
	virtual ~AddNewController();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_AddNewController };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	std::vector<int>		subnetList;	// list of existing subnets. 
	std::vector<int>		devidList;	// list of existing device IDs. Compare input to this list for validity check.
	std::vector<CString>	tNames;	// list of template names
	std::vector<CString>	inputMessage;  // copy to status on start
	// 2d vector, first param is subnet index, i.e. devMACList[subnet_index][index_in_subnet].
	std::vector<std::vector<int>>		devMACList;	// list of existing device MACs. Compare input to this list for validity check.

	CString					lastCountValue;  // holds contents of count window

	DECLARE_MESSAGE_MAP()
public:
	int						newDevID;	// save value of new device ID here
	// NOTE- type is used to select the object template used, it is not saved or part of controller data
	int						controllerType; // 0=generic 1=AHU 2=VAV 3=Boiler 4=Chiller 5=Pump 6=misc i/o (10 AI&AO 20 AV 5 BI/BO 10 BV)
	int						subnetSel;  // INDEX of selected subnet
	int						multCheck;	// is multiple checked?
	int						multcount;	// if multiple is checked, add this many
	int						newIsTemplate;// 0=no, 1=yes
	int						mstpMAC;	// MAC address on mstp network
	std::string				libraryName;  // if a DLL is selected
	
	CListBox m_status;
	virtual BOOL OnInitDialog();
	CComboBox m_controller_type;
	CComboBox m_controller_net;
	CEdit m_controller_devid;
	afx_msg void OnChangeControllerDevid();
	CButton m_IDOK;
	int CheckDevID();  // checks that the device id entered in box is not in devidList
	int CheckMAC();

	void SetSubnetList(std::vector<int> nl) { subnetList = nl; };
	void SetDeviceIDList(std::vector<int> nl) { devidList = nl; };
	void AddMACList(std::vector<int> nl) { devMACList.push_back(nl); };  // Note subnets are added one by one, in order of index
	void SetTemplateNames(std::vector < std::string> nl);// { tNames = nl; };
	void SetInputMessage(std::vector<CString> nm) { inputMessage = nm; };
	afx_msg void OnClickedMultipleControllers();
	CButton m_add_multiple;
	CEdit m_controller_count;
	afx_msg void OnChangeControllerCount();
	CButton m_addAsTemplate;
	afx_msg void OnBnClickedMultipleControllers2();
	afx_msg void OnCbnSelchangeControllerType();
	CEdit m_controller_mac;
	afx_msg void OnEnChangeControllerMac();
	afx_msg void OnEnKillfocusControllerMac();
	afx_msg void OnEnKillfocusControllerDevid();
	afx_msg void OnEnKillfocusControllerCount();
	afx_msg void OnBnClickedLibrarySelect();
	CEdit m_library_name;
	afx_msg void OnCbnKillfocusAddObjDevidList();
};
