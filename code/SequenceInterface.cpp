#include "pch.h"
#include "SequenceInterface.h"


SequenceInterface::SequenceInterface()
{
	stateInSize = 0; 
	stateOutSize = 0;

	//runSequence = nullptr;
	//getLabel = nullptr;
	//getStateSize = nullptr;

	//getParameterCount = nullptr;
	//getParameters = nullptr;
	//setParameters = nullptr;
	//getParameterLabel = nullptr;
	CreateLibraryFunc = NULL;
	bacLib = NULL;
	hDLL = nullptr;
}

// only called for input array
int 
SequenceInterface::SetStateArray(std::vector<double> newvec)
{
	if (newvec.size() != stateIn.size()) return 0;

	stateIn = newvec;

	return 1;
}


int 
SequenceInterface::RunSequence()
{
	return 1;
}


// connect to DLL (LoadLibrary) and link functions when name is entered, return value is success/fail
int 
SequenceInterface::ConnectToDLL(std::string lDLL)
{
	int si = 0;
	int so = 0;
	int pa = 0; // parameter count
	size_t i = 0;
	char labstr[50] = {};
	std::string errmsg;
	std::stringstream ss1;

	hDLL = LoadLibraryA(lDLL.c_str());

	if (hDLL == nullptr) {
		messageStrings.push_back("ERROR: DLL could not be loaded. Functions not connected."); 
		// sequence from Google
		 // 1. Get the numeric error code
		DWORD errorCode = GetLastError();

		// 2. Format the code into a readable string message
		LPVOID messageBuffer;
		FormatMessage(
			FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			errorCode,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			(LPTSTR)&messageBuffer,
			0,
			NULL
		);

		//std::wcout 
		messageStrings.push_back("LoadLibrary failed with error code: ");
		ss1 << errorCode << ": " << (wchar_t*)messageBuffer << std::endl;
		messageStrings.push_back(ss1.str());
		switch (errorCode) {
			case 5: messageStrings.push_back("Access Denied: The system is not allowing access to the library file."); break;//
			case 126:messageStrings.push_back("Library file dependencies not found."); break;//
			case 193:messageStrings.push_back("Library file format mismatch error. The library file has a different architecture than the BDE."); break;//
			case 1114: messageStrings.push_back("The Library file has an internal error and can not load."); break;//
			default: break;
		}

		// Free the buffer allocated by FormatMessage
		LocalFree(messageBuffer);
		return 0;
	}

	// DLL related functions
	CreateLibraryFunc = reinterpret_cast<fCreateLibraryFunc *>(GetProcAddress(hDLL, "ConnectBACLibrary"));
	if (!CreateLibraryFunc) {
		messageStrings.push_back("ERROR: Could not connect to library Create function.");
		DWORD errorCode = GetLastError();

		// 2. Format the code into a readable string message
		LPVOID messageBuffer;
		FormatMessage(
			FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			errorCode,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			(LPTSTR)&messageBuffer,
			0,
			NULL
		);

		//std::wcout 
		messageStrings.push_back("LoadLibrary failed with error code: ");
		ss1 << errorCode << ": " << (wchar_t*)messageBuffer << std::endl;
		messageStrings.push_back(ss1.str());
		switch (errorCode) {
			case 5: messageStrings.push_back("Access Denied: The system is not allowing access to the library file."); break;//
			case 126:messageStrings.push_back("Library file dependencies not found."); break;//
			case 193:messageStrings.push_back("Library file format mismatch error. The library file has a different architecture than the BDE."); break;//
			case 1114: messageStrings.push_back("The Library file has an internal error and can not load."); break;//
			default: break;
		}

		// Free the buffer allocated by FormatMessage
		LocalFree(messageBuffer);
		return 0;
	}

	bacLib = CreateLibraryFunc();
	si = bacLib->GetStateSize(0);
	so = bacLib->GetStateSize(1);
	pa = bacLib->GetStateSize(2);
	// 
	// 
	//fRunSequence	runSequence;
	//fGetStateLabel	getLabel;
	//fGetStateSize	getStateSize;

	// Connect to state functions
	//runSequence = reinterpret_cast<fRunSequence>(GetProcAddress(hDLL, "RunSequence"));
	//if (runSequence == nullptr) {
	//	messageStrings.push_back("ERROR: DLL function RunSequence not found. Functions not connected.");
	//	return 0;
	//}
	//
	//getLabel = reinterpret_cast<fGetStateLabel>(GetProcAddress(hDLL, "GetStateLabel"));
	//if (getLabel == nullptr) {
	//	messageStrings.push_back("ERROR: DLL function GetStateLabel not found. Functions not connected.");
	//	return 0;
	//}
	//
	//getStateSize = reinterpret_cast<fGetStateSize>(GetProcAddress(hDLL, "GetStateSize"));
	//if (getStateSize == nullptr) {
	//	messageStrings.push_back("ERROR: DLL function GetStateSize not found. Functions not connected.");
	//	return 0;
	//}

	// Get library label
	bacLib->GetStateLabel(-1, 0, labstr);
	//si = getLabel(-1, 0, labstr);
	ss1 << "Open library with label: " << labstr;
	messageStrings.push_back(ss1.str());
	ss1.str("");

	// Get state vector sizes
	//si = getStateSize(0);
	//so = getStateSize(1);

	if ((si < 1) || (so < 1)) {
		messageStrings.push_back("ERROR: DLL returned invalid I/O count, no functions connected.");
		return 0;
	}

	// MAG TODO is this a reasonable upper bound?
	if ((si > 500) || (so > 500)) {
		messageStrings.push_back("ERROR: DLL returned invalid I/O count, no functions connected.");
		return 0;
	}

	stateIn.resize(si);
	stateOut.resize(so);
	stateInLabels.resize(si);
	stateOutLabels.resize(so);

	// Get input labels
	for (i = 0; i < si; i++){
		if (bacLib->GetStateLabel(0, i, labstr)) {
			stateInLabels[i] = labstr;
		} else {
			stateInLabels[i] = "ERR";
		}
	}

	// Get output labels
	for (i = 0; i < so; i++) {
		if (bacLib->GetStateLabel(1, i, labstr)) {
			stateOutLabels[i] = labstr;
		} else {
			stateOutLabels[i] = "ERR";
		}
	}

	// connect to parameter functions
	//getParameterCount
	//getParameters
	//setParameters
	//getParameterLabel

	//getParameterCount = reinterpret_cast<fGetParameterCount>(GetProcAddress(hDLL, "GetParameterCount"));
	//if (getParameterCount == nullptr) {
	//	messageStrings.push_back("ERROR: DLL function GetParameterCount not found. Functions not connected.");
	//	return 0;
	//}

	// Get count of parameters
	//pa = getStateSize(2);
	if (pa > 0) {  // connect to other parameter functions
		//getParameters = reinterpret_cast<fTransferParameters>(GetProcAddress(hDLL, "GetParameters"));
		//if (getParameters == nullptr) {
		//	messageStrings.push_back("ERROR: DLL function GetParameters not found. Functions not connected.");
		//	return 0;
		//}

		//setParameters = reinterpret_cast<fTransferParameters>(GetProcAddress(hDLL, "SetParameters"));
		//if (setParameters == nullptr) {
		//	messageStrings.push_back("ERROR: DLL function SetParameters not found. Functions not connected.");
		//	return 0;
		//}

		// Get parameter labels
		parameterLabels.resize(pa);
		for (i = 0; i < pa; i++) {
			if (bacLib->GetStateLabel(2, i, labstr)) {
				parameterLabels[i] = labstr;
			} else {
				parameterLabels[i] = "ERR";
			}
		}

		//getParameterLabel = reinterpret_cast<fGetParameterLabel>(GetProcAddress(hDLL, "GetParameterLabel"));
		//if (getParameterLabel == nullptr) {
		//	messageStrings.push_back("ERROR: DLL function GetParameterLabel not found. Functions not connected.");
		//	return 0;
		//}

	}

	//theApp.m_pMainWnd->m_status_focus.AddString(L"All DLL functions connected.");
	messageStrings.push_back("All library functions connected.");

	return 1;
}  // end ConnectToDLL


std::vector<std::string> 
SequenceInterface::GetMessageStrings()
{
	std::vector<std::string> rv;

	rv = messageStrings;
	messageStrings.clear();

	return rv;
}
