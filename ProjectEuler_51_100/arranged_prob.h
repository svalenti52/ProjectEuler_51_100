#pragma once

#include <iostream>
#include <boost/multiprecision/cpp_dec_float.hpp>
#include "../repos/MonteCarlo/MonteCarlo/Primes.h"

using namespace std;

using u64 = uint64_t;

bool probability_eq_50(u64 bc1, u64 tc1, u64 bc2, u64 tc2)
{

	u64 gcd_ = gcd(tc1, bc1);
	tc1 /= gcd_;
	bc1 /= gcd_;

	gcd_ = gcd(tc1, bc2);
	tc1 /= gcd_;
	bc2 /= gcd_;

	gcd_ = gcd(tc2, bc1);
	tc2 /= gcd_;
	bc1 /= gcd_;

	gcd_ = gcd(tc2, bc2);
	tc2 /= gcd_;
	bc2 /= gcd_;

	if (bc1 * bc2 == 1 && tc1 * tc2 == 2)
		return true;
	return false;
}

void arranged_prob2()
{
	using namespace boost::multiprecision;
	//const u64 basis = 1'029'700'000'000;
	const u64 basis = 1070379110497;

	u64 tot_chips = basis;
	u64 blue_chips = 756872327470;
	//u64 blue_chips = 30;

	u64 tot_less = tot_chips - 1;
	u64 blue_less = blue_chips - 1;

	bool done = false;

	while (!done)
	{
		bool past_50 = false;

		while (!past_50)
		{
			// adjusting tot_chips, blue_chips directly is wrong
			done = probability_eq_50(blue_chips, tot_chips, blue_less, tot_less);
			if (done) break;

			cpp_dec_float_50 rat = (static_cast<cpp_dec_float_50>(blue_chips) / static_cast<cpp_dec_float_50>(tot_chips))
				* (static_cast<cpp_dec_float_50>(blue_less) / static_cast<cpp_dec_float_50>(tot_less));

			if (rat >= 0.5) past_50 = true;
			else
			{
				++blue_chips;
				++blue_less;
			}
		}
		if (tot_chips % 1'000'000 == 0)
			cout << tot_chips << ' ';
		if (!done)
		{
			++tot_chips;
			++tot_less;
		}
	}

	cout << '(' << blue_chips << '/' << tot_chips << ") * (" << blue_less << '/' << tot_less << ")\n";
	cout << "Number of blue chips = " << blue_chips << '\n';

	//cout << std::setprecision(std::numeric_limits<cpp_dec_float_100>::max_digits10) << rat << '\n';
}

//bool select_range(VI vi)
//{
//	const u64 lb = 1e12;
//	const u64 ub = 2e12;
//
//
//}

void arranged_prob1()
{
	const u64 ub = 1'000'000;
	Primes_List pl(ub);
	Primes primes(pl, ub);
	vector<u64> prime_v;
	for (int ix = 0; ix <= primes.get_last_index(); ++ix)
		prime_v.emplace_back(primes.get_ith_prime(ix));

	u64 prime_mult = accumulate(prime_v.begin(), prime_v.begin() + 11, 1LL, multiplies());

	//for (auto i : prime_v)
	//	cout << i << ' ';
	//cout << "\n\n";

	cout << "size = " << prime_v.size() << '\n';

	//cout << "primes! = " << prime_mult << "    " << primes.get_last_index() << "\n\n";

	while (prime_mult < 1e12)
		prime_mult *= 2;
	//prime_mult *= 2;

	cout << "primes! * 2^n = " << prime_mult << "    " << primes.get_last_index() << "\n\n";

	u64 tot_less = prime_mult - 1;

	for (auto i : prime_v)
	{
		if (tot_less % i == 0)
			cout << i << "  divides one less!\n";
	}

	//vector<u64> tot_chips_pot;

	//for (auto i : prime_v)
	//{
	//	u64 sum = accumulate(begin(prime_v), end(prime_v), 1LL);
	//	while (sum < 1e12)
	//	{
	//		sum *= i;
	//	}
	//	tot_chips_pot.emplace_back(sum);
	//}

	//for (auto i : tot_chips_pot)
	//	cout << i << '\n';
	//cout << '\n';
}

void arranged_prob()
{
	u64 tot_chips = 4;
	u64 blue_chips = 3;

	while (tot_chips <= 1'000'000'000'000)
	{
		u64 t_tot_chips = 3 * tot_chips + 4 * blue_chips - 3;
		blue_chips = 2 * tot_chips + 3 * blue_chips - 2;

		tot_chips = t_tot_chips;
	}

	cout << "Blue Chips = " << blue_chips << '\n';

	cout << "Total Chips = " << tot_chips << '\n';
}
