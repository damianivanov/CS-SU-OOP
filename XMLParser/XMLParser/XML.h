#pragma once
#include <string>
#include <vector>
#include <map>
#include "Element.h"

class XML
{
public:
	XML();
	XML(std::vector<std::string> content);
	~XML();

	void Print();
	void Deserialization();
	void Serialization();
	void Select(string id, string key);
	void Set(string id, string key, string value);
	void Text(string id);
	void Delete(string id, string key);
private:
	std::vector<std::string> content;
	std::vector<Element> Deserialized;
	void Add_Element(Element& element);
	Element Element_Id(string id);

	bool Duplicates(string value);
	int Free_Id(string value);
};

