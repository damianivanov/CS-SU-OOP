#include "XML.h"
#include <iostream>
#include <regex>
#include <unordered_map>
	
XML::XML(){}
XML::XML(std::vector<std::string> content) {
	this->content = content;
	this->Deserialization();
}
XML* XML::operator=(const XML& other) {
	this->content = other.content;
	this->Deserialized = other.Deserialized;
	return this;
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
	if (element.get_childs().size() != 0)
	{
		auto childs = element.get_childs();
		for (auto x : childs)
		{
			cout << x.To_string() << endl;
		}
	}
	else
		cout << element.get_text() << endl;
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
	return *element;
}
void XML::NewChild(string id)
{
	Element* element = Element_ById(id);
	Element new_child;
	//TODO
	new_child.set_id(to_string(Same_ID("none")));
	new_child.set_parent(*element);
	element->add_child(new_child);
	int i = Index_ById(element->get_id());
	int tabs = Tabs(content[i])+1;
	//adding new child to content for serialization
	Deserialized.insert(Deserialized.begin() + i+1, *element);
	Deserialized.erase(Deserialized.begin() + i);
	Deserialized.insert(Deserialized.begin() + i+element->get_childs().size(), new_child);
}

vector<Element> XML::get_Deserialized() {return Deserialized;}
vector<string> XML::get_Content(){return this->content;}

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
void XML::Deserialization()
{
	for (auto line : content)
	{
		Element el;
		el.Extract_name(line);
		el.set_tabs(Tabs(line));
		if (!el.IsClosingTag())
		{
			el.Extract_attributes(line);
			el.Extract_text(line);

			//--mash potatoes-- 
			//if (el.get_id() != "none")
			//{ 
			//	//check if there are no duplicates
			//	if (Duplicates(el.get_id()))
			//	{
			//		int next_Id = Free_Id(el.get_id());
			//		string new_Id = el.get_id() + "_" + to_string(next_Id);
			//		el.set_id(new_Id);
			//		el.Add_attribute("id", new_Id);
			//	}
			//}
			//}
			//else
			//{
			//	string new_id = to_string(Deserialized.size());
			//	el.set_id(new_id);
			//	el.Add_attribute("id", to_string(Deserialized.size()));
			//}
		}
		Add_Element(el);		
	}
	ID_Setter();
	Setting_Parents();
	Setting_Childs();
}
void XML::Serialization() {
	content.clear();
	for (size_t i = 0; i < Deserialized.size(); ++i)
	{
		string curr = Deserialized[i].To_string()+"\n";
		content.push_back(curr);
	}
}
void XML::Clear() {
	Deserialized.clear();
	content.clear();
}

void XML::Add_Element(Element &element) {this->Deserialized.push_back(element);}
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
	int counter = 0;
	for (auto x : Deserialized)
	{
		if (x.get_id() == value)
			counter++;
	}
	return counter > 1;
}
int XML::Same_ID(string value) {
	int with_same_Id = 0;
	for (auto x : Deserialized)
	{
		////only way to put parameters in regex
		//string regexQuery = "["+ value+ "]|(?!\")[" + value+ "](?=_)";
		//regex r_id(regexQuery);
		//smatch s_id;
		//string curr_Id = x.get_id();	
		//// for 0_1; 0_2 etc
		//regex_search(curr_Id,s_id,r_id);
		//return s_id.size();
		if (x.get_id()==value)
		{
			with_same_Id++;
		}
	}
	return with_same_Id;
}
int XML::Tabs(string line) {

	//Bug Found that \t\t\t<...>...</...>\t 
	//returns 4 instead of 3
	regex r_before_open_tag("(.*?<)");
	smatch m_before_open_tag;
	regex_search(line, m_before_open_tag, r_before_open_tag);
	string substring = m_before_open_tag.str();

	regex r_tabs("\\t");
	smatch m_tabs;
	//stackoverflow
	return distance(sregex_iterator(substring.begin(), substring.end(), r_tabs), sregex_iterator());
}
int XML::Index_ById(string id)
{
	int index = 0;
	for (auto x : Deserialized)
	{
		if (x.get_id()==id)
			return index;
		index++;
	}
	return 0;
}
void XML::ID_Setter() 
{
	for (auto element:Deserialized)
	{
		if (Duplicates(element.get_id())&&element.get_id()!="none")
		{
			//int with_same_id = Same_ID(element.get_id());
			int counter = 1;
			for (auto z : Deserialized)
			{
				if (z.get_id()==element.get_id())
				{
					Deserialized.at(Index_ById(z.get_id())).set_id(element.get_id() + "_" + to_string(counter));
					counter++;
				}
			}
		}
	}

}