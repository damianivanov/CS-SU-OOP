#pragma once
#include "Element.h"
class Fire : virtual public Element
{
public:
	Fire() { 
		name = "Fire";
		this->combination = {"Earth","Water","Fire"};
		IsBase = true;
	}
	~Fire() {}
	Element* copy()
	{
		return new Fire(*this);
	}
private:

};