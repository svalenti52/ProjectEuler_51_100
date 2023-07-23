#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include "../repos/MonteCarlo/MonteCarlo/Chronology.h"

using namespace std;

using VVI = vector<vector<int>>;
using VI = vector<int>;

//////////////////////////////////////////////////////////////////////////////

VVI vvi;

/////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////

int sum_from_bottom(VVI& vvi_sum)
{
	auto nrx = vvi_sum.rend();
	for (auto rx = vvi_sum.rbegin(); rx != vvi_sum.rend(); ++rx)
	{
		if (nrx != vvi_sum.rend())
		{
			for (auto cx = rx->begin(); cx != rx->end(); ++cx)
			{
				size_t cxx = cx - rx->begin();
				int left = *(nrx->begin() + cxx);
				int right = *(nrx->begin() + cxx + 1);
				if (left > right)
					*cx += left;
				else
					*cx += right;
			}
		}
		nrx = rx;
	}

	auto sum = vvi_sum[0].begin();

	return *sum;
}

void show_vvi_sum(VVI& vvi_sum)
{
	for (auto vi : vvi_sum)
	{
		for (int i : vi)
			cout << setw(5) << i << " ";
		cout << '\n';
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////

void max_path_sum_2()
{
	ifstream in("triangle_path_2.txt");

	if (in.is_open())
		cout << "open\n";
	else
		cout << "not open\n";

	while (!in.eof())
	{
		string line;
		getline(in, line);
		using tokenizer = boost::tokenizer<boost::char_separator<char>>;
		boost::char_separator<char> sep(" ");
		tokenizer tokens(line, sep);
		vector<int> vi;
		for (tokenizer::iterator tok_iter = tokens.begin();
			tok_iter != tokens.end(); ++tok_iter)
			vi.emplace_back(stoi(*tok_iter, nullptr, 10));
		vvi.emplace_back(vi);
	}
	//++++++++++++++++++++++++++++++++++++++++
	int max_sum = 0;
	VVI remove_max_array{ vvi };

	StopWatch sw;
	int sum = sum_from_bottom(vvi);
	sw.stop();

	cout << "Maximum Path = " << sum << '\n';

}
