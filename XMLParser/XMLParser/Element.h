#pragma once
#include <vector>
#include <map>
#include <string>
using namespace std;

class Element
{
	public:
		Element();
		~Element();
		string get_id();
		map<string,string> get_attributes();
	private:	   
		vector<Element> childs;
		Element* parent;
		string id;
		map<string, string> attributes;
};