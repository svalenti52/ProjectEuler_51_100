#pragma once

#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include "../repos/MonteCarlo/MonteCarlo/Chronology.h"

using namespace std;
using s64 = int64_t;
using VS = vector<s64>;
using VVS = vector<vector<s64>>;

static const s64 target_sum = 110;

void show_extended_vector(VS& vs, s64 target_diff)
{
	for (s64 s : vs)
		cout << s << ' ';
	cout << target_diff << '\n';
}

void count_by_index(int index, VS& vs, s64& count)
{
	s64 target_diff = 0; // this is at vsize, i.e., outside the vector
	s64 vsize = size(vs);
	auto endvs_it = end(vs) - 1;

	if (index == vsize - 1) // last one in vector
	{
		target_diff = target_sum - accumulate(begin(vs), end(vs), 0LL);

		// show_extended_vector(vs, target_diff);

		while (*endvs_it <= target_diff)
		{
			++count;  //+= local_count;
			++(*endvs_it);
			--target_diff;
		}
	}
	else
	{
		do
		{
			count_by_index(index + 1, vs, count);
			++vs[index];
			for (auto it_right = begin(vs) + index + 1; it_right != end(vs); ++it_right)
				*it_right = vs[index];
			target_diff = target_sum - accumulate(vs.begin(), vs.end(), 0LL);
			//if (index == vsize / 3)
			//	show_extended_vector(vs, target_diff);

		} while (vs[index] <= target_diff);//vs[index] < (target_sum - sum_prior) / (vsize - index));
	}

}

void counting_summations()
{
	s64 count = 0;

	StopWatch s;

	for (int ix = 1; ix < target_sum; ++ix)
	{
		VS comb(ix, 1);
		count_by_index(0, comb, count);
	}

	s.stop();

	cout << count << '\n';
}

////////////////////////////////////////

// adapted from
// https://www.geeksforgeeks.org/find-all-combinations-that-adds-upto-given-number-2/
// takes a while to get the correct answer

/*    arr - array to store the combination
	index - next location in array
	num - given number
	reducedNum - reduced number */
void findCombinationsUtil(int arr[], int index,
	int num, int reducedNum, s64& cnt)
{
	// Base condition
	if (reducedNum < 0)
		return;

	// If combination is found, print it
	if (reducedNum == 0)
	{
		if (index == 15)
		{
			for (int i = 0; i < index; i++)
				cout << arr[i] << " ";
			cout << endl;
		}
		++cnt;
		return;
	}

	// Find the previous number stored in arr[]
	// It helps in maintaining increasing order
	int prev = (index == 0) ? 1 : arr[index - 1];

	// note loop starts from previous number
	// i.e. at array location index - 1
	for (int k = prev; k <= num; k++)
	{
		// next element of array is k
		arr[index] = k;

		// call recursively with reduced number
		findCombinationsUtil(arr, index + 1, num,
			reducedNum - k, cnt);
	}
}

/* Function to find out all combinations of
   positive numbers that add upto given number.
   It uses findCombinationsUtil() */
void findCombinations(int n)
{
	// array to store the combinations
	// It can contain max n elements
	int arr[100];

	s64 count = 0;

	//find all combinations
	findCombinationsUtil(arr, 0, n, n, count);

	cout << "For total number of combinations of numbers adding to 100 (sans 100) = " << count - 1 << '\n';
}

///////////////////////////////////////////////////////////

#include <stdio.h>

void combos() {

	int numbers[99], results[101] = { 1 };

	for (int i = 0; i < 99; i++) {
		numbers[i] = i + 1;
	}

	for (int i = 0; i < 99; i++) {
		for (int j = numbers[i]; j <= 100; j++) {
			results[j] += results[j - numbers[i]];
		}
	}

	printf("%d\n", results[100]);

	for (int ix = 0; ix < 101; ++ix)
		cout << results[ix] << ' ';
	cout << '\n';

}

void combos1() {

	int target_sum = 100;
	VI numbers(target_sum - 1, 0);
	iota(begin(numbers), end(numbers), 1);

	VI results(target_sum + 1, 0);
	results[0] = 1;

	for (int i : numbers)
	{
		for (int j = i; j <= target_sum; j++) {
			results[j] += results[j - i];
		}
	}

	printf("%d\n", results[target_sum]);

	for (int i : results)
		cout << i << ' ';
	cout << '\n';

}
