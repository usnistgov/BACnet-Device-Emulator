#include "pch.h"
#include "BACnetProperty.h"
/*
private:
	std::string				label;				// informative property identifier
	BACenums::BACProp		index;				// Index identifies type of property (propID)
	BACenums::BACPropType	baseType;			// Property datatype (ParseType), used with BACvalue
	unsigned char			propGroup;			// if there is a property grouping
	word					propET;
	int						propFlags;			// O, R,
	BACvalue				value;				// set to value of property
	BACenums::BACObj		parentObjectType;  // type of parent object, required for some operations
*/

BACnetProperty::BACnetProperty()
{
	BACvalue bv;

	memset(&bv, 0, sizeof(BACvalue));
	value.push_back(bv);
	treeposVal.push_back(0);
	treepos = 0;

	label = "NA";
	propType = BACenums::BACProp::en_ERROR_PROP;
	baseType = BACenums::BACPropType::ERROR_NOT_ENUM;
	propGroup = 0;
	propET = 0;
	value[0].type = 0;
	value[0].value.b = 0;
	propFlags = 0;
	parentObjectType = BACenums::BACObj::ERROR_OBJECT;
}

BACnetProperty::BACnetProperty(std::string lbl, int indx, int bt, unsigned char pg, word etw, int pf) 
{
	//BACvalue bv;
	//int i = MapTypeToValue(bt);

	treepos = 0;
	label = lbl;
	SetPropType(indx);
	SetBaseType(bt);
	propGroup = pg;
	propET = etw;
	propFlags = pf;
	MapTypeToValue(indx);
	//memset(&bv, 0, sizeof(BACvalue));

	//if (i < 0) {
	//	// add mapping function for composite or complex types
	//	i = 1;  // get rid of this after new mapping function is inserted above.
	//}
	//bv.type = i; //  MAG 260406 todo: add function to map base type to value[0].type
	//value.push_back(bv);
}


BACnetProperty::BACnetProperty(std::string lbl, int indx, int bt)
{
	BACvalue bv;

	memset(&bv, 0, sizeof(BACvalue));
	value.push_back(bv);
	treeposVal.push_back(0);
	treepos = 0;

	label = lbl;
	SetPropType(indx);
	SetBaseType(bt);
	propGroup = 0;
	propET = 0;
	propFlags = 0;
	MapTypeToValue(indx);

	//value[0].type = 0;
	//value[0].value.b = 0;
}


BACnetProperty::BACnetProperty(char lbl, int indx, int bt)
{
	BACvalue bv;

	memset(&bv, 0, sizeof(BACvalue));
	value.push_back(bv);
	treeposVal.push_back(0);
	treepos = 0;

	label = lbl;
	SetPropType(indx);
	SetBaseType(bt);
	propGroup = 0;
	propET = 0;
	propFlags = 0;
	MapTypeToValue(indx);

	//value[0].type = 0;
	//value[0].value.b = 0;
}

BACnetProperty::BACnetProperty(int indx, unsigned int val)
{
	BACvalue bv;

	memset(&bv, 0, sizeof(BACvalue));
	value.push_back(bv);
	treeposVal.push_back(0);
	treepos = 0;

	//SetPropType(indx);

	value[0].value.ui = val;
	value[0].type = 2;
	if ((indx < 0) || (indx >= BAClabels::PropertyLabels.size())){
		label = "OUT OF RANGE";
	} else {
		label = BAClabels::PropertyLabels[indx];
	}
}


// Sets values for member variables. Note conversion of bt to BACvalue type i
void
BACnetProperty::SetPropertyValues(std::string lbl, int indx, int bt, unsigned char pg, word etw, int pf) 
{
	//int i = MapTypeToValue(bt);

	SetValueType(indx);
	label = lbl;
	SetPropType(indx);
	SetBaseType(bt);
	propGroup = pg;
	propET = etw;
	propFlags = pf;

	//if (i < 0) {
	//	// add mapping function for composite or complex types
	//	i = 0;  // get rid of this after new mapping function is inserted above.
	//}
	//value[0].type = i; //  MAG 260406 todo: add function to map base type to value[0].type
}


// Sets values for member variables. Note conversion of bt to BACvalue type i
void
BACnetProperty::SetPropertyValues(std::string lbl, int indx, BACenums::BACPropType bt)
{
	int i = MapTypeToValue(bt);

	label = lbl;
	SetPropType(indx);
	SetBaseType(bt);

	if (i < 0) {
		// add mapping function for composite or complex types
		i = 0;  // get rid of this after new mapping function is inserted above.
	}
	value[0].type = i; //  MAG 260406 todo: add function to map base type to value[0].type
}


// Sets the parent object type
void 
BACnetProperty::SetObjectType(int ptype)
{
	int newp = ptype;

	// check range on ptype
	if ((newp < 0)||(newp >= BAClabels::ObjectLabels.size())) {
		newp = 2; // av by default
	}

	parentObjectType = (BACenums::BACObj) newp;
}


// Sets property index (type) and label based on index
void
BACnetProperty::SetPropType(BACenums::BACProp newIndex)
{
	int i;

	// Set index
	if (newIndex == BACenums::BACProp::en_ERROR_PROP) {
		i = 77; // object-name
		propType = BACenums::BACProp::en_OBJECT_NAME;
	} else {
		propType = newIndex;
		i = (int)newIndex;
	}

	// Set label
	if (i < BAClabels::PropertyLabels.size()) {
		label = BAClabels::PropertyLabels[i];
	} else {
		label = "ERROR property index out of range";
	}

	// Set base type
	baseType = GetPropertyVarType((int)parentObjectType, i);
}


// indicates type of parent object
void 
BACnetProperty::SetPropType(int newIndex)
{
	int enumsize = (int)BAClabels::PropertyLabels.size();

	if (newIndex < 0) return;
	if (newIndex >= enumsize) return; // out of range high

	propType = static_cast<BACenums::BACProp>(newIndex);
	baseType = GetPropertyVarType((int)parentObjectType, newIndex);
	SetValueType(newIndex);
	//if (label.size() == 2) {
		label = BAClabels::PropertyLabels[newIndex];
	//}
}


// indicates type of parent object
void 
BACnetProperty::SetPropType(std::string newIndex)
{
	int indexInt = 0;
	std::stringstream ss1;
	
	try {
		indexInt = stoi(newIndex);
	}
	catch (const std::invalid_argument& e) {
		ss1 << e.what();
		return;
	}
	catch (const std::out_of_range& e) {
		ss1 << e.what();
		return;
	}

	SetPropType(indexInt);
}

void 
BACnetProperty::SetBaseType(int newType){
	int enumsize = sizeof(BACenums::BACPropType);

	if (newType < 0) return;
	if (newType >= enumsize / sizeof(int)) return; // out of range high

	baseType = static_cast<BACenums::BACPropType>(newType);
}


void
BACnetProperty::SetBaseType(BACenums::BACPropType newType) {

	baseType = newType;
}


void 
BACnetProperty::SetBaseType(std::string newType) {
	int indexInt = 0;
	std::stringstream ss1;

	try {
		indexInt = stoi(newType);
	}
	catch (const std::invalid_argument& e) {
		ss1 << e.what();
		return;
	}
	catch (const std::out_of_range& e) {
		ss1 << e.what();
		return;
	}

	SetPropType(indexInt);

}


int
BACnetProperty::GetPropValue(BACvalue* bv)
{
	if (bv == nullptr) return 0;

	memcpy(bv, &value[0], sizeof(BACvalue));
	
	return 1;
}


// With array index
int
BACnetProperty::GetPropValue(int idx, BACvalue* bv)
{
	if (bv == nullptr) return 0;
	if (idx < 0) return GetPropValue(bv);
	if (idx >= value.size()) return 0;

	memcpy(bv, &value[idx], sizeof(BACvalue));

	return 1;
}


int
BACnetProperty::SetPropValue(BACvalue* bv)
{
	if (bv == nullptr) return 0;

	if (value.size() == 0) {
		value.push_back(*bv);
		treeposVal.push_back(0);
	} else
		memcpy(&value[0], bv, sizeof(BACvalue));

	return 1;
}


int
BACnetProperty::AddPropValue(BACvalue* bv)
{
	if (bv == nullptr) return 0;

	value.push_back(*bv);
	treeposVal.push_back(0);

	return 1;
}


// With array index
// not if idx== -1 new value is pushed on back of array. -2 or less is error
int
BACnetProperty::SetPropValue(int idx, BACvalue* bv)
{
	if (bv == nullptr) return 0;
	if (idx < -1) return SetPropValue(bv);
	if (idx >= value.size()) return 0;
	if (idx == -1) {
		value.push_back(*bv);
		treeposVal.push_back(0);
		return 1;
	}

	memcpy(&value[idx], bv, sizeof(BACvalue));

	return 1;
}


// Set BOOL
int
BACnetProperty::SetPropValue(char bv)
{
	value[0].value.b = bv;
	value[0].type = 1;

	return 1;
}

// Set Unsigned Int
int
BACnetProperty::SetPropValue(unsigned int bv)
{
	value[0].value.ui = bv;
	value[0].type = 2;

	return 1;
}


// Set Integer (signed)
int
BACnetProperty::SetPropValue(int bv)
{
	value[0].value.i = bv;
	value[0].type = 3;

	return 1;
}

// Set Float/Real
int
BACnetProperty::SetPropValue(float bv)
{
	value[0].value.r = bv;
	value[0].type = 4;

	return 1;
}


// Set Double
int
BACnetProperty::SetPropValue(double bv)
{
	value[0].value.d = bv;
	value[0].type = 5;

	return 1;
}


// Set Enum NOTE name modification as enum is also unsigned int
int
BACnetProperty::SetEnumValue(unsigned int bv)
{
	value[0].value.en = bv;
	value[0].type = 9;

	return 1;
}


// Set BACnet Date
int
BACnetProperty::SetPropValue(BACnetDate bv)
{
	memcpy(&value[0].value.date, &bv, sizeof(BACnetDate));
	value[0].type = 10;

	return 1;
}


// Set BACnet Time
int
BACnetProperty::SetPropValue(BACnetTime bv)
{
	memcpy(&value[0].value.time, &bv, sizeof(BACnetTime));
	value[0].type = 11;

	return 1;
}


// Set BACnet Date
int
BACnetProperty::SetPropValue(BNObjId bv)
{
	memcpy(&value[0].value.o, &bv, sizeof(BNObjId));
	value[0].type = 10;

	return 1;
}


// MAG 260406 
// Maps enum type to one of BACvalue types:

///*
//union prop_value {			// 0 nullptr  MAG 05APR05 add nullptr
//char			b;		// 1 bool
//unsigned int	ui;		// 2 unsigned int
//int				i;		// 3 signed int
//float			r;		// 4 real
//double			d;		// 5 double
//octet			oc[255];// 6 octet[100]
//char			t[255];	// 7 char[100]
//octet			bt[255];// 8 bit string octet[100]
//unsigned int	en;		// 9 enumerated (unsigned int)
//BACnetDate		date;	// 10 BACnet Date
//BACnetTime		time;	// 11 BACnet Time
//BNObjId			o;		// 12 object id
//};
//*/


int 
BACnetProperty::FindTreeItem(HTREEITEM findItem, int *arrIndex)
{
	if (findItem == treepos) {  // it's me they're looking for!
		*arrIndex = -1;
		return 1;
	}

	while(treeposVal.size() < value.size()) treeposVal.push_back(0);

	for (size_t i = 0; i < value.size(); i++){
		if (treeposVal[i] == findItem) {
			*arrIndex = i;
			return 1;
		}
	}

	return 0;
}


HTREEITEM	
BACnetProperty::GetTreeposVar(int id)
{
	if (id < 0) return 0;
	if (id >= treeposVal.size()) return 0;

	return treeposVal[id];
}

void		
BACnetProperty::SetTreeposVar(HTREEITEM rv, int id)
{
	if (id < 0) return;
	if (id >= value.size()) return;

	// check if somehow treeposVal array is smaller than value array, if so add to it as necessary
	while (treeposVal.size() <= id) {
		treeposVal.push_back(0);
	}

	treeposVal[id] = rv;
}



int
BACnetProperty::MapTypeToValue(BACenums::BACPropType pt)
{
	return(MapTypeToValue((int)pt));
}


// MAG 260507
// Purpose: Set the 'value' class member type based on input propID. Will require accessing object type for some propID.
int BACnetProperty::SetValueType(int propID)
{
	BACvalue lbv = {};

	value.clear();  // value array must be empty. lbv or array of lbv is added below.

	if (propID < 0) return -1;
	if (propID >= BAClabels::PropertyLabels.size()) return -1;

	switch (propID) {
	case 0: lbv.type = 8; break;
	case 2: lbv.type = 9; break;
	case 4: lbv.type = 7; break;
	//case 5: lbv.type = x; break;
	case 6: lbv.type = 9; break;
	case 7: lbv.type = 2; break;
	case 10: lbv.type = 2; break;
	case 11: lbv.type = 2; break;
	case 12: lbv.type = 7; break;
	case 14: lbv.type = 4; break;
	case 15: lbv.type = 2; break;
	case 16: lbv.type = 10; value.push_back(lbv); lbv.type = 11; break;  // sequence 10, 11
	case 17: lbv.type = 2; break;
	case 19: lbv.type = 12; value.push_back(lbv); lbv.type = 9; value.push_back(lbv); lbv.type = 2; break;//seq 12, 9, 2
	case 20: lbv.type = 9; break;
	case 21: lbv.type = 4; break;
	case 22: lbv.type = 4; break;
	case 24: lbv.type = 1; break;
	case 25: lbv.type = 4; break;
	case 26: lbv.type = 4; break;
	case 27: lbv.type = 9; break;
	case 28: lbv.type = 7; break;
	case 30: lbv.type = 12; value.push_back(lbv); lbv.type = 2; value.push_back(lbv); lbv.type = 6; break;//seq 12, 2, 6
	case 31: lbv.type = 7; break;
	case 33: lbv.type = 2; break;
	case 34: lbv.type = 4; break;
	case 35: lbv.type = 8; break;
	case 36: lbv.type = 9; break;
	case 39: lbv.type = 2; break;
	case 40: lbv.type = 2; break;
	case 44: lbv.type = 7; break;
	case 45: lbv.type = 4; break;
	case 46: lbv.type = 7; break;
	case 49: lbv.type = 4; break;
	case 50: lbv.type = 9; break;
	case 52: lbv.type = 8; break;
	case 56: lbv.type = 10; break;
	case 57: lbv.type = 11; break;
	case 58: lbv.type = 7; break;
	case 59: lbv.type = 4; break;
	case 60: lbv.type = 12; value.push_back(lbv); lbv.type = 9; value.push_back(lbv); lbv.type = 2; break;//seq 12, 9, 2
	case 61: lbv.type = 4; break;
	case 62: lbv.type = 2; break;
	case 63: lbv.type = 2; break;
	case 64: lbv.type = 2; break;
	case 65: lbv.type = 4; break;
	case 67: lbv.type = 2; break;
	case 68: lbv.type = 4; break;
	case 69: lbv.type = 4; break;
	case 70: lbv.type = 7; break;
	case 72: lbv.type = 9; break;
	case 73: lbv.type = 2; break;
	case 74: lbv.type = 2; break;
	case 75: lbv.type = 12; break;
	case 76: lbv.type = 12; break;
	case 77: lbv.type = 7; break;
	case 79: lbv.type = 9; break;
	case 81: lbv.type = 1; break;
	case 82: lbv.type = 9; break;
	case 84: lbv.type = 9; break;
	case 85: lbv.type = 2; break;
	//case 87: lbv.type = seq[16] of BACnetPriorityValue; break;
	case 88: lbv.type = 2; break;
	case 93: lbv.type = 4; break;
	case 94: lbv.type = 9; break;
	case 96: lbv.type = 8; break;
	case 97: lbv.type = 8; break;
	case 98: lbv.type = 2; break;
	case 103: lbv.type = 9; break;
	case 104: lbv.type = 2; break;
	case 106: lbv.type = 4; break;
	case 107: lbv.type = 9; break;
	case 108: lbv.type = 4; break;
	case 109: lbv.type = 12; value.push_back(lbv); lbv.type = 9; value.push_back(lbv); lbv.type = 2; break;//seq 12, 9, 2
	case 110: lbv.type = 7; break;
	case 111: lbv.type = 8; break;
	case 112: lbv.type = 9; break;
	case 113: lbv.type = 2; break;
	case 114: lbv.type = 10; value.push_back(lbv); lbv.type = 11; break;  // sequence 10, 11
	case 115: lbv.type = 10; value.push_back(lbv); lbv.type = 11; break;  // sequence 10, 11
	//case 116: lbv.type = x; break;
	case 117: lbv.type = 9; break;
	case 118: lbv.type = 2; break;
	case 119: lbv.type = 3; break;
	case 120: lbv.type = 2; break;
	case 121: lbv.type = 7; break;
	case 122: lbv.type = 9; break;
	//case 130: lbv.type = Choice of 11, 2, or (10, 11); break;
	case 139: lbv.type = 2; break;
	//case 152: lbv.type = x; break;
	case 153: lbv.type = 2; break;
	case 154: lbv.type = 12; break;
	case 155: lbv.type = 2; break;
	//case 157: lbv.type = Choice of 11, 2, or (10, 11); break;
	case 167: lbv.type = 2; break;
	case 168: lbv.type = 7; break;
	case 169: lbv.type = 12; value.push_back(lbv); lbv.type = 2; value.push_back(lbv); lbv.type = 6; break;//seq 12, 2, 6
	case 170: lbv.type = 12; value.push_back(lbv); lbv.type = 2; value.push_back(lbv); lbv.type = 6; break;//seq 12, 2, 6
	case 171: lbv.type = 1; break;
	case 172: lbv.type = 1; break;
	case 193: lbv.type = 1; break;
	case 195: lbv.type = 2; break;
	case 196: lbv.type = 9; break;
	//case 202: lbv.type = x; break;
	//case 203: lbv.type = Choice of 11, 2, or (10, 11); break;
	case 204: lbv.type = 2; break;
	case 209: lbv.type = 12; break;
	case 338: lbv.type = 9; break;
	case 339: lbv.type = 2; break;
	case 340: lbv.type = 2; break;
	case 341: lbv.type = 2; break;
	case 351: lbv.type = 7; break;
	case 352: lbv.type = 7; break;
	case 353: lbv.type = 1; break;
	case 354: lbv.type = 12; value.push_back(lbv); lbv.type = 9; value.push_back(lbv); lbv.type = 2; break;//seq 12, 9, 2
	case 355: lbv.type = 1; break;
	case 356: lbv.type = 2; break;
	case 357: lbv.type = 1; break;
	case 372: lbv.type = 7; break;
	default: lbv.type = 1; break;
	}
	value.push_back(lbv);

	return 1;
}


// Maps Property Type to type used in BACvalue
int 
BACnetProperty::MapTypeToValue(int /*BACenums::BACPropType*/ pt)
{
	switch ((int)pt) {
		// type (1)://  1 bool
		case(88): // BOOLEAN,
			return 1;
			// type (2)://  2 unsigned int
		case(50): // BACnetEngineeringUnits,
		case(52): // BACnetEventState,
		case(64): // BACnetNotifyType,
		case(67): // BACnetObjectType,
		case(75): // BACnetReliability,
		case(118): // Unsigned_1to16, 
		case(119): // Unsigned_1to127, 
		case(120): // Unsigned_1to16b, 
		case(121): // Unsigned, 
		case(122): // Unsigned16, 
		case(123): // Unsigned32, 
		case(124): // Unsigned8, 
			return 2;
			// type (3)://  3 signed int
			//	return 3;
			// type (4)://  4 real
		case(116): // REAL, 
			return 4;
			// type (5)://  5 double
			//	return 5;
			// type (6)://  6 octet[100]
			//	return 6;
			// type (7)://  7 char[100]
		//case(88):
		case(89): // CharacterString,
			return 7;
			// type (8)://  8 bit string octet[100]
		case(53): // BACnetEventTransitionBits,
		case(59): // BACnetLimitEnable,
		case(85): // BACnetStatusFlags,
			return 8;
			// type (9)://  9 enumerated (unsigned int)
		case(56):	// local-date
			return 9;
			// type (10):// 10 BACnet Date
			return 10;
			// type (11):// 11 BACnet Time
			return 11;
			// type (12):// 12 object id
		case(65): // BACnetObjectIdentifier,
			return 12;
			// default: need to do something to handle these! These are composite or complex types, need to add second map subroutine
		case(42): // BACnetDateTime,
		case(66): // BACnetObjectPropertyReference,
		case(71): // BACnetPriorityArray,
		default:
			return -1;
		/*
		//select from following, add (int) to switch above in correct type
		//				case(  1): // Any
		//				case(  2): // BACnetAccessCredentialDisable
		//				case(  3): // BACnetAccessEvent
		//				case(  4): // BACnetAccessPassbackMode
		//				case(  5): // BACnetAccessThreatLevel
		//				case(  6): // BACnetAccessUserType
		//				case(  7): // BACnetAccessZoneOccupancyState
		//				case(  8): // BACnetAccumulatorRecord
		//				case(  9): // BACnetAction
		//				case( 10): // BACnetAddressBinding,
		//				case( 11): // BACnetARRAY_F3_of_BACnetTimeStamp,
		//				case( 12): // BACnetSecurityKeySet,
		//				case( 13): // BACnetARRAY_3_of_BACnetTimeStamp,
		//				case( 14): // BACnetARRAY_3_of_CharacterString,
		//				case( 15): // BACnetARRAY_3_of_Unsigned,
		//				case( 16): // BACnetARRAY_7_of_BACnetDailySchedule,
		//				case( 17): // BACnetARRAY_N_of_BACnetAccessRule,
		//				case( 18): // BACnetARRAY_N_of_BACnetActionList,
		//				case( 19): // BACnetARRAY_N_of_BACnetAssignedAccessRights,
		//				case( 20): // BACnetARRAY_N_of_BACnetAuthenticationFactorFormat,
		//				case( 21): // BACnetARRAY_N_of_BACnetAuthenticationPolicy,
		//				case( 22): // BACnetARRAY_N_of_BACnetCredentialAuthenticationFactor,
		//				case( 23): // BACnetARRAY_N_of_BACnetDeviceObjectPropertyReference,
		//				case( 24): // BACnetARRAY_N_of_BACnetDeviceObjectReference,
		//				case( 25): // BACnetNetworkSecurityPolicy,
		//				case( 26): // BACnetARRAY_N_of_BACnetObjectIdentifier,
		//				case( 27): // BACnetARRAY_N_of_BACnetOptionalCharacterString,
		//				case( 28): // BACnetARRAY_N_of_BACnetPropertyAccessResult,
		//				case( 29): // BACnetARRAY_N_of_BIT_STRING,
		//				case( 30): // BACnetARRAY_N_of_BOOLEAN,
		//				case( 31): // BACnetARRAY_N_of_CharacterString,
		//				case( 32): // BACnetARRAY_N_of_Unsigned,
		//				case( 33): // BACnetARRAY_N_of,
		//				case( 34): // BACnetARRAY_N_of_BACnetSpecialEvent,
		//				case( 35): // BACnetAuthenticationFactor,
		//				case( 36): // BACnetAuthenticationStatus,
		//				case( 37): // BACnetAuthorizationMode,
		//				case( 38): // BACnetBackupState,
		//				case( 39): // BACnetBinaryPV,
		//				case( 40): // BACnetClientCOV,
		//				case( 41): // BACnetDateRange,
		//				case( 43): // BACnetDeviceObjectPropertyReference,
		//				case( 44): // BACnetDeviceObjectReference,
		//				case( 45): // BACnetDeviceStatus,
		//				case( 46): // BACnetDoorAlarmState,
		//				case( 47): // BACnetDoorSecuredStatus,
		//				case( 48): // BACnetDoorStatus,
		//				case( 49): // BACnetDoorValue,
		//				case( 51): // BACnetEventParameter,
		//				case( 54): // BACnetEventType,
		//				case( 55): // BACnetFileAccessMethod,
		//				case( 56): // BACnetLifeSafetyMode,
		//				case( 57): // BACnetLifeSafetyOperation,
		//				case( 58): // BACnetLifeSafetyState,
		//				case( 59): // BACnetLimitEnable,
		//				case( 60): // BACnetLockStatus,
		//				case( 61): // BACnetLoggingType,
		//				case( 62): // BACnetMaintenance,
		//				case( 63): // BACnetNodeType,
		//				case( 68): // BACnetObjectTypesSupported,
		//				case( 69): // BACnetPolarity,
		//				case( 70): // BACnetPrescale,
		//				case( 72): // BACnetProgramError,
		//				case( 73): // BACnetProgramRequest,
		//				case( 74): // BACnetProgramState,
		//				case( 76): // BACnetRestartReason,
		//				case( 77): // BACnetScale,
		//				case( 78): // BACnetSecurityLevel,
		//				case( 79): // BACnetSegmentation,
		//				case( 80): // BACnetServicesSupported,
		//				case( 81): // BACnetSetpointReference,
		//				case( 82): // BACnetShedLevel,
		//				case( 83): // BACnetShedState,
		//				case( 84): // BACnetSilencedState,
		//				case( 87): // BIT_STRING,
		//				case( 90): // Date,
		//				case( 91): // Double,
		//				case( 92): // INTEGER,
		//				case( 93): // List_of_BACnetAccessCredentialDisableReason,
		//				case( 94): // List_of_BACnetAccessEvent,
		//				case( 95): // List_of_BACnetAccessZoneOccupancyState,
		//				case( 96): // List_of_BACnetAddressBinding,
		//				case( 97): // List_of_BACnetCalendarEntry,
		//				case( 98): // List_of_BACnetCOVSubscription,
		//				case( 99): // List_of_BACnetDestination,
		//				case(100): // List_of_BACnetDeviceObjectPropertyReference,
		//				case(101): // List_of_BACnetDeviceObjectReference,
		//				case(102): // List_of_BACnetDoorAlarmState,
		//				case(103): // List_of_BACnetEventLogRecord,
		//				case(104): // List_of_BACnetLifeSafetyMode,
		//				case(105): // List_of_BACnetLifeSafetyState,
		//				case(106): // List_of_BACnetLogMultipleRecord,
		//				case(107): // List_of_BACnetLogRecord,
		//				case(108): // List_of_BACnetRecipient,
		//				case(109): // List_of_BACnetVTClass,
		//				case(110): // List_of_BACnetVTSession,
		//				case(111): // List_of_ReadAccessResult,
		//				case(112): // List_of_ReadAccessSpecification,
		//				case(113): // List_of_Unsigned,
		//				case(114): // List_of_Unsigned8,
		//				case(115): // OCTET_STRING,
		//				case(117): // Time,
		//				case(125): // List_of_BACnetAuthorizationExemption,
		//				case(126): // BACnetFaultType,
		//				case(127): // BACnetFaultParameter,
		//				case(128): // BACnetEventStatus,
		//				case(129): // BACnetEventNotificationSubscription,
		//				case(130): // BACnetProcessIdSelection,
		//				case(131): // BACnetPortPermission,
		//				case(132): // BACnetLightingCommand,
		//				case(133): // BACnetLightingInProgress,
		//				case(134): // BACnetLightingTransition,
		//				case(135): // BACnetChannelValue,
		//				case(136): // BACnetWriteStatus,
		//	}*/

		return -1;
	}
}


// Must have object type to determine type of some props
// From BACnetPropertyIdentifier enumeration
// inputs are object type and property identifier
BACenums::BACPropType 
BACnetProperty::GetPropertyVarType(int obj, int prop)  
{
	if (prop >= 511) return BACenums::BACPropType::ERROR_NOT_ENUM;
	// NOTE 136 == number of property types

	// check props where it's always the same type first
	switch (prop) {
		case(2): return BACenums::BACPropType::en_BACnetAction;                              // action
		case(4): return BACenums::BACPropType::en_CharacterString;                           // active-text
		case(5): return BACenums::BACPropType::en_List_of_BACnetVTSession;                   // active-vt-sessions
		case(6): return BACenums::BACPropType::en_BACnetBinaryPV;                            // alarm-value
		case(7): return BACenums::BACPropType::en_Unsigned;                                  // alarm-values
		case(12): return BACenums::BACPropType::en_CharacterString;                           // application-software-version
		case(14): return BACenums::BACPropType::en_REAL;                                      // bias
		case(16): return BACenums::BACPropType::en_BACnetDateTime;                            // change-of-state-time
		case(17): return BACenums::BACPropType::en_Unsigned;                                  // notification-class
		case(19): return BACenums::BACPropType::en_BACnetObjectPropertyReference;             // controlled-variable-reference
		case(20): return BACenums::BACPropType::en_BACnetEngineeringUnits;                    // controlled-variable-units
		case(21): return BACenums::BACPropType::en_REAL;                                      // controlled-variable-value
		case(24): return BACenums::BACPropType::en_BOOLEAN;                                   // daylight-savings-status
		case(25): return BACenums::BACPropType::en_REAL;                                      // deadband
		case(27): return BACenums::BACPropType::en_BACnetEngineeringUnits;                    // derivative-constant-units
		case(28): return BACenums::BACPropType::en_CharacterString;                           // description
		case(30): return BACenums::BACPropType::en_BACnetAddressBinding;                      // device-address-binding
		case(31): return BACenums::BACPropType::en_CharacterString;                           // device-type
		case(33): return BACenums::BACPropType::en_Unsigned32;                                // elapsed-active-time
		case(34): return BACenums::BACPropType::en_REAL;                                      // error-limit
		case(35): return BACenums::BACPropType::en_BACnetEventTransitionBits;                 // event-enable
		case(36): return BACenums::BACPropType::en_BACnetEventState;                          // event-state
		case(39): return BACenums::BACPropType::en_Unsigned;                                  // fault-values
		case(44): return BACenums::BACPropType::en_CharacterString;                           // firmware-revision
		case(45): return BACenums::BACPropType::en_REAL;                                      // high-limit
		case(46): return BACenums::BACPropType::en_CharacterString;                           // inactive-text
		case(49): return BACenums::BACPropType::en_REAL;                                      // integral-constant
		case(50): return BACenums::BACPropType::en_BACnetEngineeringUnits;                    // integral-constant-units
		case(52): return BACenums::BACPropType::en_BACnetLimitEnable;                         // limit-enable
		case(56): return BACenums::BACPropType::en_Date;                                      // local-date
		case(57): return BACenums::BACPropType::en_Time;                                      // local-time
		case(58): return BACenums::BACPropType::en_CharacterString;                           // location
		case(59): return BACenums::BACPropType::en_REAL;                                      // low-limit
		case(60): return BACenums::BACPropType::en_BACnetObjectPropertyReference;             // manipulated-variable-reference
		case(61): return BACenums::BACPropType::en_REAL;                                      // maximum-output
		case(62): return BACenums::BACPropType::en_Unsigned;                                  // max-apdu-length-accepted
		case(65): return BACenums::BACPropType::en_REAL;                                      // max-pres-value
		case(66): return BACenums::BACPropType::en_Unsigned32;                                // minimum-off-time
		case(68): return BACenums::BACPropType::en_REAL;                                      // minimum-output
		case(70): return BACenums::BACPropType::en_CharacterString;                           // model-name
		case(72): return BACenums::BACPropType::en_BACnetNotifyType;                          // notify-type
		case(73): return BACenums::BACPropType::en_Unsigned;                                  // number-of-apdu-retries
		case(75): return BACenums::BACPropType::en_BACnetObjectIdentifier;                    // object-identifier
		case(77): return BACenums::BACPropType::en_CharacterString;                           // object-name
		case(79): return BACenums::BACPropType::en_BACnetObjectType;                          // object-type
		case(81): return BACenums::BACPropType::en_BOOLEAN;                                   // out-of-service
		case(82): return BACenums::BACPropType::en_BACnetEngineeringUnits;                    // output-units
		case(84): return BACenums::BACPropType::en_BACnetPolarity;                            // polarity
		case(87): return BACenums::BACPropType::en_BACnetPriorityArray;                       // priority-array
		case(88): return BACenums::BACPropType::en_Unsigned;                                  // priority-for-writing
		case(93): return BACenums::BACPropType::en_REAL;                                      // proportional-constant
		case(94): return BACenums::BACPropType::en_BACnetEngineeringUnits;                    // proportional-constant-units
		case(96): return BACenums::BACPropType::en_BACnetObjectTypesSupported;                // protocol-object-types-supported
		case(97): return BACenums::BACPropType::en_BACnetServicesSupported;                   // protocol-services-supported
		case(98): return BACenums::BACPropType::en_Unsigned;                                  // protocol-version
		case(103): return BACenums::BACPropType::en_BACnetReliability;                         // reliability
		case(106): return BACenums::BACPropType::en_REAL;                                      // resolution
		case(107): return BACenums::BACPropType::en_BACnetSegmentation;                        // segmentation-supported
		case(108): return BACenums::BACPropType::en_REAL;                                      // setpoint
		case(109): return BACenums::BACPropType::en_BACnetSetpointReference;                   // setpoint-reference
		case(110): return BACenums::BACPropType::en_CharacterString;                           // state-text
		case(111): return BACenums::BACPropType::en_BACnetStatusFlags;                         // status-flags
		case(112): return BACenums::BACPropType::en_BACnetDeviceStatus;                        // system-status
		case(113): return BACenums::BACPropType::en_Unsigned;                                  // time-delay
		case(114): return BACenums::BACPropType::en_BACnetDateTime;                            // time-of-active-time-reset
		case(116): return BACenums::BACPropType::en_List_of_BACnetRecipient;                   // time-synchronization-recipients
		case(117): return BACenums::BACPropType::en_BACnetEngineeringUnits;                    // units
		case(118): return BACenums::BACPropType::en_Unsigned;                                  // update-interval
		case(119): return BACenums::BACPropType::en_INTEGER;                                   // utc-offset
		case(120): return BACenums::BACPropType::en_Unsigned16;                                // vendor-identifier
		case(121): return BACenums::BACPropType::en_CharacterString;                           // vendor-name
		case(122): return BACenums::BACPropType::en_List_of_BACnetVTClass;                     // vt-classes-supported
		case(130): return BACenums::BACPropType::en_BACnetTimeStamp;                           // event-time-stamps
		case(139): return BACenums::BACPropType::en_Unsigned;                                  // protocol-revision
		case(152): return BACenums::BACPropType::en_List_of_BACnetCOVSubscription;             // active-cov-subscriptions
		case(153): return BACenums::BACPropType::en_Unsigned16;                                // backup-failure-timeout
		case(154): return BACenums::BACPropType::en_BACnetObjectIdentifier;                    // configuration-files
		case(155): return BACenums::BACPropType::en_Unsigned;                                  // database-revision
		case(157): return BACenums::BACPropType::en_BACnetTimeStamp;                           // last-restore-time
		case(167): return BACenums::BACPropType::en_Unsigned;                                  // max-segments-accepted
		case(168): return BACenums::BACPropType::en_CharacterString;                           // profile-name
		case(169): return BACenums::BACPropType::en_BACnetAddressBinding;                      // auto-slave-discovery
		case(171): return BACenums::BACPropType::en_BOOLEAN;                                   // slave-address-binding
		case(195): return BACenums::BACPropType::en_Unsigned;                                  // interval-offset
		case(196): return BACenums::BACPropType::en_BACnetRestartReason;                       // last-restart-reason
		case(202): return BACenums::BACPropType::en_List_of_BACnetRecipient;                   // restart-notification-recipients
		case(203): return BACenums::BACPropType::en_BACnetTimeStamp;                           // time-of-device-restart
		case(204): return BACenums::BACPropType::en_Unsigned;                                  // time-synchronization-interval
		case(209): return BACenums::BACPropType::en_BACnetObjectIdentifier;                    // structured-object-list
		case(338): return BACenums::BACPropType::en_BACnetBackupState;                         // backup-and-restore-state
		case(339): return BACenums::BACPropType::en_Unsigned16;                                // backup-preparation-time
		case(351): return BACenums::BACPropType::en_CharacterString;                           // event-message-texts
		case(353): return BACenums::BACPropType::en_BOOLEAN;                                   // event-detection-enable
		case(354): return BACenums::BACPropType::en_BACnetObjectPropertyReference;             // event-algoriithm-inhibit-ref
		case(355): return BACenums::BACPropType::en_BOOLEAN;                                   // event-algoriithm-inhibit
		case(356): return BACenums::BACPropType::en_Unsigned;                                  // time-delay-normal
		case(357): return BACenums::BACPropType::en_BOOLEAN;                                   // reliability-evaluation-inhibit
		case(372): return BACenums::BACPropType::en_CharacterString;                           // serial-number
		default: break;
	}

	if ((obj < 0) || (obj >= BAClabels::ObjectLabels.size())) return BACenums::BACPropType::ERROR_NOT_ENUM;

	// Most common type gets default
	switch (prop) {
		case(15):
			switch (obj) {
				case (5):	return BACenums::BACPropType::en_Unsigned32;						// change-of-state-count BV
				default:	return BACenums::BACPropType::en_Unsigned;							// change-of-state-count BI, BO
			}
		case(40):
			switch (obj) {
				case (4): return BACenums::BACPropType::en_BACnetBinaryPV;						// feedback-value BO
				default:  return BACenums::BACPropType::en_Unsigned;							// feedback-value MO
			}
		case(85):
			switch(obj){
				case 0:  // AI
				case 1:  // AO
				case 2:  // AV
					return BACenums::BACPropType::en_REAL;											// present-value // AI AO AV
				case 3:  // BI
				case 4:  // BO
				case 5:  // BV
					return BACenums::BACPropType::en_BACnetBinaryPV;								// present-value  // BI BO BV
				default: return BACenums::BACPropType::en_Unsigned;									// present-value  // MI MO MV
			}
		case(104): 
			switch (obj) {
				case 1:  // AO
				case 2:  // AV
					return BACenums::BACPropType::en_REAL;											// present-value // AI AO AV
				case 4:  // BO
				case 5:  // BV
					return BACenums::BACPropType::en_BACnetBinaryPV;								// present-value  // BI BO BV
				default: return BACenums::BACPropType::en_Unsigned;									// present-value  // MI MO MV
			}
	}  // end switch 2

	return BACenums::BACPropType::ERROR_TYPE_NOT_SUPPORTED;
}

std::string 
BACnetProperty::GetValueString()
{
	std::string rval;  // add label and value

	rval = label + ": " + BACfuncs::BACvalueToString(&value[0]);

	return rval;
}


// save to array of strings- usually one line, could be more if value is array type
std::vector<std::string>	
BACnetProperty::GetXMLString()
{
	std::vector<std::string> rv;
	std::stringstream ss1;
	std::string vs1;
	int ecount = 0;

	ss1 << "<property type=\"" << (int)propType << "\" label=\"" << label << "\" >";
	for (size_t ival = 0; ival < value.size(); ival++){
		vs1 = BACfuncs::BACvalueToString(&value[ival]);
		ss1 << "<value type=\"" << (int)value[ival].type << "\" >" << vs1 << "</value>";
		if (ss1.str().size() - ecount > 900) {
			ecount += 900;
			ss1 << std::endl;
		}
	}
	ss1 << "</property>";

	rv.push_back(ss1.str());

	return rv;
}


// Purpose: wipes out content of value array, preserves type.
void BACnetProperty::ClearPropValues()
{
	BACvalue bv = {};
	
	bv.type = value[0].type;;
	value.clear();
	value.push_back(bv);
	treeposVal.push_back(0);

}