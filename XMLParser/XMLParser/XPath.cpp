#include "XPath.h"

XPath::XPath() {}
XPath* XPath::operator=(const XPath& other)
{
	this->Deserialized = other.Deserialized;
	return this;
}
XPath::XPath(vector<Element> deserialized) {
	this->Deserialized = deserialized;
}

vector<string> XPath::Parser(string id, string xpath)
{
	vector<string> result;
	// = @ [] /
	if (xpath.find("=") != string::npos)
	{
		//Tests:
		// xpath 1 person(address="USA")/name - OK returned Jhon Smith
		// xpath 1 person(address="USA")/id -OK return 0_1(Id of Jhon Smith)

		regex r_value("[^\"]\\w+(?=\")");
		smatch s_value;
		regex_search(xpath, s_value, r_value);

		regex r_key("[^\\(]\\w+(?=\\=)");
		smatch s_key;
		regex_search(xpath, s_key, r_key);

		vector<string> elements = xpath_to_vector(xpath);
		result = this->Equal(elements, s_key.str(), s_value.str());
	}
	else if (xpath.find('@') != string::npos)
	{
		regex r_index("[^\\@]\\w+(?=\\))");
		smatch s_index;
		regex_search(xpath, s_index, r_index);

		string key = s_index.str();
		vector<string> elements = xpath_to_vector(xpath);
		result = this->At(key,elements);
	}
	else if (xpath.find('[') != string::npos && xpath.find(']') != string::npos)
	{
		//Tested with:
		//xpath 1 people/person[0]/address - OK
		//xpath 1 people/person[1]/address - OK
		//xpath 1 person/address[0] - OK
		//xpath 1 person[0]/address - OK
		//xpath 1 city - NOT OK - Acctually invalid xpath
		//xpath 1 /city - NOT OK - NOW OK
		//xpath 1address/city - NOT OK - Invalid

		regex r_index("(?!\\[)\\d+(?=\\])");
		smatch s_index;
		regex_search(xpath, s_index, r_index);
		int index = stoi(s_index.str());

		vector<string> elements = xpath_to_vector(xpath);
		result.push_back(this->Index(elements, index));
	}
	else if (xpath.find('/') != string::npos)
	{
		vector<string> elements = xpath_to_vector(xpath);
		result = this->Dash(elements);
	}
	return result;

}

// /
vector<string> XPath::Dash(vector<string> elements)
{
	vector<string> result;
	vector<Element> tmp;
	for (auto x : Deserialized)
	{
		if (x.get_name()==elements[elements.size()-1])
		{
			tmp.push_back(x);
		}
	}
	for (int j=0;j<tmp.size();++j)
	{
		Element curr=tmp[j];
		for (int p = elements.size() - 2; p >= 0; --p)
		{
			curr = *curr.get_parent();
			if (curr.get_name()!=elements[p])
			{
				tmp.erase(tmp.begin() + j);
			}
		}			
	}	
	for (auto x : tmp)
	{
		result.push_back(x.get_text());
	}
	return result;
}

//[]
string XPath::Index(vector<string> elements, int index) {
	vector<string> result = Dash(elements);
	if (result.size()>index)
	{
		return result[index];
	}
	return "";
}

//@
vector<string> XPath::At(string key, vector<string> elements)
{
	vector<string> result;
	for (auto element : Deserialized) 
	{
		if (element.get_name() == elements[elements.size() - 2])
		{
			if (key == "id")
			{
				result.push_back(element.get_id());
			}
			else
			{
				for (auto attribute : element.get_attributes())
				{
					if (attribute.first==key)
					{
						result.push_back(attribute.second);
					}
				}
			}

		}	
	}
	return result;
}

////=
vector<string> XPath::Equal(vector<string> elements, string key, string value)
{

	vector<string> result;
	for (auto x : Deserialized)
	{
		if (x.get_name() == key && x.get_text() == value)
		{
			Element curr_element_parent = *x.get_parent();
			if (elements[elements.size()-1]=="id")
			{
				result.push_back(curr_element_parent.get_id());
			}
			else 
			{
				for (auto childs : curr_element_parent.get_childs())
				{
					if (childs.get_name() == elements[elements.size() - 1])
					{
						result.push_back(childs.get_text());
					}
				}
			}
		}
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