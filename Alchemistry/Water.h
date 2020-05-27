#pragma once
#include "Element.h"

class Water: virtual public Element
{
	public:
		Element* copy()
		{
			return new Water(*this);
		}
		Water() { 
			this->name = "Water"; 
			this->combination = { "Air","Fire" };
			IsBase = true;
		}
		~Water() {}
	private:
};

