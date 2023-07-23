#pragma once

#include <vector>
#include <cstdint>
#include <numeric>
#include <iostream>

using namespace std;

void counting_fractions_range()
{
	const uint64_t upper_bound = 12'001;

	double ub = static_cast<double>(1) / static_cast<double>(2);
	double lb = static_cast<double>(1) / static_cast<double>(3);
	uint64_t count_fraction_range = 0;

	for (int den = 2; den < upper_bound; ++den)
	{
		for (int num = 1; num < den; ++num)
		{
			int hcd = gcd(num, den);
			if (hcd != 1) continue;
			double comp = static_cast<double>(num) / static_cast<double>(den);
			if (lb < comp && comp < ub)
				++count_fraction_range;
		}
	}
	cout << "Count of Proper Fractions in range 1/3 through 1/2 = " << count_fraction_range << '\n';
}
