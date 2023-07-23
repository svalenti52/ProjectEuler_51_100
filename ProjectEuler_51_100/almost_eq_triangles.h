#pragma once

#include <iostream>
#include <cmath>
#include <boost/multiprecision/cpp_dec_float.hpp>
#include "../repos/MonteCarlo/MonteCarlo/Chronology.h"

using u64 = uint64_t;

void almost_eq_triangles()
{
	u64 count_integral_triangles = 0;
	u64 sum_perimeters = 0;

	const u64 perimeter_limit = 1'000'000'000;
	const cpp_dec_float_100 one_half = static_cast<cpp_dec_float_100>(0.5);
	const cpp_dec_float_100 one_quarter = static_cast<cpp_dec_float_100>(0.25);

	StopWatch stopwatch;

	for (u64 perimeter = 7; perimeter <= perimeter_limit; perimeter += 3)
	{
		u64 short_side = perimeter / 3;
		u64 long_side = short_side + 1;

		if (long_side % 2 == 1) continue;

		cpp_dec_float_100 area = one_half * static_cast<cpp_dec_float_100>(long_side)
			* sqrt(static_cast<cpp_dec_float_100>(short_side) * static_cast<cpp_dec_float_100>(short_side)
				- one_quarter * static_cast<cpp_dec_float_100>(long_side) * static_cast<cpp_dec_float_100>(long_side));

		if (abs(area - floor(area + one_quarter)) < 1e-20)
		{
			cout << "perimeter = " << perimeter << '\n';
			cout << "area = " << std::setprecision(std::numeric_limits<cpp_dec_float_100>::max_digits10) << area << '\n';
			++count_integral_triangles;
			sum_perimeters += perimeter;
		}
	}

	for (u64 perimeter = 5; perimeter <= perimeter_limit; perimeter += 3)
	{
		u64 short_side = perimeter / 3;
		u64 long_side = short_side + 1;

		if (short_side % 2 == 1) continue;

		cpp_dec_float_100 area = one_half * static_cast<cpp_dec_float_100>(short_side)
			* sqrt(static_cast<cpp_dec_float_100>(long_side) * static_cast<cpp_dec_float_100>(long_side)
				- one_quarter * static_cast<cpp_dec_float_100>(short_side) * static_cast<cpp_dec_float_100>(short_side));

		if (abs(area - floor(area + one_quarter)) < 1e-20)
		{
			cout << "perimeter = " << perimeter << '\n';
			cout << "area = " << std::setprecision(std::numeric_limits<cpp_dec_float_100>::max_digits10) << area << '\n';
			++count_integral_triangles;
			sum_perimeters += perimeter;
		}
	}

	stopwatch.stop();

	cout << "Count of Integral areas = " << count_integral_triangles << '\n';
	cout << "Sum of Perimeters = " << sum_perimeters << '\n';
}
