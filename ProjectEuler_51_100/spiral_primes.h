#pragma once

#include <vector>
#include <algorithm>
#include <iostream>
#include "../repos/MonteCarlo/MonteCarlo/Primes.h"

void spiral_primes()
{
	using namespace std;

	Primes_List pl(1'000'000'000);

	vector<vector<int>> matrix_spiral = { {3, 13, 31}, { 5, 17, 37 }, { 7, 21, 43 }, { 9, 25, 49 } };
	// Add 1 for the '1' at the center

	vector<int> diffs = { 26, 28, 30, 32 };

	vector<int> count_primes = { 0, 0, 0, 0 };

	int spiral_side_len = 7;

	double fraction_prime;

	for (int ix = 0; ix < 14'000; ++ix)
	{
		int total_prime = 0;
		int total_numbers = 1; // counting the one at the beginning

		int jx = 0;
		for (auto& vi : matrix_spiral)
		{
			vi.emplace_back(*(vi.end() - 1) + diffs[jx]);
			diffs[jx] += 8;
			++jx;
		}
		spiral_side_len += 2;
		jx = 0;
		for (auto& vi : matrix_spiral)
		{
			count_primes[jx] = count_if(vi.begin(), vi.end(), [&pl](int i) { return pl.is_prime(i); });
			++jx;
		}

		for (int t : count_primes)
			total_prime += t;
		for (auto& vi : matrix_spiral)
			total_numbers += vi.size();

		fraction_prime = static_cast<double>(total_prime) / static_cast<double>(total_numbers);

		if (fraction_prime < 0.1) break;

	}
	for (auto& vi : matrix_spiral)
		cout << vi[vi.size()-1] << ", ";
	cout << '\n';

	cout << "\nSpiral Side Length at which Fraction of Primes drops under 0.1 is " << spiral_side_len << '\n';
	cout << "Fraction is " << fraction_prime << '\n';
}
