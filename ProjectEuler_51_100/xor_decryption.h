#pragma once

#include <vector>
#include <fstream>
#include <numeric>
#include <iostream>
#include <string>
#include "../repos/MonteCarlo/MonteCarlo/Combinatorics.h"
#include <boost/tokenizer.hpp>

void xor_decryption()
{
	using namespace std;
	vector<char> symbols(26, 'a');
	vector<char> permutation;
	vector<vector<char>> permutations;

	iota(symbols.begin(), symbols.end(), 'a');

	//for (char s : symbols)
	//	cout << s << ", ";
	//cout << '\n';

	create_combinatorial_element_set<char>(symbols, permutations, permutation, 0, 3, [](vector<char>& c) {return true; }, permutations_without_repetition<char>);

	//for (auto& vc : permutations)
	//{
	//	for (auto c : vc)
	//		cout << c << " ";
	//	cout << '\n';
	//}

	ifstream in("p059_cipher.txt");
	if (in.is_open())
		cout << "OPEN!!\n";
	else
	{
		cout << "FILE NOT OPEN\n";
		return;
	}
	string encrypted_ascii;
	in >> encrypted_ascii;

	vector<string> cipher;
	using tokenizer = boost::tokenizer<boost::char_separator<char>>;
	boost::char_separator<char> sep(",");
	tokenizer tokens(encrypted_ascii, sep);
	for (tokenizer::iterator tok_iter = tokens.begin();
		tok_iter != tokens.end(); ++tok_iter)
		cipher.emplace_back(*tok_iter);


	vector<char> cipher_numeric;
	vector<char> plain_text;
	for (string& s : cipher)
		cipher_numeric.emplace_back(stol(s, nullptr));

	//for (string& s : cipher)
	//	cout << s << " ";
	//cout << '\n';

	//for (char c : cipher_numeric)
	//	cout << c << " ";
	//cout << '\n';

	for (int kx = 2942; kx < 2943; ++kx)
	{
		bool likely_message = false;
		string msg;
		for (int ix = 0; ix < cipher_numeric.size(); ++ix)
		{
			char c = cipher_numeric[ix] ^ permutations[kx][ix%3];
			plain_text.emplace_back(c);
//			if ((c >= 'A' || c <= 'z') && (c > '@' || c == ' ' || c == '.')) {
				likely_message = true;
				msg += c;
//			}
			//else
			//{
			//	likely_message = false;
			//	break;
			//}
		}
		//if (likely_message)
		//{
		//	cout << kx << ".  ";
		//	cout << msg << '\n';;
		//}
	}

	for (char c : plain_text)
	{
		cout << c;
	}
	cout << '\n';

	int sum = accumulate(plain_text.begin(), plain_text.end(), 0);

	cout << "Sum of plain text = " << sum << '\n';
}
