
// BACnet Device EmulatorDlg.h : header file
//

#pragma once

#include "BACnetController.h"
#include "AddNewNet.h"
#include "AddNewController.h"
#include "ModifyPropValue.h"
#include "BACTreeCtrl.h"
#include "BACnet Device EmulatorDlg.h"
#include "DeleteControllerDialog.h"
#include "AddNewObject.h"
#include <numeric>

// CBACnetDeviceEmulatorDlg dialog
class CBACnetDeviceEmulatorDlg : public CDialogEx
{
// Construction
public:
	CBACnetDeviceEmulatorDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BACNET_DEVICE_EMULATOR_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	int prevFocusID;  // previous focus ID

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CListBox m_status;
	CListBox m_status_focus;
	afx_msg void OnBnClickedTestButton1();
	BACTreeCtrl m_net_tree;		// left tree, showing network, controllers, objects
	BACTreeCtrl m_tree_focus;	// right tree, focusing on one controller, objects, properties
	void UpdateNetworkTree();
	void UpdateFocusTree(int devID);

	void UpdateMessageStrings();

	afx_msg void OnBnClickedTestButton2();
	afx_msg void OnBnClickedReadFile();
	afx_msg void OnBnClickedSendIam();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedAddController();
	afx_msg void OnBnClickedSaveFile();
	afx_msg void OnFileOpenconfigfile();
	afx_msg void OnFileSaveconfigfile();
	afx_msg void OnDropFiles(HDROP hDropInfo);
	CComboBox m_select_ip;
	CStatic m_select_network_adapter_label;
	afx_msg void OnCbnSelchangeSelectIp();
	afx_msg void OnBnClickedDelController();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedAddObject();
	afx_msg void OnLbnSelchangeStatus();
};
