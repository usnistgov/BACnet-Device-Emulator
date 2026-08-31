#pragma once
#include "BACnetProperty.h"
#include "DemoControllers.h"
#include <vector>
// MAG 260402 Create BACnetObject class
// Purpose: to hold array of BACnet properties.

class BACnetObject
{
private:
	std::vector<BACnetProperty>	propList;	// all of the properties added to this object. Note list should stay sorted by prop type, not order added
	// NOTE these are only set when the value of property OBJECT-IDENTIFIER is set
	int		objType;	// type of object, needed for sort
	int		objInst;	// instance of object, needed for sort
	// MAG get object type from Object_Identifier property
	//int							objectType; // index of object type i.e. Analog Input = 0 or Device = 8
	HTREEITEM treepos;
	HTREEITEM focustreepos;

public:
	BACnetObject(int objid);
	int GetObjectType();
	int SetObjectType(int objType);

	int GetObjectProperty(int myprop, int arrindex, BACvalue *bv); // MAG 260406 note array index is optional, will only be eval for props with an array

	int SetPropertyValue(int propType, BACvalue* bv);
	int GetPropertyValue(int propType, BACvalue* bv);

	int SetPropertyValue(int propType, int idx, BACvalue* bv);  // with property index
	int GetPropertyValue(int propType, int idx, BACvalue* bv);  // with property index
	int GetPropertyArraySize(int propType);

	int SetPropertyValue(int propType, int valueType, char* propValue);

	int SetPropertyValue(BACenums::BACProp propType, BACvalue* bv);  // Sets value. Adds property if not present.
	int GetPropertyValue(BACenums::BACProp propType, BACvalue* bv);

	//int SetPropertyValue(BACenums::BACProp propType, int propArr, BACvalue* bv);  // Sets value. Adds property if not present.
	//int GetPropertyValue(BACenums::BACProp propType, int propArr, BACvalue* bv);

	int AddProperty(int type);	// Adds as array, use SetPropertyValue for non-array
	int AddProperty(int type, BACvalue* bv);// Adds as array, use SetPropertyValue for non-array

	void ClearProperty(int type);	// Deletes contents of property value array

	int AddObjectProps(int objType);	// Adds properties based on type of object
	int AddDefaultPropValues(int objType);

	std::vector<std::string>	GetPropStrings();
	std::string					GetPropString(int propID);
	std::vector<std::string>	GetXMLString();	// save to array of strings- usually one line, could be more if value is array type

	HTREEITEM GetTreepos() { return treepos; }
	void SetTreepos(HTREEITEM rv) { treepos = rv; }
	int FindTreeItem(HTREEITEM findItem, int* prop, int* arrIndex);
	int SetItemTreepos(HTREEITEM hti, int prop, int arrIndex);
	int SetPropTreepos(HTREEITEM hti, int prop, int arrIndex);
	int ResetTreepos();

	HTREEITEM GetFocusTreepos() { return focustreepos; }
	void SetFocusTreepos(HTREEITEM rv) { focustreepos = rv; }
	int FindFocusTreeItem(HTREEITEM findItem, int* prop, int* arrIndex);
	int SetItemFocusTreepos(HTREEITEM hti, int prop, int arrIndex);
	int SetPropFocusTreepos(HTREEITEM hti, int prop, int arrIndex);
	int ResetFocusTreepos();
	HTREEITEM GetItemFocusTreepos(int prop, int arrIndex);

	//int AddProperty(int type, int value);
	//
	//int AddObject(int objectType);

	bool operator<(const BACnetObject& other) const {
		if (objType < other.objType) return TRUE;
		if (objType == other.objType)
			if (objInst < other.objInst) return TRUE;

		return FALSE;
	}

	bool operator==(const BACnetObject& other) const {
		if ((objType == other.objType)&&(objInst == other.objInst)) return TRUE;

		return FALSE;
	}


};

