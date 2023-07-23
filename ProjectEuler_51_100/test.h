#pragma once

#include <set>
#include <iostream>
#include <tuple>

using u64 = uint64_t;

void test()
{
	using namespace std;

	set<pair<u64, u64>> ints;

	for (u64 x = 1; x < 10; ++x)
		ints.insert(make_pair(x, x + 1));

	for (pair<u64, u64> px : ints)
		cout << "(" << px.first << "," << px.second << ")  ";
	cout << '\n';
}
