#pragma once
#include "afxdialogex.h"


// ModifyPropValue dialog

class ModifyPropValue : public CDialogEx
{
	DECLARE_DYNAMIC(ModifyPropValue)

public:
	ModifyPropValue(CWnd* pParent = nullptr);   // standard constructor
	virtual ~ModifyPropValue();

	// return value stored here
	CString newValue;	// new modified value for return
	
	// inputs for display
	CString prevValue;  // previous value for display
	int		devID;
	int		objID;
	int		objInst;
	int		propID;
	CString propLabel;

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ModifyPropValue };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_prop_info;
	CEdit m_prev_value;
	CEdit m_edit_value;
	virtual BOOL OnInitDialog();
	afx_msg void OnEnKillfocusEditValue();
};
