#pragma once

#include <set>
#include <iostream>
#include <functional>
#include <tuple>
#include <string>

using namespace std;

using pii = pair<int, int>;
using vpii = vector<pii>;

void print_set(set<int>& s)
{
	for (int i : s)
		cout << i << " ";
	cout << '\n';
}

bool within_range_xxxx(int ix, function<int(int)> f)
{
	int val = f(ix);
	if (val >= 1'000 && val < 10'000)
		return true;
	return false;
}

void search_for(pii& fixed, vpii& range_to_search, bool print, string& name, vpii::iterator& last_it)
{
	last_it = find_if(range_to_search.begin(), range_to_search.end(), [&fixed](pii& s) {return fixed.second == s.first; });
	if (last_it != range_to_search.end() && print)
		cout << name << " upper = " << last_it->first << "  lower = " << last_it->second << '\n';
	//else if (print)
	//	cout << "first end\n";
}

void search_for_next_(pii& fixed, vpii& range_to_search, bool print, string& name, vpii::iterator& last_it)
{
	++last_it;
	last_it = find_if(last_it, range_to_search.end(), [&fixed](pii& s) {return fixed.second == s.first; });
	if (last_it != range_to_search.end() && print)
	{
		cout << name << " next upper = " << last_it->first << "  next lower = " << last_it->second;
		cout << "   (" << fixed.first << ", " << fixed.second << ")\n";
	}
	//else if (print)
	//	cout << "next end\n";
}

void cyclical_figurate()
{
	set<int> triangle; auto tri_calc = [](int n) {return n * (n + 1) / 2; };
	set<int> square; auto sqr_calc = [](int n) {return n * n; };
	set<int> pentagonal; auto pen_calc = [](int n) {return n * (3 * n - 1) / 2; };
	set<int> hexagonal; auto hex_calc = [](int n) {return n * (2 * n - 1); };
	set<int> heptagonal; auto hep_calc = [](int n) {return n * (5 * n - 3) / 2; };
	set<int> octagonal; auto oct_calc = [](int n) {return n * (3 * n - 2); };

	for (int ix = 1; ix < 10000; ++ix)
	{
		if (tri_calc(ix) >= 10'000) break;
		if (within_range_xxxx(ix, tri_calc))
			triangle.insert(tri_calc(ix));
		//============================
		if (within_range_xxxx(ix, sqr_calc))
			square.insert(sqr_calc(ix));
		//============================
		if (within_range_xxxx(ix, pen_calc))
			pentagonal.insert(pen_calc(ix));
		//============================
		if (within_range_xxxx(ix, hex_calc))
			hexagonal.insert(hex_calc(ix));
		//============================
		if (within_range_xxxx(ix, hep_calc))
			heptagonal.insert(hep_calc(ix));
		//============================
		if (within_range_xxxx(ix, oct_calc))
			octagonal.insert(oct_calc(ix));
	}
	//print_set(triangle);
	//print_set(square);
	//print_set(pentagonal);
	//print_set(hexagonal);
	//print_set(heptagonal);
	//print_set(octagonal);

	vector<string> shapes = { "triangle", "square", "pentagonal", "hexagonal", "heptagonal", "octagonal"};
	vector<string> shape_names = { string("Square"), string("Pentagonal"), string("Hexagonal"), string("Heptagonal"), string("Octagonal") };
	vector<vpii::iterator> iterators;
	vector<vpii> ranges_;

	vpii tri_v;
	vpii sqr_v;
	vpii pen_v;
	vpii hex_v;
	vpii hep_v;
	vpii oct_v;


	for (int v : triangle)
		tri_v.emplace_back(make_pair(v/100,v%100));
	for (int v : square)
		sqr_v.emplace_back(make_pair(v / 100, v % 100));
	for (int v : pentagonal)
		pen_v.emplace_back(make_pair(v / 100, v % 100));
	for (int v : hexagonal)
		hex_v.emplace_back(make_pair(v / 100, v % 100));
	for (int v : heptagonal)
		hep_v.emplace_back(make_pair(v / 100, v % 100));
	for (int v : octagonal)
		oct_v.emplace_back(make_pair(v / 100, v % 100));

	ranges_.emplace_back(sqr_v);
	ranges_.emplace_back(pen_v);
	ranges_.emplace_back(hex_v);
	ranges_.emplace_back(hep_v);
	ranges_.emplace_back(oct_v);

	iterators.emplace_back(ranges_[0].begin());
	iterators.emplace_back(ranges_[1].begin());
	iterators.emplace_back(ranges_[2].begin());
	iterators.emplace_back(ranges_[3].begin());
	iterators.emplace_back(ranges_[4].begin());

	//for (pii& p : ranges_[3])
	//	cout << "upper = " << p.first << "  lower = " << p.second << '\n';

	vector<int> indexes = { 0, 1, 2, 3, 4 };
	vector<int> indexes_solution;
	vector<int> raw_solution_upper;
	vector<int> raw_solution_lower;

	for (pii tri : tri_v)
	{
		do {
			search_for(tri, ranges_[indexes[0]], false, shape_names[indexes[0]], iterators[indexes[0]]);
			while (iterators[indexes[0]] != ranges_[indexes[0]].end())
			{
				search_for(*iterators[indexes[0]], ranges_[indexes[1]], false, shape_names[indexes[1]], iterators[indexes[1]]);
				while (iterators[indexes[1]] != ranges_[indexes[1]].end())
				{
					search_for(*iterators[indexes[1]], ranges_[indexes[2]], false, shape_names[indexes[2]], iterators[indexes[2]]);
					while (iterators[indexes[2]] != ranges_[indexes[2]].end())
					{
						search_for(*iterators[indexes[2]], ranges_[indexes[3]], false, shape_names[indexes[3]], iterators[indexes[3]]);
						while (iterators[indexes[3]] != ranges_[indexes[3]].end())
						{
							search_for(*(iterators[indexes[3]]), ranges_[indexes[4]], true, shape_names[indexes[4]], iterators[indexes[4]]);
							while (iterators[indexes[4]] != ranges_[indexes[4]].end())
							{
								if (iterators[indexes[4]]->second == tri.first)
								{
									cout << "CYCLE COMPLETE!!\n";
									raw_solution_upper.emplace_back(tri.first);
									raw_solution_lower.emplace_back(tri.second);
									raw_solution_upper.emplace_back(iterators[indexes[0]]->first);
									raw_solution_lower.emplace_back(iterators[indexes[0]]->second);
									raw_solution_upper.emplace_back(iterators[indexes[1]]->first);
									raw_solution_lower.emplace_back(iterators[indexes[1]]->second);
									raw_solution_upper.emplace_back(iterators[indexes[2]]->first);
									raw_solution_lower.emplace_back(iterators[indexes[2]]->second);
									raw_solution_upper.emplace_back(iterators[indexes[3]]->first);
									raw_solution_lower.emplace_back(iterators[indexes[3]]->second);
									raw_solution_upper.emplace_back(iterators[indexes[4]]->first);
									raw_solution_lower.emplace_back(iterators[indexes[4]]->second);
									for (int i : indexes)
										indexes_solution.emplace_back(i);
								}
								else
									cout << "CYCLE NOT COMPLETE\n";
								search_for_next_(*(iterators[indexes[3]]), ranges_[indexes[4]], true, shape_names[indexes[4]], iterators[indexes[4]]);
							}
							search_for_next_(*iterators[indexes[2]], ranges_[indexes[3]], false, shape_names[indexes[3]], iterators[indexes[3]]);
						}
						search_for_next_(*iterators[indexes[1]], ranges_[indexes[2]], false, shape_names[indexes[2]], iterators[indexes[2]]);
					}
					search_for_next_(*iterators[indexes[0]], ranges_[indexes[1]], false , shape_names[indexes[1]], iterators[indexes[1]]);
				}
				search_for_next_(tri, ranges_[indexes[0]], false, shape_names[indexes[0]], iterators[indexes[0]]);
			}
		} while (next_permutation(indexes.begin(), indexes.end()));
	}

	vector<int> finished;
	for (int ix = 0; ix < raw_solution_upper.size(); ++ix)
	{
		finished.emplace_back(raw_solution_upper[ix]*100 + raw_solution_lower[ix]);
	}

	cout << "\n\n6-Cycle of 4-Digit Numbers\n";
	for (int f : finished)
		cout << f << " ";
	cout << '\n';

	cout << "\nOrder of Numbers (Triangle Numbers Always First, remaining 5 positions permuted)\n";
	cout << "Triangle ";
	for (int i : indexes_solution)
		cout << shape_names[i] << " ";
	cout << '\n';

	int sum = accumulate(finished.begin(), finished.end(), 0);
	cout << "\nSum of 6-Cycle = " << sum << '\n';
}
