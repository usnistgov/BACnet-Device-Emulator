#pragma once
#include "afxdialogex.h"


// AddNewNet dialog

class AddNewNet : public CDialogEx
{
	DECLARE_DYNAMIC(AddNewNet)

public:
	AddNewNet(CWnd* pParent = nullptr);   // standard constructor
	virtual ~AddNewNet();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_AddNewNet };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CListBox m_newnet_status;
	CEdit m_new_net_edit;
	CButton m_IDOK;

	std::vector<CString>	inputMessage;  // copy to status on start
	std::vector<int>		inputNets; // list of existing subnets. Compare input to this list for validity check.
	int						newNet;	// save value of new net here
	int						netType;
	afx_msg void OnEnChangeNewNetEdit();
	virtual BOOL OnInitDialog();
	CComboBox m_network_type_select;
	afx_msg void OnCbnSelchangeNetworkTypeSelect();
	afx_msg void OnEnKillfocusNewNetEdit();
};
