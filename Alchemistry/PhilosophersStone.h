	#pragma once
#include "Element.h"
class PhilosopherStone: virtual public Element
{
public:
	Element* copy()
	{
		return new PhilosopherStone(*this);
	}
	PhilosopherStone() { this->name = "Philosopher's Stone"; }
	~PhilosopherStone() {}

private:

};
