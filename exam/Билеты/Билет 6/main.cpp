
#include <iostream>

struct spis2
{
	int info;
	spis2* prev = nullptr, * next = nullptr;
};

bool is_empty(spis2* begin, spis2* end)
{
	return begin == nullptr && end == nullptr;
}

void add_begin(spis2*& begin, spis2*& end, int add)
{
	spis2* new_el = new spis2;
	new_el->info = add;

	if(is_empty(begin, end))
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

void add_end(spis2*& begin, spis2*& end, int add)
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

	while(t)
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

int main()
{
	spis2* begin1 = nullptr, * end1 = nullptr, * begin2 = nullptr, * end2 = nullptr;
	int size = 7;

	for (int i = 0; i < size; i++)
	{
		int add;
		std::cin >> add;
		add_begin(begin1, end1, add);
		//add_end(begin1, end2, add);
	}
	
	print_begin(begin1);
	//print_end(end1);
	std::cout << '\n';

	spis2* t = begin1->next;

	for (int i = 1; i < size; i += 2)
	{
		add_begin(begin2, end2, t->info);
		t = t->next->next;
	}

	print_begin(begin2);
	//print_end(end2);

	clear(begin1, end1);
	clear(begin2, end2);   

	return 0;
}
