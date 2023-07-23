#pragma once

#include <set>
#include "../repos/MonteCarlo/MonteCarlo/Primes.h"

void prime_power_triples()
{
	Primes_List pl(7200);
	Primes primes(pl, 7200);
	set<int> duplicate_check;

	int count_prime_triples = 0;

	for (int ix = 0; ix < primes.get_last_index(); ++ix)
		for (int jx = 0; jx < 369; ++jx)
			for (int kx = 0; kx < 85; ++kx)
			{
				double sum_triple = pow(primes.get_ith_prime(ix), 2) + pow(primes.get_ith_prime(jx), 3) + pow(primes.get_ith_prime(kx), 4);
				int sum_triple_int = static_cast<int>(sum_triple);

				if (sum_triple < 50'000'000)
				{
					++count_prime_triples;
					auto inserted = duplicate_check.insert(sum_triple_int);

					if (sum_triple_int == 145)
						cout << "Triple Prime Powers Sum = 145 at: "
						<< '(' << primes.get_ith_prime(ix) << ','
						<< primes.get_ith_prime(jx) << ','
						<< primes.get_ith_prime(kx) << ")\n";

					/*if (!inserted.second)
						cout << "Duplicate at " << sum_triple_int << ' ';*/
				}
			}

	cout << "Count of Prime Power Triples = " << count_prime_triples << "  Duplicate Check = " << duplicate_check.size() << '\n';
}
