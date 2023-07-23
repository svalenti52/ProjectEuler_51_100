#pragma once

#include <iostream>
#include <fstream>
#include <numeric>
#include <string>
#include <vector>
#include <set>
#include <list>
#include <tuple>
#include <boost/tokenizer.hpp>

using namespace std;

using PCC = pair<char, char>;
using SPCC = set<PCC>;
using SC = set<char>;
using VC = vector<char>;

void show_chars(SC& sc)
{
	for (char c : sc)
		cout << c << ' ';
	cout << '\n';
}

void show_chars(VC& vc)
{
	for (char c : vc)
		cout << c << ' ';
	cout << '\n';
}

void show_pairs_chars(SPCC& spcc)
{
	for (PCC pc : spcc)
		cout << '(' << pc.first << ',' << pc.second << ") ";
	cout << '\n';
}

///////////////////////////////////////////////////

void passcode_derivation()
{
	vector<string> vs;
	ifstream in("keylog.txt");
	if (!in.is_open())
	{
		cout << "FILE NOT OPEN\n";
		return;
	}

	while (!in.eof())
	{
		string keylog;
		in >> keylog;
		vs.emplace_back(keylog);
	}
	SPCC ordered_pair_of_chars;
	SC sc;

	for (string& s : vs)
	{
		// 
		ordered_pair_of_chars.insert(make_pair(s[0], s[1]));
		ordered_pair_of_chars.insert(make_pair(s[0], s[2]));
		ordered_pair_of_chars.insert(make_pair(s[1], s[2]));
		for (char c : s)
			sc.insert(c);
	}

	vector<char> preceding_chars;

	while (!ordered_pair_of_chars.empty())
	{
		vector<char> remove_in_order;
		for (char c : sc)
		{
			bool preceeds_all = true;
			for (auto& p : ordered_pair_of_chars)
			{
				if (c == p.second)
				{
					preceeds_all = false;
					break;
				}
			}
			if (preceeds_all)
			{
				preceding_chars.emplace_back(c);
				bool removed_all = false;
				while (!removed_all)
				{
					auto pair_it = find_if(begin(ordered_pair_of_chars), end(ordered_pair_of_chars), [&c](auto pc)
						{ if (c == pc.first) return true; return false; });
					if (pair_it == ordered_pair_of_chars.end())
					{
						removed_all = true;
						remove_in_order.emplace_back(c);
					}
					else
					{
						ordered_pair_of_chars.erase(pair_it);
					}
				}
				// at completion, all existing "preceding all" chars detectable in current loop
				// should be in remove_in_order
			}
//			cout << "\nShrinking Set\n";
//			show_pairs_chars(sos);
		} // end -- for (char c : sc)
		for (char c : remove_in_order)
		{
			auto remove_it = find(begin(sc), end(sc), c);
			if (remove_it != end(sc))
			{
				//cout << "\n   removed single char = " << c << '\n';
				sc.erase(remove_it);
			}
		}
		remove_in_order.clear();
	}

	for (char c : sc)
		preceding_chars.emplace_back(c); // finally, put in the character that preceeds none!

	show_chars(preceding_chars);
}
