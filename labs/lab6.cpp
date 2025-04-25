
#include <iostream>

void swap(int&, int&) noexcept;
void bubble_sort(int*&, int, bool);
void insertion_sort(int*&, int, bool);
void selection_sort(int*&, int, bool);
void quick_sort(int*&, int, int, bool);
int linear_search(const int*, int, int);
int binary_search(int*&, int, int);
int interpolation_search(int*&, int, int);
int* input_array(int&);
int* random_array(int&);
void print_array(const int*, int);
void sort(int*&, int);
void search(int*&, int);
void clear();

void swap(int& a, int& b) noexcept
{
	const int temp = a;
	a = b;
	b = temp;
}

int* input_array(int& size)
{
	std::cout << "Input size of your array: ";
	std::cin >> size;

	const auto arr = new int[size];

	for (int i = 0; i < size; ++i)
	{
		std::cout << "Input element of array No " << i + 1 << ": ";
		std::cin >> arr[i];
	}

	return arr;
}

int* random_array(int& size)
{
	size = rand() % 20 + 1;

	const auto arr = new int[size];

	for (int i = 0; i < size; ++i)
		arr[i] = rand() % 200 - 100;

	return arr;
}

void bubble_sort(int*& arr, const int size, const bool is_ascending)
{
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size - i - 1; j++)
		{
			if (is_ascending)
			{
				if (arr[j] > arr[j + 1])
					swap(arr[j], arr[j + 1]);
			}
			else
			{
				if (arr[j] < arr[j + 1])
					swap(arr[j], arr[j + 1]);
			}
		}
	}
}

void insertion_sort(int*& arr, const int size, const bool is_ascending)
{
	for (int i = 1; i < size; ++i)
	{
		const int key = arr[i];
		int j = i - 1;

		if (is_ascending)
		{
			while (j >= 0 && arr[j] > key)
			{
				arr[j + 1] = arr[j];
				--j;
			}
		}
		else
		{
			while (j >= 0 && arr[j] < key)
			{
				arr[j + 1] = arr[j];
				--j;
			}
		}
		arr[j + 1] = key;
	}
}

void selection_sort(int*& arr, const int size, const bool is_ascending)
{
	for (int i = 0; i < size - 1; ++i) 
	{
		int min_idx = i;

		for (int j = i + 1; j < size; ++j)
		{
			if (is_ascending)
			{
				if (arr[j] < arr[min_idx])
					min_idx = j;
			}
			else
			{
				if (arr[j] > arr[min_idx])
					min_idx = j;
			}
		}

		swap(arr[min_idx], arr[i]);
	}
}

void quick_sort(int*& arr, const int low, const int high, const bool is_ascending)
{
	if (low < high)
	{
		const int x = arr[(low + high) / 2];

		int i = low, j = high;

		while (i <= j)
		{
			if (is_ascending)
			{
				while (arr[i] < x) ++i;
				while (arr[j] > x) --j;
			}
			else
			{
				while (arr[i] > x) ++i;
				while (arr[j] < x) --j;
			}

			if (i <= j)
			{
				swap(arr[i], arr[j]);
				++i;
				--j;
			}
		}

		if (low < j) quick_sort(arr, low, j, is_ascending);
		if (i < high) quick_sort(arr, i, high, is_ascending);
	}
}

int linear_search(const int* arr, const int size, const int find)
{
	for (int i = 0; i < size; ++i)
		if (arr[i] == find)
			return i;

	return -1;
}

int binary_search(int*& arr, const int size, const int find)
{
	quick_sort(arr, 0, size - 1, true);

	int left = 0;
	int right = size - 1;

	while (left <= right) 
	{
		const int middle = left + (right - left) / 2;

		if (arr[middle] == find)
			return middle;

		if (arr[middle] < find)
			left = middle + 1;
		else
			right = middle - 1;
	}

	return -1;
}

int interpolation_search(int*& arr, const int size, const int find)
{
	quick_sort(arr, 0, size - 1, true);

	int low = 0;
	int high = size - 1;

	while (low <= high && find >= arr[low] && find <= arr[high]) 
	{
		if (low == high) 
		{
			if (arr[low] == find) return low;
			return -1;
		}

		const int pos = low + (high - low) / (arr[high] - arr[low]) * (find - arr[low]);

		if (arr[pos] == find)
			return pos;

		if (arr[pos] < find)
			low = pos + 1;
		else
			high = pos - 1;
	}

	return -1;
}

void print_array(const int* arr, const int size)
{
	for(int i = 0; i < size; ++i)
		std::cout << arr[i] << ' ';
	std::cout << '\n';
}

void sort(int*& arr, const int size)
{
	int type1, type2;

	std::cout << "How to sort an array?\n0 - Ascending\n1 - Descending: ";
	std::cin >> type1;

	std::cout << "With which algorithm to sort?\n1 - BubbleSort\n2 - InsertionSort\n3 - SelectionSort\n4 - QuickSort: ";
	std::cin >> type2;

	switch (type2)
	{
	case 1:
		bubble_sort(arr, size, !type1);
		break;
	case 2:
		insertion_sort(arr, size, !type1);
		break;
	case 3:
		selection_sort(arr, size, !type1);
		break;
	case 4:
		quick_sort(arr, 0, size - 1, !type1);
		break;
	default:
		std::cout << "Wrong option! Please, select again.\n";
		return;
	}

	std::cout << "Sorted array: ";
	print_array(arr, size);
}

void search(int*& arr, const int size)
{
	int find, type, result;

	std::cout << "Enter value to find: ";
	std::cin >> find;

	std::cout << "With which algorithm to find?\n1 - LinearSearch\n2 - BinarySearch\n3 - InterpolationSearch: ";
	std::cin >> type;

	switch (type)
	{
	case 1:
		result = linear_search(arr, size, find);
		break;
	case 2:
		result = binary_search(arr, size, find);
		break;
	case 3:
		result = interpolation_search(arr, size, find);
		break;
	default:
		std::cout << "Wrong option! Please, select again.\n";
		return;
	}

	if (result == -1)
		std::cout << "There's no element with value " << find << "!\n";
	else
		std::cout << "Element with value " << find << " has index " << result << ".\n";
}

void clear()
{
	system("pause");
	system("cls");
}

int main()
{
	srand(static_cast<unsigned>(time(nullptr)));
	int size = 0, choice = 0;
	int* arr = nullptr;

	do
	{
		std::cout << "How to create an array?\n1 - enter values\n2 - create random: ";
		std::cin >> choice;

		switch (choice)
		{
		case 1:
			arr = input_array(size);
			break;
		case 2:
			arr = random_array(size);
			break;
		default:
			std::cout << "Wrong option! Please, select again.\n";
		}
		clear();
	} while (choice != 1 && choice != 2);

	do
	{
		choice = 0;

		print_array(arr, size);

		std::cout << "Enter your choice:\n1 - sort array\n2 - search in array\nany else - exit: ";
		std::cin >> choice;

		switch (choice)
		{
		case 1:
			sort(arr, size);
			clear();
			break;
		case 2:
			search(arr, size);
			clear();
			break;
		default:
			std::cout << "Have a nice day!";
		}
	} while (choice == 1 || choice == 2);

	return 0;
}