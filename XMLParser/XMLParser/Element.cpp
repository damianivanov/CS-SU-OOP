#include "Element.h"

Element::~Element(){}
Element::Element() { parent = NULL; }

string Element::get_id()
{
	return id;
}
map<string, string> Element::get_attributes() {
	return this->attributes;
}