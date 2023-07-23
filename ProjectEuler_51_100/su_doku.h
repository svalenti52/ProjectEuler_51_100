#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <deque>
#include <string>
#include <algorithm>
#include <Eigen/Dense>
#include <array>
#include <tuple>
#include <cmath>
#include "../repos/MonteCarlo/MonteCarlo/Primes.h"


using namespace std;
using Eigen::MatrixXi;

using VST = vector<string>;
using VVSI = vector<vector<set<int>>>;
using SI = set<int>;
using VM = vector<MatrixXi>;

typedef set<int>::iterator it_set;
typedef set<int> set_t;

class square {
	int _row;
	int _col;
	int _box;
	bool _solved;  // solved when value.size() == 1
public:
	square() {}

	set<int> _value;

	void init(int row, int col, int box) {
		_row = row;
		_col = col;
		_box = box;
		for (int ix = 1; ix <= 9; ++ix) _value.insert(ix);
		_solved = false;
	}

	~square() {}

	void operator = (square& rhs) {
		_row = rhs._row;
		_col = rhs._col;
		_box = rhs._box;
		_solved = rhs._solved;
		_value.clear();
		for (it_set ix = rhs._value.begin();
			ix != rhs._value.end();
			++ix)
			_value.insert(*ix);
	}

	void operator *= (int value) {
		_value.clear();
		_value.insert(value);
		_solved = true;
	}

	void operator -= (int value) {
		_value.erase(value);
		if (_value.size() == 1) _solved = true;
		else _solved = false;
	}

	void operator += (int value) {
		_value.insert(value);
		if (_value.size() == 1) _solved = true;
		else _solved = false;
	}

	bool operator == (int value) {
		for (it_set ix = _value.begin();
			ix != _value.end();
			++ix)
			if (*ix == value) return true;
		return false;
	}

	void show_pos() {
		cout << _row << ":"
			<< _col << "-"
			<< _box;
	}

	void show_vals() {
		show_pos();
		cout << " = ";
		for (it_set ix = _value.begin();
			ix != _value.end();
			++ix)
			cout << " " << *ix;
	}

	bool is_solved() {
		return _solved;
	}

	int row() {
		return _row;
	}

	int col() {
		return _col;
	}

	int box() {
		return _box;
	}

	int val() {
		if (_solved)
			return *_value.begin();
		return 0;
	}

	int val1() {
		return *_value.begin();
	}

	int val2() {
		it_set ix = _value.begin();
		++ix;
		return *ix;
	}

	int val3() {
		it_set ix = _value.begin();
		++ix, ++ix;
		return *ix;
	}

	bool is_double() {
		if (_value.size() == 2) return true;
		return false;
	}

	bool is_triple() {
		if (_value.size() == 3) return true;
		return false;
	}
};

typedef std::array<square, 81> as_t;

//

void
init_board(as_t& b) {

	for (int ix = 0; ix < 81; ++ix)
		b[ix].init((ix / 9) + 1, (ix % 9) + 1, ((ix / 9) / 3) * 3 + (ix % 9) / 3 + 1);
}

void
disp_board_row(as_t& b) {
	for (int ix = 0; ix < 81; ++ix) {
		b[ix].show_vals();
		cout << endl;
		if ((ix + 1) % 9 == 0) cout << endl;
	}
}

void
disp_board_col(as_t& b) {
	for (int ix = 1; ix <= 9; ++ix) {
		for (int jx = 0; jx < 81; ++jx)
			if (b[jx].col() == ix) {
				b[jx].show_vals();
				cout << endl;
			}
		cout << endl;
	}
}

void
disp_board_box(as_t& b) {
	for (int ix = 1; ix <= 9; ++ix) {
		for (int jx = 0; jx < 81; ++jx)
			if (b[jx].box() == ix) {
				b[jx].show_vals();
				cout << endl;
			}
		cout << endl;
	}
}

int
count_doubles(as_t& b) {
	int cnt = 0;

	for (int ix = 0; ix < 81; ++ix)
		if (b[ix].is_double())
			++cnt;

	return cnt;
}

int
count_triples(as_t& b) {
	int cnt = 0;

	for (int ix = 0; ix < 81; ++ix)
		if (b[ix].is_triple())
			++cnt;

	return cnt;
}

void xlat_board_to_matrix(as_t& b, MatrixXi& board)
{
	for (int rx = 0; rx < 9; ++rx)
		for (int cx = 0; cx < 9; ++cx)
			board(rx, cx) = b[9 * rx + cx].val();
}

void
set_init_board(as_t& b, MatrixXi& board) {

	for (int rx = 0; rx < 9; ++rx)
		for (int cx = 0; cx < 9; ++cx)
			if (board(rx, cx) != 0)
				b[9 * rx + cx] *= board(rx, cx);

	//for (int ix = 0; ix < 81; ++ix)
	//	switch (ix) {
	//	case 0:
	//		b[ix] *= 2;
	//		break;
	//	case 4:
	//		b[ix] *= 8;
	//		break;
	//	case 6:
	//		b[ix] *= 3;
	//		break;
	//	case 10:
	//		b[ix] *= 6;
	//		break;
	//	case 13:
	//		b[ix] *= 7;
	//		break;
	//	case 16:
	//		b[ix] *= 8;
	//		break;
	//	case 17:
	//		b[ix] *= 4;
	//		break;
	//	case 19:
	//		b[ix] *= 3;
	//		break;
	//	case 21:
	//		b[ix] *= 5;
	//		break;
	//	case 24:
	//		b[ix] *= 2;
	//		break;
	//	case 26:
	//		b[ix] *= 9;
	//		break;
	//	case 30:
	//		b[ix] *= 1;
	//		break;
	//	case 32:
	//		b[ix] *= 5;
	//		break;
	//	case 33:
	//		b[ix] *= 4;
	//		break;
	//	case 35:
	//		b[ix] *= 8;
	//		break;
	//	case 45:
	//		b[ix] *= 4;
	//		break;
	//	case 47:
	//		b[ix] *= 2;
	//		break;
	//	case 48:
	//		b[ix] *= 7;
	//		break;
	//	case 50:
	//		b[ix] *= 6;
	//		break;
	//	case 54:
	//		b[ix] *= 3;
	//		break;
	//	case 56:
	//		b[ix] *= 1;
	//		break;
	//	case 59:
	//		b[ix] *= 7;
	//		break;
	//	case 61:
	//		b[ix] *= 4;
	//		break;
	//	case 63:
	//		b[ix] *= 7;
	//		break;
	//	case 64:
	//		b[ix] *= 2;
	//		break;
	//	case 67:
	//		b[ix] *= 4;
	//		break;
	//	case 70:
	//		b[ix] *= 6;
	//		break;
	//	case 74:
	//		b[ix] *= 4;
	//		break;
	//	case 76:
	//		b[ix] *= 1;
	//		break;
	//	case 80:
	//		b[ix] *= 3;
	//		break;



			/*			case 17:
							b[ix] *= 3;
							break;
						case 20:
							b[ix] *= 6;
							break;
						case 25:
							b[ix] *= 2;
							break;
						case 26:
							b[ix] *= 1;
							break;
						case 27:
							b[ix] *= 6;
							break;
						case 35:
							b[ix] *= 4;
							break;
						case 39:
							b[ix] *= 5;
							break;
						case 40:
							b[ix] *= 7;
							break;
						case 41:
							b[ix] *= 9;
							break;
						case 45:
							b[ix] *= 3;
							break;
						case 53:
							b[ix] *= 9;
							break;
						case 54:
							b[ix] *= 1;
							break;
						case 55:
							b[ix] *= 3;
							break;
						case 60:
							b[ix] *= 7;
							break;
						case 63:
							b[ix] *= 7;
							break;
						case 66:
							b[ix] *= 3;
							break;
						case 74:
							b[ix] *= 5;
							break;
						case 77:
							b[ix] *= 2;
							break;
						case 78:
							b[ix] *= 9;
							break;*/
							/*			case 69:
											b[ix] *= 2;
											break;
										case 72:
											b[ix] *= 6;
											break;
										case 73:
											b[ix] *= 2;
											break;

										case 24:
											b[ix] *= 4;
											break;
							/*			case 1:
											b[ix] *= 3;
											break;
										case 73:
											b[ix] *= 8;
											break;
										case 79:
											b[ix] *= 5;
											break; */
		//default:
		//	break;
		//}
}

//

int
count_solved(as_t& b) {
	int cnt = 0;
	for (int ix = 0; ix < 81; ++ix)
		if (b[ix].is_solved()) ++cnt;
	return cnt;
}

void
reduce_board(as_t& b) {
	for (int ix = 0; ix < 81; ++ix)
		for (int jx = 0; jx < 81; ++jx)
			if ((ix != jx) && !b[ix].is_solved() &&
				((b[ix].row() == b[jx].row()) ||
					(b[ix].col() == b[jx].col()) ||
					(b[ix].box() == b[jx].box())))

				b[ix] -= b[jx].val();
}

void
unique_per_row(as_t& b) {
	for (int ix = 0; ix < 81; ++ix) {
		square temp = b[ix];
		for (int jx = 0; jx < 81; ++jx) {
			if ((ix != jx) && b[ix].row() == b[jx].row()) {
				for (it_set kx = b[jx]._value.begin();
					kx != b[jx]._value.end();
					++kx)

					b[ix] -= *kx;
			}
			if (b[ix]._value.size() == 0) break;
		}
		if (b[ix]._value.size() == 0) b[ix] = temp;
	}
}

void
unique_per_col(as_t& b) {
	for (int ix = 0; ix < 81; ++ix) {
		square temp = b[ix];
		for (int jx = 0; jx < 81; ++jx) {
			if ((ix != jx) && b[ix].col() == b[jx].col()) {
				for (it_set kx = b[jx]._value.begin();
					kx != b[jx]._value.end();
					++kx)

					b[ix] -= *kx;
			}
			if (b[ix]._value.size() == 0) break;
		}
		if (b[ix]._value.size() == 0) b[ix] = temp;
	}
}

void
unique_per_box(as_t& b) {
	for (int ix = 0; ix < 81; ++ix) {
		square temp = b[ix];
		for (int jx = 0; jx < 81; ++jx) {
			if ((ix != jx) && b[ix].box() == b[jx].box()) {
				for (it_set kx = b[jx]._value.begin();
					kx != b[jx]._value.end();
					++kx)

					b[ix] -= *kx;
			}
			if (b[ix]._value.size() == 0) break;
		}
		if (b[ix]._value.size() == 0) b[ix] = temp;
	}
}

void
unique_test(as_t& b) {
	unique_per_row(b);
	unique_per_col(b);
	unique_per_box(b);
}

//

bool
verify_board(as_t& b) {
	if (count_solved(b) != 81) return false;
	else {
		set_t temp;
		for (int ix = 0; ix < 81; ++ix)
			temp.insert((ix / 9 * 10) + b[ix].val1());
		if (temp.size() != 81) {
			//cout << " sz=" << temp.size() << " ";
			return false;
		}
	}
	return true;
}

//

void
print_result(as_t& b) {
	cout << "doubles=" << count_doubles(b) <<
		"   triples=" << count_triples(b) <<
		"   solved=" << count_solved(b);
	if (verify_board(b))
		cout << "  TRUE" << endl;
	else
		cout << "  FALSE" << endl;
}


void
try_doubles(as_t& b) {
	for (int ix = 0; ix < 81; ++ix) {
		if (!b[ix].is_double()) continue;
		as_t temp = b;
		int first_val = b[ix].val1();
		int second_val = b[ix].val2();
		b[ix] -= second_val;
		for (int jx = 0; jx < 10; ++jx) {
			reduce_board(b);
			unique_test(b);
		}
		/*cout << first_val << " row=" <<
			ix / 9 + 1 << " col=" << ix % 9 + 1 << endl;
		print_result(b);*/
		if (verify_board(b) == true) return;
		b = temp;
		b[ix] -= first_val;
		b[ix] += second_val;
		for (int jx = 0; jx < 10; ++jx) {
			reduce_board(b);
			unique_test(b);
		}
		/*cout << second_val << " row=" <<
			ix / 9 + 1 << " col=" << ix % 9 + 1 << endl;
		print_result(b);*/
		if (verify_board(b) == true) return;
		b = temp;
		//cout << "--------" << endl;
	}
}


void
try_triples(as_t& b) {
	for (int ix = 0; ix < 81; ++ix) {
		if (!b[ix].is_triple()) continue;
		as_t temp = b;
		int first_val = b[ix].val1();
		int second_val = b[ix].val2();
		int third_val = b[ix].val3();
		b[ix] -= second_val;
		b[ix] -= third_val;
		for (int jx = 0; jx < 20; ++jx) {
			reduce_board(b);
			unique_test(b);
		}
		/*cout << first_val << " row=" <<
			ix / 9 + 1 << " col=" << ix % 9 + 1 << endl;
		print_result(b);*/
		if (verify_board(b) == true) return;
		b = temp;
		b[ix] -= first_val;
		b[ix] -= third_val;
		for (int jx = 0; jx < 20; ++jx) {
			reduce_board(b);
			unique_test(b);
		}
		/*cout << second_val << " row=" <<
			ix / 9 + 1 << " col=" << ix % 9 + 1 << endl;
		print_result(b);*/
		if (verify_board(b) == true) return;
		b = temp;
		b[ix] -= first_val;
		b[ix] -= second_val;
		for (int jx = 0; jx < 20; ++jx) {
			reduce_board(b);
			unique_test(b);
		}
		if (verify_board(b) == true) return;
		b = temp;
		//cout << "--------" << endl;
	}
}
//

int upper_left_hand_corner(MatrixXi& bd)
{
	deque<int> digits;
	digits.push_back(bd(0, 0));
	digits.push_back(bd(0, 1));
	digits.push_back(bd(0, 2));

	int number = digits_to_number_ms_to_ls(digits);
	return number;
}

//

//

void su_doku()
{
	vector<string> vs;
	MatrixXi sudoko_bd(9, 9);
	VI upper_lhc;
	ifstream in("sudoku.txt");
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

	int row = 0;
	for (auto str : vs)
	{
		if (str.size() != 9)
		{
			row = 0;
			continue;
		}
		for (int col = 0; col < 9; ++col)
		{
			char digit_c = str[col];
			string digit_s{ digit_c };
			sudoko_bd(row, col) = strtol(digit_s.c_str(), nullptr, 10);
		}
		++row;

		if (row == 9)
		{

			as_t board;

			init_board(board);

			set_init_board(board, sudoko_bd);

			//disp_board_row(board);

			//print_result(board);  cout << endl;

			for (int ix = 0; ix < 100; ++ix) {
				reduce_board(board);
				unique_test(board);
			}

			try_doubles(board);

			try_triples(board);

			//print_result(board);  cout << endl;

			//disp_board_row(board);

			xlat_board_to_matrix(board, sudoko_bd);

			int number = upper_left_hand_corner(sudoko_bd);

			upper_lhc.emplace_back(number);

			row = 0;
		}
	}

	int index = 1;
	for (int x : upper_lhc)
	{
		cout << index << ". " << x << '\n';
		++index;
	}

	int sum = accumulate(upper_lhc.begin(), upper_lhc.end(), 0);

	cout << "Sum of Upper Left Hand as 3-digit Number = " << sum << '\n';
	cout << sudoko_bd << '\n';
}
