// ModifyPropValue.cpp : implementation file
//

#include "pch.h"
#include "BACnet Device Emulator.h"
#include "afxdialogex.h"
#include "ModifyPropValue.h"


// ModifyPropValue dialog

IMPLEMENT_DYNAMIC(ModifyPropValue, CDialogEx)

ModifyPropValue::ModifyPropValue(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ModifyPropValue, pParent)
{
	prevValue = "NA";  // previous value for display
	devID = -1;
	objID = -1;
	objInst = -1;
	propID = -1;
	propLabel = "NA";

}

ModifyPropValue::~ModifyPropValue()
{
}

void ModifyPropValue::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROP_INFO, m_prop_info);
	DDX_Control(pDX, IDC_PREV_VALUE, m_prev_value);
	DDX_Control(pDX, IDC_EDIT_VALUE, m_edit_value);
}


BEGIN_MESSAGE_MAP(ModifyPropValue, CDialogEx)
	ON_EN_KILLFOCUS(IDC_EDIT_VALUE, &ModifyPropValue::OnEnKillfocusEditValue)
END_MESSAGE_MAP()


// ModifyPropValue message handlers

BOOL ModifyPropValue::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	CString msg1 = L"Modifying property: ";
	CString cs2;

	//CString prevValue;  // previous value for display
	//int		devID;
	//int		objID;
	//int		objInst;
	//int		propID;
	//CString propLabel;

	if (devID > 0) {
		cs2.Format(L"DevID: %d ", devID);
		msg1 += cs2;
	}

	if ((objID > 0)&&(objInst > 0)) {
		cs2.Format(L"ObjID: %02d:%02d ", objID, objInst);
		msg1 += cs2;
	}

	if (propID > 0) {
		cs2.Format(L"Property %s (%d) ",propLabel.GetBuffer(), propID);
		msg1 += cs2;
	}
	
	m_prop_info.SetWindowText(msg1);

	cs2.Format(L"Current Value: [ %s ]", prevValue.GetBuffer());
	m_prev_value.SetWindowText(cs2);
	m_edit_value.SetFocus();

	return FALSE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void ModifyPropValue::OnEnKillfocusEditValue()
{
	// TODO: Add your control notification handler code here
	m_edit_value.GetWindowText(newValue);
}
