#pragma once
#include "Element.h"
#include "Air.h"

class Spirit : public Air
{
public:
	Spirit() {
		this->name = "Spirit";
		this->combination = { "Air","Earth","Water","Fire" };
		this->parents = {"Air"};
		this->IsBase = false;
	}
	~Spirit(){}
	Element* copy() { return new Spirit(*this); }
private:
};