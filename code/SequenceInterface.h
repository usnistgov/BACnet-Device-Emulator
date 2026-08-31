#pragma once
// MAG 260717 create SequenceInterface class
// Purpose: To create an interface to sequence of operations logic in a DLL.
// Data is transferred in and out of the DLL using state vectors of type double
// Note state vector mapping is done by calling BACnetController type

// The interface must have the following functions:
// int RunSequence(double *stateIn, double *stateOut); - Executes the logic in the DLL. Returns 1 for success. Output values returned in stateOut.
// int GetStateLabel(int inOut, int index, char *label);- inOut=0 for inputs, 1 for outputs. *label is pointer to a char[50] or larger.
// int GetStateSize(int inOut);- inOut=0 for inputs, 1 for outputs.
// int GetParameterCount();- The number of parameters, may be zero
// int SetParameters(double *pv) - Set and Get are optional if parameter count is zero, required if count is > 0
// int GetParameters(double *pv)
// int GetParameterLabel(int indx, char *label) - Also optional of no parameters are used
// MAG TODO: see if other i/o functions are necessary, such as text transfer for metadata, minimum point list requirements (i.e. need X AI, Y AO, etc.)

//#include "BACnet Device Emulator.h"

//// DLL function definitions
// MAG NOTE individual function defs were replaced by Class based functions- code left here in case a need to revert
// IF NEEDED respec these to have a parameter for device ID, and wrap the class in these functions with the devID used
// to determine which instance of the class is called.
//typedef int(__cdecl* fRunSequence)(double *, double *);		// stateIn, stateOut
//typedef int(__cdecl* fGetStateLabel)(int, int, char *);		// in/out, index, return char string
//typedef int(__cdecl* fGetStateSize)(int);					// in/out
////TODO add funcs for parameters
//
//typedef int(__cdecl* fGetParameterCount)();					// Just the number of parameters, may be zero
//typedef int(__cdecl* fTransferParameters)(double*);			// parameters in, parameters out, same template (Set and Get used)
////typedef int(__cdecl* fGetParameterLabel)(int, char*);		// index, return char string



// MAG 260727 add functionality to connect to library using Class interface
// Interface definition, so compiler knows what extern below intends.
// NOTE must be identical to original interfce definition in BACnetLibrary.h !!!
class IBACnetLibrary {
public:
	//int InitTestLibrary() { return 0; }
	virtual int SetID(int nID) { return 0; }
	virtual int GetID() { return 0; }
	virtual int RunSequence(double* stateIn, double* stateOut) { return 0; }
	virtual int	GetStateLabel(int inOut, int index, char* label) { return 0; }
	virtual int GetStateSize(int inOut) { return 0; }
	virtual int	SetParameters(double* pv) { return 0; }
	virtual int GetParameters(double* pv) { return 0; }
};

//typedef IBACnetLibrary* (fCreateLibraryFunc)();  // used by GetProcAddress
typedef IBACnetLibrary*(__cdecl fCreateLibraryFunc)();  // used by GetProcAddress


// Exported factory function to create unique connections
extern "C" __declspec(dllexport) IBACnetLibrary* ConnectBACLibrary();


#include <sstream>

class SequenceInterface
{
private:
	// note use .data() to access vector<double> as an array
	std::vector<double> stateIn;
	std::vector<double> stateOut;
	int stateInSize; // MAG not sure if these are necessary as using vectors
	int stateOutSize;
	std::vector<std::string> stateInLabels;
	std::vector<std::string> stateOutLabels;

	std::vector<double> parameters;	// optional to use, parameter values determined by DLL
	std::vector<std::string> parameterLabels;

	// The Class Interface Object
	IBACnetLibrary	*bacLib;
	fCreateLibraryFunc *CreateLibraryFunc;  // pointer to function to create library connection

	// DLL related functions
	//fRunSequence	runSequence;
	//fGetStateLabel	getLabel;
	//fGetStateSize	getStateSize;

	////fGetParameterCount	getParameterCount; MAG use getStateSize with io param = 2
	//fTransferParameters	getParameters;
	//fTransferParameters	setParameters;
	//fGetParameterLabel	getParameterLabel; MAG use getLabel with io param = 2

	std::string		labelDLL;  // holds the DLL path/name
	HMODULE			hDLL;  // set with LoadLibrary

	std::vector<std::string>	messageStrings;
public:
	SequenceInterface();// { stateInSize = 0; stateOutSize = 0; };

	std::vector<double>			GetStateArray() { return stateOut;};
	int							SetStateArray(std::vector<double> inState);  // only called for input array

	int							RunSequence();

	int							GetStateSize(int inOut) { if (inOut == 0) return stateIn.size(); return stateOut.size(); };
	std::vector<std::string>	GetStateLabels(int inOut) { if (inOut == 0) return stateInLabels; return stateOutLabels; };

	int							ConnectToDLL(std::string lDLL); // connect to DLL (LoadLibrary) and link functions when name is entered, return value is success/fail
	std::string					GetDLLName() { return labelDLL; };
	int							SetDeviceID(int devID) { if (bacLib != NULL) return bacLib->SetID(devID); return 0; }

	std::vector<std::string>	GetMessageStrings();
};

