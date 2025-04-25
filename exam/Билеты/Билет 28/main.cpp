
#include <iostream>

struct stack
{
	int info;
	stack* next = nullptr;
};

bool is_empty(stack* top)
{
	return top == nullptr;
}

void add(stack*& top, int add)
{
	if (is_empty(top))
	{
		top = new stack;
		top->info = add;
	}
	else
	{
		stack* t = top;
		top = new stack;
		top->info = add;
		top->next = t;
	}
}

void print(stack* top)
{
	stack* t = top;

	while (t)
	{
		std::cout << t->info << ' ';
		t = t->next;
	}
}

void task(stack*& top)
{
    if (top == nullptr || top->next == nullptr)
        return;

    stack* max = top, * min = top, * t = top, * min_prev = nullptr, * max_prev = nullptr, * prev = nullptr;
    int max_val = top->info, min_val = top->info;

	while (t)
    {
        if (t->info > max_val)
        {
            max_prev = prev;
            max = t;
            max_val = t->info;
        }
        if (t->info < min_val)
        {
            min_prev = prev;
            min = t;
            min_val = t->info;
        }
        prev = t;
        t = t->next;
    }

    if (min != max)
    {
        if (min_prev)
            min_prev->next = max;
        else
            top = max;

        if (max_prev)
            max_prev->next = min;
        else
            top = min;

        stack* temp = min->next;
        min->next = max->next;
        max->next = temp;
    }
}

void clear(stack* top)
{
	if (is_empty(top))
		return;

	if (!top->next)
	{
		delete top;
		return;
	}

	stack* t = top;
	while (t)
	{
		top = top->next;
		delete t;
		t = top;
	}

}

int main()
{
	stack* top = nullptr;
	int size = 7;

	for (int i = 0; i < size; i++)
	{
		int value;
		std::cin >> value;
		add(top, value);
	}

	print(top);
	task(top);
	std::cout << '\n';
	print(top);
	clear(top);

	return 0;
}