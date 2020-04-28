#include "XML.h"
#include <iostream>
	
XML::XML(){}
XML::XML(std::vector<std::string> content) {
	this->content = content;
}
XML::~XML(){}
void XML::Print()
{
	for (auto x : content) {
		std::cout << x << "\n";
	}
}
void XML::Select(string id, string key)
{
	int index = 0;
	for (auto element:Deserialized)
	{
		if (element.get_id()==id)
			break;
		index++;
	}
	Element element = Deserialized.at(index);
	map<string,string> attributes = element.get_attributes();
	for (auto it = attributes.cbegin(); it != attributes.cend(); ++it)
	{
		if (it->first==key)
		{
			cout << it->second <<"\n";
		}
	}
}