#pragma once

#include "combinatoric_selections.h"
#include "../../MonteCarlo/MonteCarlo/Combinatorics.h"
#include "../../../boost_1_79_0/boost/multiprecision/cpp_int.hpp"

void combinatoric_selections()
{
	using namespace boost::multiprecision;
	u64 count_gt_million = 0;

	for (cpp_int ix = 1; ix <= 100; ++ix)
		for (cpp_int jx = 1; jx <= ix; ++jx)
		{
			cpp_int count = number_combinations_without_repetition(ix, jx);
			if (count > 1'000'000)
				++count_gt_million;
		}

	std::cout << "Combinations greater than one million = " << count_gt_million << '\n';
}
