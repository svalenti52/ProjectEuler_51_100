#pragma once

#include <iostream>
#include <vector>
#include <numeric>
#include <boost/multiprecision/cpp_int.hpp>
#include "../repos/MonteCarlo/MonteCarlo/Chronology.h"

using namespace std;
using CPP_INT = cpp_int;
using VI = vector<int>;
using VCI = vector<CPP_INT>;

void coin_partitions()
{
	int target_sum = 60'000;
	VI numbers(target_sum - 1, 0);
	iota(begin(numbers), end(numbers), 1);

	VCI results(target_sum + 1, 0);
	results[0] = 1;

	StopWatch stopWatch;

	for (int i : numbers)
	{
		for (int j = i; j <= target_sum; j++) {
			results[j] += results[j - i];
		}
	}

	stopWatch.stop();

	*(end(results) - 1) += 1; // have to add one to the last value, all prior are complete

	//for (CPP_INT i : results)
	//	cout << i << ' ';
	//cout << '\n';

	auto ans_it = find_if(begin(results), end(results), [](CPP_INT i) {if (i % 1'000'000 == 0) return true; return false; });

	if (ans_it != end(results))
	{
		size_t ts = ans_it - begin(results);
		cout << '\n' << ts << '\n';
	}
	else
	{
		cout << "Not Found\n";
	}

}
