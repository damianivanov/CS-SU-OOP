#include "Payer.h"

int Payer::digit_sum(int num)
{
	int result = 0;
	while (num != 0)
	{
		result += num % 10;
		num /= 10;
	}
	return result;
}
int Payer::generate_id(unsigned int group_id, int institution_id) {
	vector<int> digits; //inscurance_id  
	size_t sum_of_group_id = digit_sum(group_id);
	int group_id_copy = group_id;
	std::srand(time(NULL));
	int i = 0;
	//random digit to every position of group_id
	for (; group_id_copy != 0; i++) {
		group_id_copy /= 10;
		digits.push_back(rand() % 10);
	}
	int difference = (digit_sum(vector_to_int(digits)) + digit_sum(institution_id)) - sum_of_group_id;

	if (difference != 0)
	{
		//make the difference 0 by adding to random digit, random number;
		if (difference < 0)
		{
			while (difference < 0) {
				//adding to the digits
				for (int& x : digits)
				{
					int curr = rand() % (10 - x);// x+curr should not be over 9(single digit)
					x += curr;
					difference += curr;
					if (difference >= 0)
						break;
				}
			}
		}
		//substracting
		while (difference > 0)
			{
				for (int& x : digits)
				{
					int curr = rand() % (x + 1);// x+curr should not be over 9(single digit)
					x -= curr;
					difference -= curr;
					if (difference <= 0)
					{
						digits.push_back(difference * (-1)); //adds difference as a last digit
						break;
					}
				}
			}	
	}
	return vector_to_int(digits);

}
bool Payer::payer_member_rule(int institution_id, unsigned int group_id, int insurance_id) {
	return digit_sum(group_id) == digit_sum(insurance_id) + digit_sum(institution_id);
}
int Payer::vector_to_int(const vector<int>& digits)
{
	int result = 0;
	int mult = 1;
	for (int i = digits.size() - 1; i >= 0; --i)
	{
		result += digits[i] * mult;
		mult *= 10;
	}
	return result;
}