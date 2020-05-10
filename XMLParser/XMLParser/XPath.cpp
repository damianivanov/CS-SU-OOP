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
		regex r_index("[^\\@]\\w+(?=\\))");
		regex r_element("^\\w+");

		smatch s_index;
		smatch s_element;

		regex_search(xpath, s_index, r_index);
		regex_search(xpath, s_element, r_element);

		string key = s_index.str();
		string element = s_element.str();

		result = this->At(element, key);
	}
	else if (xpath.find('[')!=string::npos && xpath.find(']')!=string::npos) 
	{
		regex r_index("(?!\\[)\\d+(?=\\])");
		smatch s_index;
		regex_search(xpath, s_index, r_index);
		int index=stoi(s_index.str());
		vector<string> elements = xpath_to_vector(xpath);
		result[0] = this->Index(elements[0],elements[1],index);
	}
	else if (xpath.find('/')!=string::npos)
	{
		vector<string> elements = xpath_to_vector(xpath);
		result = this->Dash(elements[0],elements[1]);
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

vector<string> XPath::xpath_to_vector(string xpath)
{
	vector<string> elements;

	regex r_element("\\w+(?!\\/)\\w+");
	smatch s_element;
	while (regex_search(xpath, s_element, r_element))
	{
		elements.push_back(s_element.str());
		xpath = s_element.suffix();
	}
	return elements;
}