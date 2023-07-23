#pragma once

#include <vector>
#include <boost/multiprecision/cpp_int.hpp>

void square_root_convergents()
{
	using namespace boost::multiprecision;
	const cpp_int numerator_1 = 3;
	const cpp_int denominator_1 = 2;

	cpp_int numerator_1_adj = 3;
	cpp_int denominator_1_adj = 2;

	cpp_int numerator = 0;
	cpp_int denominator = 1;

	vector<cpp_int> numerators;
	vector<cpp_int> denominators;

	for (int ix = 0; ix < 1'000; ++ix)
	{
		if (ix == 0)
		{
			numerators.emplace_back(numerator_1);
			denominators.emplace_back(denominator_1);
		}

		else
		{
			numerator = 2;
			denominator = 5;
			for (int jx = 1; jx < ix; ++jx)
			{
				numerator = 2 * denominator + numerator;
				swap(numerator, denominator);
			}
			numerators.emplace_back(numerator + denominator);
			denominators.emplace_back(denominator);
		}
	}

	cpp_int count_numerator_more_digits = 0;
	for (int ix = 0; ix < numerators.size(); ++ix)
	{
		if (digit_count(numerators[ix]) > digit_count(denominators[ix]))
			++count_numerator_more_digits;
	}

	cout << "\nNumerators:\n";
	for (cpp_int n : numerators)
		cout << n << ", ";
	cout << '\n';

	cout << "\nDenominators:\n";
	for (cpp_int d : denominators)
		cout << d << ", ";
	cout << '\n';

	cout << "\nNumber where Numerators Have More Digits than Denominator in Expansion = " << count_numerator_more_digits << '\n';
}
