#pragma once

#include <deque>
#include <iostream>
#include "../../MonteCarlo/MonteCarlo/Primes.h"
#include "../../MonteCarlo/MonteCarlo/Combinatorics.h"

using namespace std;
using u64 = uint64_t;

u64 construct_number_from_digits(deque<u64> ds)
{
	u64 number = 0;
	for (u64 d : ds)
		number = 10 * number + d;
	return number;
}

u64 insert_digits(u64 p, Primes_List& pl, int d1, int d2, int d3)
{
	deque<u64> digits = number_to_digits_ms_to_ls(p);
	
	u64 count = 0;
	for (u64 ix = 0; ix < 10; ++ix)
	{
		if (ix == 0 && d1 == 0) continue; // lead 0's not permitted
		// need to insert variable indices
		digits[d1] = ix;
		digits[d2] = ix;
		digits[d3] = ix;

		u64 test_prime = construct_number_from_digits(digits);
		if (pl.is_prime(test_prime))
			++count;
	}
	return count;
}

void prime_digit_replacement()
{
	Primes_List pl(1'000'000);
	Primes primes(pl, 1'000'000);

	vector<int> symbols = {0, 1, 2, 3, 4};
	vector<int> permutation;
	vector<vector<int>> permutations;

	create_combinatorial_element_set<int>(symbols, permutations, permutation, 0, 3, [](vector<int>& x) {return true; }, combinations_without_repetition<int>);

	u64 max_nr_primes = 0;

	for (int ix = 0; ix <= primes.get_last_index(); ++ix)
	{
		u64 prime = primes.get_ith_prime(ix);
		if (prime < 100'000) continue;

		for (vector<int>& vd : permutations)
		{

			u64 count = insert_digits(prime, pl, vd[0], vd[1], vd[2]);

			if (count > max_nr_primes)
				max_nr_primes = count;

			if (count == 8)
			{
				cout << "Digit Positions to do Substitution\n";
				for (int x : vd)
					cout << x << ", ";
				cout << "\n\n";
				break;
			}
		}
		if (max_nr_primes == 8)
			break;
	}

	cout << "Max Nr of Primes = " << max_nr_primes << '\n';
	cout << "Millionth Prime (Upper Bound on Primes to Search) = " << primes.get_ith_prime(primes.get_last_index()) << '\n';
}
