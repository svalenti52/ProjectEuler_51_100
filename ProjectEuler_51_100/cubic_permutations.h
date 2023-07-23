#pragma once

#include <vector>
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;
using u64 = uint64_t;

void cubic_permutations()
{
	vector<u64> vi;
	vector<string> ns;

	for (u64 ix = 345; ix < 10'000; ++ix)
		vi.emplace_back(ix * ix * ix);

	for (u64 d : vi)
		//if (d < 100'000'000) continue;
		ns.emplace_back(to_string(d));
	//	cout << d << ", ";
	//cout << '\n';

	int max_count = 0;

	for (int ix = 0; ix < ns.size(); ++ix)
	{
		int count = 0;
		int jx = ix + 1;
		for (int jx = ix+1; jx < ns.size(); ++jx)
			if (is_permutation(ns[jx].begin(), ns[jx].end(), ns[ix].begin()))
				++count;
		if (count == 4)
			max_count = count;
		if (max_count == 4)
		{
			cout << ns[ix] << '\n';
			break;
		}
	}
	cout << "Permutations = " << max_count << '\n';
}
