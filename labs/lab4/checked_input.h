
#pragma once
#include <iostream>

template <typename T>
void checked_input(T& input)
{
    while (!(std::cin >> input))
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::cout << "Enter valid input: ";
    }
}

inline void clear_input()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}