#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <iomanip>
#include <boost/tokenizer.hpp>
#include "../repos/MonteCarlo/MonteCarlo/Chronology.h"

using namespace std;
using u64 = uint64_t;
using VST = vector<string>;

const int billion = 1'000'000'000;

struct CM_80x80
{
	vector<vector<int>> mat_;
	CM_80x80()
	{
		vector<int> cols_;
		for (int ix = 0; ix < 80; ++ix)
			cols_.emplace_back(0);
		for (int ix = 0; ix < 80; ++ix)
			mat_.emplace_back(cols_);
	}

	void show()
	{
		for (auto rx : mat_)
		{
			for (int cx : rx)
				cout << cx << ' ';
			cout << '\n';
		}
	}

	void show(int dim)
	{
		for (int rx = 0; rx < dim; ++rx)
		{
			for (int cx = 0; cx < dim; ++cx)
				cout << setw(5) << mat_[rx][cx] << ' ';
			cout << "\n\n";
		}
	}

	void show(int min_value, int med_value, char lt, char md, char gt)
	{
		for (auto rx : mat_)
		{
			for (int cx : rx)
				if (cx <= min_value)
					cout << lt << ' ';
				else if (cx <= med_value)
					cout << md << ' ';
				else
					cout << gt << ' ';
			cout << '\n';
		}
	}

	~CM_80x80()
	{
		for (auto vi : mat_)
			vi.clear();
		mat_.clear();
	}

	void assign(int ix, int rx, int cx) { mat_[rx][cx] = ix; }
	int cost(int rx, int cx) { return mat_[rx][cx]; }
};

///////////////////////////////////////////////////////////

const int diag_ub = 80;  // 5
const int diag_max = diag_ub - 1;

string path_direction_;

void accumulate_south_east(int diag, const CM_80x80& cost_matrix, CM_80x80& accum_matrix)
{
	int start = 0;
	int end = diag_max;

	if (diag < diag_ub)
	{
		end = diag;
	}
	else
	{
		start = diag - diag_max;
	}

	for (int rx = start; rx <= end; ++rx)
	{
		int cx = diag - rx;

		switch (rx)
		{
		case 0:
			switch (cx)
			{
			case 0:
				accum_matrix.mat_[rx][cx] = cost_matrix.mat_[rx][cx];
				break;
			default:
				accum_matrix.mat_[rx][cx] = cost_matrix.mat_[rx][cx] + accum_matrix.mat_[rx][cx - 1];
				break;
			}
			break;
		default:
			switch (cx)
			{
			case 0:
				accum_matrix.mat_[rx][cx] = cost_matrix.mat_[rx][cx] + accum_matrix.mat_[rx - 1][cx];
				break;
			default:
				accum_matrix.mat_[rx][cx] = cost_matrix.mat_[rx][cx] + min(accum_matrix.mat_[rx - 1][cx], accum_matrix.mat_[rx][cx - 1]);
				break;
			}
			break;
		}
	}
}

void check_north_west(int diag, CM_80x80& am /* <= CM_80x80& accumulate_cost_matrix */)
{
	int start = 0;
	int end = diag_max;

	if (diag < diag_ub)
	{
		end = diag;
	}
	else
	{
		start = diag - diag_max;
	}

	for (int rx = start; rx <= end; ++rx)
	{
		int cx = diag - rx;
		
		if (rx == 0 || cx == 0) continue;

		if (am.mat_[rx][cx] < am.mat_[rx - 1][cx - 1])
		{
			int subtract_row = am.mat_[rx - 1][cx - 1];
			int subtract_col = am.mat_[rx - 1][cx - 1];
			if (rx > 1 && subtract_row > am.mat_[rx - 2][cx])
				subtract_row = am.mat_[rx - 2][cx];
			if (cx > 1 && subtract_col > am.mat_[rx][cx - 2])
				subtract_col = am.mat_[rx][cx - 2];

			if (am.mat_[rx][cx] < am.mat_[rx - 1][cx] && am.mat_[rx][cx] < subtract_row)
			{
				am.mat_[rx - 1][cx] -= subtract_row;
				am.mat_[rx - 1][cx] += am.mat_[rx][cx];
			}
			else if (am.mat_[rx][cx] < am.mat_[rx][cx - 1] && am.mat_[rx][cx] < subtract_col)
			{
				am.mat_[rx][cx - 1] -= subtract_col;
				am.mat_[rx][cx - 1] += am.mat_[rx][cx];
			}
		}
	}
}

void path_sum_4_way1()
{
	VST vs;
	string path_dir;
	CM_80x80 cost_matrix;

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

	for (int rx = 0; rx < diag_ub; ++rx)
	{
		vector<string> cols;
		using tokenizer = boost::tokenizer<boost::char_separator<char>>;
		boost::char_separator<char> sep(",");
		tokenizer tokens(vs[rx], sep);
		for (tokenizer::iterator tok_iter = tokens.begin();
			tok_iter != tokens.end(); ++tok_iter)
			cols.emplace_back(*tok_iter);

		for (int jx = 0; jx < diag_ub; ++jx)
			cost_matrix.assign(strtol(cols[jx].c_str(), nullptr, 10), rx, jx);
	}

	///////////////////////////////////////////////////////////
	//// Large Matrix is Read and Parsed
	///////////////////////////////////////////////////////////


	CM_80x80 accum_matrix(cost_matrix);

	StopWatch s;

	for (int dg = 0; dg <= 2 * diag_max; ++dg)
	{
		accumulate_south_east(dg, cost_matrix, accum_matrix);
		check_north_west(dg, accum_matrix);
		accumulate_south_east(dg, cost_matrix, accum_matrix);
	}

	s.stop();

	cout << "Cost By Cell (79,79) = " << accum_matrix.mat_[diag_max][diag_max] << '\n';
}
