#pragma once

#include <set>
#include <vector>
#include <iostream>
#include "../repos/MonteCarlo/MonteCarlo/Chronology.h"

using namespace std;

void amicable_chains()
{
	const int chain_lengths = 1'000'000;
	vector<vector<int>> chains;
	vector<int> acc_div(chain_lengths, 0);

	int max_chain_length = 0;

	StopWatch stopwatch;

	for (int ix = 1; ix <= chain_lengths; ++ix)
	{
		vector<int> chain;
		chains.push_back(chain);
	}

	int number = 1;
	for (auto& vi : chains)
	{
		for (int div = 1; div <= number / 2; ++div)
			if (number % div == 0)
				vi.emplace_back(div);

		++number;
	}

	number = 1;
	for (int& i : acc_div)
	{
		if (number == 1)
			i = 1;
		else
			i = accumulate(chains[number - 1].begin(), chains[number-1].end(), 0);
		++number;
	}

	stopwatch.stop();

	StopWatch sw;

	for (int ix = 10; ix <= chain_lengths; ++ix)
	{
		std::set<int> si;

		int index = ix;
		bool amicable = false;
		auto pr = si.insert(index);
		while (pr.second)
		{
			index = acc_div[index - 1];
			if (index > chain_lengths)
			{
				pr = si.insert(0);
				break;
			}
			pr = si.insert(index);
			if (index == ix) amicable = true;
		}

		if (max_chain_length < si.size() && amicable)
		{
			max_chain_length = si.size();
			cout << "number " << ix << " has amicable chain length " << max_chain_length << "  smallest elt in chain = " << *si.begin() << '\n';

			for (auto i : si)
				cout << i << ' ';
			cout << "\n\n";
		}
	}

	sw.stop();
}
