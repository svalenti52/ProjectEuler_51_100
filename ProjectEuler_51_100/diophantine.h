#pragma once

#include <iostream>
#include <vector>
#include <boost/multiprecision/cpp_int.hpp>
#include "../repos/MonteCarlo/MonteCarlo/Continued_Fractions.h"

using u64 = uint64_t;

void diophantine1()
{
	using namespace boost::multiprecision;
	cpp_int zero;
	vector<cpp_int> min_x { zero, zero }; // 0, 1 taken care of

	cpp_int x_max = 0;
	cpp_int d_at_max = 0;

	for (cpp_int d = 2; d <= 1'000; ++d)
	{
		double dbl_sqrt = sqrt(static_cast<double>(d));
		cpp_int sqrt_i = static_cast<cpp_int>(floor(dbl_sqrt));
		if (sqrt_i * sqrt_i == d)
		{
			min_x.emplace_back(0);
			continue;
		}

		cpp_int coef = coefficient_init;
		cpp_int term = term_init;
		cpp_int opposite = integral_init;

		//cpp_int integer_part = integer_part_sequence(d, coef, term, opposite);
		cpp_int convergent_numerator = root_sequence_convergents(d, coef, term, opposite);
		if (convergent_numerator > x_max)
		{
			x_max = convergent_numerator;
			d_at_max = d;
		}
	}

	cout << "Max d = " << d_at_max << "    Max x = " << x_max << '\n';
}
