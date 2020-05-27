#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <regex>
#include "Formula.h"

#include "Air.h"
#include "Water.h"
#include "PhilosophersStone.h"
#include "Earth.h"
#include "FIre.h"
#include "Metal.h"
#include "Stone.h"
#include "Energy.h"
#include "Spirit.h"
#include "Gold.h"
using namespace std;
class Book
{
public:
	Book();
	~Book(); 
	
	Book(vector<string> content);

	void set_content(vector<string> content) { this->content = content; }
	void set_formulas(vector<Formula> Formulas) { this->Formulas = Formulas; }
	bool Have_PhilosopherStone_Formula();

	vector<Formula> get_Formulas() { return this->Formulas;}
	vector<string> get_content() { return this->content;}
	bool Valid_Formula(Formula formula);
	void Deserializer();
	Formula* at(size_t index);

private:
	std::vector<string> content;
	std::vector<Formula> Formulas;
	void Add_Formula(Formula formula);
	bool Can_React(Element* rel, Element* lel);
};

