#pragma once

#include <boost/multiprecision/cpp_int.hpp>
#include <iostream>

void power_digit_sum()
{
	using namespace std;
	using namespace boost::multiprecision;
	using u32 = uint32_t;

	cpp_int dig_sum_max = 0;
	u32 a_max = 0;
	u32 b_max = 0;

	for (u32 a = 1; a < 100; ++a)
	{
		for (u32 b = 1; b < 100; ++b)
		{
			cpp_int prod = 1;
			for (u32 ix = 0; ix < b; ++ix)
			{
				prod *= a;
			}
			cpp_int dig_sum = digit_sum(prod);
			if (dig_sum > dig_sum_max)
			{
				dig_sum_max = dig_sum;
				a_max = a;
				b_max = b;
			}
		}
	}
	cout << "Maximum Digital Sum = " << dig_sum_max << '\n';
	cout << "Base = " << a_max << "  Exp = " << b_max << '\n';
}
