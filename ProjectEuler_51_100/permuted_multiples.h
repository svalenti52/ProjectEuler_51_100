#pragma once

#include <vector>
#include <deque>
#include <iostream>
#include "../../MonteCarlo/MonteCarlo/Combinatorics.h"

void permuted_multiples()
{
	using namespace std;

	vector<int> symbols = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	vector<int> permutation;
	vector<vector<int>> permutations;

	// Try less the 10,000,000
	// Digit 0 (ms) must be one
	// Digit 1 taken from 0 - 6
	// Digit 2-6 are taken from permutation

	create_combinatorial_element_set<int>(symbols, permutations, permutation, 0, 4, [](vector<int>& v) {return true; }, permutations_without_repetition<int>);

	deque<int> digits;

	bool found_matching = false;

	int first_digit = 1;
	for (int ix = 0; ix < 7; ++ix)
	{
		for (vector<int>& vi : permutations)
		{
			digits.emplace_back(first_digit);
			digits.emplace_back(ix);
			for (int i : vi)
			{
				digits.emplace_back(i);
			}
			deque<int> tmp_digits = digits;
			int number = digits_to_number_ms_to_ls(tmp_digits);
			cout << number << ", ";
			int _2x = 2 * number;
			int _3x = 3 * number;
			int _4x = 4 * number;
			int _5x = 5 * number;
			int _6x = 6 * number;
			deque<int> _2xd = number_to_digits_ms_to_ls(_2x);
			deque<int> _3xd = number_to_digits_ms_to_ls(_3x);
			deque<int> _4xd = number_to_digits_ms_to_ls(_4x);
			deque<int> _5xd = number_to_digits_ms_to_ls(_5x);
			deque<int> _6xd = number_to_digits_ms_to_ls(_6x);
			sort(digits.begin(), digits.end());
			sort(_2xd.begin(), _2xd.end());
			sort(_3xd.begin(), _3xd.end());
			sort(_4xd.begin(), _4xd.end());
			sort(_5xd.begin(), _5xd.end());
			sort(_6xd.begin(), _6xd.end());
			if (digits == _2xd && digits == _3xd && digits == _4xd && digits == _5xd && digits == _6xd)
			{
				found_matching = true;
				break;
			}
			digits.clear();
		}
		if (found_matching) break;
	}
	if (found_matching)
		cout << "found it\n";
	else
		cout << "not found\n";
}
