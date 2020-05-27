#pragma once
#include "Element.h"

class Earth : virtual public Element
{
public:
	Earth() { 
		this->name = "Earth"; 
		this->combination = { "Air","Water","Fire" };
		IsBase = true;
	}
	~Earth(){}
	Element* copy() { return new Earth(*this); }
private:
};
