#pragma once
#include <afxcmn.h>
class BACTreeCtrl : public CTreeCtrl
{
	DECLARE_DYNAMIC(BACTreeCtrl)
public:
	BACTreeCtrl();
	//virtual ~BACTreeCtrl();

protected:
	//DECLARE_MESSAGE_MAP()
	int type; // 1=Subnet, 2=Controller, 3=
public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnNMClick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnTvnSelchanged(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnNMCustomdraw(NMHDR* pNMHDR, LRESULT* pResult);
};

