#include "Element.h"
Element& Element::operator=(const Element& element) {
	this->name = element.name;
	this->combination = element.combination;
	this->parents = element.parents;
	return *this;
}
