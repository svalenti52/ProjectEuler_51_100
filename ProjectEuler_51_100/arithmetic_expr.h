#pragma once

#include <iostream>
#include "../repos/MonteCarlo/MonteCarlo/Combinatorics.h"
#include <algorithm>
#include <set>

using namespace std;

using VI = vector<int>;
using VVI = vector<vector<int>>;
using VSI = vector<std::set<int>>;

enum Operations
{
	plus_ = 1,
	minus_,
	multiply_,
	divide_
};

int find_ix_with_longest_seq_beg_with_1(VSI& vsi)
{
	int longest_seq_index = 0;
	int longest_seq = 0;

	int index = 0;
	for (auto si : vsi)
	{
		int consecutive_count = 1;
		for (auto i : si)
		{
			if (i <= 0);
			else if (i == consecutive_count) ++consecutive_count;
			else break;
		}
		if (longest_seq < consecutive_count)
		{
			longest_seq = consecutive_count;
			longest_seq_index = index;
		}
		++index;
	}

	return longest_seq_index;
}

double operate(Operations op, double i1, double i2)
{
	double result = 0.0;
	switch (op)
	{
	case plus_:
		result = i1 + i2;
		break;
	case minus_:
		result = i1 - i2;
		break;
	case multiply_:
		result = i1 * i2;
		break;
	case divide_:
		if (abs(i2 - 0) > .5)
			result = i1 / i2;
		break;
	default:
		return 0.0;
	}
	return result;
}

void mixed_order_operate(vector<Operations>& vop, VI& elts, VI& results)
{
	vector<double> elts_d;

	for (auto i : elts)
		elts_d.emplace_back(static_cast<double>(i));

	// 0, 1, 2
	double result = operate(vop[0], elts_d[0], elts_d[1]);
	result = operate(vop[1], result, elts_d[2]);
	result = operate(vop[2], result, elts_d[3]);
	double result_f = floor(result + 0.25);
	abs(result - result_f < 1e-8) ? results.emplace_back(static_cast<int>(result_f)) : results.emplace_back(0);

	// 0, 2, 1
	result = operate(vop[0], elts_d[0], elts_d[1]);
	double result1 = operate(vop[2], elts_d[2], elts_d[3]);
	result = operate(vop[1], result, result1);
	result_f = floor(result + 0.25);
	abs(result - result_f < 1e-8) ? results.emplace_back(static_cast<int>(result_f)) : results.emplace_back(0);

	// 1, 0, 2
	result = operate(vop[1], elts_d[1], elts_d[2]);
	result = operate(vop[0], elts_d[0], result);
	result = operate(vop[2], result, elts_d[3]);
	result_f = floor(result + 0.25);
	abs(result - result_f < 1e-8) ? results.emplace_back(static_cast<int>(result_f)) : results.emplace_back(0);

	// 1, 2, 0
	result = operate(vop[1], elts_d[1], elts_d[2]);
	result = operate(vop[2], result, elts_d[3]);
	result = operate(vop[0], elts_d[0], result);
	result_f = floor(result + 0.25);
	abs(result - result_f < 1e-8) ? results.emplace_back(static_cast<int>(result_f)) : results.emplace_back(0);

	// 2, 0, 1
	result = operate(vop[2], elts_d[2], elts_d[3]);
	result1 = operate(vop[0], elts_d[0], elts_d[1]);
	result = operate(vop[0], result1, result);
	result_f = floor(result + 0.25);
	abs(result - result_f < 1e-8) ? results.emplace_back(static_cast<int>(result_f)) : results.emplace_back(0);

	// 2, 1, 0
	result = operate(vop[2], elts_d[2], elts_d[3]);
	result = operate(vop[1], elts_d[1], result);
	result = operate(vop[0], elts_d[0], result);
	result_f = floor(result + 0.25);
	abs(result - result_f < 1e-8) ? results.emplace_back(static_cast<int>(result_f)) : results.emplace_back(0);
}

void arithmetic_expr()
{
	vector<int> symbols{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	vector<int> permutation;
	vector<vector<int>> combos;

	create_combinatorial_element_set<int>(symbols, combos, permutation, 0, 4, [](vector<int>& vi) {return true; }, combinations_without_repetition<int>);

	vector <Operations> operations{ plus_, minus_, multiply_, divide_ };
	vector<Operations> op_perm;
	vector<vector<Operations>> op_perms;

	create_combinatorial_element_set<Operations>(operations, op_perms, op_perm, 0, 3, [](vector<Operations>& vi) {return true; }, permutations_with_repetition<Operations>);

	cout << "Op Perms size = " << op_perms.size() << '\n';

	VSI answers;

	for (VI& vi : combos)
	{
		std::set<int> answer_v;
		double t_ans;
		do
		{
			for (auto& vops : op_perms)
			{
				vector<int> mixed_order(6, 0);

				mixed_order_operate(vops, vi, mixed_order);

				for (auto i : mixed_order)
					if (i > 0)
						answer_v.insert(i);
			}
		} while (next_permutation(begin(vi), end(vi)));
		answers.emplace_back(answer_v);
	}

	cout << "answers size = " << answers.size() << '\n';

	for (int ix = 0; ix < combos.size(); ++ix)
	{
		for (auto i : combos[ix])
			cout << i << ' ';
		cout << ":\n";
		for (auto i : answers[ix])
			cout << i << ' ';
		cout << "\n\n";
	}

	int index = find_ix_with_longest_seq_beg_with_1(answers);

	cout << "index with longest consecutive sequence = " << index << '\n';

	for (auto i : combos[index])
		cout << i << ' ';
	cout << ":\n";
	for (auto i : answers[index])
		cout << i << ' ';
	cout << "\n\n";

}
