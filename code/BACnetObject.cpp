#include "pch.h"
#include "BACnetObject.h"

// Add a new object, i.e. an AI, AO, Device, etc...
// objid: object type, 0 for AI, 8 for Device...
// Note this just adds properties, values must be set after
// Note Object instance must be set after by calling function (probably in BACnetDevice)
BACnetObject::BACnetObject(int objid)
{
	//	BACnetProperty(std::string lbl, int indx, int bt, unsigned char pg, word et, int pf);
	std::string lbl;
	BACnetProperty newbp;
	BACvalue bv;

	if (objid < 0) objid = 2;  // make it an analog value by default if out of range
	if (objid >= BAClabels::ObjectLabels.size()) objid = 2;  // make it an analog value by default if out of range

	// Set the object type
	newbp.SetObjectType(objid);

	// add props for object
	AddObjectProps(objid);
	AddDefaultPropValues(objid);	

	treepos = 0;
	focustreepos = 0;
}


// Add properties to new object 
int
BACnetObject::AddObjectProps(int objType)
{
	std::vector<int>	props;
	BACnetProperty		newbp;
	BACvalue			bv = {};
	std::vector<int>	propsAI = { 0,17,22,25,28,31,35,36,45,52,59,65,69,72,75,77,79,81,85,103,106,111,113,117,118,130,168,351,352,353,354,355,356,357 };
	std::vector<int>	propsAO = { 0,17,22,25,28,31,35,36,45,52,59,65,69,72,75,77,79,81,85,87,103,104,106,111,113,117,130,168,351,352,353,354,355,356,357 };
	std::vector<int>	propsAV = { 0,17,22,25,28,35,36,45,52,59,65,69,72,75,77,79,81,85,87,103,104,106,111,113,117,130,168,351,352,353,354,355,356,357 };
	std::vector<int>	propsBI = { 0,4,6,15,16,17,28,31,33,35,36,46,72,75,77,79,81,84,85,103,111,113,114,115,130,168,351,352,353,354,355,356,357 };
	std::vector<int>	propsBO = { 0,4,15,16,17,28,31,33,35,36,40,46,66,67,72,75,77,79,81,84,85,87,103,104,111,113,114,115,130,168,351,352,353,354,355,356,357 };
	std::vector<int>	propsBV = { 0,4,6,15,16,17,28,33,35,36,46,66,67,72,75,77,79,81,85,87,103,104,111,113,114,115,130,168,351,352,353,354,355,356,357 };
	std::vector<int>	propsDV = { 5,10,11,12,24,28,30,44,56,57,58,62,63,64,70,73,75,76,77,79,96,97,98,107,112,116,119,120,121,122,139,152,153,154,155,157,167,168,169,170,171,172,193,195,196,202,203,204,206,209,338,339,340,341,372 };
	std::vector<int>	propsMI = { 0,7,17,28,31,35,36,39,72,74,75,77,79,81,85,103,110,111,113,130,168,351,352,353,354,355,356,357 };
	std::vector<int>	propsMO = { 0,17,28,31,35,36,40,72,74,75,77,79,81,85,87,103,104,110,111,113,130,168,351,352,353,354,355,356,357 };
	std::vector<int>	propsMV = { 0,7,17,28,35,36,39,72,74,75,77,79,81,85,87,103,104,110,111,113,130,168,351,352,353,354,355,356,357 };
	std::vector<int>	propsDF = { 28,75,77,79,85 }; // default
	int ptype = 0;
	BACenums::BACPropType penum = BACenums::BACPropType::ERROR_TYPE_NOT_SUPPORTED;

	if (objType < 0) return 0;
	if (objType >= BAClabels::ObjectLabels.size()) return 0;

	newbp.SetObjectType(objType);

	// MAG NOTE properties are in numerical order!!
	switch (objType) {
		case 0: props = propsAI; break;
		case 1: props = propsAO; break;
		case 2: props = propsAV; break;
		case 3: props = propsBI; break;
		case 4: props = propsBO; break;
		case 5: props = propsBV; break;
		case 8: props = propsDV; break;
		case 13: props =propsMI; break;
		case 14: props =propsMO; break;
		case 19: props =propsMV; break;
		default:props = propsDF; break;
	}

	for (size_t i = 0; i < props.size(); i++) {
		newbp.SetPropType(props[i]);
		if (newbp.GetBaseType() != (int)BACenums::BACPropType::ERROR_NOT_ENUM) {  // only add props if type is not error

			// Set default values
			penum = BACnetProperty::GetPropertyVarType(objType, props[i]);
			if (penum == BACenums::BACPropType::ERROR_TYPE_NOT_SUPPORTED) {
				propList.push_back(newbp);  // add without value
				continue;
			}
			if (penum == BACenums::BACPropType::ERROR_NOT_ENUM) {
				propList.push_back(newbp);  // add without value
				continue;
			}

			ptype = BACnetProperty::MapTypeToValue(penum);
			bv.type = ptype;
			bv.length = 0;
			switch (ptype) {
				case 0: // NULL
					break;
				case 1: // BOOL
					bv.value.b = 1;
					break;
				case 2: // UI
					bv.value.ui = 42;
					break;
				case 3: // signed int
					bv.value.i = -42;
					break;
				case 4: // real
					bv.value.r = 42.1;
					break;
				case 5: // double
					bv.value.d = 42.0001;
					break;
				case 6:  // octet
					bv.value.oc[0] = 0xBA;
					bv.value.oc[1] = 0xC0;
					bv.value.oc[2] = 0;
					break;
				case 7: //char string
					strcpy_s(bv.value.t, 25, "EvilCorp Intl.");
					bv.length = strlen(bv.value.t);
					break;
				case 8: // bit string
					bv.value.bt[0] = 22;
					bv.value.bt[1] = 22;
					bv.value.bt[2] = 22;
					bv.value.bt[0] = 0;
					break;	  
				case 9: // enum
					bv.value.en = 7;
					break;
				case 10: // date
					bv.value.date.year = 126;
					bv.value.date.month = 3;
					bv.value.date.day_of_month = 14;
					break;
				case 11: // Time
					bv.value.time.hour = 3;
					bv.value.time.minute = 14;
					bv.value.time.second = 15;
					break;

				case 12: // object id
					bv.value.o.object = 2;
					bv.value.o.id = 142;
					break;
				default: 
					bv.type = 1;
					bv.value.b = 1;
					break;
			}
			newbp.SetPropValue(&bv);
			propList.push_back(newbp);
		}
	}

//	memset(&bv, 0, sizeof(BACvalue));
//	// custom steps for objects
//	switch (objType) {
//		case 8: // device
//			// set object_list
//			bv.type = 2;
//			bv.value.ui = 1; // one object
//			SetPropertyValue((int)BACenums::BACProp::en_OBJECT_LIST, 0, &bv);
//			bv.type = 12;
//			bv.value.o.object = 8;
//			bv.value.o.id = objInst;
//			AddProperty((int)BACenums::BACProp::en_OBJECT_LIST, &bv);
//
//			break;
//		default:
//			break;
//	}

	return 1;
}


// Add properties to new object 
int
BACnetObject::AddDefaultPropValues(int objType)
{
	BACvalue	bv;
	char		cv[150] = {};

	if (objType < 0) return 0;
	if (objType >= BAClabels::ObjectLabels.size()) return 0;

	// description
	sprintf_s(cv, 150, "An OBJ type %02d", objType);
	bv.type = 7; // char
	strcpy_s(bv.value.t, cv);// "New Device Desc");
	bv.length = strlen(bv.value.t);
	SetPropertyValue(28, &bv);

	// object-name
	sprintf_s(cv, 150, "OBJ%02d XX", objType);  // NOTE object instance isn't yet known
	bv.type = 7;
	strcpy_s(bv.value.t, cv);// "New Object Name");
	bv.length = strlen(bv.value.t);
	SetPropertyValue(77, &bv);

	// object-type
	bv.type = 9; // enumerated
	bv.value.en = objType;
	bv.length = strlen(bv.value.t);
	SetPropertyValue(79, &bv);

	// profile-name
	bv.type = 7;
	strcpy_s(bv.value.t, "1-Beta Profile");
	bv.length = strlen(bv.value.t);
	SetPropertyValue(168, &bv);

	return 1;
}



// MAG 260406 Create function
// Purpose: to return the value in a property, identified by myprop (int index to property type) and arrindex
// note array index is optional, will only be eval for props with an array
// note on return error bv is not modified
int 
BACnetObject::GetObjectProperty(int myprop, int arrindex, BACvalue* bv)
{
	if (bv == NULL) return 0;
	if ((myprop < 0) || (myprop >= BAClabels::PropertyLabels.size())) {
		strcpy_s(bv->value.t, "Prop Out of Range");
		bv->type = 7;
		bv->length = strlen(bv->value.t);
		return 0;
	}

	// scan through prop list to find myprop
	for (size_t i = 0; i < propList.size(); i++) {
		if (propList[i].GetPropType() == myprop) {
			return propList[i].GetPropValue(arrindex, bv);
		}
	}

	// didn't find it
	return 0;
}


// Returns object type, or -1 for error
int
BACnetObject::GetObjectType()
{
	int i = 0;
	BACvalue bv;

	for (i = 0; i < propList.size(); i++){
		if (propList[i].GetPropType() == (int)BACenums::BACProp::en_OBJECT_IDENTIFIER) {
			propList[i].GetPropValue(&bv);
			return(bv.value.o.object);
		}
	}

	return -1;
}


// Returns object type, or 0 for error
int
BACnetObject::SetObjectType(int objType)
{
	int i = 0;
	BACvalue bv;

	bv.value.o.object = objType;
	bv.value.o.id = 0; // will need to be set later
	bv.type = 12;

	for (i = 0; i < propList.size(); i++) {
		if (propList[i].GetPropType() == (int)BACenums::BACProp::en_OBJECT_IDENTIFIER) {
			return propList[i].SetPropValue(&bv);
		}
	}

	return 0;
}


int BACnetObject::SetPropertyValue(BACenums::BACProp propType, BACvalue* bv)
{
	return SetPropertyValue((int)propType, bv);
}


int BACnetObject::SetPropertyValue(int propType, BACvalue* bv)
{
	int i = 0;

	if (bv == NULL) return 0;
	for (i = 0; i < propList.size(); i++){
		if ((int)propList[i].GetPropType() == propType) {
			if (propType == (int)BACenums::BACProp::en_OBJECT_IDENTIFIER) {
				objType = bv->value.o.object;
				objInst = bv->value.o.id;
			}
			return(propList[i].SetPropValue(bv));
		}
	}

	// prop not added yet, add it now
	AddProperty(propType,bv);

	return 0;
}


int 
BACnetObject::SetPropertyValue(int propType, int valueType, char* propValue)
{
	BACvalue lbv = {};

	// valid/range checks
	if (propValue == NULL) return 0;
	if ((propType < 0) || (propType >= (int)BACenums::BACProp::en_ERROR_PROP)) return 0;
	if ((valueType < 0) || (valueType > 12)) return 0;

	lbv.type = valueType;
	BACfuncs::StringToBACvalue(propValue, &lbv);
	AddProperty(propType, &lbv);
}


// MAG 260506
// If propArr is < -1 (i.e. -2) non-array version is called
// If propArr is -1 then value is added to end of prop array
// With index
int BACnetObject::SetPropertyValue(int propType, int idx, BACvalue* bv)
{
	int i = 0;

	if (bv == NULL) return 0;
	if (idx < -1) return SetPropertyValue(propType, bv);

	for (i = 0; i < propList.size(); i++) {
		if ((int)propList[i].GetPropType() == propType) {
			if (propType == (int)BACenums::BACProp::en_OBJECT_IDENTIFIER) {
				objType = bv->value.o.object;
				objInst = bv->value.o.id;
			}
			return(propList[i].SetPropValue(idx,bv));
		}
	}

	//// prop not added yet, add it now
	//AddProperty(propType, bv);
	// No should return error if prop/index does not exist

	return 0;
}


int BACnetObject::GetPropertyValue(BACenums::BACProp propType, BACvalue* bv)
{
	return GetPropertyValue((int)propType, bv);
}


int BACnetObject::GetPropertyValue(int propType, BACvalue* bv)
{
	int i = 0;

	if (bv == NULL) return 0;
	for (i = 0; i < propList.size(); i++) {
		if ((int)propList[i].GetPropType() == propType) {
			return(propList[i].GetPropValue(bv));
		}
	}

	return 0;
}


int BACnetObject::GetPropertyValue(int propType, int idx, BACvalue* bv)
{
	int i = 0;

	if (bv == NULL) return 0;
	for (i = 0; i < propList.size(); i++) {
		if ((int)propList[i].GetPropType() == propType) {
			return(propList[i].GetPropValue(idx, bv));
		}
	}

	return 0;
}


int BACnetObject::GetPropertyArraySize(int propType)
{
	int i = 0;

	if (propType < 0) return 0;
	if (propType >= (int)BACenums::BACProp::en_ERROR_PROP) return 0;

	for (i = 0; i < propList.size(); i++) {
		if ((int)propList[i].GetPropType() == propType) {
			return(propList[i].GetPropArraySize());
		}
	}

	return 0;
}

// If property already exists, this just returns success. Else inserts in property array.
int 
BACnetObject::AddProperty(int type)
{
	BACnetProperty newbp;
	BACvalue bv;
	int i = 0;

	if (type < 0) return 0;
	if (type >= BAClabels::PropertyLabels.size()) return 0;

	if( GetPropertyValue(BACenums::BACProp::en_OBJECT_IDENTIFIER, &bv) == 0) 
		return 0;
	newbp.SetObjectType(bv.value.o.object);

	// add common required properties 
	newbp.SetPropType(type);
	while ((i < propList.size())&&(propList[i].GetPropType() < type)) i++;
	if ((int)propList[i].GetPropType() == type) 
		return 1;
	if (i == propList.size()) propList.push_back(newbp);	// put at end of list
	else propList.insert(propList.begin() + i, newbp);		// insert at proper location

	return 1;
}


int
BACnetObject::AddProperty(int type, BACvalue *bvnew)
{
	BACnetProperty newbp;
	BACvalue bv;
	int i = 0;

	if (type < 0) return 0;
	if (type >= BAClabels::PropertyLabels.size()) return 0;

	if (GetPropertyValue(BACenums::BACProp::en_OBJECT_IDENTIFIER, &bv) == 0)
		return 0;
	newbp.SetObjectType(bv.value.o.object);

	// add common required properties 
	newbp.SetPropType(type);
	newbp.SetPropValue(0, bvnew);  // MAG this line is the only difference from other AddProperty function
	while ((i < propList.size()) && (propList[i].GetPropType() < type)) i++;
	if ((i != propList.size()) && ((int)propList[i].GetPropType() == type)) {
		// add to value vector
		propList[i].AddPropValue(bvnew);
		return 1;
	}
	if (i == propList.size()) propList.push_back(newbp);	// put at end of list
	else propList.insert(propList.begin() + i, newbp);		// insert at proper location

	return 1;
}


void
BACnetObject::ClearProperty(int type)
{
	BACnetProperty newbp;
	BACvalue bv;
	int i = 0;

	if (type < 0) return;
	if (type >= BAClabels::PropertyLabels.size()) return;

	//auto it = std::find(propList.begin(), propList.end(), type);
	//if (it != propList.end()) it->ClearPropValues();

	for (i = 0; i < propList.size(); i++){
		if (propList[i].GetPropType() == type) {
			propList[i].ClearPropValues();
			return;
		}
	}

	return;
}


// MAG 260420
// Purpose: Print value strings from all props and return as vector of strings
// If no props should return zero length vector
std::vector<std::string>
BACnetObject::GetPropStrings()
{
	std::vector<std::string> vso;
	std::stringstream ss1;

	for (size_t i = 0; i < propList.size(); i++){
		ss1 << "P" << propList[i].GetPropType() << ": " << propList[i].GetValueString();  // print Prop## and value string
		vso.push_back(ss1.str());
		ss1.str("");
		//vso.push_back(propList[i].GetValueString());
	}

	return vso;
}


std::string
BACnetObject::GetPropString(int propID)
{
	std::string rv;

	for (size_t i = 0; i < propList.size(); i++) {
		if (propList[i].GetPropType() == propID) {
			return propList[i].GetValueString();
		}
	}

	// if not returned yet then return error
	rv = "ERR";

	return rv;
}

// save to array of strings- usually one line, could be more if value is array type
std::vector<std::string>
BACnetObject::GetXMLString()
{
	std::vector<std::string> rvp;
	std::vector<std::string> rv;
	std::stringstream ss1;
	BACvalue bv;

	// get object type and instance
	GetPropertyValue(75, &bv); // object-identifier
	ss1 << "<object type=\"" << bv.value.o.object << "\" instance=\"" << bv.value.o.id << "\" >";
	rv.push_back(ss1.str());
	ss1.str("");

	// get object name for label
	GetPropertyValue(77, &bv); // object-name
	ss1 << " label=\"" << bv.value.t << "\" >";

	for (size_t ival = 0; ival < propList.size(); ival++) {
		rvp = propList[ival].GetXMLString();
		rv.insert(rv.end(), rvp.begin(), rvp.end());
		rvp.clear();
	}

	rv.push_back("</object>");

	return rv;
}


// MAG 260707 returns HTI for Focus tree item
HTREEITEM BACnetObject::GetItemFocusTreepos(int prop, int arrIndex)
{
	if(prop < 0) return 0;

	for (size_t i = 0; i < propList.size(); i++){
		if (propList[i].GetPropType() == prop) {
			if (arrIndex < 0) return propList[i].GetTreepos();
			return propList[i].GetTreeposVar(arrIndex);
		}
	}
	return 0;
}


int
BACnetObject::FindTreeItem(HTREEITEM findItem, int* prop, int* arrIndex)
{
	if (findItem == treepos) {  // it's me they're looking for!
		*arrIndex = -1;
		return 1;
	}

	// MAG 260707 props only have focustree id's, comment this out
	//for (size_t i = 0; i < propList.size(); i++) {
	//	if (propList[i].FindTreeItem(findItem, arrIndex) == 1) {
	//		*prop = propList[i].GetPropType();
	//		return 1;
	//	}
	//}

	return 0;
}


int
BACnetObject::FindFocusTreeItem(HTREEITEM findItem, int* prop, int* arrIndex)
{
	if (findItem == focustreepos) {  // it's me they're looking for!
		*arrIndex = -1;
		return 1;
	}

	for (size_t i = 0; i < propList.size(); i++) {
		if (propList[i].FindTreeItem(findItem, arrIndex) == 1) {
			*prop = propList[i].GetPropType();
			return 1;
		}
	}

	return 0;
}


int
BACnetObject::SetItemTreepos(HTREEITEM hti, int prop, int arrIndex)
{
	if (prop < 0) return 0;

	for (size_t i = 0; i < propList.size(); i++) {
		if (propList[i].GetPropType() == prop) {
			if (arrIndex == -1) { // i.e. index not used, we've found it
				propList[i].SetTreepos(hti);
			} else {	// else check var index array
				propList[i].SetTreeposVar(hti, arrIndex);
			}
			return 1;
		}
	}

	return 0;
}


int
BACnetObject::SetItemFocusTreepos(HTREEITEM hti, int prop, int arrIndex)
{
	return SetItemTreepos(hti, prop, arrIndex);  // props only have focus tree
}


// Sets Prop treepos- NOTE PROP IS INDEX
// Based on SetItemTreepos
int
BACnetObject::SetPropTreepos(HTREEITEM hti, int prop, int arrIndex)
{
	if (prop < 0) return 0;
	if (prop > propList.size()) return 0;

	if (arrIndex == -1) { // i.e. index not used, we've found it
		propList[prop].SetTreepos(hti);
	} else {	// else check var index array
		propList[prop].SetTreeposVar(hti, arrIndex);
	}

	return 1;
}


int
BACnetObject::ResetTreepos()
{
	for (size_t i = 0; i < propList.size(); i++) {
		propList[i].SetTreepos(0);
	}
	return 1;
}