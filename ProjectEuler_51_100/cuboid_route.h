#pragma once

double length_of_shortest_path(double x, double y, double z, double a)
{
	return sqrt(a * a + y * y) + sqrt((x - a) * (x - a) + z * z);
}

void cuboid_route()
{
	double x; // assume x >= y >= z
	double y;
	double z;

	int count_integral_paths = 2060; // starting at number of integral shortest paths up to 100 x 100 x 100 (inclusive)
	int current_cuboid_dim = 101; // therefore start at 101 x 1 x 1
	//int max_cuboid_dim = 2000;
	bool million_passed = false;

	while (!million_passed)
	{
		for (int ix = current_cuboid_dim; ix <= current_cuboid_dim && !million_passed; ++ix)
			for (int iy = 1; iy <= ix && !million_passed; ++iy)
				for (int iz = 1; iz <= iy && !million_passed; ++iz)
				{
					x = static_cast<int>(ix);
					y = static_cast<int>(iy);
					z = static_cast<int>(iz);

					double a = x * y / (y + z);

					double shortest_path = length_of_shortest_path(x, y, z, a);

					double shortest_path_plus_quarter = shortest_path + 0.25;

					double diff = abs(floor(shortest_path_plus_quarter) - shortest_path);

					if (diff < 1e-10)
						++count_integral_paths;

					if (count_integral_paths > 1'000'000)
						million_passed = true;
				}
		if (!million_passed)  // do NOT increment if > million detected
			++current_cuboid_dim; // only increment if have not detected > million yet
	}

	cout << "Minimum Cuboid with Integral Length Side (the longest side of the 3 dimensions)\n"
		<< "to support greater than a million integral shortest paths for contained Integral Cuboids = "
		<< current_cuboid_dim << '\n';
}
