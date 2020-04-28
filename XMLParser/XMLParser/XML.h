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
private:
	std::vector<std::string> content;
	std::vector<Element> Deserialized;
};

