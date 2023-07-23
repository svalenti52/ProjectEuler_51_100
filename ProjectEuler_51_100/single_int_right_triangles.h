#pragma once

#include <vector>
#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;
using u64 = uint64_t;

void single_int_right_triangles()
{
	const u64 ub = 1'500'000; //1'500'000;
	vector<u64> L(ub+1, 0); // one extra since size of squares is ub+1 so index lines up with integers
	vector<u64> squares;

	for (u64 ix = 0; ix <= ub; ++ix)
		squares.emplace_back(ix * ix);

	for (u64 ix = 1; ix <= ub/2; ++ix)
	//for (u64 ix = 2; ix <= ub/2; ++ix)
	{
		for (u64 jx = 1; jx < ix; ++jx)
		//for (u64 jx = ix-1; jx < ix; jx+=2)
		{
			bool found = binary_search(squares.begin() + ix, squares.end(), squares[ix] + squares[jx]);
			if (found)
			{
				u64 hyp_sqr = squares[ix] + squares[jx];
				double hyp_d = std::sqrt(hyp_sqr);
				u64 length = static_cast<u64>(hyp_d) + ix + jx;
				if (length <= ub)
				{
					++L[length];
					//cout << length << " ";
				}
			}
		}
		if (ix % 1000 == 0)
			cout << "side size = " << ix << '\n';
	}

	//cout << '\n';
	//for (int i : L)
	//	cout << i << ' ';
	//cout << '\n';

	u64 count_single_rt = count(L.begin(), L.end(), 1LL);

	cout << "Count of Single Integral Right Triangles = " << count_single_rt << '\n';
}

void single_int_right_triangles1()
{
	const u64 ub = 1'500'000; //1'500'000;
	vector<u64> L(ub + 1, 0); // one extra since size of squares is ub+1 so index lines up with integers
	const u64 sqrt_ub = std::sqrt(ub);

	for (u64 m = 2; m < sqrt_ub; ++m)
	{
		u64 n = 1;
		if ((m & 1) == 1) n = 2;
		for (; n < m && n <=611; n+=2)
		{
			if (gcd(m, n) != 1) continue;
			for (u64 k = 1; k < ub; ++k)
			{
				u64 a = k * (m * m - n * n);
				u64 b = k * 2 * m * n;
				u64 c = k * (m * m + n * n);
				u64 length = a + b + c;
				if (length > ub) break;
				++L[length];
			}
		}
		if (m % 1000 == 0) cout << "m = " << m << '\n';
	}
	//for (int i : L)
	//	cout << i << ' ';
	//cout << '\n';

	u64 count_single_rt = count(L.begin(), L.end(), 1LL);

	cout << "Count of Single Integral Right Triangles = " << count_single_rt << '\n';
	cout << "At 1441440 = " << L[1441440] << '\n';
}
