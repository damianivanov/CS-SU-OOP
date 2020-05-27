#include "Alchemic.h"

Alchemic::Alchemic()
{
	philosopher_stone = false;
	book = new Book(); 
}
Alchemic::~Alchemic() {}

void Alchemic::Fill_Inventory() {
	cout << "Earth: ";
	int tmp;
	cin >> tmp;
	inventory["Earth"] = tmp;

	cout << "Fire: ";
	cin >> tmp;
	inventory["Fire"] = tmp;

	cout << "Water: ";
	cin >> tmp;
	inventory["Water"] = tmp;

	cout << "Air: ";
	cin >> tmp;
	inventory["Air"] = tmp;
}
void Alchemic::Remove_Invalid() {

	PhilosopherStone tmp;
	string tmp_name = tmp.get_name();
	vector<Formula> invalid;
	auto formulas = book->get_Formulas();
	for (auto x : formulas)
	{
		auto tmp_formulas = book->get_Formulas();
		if (!book->Valid_Formula(x) && (x.get_result()->get_name() != tmp_name))
		{
			invalid.push_back(x);
			tmp_formulas.erase(remove(tmp_formulas.begin(), tmp_formulas.end(), x), tmp_formulas.end());
		}
		book->set_formulas(tmp_formulas);
	}
}
void Alchemic::Magic()
{
	Remove_Invalid();
	PhilosopherStone tmp;
	string tmp_name = tmp.get_name();
	auto Formulas = book->get_Formulas();
	for (auto x:Formulas)
	{
		if (x.get_result()->get_name()==tmp_name)
		{
			//try to create it
			if (Create(x.get_result(),x))
			{
				cout << "Philosopher's Stone created from " << x.to_string() << endl;
			}
		}
	}
	;
}
bool Alchemic::Create(Element* element, Formula formula) 
{	

	bool flag = true;
	for (size_t i=0;i<formula.get_elements().size()-1;++i)
	{
		auto x = formula.get_elements()[i];
		if (Available(x))
		{
			inventory[x->get_name()]--;
			flag = true;			
		}
		else {
			flag = false;
			Formula* curr = Have_Formula(x);
			if (curr!=nullptr)
			{
				//There is formula for the result
				bool created = Create(x->copy(), *curr);
				if (!created)
				{
					//--- Pseudocode ---
					//check which element's needs more and check if one of his parents have division
				}
				else if (created)
				{
					string result_name = curr->get_result()->get_name();
					inventory.insert(std::pair<string, int>(result_name,0)); // => insert and -- to use the element
					cout << result_name << " created from " << curr->to_string() << endl;		
					flag = true;
				}
				
			}
		}
	}	
	if (!flag)
	{
		cout << "Couldn't make "<<element->get_name() << endl;
	}
	return flag;
}
bool Alchemic::Available(Element* element) {
	for (auto x : inventory)
	{
		if (x.first == element->get_name() && x.second>0)
		{
			return true;
		}
	}
	return false;
}
Formula* Alchemic::Have_Formula(Element* element)
{
	for (size_t i=0;i<book->get_Formulas().size();++i)
	{
		Formula* curr = book->at(i);
		if (curr->get_result()->get_name()==element->get_name())
		{
			if (Have_Resources(curr))
			{
				return curr;
			}
		}
	}
	return nullptr;
}
bool Alchemic::Have_Resources(Formula* formula) {
	for (size_t i = 0; i < formula->get_elements().size()-1; ++i) {

		Element* element = formula->get_elements()[i];
		if (inventory[element->get_name()]<1&& element->get_IsBase())
		{
			return false;
		}
	}
	return true;
}
bool Alchemic::Have_Division(Element* element)
{
	for (auto x : book->get_Formulas())
	{
		if (x.get_elements().size()==1)
		{
			if (x.get_elements()[0]->get_name()==element->get_name())
			{
				return true;
			}
		}
	}
	return false;
}
void Alchemic::Division(Element* element)
{
	string element_name = element->get_name();
	PhilosopherStone tmp;
	if (element->get_IsBase() || element_name==tmp.get_name())
	{
		inventory[element_name]++;
	}
	else
	{
		auto parents = element->get_parents();
		if (parents.size()==1)
		{
			string parent = parents[0];
			if (inventory[element_name]!=0)
				inventory[element_name]--;
			inventory[parent]+=2;
		}
		else
		{
			if (inventory[element_name] != 0)
				inventory[element_name]--;
			string Lparent = parents[0];
			string Rparent = parents[1];
			inventory[Lparent] ++;
			inventory[Rparent] ++;
		}
	}
}
