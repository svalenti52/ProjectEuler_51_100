#pragma once

#include "boost/multiprecision/cpp_int.hpp"
#include "../repos/MonteCarlo/MonteCarlo/Primes.h"

void lychrel_numbers()
{
	using namespace std;
	using namespace boost::multiprecision;

	int count_lychrel = 0;
	for (cpp_int number = 1; number < 10'000; ++number)
	{
		cpp_int rev_number = numeric_digits_reversed(number);
		cpp_int sum_number_w_reverse = number + rev_number;
		int ix = 0;
		for (ix; ix < 50; ++ix)
		{
			if (is_numeric_calc_palindrome(sum_number_w_reverse))
				break;
			rev_number = numeric_digits_reversed(sum_number_w_reverse);
			sum_number_w_reverse = sum_number_w_reverse + rev_number;
		}
		if (ix == 50)
		{
			++count_lychrel;
			cout << sum_number_w_reverse << '\n';
		}
	}
	cout << "Lychrel Number Count = " << count_lychrel << '\n';
}
