#pragma once
#include "XML.h"
#include <vector>

class XPath:private XML
{
public:
	XPath();
	XPath(vector<Element> deserialized);
	XPath* operator=(const XPath& other);
	virtual ~XPath() {}
	
	vector<string> Parser(string id,string xpath);

	vector<string> Dash(string element, string key);
	string Index(string element,string key,int index);
	vector<string> At(string id, string element);
	vector<string> Equal(string element, string key, string value);

private:
	vector<Element> Deserialized;
	vector<string> xpath_to_vector(string xpath);
};

