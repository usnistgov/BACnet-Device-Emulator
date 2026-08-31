// DeleteControllerDialog.cpp : implementation file
//

#include "pch.h"
#include "BACnet Device Emulator.h"
#include "afxdialogex.h"
#include "DeleteControllerDialog.h"


// DeleteControllerDialog dialog

IMPLEMENT_DYNAMIC(DeleteControllerDialog, CDialogEx)

DeleteControllerDialog::DeleteControllerDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DeleteControllerDialog, pParent)
{

}

DeleteControllerDialog::~DeleteControllerDialog()
{
}

void DeleteControllerDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DELETE_LIST, m_delete_list);
}


BEGIN_MESSAGE_MAP(DeleteControllerDialog, CDialogEx)
	ON_CBN_SELCHANGE(IDC_DELETE_LIST, &DeleteControllerDialog::OnCbnSelchangeDeleteList)
END_MESSAGE_MAP()


// DeleteControllerDialog message handlers

BOOL DeleteControllerDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	CString cs1;

	for (size_t i = 0; i < devList.size(); i++){
		cs1.Format(L"%d", devList[i]);
		m_delete_list.AddString(cs1);
	}
	selectedToDie = devList.size() - 1;
	m_delete_list.SetCurSel(selectedToDie);  // set to last

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void DeleteControllerDialog::OnCbnSelchangeDeleteList()
{
	// TODO: Add your control notification handler code here
	selectedToDie = m_delete_list.GetCurSel();
}
