#pragma once
#include "Element.h"
#include "Water.h"
#include "Fire.h"

class Stone : public Water, public Fire
{
public:
	Stone(){ this->name = "Stone"; 
	this->combination = {"Air", "Earth", "Water", "Fire"};
	this->parents = { "Water","Fire" };
	this->IsBase = false;
	}
	~Stone(){}
	Element* copy() { return new Stone(*this); }
private:
};