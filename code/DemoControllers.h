#pragma once
#include "pch.h"
//#include <vector>
//#include <string>

// class to hold data for property templates
class PropertyTemplateA {
public:
	int ptype;			// property type (index into BACnetPropertyType? array)
	int vtype;			// variable type (application encoding type)
	int pIndex;			// property index
	std::string pvalue;	// variable value (as a text string)
	PropertyTemplateA() { ptype = 0; vtype = 0; pIndex = -1; };
	PropertyTemplateA(int a, int b, char* c) { ptype = a; vtype = b; pIndex = -1; pvalue = c; };
	PropertyTemplateA(int a, int b, int c, char* d) { ptype = a; vtype = b; pIndex = c; pvalue = d; };
};

class ObjectTemplate {
public:
	int otype;			// object type
	int oinstance;		// object instance
	std::vector<PropertyTemplateA> ptList; 

	int InitObjectTemplate();
	ObjectTemplate() { otype = -1; oinstance = -1;};
	ObjectTemplate(int ot, int oi) { otype = ot; oinstance = oi; }; // MAG need to add range check
};

