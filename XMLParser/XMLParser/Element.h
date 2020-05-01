#pragma once
#include <string>
#include <vector>
#include <map>
#include <sstream>  
#include <regex>

using namespace std;

class Element
{
	public:
		Element();
		~Element();
		string get_name();
		string get_id();
		string get_text();
		map<string,string> get_attributes();
		vector<Element> get_childs();
		Element* get_parent();
		
		void Extract_attributes(string line);
		void Extract_name(string line);
		void Extract_text(string line);

		void set_name(string name);
		void set_id(string id);
		void set_attributes(map<string,string> attributes);
		void set_childs(vector<Element> childs);
		void set_parent(Element& parent);

		void Add_attribute(string key, string value);
	private:	   
		string name;
		vector<Element> childs;
		Element* parent;
		string id= "none";
		map<string, string> attributes;
		string text;
		map<string,string> Attribute_parse(string line);
};