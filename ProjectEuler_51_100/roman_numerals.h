#pragma once

#include "../repos/Utilities/Utilities/comma_separated.h"

using namespace std;

void roman_numerals()
{
	VS_ roman;
	string fname("roman.txt");
	
	read_string_per_line(fname, roman);

	int saved_chars = 0;

	for (auto s : roman)
	{
		auto viiii = s.find("VIIII");
		if (viiii != string::npos)
		{
			s.replace(viiii, 5, "IX");
			saved_chars += 3;
		}
		else
		{
			auto iiii = s.find("IIII");
			if (iiii != string::npos)
			{
				s.replace(iiii, 4, "IV");
				saved_chars += 2;
			}
		}
		
		auto lxxxx = s.find("LXXXX");
		if (lxxxx != string::npos)
		{
			s.replace(lxxxx, 5, "XC");
			saved_chars += 3;
		}
		else
		{
			auto xxxx = s.find("XXXX");
			if (xxxx != string::npos)
			{
				s.replace(xxxx, 4, "XL");
				saved_chars += 2;
			}
		}

		auto dcccc = s.find("DCCCC");
		if (dcccc != string::npos)
		{
			s.replace(dcccc, 5, "CM");
			saved_chars += 3;
		}
		else
		{
			auto cccc = s.find("CCCC");
			if (cccc != string::npos)
			{
				s.replace(cccc, 4, "CD");
				saved_chars += 2;
			}
		}
	}

	cout << "Saved characters = " << saved_chars << '\n';
}
