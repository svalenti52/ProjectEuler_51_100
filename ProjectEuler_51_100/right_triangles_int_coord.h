#pragma once

#include <iostream>
#include <cmath>
#include <set>
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/polygon.hpp>

using namespace boost::geometry;

using XY = model::d2::point_xy<int>;

const XY origin(0, 0);

ostream& operator << (ostream& oss, const XY& p)
{
	oss << '(' << p.get<0>() << ", " << p.get<1>() << ')';
	return oss;
}

void right_triangles_int_coord()
{
	vector<XY> fst;
	vector<XY> snd;

	vector<pair<XY, XY>> triangle_points;

	for (int ix = 0; ix <= 50; ++ix)
		for (int jx = 0; jx <= 50; ++jx)
		{
			if (ix == 0 && jx == 0) continue;
			XY p1(ix, jx), p2(ix, jx);
			fst.emplace_back(p1);
			snd.emplace_back(p2);
		}

	int count = 0;
	for (auto p1 : fst)
		for (auto p2 : snd)
		{
			auto dist = distance(p1, p2);

			if (dist == 0) continue;

			auto d1 = distance(p1, origin);
			auto d2 = distance(p2, origin);
			auto d3 = distance(p1, p2);

			vector<double> triangle{ d1, d2, d3 };
			sort(triangle.begin(), triangle.end());


			if ((abs(triangle[2] * triangle[2] - (triangle[0] * triangle[0] + triangle[1] * triangle[1])) < 1e-10))
			{
				std::cout << ++count << ": " << origin << "  " << p1 << "  " << p2 << '\n';
				triangle_points.emplace_back(make_pair(p1, p2));
			}
		}

			
	std::cout << "Number of Triangles is: " << triangle_points.size() / 2 << std::endl;
}
