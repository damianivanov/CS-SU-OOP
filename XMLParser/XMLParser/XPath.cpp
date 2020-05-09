#include "XPath.h"

XPath::XPath() {}
XPath* XPath::operator=(const XPath& other)
{
	this->Deserialized = other.Deserialized;
	return this;
}
XPath::XPath(vector<Element> deserialized){
	this->Deserialized = deserialized;	
}

vector<string> XPath::Parser(string id, string xpath)
{
	vector<string> result;
	// = @ [] /
	if (xpath.find("=") != string::npos)
	{

	}
	else if (xpath.find('@')!=string::npos)
	{

	}
	else if (xpath.find('[')!=string::npos && xpath.find(']')!=string::npos) 
	{

	}
	else if (xpath.find('/')!=string::npos)
	{
		regex r_element("\\w+(?=\\/)");
		regex r_key("(?!\\/)\\w+$");

		smatch s_element;
		smatch s_key;

		regex_search(xpath, s_element, r_element);
		regex_search(xpath, s_key, r_key);
		
		result = this->Dash(s_element.str(),s_key.str());
	}
	return result;

}

// /
vector<string> XPath::Dash(string element, string key) 
{
	vector<string> result;
	for (auto x : Deserialized)
	{
		if (x.get_name()==element)
		{
			for (auto attribute : x.get_childs())
			{
				if (attribute.get_name()==key)
				{
					result.push_back(attribute.get_text());
				}
			}
		}
	}
	return result;
}

//[]
string XPath::Index(string element, string key, int index) {
	vector<string> result = Dash(element, key);
	return result[index];
}

//@
vector<string> XPath::At(string element, string key)
{
	vector<string> result;
	for (auto x : Deserialized)
	{
		if (x.get_name() == element)
		{
			if (key == "id")
			{
				result.push_back(x.get_id());
			}
			else
			{
				for (auto z : x.get_childs())
				{
					if (z.get_name() == key)
					{
						result.push_back(z.get_text());
					}
				}
				for (auto z : x.get_attributes())
				{
					if (z.first == key)
					{
						result.push_back(z.second);
					}
				}
			}
		}
	}
	return result;
}

////=
vector<string> XPath::Equal(string element, string key, string value)
{
	vector<string> all = At(element, key);
	vector<string> result;
	for (auto x:all)
	{
		if (x == value)
			result.push_back(x);
	}
	return result;
}