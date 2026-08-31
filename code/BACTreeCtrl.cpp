#include "pch.h"
#include "BACTreeCtrl.h"
#include "BACnet Device Emulator.h"
IMPLEMENT_DYNAMIC(BACTreeCtrl, CTreeCtrl);


extern CBACnetDeviceEmulatorApp theApp;

BACTreeCtrl::BACTreeCtrl() 
{
	type = 0; 
};
BEGIN_MESSAGE_MAP(BACTreeCtrl, CTreeCtrl)
	ON_NOTIFY_REFLECT(NM_CLICK, &BACTreeCtrl::OnNMClick)
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, &BACTreeCtrl::OnTvnSelchanged)
	ON_WM_LBUTTONDBLCLK()
	ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, &BACTreeCtrl::OnNMCustomdraw)
END_MESSAGE_MAP()

void BACTreeCtrl::OnNMClick(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: Add your control notification handler code here
	*pResult = 0;

	//LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	//NMTVCUSTOMDRAW* pcd = (NMTVCUSTOMDRAW*)pNMHDR;
	//HTREEITEM   hItem = (HTREEITEM)pcd->nmcd.dwItemSpec;
	//
	//theApp.ReadClick(hItem);

}

void BACTreeCtrl::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	DWORD dwPos = GetMessagePos();
	CPoint pt(GET_X_LPARAM(dwPos), GET_Y_LPARAM(dwPos));
	CPoint spt;
	int unitIndex = 0;
	//HVUnit* hvu = nullptr;

	spt = pt;

	// Convert to screen location for hittest to work
	ScreenToClient(&spt);

	UINT test = 0;
	HTREEITEM hti = HitTest(spt, &test);

	if(hti != NULL)
		theApp.ReadClick(hti);

	CTreeCtrl::OnLButtonUp(nFlags, point);
}

void BACTreeCtrl::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	DWORD dwPos = GetMessagePos();
	CPoint pt(GET_X_LPARAM(dwPos), GET_Y_LPARAM(dwPos));
	CPoint spt;
	int unitIndex = 0;
	//HVUnit* hvu = nullptr;

	spt = pt;

	// Convert to screen location for hittest to work
	ScreenToClient(&spt);

//	UINT test = 0;
//	HTREEITEM hti = HitTest(spt, &test);
//
//	if (hti != NULL)
//		theApp.ReadClick(hti);

	CTreeCtrl::OnLButtonDown(nFlags, point);
}

void BACTreeCtrl::OnTvnSelchanged(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	//LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);

	HTREEITEM hNewItem = pNMTreeView->itemNew.hItem; // The item currently selected
	//HTREEITEM hOldItem = pNMTreeView->itemOld.hItem; // The item previously selected

	if (hNewItem != NULL) theApp.ReadClick(hNewItem);
	*pResult = 0;
}

void BACTreeCtrl::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	DWORD dwPos = GetMessagePos();
	CPoint pt(GET_X_LPARAM(dwPos), GET_Y_LPARAM(dwPos));
	CPoint spt;
	int unitIndex = 0;

	spt = pt;
	// Convert to screen location for hittest to work
	ScreenToClient(&spt);

	UINT test = 0;
	HTREEITEM hti = HitTest(spt, &test);
	if (hti != NULL) theApp.ReadDblClick(hti);

	
	// base class handler
	CTreeCtrl::OnLButtonDblClk(nFlags, point);
}

void BACTreeCtrl::OnNMCustomdraw(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: Add your control notification handler code here
	//*pResult = 0;
	LPNMTVCUSTOMDRAW pTVCD = reinterpret_cast<LPNMTVCUSTOMDRAW>(pNMHDR);
	*pResult = CDRF_DODEFAULT;
	int ldevID = 0;

	switch (pTVCD->nmcd.dwDrawStage)
	{
		case CDDS_PREPAINT:
			*pResult = CDRF_NOTIFYITEMDRAW;
			break;

		case CDDS_ITEMPREPAINT:
		{
			HTREEITEM hItem = (HTREEITEM)pTVCD->nmcd.dwItemSpec;

			// Example: Change text color to Red if item is some specific data
			ldevID = theApp.GetItemType(hItem);
			switch(ldevID){
				case 1:	pTVCD->clrText = RGB(0, 0, 255); break;// Template text
				case 2: pTVCD->clrText = RGB(0, 128, 0); break;// Host Device text
			}

			*pResult = CDRF_DODEFAULT;
		}
		break;
	}
}
