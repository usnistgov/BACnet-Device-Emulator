#pragma once
#include <vector>
#include <string>

//Interface definition class NOTE keep consistent with version in BDE/SequenceLibrary
class IBACnetLibrary {
public:
	//int InitTestLibrary() {	return 0; }
	virtual int SetID(int nID) { return 0; }
	virtual int GetID() { return 0; }
	virtual int RunSequence(double* stateIn, double* stateOut) { return 0; }
	virtual int	GetStateLabel(int inOut, int index, char* label) { return 0; }
	virtual int GetStateSize(int inOut) { return 0; }
	virtual int	SetParameters(double* pv) { return 0; }
	virtual int GetParameters(double* pv) { return 0; }
};


class BACnetLibrary : public IBACnetLibrary
{
private :
	int m_id;  
	int stateInCount = 8;
	int stateOutCount = 7;
	int paramCount = 5;

	std::string libraryName;
	std::vector<std::string> inputLabels;
	std::vector<std::string> outputLabels;
	std::vector<std::string> paramLabels;
	std::vector<double> inputState;
	std::vector<double> outputState;
	std::vector<double> paramState;

public:
	BACnetLibrary();
	//int InitTestLibrary();  // handled in class constructor
	int SetID(int nID) { if (nID < 0) return 0; m_id = nID; return 1; };
	int GetID() { return m_id; };

	int RunSequence(double* stateIn, double* stateOut);
	int	GetStateLabel(int inOut, int index, char* label);
	int GetStateSize(int inOut);
	int	SetParameters(double* pv);
	int GetParameters(double* pv);
};

