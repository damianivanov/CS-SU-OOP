#pragma once
#include "Institution.h"
class Group : public Institution
{
public:
	Group(string name, int id) : group_id{ 0 }, Institution{ name,id }, group_payer{ nullptr }, people{0}{};
	Group(string name, int id, unsigned int group_id) : group_id{ group_id }, Institution{ name,id }, group_payer{ nullptr }, people{ 0 }{};
	~Group() {};
	bool valid() { return this->group_payer != nullptr; }
	void add_person(Person* person) { person->set_insurance_id(group_payer->generate_id(group_id, institution_id)); people++; }
	void assosiate_payer(Payer* payer) { this->group_payer = payer; this->payer = payer; }
	Payer* get_group_payer() { return group_payer; }

	bool has_member(Person* person) { return payer->payer_member_rule(institution_id,group_id, person->get_insurance_id()); }
private:
	int people;
	Payer* group_payer;
	unsigned int group_id;
};