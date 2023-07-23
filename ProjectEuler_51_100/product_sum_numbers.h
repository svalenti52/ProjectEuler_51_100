#pragma once

//#include "../repos/MonteCarlo/MonteCarlo/Primes.h"
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

const int n_set_largest_size = 12'000;

int get_n_set_size(vector<int>& m_set)
{
	int n_prod = accumulate(begin(m_set), end(m_set), 1, multiplies());
	int m_sum = accumulate(begin(m_set), end(m_set), 0);

	return n_prod - m_sum + m_set.size();
}

void prep_n_set(vector<int>& nss, vector<int>& m_set, int index)
{
	if (m_set.size() == 0)
	{
		m_set.emplace_back(2);
		prep_n_set(nss, m_set, 0);
	}
	if (m_set.size() == 1)
	{
		m_set.emplace_back(2);
		prep_n_set(nss, m_set, 1);
	}
	else if (m_set.size() == 14) // note: 2^14 < 2 * 12,000
	{
		for (int ix = 2; ix <= n_set_largest_size; ++ix)
		{
			m_set[index] = ix;
			int n_prod = accumulate(begin(m_set), end(m_set), 1, multiplies());
			if (n_prod > 2 * n_set_largest_size) break;
			int n_set_sz = get_n_set_size(m_set);

			if (n_set_sz <= n_set_largest_size)
				if (n_prod < nss[n_set_sz])
					nss[n_set_sz] = n_prod;
		}
	}
	else if (m_set.size() == 2)
	{
		for (int ix = 2; ix <= n_set_largest_size; ++ix)
			for (int jx = ix; jx <= n_set_largest_size; ++jx)
			{
				m_set[0] = ix;
				m_set[1] = jx;
				int n_prod = accumulate(begin(m_set), end(m_set), 1, multiplies());
				if (n_prod > 2 * n_set_largest_size) break;
				int n_set_sz = get_n_set_size(m_set);

				if (n_set_sz <= n_set_largest_size)
					if (n_prod < nss[n_set_sz])
						nss[n_set_sz] = n_prod;
				m_set.emplace_back(2);
				prep_n_set(nss, m_set, 2);
				m_set.pop_back();
			}
	}
	else // size 3 - 13 inclusive
	{
		for (int ix = 2; ix <= n_set_largest_size; ++ix)
		{
			m_set[index] = ix;
			int n_prod = accumulate(begin(m_set), end(m_set), 1, multiplies());
			if (n_prod > 2 * n_set_largest_size) break;
			int n_set_sz = get_n_set_size(m_set);

			if (n_set_sz <= n_set_largest_size)
				if (n_prod < nss[n_set_sz])
					nss[n_set_sz] = n_prod;
			m_set.emplace_back(2);
			prep_n_set(nss, m_set, index + 1);
			m_set.pop_back();
		}
	}
}

void product_sum_numbers()
{
	vector<int> n_set_sizes(n_set_largest_size + 1, billion);

	n_set_sizes[0] = 0;
	n_set_sizes[1] = 0;

	vector<int> mset(2, 2);

	prep_n_set(n_set_sizes, mset, 0);

	int ix = 0;
	for (auto x : n_set_sizes)
		cout << ix++ << ". " << x << '\n';

	set<int> unique_mins;
	for (auto n : n_set_sizes)
		unique_mins.insert(n);

	int sum_min = accumulate(begin(unique_mins), end(unique_mins), 0);

	cout << "Sum of Minimum Numbers is " << sum_min << '\n';
}

