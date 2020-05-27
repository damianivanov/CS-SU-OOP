#include "Book.h"
Book::Book(){}
Book::Book(vector<string> content) { 
	this->content = content; 
	Deserializer(); 
}
Book::~Book(){}

void Book::Add_Formula(Formula formula) {
	Formulas.push_back(formula);
}
void Book::Deserializer() {
	for (string line:content)
	{
		Formula curr;

		regex r("(\\w+)");
		smatch s_m;
		while (regex_search(line, s_m, r))
		{
			string tmp_element = s_m.str();
			if (tmp_element=="Water")
			{
				curr.add_element(new Water);
			}
			else if (tmp_element == "Air") {
				curr.add_element(new Air);
			}
			else if (tmp_element == "Fire")
			{
				curr.add_element(new Fire);
			}
			else if (tmp_element == "Earth")
			{
				curr.add_element(new Earth);
			}
			else if (tmp_element == "Metal")
			{
				curr.add_element(new Metal);
			}
			else if (tmp_element == "Stone")
			{
				curr.add_element(new Stone);
			}
			else if (tmp_element == "Energy")
			{
				curr.add_element(new Energy);
			}
			else if (tmp_element == "Spirit")
			{
				curr.add_element(new Spirit);
			}
			else if (tmp_element == "Gold")
			{
				curr.add_element(new Gold);
			}
			else if (line ==" = Philosopher's Stone")
			{
				curr.add_element(new PhilosopherStone);
				break;
			}
			line = s_m.suffix();
		}
		vector<Element*> elements = curr.get_elements();
		Element* result = elements[elements.size()-1];
		elements.pop_back();
		curr.set_result(result);
		Formulas.push_back(curr);
	}
	
}
bool Book::Valid_Formula(Formula formula)
{
	vector<Element*> elements = formula.get_elements();
	if (elements.size()==3)
	{
		if (Can_React(elements[0], elements[1]))
		{
			return true;
		}
		return false;

	}
	else if (elements.size() == 1)
	{
		return true;
	}
	else
	{
		for (size_t i = 0; i < elements.size() - 1; i++)
		{
			if (!Can_React(elements[i], elements[i + 1]))
			{
				return false;
			}
		}
	}
	
	return true;
}
bool Book::Can_React(Element* rel, Element* lel)
{
	auto combinations = rel->get_combination();
	if (rel->get_IsBase()&&lel->get_IsBase())
	{
		for (auto x : combinations)
		{
			if (x == lel->get_name())
			{
				return true;
			}
		}
		return false;
	}	
	else if (rel->get_IsBase() && !lel->get_IsBase() || !rel->get_IsBase() && lel->get_IsBase())
	{
		//searching for base element in the list of comination of the non-base element
		if (!rel->get_IsBase())
		{
			for (auto x : combinations)
			{
				if (x==lel->get_name())
					return true;
			}
			return false;
		}
		else {
			for (auto x : lel->get_combination())
			{
				if (x == rel->get_name())
					return true;
			}
			return false;
		}
	}
	//Two Secondary Elements
	else
	{
		for (auto x : combinations)
		{
			vector<string> combination = lel->get_combination();
			auto result = find(combination.begin(), combination.end(), x);
			if (result == combination.end())
			{
				return false;
			}
		}
		return true;
	}
	return false;
}
bool Book::Have_PhilosopherStone_Formula() {
	bool flag = false;
	for (auto x : Formulas)
	{	
		string curr_name = x.get_result()->get_name().c_str();
		if (curr_name=="Philosopher's Stone")
		{
			flag = true;
			return flag;
		}
	}
	return flag;
}
Formula* Book::at(size_t index) {
	if (index<0||index>=Formulas.size())
	{
		return nullptr;
	}
	return &Formulas[index];
}