#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

struct CallDetails
{
	unsigned callID;

	string callDate;

	unsigned cityCode;
	string cityName;

	unsigned long long callDuration;

	double callTariff;

	string fullPhoneNumber;
	string localPhoneNumber;

	CallDetails() = default;

	CallDetails(unsigned id, string date, unsigned code, string name, unsigned long long duration, double tariff, string fullNumber, string localNumber)
	{
		callID = id;
		callDate = date;
		cityCode = code;
		cityName = name;
		callDuration = duration;
		callTariff = tariff;
		fullPhoneNumber = fullNumber;
		localPhoneNumber = localNumber;
	}
};

struct CityInfo
{
	string cityName;
	unsigned cityCode;
	unsigned long long totalCallTime;

	CityInfo() = default;

	CityInfo(string name, unsigned code, unsigned long long time)
	{
		cityName = name;
		cityCode = code;
		totalCallTime = time;
	}
};

vector<CallDetails> callRecords;
vector<CityInfo> cityDirectory;

bool isValidInteger(string);
bool isValidDouble(string);
void convertToUnsigned(int, unsigned&);
void convertToUnsignedLongLong(int, unsigned long long&);
bool isValidDate(string);
bool isValidCity(string);
void addNewCall();
void updateCallIDs(unsigned);
void removeCall();
void displayCalls();
void exportCallsToFile();
void clearDataFile();
void finalizeAction();
void generateCityDirectory();
void importFromFile();
void bubbleSort(int);
void selectionSort(int);
void quickSort(int, int, int);
void searchRecords();
void linearSearch(unsigned long long);
void binarySearch(unsigned long long);
void interpolationSearch(unsigned long long);

bool isValidDate(string date)
{
	for (int i = 0; i < date.length(); i++)
	{
		char currentChar = date[i];
		if (!isdigit(currentChar) && currentChar != '.')
			return false;

		if (currentChar == '.' && i != 2 && i != 5 && i != 10)
			return false;
	}

	return true;
}

bool isValidInteger(string input)
{
	try
	{
		stoi(input);
	}
	catch (invalid_argument)
	{
		return false;
	}

	return true;
}

bool isValidDouble(string input)
{
	try
	{
		stod(input);
	}
	catch (invalid_argument)
	{
		return false;
	}

	return true;
}

void convertToUnsigned(int input, unsigned& result)
{
	if (input < 0)
		input *= -1;

	result = static_cast<unsigned>(input);
}

void convertToUnsignedLongLong(int input, unsigned long long& result)
{
	if (input < 0)
		input *= -1;

	result = static_cast<unsigned long long>(input);
}

bool isValidCity(string info, string& cityName, unsigned& cityCode)
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
	int inputCityCode = 0;

	try
	{
		inputCityCode = stoi(info);
	}
	catch (invalid_argument)
	{
		type = 1;
	}

	while (file)
	{
		string buf;
		string name;
		getline(file, name, ':');

		if (name.empty())
			break;

		getline(file, buf, '\n');
		int code = stoi(buf);

		if (type == 0 && code == inputCityCode)
		{
			cityCode = code;
			cityName = name;
			return true;
		}
		else if (type == 1 && name == info)
		{
			cityCode = code;
			cityName = name;
			return true;
		}
	}

	file.close();
	cout << "Города с таким кодом или названием не существует!\n";
	return false;
}

void addNewCall()
{
	CallDetails newCall;

	string inputBuffer;

	do
	{
		cout << "Введите дату звонка в формате дд.мм.гггг: ";
		getline(cin, newCall.callDate);
	} while (!isValidDate(newCall.callDate));

	do
	{
		cout << "Введите имя города или его код: ";
		getline(cin, inputBuffer);
	} while (!isValidCity(inputBuffer, newCall.cityName, newCall.cityCode));

	do
	{
		cout << "Введите время разговора (в минутах): ";
		getline(cin, inputBuffer);
	} while (!isValidInteger(inputBuffer));

	convertToUnsignedLongLong(stoi(inputBuffer), newCall.callDuration);

	do
	{
		cout << "Введите тариф: ";
		getline(cin, inputBuffer);
	} while (!isValidDouble(inputBuffer));

	newCall.callTariff = stod(inputBuffer);

	cout << "Введите телефонный номер города: ";
	getline(cin, newCall.fullPhoneNumber);

	cout << "Введите телефонный номер: ";
	getline(cin, newCall.localPhoneNumber);

	newCall.callID = callRecords.size() + 1;

	callRecords.push_back(newCall);
}

void updateCallIDs(unsigned idToDelete)
{
	for (size_t i = 0; i < callRecords.size(); i++)
		if (callRecords[i].callID > idToDelete)
			callRecords[i].callID--;
}

void removeCall()
{
	if (callRecords.empty())
	{
		cout << "У вас нет телефонных звонков!\n";
		return;
	}

	unsigned idToDelete;
	string inputBuffer;

	do
	{
		cout << "Введите ID звонка, который вы хотите удалить: ";
		getline(cin, inputBuffer);
	} while (!isValidInteger(inputBuffer));

	convertToUnsigned(stoi(inputBuffer), idToDelete);

	if (idToDelete > callRecords.size())
	{
		cout << "Не существует элемента с таким ID!\n";
		return;
	}

	for (auto it = callRecords.cbegin(); it != callRecords.cend(); ++it)
	{
		if (it->callID == idToDelete)
		{
			callRecords.erase(it);
			updateCallIDs(idToDelete);
			break;
		}
	}
}

void displayCalls()
{
	cout << "--------------------------------PhoneCalls v. 0.0.1---------------------------------------\n\n";

	if (callRecords.empty())
	{
		cout << "Список звонков пустой!\n";
		return;
	}

	cout << "ID" << setw(15) << "Дата" << setw(25) << "Город и код" << setw(15) << "Время" << setw(15) << "Тариф" << setw(25) << "Номер города" << setw(25) << "Номер" << '\n';

	for (const auto& call : callRecords)
	{
		cout << call.callID << setw(15) << call.callDate << setw(25) << call.cityName << ':' << call.cityCode << setw(15) << call.callDuration << setw(15) << call.callTariff << setw(25) << call.fullPhoneNumber << setw(25) << call.localPhoneNumber << '\n';
	}

	cout << "------------------------------------------------------------------------------------------\n\n";

	cout << setw(25) << "Город" << setw(15) << "Код" << setw(25) << "Общее время" << '\n';

	fstream file("individual_task.txt", ios::out | ios::trunc);
	file.close();
	file.open("individual_task.txt", ios::out);

	unsigned long long totalTime = 0;
	for (const auto& city : cityDirectory)
	{
		cout << setw(25) << city.cityName << setw(15) << city.cityCode << setw(25) << city.totalCallTime << '\n';
		file << setw(25) << city.cityName << setw(15) << city.cityCode << setw(25) << city.totalCallTime << '\n';
		totalTime += city.totalCallTime;
	}

	cout << "Итого времени: " << totalTime << '\n';
	file << "Итого времени: " << totalTime << '\n';
}

void exportCallsToFile()
{
	fstream file("database.txt", ios::app);
	for (const auto& call : callRecords)
	{
		file << call.callID << ':' << call.callDate << ':' << call.cityName << ':' << call.cityCode << ':' << call.callDuration << ':' << call.callTariff << ':' << call.fullPhoneNumber << ':' << call.localPhoneNumber << '\n';
	}
	file.close();
}

void clearDataFile()
{
	fstream file("database.txt", ofstream::out | ofstream::trunc);
	file.close();
}

void finalizeAction()
{
	system("pause");
	system("cls");
}

void generateCityDirectory()
{
	fstream file("city_list.txt", ios::in);

	while (true)
	{
		string inputBuffer, cityName;

		unsigned long long callTime = 0;

		getline(file, cityName, ':');

		if (cityName[0] == '\n' || cityName[0] == '\0')
			break;

		getline(file, inputBuffer, '\n');
		unsigned cityCode = stoi(inputBuffer);

		for (int i = 0; i < callRecords.size(); i++)
		{
			if (callRecords[i].cityCode == cityCode)
				callTime += callRecords[i].callDuration;
		}

		cityDirectory.emplace_back(cityName, cityCode, callTime);
	}
	file.close();
}

void importFromFile()
{
	fstream file("database.txt", ios::in);
	string inputBuffer, callDate, cityName, cityPhoneNumber, localPhoneNumber;
	unsigned id, cityCode;
	unsigned long long callTime;
	double callTariff;

	while (file)
	{
		getline(file, inputBuffer, ':');
		if (inputBuffer.empty())
			break;

		id = stoi(inputBuffer);
		getline(file, callDate, ':');
		getline(file, cityName, ':');
		getline(file, inputBuffer, ':');
		cityCode = stoi(inputBuffer);
		getline(file, inputBuffer, ':');
		callTime = stoull(inputBuffer);
		getline(file, inputBuffer, ':');
		callTariff = stod(inputBuffer);
		getline(file, cityPhoneNumber, ':');
		getline(file, localPhoneNumber, '\n');

		callRecords.emplace_back(id, callDate, cityCode, cityName, callTime, callTariff, cityPhoneNumber, localPhoneNumber);
	}
	file.close();
}

void sortCities()
{
	if (cityDirectory.empty())
	{
		cout << "Список городов пустой!\n";
		return;
	}

	int sortOrder = 0, sortMethod = 0;
	string inputBuffer;

	cout << "Выберите порядок сортировки:\n1 - По возрастанию\n2 - По убыванию: ";
	while (sortOrder != 1 && sortOrder != 2)
	{
		getline(cin, inputBuffer);
		if (!isValidInteger(inputBuffer))
		{
			cout << "Введите корректное число: ";
			continue;
		}

		sortOrder = stoi(inputBuffer);
		if (sortOrder != 1 && sortOrder != 2)
			cout << "Введите корректное число: ";
	}

	cout << "Выберите метод сортировки:\n1 - SelectionSort\n2 - QuickSort\n3 - BubbleSort: ";
	while (sortMethod < 1 || sortMethod > 3)
	{
		getline(cin, inputBuffer);
		if (!isValidInteger(inputBuffer))
		{
			cout << "Введите корректное число: ";
			continue;
		}

		sortMethod = stoi(inputBuffer);
		if (sortMethod < 1 || sortMethod > 3)
			cout << "Введите корректное число: ";
	}

	switch (sortMethod)
	{
	case 1:
		selectionSort(sortOrder);
		break;
	case 2:
		quickSort(0, cityDirectory.size() - 1, sortOrder);
		break;
	case 3:
		bubbleSort(sortOrder);
		break;
	}
}

void bubbleSort(int type)
{
	for (size_t i = 0; i < cityDirectory.size(); i++)
	{
		for (size_t j = 0; j < cityDirectory.size() - i - 1; j++)
		{
			if (type == 1)
			{
				if (cityDirectory[j].totalCallTime > cityDirectory[j + 1].totalCallTime)
				{
					swap(cityDirectory[j], cityDirectory[j + 1]);
				}
			}
			else
			{
				if (cityDirectory[j].totalCallTime < cityDirectory[j + 1].totalCallTime)
				{
					swap(cityDirectory[j], cityDirectory[j + 1]);
				}
			}
		}
	}
}

void selectionSort(int sortOrder)
{
	for (size_t i = 0; i < cityDirectory.size(); i++)
	{
		size_t minOrMaxIndex = i;
		for (size_t j = i + 1; j < cityDirectory.size(); j++)
		{
			bool condition = sortOrder == 1 ? cityDirectory[j].totalCallTime < cityDirectory[minOrMaxIndex].totalCallTime : cityDirectory[j].totalCallTime > cityDirectory[minOrMaxIndex].totalCallTime;
			if (condition)
			{
				minOrMaxIndex = j;
			}
		}
		if (minOrMaxIndex != i)
		{
			swap(cityDirectory[i], cityDirectory[minOrMaxIndex]);
		}
	}
}

void quickSort(int low, int high, int sortOrder)
{
	if (low < high)
	{
		unsigned long long pivot = cityDirectory[(low + high) / 2].totalCallTime;
		int left = low, right = high;
		while (left <= right)
		{
			if (sortOrder == 1)
			{
				while (cityDirectory[left].totalCallTime < pivot) left++;
				while (cityDirectory[right].totalCallTime > pivot) right--;
			}
			else
			{
				while (cityDirectory[left].totalCallTime > pivot) left++;
				while (cityDirectory[right].totalCallTime < pivot) right--;
			}
			if (left <= right)
			{
				swap(cityDirectory[left], cityDirectory[right]);
				left++;
				right--;
			}
		}
		if (low < right) quickSort(low, right, sortOrder);
		if (left < high) quickSort(left, high, sortOrder);
	}
}

void searchCitiesByCallTime()
{
	if (cityDirectory.empty())
	{
		cout << "Список городов пуст!\n";
		return;
	}

	string inputBuffer;
	unsigned long long callTimeToFind;
	int searchMethod;

	cout << "Введите количество минут для поиска: ";
	while (true)
	{
		getline(cin, inputBuffer);
		if (isValidInteger(inputBuffer))
		{
			callTimeToFind = stoull(inputBuffer);
			break;
		}
		cout << "Некорректный ввод. Попробуйте снова: ";
	}

	cout << "Выберите метод поиска:\n1 - Линейный\n2 - Бинарный\n3 - Интерполяционный: ";
	do
	{
		getline(cin, inputBuffer);
		searchMethod = isValidInteger(inputBuffer) ? stoi(inputBuffer) : 0;
	} while (searchMethod < 1 || searchMethod > 3);

	if (searchMethod != 1)
		cout << "Массив был отсортирован (по возрастанию, алгоритмом SelectionSort)!\n";

	cout << "Города с общим временем разговоров " << callTimeToFind << " минут: ";

	switch (searchMethod)
	{
	case 1:
		linearSearch(callTimeToFind);
		break;
	case 2:
		binarySearch(callTimeToFind);
		break;
	case 3:
		interpolationSearch(callTimeToFind);
		break;
	}
}

void linearSearch(unsigned long long callTimeToFind)
{
	bool found = false;
	for (const auto& city : cityDirectory)
	{
		if (city.totalCallTime == callTimeToFind)
		{
			found = true;
			cout << city.cityName << ' ';
		}
	}
	if (!found)
		cout << "нет городов с таким временем.\n";
	else
		cout << '\n';
}

void binarySearch(unsigned long long callTimeToFind)
{
	selectionSort(1);

	int left = 0, right = cityDirectory.size() - 1, mid;

	while (left <= right)
	{
		mid = left + (right - left) / 2;
		if (cityDirectory[mid].totalCallTime < callTimeToFind)
			left = mid + 1;
		else if (cityDirectory[mid].totalCallTime > callTimeToFind)
			right = mid - 1;
		else
			break;
	}

	if (cityDirectory[mid].totalCallTime != callTimeToFind)
	{
		cout << "нет городов с таким временем.\n";
		return;
	}

	cout << cityDirectory[mid].cityName << ' ';
	for (int i = mid + 1; i < cityDirectory.size() && cityDirectory[i].totalCallTime == callTimeToFind; i++)
		cout << cityDirectory[i].cityName << ' ';
	for (int i = mid - 1; i >= 0 && cityDirectory[i].totalCallTime == callTimeToFind; i--)
		cout << cityDirectory[i].cityName << ' ';
	cout << '\n';
}

void interpolationSearch(unsigned long long callTimeToFind)
{
	selectionSort(1);

	int low = 0;
	int high = cityDirectory.size() - 1;

	while (low <= high && callTimeToFind >= cityDirectory[low].totalCallTime && callTimeToFind <= cityDirectory[high].totalCallTime)
	{
		if (low == high)
		{
			if (cityDirectory[low].totalCallTime == callTimeToFind)
			{
				cout << cityDirectory[low].cityName << ' ';

				for (int i = low + 1; i < cityDirectory.size(); i++)
				{
					if (cityDirectory[i].totalCallTime != callTimeToFind)
						break;

					cout << cityDirectory[i].cityName << ' ';
				}

				for (int i = low - 1; i >= 0; i--)
				{
					if (cityDirectory[i].totalCallTime != callTimeToFind)
						break;

					cout << cityDirectory[i].totalCallTime << ' ';
				}

				cout << '\n';

				return;
			}

			cout << "нет городов с таким временем!\n";
			return;
		}

		int pos = low + (high - low) / (cityDirectory[high].totalCallTime - cityDirectory[low].totalCallTime) * (callTimeToFind - cityDirectory[low].totalCallTime);

		if (cityDirectory[pos].totalCallTime == callTimeToFind)
		{
			cout << cityDirectory[pos].cityName << ' ';

			for (int i = pos + 1; i < cityDirectory.size(); i++)
			{
				if (cityDirectory[i].totalCallTime != callTimeToFind)
					break;

				cout << cityDirectory[i].totalCallTime << ' ';
			}

			for (int i = pos - 1; i >= 0; i--)
			{
				if (cityDirectory[i].totalCallTime != callTimeToFind)
					break;

				cout << cityDirectory[i].cityName << ' ';
			}

			cout << '\n';

			return;
		}

		if (cityDirectory[pos].totalCallTime < callTimeToFind)
			low = pos + 1;
		else
			high = pos - 1;
	}

	cout << "нет городов с таким временем!\n";
}

int main()
{
	setlocale(LC_ALL, "Russian");

	int userChoice;

	importFromFile();
	generateCityDirectory();

	do
	{
		displayCalls();
		userChoice = 0;

		cout << "\nВыберите действие:\n"
			<< "1 - Добавить запись\n"
			<< "2 - Удалить запись\n"
			<< "3 - Очистить список\n"
			<< "4 - Отсортировать города по времени разговоров\n"
			<< "5 - Вернуть города в исходное состояние\n"
			<< "6 - Найти город по времени разговоров\n"
			<< "-1 - Выход: ";

		while ((userChoice < 1 || userChoice > 6) && userChoice != -1)
		{
			string inputBuffer;

			getline(cin, inputBuffer);
			if (isValidInteger(inputBuffer))
			{
				userChoice = stoi(inputBuffer);
				if ((userChoice < 1 || userChoice > 6) && userChoice != -1)
					cout << "Введите подходящее число: ";
			}
			else
			{
				cout << "Введите подходящее число: ";
			}
		}

		switch (userChoice)
		{
		case 1:
			addNewCall();
			cityDirectory.clear();
			generateCityDirectory();
			finalizeAction();
			break;
		case 2:
			removeCall();
			cityDirectory.clear();
			generateCityDirectory();
			finalizeAction();
			break;
		case 3:
			callRecords.clear();
			cityDirectory.clear();
			generateCityDirectory();
			finalizeAction();
			break;
		case 4:
			sortCities();
			finalizeAction();
			break;
		case 5:
			cityDirectory.clear();
			generateCityDirectory();
			finalizeAction();
			break;
		case 6:
			searchCitiesByCallTime();
			finalizeAction();
			break;
		default:
			break;
		}

		clearDataFile();
		exportCallsToFile();
	} while (userChoice != -1);

	return 0;
}
