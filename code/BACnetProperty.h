#pragma once
#include <string>
#include <sstream>
#include <exception>
#include <system_error>
#include "BACnet Enums.h"
#include "BACnet Labels.h"
#include "BACnetProductions.h"
#include "BACnet Functions.h"

// MAG designed to work with propdescriptor2012 as in stdobjpr2012.cpp
class BACnetProperty
{
private:
	std::string				label;				// informative property identifier- set by default to type label, but could be modified
	BACenums::BACProp		propType;			// Index identifies type of property (propID)
	BACenums::BACPropType	baseType;			// Property datatype (ParseType), used with BACvalue
	unsigned char			propGroup;			// if there is a property grouping
	word					propET;
	int						propFlags;			// O, R, 
	std::vector<BACvalue>	value;				// set to value of property. Vector to allow for array types, will usually just be size 1
	BACenums::BACObj		parentObjectType;  // type of parent object, required for some operations
	// Add qualifiers like R or O or WithService if needed
	
	HTREEITEM				treepos;			// NOTE these are only in the FOCUS tree for properties.
	std::vector<HTREEITEM>	treeposVal;			// for value elements, which have their own line in the FOCUS display
public:
	BACnetProperty(std::string lbl, int indx, int bt, unsigned char pg, word etw, int pf);
	BACnetProperty(std::string lbl, int indx, int bt);
	BACnetProperty(char		   lbl, int indx, int bt);
	BACnetProperty(int indx, unsigned int bt);
	BACnetProperty();

	int SetValueType(int propID); // MAG 260507 Sets 'value' type based on input property type.

	static int MapTypeToValue(int pt);
	static int MapTypeToValue(BACenums::BACPropType pt);

	void SetObjectType(BACenums::BACObj ptype) { parentObjectType = ptype; };	// indicates type of parent object
	void SetObjectType(int ptype);												// indicates type of parent object

	BACenums::BACObj GetObjectType() { return parentObjectType; };

	static BACenums::BACPropType GetPropertyVarType(int obj, int prop);  // Must have object type to determine type of some props

	void SetPropertyValues(std::string lbl, int indx, int bt, unsigned char pg, word etw, int pf);
	void SetPropertyValues(std::string lbl, int indx, BACenums::BACPropType bt);

	void SetLabel(std::string newlabel) { label = newlabel; };
	void SetLabel(CString newlabel) { label = CT2A(newlabel); };
	void SetLabel(char* newlabel) { if (newlabel == NULL) return; label = newlabel; };

	std::string GetLabel() { return label; };
	std::string GetValueString();
	std::vector<std::string>	GetXMLString();	// save to array of strings- usually one line, could be more if value is array type

	void SetPropType(int newIndex);	
	void SetPropType(std::string newIndex);
	void SetPropType(BACenums::BACProp propIndex);
	
	//int GetIndex() { return (int)propType; };

	void SetBaseType(int newType);
	void SetBaseType(BACenums::BACPropType newType);
	void SetBaseType(std::string newType);

	int GetPropType() { return (int)propType; };
	int GetBaseType() { return (int)baseType; };

	int GetPropValue(BACvalue* bv);			// non-array version
	int GetPropValue(int idx, BACvalue* bv);// for array type properties
	int GetPropArraySize() { return value.size(); };

	int SetPropValue(BACvalue* bv);		// non-array version
	int SetPropValue(char bv);			// non-array type 1
	int SetPropValue(unsigned int bv);	// non-array type 2
	int SetPropValue(int bv);			// non-array type 3
	int SetPropValue(float bv);			// non-array type 4
	int SetPropValue(double bv);		// non-array type 5

	int SetEnumValue(unsigned int bv);	// non-array type 9 enumerated NOTE name modification as enum are alos unsigned int

	int SetPropValue(BACnetDate bv);	// non-array type 10
	int SetPropValue(BACnetTime bv);	// non-array type 11
	int SetPropValue(BNObjId bv);		// non-array type 12

	int AddPropValue(BACvalue* bv);		// For all array type properties
	int SetPropValue(int index, BACvalue* bv); // For all array type properties

	HTREEITEM GetTreepos() { return treepos; }
	void SetTreepos(HTREEITEM rv) { treepos = rv; }
	int FindTreeItem(HTREEITEM findItem, int *arrIndex);
	HTREEITEM GetTreeposVar(int id);
	void SetTreeposVar(HTREEITEM rv, int id);

	void ClearPropValues();

	bool operator<(const BACnetProperty& other) const {
		return propType < other.propType;
	}
	bool operator>(const BACnetProperty& other) const {
		return propType > other.propType;
	}
	bool operator<=(const BACnetProperty& other) const {
		return propType <= other.propType;
	}
	bool operator>=(const BACnetProperty& other) const {
		return propType >= other.propType;
	}
	bool operator==(const BACnetProperty& other) const {
		return propType == other.propType;
	}

};

