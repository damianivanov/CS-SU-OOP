#include "Element.h"

Element::~Element(){}
Element::Element() { tabs=0 ; parent = NULL; }

Element& Element::operator= (const Element& other)
{
	this->tabs = other.tabs;
	this->attributes = other.attributes;
	this->childs = other.childs;
	this->parent = other.parent;
	this->name = other.name;
	this->text = other.text;
	this->id = other.id;
	return *this;
}

//getters
string Element::get_id() {return id;}
map<string, string> Element::get_attributes() {return attributes;}
vector<Element> Element::get_childs() {return childs;}
Element* Element::get_parent() {return parent;}
string Element::get_name() { return name; }
string Element::get_text() { return text; }
bool Element::IsClosingTag() { return name[0] == '/'; }
//setters
void Element::set_name(string name) { this->name = name; }
void Element::set_id(string id) { this->id = id; attributes["id"] = id;}
void Element::set_tabs(int tabs) { this->tabs = tabs; }
void Element::set_attributes(map<string, string> attributes) { this->attributes = attributes; }
void Element::add_child(const Element& child) {this->childs.push_back(child);}
void Element::set_parent(Element& parent) { this->parent = &parent; }

void Element::Add_attribute(string key, string value){
	attributes[key] = value;
}
void Element::Extract_name(string line)
{
	//<people>
	//regex r_name("(?!\\<)\\w*(?=\\>)|(?!\\<)\\w*(?= )|\\/\\w*(?=\\>)");
	regex r_name("[^\\<]\\w+(?=\\>)|[^\\<]\\w+(?=\\ )|\\/\\w*(?=\\>)");
	smatch m_name;
	regex_search(line, m_name, r_name);
	name = m_name.str();
}
void Element::Extract_attributes(string line)
{
	map<string,string> map = Attribute_parse(line);
	for (auto it = map.cbegin(); it != map.cend(); ++it)
	{
		string key = it->first;
		string value =it->second;

		if (key == "id")
			set_id(value);		
		attributes.insert(pair<string, string>(key,value));
	}
}
void Element::Extract_text(string line)
{
	regex r_text("(?!>)\\w*\\s*\\w*(?=\\<\\/)");
	smatch m_text;
	regex_search(line, m_text, r_text);
	text = m_text.str();
}

map<string, string> Element::Attribute_parse(string line) {

	map<string, string> result;
	regex r_key("(?! )\\w*(?=\\=)");
	regex r_value("(?!\")\\w+(?=\")");

	smatch m_key;
	smatch m_value;

	regex_search(line, m_key, r_key);
	regex_search(line, m_value, r_value);

	for (unsigned i = 0; i < m_key.size(); ++i) 
	{
		result.insert(pair<string,string>(m_key[i], m_value[i]));
	}
	return result;
}
string Element::To_string() {
	
	string result;
	for (int i = 0; i < tabs; i++)
	{
		result += "\t";
	}
	result+= "<" + name;
	if (attributes.size()!=0)
	{
		for (auto x : attributes)
		{
			result += " " + x.first + "=\"" + x.second + "\"";
		}
	}

	if (this->childs.size() == 0 && !this->IsClosingTag())
	{
		result += ">" + text;
		result += "</" + name + ">";
	}
	else
		result += ">";
	return result;
}