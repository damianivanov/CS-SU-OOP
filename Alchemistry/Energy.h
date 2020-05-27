#pragma once
#include "Element.h"
#include "Water.h"
#include "Air.h"

class Energy : public Water, public Air
{
public:
	Energy() 
	{
		this->name = "Energy"; 
		this->combination = { "Air","Earth","Water","Fire" };
		this->parents = {"Water","Air"};
		this->IsBase = false;
	}
	~Energy() {}
	Element* copy() { return new Energy(*this); }
private:
};