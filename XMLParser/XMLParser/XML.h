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
	XML* operator=(const XML& other);

	vector<Element> get_Deserialized();
	vector<string> get_Content();

	Element* Element_ById(string id);
	void Deserialization();
	void Serialization();
	void Clear();
	
	void Print();
	void Select(string id, string key);
	void Set(string id, string key, string value);
	void Text(string id);
	void Delete(string id, string key);
	void Children(string id);
	Element& Child(string id, size_t n);
	void NewChild(string id);

private:
	std::vector<std::string> content;
	std::vector<Element> Deserialized;

	void Add_Element(Element& element);
	void Setting_Parents();
	void Setting_Childs();
	bool Duplicates(string value);
	int Free_Id(string value);
	int Tabs(string line);
	int Index_ById(string id);
	
};

