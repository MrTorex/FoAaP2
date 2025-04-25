
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

struct phone_call
{
	unsigned id;

	string date;

	unsigned city_code;
	string city_name;

	unsigned long long time;

	double tarif;

	string city_phone_number;
	string phone_number;

	phone_call() = default;

	phone_call(unsigned id, string date, unsigned city_code, string city_name, unsigned long long time, double tarif, string city_phone_number, string phone_number)
	{
		this->id = id;
		this->date = date;
		this->city_code = city_code;
		this->city_name = city_name;
		this->time = time;
		this->tarif = tarif;
		this->city_phone_number = city_phone_number;
		this->phone_number = phone_number;
	}
};

struct city
{
	string name;
	unsigned code;
	unsigned long long time;

	city() = default;

	city(string n, unsigned c, unsigned long long t)
	{
		name = n;
		code = c;
		time = t;
	}
};

vector<phone_call> phone_calls;
vector<city> cities;

bool check_int_input(string);
bool check_double_input(string);
void convert_int_to_unsigned(int, unsigned&);
void convert_int_to_unsigned_long_long(int, unsigned long long&);
bool check_date_input(string);
bool check_city_input(string);
void create_new_phone_call();
void set_new_ids(unsigned);
void delete_phone_call();
void print_phone_calls();
void print_phone_calls_to_file();
void clear_file();
void end_of_function();
void create_city_vector();
void read_from_file();
void selection_sort(int);
void bubble_sort(int);
void quick_sort(int, int, int);
void find();
void find_linear(unsigned long long);
void find_binary(unsigned long long);
void find_interpolation(unsigned long long);

bool check_date_input(string date)
{
	for (int i = 0; i < date.length(); i++)
	{
		char c = date[i];
		if (!isdigit(c) && c != '.')
			return false;

		if (c == '.' && i != 2 && i != 5 && i != 10)
			return false;
	}

	return true;
}

bool check_city_input(string info, string& city_name, unsigned& city_code)
{
	fstream file("city_list.txt", ios::in);

	if (!file.is_open())
	{
		cout << "Файл с городами был создан по умолчанию, поскольку файла не существует.\n";
		file.close();
		file.open("city_list.txt", ios::app);
		file << "Brest:1\nVitebsk:2\nGomel:3\nGrodno:4\nMogilev:5\nMinsk:6";
		file.close();
		file.open("city_list.txt", ios::in);
	}

	int type = 0;
	int input_city_code = 0;

	try
	{
		input_city_code = stoi(info);
	}
	catch (invalid_argument)
	{
		type = 1;
	}

	while(true)
	{
		string buf;

		string name;

		getline(file, name, ':');

		if (name[0] == '\n' || name[0] == '\0')
			break;

		getline(file, buf, '\n');
		int code = stoi(buf);

		if (type == 0)
		{
			if (code == input_city_code)
			{
				city_code = code;
				city_name = name;
				return true;
			}
		}
		else
		{
			if (name == info)
			{
				city_code = code;
				city_name = name;
				return true;
			}
		}
	}

	file.close();

	cout << "Города с таким годом или названием не существует!\n";

	return false;
}

bool check_int_input(string input)
{
	try
	{
		int temp = stoi(input);
	}
	catch (invalid_argument)
	{
		return false;
	}

	return true;
}

bool check_double_input(string input)
{
	try
	{
		double temp = stod(input);
	}
	catch (invalid_argument)
	{
		return false;
	}

	return true;
}

void convert_int_to_unsigned_long_long(int input, unsigned long long& result)
{
	if (input < 0)
		input *= -1;

	result = input;
}

void convert_int_to_unsigned(int input, unsigned& result)
{
	if (input < 0)
		input *= -1;

	result = input;
}

void create_new_phone_call()
{
	phone_call add;

	string buf;

	do
	{
		cout << "Введите дату звонка в формате дд.мм.гггг: ";
		getline(cin, add.date);
	} while (!check_date_input(add.date));

	do
	{
		cout << "Введите имя города или его код: ";
		getline(cin, buf);
	} while (!check_city_input(buf, add.city_name, add.city_code));

	do
	{
		cout << "Введите время разговора (в минутах): ";
		getline(cin, buf);
	} while (!check_int_input(buf));

	convert_int_to_unsigned_long_long(stoi(buf), add.time);

	do
	{
		cout << "Введите тариф: ";
		getline(cin, buf);
	} while (!check_double_input(buf));

	add.tarif = stod(buf);

	cout << "Введите телефонный номер города: ";
	getline(cin, add.city_phone_number);

	cout << "Введите телефонный номер: ";
	getline(cin, add.phone_number);

	add.id = phone_calls.size() + 1;

	phone_calls.push_back(add);
}

void set_new_ids(unsigned id_to_delete)
{
	for (int i = 0; i < phone_calls.size(); i++)
		if (phone_calls[i].id > id_to_delete)
			phone_calls[i].id--;
}

void delete_phone_call()
{
	if (phone_calls.empty())
	{
		cout << "У вас нет телефонных звонков!\n";
		return;
	}

	unsigned id_to_delete;

	string buf;

	do
	{
		cout << "Введите ID звонка, который вы хотите удалить: ";
		getline(cin, buf);
	} while (!check_int_input(buf));

	convert_int_to_unsigned(stoi(buf), id_to_delete);

	if (id_to_delete > phone_calls.size())
	{
		cout << "Не существует элемента с таким ID!\n";
		return;
	}

	for (auto it = phone_calls.cbegin(); it != phone_calls.cend(); ++it)
	{
		if (it->id == id_to_delete)
		{
			phone_calls.erase(it);
			set_new_ids(id_to_delete);
			break;
		}
	}
}

void print_phone_calls()
{
	cout << "--------------------------------PhoneCall Manager v. 1.0.0--------------------------------\n\n";

	if (phone_calls.empty())
	{
		cout << "Список звонков пустой!\n";
		return;
	}

	cout << "ID" << setw(15) << "Дата" << setw(25) << "Город и код" << setw(15) << "Время" << setw(15) << "Тариф" << setw(25) << "Номер города" << setw(25) << "Номер" << '\n';

	for (int i = 0; i < phone_calls.size(); i++)
		cout << phone_calls[i].id << setw(15) << phone_calls[i].date << setw(25) << phone_calls[i].city_name << ':' << phone_calls[i].city_code << setw(15) << phone_calls[i].time << setw(15) << phone_calls[i].tarif << setw(25) << phone_calls[i].city_phone_number << setw(25) << phone_calls[i].phone_number << '\n';

	cout << "------------------------------------------------------------------------------------------\n\n";

	cout << setw(25) << "Город" << setw(15) << "Код" << setw(25) << "Общее время" << '\n';

	fstream file("individual_task.txt", ios::out | ios::trunc);
	file.close();
	file.open("individual_task.txt", ios::out);

	unsigned long long time = 0;
	for (int i = 0; i < cities.size(); i++)
	{
		cout << setw(25) << cities[i].name << setw(15) << cities[i].code << setw(25) << cities[i].time << '\n';
		file << setw(25) << cities[i].name << setw(15) << cities[i].code << setw(25) << cities[i].time << '\n';
		time += cities[i].time;
	}

	cout << "Итого времени: " << time << '\n';
	file << "Итого времени: " << time << '\n';
}

void print_phone_calls_to_file()
{
	fstream file("database.txt", ios::app);
	for (int i = 0; i < phone_calls.size(); i++)
		file << phone_calls[i].id << ':' << phone_calls[i].date << ':' << phone_calls[i].city_name << ':' << phone_calls[i].city_code << ':' << phone_calls[i].time << ':' << phone_calls[i].tarif << ':' << phone_calls[i].city_phone_number << ':' << phone_calls[i].phone_number << '\n';
}

void clear_file()
{
	fstream file("database.txt", ofstream::out | ofstream::trunc);
	file.close();
}

void end_of_function()
{
	system("pause");
	system("cls");
}

void create_city_vector()
{
	fstream file("city_list.txt", ios::in);
	while (true)
	{
		string buf;

		string name;

		unsigned long long time = 0;

		getline(file, name, ':');

		if (name[0] == '\n' || name[0] == '\0')
			break;

		getline(file, buf, '\n');
		unsigned code = stoi(buf);

		for (int i = 0; i < phone_calls.size(); i++)
		{
			if (phone_calls[i].city_code == code)
				time += phone_calls[i].time;
		}

		cities.emplace_back(name, code, time);
	}

	file.close();
}

void read_from_file()
{
	fstream file("database.txt", ios::in);

	while (true)
	{
		string buf;

		getline(file, buf, ':');

		if(buf[0] == '\n' || buf[0] == '\0')
			break;

		unsigned id = stoi(buf);

		string date;
		getline(file, date, ':');

		string city_name;
		getline(file, city_name, ':');

		getline(file, buf, ':');
		unsigned city_code = stoi(buf);

		getline(file, buf, ':');
		unsigned long long time = stoi(buf);

		getline(file, buf, ':');
		double tarif = stod(buf);

		string city_phone_number;
		getline(file, city_phone_number, ':');

		string phone_number;
		getline(file, phone_number, '\n');

		phone_calls.emplace_back(id, date, city_code, city_name, time, tarif, city_phone_number, phone_number);
	}

	file.close();
}

void bubble_sort(int type)
{
	for (int i = 0; i < cities.size(); i++)
	{
		for (int j = 0; j < cities.size() - i - 1; j++)
		{
			if (type == 1)
			{
				if (cities[j].time > cities[j+1].time)
				{
					city temp = cities[j];
					cities[j] = cities[j + 1];
					cities[j + 1] = temp;
				}
			}
			else
			{
				if (cities[j].time < cities[j + 1].time)
				{
					city temp = cities[j];
					cities[j] = cities[j + 1];
					cities[j + 1] = temp;
				}
			}
		}
	}
}

void selection_sort(int type)
{
	for (int i = 0; i < cities.size(); i++)
	{
		int m = i;

		for (int j = i + 1; j < cities.size(); j++)
		{
			if (type == 1)
			{
				if (cities[j].time < cities[m].time) m = j;
			}

			else
			{
				if (cities[j].time > cities[m].time) m = j;
			}
		}

		city temp = cities[m];
		cities[m] = cities[i];
		cities[i] = temp;
	}
}

void quick_sort(int low, int high, int type)
{
	if (low < high) 
	{
		unsigned x = cities[(low + high) / 2].time;
		int i = low, j = high;
		while (i <= j) 
		{
			if (type == 1) 
			{
				while (cities[i].time < x) i++;
				while (cities[j].time > x) j--;
			}
			else 
			{
				while (cities[i].time > x) i++;
				while (cities[j].time < x) j--;
			}
			if (i <= j) 
			{
				city temp = cities[i];
				cities[i] = cities[j];
				cities[j] = temp;
				i++;
				j--;
			}
		}
		if (low < j) quick_sort(low, j, type);
		if (i < high) quick_sort(i, high, type);
	}
}

void sort_cities()
{
	if (cities.empty())
	{
		cout << "Список городов пустой!\n";
		return;
	}

	int sort_parameter1 = 0, sort_parameter2 = 0;

	string buf;

	cout << "Как сортировать?\n1 - По возрастанию\n2 - По убыванию: ";
	while (sort_parameter1 != 1 && sort_parameter1 != 2)
	{
		getline(cin, buf);

		if (!check_int_input(buf))
		{
			cout << "Введите правильное число: ";
			continue;
		}

		sort_parameter1 = stoi(buf);

		if (sort_parameter1 != 1 && sort_parameter1 != 2)
			cout << "Введите правильное число: ";
	}

	cout << "Каким методом сортировать?\n1 - SelectionSort\n2 - QuickSort\n3 - BubbleSort: ";
	while (sort_parameter2 < 1 || sort_parameter2 > 3)
	{
		getline(cin, buf);

		if (!check_int_input(buf))
		{
			cout << "Введите правильное число: ";
			continue;
		}

		sort_parameter2 = stoi(buf);

		if (sort_parameter2 < 1 || sort_parameter2 > 3)
			cout << "Введите правильное число: ";
	}

	switch (sort_parameter2)
	{
	case 1:
		selection_sort(sort_parameter1);
		break;
	case 2:
		quick_sort(0, cities.size() - 1, sort_parameter1);
		break;
	case 3:
		bubble_sort(sort_parameter1);
		break;
	default:
		break;
	}
}

void find()
{
	if (cities.empty())
	{
		cout << "Список городов пуст!!\n";
		return;
	}

	string buf;

	while (!check_int_input(buf))
	{
		cout << "Введите кол-во разговоров для нахождения: ";
		getline(cin, buf);
	}

	unsigned long long time_to_find = stoi(buf);

	int find_parameter = 0;

	cout << "Как искать?\n1 - Линейно\n2 - Бинарно\n3 - Интерполяционно: ";
	while (find_parameter < 1 || find_parameter > 3)
	{
		getline(cin, buf);

		if (!check_int_input(buf))
		{
			cout << "Введите правильное число: ";
			continue;
		}

		find_parameter = stoi(buf);

		if (find_parameter < 1 || find_parameter > 3)
			cout << "Введите правильное число: ";
	}

	if (find_parameter != 1)
		cout << "Массив был отсортирован (по возрастанию, алгоритмом SelectionSort)!\n";

	cout << "Названия городов с таким временем: ";

	switch (find_parameter)
	{
	case 1:
		find_linear(time_to_find);
		break;
	case 2:
		find_binary(time_to_find);
		break;
	case 3:
		find_interpolation(time_to_find);
		break;
	default:
		break;
	}
}

void find_linear(unsigned long long time_to_find)
{
	int code = 0;

	for (int i = 0; i < cities.size(); i++)
	{
		if (cities[i].time == time_to_find)
		{
			code = 1;
			cout << cities[i].name << ' ';
		}
	}

	if (code == 0)
		cout << "нет городов с таким временем!\n";
	else
		cout << '\n';
}

void find_binary(unsigned long long time_to_find)
{
	selection_sort(1);

	int i_key = 0, j = cities.size() - 1;

	while (i_key < j)
	{
		const int m = (i_key + j) / 2;

		if (cities[m].time < time_to_find) i_key = m + 1;

		else j = m;
	}

	if (cities[i_key].time != time_to_find)
	{
		cout << "нет городов с таким временем!\n";
		return;
	}

	cout << cities[i_key].name << ' ';

	for (int i = i_key + 1; i < cities.size(); i++)
	{
		if (cities[i].time != time_to_find)
			break;

		cout << cities[i].name << ' ';
	}

	for (int i = i_key - 1; i >= 0; i--)
	{
		if (cities[i].time != time_to_find)
			break;

		cout << cities[i].name << ' ';
	}

	cout << '\n';
}

void find_interpolation(unsigned long long time_to_find)
{
	selection_sort(1);

	int low = 0;
	int high = cities.size() - 1;

	while (low <= high && time_to_find >= cities[low].time && time_to_find <= cities[high].time)
	{
		if (low == high)
		{
			if (cities[low].time == time_to_find)
			{
				cout << cities[low].name << ' ';

				for (int i = low + 1; i < cities.size(); i++)
				{
					if (cities[i].time != time_to_find)
						break;

					cout << cities[i].name << ' ';
				}

				for (int i = low - 1; i >= 0; i--)
				{
					if (cities[i].time != time_to_find)
						break;

					cout << cities[i].name << ' ';
				}

				cout << '\n';

				return;
			}

			cout << "нет городов с таким временем!\n";
			return;
		}

		int pos = low + (high - low) / (cities[high].time - cities[low].time) * (time_to_find - cities[low].time);

		if (cities[pos].time == time_to_find)
		{
			cout << cities[pos].name << ' ';

			for (int i = pos + 1; i < cities.size(); i++)
			{
				if (cities[i].time != time_to_find)
					break;

				cout << cities[i].name << ' ';
			}

			for (int i = pos - 1; i >= 0; i--)
			{
				if (cities[i].time != time_to_find)
					break;

				cout << cities[i].name << ' ';
			}

			cout << '\n';

			return;
		}

		if (cities[pos].time < time_to_find)
			low = pos + 1;
		else
			high = pos - 1;
	}

	cout << "нет городов с таким временем!\n";
}

int main()
{
	setlocale(LC_NUMERIC, "C");
	setlocale(LC_CTYPE, "Russian");


	int choice;

	read_from_file();
	create_city_vector();

	do
	{
		print_phone_calls();
		choice = 0;

		cout << "\nВыберите действие:\n1 - добавить запись\n2 - удалить запись\n3 - очистить список\n4 - отсортировать города по времени разговоров\n5 - вернуть города в исходный вид\n6 - найти город по времени разговоров\n-1 - выход: ";

		while ((choice < 1 || choice > 6) && choice != -1)
		{
			string buf;

			getline(cin, buf);
			if (!check_int_input(buf))
				cout << "Введите подходящее число: ";

			else
			{
				choice = stoi(buf);
				if ((choice < 1 || choice > 6) && choice != -1)
					cout << "Введите подходящее число: ";
			}
		}

		switch (choice)
		{
		case 1:
			create_new_phone_call();
			cities.clear();
			create_city_vector();
			end_of_function();
			break;
		case 2:
			delete_phone_call();
			cities.clear();
			create_city_vector();
			end_of_function();
			break;
		case 3:
			phone_calls.clear();
			cities.clear();
			create_city_vector();
			end_of_function();
			break;
		case 4:
			sort_cities();
			end_of_function();
			break;
		case 5:
			cities.clear();
			create_city_vector();
			end_of_function();
			break;
		case 6:
			find();
			end_of_function();
			break;
		default:
			break;
		}

		clear_file();
		print_phone_calls_to_file();
	} while (choice != -1);
	return 0;
}