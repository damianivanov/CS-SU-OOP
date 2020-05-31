#include "Organisation.h"
void Organisation::add_institution(Institution* institution,bool direct) {
	bool exists = false;
	if (!valid())
	{
		//currently 0 added organisations
		institutions_list.push_back(institution);
		cout << "Successfuly added First institution: " << institution->get_name() << " to " << this->get_name()<<endl;
		assign_payer();
		return;

	}
	for (auto i : institutions_list)
	{
		if (institution==i)
		{
			cout << "Institution: " << institution->get_name() << " already added to " << this->get_name() << " organisation!" << endl;
			exists = true;
			break;
		}
	}

	if ((payer != institution->get_payer()||!institution->valid())&&!direct)
	{
		cout << "Invalid Institution - "<<institution->get_name() << endl;
	}
	else if (!exists)
	{
		institutions_list.push_back(institution);
		cout << "Successfuly added institution: " << institution->get_name() << " to " << this->get_name()<< endl;
	}
	assign_payer();
}
void Organisation::assign_payer() {
	map<Payer*, size_t> payers;
	for (auto x : institutions_list) {
		Payer* curr = x->get_payer();
		payers[curr]++;
	}
	map<Payer*, size_t>::value_compare mycomp = payers.value_comp();
	payer = payers.rbegin()->first;
}
bool Organisation::has_member(Person* payer)
{
	for (auto i : institutions_list)
	{
		if (i->has_member(payer))
		{
			return true;
		}
	}
	return false;
}