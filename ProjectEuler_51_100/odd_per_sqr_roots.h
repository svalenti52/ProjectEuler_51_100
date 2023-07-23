#pragma once

#include <cmath>
#include <vector>
#include <algorithm>
#include <tuple>

using num_coeff_term_div = tuple<int, int, int, int>;

void odd_per_sqr_roots()
{
	vector<int> odd_periodic_elts;

	for (int number = 2; number <= 10'000; ++number)
	{
		int irrational_coefficient = 1;
		int irrational_term = 0;
		int integral_side = 1;
		bool irrational_numerator = true;

		vector<int> sequence_of_integers;

		vector<num_coeff_term_div> irrational_set; // number, irrational_coefficient, irrational_term, integral_side

		auto is_odd = [](int i)
		{
			return (i & 1) == 1;
		};


		auto conjugate_reduction = [&irrational_set](int number, int& coefficient, int& term, int& integral, bool& irrational_numerator)
		{
			if (!irrational_numerator)
			{
				int tmp_coeff = coefficient;
				int tmp_term = term;
				irrational_numerator = !irrational_numerator;
				coefficient *= integral;
				term = integral * (-term);
				integral = tmp_coeff * tmp_coeff * number + (-tmp_term * tmp_term);
				int div1 = gcd(coefficient, integral);
				int div2 = gcd(term, integral);
				int div3 = gcd(div1, div2);
				coefficient /= div3;
				term /= div3;
				integral /= div3;
			}
		};

		auto flip = [](bool& irrational_numerator)
		{
			irrational_numerator = !irrational_numerator;
		};

		auto extract_integer = [&sequence_of_integers](int number, int& coefficient, int& term, int& integral, bool& irrational_numerator)
		{
			if (irrational_numerator)
			{
				double x = static_cast<double>(number);
				double sr = sqrt(x);
				sr *= coefficient;
				sr += term;
				sr /= integral;
				int extracted_integer = static_cast<int>(floor(sr));
				term -= extracted_integer * integral;
				sequence_of_integers.emplace_back(extracted_integer);
				return extracted_integer;
			}
			return 0; // irrational number should be in numerator
		};

		double sr = sqrt(static_cast<double>(number));
		if ((sr - floor(sr) < 1e-10)) continue; // skip if not an irrational square root

		int integer_part = extract_integer(number, irrational_coefficient, irrational_term, integral_side, irrational_numerator);
		flip(irrational_numerator);
		conjugate_reduction(number, irrational_coefficient, irrational_term, integral_side, irrational_numerator);

		irrational_set.clear(); // remove integer part of irrational number

		int period_count = 0;
		while (true)
		{
			int integer_part = extract_integer(number, irrational_coefficient, irrational_term, integral_side, irrational_numerator);
			flip(irrational_numerator);
			conjugate_reduction(number, irrational_coefficient, irrational_term, integral_side, irrational_numerator);

			auto detect = find_if(irrational_set.begin(), irrational_set.end(), [=](num_coeff_term_div t)
				{auto [nr, co, tr, dn] = t;
			return (number == nr && irrational_coefficient == co && irrational_term == tr && integral_side == dn); });

			if (detect == irrational_set.end())
			{
				irrational_set.emplace_back(make_tuple(number, irrational_coefficient, irrational_term, integral_side));
				++period_count;
			}
			else
				break;

			//cout << "\nnumber " << number << "  coeff " << irrational_coefficient << "  term " << irrational_term << "  opp side int " << integral_side
			//	<< "  irr num " << irrational_numerator;
		}
		cout << "\nNumber " << number << "  Period Count = " << period_count;
		if (is_odd(period_count))
			odd_periodic_elts.emplace_back(number);

		irrational_set.clear();

		//cout << '\n';
		//for (int i : sequence_of_integers)
		//	cout << i << ", ";
		//cout << '\n';

	}

	cout << "\n\nCount for odd periods of continued fractions of sqrt <= 10,000 = " << odd_periodic_elts.size() << '\n';
}

#include <boost/multiprecision/cpp_dec_float.hpp>

typedef number<cpp_dec_float<250> > cpp_dec_float_200;

void odd_per_sqr_roots_float()
{
	vector<cpp_dec_float_200> odd_periodic_elts;

	auto is_odd = [](int i)
	{
		return i & 1 == 1;
	};

	auto inv_take_frac_part = [](cpp_dec_float_200 x)
		{
			cpp_dec_float_200 ans = 1 / x;
			return ans - floor(ans);
		};

	for (int ix = 2; ix <= 10'000; ++ix)
	//for (int ix = 9997; ix <= 9997; ++ix)
	{

		vector<cpp_dec_float_200> periodic_detect;
		int period = 0;

		cpp_dec_float_200 x = static_cast<cpp_dec_float_200>(ix);

		cpp_dec_float_200 sr = sqrt(x);
		if ((sr - floor(sr) < 1e-10)) continue; // skip if not an irrational square root

		cpp_dec_float_200 inv_fractional = inv_take_frac_part(sr);

		bool find_period = false;
		while (!find_period)
		{
			inv_fractional = inv_take_frac_part(inv_fractional);
			if (!periodic_detect.empty())
				++period;
			find_period = find_if(periodic_detect.begin(), periodic_detect.end(), [inv_fractional](cpp_dec_float_200 d) {return abs(inv_fractional - d) < 1e-6; }) != periodic_detect.end();
			periodic_detect.emplace_back(inv_fractional); // insert after setting find_period!
		}

		cout << "Period = " << period << "   for square root of " << ix << '\n';

		if (is_odd(period))
			odd_periodic_elts.emplace_back(ix);

		//for (cpp_dec_float_200 d : periodic_detect)
		//	cout << d << ", ";
		//cout << '\n';

		periodic_detect.clear();
	}
	cout << "\n\nCount for odd periods of continued fractions of sqrt <= 10,000 = " << odd_periodic_elts.size() << '\n';
}
