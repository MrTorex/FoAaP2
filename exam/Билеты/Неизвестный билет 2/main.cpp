
#include <iostream>

struct spis2
{
	char info;
	spis2* prev = nullptr, * next = nullptr;
};

bool is_empty(spis2* begin, spis2* end)
{
	return begin == nullptr && end == nullptr;
}

void add_begin(spis2*& begin, spis2*& end, char add)
{
	spis2* new_el = new spis2;
	new_el->info = add;

	if (is_empty(begin, end))
	{
		begin = new_el;
		end = new_el;
	}
	else
	{
		new_el->next = begin;
		begin->prev = new_el;
		begin = new_el;
	}
}

void add_end(spis2*& begin, spis2*& end, char add)
{
	spis2* new_el = new spis2;
	new_el->info = add;

	if (is_empty(begin, end))
	{
		begin = new_el;
		end = new_el;
	}
	else
	{
		new_el->prev = end;
		end->next = new_el;
		end = new_el;
	}
}

void print_begin(spis2* begin)
{
	spis2* t = begin;

	while (t)
	{
		std::cout << t->info << ' ';
		t = t->next;
	}
}

void print_end(spis2* end)
{
	spis2* t = end;

	while (t)
	{
		std::cout << t->info << ' ';
		t = t->prev;
	}
}

void clear(spis2*& begin, spis2*& end)
{
	while (begin)
	{
		if (is_empty(begin, end))
			return;

		if (begin == end)
		{
			delete begin;
			begin = nullptr;
			end = nullptr;
		}
		else
		{
			spis2* t = begin;
			begin = begin->next;
			begin->prev = nullptr;
			delete t;
		}
	}
}

void task(spis2*& begin, spis2*& end, int& size)
{
	int mid = size / 2;

	spis2* t = end;

	for (int i = 0; i < mid; i++)
		t = t->prev;

	spis2* add = new spis2;
	add->info = 'w';

	add->prev = t;
	add->next = t->next;
	t->next->prev = add;
	t->next = add;
	size++;
}

int main()
{
	spis2* begin = nullptr, * end = nullptr;
	int size;
	std::cin >> size;

	for (int i = 0; i < size; i++)
	{
		char c;
		std::cin >> c;
		add_begin(begin, end, c);
	}

	print_begin(begin);
	std::cout << '\n';
	task(begin, end, size);
	print_begin(begin);
	clear(begin, end);

	return 0;
}