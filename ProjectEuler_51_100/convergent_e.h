#pragma once
#include <cstdint>
#include <vector>
#include <iostream>
#include <iomanip>
#include <numbers>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/cpp_dec_float.hpp>
#include <boost/multiprecision/cpp_bin_float.hpp>
#include "../repos/MonteCarlo/MonteCarlo/Primes.h"

using namespace std;
using namespace boost::multiprecision;

//using s64 = int64_t;

typedef number<cpp_dec_float<128> > cpp_dec_float_128;

void convergent_e()
{
	//2.71828182845904523536028747135266249775724709369995
	const cpp_dec_float_128  euler("2.71828182845904523536028747135266249775724709369995957496696762772407663035354759457138217852516642742746639193200305992");
	cpp_int num_coeff = 1;
	cpp_int num_term = 0;
	cpp_int den_coeff = 0;
	cpp_int den_term = 1;

	vector<cpp_int> numerator_convergents;

	cout << euler << '\n';

	auto extract_numerator = [euler](cpp_int& num_co, cpp_int& num_tm, cpp_int& den_co, cpp_int& den_tm)
	{
		cpp_dec_float_128   num_co_d = static_cast<cpp_dec_float_128 >(num_co);
		cpp_dec_float_128   num_tm_d = static_cast<cpp_dec_float_128 >(num_tm);
		cpp_dec_float_128   den_co_d = static_cast<cpp_dec_float_128 >(den_co);
		cpp_dec_float_128   den_tm_d = static_cast<cpp_dec_float_128 >(den_tm);
		cpp_int two = 2;
		cpp_int three = 3;
		cpp_dec_float_128 mpy = num_co_d * euler;
		cout << std::setprecision(std::numeric_limits<cpp_dec_float_128>::digits10) << num_co_d << " @ " << num_tm_d << " @ " << den_co_d << " @ " << den_tm_d << '\n';
		cpp_dec_float_128  integer_part_d = (num_co_d * euler + num_tm_d) / (den_co_d * euler + den_tm_d);
		cout  << integer_part_d << " -> " << '\n';
		integer_part_d = floor(integer_part_d);
		cout << " * " << integer_part_d << " * \n";
		
		cpp_int integer_part = static_cast<cpp_int>(integer_part_d);
		cout << integer_part << "  -> " << integer_part_d << '\n';
		
		num_co -= integer_part * den_co;
		num_tm -= integer_part * den_tm;
		cout << "extract " << num_co << " : ";
		return abs(num_tm);
	};

	auto flip = [](cpp_int& num_co, cpp_int& num_tm, cpp_int& den_co, cpp_int& den_tm)
	{
		cout << "swap " << num_tm << '\n';
		swap(num_co, den_co);
		swap(num_tm, den_tm);
	};

	for (int ix = 1; ix <= 100; ++ix)
	{
		cout << "Number = " << ix << '\n';
		cpp_int numerator_conv = extract_numerator(num_coeff, num_term, den_coeff, den_term);
		flip(num_coeff, num_term, den_coeff, den_term);
		numerator_convergents.emplace_back(numerator_conv);
	}

	cout << '\n';
	for (cpp_int x : numerator_convergents)
		cout << x << ", ";
	cout << '\n';

	cpp_int sum = digit_sum(numerator_convergents[99]);
	cout << "Sum of 100th Convergent = " << sum << "   (" << numerator_convergents[99] << ")\n";
}
