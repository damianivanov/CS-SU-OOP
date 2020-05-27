#pragma once
#include "Element.h"

class Air: virtual public Element
{
	using element_type = Air;
public:
	
	Element* copy()
	{
		return new Air(*this);
	}
	Air() 
	{
		this->name = "Air";
		this->combination = { "Air","Earth","Water","Fire" };
		IsBase = true;
	}
	~Air(){}


private:

};
