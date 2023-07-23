#pragma once

#include <vector>
#include <iostream>
#include <string>
#include "../repos/MonteCarlo/MonteCarlo/Combinatorics.h"

using namespace std;

using VB = vector<bool>;

string convert_to_string(VI& vi)
{
	string tmp;
	for (int i : vi)
	{
		char c = 48 + i;
		tmp.push_back(c);
	}
	return tmp;
}

bool stf(const char c, const string& s)
{
	if (s.find(c) != string::npos) return true;
	return false;
}

bool strings_meet_req(const string& s1, const string& s2)
{
	auto np = string::npos;

	if (!((stf('0', s1) && stf('1', s2)) || (stf('0', s2) && stf('1', s1)))) return false;
	if (!((stf('0', s1) && stf('4', s2)) || (stf('0', s2) && stf('4', s1)))) return false;
	if (!((stf('0', s1) && (stf('6', s2) || stf('9', s2))) || (stf('0', s2) && (stf('6', s1) || stf('9', s1)) ) ) ) return false;

	if ( !( (stf('1', s1) && (stf('6', s2) || stf('9', s2))) || (stf('1', s2) && (stf('6', s1) || stf('9', s1))) ) ) return false;

	if ( !( (stf('2', s1) && stf('5', s2)) || (stf('2', s2) && stf('5', s1)) ) ) return false;
	
	if ( !( ( stf('3', s1) && (stf('6', s2) || stf('9', s2)) ) || ( stf('3', s2) && (stf('6', s1) || stf('9', s1)) ) ) ) return false;

	if (!( (stf('4', s1) && (stf('6', s2) || stf('9', s2))) || (stf('4', s2) && (stf('6', s1) || stf('9', s1))) )) return false;

	if (!( ( stf('1', s1) && stf('8', s2) ) || ( stf('1', s2) && stf('8', s1)) ) ) return false;

	return true;
}

void expand_string_69(string& s)
{
	auto np = string::npos;

	if (s.find('6') != np && s.find('9') == np)
		s.push_back('9');
	else if (s.find('6') == np && s.find('9') != np)
		s.push_back('6');

	sort(s.begin(), s.end());
}

void cube_digit_pairs()
{
	VI symbols = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	VI combo;
	VVI combos1;
	VVI combos2;

	set<string> red1;
	set<string> red2;
	set<pair<string, string>> red_pair;

	vector<string> red_1;
	vector<string> red_2;

	int count_square_dice = 0;

	create_combinatorial_element_set<int>(symbols, combos1, combo, 0, 6, [](VI& vi) { return true; }, combinations_without_repetition<int>);

	create_combinatorial_element_set<int>(symbols, combos2, combo, 0, 6, [](VI& vi) { return true; }, combinations_without_repetition<int>);

	int kx = 0;

	for (auto vi1 : combos1)
	{
		for (auto vi2 : combos2)
		{
			string s1 = convert_to_string(vi1);
			string s2 = convert_to_string(vi2);

			if (!strings_meet_req(s1, s2)) continue;

			++count_square_dice;
			
			expand_string_69(s1);
			expand_string_69(s2);

			if (s2 < s1) continue;

			red1.insert(s1);
			red2.insert(s2);

			red_1.push_back(s1);
			red_2.push_back(s2);
		}
	}

	vector<pair<string, string>> vp_red;
	int count_of_comparisons = 0;

	for (int rx = 0; rx < red_1.size(); ++rx)
	{
		{
			++count_of_comparisons;
			vp_red.emplace_back(make_pair(red_1[rx], red_2[rx]));
		}
	}

	int ix = 0;
	for (auto ps : vp_red)
		cout << ++ix << ". " << ps.first << " - " << ps.second << '\n';
	cout << "count of comparisons = " << count_of_comparisons << '\n';

	cout << "size set 1 = " << red1.size() << '\n';
	cout << "size set 2 = " << red2.size() << '\n';

	cout << "Squares Dice Count = " << count_square_dice << '\n';

}
