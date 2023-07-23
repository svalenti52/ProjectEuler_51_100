#pragma once

#include <iostream>
#include "../repos/MonteCarlo/MonteCarlo/Primes.h"

void square_digit_chains()
{
	int count_89s = 0;

	for (int ix = 1; ix < 10'000'000; ++ix)
	{
		int number = ix;
		while (number != 1 && number != 89)
		{
			vector<int> digit;
			digits_from_number(number, digit);

			transform(begin(digit), end(digit), begin(digit), [](int i) {return i * i; });
			number = accumulate(begin(digit), end(digit), 0);
		}
		if (number == 89) ++count_89s;
	}
	cout << "Number of Convergences to 89 below 10,000,000 = " << count_89s << '\n';
}
