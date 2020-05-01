#include "XML.h"
#include <iostream>
#include <regex>
	
XML::XML(){}
XML::XML(std::vector<std::string> content) {
	this->content = content;
}
XML::~XML(){}

//Requirments
void XML::Print()
{
	for (auto x : content) {
		std::cout << x << "\n";
	}
}
void XML::Select(string id, string key)
{
	Element element = Element_Id(id);
	map<string,string> attributes = element.get_attributes();
	for (auto it = attributes.cbegin(); it != attributes.cend(); ++it)
	{
		if (it->first==key)
		{
			cout <<key<<" = "<<it->second <<"\n";
		}
	}
}
void XML::Set(string id, string key, string value) 
{
	Element element = Element_Id(id);
	map<string, string> attributes = element.get_attributes();
	int index = 0;
	attributes[key] = value;
	for (map<string,string>::iterator it = attributes.find(key); it != attributes.cend(); ++it)
	{
		if (it->first == key)
		{
			if (key=="id")
			{
				element.set_id(value);
			}
			it->second = value;
		}
		index++;
	}
	
	element.set_attributes(attributes);
	Deserialized.erase(Deserialized.begin() + index-1);
	Deserialized.insert(Deserialized.begin() + index, element);	
}
void XML::Text(string id) {

	Element element = Element_Id(id);	
	cout << element.get_text();
}
void XML::Delete(string id, string key) {

	Element element = Element_Id(id);
	map<string, string> attributes = element.get_attributes();	
	attributes.erase(key);
	
}

Element XML::Element_Id(string id) {
	int index = 0;
	for (auto element : Deserialized)
	{
		if (element.get_id() == id)
			break;
		index++;
	}
	Element element = Deserialized.at(index);
	return element;
}
void XML::Add_Element(Element &element) {
	this->Deserialized.push_back(element);
}

void XML::Deserialization()
{
	for (auto line : content)
	{
		Element el;
		el.Extract_name(line);
		el.Extract_attributes(line);
		el.Extract_text(line);
		if (el.get_id() != "none")
		{
			//check if there are no duplicates
			if (Duplicates(el.get_id()))
			{
				int next_Id = Free_Id(el.get_id());
				string new_Id = el.get_id() + "_" + to_string(next_Id);
				el.set_id(new_Id);
				el.Add_attribute("id", new_Id);
			} 
		}
		else
		{
			string new_id = to_string(Deserialized.size());
			el.set_id(new_id);
			el.Add_attribute("id", to_string(Deserialized.size()));
		}
		Add_Element(el);
		
	}
}
void XML::Serialization() {
		
}

bool XML::Duplicates(string value)
{
	for (auto x : Deserialized)
	{
		if (x.get_id() == value) {
			return true;
		}
	}
	return false;
}
int XML::Free_Id(string value) {

	int with_same_Id = 0;
	for (auto x : Deserialized)
	{
		string regexQuery = "["+ value+ "]|(?!\")[" + value+ "](?=\_)";
		regex r_id(regexQuery);
		smatch s_id;
		string curr_Id = x.get_id();		 
		regex_search(curr_Id,s_id,r_id);
		return s_id.size();
	}
	return with_same_Id;
}