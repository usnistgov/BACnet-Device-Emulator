
// BACnet Device Emulator.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols
#include "mxml.h"
#include <string>
#include "BACnet Device EmulatorDlg.h"
// CBACnetDeviceEmulatorApp:
// See BACnet Device Emulator.cpp for the implementation of this class
//

class CBACnetDeviceEmulatorApp : public CWinApp
{
private:
	std::vector<std::string>	statusStrings;  // Add strings in local subroutines, can be retrieved by calling functionn w/o depending on extern dlg link
	std::string					controllerTemplateFile; // name/path of controller template file

public:
	CBACnetDeviceEmulatorApp();
	CBACnetDeviceEmulatorDlg *m_pMainWnd;
// Overrides
public:
	virtual BOOL InitInstance();

	int		ReadConfigFile(char* ipname);
	int		SaveConfigFile(char* ipname);

	//int		ReadTemplateFile(char* ipname);

	std::string GetTemplateFile() { return controllerTemplateFile; }
	void SetTemplateFile(std::string fv) { controllerTemplateFile = fv; }
	//int ReadTemplateFile();

	void ReadClick(HTREEITEM hti);  // the tree has been clicked! (left buttton)
	void ReadDblClick(HTREEITEM hti);  // the focus tree has been dbl clicked! (left buttton)

	std::vector<std::string> GetStatusStrings();

	int GetItemType(HTREEITEM hti);  // returns type of controller in terms of does it have a different color on tree display
// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CBACnetDeviceEmulatorApp theApp;
