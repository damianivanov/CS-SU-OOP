#pragma once
#include "Element.h"
#include "Earth.h"
#include "Fire.h"

class Metal : public Fire, public Earth
{
	public:
		Metal() {
			this->name = "Metal";
			this->combination = { "Air","Earth","Water","Fire" };
			this->parents = { "Fire","Earth" };
			this->IsBase = false;
		}
		~Metal(){}
		Element* copy() { return new Metal(*this); }
	private:

};