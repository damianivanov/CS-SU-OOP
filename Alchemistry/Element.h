#pragma once
#include <string>
#include <vector>
using namespace std;
class Element
{
public:
	Element() { IsBase = false; }
	~Element(){}
	Element(std::string name) { this->name = name; IsBase = false; }

	std::string get_name() { return name; }
	bool get_IsBase() { return IsBase; }
	Element& operator=(const Element& other);
	vector<string> get_combination() { return combination; }
	vector<string> get_parents() { return parents; }
	virtual Element* copy()=0;
protected:
	
	std::string name;
	bool IsBase;
	vector<string> parents;
	vector<string> combination;
};

