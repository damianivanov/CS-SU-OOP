// Business.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <map>
#include <limits>
#include "Organisation.h"
#include "Institution.h"
#include "Group.h"
std::vector<Institution*> clear_institutions(const vector<Institution*> all)
{
	vector<Institution*> cleared;
	for (auto x : all)
	{
		if (x->valid())
		{
			cleared.push_back(x);
		}
	}
	return cleared;
}
Institution* find_most_popular_institution(const vector<Institution*> institutions, const vector<Person*> people)
{
	map<Institution*, size_t> result;
	for (auto i:institutions)
	{
		for (auto p : people) {
			if (i->has_member(p))
			{
				result[i]++;
			}
		}
	}
	map<Institution*, size_t>::value_compare mycomp = result.value_comp();
	return result.cbegin()->first;
}

int main()
{
	vector<Institution*> v_institutions;
	vector<Person*> v_person;

	std::srand(time(NULL));
	int institutions = 100; //random starting point of id's of institutions (does not affect the algorithm)

	//Random Test data
	Payer* p1 = new Payer("Ivan");
	Payer* p2 = new Payer("Dragan");
	Payer* p3 = new Payer("Petkan");
	Payer* p4 = new Payer("Georgi");

	Person person1("Traiko");
	person1.set_payer(p1);

	Person person2("Znaiko");
	person2.set_payer(p2);

	Person person3("Basdfgh");
	person3.set_payer(p3);

	v_person.push_back(&person1);
	v_person.push_back(&person2);
	v_person.push_back(&person3);

	Group group1{"group1",institutions++,rand()%(UINT_MAX)};
	group1.assosiate_payer(p1);
	group1.add_person(&person1);
	group1.add_person(&person3);

	Group group2{"group2",institutions++,rand()%(UINT_MAX)};
	group2.assosiate_payer(p2);
	group2.add_person(&person2);

	Organisation org1{"Organ1",institutions++};
	org1.add_institution(&group1);

	Organisation org2{ "Organ2",institutions++ };
	org2.add_institution(&group1);
	org2.add_institution(&group1);
	org2.add_institution(&group2);


	Organisation org3{ "Organ3",institutions++ };
	// adds directly and ignores the validity of organg3(which is not valid because doesnt have other institutions)
	org1.add_institution(&org3,true);
	
	
	v_institutions.push_back(&group1);
	v_institutions.push_back(&group2);
	v_institutions.push_back(&org1);
	v_institutions.push_back(&org2);
	v_institutions.push_back(&org3);

	//organisation payer
	Institution* most = find_most_popular_institution(v_institutions, v_person);

	//from 5 to 4 (1 invalid)
	auto list = clear_institutions(v_institutions);
}

