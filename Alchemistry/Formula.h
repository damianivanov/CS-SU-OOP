#pragma once
#include "Element.h"
#include <vector>
using namespace std;
class Formula
{
public:
	Formula();
	~Formula();
	void set_result(Element* result) { this->result = result; }
	Element* get_result() { return result; }
	inline bool operator==(const Formula& rhs) { return rhs.result->get_name() == this->result->get_name() && rhs.elements == this->elements; }

	vector<Element*> get_elements() { return this->elements; }
	void add_element(Element* element) { elements.push_back(element); }
	string to_string();
private:

	Element* result;
	vector<Element*> elements;
};

