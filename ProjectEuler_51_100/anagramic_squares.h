#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include "../repos/Utilities/Utilities/comma_separated.h"
#include "../repos/MonteCarlo/MonteCarlo/Combinatorics.h"
#include "../repos/MonteCarlo/MonteCarlo/Primes.h"

using namespace std;

bool passes_must(VI& vi)
{
	if (vi[0] == 0) return false;
	switch (vi[vi.size() - 1])
	{
	case 0:
	case 2:
	case 3:
	case 7:
	case 8:
		return false;
	default:
		break;
	}
	return true;
}

VI twice_mult_count(const string& s, const string& t)
{
	string temp;
	VI twice;
	for (int ix = 0; ix < s.size() - 1; ++ix)
	{
		temp = s.substr(ix + 1, s.size() - ix);
		size_t pos = temp.find(s[ix]);
		if (pos == string::npos) continue;
		else
		{
			twice.emplace_back(ix);
			twice.emplace_back(ix + 1 + pos);
		}
	}

	if (twice.size() != 0)
	{
		for (int ix = 0; ix < t.size() - 1; ++ix)
		{
			temp = t.substr(ix + 1, t.size() - ix);
			size_t pos = temp.find(t[ix]);
			if (pos == string::npos) continue;
			else
			{
				twice.emplace_back(ix);
				twice.emplace_back(ix + 1 + pos);
			}
		}
	}

	return twice;
}

bool is_square(int number)
{
//	cout << "sqr test = " << number << '\n';
	double sq_root = sqrt(static_cast<double>(number));
	if (abs(sq_root - floor(sq_root) < 1e-8)) return true;
	return false;
}

void anagramic_squares()
{
	using VPSS = vector<pair<string, string>>;
	using PSS = pair<string, string>;
	vector<string> vs;
	string words{ "words.txt" };
	VPSS anagrams;

	read_comma_quoted_string(words, vs);

	for (auto it_s = vs.begin(); it_s != vs.end(); ++it_s)
	{
		cout << *it_s << '\n';
		for (auto it_t = it_s + 1; it_t != vs.end(); ++it_t)
		{
			if (it_s->size() == it_t->size())
			{
				string u = *it_s;
				string v = *it_t;
				bool letters_in_common = true;
				for (auto c : *it_s)
				{
					auto x = v.find(c);
					if (x == string::npos)
					{
						letters_in_common = false;
						break;
					}
				}
				

				next_permutation(begin(v), end(v));
				
				while (letters_in_common && *it_t != v)
				{
					if (*it_s == v)
						anagrams.emplace_back(make_pair(*it_s, *it_t));
					next_permutation(begin(v), end(v));
				}
			}
		}
	}

	sort(begin(anagrams), end(anagrams), [](PSS& lhs, PSS& rhs) { return lhs.first.size() > rhs.first.size(); });

	for (auto prs : anagrams)
	{
		cout << prs.first << "  " << prs.second << '\n';
	}

	VI symbols_(10, 0);
	iota(begin(symbols_), end(symbols_), 0);
	VVI combos;
	VI combo;
	vector<int> number1, number2;
	for (auto& prs : anagrams)
	{
		number1.resize(prs.first.size());
		number2.resize(prs.first.size());

		vector<int> twice = twice_mult_count(prs.first, prs.second);
		if (twice.size() != 0)
			cout << "twice => " << prs.first << "  " << '\n';

		create_combinatorial_element_set<int>(symbols_, combos, combo, 0, prs.first.size(), passes_must, permutations_without_repetition<int>);

		for (VI& fir_digits : combos)
		{
			if (twice.size() != 0)
				fir_digits[twice[1]] = fir_digits[twice[0]];

			int m = digits_to_number_ms_to_ls(fir_digits);
			if (is_square(m))
			{
				VI sec_digits(prs.first.size(), 0); // first and second size should be identical
				int fpos = 0;
				for (auto c : prs.first)
				{
					size_t spos = prs.second.find(c);
					sec_digits[spos] = fir_digits[fpos];
					++fpos;
				}
				if (twice.size() != 0)
					sec_digits[twice[3]] = sec_digits[twice[2]];
				int n = digits_to_number_ms_to_ls(sec_digits);
				if (is_square(n))
					cout << "--got it--  " << m << "  " << n << "  " << prs.first << '\n';
			}
		}
		combos.clear();
		combo.clear();
	}
}
