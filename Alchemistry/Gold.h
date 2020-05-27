#pragma once
#include "Element.h"
#include "Metal.h"

class Gold : public Metal
{
public:
	Gold(){ this->name = "Gold"; 
	this->combination = { "Air","Earth","Water","Fire" };
	this->parents = { "Metal"};
	this->IsBase = false;
	}
	~Gold(){}
	Element* copy() { return new Gold(*this); }
private:
};