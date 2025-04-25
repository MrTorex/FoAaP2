
#include <iostream>

struct participant
{
	int place;
	std::string last_name;

	participant();

	participant(const std::string& last_name, int place);

	void print() const;
};

participant::participant() { place = 0; last_name = "Ivanov"; }

participant::participant(const std::string& last_name, const int place) { this->last_name = last_name; this->place = place; }

void participant::print() const
{
	std::cout << "Last name: " << last_name << ", place: " << place << '\n';
}

void clear();

void to_hash_table(int* hash_table, const participant* participants, int m, int n);

participant* find_by_place(const int* hash_table, participant* participants, int m, int n, int place);

void to_hash_table(int* hash_table, const participant* participants, const int m, const int n)
{
	for (int it = 0; it < n; it++)
	{
		const participant participant = participants[it];

		int i = participant.place % m;

		if (hash_table[i] == -1)
		{
			hash_table[i] = participant.place;
			continue;
		}

		const int c = 1 + participant.place % (m - 2);

		while (hash_table[i] != -1)
		{
			i -= c;

			if (i < 0)
				i += m;
		}

		hash_table[i] = participant.place;
	}
}

participant* find_by_place(const int* hash_table, participant* participants, const int m, const int n, const int place)
{
	int i = place % m;

	if (hash_table[i] == place)
		return &participants[i - 1];

	const int c = 1 + place % (m - 2);

	for (int j = 0; j < m; j++)
	{
		i -= c;

		if (i < 0)
			i += m;

		if (hash_table[i] == place)
			return &participants[i - 1];
	}

	return nullptr;
}

void clear()
{
	system("pause");
	system("cls");
}

int main()
{
	constexpr int n = 7, m = 15;

	participant participants[n];

	int hash_table[m];

	for (int& i : hash_table)
		i = -1;

	for (int i = 0; i < n; i++)
	{
		std::string last_name;

		int place;

		std::cout << "Enter last name of participant No " << i + 1 << ": ";
		std::cin >> last_name;

		std::cout << "Enter place of participant No " << i + 1 << ": ";
		std::cin >> place;

		participants[i] = participant(last_name, place);
	}

	to_hash_table(hash_table, participants, m, n);

	clear();

	int place_to_find = 0;

	do
	{
		std::cout << "Participants:\n";

		for (const participant& participant : participants)
			participant.print();

		std::cout << "Hash table: ";

		for (const int i : hash_table)
			std::cout << i << ' ';

		std::cout << "\nEnter participant's place to find (-1 to exit): ";
		std::cin >> place_to_find;

		if(place_to_find != -1)
		{
			const participant* found = find_by_place(hash_table, participants, m, n, place_to_find);

			if (found == nullptr)
				std::cout << "There's no participant with place " << place_to_find << "!\n";
			else
				found->print();

			clear();
		}
	} while (place_to_find != -1);

	std::cout << "Have a nice day!";

	return 0;
}