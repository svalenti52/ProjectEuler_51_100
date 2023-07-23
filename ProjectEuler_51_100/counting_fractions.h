#pragma once

#include <vector>
#include <cstdint>
#include <numeric>
#include <iostream>

using namespace std;

//using PII = pair<int, int>;
//
//struct NUM_DEN
//{
//	PII num_den;
//	friend bool operator < (const NUM_DEN& lhs, const NUM_DEN& rhs);
//};
//
//bool operator < (const NUM_DEN& lhs, const NUM_DEN& rhs)
//{
//	double lhsd = static_cast<double>(lhs.num_den.first / lhs.num_den.second);
//	double rhsd = static_cast<double>(rhs.num_den.first / rhs.num_den.second);
//	if (lhsd < rhsd) return true;
//	return false;
//}

void counting_fractions()
{
	const uint64_t upper_bound = 1'000'001;

	vector<uint64_t> totient(upper_bound, 0);
	iota(totient.begin(), totient.end(), 0);

	for (uint64_t ix = 2; ix < upper_bound; ++ix)
		if (totient[ix] == ix)
			for (uint64_t jx = ix; jx < upper_bound; jx += ix)
				totient[jx] = (ix - 1) * totient[jx] / ix;

	for (uint64_t ix = upper_bound - 50; ix < upper_bound; ++ix)
		cout << '(' << ix << ", " << totient[ix] << ")\n";

	uint64_t count_proper_fractions = 0;

	for (auto tot_it = totient.begin() + 2; tot_it != totient.end(); ++tot_it)
		count_proper_fractions += *tot_it;

	//for (int den = 2; den <= 1'000'000; ++den)
	//{
	//	if (gcd(den, 2) == 2)
	//		for (int num = 1; num < den; num += 2)
	//		{
	//			int hcd = gcd(num, den);
	//			if (hcd != 1) continue;
	//			++count_proper_fractions;
	//		}
	//	else
	//		for (int num = 1; num < den; ++num)
	//		{
	//			int hcd = gcd(num, den);
	//			if (hcd != 1) continue;
	//			++count_proper_fractions;
	//		}
	//	if (den % 10'000 == 0)
	//		cout << den << '\n';
	//}

	cout << "Number of Proper Fractions <= 1,000,000 = " << count_proper_fractions << '\n';
}
