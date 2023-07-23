#pragma once

#include <vector>
#include <cstdint>
#include <numeric>
#include <iostream>

using namespace std;

void totient_max()
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

    double max_ratio = 0.0;
    uint64_t max_ix = 2;

    for (uint64_t ix = 2; ix < upper_bound; ++ix)
    {
        double tmp_ratio = static_cast<double>(ix) / static_cast<double>(totient[ix]);
        if (max_ratio < tmp_ratio)
        {
            max_ratio = tmp_ratio;
            max_ix = ix;
        }
    }

    cout << "Maximum Index to Totient Ratio at Index = " << max_ix << "   (" << max_ratio << ")\n";
}
