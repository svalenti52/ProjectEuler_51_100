#pragma once

#include <iostream>
#include <boost/multiprecision/cpp_dec_float.hpp>
#include <vector>
#include <algorithm>

using namespace std;
using namespace boost::multiprecision;

void sqrt_digital_expansion()
{
	vector<int> digital_sums;

	for (int ix = 1; ix <= 100; ++ix)
	{
		cpp_dec_float_100 sqr_number = static_cast<cpp_dec_float_100>(ix);
		cpp_dec_float_100 digit_conveyer_belt = sqrt(sqr_number);
		if ((digit_conveyer_belt - floor(digit_conveyer_belt)) < 1e-10) continue;

		int digital_sum = 0;

		// unsure of whether to include the integer part of original number...
		// not clear from the description except they do give the digital sum for sqrt 2

		cout << '\n' << ix << ". ";
		for (int jx = 0; jx < 100; ++jx)
		{
			cpp_dec_float_100 promoted_integer = floor(digit_conveyer_belt);
			digital_sum += static_cast<int>(promoted_integer);
			digit_conveyer_belt -= promoted_integer;
			digit_conveyer_belt *= 10;
		}
		cout << digital_sum;

		digital_sums.emplace_back(digital_sum);
	}

	int tot_digital_sum = accumulate(begin(digital_sums), end(digital_sums), 0);

	cout << "\n\nTotal Digital Sum = " << tot_digital_sum << '\n';
}
