#pragma once

#include <vector>
#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

using VI = vector<int>;

bool legitimate(const VI& vi)
{
	bool legit = false;

	int sum1 = vi[0] + vi[5] + vi[6];
	int sum2 = vi[1] + vi[6] + vi[7];
	int sum3 = vi[2] + vi[7] + vi[8];
	int sum4 = vi[3] + vi[8] + vi[9];
	int sum5 = vi[4] + vi[9] + vi[5];

	if (
		sum1 == sum2 &&
		sum2 == sum3 &&
		sum3 == sum4 &&
		sum4 == sum5
		)
	{
		if (
			vi[0] < vi[1] &&
			vi[0] < vi[2] &&
			vi[0] < vi[3] &&
			vi[0] < vi[4]
			)
		{
			legit = true;
		}
	}
	return legit;
}

string construct_5gon_rep(const VI& vi)
{
	string a = to_string(vi[0]) + to_string(vi[5]) + to_string(vi[6]);
	string b = to_string(vi[1]) + to_string(vi[6]) + to_string(vi[7]);
	string c = to_string(vi[2]) + to_string(vi[7]) + to_string(vi[8]);
	string d = to_string(vi[3]) + to_string(vi[8]) + to_string(vi[9]);
	string e = to_string(vi[4]) + to_string(vi[9]) + to_string(vi[5]);

	string s = a + b + c + d + e;

	return s;
}

void magic_5gon_ring()
{
	VI symbols(10, 0);
	iota(symbols.begin(), symbols.end(), 1);

	const int fixed = 10;
	string max_rep = "";
	do
	{
		if (legitimate(symbols))
		{
			/*for (int i : symbols)
				cout << i;
			cout << '\n';*/
			string ts = construct_5gon_rep(symbols);
			if (ts > max_rep)
				max_rep = ts;
		}
	} while (next_permutation(symbols.begin(), symbols.end()));

	cout << "Largest 16 bit number the 5-gon requirements = " << max_rep << '\n';
}
