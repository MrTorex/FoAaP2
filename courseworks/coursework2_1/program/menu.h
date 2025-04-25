
#pragma once
#include <iostream>
#include "production.h"
#include "checked_input.h"

inline void end_of_function()
{
	system("pause");
	system("cls");
}

inline void menu()
{
	int choice = 0;

	read_from_file();

	do
	{
		print_productions();
		choice = 0;

		std::cout << "\nChoose your option:\n1 - create new production\n2 - delete production\n3 - clear productions\n4 - sort productions by amount\n5 - sort productions by ID\n6 - find elements by amount\n7 - individual task\n-1 - exit: ";
		
		while ((choice < 1 || choice > 7) && choice != -1)
		{
			checked_int_input(choice);
			if ((choice < 1 || choice > 7) && choice != -1)
				std::cout << "Enter valid input: ";
		}

		switch (choice)
		{
		case 1:
			clear_input();
			create_new_production();
			end_of_function();
			break;
		case 2:
			clear_input();
			delete_production();
			end_of_function();
			break;
		case 3:
			clear();
			end_of_function();
			break;
		case 4:
			sort_by_amount();
			end_of_function();
			break;
		case 5:
			sort_by_id();
			end_of_function();
			break;
		case 6:
			find();
			end_of_function();
			break;
		case 7:
			individual_task();
			end_of_function();
			break;
		default:
			std::cout << "Have a nice day!";
			break;
		}

		write_to_file();
	} while (choice != -1);
}