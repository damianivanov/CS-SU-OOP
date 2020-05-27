#pragma once
#include "Book.h"
#include <map>
class Alchemic
{
public:
	Alchemic();
	~Alchemic();
	void set_book(Book& other) 
	{ 
		this->book = &other; 
		set_philosopher_stone(book->Have_PhilosopherStone_Formula());
	}
	void set_philosopher_stone(bool philosopher_stone) { this->philosopher_stone = philosopher_stone; }
	void set_inventory(map<string, unsigned> inv) {  this->inventory=inv; }

	Book* get_book() { return this->book; }	
	bool get_philosopher_stone() { return this->philosopher_stone; }
	map<string, unsigned> get_inventory() { return this->inventory; }

	void Fill_Inventory();
	void Magic();
private:
	map<string, unsigned> inventory;
	Book* book;
	bool philosopher_stone;
	//bool Possible(Formula formula);
	void Remove_Invalid();
	bool Create(Element* element, Formula formula);
	bool Available(Element* element);
	Formula* Have_Formula(Element* element);
	bool Have_Resources(Formula* curr);
	bool Have_Division(Element* element);
	void Division(Element* element);
};



