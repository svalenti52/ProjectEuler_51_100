#pragma once

#include <vector>
#include <iostream>
#include "../repos/MonteCarlo/MonteCarlo/Combinatorics.h"

using namespace std;

int dim_M = 53;
int dim_N = 52;

bool passes_muster(vector<int>& test)
{
	if (test[1] > dim_N) return false;
	return true;
}

int count_rect(const int dM, const int dN, int rM, int rN)
{
	return ((dM - (rM - 1)) * (dN - (rN - 1)));
}

void counting_rectangles()
{
	int dist_from_2mil = billion;
	int m = 0;
	int n = 0;
	for (int m_side = 50; m_side < 105; ++m_side)
		for (int n_side = 1; n_side <= m_side; ++n_side)
		{
			dim_M = m_side;
			dim_N = n_side;
			vector<int> symbols(dim_M, 0);

			iota(begin(symbols), end(symbols), 1);

			vector<int> permutation;
			vector<vector<int>> permutations;

			create_combinatorial_element_set<int>(symbols, permutations, permutation, 0, 2, passes_muster, permutations_with_repetition<int>);

			int rect_M = dim_M;
			int rect_N = dim_N;

			vector<int> partial_sums;

			for (vector<int>& vi : permutations)
			{
				int count_rectangles = count_rect(dim_M, dim_N, vi[0], vi[1]);
				partial_sums.emplace_back(count_rectangles);
			}

			int total_sum = accumulate(begin(partial_sums), end(partial_sums), 0);

			int diff = abs(2'000'000 - total_sum);

			if (diff < dist_from_2mil)
			{
				dist_from_2mil = diff;
				m = dim_M;
				n = dim_N;
			}
		}

	cout << "Distance from 2 mil = " << dist_from_2mil << "  for M = " << m << "  N = " << n
		<< "  Product = " << m * n << '\n';
}
