#include "pch.h"
#include "BACnetLibrary.h"

// Exported factory function to create unique connections
extern "C" __declspec(dllexport) IBACnetLibrary* ConnectBACLibrary() {
    return new BACnetLibrary();
}

BACnetLibrary::BACnetLibrary() : m_id(0)
{
    libraryName = "BDE Test Library 260720";  // Note embed version in library name.

    // Note count must match stateInCount
    inputLabels.push_back("OAT");   // 0
    inputLabels.push_back("MAT");   // 1
    inputLabels.push_back("MATcc"); // 2
    inputLabels.push_back("MAThc"); // 3
    inputLabels.push_back("SAT");   // 4
    inputLabels.push_back("RAT");   // 5
    inputLabels.push_back("SAP");   // 6
    inputLabels.push_back("RAP");   // 7
    //if (inputLabels.size() != stateInCount) return 0;

    // Note count must match stateOutCount
    outputLabels.push_back("OA damp");  // 0
    outputLabels.push_back("MA damp");  // 1
    outputLabels.push_back("RA damp");  // 2
    outputLabels.push_back("CC dmd");   // 3
    outputLabels.push_back("HC dmd");   // 4
    outputLabels.push_back("SA fan");   // 5
    outputLabels.push_back("RA fan");   // 6
    //if (outputLabels.size() != stateOutCount) return 0;

    // Note count must match paramCount
    // Note these test parameters are meaningless
    paramLabels.push_back("OCC param");  // 0
    paramLabels.push_back("Fan param");  // 1
    paramLabels.push_back("Damp param");  // 2
    paramLabels.push_back("AHU param");  // 3
    paramLabels.push_back("Zone param");  // 4
    //if (paramLabels.size() != paramCount) return 0;

    // These must also match their respective count size
    inputState = { 82, 78, 55, 55, 55, 82, 0.25, 0.05 };
    outputState = { 50, 50, 50, 42, 0, 55, 48 };
    paramState = { 1, .2, .3, .8, 5 };

    //if (inputState.size() != stateInCount) return 0;
    //if (outputState.size() != stateOutCount) return 0;
    //if (paramState.size() != paramCount) return 0;

}


//int BACnetLibrary::InitTestLibrary()
//{
//}
int 
BACnetLibrary::RunSequence(double* stateIn, double* stateOut) 
{
    size_t i = 0;

    // first some error checking...
    if ((stateIn == NULL) || (stateOut == NULL)) return 0;

    // copy input values to input state array
    for (i = 0; i < stateInCount; i++)  inputState[i] = stateIn[i];

    // insert SOO logic here...

    // copy output values to output return array
    for (i = 0; i < stateOutCount; i++) stateOut[i] = inputState[i];

    // If all went well return with success!
    return 1;
}


int	
BACnetLibrary::GetStateLabel(int inOut, int index, char* label) 
{
    size_t len = 0;
    if (label == NULL) return 0;
    if (index < 0) return 0;
    if ((inOut < -1) || (inOut > 2)) return 0; // adjust range if more options are added

    if (inOut == -1) {  // requesting library name
        // NOTE- recommend using try-catch blocks when interacting with input or output arrays (numerous locations in library) 
        // in production releases but omitted here for clarity
        //try {
        len = libraryName.copy(label, 49);
        label[len] = 0;
        //}
        return 1;
    }

    switch (inOut) {
        case 0: // requesting input label
            if (index >= stateInCount) return 0;
            len = inputLabels[index].copy(label, 49);
            label[len] = 0;
            break;
        case 1: // requesting output label
            if (index >= stateOutCount) return 0;
            len = outputLabels[index].copy(label, 49);
            label[len] = 0;
            break;
        case 2: // requesting parameter label
            if (index >= paramCount) return 0;
            len = paramLabels[index].copy(label, 49);
            label[len] = 0;
            break;
        default:
            break;
    }

    return 1;
}


int 
BACnetLibrary::GetStateSize(int inOut) 
{
    switch (inOut) {
    case 0: return stateInCount;
    case 1: return stateOutCount;
    case 2: return paramCount;
    default: break;
    }

    return 0;
}


int	
BACnetLibrary::SetParameters(double* pv) 
{
    if (pv == NULL) return 0;

    for (size_t i = 0; i < paramState.size(); i++) {
        paramState[i] = pv[i];
    }

    return 1;
}


int 
BACnetLibrary::GetParameters(double* pv) 
{
    if (pv == NULL) return 0;

    for (size_t i = 0; i < paramState.size(); i++) {
        pv[i] = paramState[i];
    }

    return 1;
}