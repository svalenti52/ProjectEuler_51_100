#pragma once

#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <Eigen/src/Core/Matrix.h>
#include <boost/tokenizer.hpp>

using namespace std;
using u64 = uint64_t;
using VST = vector<string>;

using Eigen::Matrix;
using M_80_x_80 = Matrix<u64, 80, 80>;
using M_80_x_1 = Matrix<u64, 80, 1>;
//using M_5_x_5 = Matrix<u64, 5, 5>;

const int ub_index = 80;

void sum_all_paths_to_right(int row, vector<u64>& vu, M_80_x_1& m, M_80_x_1& rc)
{
	for (int sx = 0; sx < row; ++sx)
	{
		u64 sum = m(sx) + rc(sx);
		for (int ssx = sx + 1; ssx < row; ++ssx)
			sum += m(ssx);
		vu.emplace_back(sum);
	}

	vu.emplace_back(rc(row));

	for (int sx = ub_index - 1; sx > row; --sx)
	{
		u64 sum = m(sx) + rc(sx);
		for (int ssx = sx - 1; ssx > row; --ssx)
			sum += m(ssx);
		vu.emplace_back(sum);
	}
}

void cost_from_right(int cx, M_80_x_80& m)
{
	// assume always have a "to right", i.e., passed in cx in range [0..78], not 79
	M_80_x_1 colr = m.col(cx+1);
	M_80_x_1 col = m.col(cx);
	M_80_x_1 tmp;

	for (int rx = 0; rx < ub_index; ++rx)
	{
		vector<u64> paths;

		sum_all_paths_to_right(rx, paths, col, colr);

		auto min_sum = min_element(paths.begin(), paths.end());

		tmp(rx) = *min_sum + col(rx);
	}

	m.col(cx) = tmp;
}


void path_sum_3_way()
{
	M_80_x_80 path_matrix;
	VST vs;

	ifstream in("matrix_80_x_80.txt");
	if (!in.is_open())
	{
		cout << "FILE NOT OPEN\n";
		return;
	}

	while (!in.eof())
	{
		string row;
		in >> row;
		vs.emplace_back(row);
	}

	for (int rx = 0; rx < ub_index; ++rx)
	{
		vector<string> cols;
		using tokenizer = boost::tokenizer<boost::char_separator<char>>;
		boost::char_separator<char> sep(",");
		tokenizer tokens(vs[rx], sep);
		for (tokenizer::iterator tok_iter = tokens.begin();
			tok_iter != tokens.end(); ++tok_iter)
			cols.emplace_back(*tok_iter);

		for (int jx = 0; jx < ub_index; ++jx)
			path_matrix(rx, jx) = strtol(cols[jx].c_str(), nullptr, 10);
	}

	for (int cx = 78; cx >= 0; --cx)
		cost_from_right(cx, path_matrix);

	M_80_x_1 zero_col = path_matrix.col(0);

	auto min_path_cost = min_element(zero_col.begin(), zero_col.end());

	cout << "Minimum Path Cost 3-Way = " << *min_path_cost << '\n';
}
