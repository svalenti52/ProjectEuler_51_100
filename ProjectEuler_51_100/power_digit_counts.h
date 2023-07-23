#pragma once

#include "boost/multiprecision/cpp_int.hpp"
#include "../repos/MonteCarlo/MonteCarlo/Primes.h"

using namespace std;
using namespace boost::multiprecision;
using u64 = uint64_t;

void power_digit_counts()
{
	int count = 0;
	for (cpp_int ix = 1; ix < 10; ++ix)
	{
		if (digit_count(ix) == 1)
			++count;
	
		for (int ub = 2; ub < 26; ++ub)
		{
			cpp_int power = 1;
			for (int jx = 0; jx < ub; ++jx)
			{
				power = power * ix;
			}
			if (digit_count(power) == ub)
				++count;
		}
	}
	cout << "Number of nth-power, n-digit numbers = " << count << '\n';
}
