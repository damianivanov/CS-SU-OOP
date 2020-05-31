#pragma once
#include <string>
#include <iostream>
#include "Person.h"
#include "Payer.h"
using namespace std;
class Institution
{
public:
	Institution() :payer{ nullptr }, institution_id{-1}{};
	Institution(string name, int id) :institution_id{ id }, payer{ nullptr }, institution_name{name}{};
	virtual ~Institution() {};

	virtual bool has_member(Person* person)=0;
	Payer* get_payer() { return this->payer; };
	string get_name() { return this->institution_name; }
	virtual bool valid()=0;
	int get_id() { return institution_id; }
protected:
	Payer* payer;
	int institution_id;
	string institution_name;
};