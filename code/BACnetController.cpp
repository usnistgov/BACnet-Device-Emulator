#include "pch.h"
#include "BACnetController.h"



BACnetController::BACnetController() 
{ 
	//subnetOn = 0;
	memset(&controllerAddr, 0, sizeof(DevAddr));
	memset(&controllerRouter, 0, sizeof(DevAddr));
	controllerAddr.device_id = -1;
	//devID = -1;
	isTemplate = 0;
	treepos = 0;
	treeState = 0;
}


BACnetController::BACnetController(int devid, unsigned int nsn)
{
	//BACvalue bv;

	memset(&controllerAddr, 0, sizeof(DevAddr));
	memset(&controllerRouter, 0, sizeof(DevAddr));
	controllerAddr.device_id = devid;
	//devID = devid;
	//subnetOn = 0; //preset in case nsn is invalid
	isTemplate = 0;
	treepos = 0;
	treeState = 0;
	SetSubnet(nsn);
	AddObject(8, devid);  // add device id
}


// Finds object/prop by HTREEITEM
HTREEITEM 
BACnetController::GetItemTreepos(int obj, int inst, int prop, int arrIndex)
{
	HTREEITEM hti = 0;
	BACvalue lbv = {};

	if (obj < 0) return 0;
	if (inst < 0) return 0;

	for (size_t i = 0; i < objectList.size(); i++){
		objectList[i].GetPropertyValue(BACenums::BACProp::en_OBJECT_IDENTIFIER, &lbv);
		if ((obj == lbv.value.o.object) && (inst == lbv.value.o.id)) {
			if (prop >= 0) {
				hti = objectList[i].GetItemFocusTreepos(prop, arrIndex);
				return hti;
			}
			hti = objectList[i].GetTreepos();
			return hti;
		}
	}

	return 0;
}


int 
BACnetController::FindTreeItem(HTREEITEM findItem, int* obj, int* inst, int* prop, int* arrIndex)
{ 
	int rv = 0;
	BACvalue bv = {};

	*obj = *inst = *prop = *arrIndex = -1;  // prepare for the worst

	if (findItem == treepos) { // it's me!
		return 1;
	}

	for (size_t i = 0; i < objectList.size(); i++) {
		if (objectList[i].FindTreeItem(findItem, prop, arrIndex) == 1){
			if (objectList[i].GetObjectProperty((int)BACenums::BACProp::en_OBJECT_IDENTIFIER, -1, &bv) == 1) {
				*obj = bv.value.o.object;
				*inst = bv.value.o.id;
				return 1;
			} else {
				return 0;
			}
		}
	}

	return 0; // not found!
}


int
BACnetController::FindFocusTreeItem(HTREEITEM findItem, int* obj, int* inst, int* prop, int* arrIndex)
{
	int rv = 0;
	BACvalue bv = {};

	*obj = *inst = *prop = *arrIndex = -1;  // prepare for the worst

	//if (findItem == treepos) { // it's me!
	//	return 1;
	//}

	for (size_t i = 0; i < objectList.size(); i++) {
		if (objectList[i].FindFocusTreeItem(findItem, prop, arrIndex) == 1) {
			if (objectList[i].GetObjectProperty((int)BACenums::BACProp::en_OBJECT_IDENTIFIER, -1, &bv) == 1) {
				*obj = bv.value.o.object;
				*inst = bv.value.o.id;
				return 1;
			}
			else {
				return 0;
			}
		}
	}

	return 0; // not found!
}



// Reset treepos in PROPS ONLY
int 
BACnetController::ResetTreepos()
{
	for (size_t i = 0; i < objectList.size(); i++) {
		objectList[i].ResetTreepos();
	}

	return 1;
}


int
BACnetController::SetItemTreepos(HTREEITEM hti, int obj, int inst, int prop, int arrIndex)
{
	BACvalue bv = {};

	// loop through objects
	for (size_t i = 0; i < objectList.size(); i++) {
		// check if it's the object- retrieve object type/instance
		if (objectList[i].GetObjectProperty((int)BACenums::BACProp::en_OBJECT_IDENTIFIER, -1, &bv) == 1) {
			if ((obj == bv.value.o.object) && (inst == bv.value.o.id)) {
				objectList[i].SetTreepos(hti);
				return 1;
			}
		}
		// check if it's under the object
		if (prop >= 0) {
			if (objectList[i].SetItemTreepos(hti, prop, arrIndex) == 1) return 1;
		}
	}
	
	// didn't find it- nothing to do just exit
	return 0;
}


// Sets Prop treepos- NOTE PROP IS INDEX
// Based on SetItemTreepos
int
BACnetController::SetPropTreepos(HTREEITEM hti, int obj, int inst, int prop, int arrIndex)
{
	BACvalue bv = {};

	// loop through objects
	for (size_t i = 0; i < objectList.size(); i++) {
		// check if it's the object- retrieve object type/instance
		if (objectList[i].GetObjectProperty((int)BACenums::BACProp::en_OBJECT_IDENTIFIER, -1, &bv) == 1) {
			if ((obj == bv.value.o.object) && (inst == bv.value.o.id)) {
				// check if it's under the object
				if (objectList[i].SetPropTreepos(hti, prop, arrIndex) == 1) return 1;  // MAG note this always returns 1
			}
		}
	}

	// didn't find it- nothing to do just exit
	return 0;
}


// return instance of the object added, or -1 for error
int BACnetController::AddObject(int objType)
{
	BACnetObject myObj= BACnetObject(objType);  // NOTE bounds check in constructor so won't fail
	int i = 0;
	int typeCounter = 0;
	BACvalue bv;

	// Don't want to add invalid/not requested object
	if (objType < 0) return -1;
	if (objType >= BAClabels::ObjectLabels.size()) return -1;

	if (myObj.GetObjectType() == (int)BACenums::BACObj::ERROR_OBJECT) {
		return -1;
	}
	// keep list sorted by object type/instance
	if (objectList.size() == 0) {  // the first one SHOULD always be a device object
		bv.type = 12;//object id
		bv.value.o.object = objType;
		bv.value.o.id = 0;
		myObj.SetPropertyValue(BACenums::BACProp::en_OBJECT_IDENTIFIER, &bv);
		objectList.push_back(myObj);
		return 0;  // return instance zero
	}

	// find correct spot in list
	while (i < objectList.size()) {
		if (objType == objectList[i].GetObjectType()) typeCounter++;
		if (objType >= objectList[i].GetObjectType()) i++;
		if (objType < objectList[i].GetObjectType()) break;
	}
	bv.type = 12;//object id
	bv.value.o.object = objType;
	bv.value.o.id = typeCounter;	// should start at zero
	myObj.SetPropertyValue(BACenums::BACProp::en_OBJECT_IDENTIFIER, &bv);

	objectList.push_back(myObj);

	return typeCounter;
}


int BACnetController::AddObject(int objType, int objInst) // return 1 for success 0 for error
{
	BACnetObject myObj = BACnetObject(objType);  // NOTE bounds check in constructor so won't fail
	int i = 0;
	int typeCounter = 0;
	BACvalue bv;

	// Don't want to add invalid/not requested object
	if (objType < 0) return -1;
	if (objType >= BAClabels::ObjectLabels.size()) return -1;

	if (myObj.GetObjectType() == (int)BACenums::BACObj::ERROR_OBJECT) {
		return -1;
	}

	memset(&bv, 0, sizeof(BACvalue));

	// keep list sorted by object type/instance
	
	if (objectList.size() == 0) {  // if list is empty add device object as first
		// add element 0 to object_list (count of objects)
		bv.type = 2;// unsigned int
		bv.value.ui = 1;
		myObj.SetPropertyValue(BACenums::BACProp::en_OBJECT_LIST, &bv);

		// add Device object to objec_list, and set object_identifier
		bv.type = 12;
		bv.value.o.object = 8;
		bv.value.o.id = controllerAddr.device_id;// devID;
		myObj.SetPropertyValue((int)BACenums::BACProp::en_OBJECT_IDENTIFIER, &bv); // both props are needed
		myObj.AddProperty((int)BACenums::BACProp::en_OBJECT_LIST, &bv);
		objectList.push_back(myObj);  // add device object

		// if needed add object from parameters
		if (objType != 8) {
			myObj = BACnetObject::BACnetObject(objType);  // reset myObj
			bv.type = 12;
			bv.value.o.object = objType;
			bv.value.o.id = objInst;
			myObj.SetPropertyValue((int)BACenums::BACProp::en_OBJECT_IDENTIFIER, &bv); // both props are needed
			myObj.AddProperty((int)BACenums::BACProp::en_OBJECT_LIST, &bv);
			objectList.push_back(myObj);  // add other new object
		}
		return 1;  // return instance zero
	}

	// if objInst < 0 find next available object inst for type
	if (objInst < 0) {
		for (i = 0; i < objectList.size(); i++){
			if (objectList[i].GetObjectType() == objType) {
				if (objectList[i].GetPropertyValue(BACenums::BACProp::en_OBJECT_IDENTIFIER, &bv) == 1) {
					if(bv.value.o.id + 1 > typeCounter)  // in case they are somehow not in order, always increment off the largest one
						typeCounter = bv.value.o.id + 1;
				} else {
					return 0; // NOTE this should never fail, this is a required property.
				}
			}
		}
		objInst = typeCounter;  // use this value
	}

	// find correct spot in list- bump up to object type
	bv.type = 12;//object id
	bv.value.o.object = objType;
	bv.value.o.id = objInst;
	myObj.SetPropertyValue(75, &bv);  // set object-identifier
	
	// check that it's not already there using std::find
	auto it = std::find(objectList.begin(), objectList.end(), myObj);
	if (it != objectList.end()) return 1;  // it already exists

	// set object-name
	sprintf_s(bv.value.t, 150, "%s %02d", BAClabels::ObjectLabels[ objType].c_str(), objInst);  // NOTE object instance isn't yet known
	bv.type = 7;
	bv.length = strlen(bv.value.t);
	myObj.SetPropertyValue(77, &bv);

	// try std::sort
	objectList.push_back(myObj);
	std::sort(objectList.begin()+1, objectList.end());

	ResetObjectIdentiferList();
	//SetObjectPropertyValue(8, 0, (int)BACenums::BACProp::en_OBJECT_LIST, -1, &bv);  // add new object to object_list
	//GetObjectPropertyValue(8, 0, (int)BACenums::BACProp::en_OBJECT_LIST, 0, &bv);	// Get count of objects in list
	

	/*
	// check case for inserting new first object, i.e. object type is lower than first object type in list
	if (objType < objectList[0].GetObjectType()) {
		objectList.insert(objectList.begin(), myObj);
		return 1;
	}

	i = 0;
	while (i < objectList.size()) {
		if(objType <= objectList[i].GetObjectType()) break;
		if (objType > objectList[i].GetObjectType()) i++;
	}
	// find correct spot in list- find position in object type
	while (i < objectList.size()) {
		if (objType == objectList[i].GetObjectType()) {
			objectList[i].GetPropertyValue((int)BACenums::BACProp::en_OBJECT_IDENTIFIER, &bv);
			if (objInst > bv.value.o.id) {
				i++;
			} else  if (objInst == bv.value.o.id) {
				return -1; // object with id already exists!
			}
			else if (objInst < bv.value.o.id) {
				break; // we've found our spot!
			}
		} else {  // not at correct object yet
			i++;
		}
	}

	if (i == objectList.size()) {	// case for adding to end of list
		objectList.push_back(myObj);
	} else {						// case for inserting in middle of list, most common?
		objectList.insert(objectList.begin() + i, myObj);// i should be at spot to insert new object into objectList
	}
	*/

	return 1;
}


// Returns 1 for success 0 for error
int BACnetController::AddObjectProperty(int objType, int objInst, int propType)
{
	int i = 0;
	BACvalue bv;

	for (i = 0;i < objectList.size();i++) {
		objectList[i].GetPropertyValue((int)BACenums::BACProp::en_OBJECT_IDENTIFIER, &bv);
		if ((bv.value.o.object == objType) && (bv.value.o.id == objInst)) {  // found the correct object!
			if ((objType == 8) && (propType == (int)BACenums::BACProp::en_OBJECT_IDENTIFIER))
				controllerAddr.device_id = objInst;  // NOTE capture device ID for convenience
			return objectList[i].AddProperty(propType);
		}
	}

	return 0; // didn't find object, can't add property, is an error.
}

//// Returns 1 for success 0 for error
//int BACnetController::AddObjectProperty(int objType, int objInst, int propType, int propArr)
//{
//	int i = 0;
//	BACvalue bv;
//
//	for (i = 0;i < objectList.size();i++) {
//		objectList[i].GetPropertyValue((int)BACenums::BACProp::en_OBJECT_IDENTIFIER, &bv);
//		if ((bv.value.o.object == objType) && (bv.value.o.id == objInst)) {  // found the correct object!
//			if ((objType == 8) && (propType == (int)BACenums::BACProp::en_OBJECT_IDENTIFIER)) devID = objInst;  // NOTE capture device ID for convenience
//			return objectList[i].AddProperty(propType, propArr);
//		}
//	}
//
//	return 0; // didn't find object, can't add property, is an error.
//}


// Returns 1 for success 0 for error
int 
BACnetController::SetObjectPropertyValue(int objType, int objInst, int propType, BACvalue* bv)
{
	int io = 0;	// index for object loop
	int rv = 1;
	BACvalue lbv;
	
	if (objType < 0) return 0;
	if (objInst < 0) return 0;
	if (propType < 0) return 0;
	if(bv == NULL) return 0;

	for (io = 0;io < objectList.size();io++) {
		objectList[io].GetPropertyValue((int)BACenums::BACProp::en_OBJECT_IDENTIFIER, &lbv);
		if ((lbv.value.o.object == objType) && (lbv.value.o.id == objInst)) {  // found the correct object!
			rv = objectList[io].SetPropertyValue(propType, bv);
			if ((rv == 1) && (objType == 8) && (propType == 75)) {  // edge case- resetting object identifier IF write is successful
				controllerAddr.device_id = bv->value.o.id;
			}
			return rv;
		}
	}

	return 0; // didn't find object, can't set property, is an error.

}
// Returns 1 for success 0 for error
int 
BACnetController::GetObjectPropertyValue(int objType, int objInst, int propType, BACvalue* bv)
{
	int io = 0;	// index for object loop

	if (objType < 0) return 0;
	if (objInst < 0) return 0;
	if (propType < 0) return 0;
	if (bv == NULL) return 0;
	if ((objType == 8) && (objInst <= 0)) objInst = controllerAddr.device_id;// devID;  // method to auto-set device id for Device Object

	for (io = 0;io < objectList.size();io++) {
		objectList[io].GetPropertyValue((int)BACenums::BACProp::en_OBJECT_IDENTIFIER, bv);
		if ((bv->value.o.object == objType) && (bv->value.o.id == objInst)) {  // found the correct object!
			return objectList[io].GetPropertyValue(propType, bv);
		}
	}

	return 0; // didn't find object, can't add property, is an error.
}


// Returns 1 for success 0 for error
int 
BACnetController::SetObjectPropertyValue(int objType, int objInst, int propType, int idx, BACvalue* bv)
{
	int io = 0;	// index for object loop
	int locobj = objInst;
	BACvalue lbv;

	if (objType < 0) return 0;
	if (objInst < 0) return 0;
	if (propType < 0) return 0;
	if (bv == NULL) return 0;
	if (idx < -1) return 0;
	if ((objInst == 0) && (objType == 8)) locobj = controllerAddr.device_id;

	for (io = 0;io < objectList.size();io++) {
		objectList[io].GetPropertyValue((int)BACenums::BACProp::en_OBJECT_IDENTIFIER, &lbv);
		if ((lbv.value.o.object == objType) && (lbv.value.o.id == locobj)) {  // found the correct object!
			return objectList[io].SetPropertyValue(propType, idx, bv);
		}
	}

	return 0; // didn't find object, can't set property, is an error.

}


// Resets the device object property object_list to match the contents of objectList
void 
BACnetController::ResetObjectIdentiferList()
{
	BACvalue bv = {};

	if (objectList.size() == 0) return; // this shouldn't happen
	bv.type = 2; // ui
	bv.value.ui = objectList.size();
	objectList[0].ClearProperty((int)BACenums::BACProp::en_OBJECT_LIST);
	objectList[0].SetPropertyValue(BACenums::BACProp::en_OBJECT_LIST, &bv);  // set first element

	// add object list contents
	for (size_t i = 0; i < objectList.size(); i++){
		if (objectList[i].GetObjectProperty((int)BACenums::BACProp::en_OBJECT_IDENTIFIER, -2, &bv)) {
			objectList[0].AddProperty((int)BACenums::BACProp::en_OBJECT_LIST, &bv);
		}
	}
}


// MAG 260526 Intent is to add objects to match template for AHU, VAV, or other equipment.
// MAG 260608 update to fit with new template structure
int 
BACnetController::SetTemplate(int devTemplate)
{
	if (devTemplate < 1) isTemplate = 0;
	else isTemplate = devTemplate;

	return 1;
	/*
	size_t i = 0;
	BACvalue bv = {};

	switch (devTemplate) {
		case 0: // generic
			for (i = 1; i <= 5; i++){ // Add analog and MSV
				AddObject(0,i);
				AddObject(1, i);
				AddObject(2, i);
				AddObject(19, i);
			}
			for (i = 1; i <= 3; i++) { // Add binary
				AddObject(3, i);
				AddObject(4, i);
				AddObject(5, i);
			}
			bv.type = 7;
			sprintf_s(bv.value.t, "EvilCorp Generic HVAC");
			SetObjectPropertyValue(8, devID, (int)BACenums::BACProp::en_MODEL_NAME, &bv);
			break;
		case 1: // AHU
			for (i = 1; i <= 12; i++)	AddObject(0, i);
			for (i = 1; i <= 8; i++)	AddObject(1, i);
			for (i = 1; i <= 20; i++)	AddObject(2, i);
			for (i = 1; i <= 3; i++)	AddObject(3, i);
			for (i = 1; i <= 3; i++)	AddObject(4, i);
			for (i = 1; i <= 20; i++)	AddObject(5, i);
			for (i = 1; i <= 4; i++)	AddObject(19, i);
		
			bv.type = 7;
			sprintf_s(bv.value.t, "EvilCorp AHU Type C");
			SetObjectPropertyValue(8, devID, (int)BACenums::BACProp::en_MODEL_NAME, &bv);
			break;
		case 2: // VAV
			for (i = 1; i <= 5; i++)	AddObject(0, i);
			for (i = 1; i <= 3; i++)	AddObject(1, i);
			for (i = 1; i <= 20; i++)	AddObject(2, i);
			for (i = 1; i <= 2; i++)	AddObject(3, i);
			for (i = 1; i <= 2; i++)	AddObject(4, i);
			for (i = 1; i <= 20; i++)	AddObject(5, i);
			for (i = 1; i <= 4; i++)	AddObject(19, i);
			bv.type = 7;
			sprintf_s(bv.value.t, "EvilCorp VAV Type C4");
			SetObjectPropertyValue(8, devID, (int)BACenums::BACProp::en_MODEL_NAME, &bv);
			break;
		// MAG NOTE add plant and other equipment types
		default: 
			for (i = 1; i <= 10; i++)	AddObject(0, i);
			for (i = 1; i <= 10; i++)	AddObject(1, i);
			for (i = 1; i <= 20; i++)	AddObject(2, i);
			for (i = 1; i <= 10; i++)	AddObject(3, i);
			for (i = 1; i <= 10; i++)	AddObject(4, i);
			for (i = 1; i <= 20; i++)	AddObject(5, i);
			for (i = 1; i <= 20; i++)	AddObject(19, i);
			bv.type = 7;
			sprintf_s(bv.value.t, "EvilCorp Boilerplate Type 22");
			SetObjectPropertyValue(8, devID, (int)BACenums::BACProp::en_MODEL_NAME, &bv);
			break;
	}

	return 1;
	*/
}


// Returns 1 for success 0 for error
int 
BACnetController::GetObjectPropertyValue(int objType, int objInst, int propType, int idx, BACvalue* bv)
{
	int io = 0;	// index for object loop
	int locobj = objInst;

	if (objType < 0) return 0;
	if (objInst < 0) return 0;
	if (propType < 0) return 0;
	if (bv == NULL) return 0;
	if (idx < -1) return 0;
	if ((objInst == 0) && (objType == 8)) locobj = controllerAddr.device_id;// devID;

	for (io = 0;io < objectList.size();io++) {
		objectList[io].GetPropertyValue((int)BACenums::BACProp::en_OBJECT_IDENTIFIER, bv);
		if ((bv->value.o.object == objType) && (bv->value.o.id == locobj)) {  // found the correct object!
			return objectList[io].GetPropertyValue(propType, idx, bv);
		}
	}

	return 0; // didn't find object, can't get property, is an error.
}


void
BACnetController::ClearObjectPropertyValue(int objType, int objInst, int propType)
{
	int io = 0;	// index for object loop
	int locobj = objInst;
	BACvalue lbv;

	if (objType < 0) return;
	if (objInst < 0) return;
	if (propType < 0) return;
	//if (bv == NULL) return;
	//if (idx < -1) return;
	if ((objInst == 0) && (objType == 8)) locobj = controllerAddr.device_id;// devID;

	for (io = 0; io < objectList.size(); io++) {
		objectList[io].GetPropertyValue((int)BACenums::BACProp::en_OBJECT_IDENTIFIER, &lbv);
		if ((lbv.value.o.object == objType) && (lbv.value.o.id == locobj)) {  // found the correct object!
			objectList[io].ClearProperty(propType);
			return;
		}
	}

	return; // didn't find object, can't set property, is an error.
}


std::vector<BACvalue>	
BACnetController::GetObjectListIdentifiers()  // Returns object-identifier pair for all objects in controller
{
	std::vector<BACvalue>	rv;
	BACvalue				objID;

	for (size_t i = 0; i < objectList.size(); i++){
		if (objectList[i].GetObjectProperty((int)BACenums::BACProp::en_OBJECT_IDENTIFIER, -1, &objID) == 1) {
			rv.push_back(objID);
		}
	}

	return rv;
}


// Returns 0 if new subnet (nsn) is out of range, 1 if reset is successful
int BACnetController::SetSubnet(unsigned int nsn)
{
	if (nsn > 0xFFFE) {// (65534))
		return 0;
	}
	if (nsn == 0) {
		return 0;
	}
	//subnetOn = nsn;
	controllerAddr.net = nsn;
	
	return 1;
}


int BACnetController::GetControllerAddressInfo(DevAddr* rv){
	if (rv == NULL) return 0;
	memcpy(rv, &controllerAddr, sizeof(DevAddr));

	return 1;
}


int BACnetController::SetControllerAddressInfo(DevAddr* rv) {
	if (rv == NULL) return 0;
	// Do we need to verify data here? That should be done before calling this function.
	memcpy(&controllerAddr, rv, sizeof(DevAddr));

	return 1;

}


int BACnetController::GetControllerRouterAddressInfo(DevAddr* rv) {
	if (rv == NULL) return 0;
	memcpy(rv, &controllerRouter, sizeof(DevAddr));

	return 1;
}


int BACnetController::SetControllerRouterAddressInfo(DevAddr* rv) {
	if (rv == NULL) return 0;
	memcpy(&controllerRouter, rv, sizeof(DevAddr));

	return 1;
}


// Passes messageStrings to calling network object
std::vector<std::string> 
BACnetController::GetMessageStrings() {
	std::vector<std::string> rv;

	rv = messageStrings;
	messageStrings.clear();
	
	return rv;
}


std::vector<std::string> 
BACnetController::GetObjectStrings()
{
	std::vector<std::string> rv;
	std::vector<std::string> rv2;
	std::stringstream ss1;

	for (size_t i = 0; i < objectList.size(); i++){
		ss1 << "Object " << i;
		rv.push_back(ss1.str());
		rv2 = objectList[i].GetPropStrings();
		rv.insert(rv.end(), rv2.begin(), rv2.end());
		rv2.clear();
		ss1.str("");
		ss1.clear();
	}

	return rv;
}

std::vector<std::string>
BACnetController::GetObjectStrings(int objID)
{
	std::vector<std::string> rv;

	if (objID < 0) return rv;
	if (objID >= objectList.size()) return rv;
	if (objectList.size() == 0) return rv;

	rv = objectList[objID].GetPropStrings();

	return rv;
}

// save to array of strings- usually one line, could be more if value is array type
std::vector<std::string>
BACnetController::GetXMLString()
{
	std::vector<std::string> rvp;
	std::vector<std::string> rv;
	std::stringstream ss1;
	BACvalue bv;
	std::string macString;
	DevAddr myda = {};

	this->GetControllerAddressInfo(&myda);
	if (myda.mac_device_len > 0) {
		ss1 << "deviceMAC=\"" << myda.mac_device_pr << "\" ";
		macString = ss1.str();
		ss1.str("");
	}

	// save id and subnet
	if (isTemplate) {
		ss1 << "<controller id=\"" << controllerAddr.device_id << "\" " << macString << "subnet=\"" << controllerAddr.net << "\" templateType=\"" << isTemplate << "\" >";
	} else { 
		ss1 << "<controller id=\"" << controllerAddr.device_id << "\" " << macString << "subnet=\"" << controllerAddr.net << "\" >";
	}
	rv.push_back(ss1.str());
	ss1.str("");

	for (size_t ival = 0; ival < objectList.size(); ival++) {
		rvp = objectList[ival].GetXMLString();
		rv.insert(rv.end(), rvp.begin(), rvp.end());
		rvp.clear();
	}

	rv.push_back("</controller>");

	return rv;
}

int
BACnetController::ConnectLibrary(CString libName)
{
	std::string ln = CT2CA(libName);

	return ConnectLibrary(ln);
}


// Name of sequence library to load
int 
BACnetController::ConnectLibrary(std::string libName) 
{
	std::vector<std::string> msgs;

	 int rv = localSeq.ConnectToDLL(libName);
	 if (rv == 1) {
		 // Set device ID in dll
		 if (localSeq.SetDeviceID(controllerAddr.device_id) != 1) {
			 messageStrings.push_back("ERROR could not set device Id in Library file!");
		 }
	 } else {
		 messageStrings.push_back("ERROR connecting to Library file!");
	 }

	// display output messages
	msgs = localSeq.GetMessageStrings();

	if (msgs.size() > 0) {
		messageStrings.reserve(messageStrings.size() + msgs.size());			// reserve space for msgs
		messageStrings.insert(messageStrings.end(), msgs.begin(), msgs.end());	// add msgs to end of messageStrings
	}

	return rv;
}
