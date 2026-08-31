#pragma once
#include "afxdialogex.h"

// MAG 260716 add dialog
// Purpose: Present to use a list of device ids, allowing them to select one to delete.
// Note: Template and local system (net 10) are not allowed to be deleted

// DeleteControllerDialog dialog

class DeleteControllerDialog : public CDialogEx
{
	DECLARE_DYNAMIC(DeleteControllerDialog)

public:
	DeleteControllerDialog(CWnd* pParent = nullptr);   // standard constructor
	virtual ~DeleteControllerDialog();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DeleteControllerDialog };
#endif

protected:
	virtual void		DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	int					selectedToDie;	// device id INDEX to delete
	std::vector<int>	devList;		// list of device ids to display in dropdown
	CComboBox			m_delete_list;
	virtual BOOL		OnInitDialog();
	afx_msg void		OnCbnSelchangeDeleteList();
};
