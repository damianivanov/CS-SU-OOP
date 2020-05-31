#pragma once
#include <string>
#include <time.h>
#include <stdlib.h>
#include "Payer.h"
using namespace std;
class Person
{
public:
	Person() : payer{ nullptr }, insurance_id{ -1 } {}
	Person(const string& name) : person_name{name}, payer{ nullptr }, insurance_id{ -1 } {}
	~Person() { delete payer; };
	void set_payer(Payer* new_payer) { payer = new_payer; insurance_id = rand(); }
	Payer* get_payer() { return payer; }
	void set_insurance_id(int id) { insurance_id = id; }
	int get_insurance_id() { return insurance_id; }
private:
	int insurance_id;
	string person_name;
	Payer* payer;

	int random() {
std::srand(time(NULL));	
		return rand();
	}
};

