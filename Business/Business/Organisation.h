#pragma once
#include <string>
#include <vector>
#include <map>
#include "Institution.h"
using namespace std;
class Organisation : public Institution
{
public:
	Organisation(string name, int id) :Institution{name,id} {};
	~Organisation() { institutions_list.clear(); };
	
	bool valid() { return institutions_list.size() != 0; }
	bool has_member(Person* person);

	string get_organization_address(){return organization_address;}
	void set_organization_address(string address) { organization_address = address; }
	
	void add_institution(Institution* institution,bool direct=false);
private:
	void assign_payer();
	vector<Institution*> institutions_list;
	string organization_address;
};