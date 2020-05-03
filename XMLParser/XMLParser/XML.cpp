#include "XML.h"
#include <iostream>
#include <regex>
#include <unordered_map>
	
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
	Element* element = Element_ById(id);
	map<string,string> attributes = element->get_attributes();
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
	Element* element = Element_ById(id);
	map<string, string> attributes = element->get_attributes();
	int index = 0;
	attributes[key] = value;
	for (map<string,string>::iterator it = attributes.find(key); it != attributes.cend(); ++it)
	{
		if (it->first == key)
		{
			if (key=="id")
			{
				element->set_id(value);
			}
			it->second = value;
		}
		index++;
	}
	
	element->set_attributes(attributes);
	Deserialized.erase(Deserialized.begin() + index-1);
	Deserialized.insert(Deserialized.begin() + index, *element);	
}
void XML::Text(string id) {

	Element element = *Element_ById(id);	
	cout << element.get_text();
}
void XML::Delete(string id, string key) {

	Element element = *Element_ById(id);
	map<string, string> attributes = element.get_attributes();	
	attributes.erase(key);	
	Deserialized.at(Index_ById(id)).set_attributes(attributes);
}
void XML::Children(string id) {
	Element element = *Element_ById(id);
	for (auto child : element.get_childs())
	{
		cout << "-" << child.get_name();
		for(auto attribute:child.get_attributes())
		{
			 cout << "\t" << attribute.first << "=" << attribute.second << endl;
		}
	}
}
Element& XML::Child(string id, size_t n)
{
	Element* element = Element_ById(id);
	if (n >= 0 && n < element->get_childs().size())
	{
		string id = element->get_childs().at(n).get_id();
		return *Element_ById(id);
	}
}
void XML::NewChild(string id)
{
	Element* element = Element_ById(id);
	Element new_child;
	new_child.set_id(to_string(Free_Id("none")));
	new_child.set_parent(*element);
	element->add_child(new_child);
	int i = Index_ById(element->get_id());
	Deserialized.insert(Deserialized.begin() + i+1, *element);
	Deserialized.erase(Deserialized.begin() + i);
	Deserialized.insert(Deserialized.begin() + i+element->get_childs().size(), new_child);
}

Element* XML::Element_ById(string id) {
	int index = 0;
	for (auto element : Deserialized)
	{
		if (element.get_id() == id)
			break;
		index++;
	}
	Element* element = &Deserialized.at(index);
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
		if (!el.IsClosingTag())
		{
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
		}
		Add_Element(el);
		
	}
	Setting_Parents();
	Setting_Childs();
}
void XML::Serialization() {
		
}

void XML::Setting_Parents() {
	unordered_map<int,Element*> tmp;
	int size = Deserialized.size();
	for (int i = 0; i < size; ++i)
	{
		if (Deserialized.at(i).IsClosingTag())
		{
			continue;
		}
		int tabs = Tabs(content[i]);
		tmp[tabs]=&Deserialized.at(i);
		if (tabs != 0)
		{
			for (auto x: tmp)
			{
				if (x.first==tabs-1)
				{
					Deserialized.at(i).set_parent(*tmp[tabs-1]);
				}
			}			
		}
	}
}
void XML::Setting_Childs()
{
	int size = Deserialized.size();
	for (int i = 0; i < size; ++i)
	{
		string curr_id = Deserialized.at(i).get_id();
		for (Element element : Deserialized)
		{
			if (element.IsClosingTag())
			{
				continue;
			}
			string element_parent_Id;
			if (element.get_parent() != NULL)
			{
				element_parent_Id = element.get_parent()->get_id();
			}
			if (curr_id ==  element_parent_Id)
			{
				Element& curr_element = *Element_ById(element.get_id());
				Deserialized.at(i).add_child(curr_element);
			}
		}
	}
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
		string regexQuery = "["+ value+ "]|(?!\")[" + value+ "](?=_)";
		regex r_id(regexQuery);
		smatch s_id;
		string curr_Id = x.get_id();		 
		regex_search(curr_Id,s_id,r_id);
		return s_id.size();
	}
	return with_same_Id;
}
int XML::Tabs(string line) {
	regex r_tabs("\\t");
	smatch m_tabs;
	//stackoverflow
	return distance(sregex_iterator(line.begin(), line.end(), r_tabs), sregex_iterator());
	 
}
int XML::Index_ById(string id)
{
	int index = 0;
	for (auto x : Deserialized)
	{
		if (x.get_id()==id)
		{
			return index;
		}
		index++;
	}
}