#pragma once

#include <vector>
#include <set>
#include <tuple>
#include <string>
#include <iostream>
#include <boost/multiprecision/cpp_int.hpp>
#include "../repos/MonteCarlo/MonteCarlo/Chronology.h"
#include "../repos/MonteCarlo/MonteCarlo/Primes.h"

using u64 = uint64_t;
using namespace std;

bool concat_is_prime(u64 p1, u64 p2, Primes_List& pl)
{
	string str_p1 = to_string(p1);
	string str_p2 = to_string(p2);
	u64 one = stoull(str_p1 + str_p2, nullptr);
	u64 two = stoull(str_p2 + str_p1, nullptr);
	return pl.is_prime(one) && pl.is_prime(two);
}

void prime_pair_sets()
{
	StopWatch stopwatch;
	Primes_List pl(100'000'000);
	Primes primes(pl, 100'000'000);
	stopwatch.stop();

	vector<u64> prime_set;
	bool found = false;
	bool concat_prime = false;

	int last_ix = 0;

	//====================================
	for (u64 ix = 122; ix <= 1228 && !found; ++ix) // TEST CASE 4
	{
		if (primes.get_ith_prime(ix) < 673) continue;
		//=====================================
		for (u64 jx = 121; jx < ix && !found; ++jx) // TEST CASE 4
		{
			concat_prime = concat_is_prime(primes.get_ith_prime(ix), primes.get_ith_prime(jx), pl);
			if (!concat_prime) continue;
			//======================================
			for (u64 kx = 28; kx < jx && !found; ++kx) // TEST CASE 4
			{
				concat_prime = concat_is_prime(primes.get_ith_prime(jx), primes.get_ith_prime(kx), pl);
				if (!concat_prime) continue;
				concat_prime = concat_is_prime(primes.get_ith_prime(ix), primes.get_ith_prime(kx), pl);
				if (!concat_prime) continue;
				//====================================
				for (u64 lx = 2; lx < kx && !found; ++lx) // TEST CASE 4
				{
					if (lx == 2) continue;
					concat_prime = concat_is_prime(primes.get_ith_prime(kx), primes.get_ith_prime(lx), pl);
					if (!concat_prime) continue;
					concat_prime = concat_is_prime(primes.get_ith_prime(jx), primes.get_ith_prime(lx), pl);
					if (!concat_prime) continue;
					concat_prime = concat_is_prime(primes.get_ith_prime(ix), primes.get_ith_prime(lx), pl);
					if (!concat_prime) continue;
					//====================================
					for (u64 mx = 1; mx < lx && !found; ++mx) // TEST CASE 4
					{
						if (mx == 2) continue;
						concat_prime = concat_is_prime(primes.get_ith_prime(lx), primes.get_ith_prime(mx), pl);
						if (!concat_prime) continue;
						concat_prime = concat_is_prime(primes.get_ith_prime(kx), primes.get_ith_prime(mx), pl);
						if (!concat_prime) continue;
						concat_prime = concat_is_prime(primes.get_ith_prime(jx), primes.get_ith_prime(mx), pl);
						if (!concat_prime) continue;
						concat_prime = concat_is_prime(primes.get_ith_prime(ix), primes.get_ith_prime(mx), pl);
						if (!concat_prime) continue;
						prime_set.emplace_back(primes.get_ith_prime(ix));
						prime_set.emplace_back(primes.get_ith_prime(jx));
						prime_set.emplace_back(primes.get_ith_prime(kx));
						prime_set.emplace_back(primes.get_ith_prime(lx));
						prime_set.emplace_back(primes.get_ith_prime(mx)); // TEST CASE 4

						found = true; // if reached here prime set complete - set found to true

					}
				}
			}
		}
	}

	for (u64 p : prime_set)
		cout << p << ' ';
	cout << '\n';

	u64 sum = accumulate(prime_set.begin(), prime_set.end(), 0LL);

	cout << "Sum of 5-Prime Set with Bi-append Prime Property = " << sum << '\n';
}
