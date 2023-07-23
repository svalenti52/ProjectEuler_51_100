#pragma once

#include <iostream>
#include "../repos/MonteCarlo/MonteCarlo/Primes.h"

using namespace std;

using VI = vector<int>;

const int ub = 10'000;
static Primes_List pl(ub);
static Primes primes(pl, ub);

//static const int target_sum = 100;


static void show_extended_vector(VI& vi, int target_diff)
{
	for (int i : vi)
		cout << i << ' ';
	cout << target_diff << '\n';
}

void count_by_index(int index, VI& vi, int& count, int px, const int target_sum)
{
	int target_diff = 0; // this is at vsize, i.e., outside the vector
	int vsize = vi.size();
	auto endvs_it = end(vi) - 1;

	if (index == vsize - 1) // last one in vector
	{
		target_diff = target_sum - accumulate(begin(vi), end(vi), 0LL);

		while (*endvs_it <= target_diff)
		{
			if (pl.is_prime(target_diff))
			{
				++count;
				//show_extended_vector(vi, target_diff);
			}
			++px;
			*endvs_it = primes.get_ith_prime(px);
			target_diff -= (primes.get_ith_prime(px) - primes.get_ith_prime(px-1));
		}
	}
	else
	{
		do
		{
			count_by_index(index + 1, vi, count, px, target_sum);
			++px;
			vi[index] = primes.get_ith_prime(px);
			for (auto it_right = begin(vi) + index + 1; it_right != end(vi); ++it_right)
				*it_right = vi[index];
			target_diff = target_sum - accumulate(begin(vi), end(vi), 0);
			//if (index == vsize / 3)
			//	show_extended_vector(vi, target_diff);

		} while (vi[index] <= target_diff);//vs[index] < (target_sum - sum_prior) / (vsize - index));
	}

}

void prime_summations()
{
	int count = 0;
	int ts = 10;

	for (; ts <= 100; ++ts)
	{
		for (int ix = 1; ix <= ts / 2; ++ix)
		{
			VI vi(ix, primes.get_ith_prime(0));
			count_by_index(0, vi, count, 0, ts);
		}
		if (count > 5000) break;
		else count = 0;
	}

	cout << "Combination of Primes Count = " << count << "  for Number = " << ts << '\n';
}
