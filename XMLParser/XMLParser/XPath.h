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

	vector<string> Dash(vector<string> elements);
	string Index(vector<string> elements,int index);
	vector<string> At(string key, vector<string> elements);
	vector<string> Equal(vector<string> elements, string key, string value);

private:
	vector<Element> Deserialized;
	vector<string> xpath_to_vector(string xpath);
};

