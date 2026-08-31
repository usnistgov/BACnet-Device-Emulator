// AddNewObject.cpp : implementation file
//

#include "pch.h"
#include "BACnet Device Emulator.h"
#include "afxdialogex.h"
#include "AddNewObject.h"


// AddNewObject dialog

IMPLEMENT_DYNAMIC(AddNewObject, CDialogEx)

AddNewObject::AddNewObject(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_AddNewObject, pParent)
{
	selectedID = 0;
	selectedObject = 0;
	selectedInstance = 0;
	selectedCount = 0;
}

AddNewObject::~AddNewObject()
{
}

void AddNewObject::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ADD_OBJ_DEVID_LIST, m_add_obj_devid_list);
	DDX_Control(pDX, IDC_ADD_OBJECT_TYPE, m_add_obj_type);
	DDX_Control(pDX, IDC_ADD_OBJ_INSTANCE, m_add_obj_instance);
	DDX_Control(pDX, IDC_ADD_OBJ_STATUS, m_add_obj_status);
	DDX_Control(pDX, IDC_ADD_OBJ_COUNT, m_add_obj_count);
}


BEGIN_MESSAGE_MAP(AddNewObject, CDialogEx)
	ON_CBN_KILLFOCUS(IDC_ADD_OBJ_DEVID_LIST, &AddNewObject::OnCbnKillfocusAddObjDevidList)
	ON_CBN_KILLFOCUS(IDC_ADD_OBJECT_TYPE, &AddNewObject::OnCbnKillfocusAddObjectType)
	ON_EN_KILLFOCUS(IDC_ADD_OBJ_INSTANCE, &AddNewObject::OnEnKillfocusAddObjInstance)
	ON_EN_CHANGE(IDC_ADD_OBJ_COUNT, &AddNewObject::OnEnChangeAddObjCount)
	ON_EN_KILLFOCUS(IDC_ADD_OBJ_COUNT, &AddNewObject::OnEnKillfocusAddObjCount)
	ON_CBN_SELCHANGE(IDC_ADD_OBJECT_TYPE, &AddNewObject::OnCbnSelchangeAddObjectType)
	ON_CBN_SELCHANGE(IDC_ADD_OBJ_DEVID_LIST, &AddNewObject::OnCbnSelchangeAddObjDevidList)
END_MESSAGE_MAP()


// AddNewObject message handlers

void AddNewObject::OnCbnKillfocusAddObjDevidList()
{
	// TODO: Add your control notification handler code here
}


void AddNewObject::OnCbnSelchangeAddObjDevidList()
{
	// TODO: Add your control notification handler code here
	selectedID = m_add_obj_devid_list.GetCurSel();
	WriteStatusString();
}


void AddNewObject::OnCbnKillfocusAddObjectType()
{
	// TODO: Add your control notification handler code here
}


void AddNewObject::OnCbnSelchangeAddObjectType()
{
	// TODO: Add your control notification handler code here
	selectedObject = m_add_obj_type.GetCurSel();
	WriteStatusString();
}


void AddNewObject::OnEnKillfocusAddObjInstance()
{
	// TODO: Add your control notification handler code here
	CString cs1;
	m_add_obj_instance.GetWindowText(cs1);
	selectedInstance = _ttoi(cs1);//  m_add_obj_instance.GetDlgItemInt(IDC_ADD_OBJ_INSTANCE);
	WriteStatusString();

}

BOOL AddNewObject::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CString cs1;
	size_t i = 0;

	// TODO:  Add extra initialization here
	for (i = 0; i < devIDList.size(); i++){  
		cs1.Format(L"%d", devIDList[i]);
		m_add_obj_devid_list.AddString(cs1);
	}
	m_add_obj_devid_list.SetCurSel(devIDList.size() - 1);
	selectedID = devIDList.size() - 1;

	for (i = 0; i < objectLabelList.size(); i++){
		m_add_obj_type.AddString(objectLabelList[i]);
	}
	m_add_obj_type.SetCurSel(0);
	selectedObject = 0;
	selectedCount = 1;
	selectedInstance = 1;

	m_add_obj_instance.SetWindowText(L"1");  // make sure these always match default values above
	m_add_obj_count.SetWindowText(L"1");

	WriteStatusString();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void AddNewObject::OnEnChangeAddObjCount()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}

void AddNewObject::OnEnKillfocusAddObjCount()
{
	// TODO: Add your control notification handler code here
	CString cs1;

	m_add_obj_count.GetWindowText(cs1);
	selectedCount = _ttoi(cs1);
	WriteStatusString();
}

// describe current config in status window
void		
AddNewObject::WriteStatusString()
{
	CString cs1;
	if (selectedCount > 1) {
		cs1.Format(L"Device %d will add %d %s objects index %d - %d", devIDList[selectedID], selectedCount, objectLabelList[selectedObject].GetBuffer(),
			selectedInstance, selectedInstance + selectedCount - 1);
	}
	else {
		cs1.Format(L"Device %d will add %s object index %d", devIDList[selectedID], objectLabelList[selectedObject].GetBuffer(), selectedInstance);
	}
	m_add_obj_status.AddString(cs1);
	m_add_obj_status.SetCurSel(m_add_obj_status.GetCount() - 1);
}


