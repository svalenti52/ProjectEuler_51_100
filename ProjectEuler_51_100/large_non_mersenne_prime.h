#pragma once

using u64 = uint64_t;

void large_non_mersenne_prime()
{
	const u64 ten_digit_modulus = 10'000'000'000;

	u64 two_power = 1;

	for (int ix = 0; ix < 7'830'457; ++ix)
	{
		two_power *= 2;
		two_power %= ten_digit_modulus;
	}

	cout << two_power << '\n';

	u64 large_prime = 28'433 * two_power + 1;

	u64 ls_10_digits = large_prime % ten_digit_modulus;

	cout << "Least significant 10 digits of large prime = " << ls_10_digits << '\n';
}
