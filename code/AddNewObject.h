#pragma once
#include "afxdialogex.h"


// AddNewObject dialog

class AddNewObject : public CDialogEx
{
	DECLARE_DYNAMIC(AddNewObject)

public:
	AddNewObject(CWnd* pParent = nullptr);   // standard constructor
	virtual ~AddNewObject();

	// these are for init data
	std::vector<int>		devIDList;
	std::vector<CString>	objectLabelList;

	// the 'selected' variables are to send data back to calling fx
	// NOTE	THESE ARE INDEXES TO LIST ARRAYS!
	int			selectedID;
	int			selectedObject;
	// These are not an index, they are a value.
	int			selectedInstance;
	int			selectedCount;

	void		WriteStatusString(); // describe current config in status window

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_AddNewObject };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	// these hold data to indicate the new object device/type/instance
	CComboBox m_add_obj_devid_list;
	CComboBox m_add_obj_type;
	CEdit m_add_obj_instance;
	
	CListBox m_add_obj_status;
	afx_msg void OnCbnKillfocusAddObjDevidList();
	afx_msg void OnCbnKillfocusAddObjectType();
	afx_msg void OnEnKillfocusAddObjInstance();
	virtual BOOL OnInitDialog();
	CEdit m_add_obj_count;
	afx_msg void OnEnChangeAddObjCount();
	afx_msg void OnEnKillfocusAddObjCount();
	afx_msg void OnCbnSelchangeAddObjectType();
	afx_msg void OnCbnSelchangeAddObjDevidList();
};
