
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

void task(spis2*& begin, spis2*& end)
{
	spis2* t = begin;
	while(t)
	{
		if(t->info % 2 == 1 || t->info % 2 == -1)
		{
			if (t == begin)
			{
				begin = begin->next;
				delete t;
				t = begin;
				continue;
			}

			if (t == end)
			{
				end = end->prev;
				end->next = nullptr;
				delete t;
				break;
			}

			t->prev->next = t->next;
			t->next->prev = t->prev;
			spis2* t1 = t;
			t = t->next;
			delete t1;
			continue;
		}
		t = t->next;
	}
}

int main()
{
	spis2* begin = nullptr, * end = nullptr;
	int size = 9;

	for (int i = 0; i < size; i++)
	{
		int add;
		std::cin >> add;
		add_begin(begin, end, add);
	}
	
	print_begin(begin);
	//print_end(end);
	std::cout << '\n';
	task(begin, end);
	print_begin(begin);

	clear(begin, end);  

	return 0;
}
