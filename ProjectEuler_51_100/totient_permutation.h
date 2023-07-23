#pragma once

#include <iostream>
#include <vector>
#include <numeric>
//#include <string>
#include "../repos/MonteCarlo/MonteCarlo/Primes.h"

using namespace std;

using u64 = uint64_t;

void totient_permutation()
{
    const u64 upper_bound = 10'000'000;

    vector<u64> totient(upper_bound, 0);
    iota(totient.begin(), totient.end(), 0);

    for (u64 ix = 2; ix < upper_bound; ++ix)
        if (totient[ix] == ix)
            for (u64 jx = ix; jx < upper_bound; jx += ix)
                totient[jx] = (ix - 1) * totient[jx] / ix;

    for (u64 ix = upper_bound - 50; ix < upper_bound; ++ix)
        cout << '(' << ix << ", " << totient[ix] << ")\n";

    double min_permutation_ratio = 1'000'000.0;
    u64 min_ix = 0;

    for (u64 nx = 2; nx < upper_bound; ++nx)
    {
        deque<u64> number_digits = number_to_digits_ms_to_ls(nx);
        deque<u64> totient_digits = number_to_digits_ms_to_ls(totient[nx]);

        if (is_permutation(number_digits.begin(), number_digits.end(), totient_digits.begin(), totient_digits.end()))
        {
            double tmp_ratio = static_cast<double>(nx) / static_cast<double>(totient[nx]);
            if (tmp_ratio < min_permutation_ratio)
            {
                min_permutation_ratio = tmp_ratio;
                min_ix = nx;
            }
        }
    }

    cout << "Min Permutation at Number = " << min_ix << "   (" << min_permutation_ratio << ")\n";
}
