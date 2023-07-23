#pragma once

#include <numeric>
#include <iostream>

using namespace std;

void ordered_fractions()
{
	const double three_sevenths = static_cast<double>(3) / static_cast<double>(7);
	double closest_lt = static_cast<double>(2) / static_cast<double>(5);
	int closest_numerator = 2;
	int closest_denominator = 5;

	int base_numerator = 4;

	for (int base_den = 11; base_den <= 1'000'000; ++base_den)
	{
		double comp = static_cast<double>(base_numerator) / static_cast<double>(base_den);
		while (comp < three_sevenths)
		{
			++base_numerator;
			comp = static_cast<double>(base_numerator) / static_cast<double>(base_den);
			//cout << "Comp => " << comp << " < " << three_sevenths << '\n';
		}
		--base_numerator;

		int hcd = gcd(base_numerator, base_den);
		int reduced_numerator = base_numerator / hcd;
		int reduced_den = base_den / hcd;

		comp = static_cast<double>(reduced_numerator) / static_cast<double>(reduced_den);
		if (comp > closest_lt)
		{
			closest_lt = comp;
			closest_numerator = reduced_numerator;
			closest_denominator = reduced_den;
		}
	}

	cout << "Closest Numerator = " << closest_numerator << "   Closest Denominator = " << closest_denominator << '\n';
}
