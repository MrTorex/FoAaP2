
#pragma once
#include <iostream>

inline void checked_int_input(int& input);
inline void checked_unsigned_input(unsigned& input);
inline void clear_input();

inline void clear_input()
{
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

inline void checked_int_input(int& input)
{
	while (!(std::cin >> input))
	{
		clear_input();

		std::cout << "Enter valid input: ";
	}
}

inline void checked_unsigned_input(unsigned& input)
{
	int to_unsigned;

	checked_int_input(to_unsigned);

	if (to_unsigned < 0)
		to_unsigned *= -1;

	input = static_cast<unsigned>(to_unsigned);
}