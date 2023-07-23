#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "../repos/Utilities/Utilities/comma_separated.h"

using namespace std;

void largest_exp()
{
	int index_of_largest_number = 0;
	double largest_number = 0;

	VVI read_in;
	string in("base_exp.txt");

	read_comma_separated_ints(in, read_in);

	int index = 1;
	for (auto vi : read_in)
	{
		double base = static_cast<double>(vi[0]);
		double exponent = static_cast<double>(vi[1]);

		double result = log(base) * exponent;

		if (result > largest_number)
		{
			largest_number = result;
			index_of_largest_number = index;
		}
		++index;
	}

	cout << "Index of Largest Number = " << index_of_largest_number << '\n';
}
