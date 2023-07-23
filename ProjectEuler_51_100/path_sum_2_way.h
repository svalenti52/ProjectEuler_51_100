#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <Eigen/Dense>
#include <Eigen/src/Core/Matrix.h>

using namespace std;
using u64 = uint64_t;
using VST = vector<string>;

using Eigen::MatrixXi;
using Eigen::Matrix;
using M_80_x_80 = Matrix<u64, 80, 80>;

u64 find_path(int rx, int cx, M_80_x_80& m)
{
	u64 right = 0;
	u64 down = 0;
	if (rx == 79 && cx == 79) return m(rx, cx);
	if (rx != 79)
		right = find_path(rx + 1, cx, m);
	if (cx != 79)
		down = find_path(rx, cx + 1, m);
	return m(rx, cx) + min(right, down);
}

void cost_bottom_up(int tx, M_80_x_80& m, M_80_x_80& c)
{
	int anchor = min(79, tx);
	int rx = anchor;
	int cx = tx - rx;

	for (; cx <= anchor; ++cx, --rx)
	{
		if (rx == 79 && cx == 79)
			c(rx, cx) = m(rx, cx);
		else if (rx == 79)
			c(rx, cx) = m(rx, cx) + c(rx, cx + 1);
		else if (cx == 79)
			c(rx, cx) = m(rx, cx) + c(rx + 1, cx);
		else
			c(rx, cx) = m(rx, cx) + min(c(rx + 1, cx), c(rx, cx + 1));
	}
}


void path_sum_2_way()
{
	M_80_x_80 path_matrix;
	M_80_x_80 cost_matrix;
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

	for (int rx = 0; rx < 80; ++rx)
	{
		vector<string> cols;
		using tokenizer = boost::tokenizer<boost::char_separator<char>>;
		boost::char_separator<char> sep(",");
		tokenizer tokens(vs[rx], sep);
		for (tokenizer::iterator tok_iter = tokens.begin();
			tok_iter != tokens.end(); ++tok_iter)
			cols.emplace_back(*tok_iter);

		for (int jx = 0; jx < 80; ++jx)
			path_matrix(rx, jx) = strtol(cols[jx].c_str(), nullptr, 10);
	}

	for (int tx = 158; tx >= 0; --tx)
		cost_bottom_up(tx, path_matrix, cost_matrix);

	u64 min_path = cost_matrix(0, 0);

	cout << "Minimum Path for right/down = " << min_path << '\n';
}
