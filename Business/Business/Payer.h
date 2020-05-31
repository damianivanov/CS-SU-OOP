#pragma once
#include <string>
#include <vector>
#include <stdlib.h>
#include <time.h>
using namespace std;
class Payer
{
public:
	Payer() {};
	Payer(string name) :payer_name{ name } {};
	~Payer() {};
	bool payer_member_rule(int institution_id,unsigned int group_id, int insurance_id);
	int generate_id(unsigned int group_id, int institution_id);
private:
	string payer_name;
	int digit_sum(int num);
	int vector_to_int(const vector<int>& digits);
};

