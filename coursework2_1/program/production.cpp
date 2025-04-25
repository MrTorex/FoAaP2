
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include "checked_input.h"
#include "production.h"

std::vector<production> productions;

production::production(const std::string& name, const unsigned amount, const unsigned workshop_number, const unsigned id, const std::string& material)
{
	this->name = name;
	this->amount = amount;
	this->workshop_number = workshop_number;
	this->id = id;
	this->material = material;
}

bool is_empty()
{
	return static_cast<int>(productions.size()) == 0;
}

void create_new_production()
{
	std::string name, material;

	unsigned amount, workshop_number;

	std::cout << "Enter name of new product: ";
	std::getline(std::cin, name, '\n');

	std::cout << "Enter amount of new product: ";
	checked_unsigned_input(amount);

	std::cout << "Enter workshop number of new product: ";
	checked_unsigned_input(workshop_number);

	const unsigned id = static_cast<unsigned>(productions.size()) + 1;

	clear_input();

	std::cout << "Enter material of new product: ";
	std::getline(std::cin, material, '\n');

	productions.emplace_back(name, amount, workshop_number, id, material);

	clear_input();
}

void set_new_ids(const unsigned id_to_delete)
{
	for (production& production : productions)
		if (production.id > id_to_delete)
			production.id--;
}

void print_productions()
{
	std::cout << "--------------------------------ProductsDatabase v. 0.0.1--------------------------------\n\n";

	if (is_empty())
	{
		std::cout << "Your products list is empty!\n";
		return;
	}

	std::cout << "ID" << std::setw(15) << "Name" << std::setw(18) << "Amount" << std::setw(25) << "Workshop number" << std::setw(25) << "Material" << '\n';

	for (const production& production : productions)
		std::cout << production.id << std::setw(15) << production.name << std::setw(18) << production.amount << std::setw(25) << production.workshop_number << std::setw(25) << production.material << '\n';
}

void write_to_file()
{
	std::fstream file;

	file.open("database.txt", std::ios::out);

	file << productions.size() << '\n';

	for (auto it = productions.cbegin(); it != productions.cend(); ++it)
		file << it->id << '*' << it->name << '*' << it->amount << '*' << it->workshop_number << '*' << it->material << '\n';

	file.close();
}

void read_from_file()
{
	std::string buffer;

	std::fstream file;

	file.open("database.txt", std::ios::in);

	std::getline(file, buffer);

	const int productions_size = std::stoi(buffer);

	for (int i = 0; i < productions_size; i++)
	{
		std::getline(file, buffer, '*');
		unsigned id = std::stoi(buffer);

		std::getline(file, buffer, '*');
		std::string name = buffer;

		std::getline(file, buffer, '*');
		unsigned amount = std::stoi(buffer);

		std::getline(file, buffer, '*');
		unsigned workshop_number = std::stoi(buffer);

		std::getline(file, buffer, '\n');
		std::string material = buffer;

		productions.emplace_back(name, amount, workshop_number, id, material);
	}

	file.open("database.txt", std::ios::in);
}

void clear()
{
	if (is_empty())
	{
		std::cout << "Your products list is empty!\n";
		return;
	}

	productions.clear();
	std::cout << "Successfully cleared!\n";
}

void delete_production()
{
	if (is_empty())
	{
		std::cout << "Your products list is empty!\n";
		return;
	}

	unsigned id_to_delete;

	std::cout << "Enter ID of production to delete: ";
	checked_unsigned_input(id_to_delete);

	if (id_to_delete > static_cast<unsigned>(productions.size()))
	{
		std::cout << "There's no element with this ID!\n";
		return;
	}

	for (auto it = productions.cbegin(); it != productions.cend(); ++it)
	{
		if (it->id == id_to_delete)
		{
			productions.erase(it);
			set_new_ids(id_to_delete);
			break;
		}
	}
}

void bubble_sort_by_amount(const unsigned type)
{
	for (int i = 0; i < static_cast<int>(productions.size()); ++i)
	{
		for (int j = 0; j < static_cast<int>(productions.size()) - i - 1; j++)
		{
			if (type == 1)
			{
				if (productions[j].amount > productions[j + 1].amount)
				{
					const production temp = productions[j];
					productions[j] = productions[j + 1];
					productions[j + 1] = temp;
				}
			}
			else
			{
				if (productions[j].amount < productions[j + 1].amount)
				{
					const production temp = productions[j];
					productions[j] = productions[j + 1];
					productions[j + 1] = temp;
				}
			}
		}
	}
}

void selection_sort_by_amount(const unsigned type)
{
	for (int i = 0; i < static_cast<int>(productions.size()) - 1; i++)
	{
		int m = i;

		for (int j = i + 1; j < static_cast<int>(productions.size()); j++)
		{
			if (type == 1)
			{
				if (productions[j].amount < productions[m].amount) m = j;
			}

			else
			{
				if (productions[j].amount > productions[m].amount) m = j;
			}
		}

		const production temp = productions[m];
		productions[m] = productions[i];
		productions[i] = temp;
	}
}

void quick_sort_by_amount(const unsigned low, const unsigned high, const unsigned type)
{
	if (low < high)
	{
		const unsigned x = productions[(low + high) / 2].amount;

		unsigned i = low, j = high;

		while (i <= j)
		{
			if (type == 1)
			{
				while (productions[i].amount < x) i++;
				while (productions[j].amount > x) j--;
			}

			else
			{
				while (productions[i].amount > x) i++;
				while (productions[j].amount < x) j--;
			}

			if (i <= j)
			{
				const production temp = productions[i];
				productions[i] = productions[j];
				productions[j] = temp;
				i++;
				j--;
			}
		}

		if (low < j) quick_sort_by_amount(low, j, type);
		if (i < high) quick_sort_by_amount(i, high, type);
	}
}

void sort_by_amount()
{
	if (is_empty())
	{
		std::cout << "Your products list is empty!\n";
		return;
	}

	unsigned sort_parameter1 = 0, sort_parameter2 = 0;

	std::cout << "How to sort a list?\n1 - Ascending\n2 - Descending: ";
	while (sort_parameter1 != 1 && sort_parameter1 != 2)
	{
		checked_unsigned_input(sort_parameter1);
		if (sort_parameter1 != 1 && sort_parameter1 != 2)
			std::cout << "Enter valid input: ";
	}

	std::cout << "How to sort a list?\n1 - SelectionSort\n2 - QuickSort\n3 - BubbleSort: ";
	while (sort_parameter2 < 1 || sort_parameter2 > 3)
	{
		checked_unsigned_input(sort_parameter2);
		if (sort_parameter2 < 1 || sort_parameter2 > 3)
			std::cout << "Enter valid input: ";
	}

	switch(sort_parameter2)
	{
	case 1:
		selection_sort_by_amount(sort_parameter1);
		break;
	case 2:
		quick_sort_by_amount(0, static_cast<unsigned>(productions.size()) - 1, sort_parameter1);
		break;
	case 3:
		bubble_sort_by_amount(sort_parameter1);
		break;
	default:
		break;
	}
}

void bubble_sort_by_id(const unsigned type)
{
	for (int i = 0; i < static_cast<int>(productions.size()); ++i)
	{
		for (int j = 0; j < static_cast<int>(productions.size()) - i - 1; j++)
		{
			if (type == 1)
			{
				if (productions[j].id > productions[j + 1].id)
				{
					const production temp = productions[j];
					productions[j] = productions[j + 1];
					productions[j + 1] = temp;
				}
			}
			else
			{
				if (productions[j].id < productions[j + 1].id)
				{
					const production temp = productions[j];
					productions[j] = productions[j + 1];
					productions[j + 1] = temp;
				}
			}
		}
	}
}

void selection_sort_by_id(const unsigned type)
{
	for (int i = 0; i < static_cast<int>(productions.size()) - 1; i++)
	{
		int m = i;

		for (int j = i + 1; j < static_cast<int>(productions.size()); j++)
		{
			if (type == 1)
			{
				if (productions[j].id < productions[m].id) m = j;
			}

			else
			{
				if (productions[j].id > productions[m].id) m = j;
			}
		}

		const production temp = productions[m];
		productions[m] = productions[i];
		productions[i] = temp;
	}
}

void quick_sort_by_id(const unsigned low, const unsigned high, const unsigned type)
{
	if (low < high)
	{
		const unsigned x = productions[(low + high) / 2].id;

		unsigned i = low, j = high;

		while (i <= j)
		{
			if (type == 1)
			{
				while (productions[i].id < x) i++;
				while (productions[j].id > x) j--;
			}

			else
			{
				while (productions[i].id > x) i++;
				while (productions[j].id < x) j--;
			}

			if (i <= j)
			{
				const production temp = productions[i];
				productions[i] = productions[j];
				productions[j] = temp;
				i++;
				j--;
			}
		}

		if (low < j) quick_sort_by_id(low, j, type);
		if (i < high) quick_sort_by_id(i, high, type);
	}
}

void sort_by_id()
{
	if (is_empty())
	{
		std::cout << "Your products list is empty!\n";
		return;
	}

	unsigned sort_parameter1 = 0, sort_parameter2 = 0;

	std::cout << "How to sort a list?\n1 - Ascending\n2 - Descending: ";
	while (sort_parameter1 != 1 && sort_parameter1 != 2)
	{
		checked_unsigned_input(sort_parameter1);
		if (sort_parameter1 != 1 && sort_parameter1 != 2)
			std::cout << "Enter valid input: ";
	}

	std::cout << "How to sort a list?\n1 - SelectionSort\n2 - QuickSort\n3 - BubbleSort: ";
	while (sort_parameter2 < 1 || sort_parameter2 > 3)
	{
		checked_unsigned_input(sort_parameter2);
		if (sort_parameter2 < 1 || sort_parameter2 > 3)
			std::cout << "Enter valid input: ";
	}

	switch (sort_parameter2)
	{
	case 1:
		selection_sort_by_id(sort_parameter1);
		break;
	case 2:
		quick_sort_by_id(0, static_cast<unsigned>(productions.size()) - 1, sort_parameter1);
		break;
	case 3:
		bubble_sort_by_id(sort_parameter1);
		break;
	default:
		break;
	}
}

void find_linear(const unsigned amount_to_find)
{
	int code = 0;

	for (const production& production : productions)
	{
		if (production.amount == amount_to_find)
		{
			code = 1;
			std::cout << production.id << ' ';
		}
	}

	if (code == 0)
		std::cout << "there's no elements with such amount!\n";
	else
		std::cout << '\n';
}

void find_binary(const unsigned amount_to_find)
{
	selection_sort_by_amount(1);

	int i_key = 0, j = static_cast<int>(productions.size()) - 1;

	while (i_key < j)
	{
		const int m = (i_key + j) / 2;

		if (productions[m].amount < amount_to_find) i_key = m + 1;
		
		else j = m;
	}

	if (productions[i_key].amount != amount_to_find)
	{
		std::cout << "there's no elements with such amount!\n";
		return;
	}

	std::cout << productions[i_key].id << ' ';

	for (int i = i_key + 1; i < static_cast<int>(productions.size()); i++)
	{
		if (productions[i].amount != amount_to_find)
			break;

		std::cout << productions[i].id << ' ';
	}

	for (int i = i_key - 1; i >= 0; i--)
	{
		if (productions[i].amount != amount_to_find)
			break;

		std::cout << productions[i].id << ' ';
	}

	std::cout << '\n';
}

void find_interpolation(const unsigned amount_to_find)
{
	selection_sort_by_amount(1);

	int low = 0;
	int high = static_cast<int>(productions.size()) - 1;

	while (low <= high && amount_to_find >= productions[low].amount && amount_to_find <= productions[high].amount)
	{
		if (low == high)
		{
			if (productions[low].amount == amount_to_find)
			{
				std::cout << productions[low].id << ' ';

				for (int i = low + 1; i < static_cast<int>(productions.size()); i++)
				{
					if (productions[i].amount != amount_to_find)
						break;

					std::cout << productions[i].id << ' ';
				}

				for (int i = low - 1; i >= 0; i--)
				{
					if (productions[i].amount != amount_to_find)
						break;

					std::cout << productions[i].id << ' ';
				}

				std::cout << '\n';

				return;
			}

			std::cout << "there's no elements with such amount!\n";
			return;
		}

		const int pos = low + (high - low) / static_cast<int>((productions[high].amount - productions[low].amount)) * static_cast<int>((amount_to_find - productions[low].amount));

		if (productions[pos].amount == amount_to_find)
		{
			std::cout << productions[pos].id << ' ';

			for (int i = pos + 1; i < static_cast<int>(productions.size()); i++)
			{
				if (productions[i].amount != amount_to_find)
					break;

				std::cout << productions[i].id << ' ';
			}

			for (int i = pos - 1; i >= 0; i--)
			{
				if (productions[i].amount != amount_to_find)
					break;

				std::cout << productions[i].id << ' ';
			}

			std::cout << '\n';

			return;
		}

		if (productions[pos].amount < amount_to_find)
			low = pos + 1;
		else
			high = pos - 1;
	}

	std::cout << "there's no elements with such amount!\n";
}

void individual_task()
{
	if (is_empty())
	{
		std::cout << "Your products list is empty!\n";
		return;
	}

	std::cout << "Enter workshop to print: ";
	unsigned workshop_to_print;
	checked_unsigned_input(workshop_to_print);

	std::vector<production> temp;

	for (const production& production : productions)
		if (production.workshop_number == workshop_to_print)
			temp.emplace_back(production);

	if (temp.empty())
	{
		std::cout << "There's no products with this workshop!\n";
		return;
	}

	for (int i = 0; i < static_cast<int>(temp.size()); ++i)
	{
		for (int j = 0; j < static_cast<int>(temp.size()) - i - 1; j++)
		{
			if (temp[j].id < temp[j + 1].id)
			{
				const production temp1 = temp[j];
				temp[j] = temp[j + 1];
				temp[j + 1] = temp1;
			}
		}
	}

	std::cout << "ID" << std::setw(15) << "Name" << std::setw(18) << "Amount" << std::setw(25) << "Workshop number" << std::setw(25) << "Material" << '\n';

	std::fstream file("idividual_task.txt", std::ios::trunc | std::ios::out);
	file.close();
	file.open("idividual_task.txt", std::ios::out);

	for (const production& production : temp)
	{
		std::cout << production.id << std::setw(15) << production.name << std::setw(18) << production.amount << std::setw(25) << production.workshop_number << std::setw(25) << production.material << '\n';
		file << production.id << ':' << production.name << ':' << production.amount << ':' << production.workshop_number << ':' << production.material << '\n';
	}

	temp.clear();
}


void find()
{
	if (is_empty())
	{
		std::cout << "Your products list is empty!\n";
		return;
	}

	std::cout << "Enter amount to find: ";
	unsigned amount_to_find;
	checked_unsigned_input(amount_to_find);

	int find_parameter = 0;

	std::cout << "How to find in list?\n1 - Linear\n2 - Binary\n3 - Interpolation: ";
	while (find_parameter < 1 || find_parameter > 3)
	{
		checked_int_input(find_parameter);
		if (find_parameter < 1 || find_parameter > 3)
			std::cout << "Enter valid input: ";
	}

	if(find_parameter != 1)
		std::cout << "Array was sorted (Ascending, SelectionSort)!\n";

	std::cout << "ID(s) of element(s) with this amount: ";

	switch (find_parameter)
	{
	case 1:
		find_linear(amount_to_find);
		break;
	case 2:
		find_binary(amount_to_find);
		break;
	case 3:
		find_interpolation(amount_to_find);
		break;
	default:
		break;
	}
}