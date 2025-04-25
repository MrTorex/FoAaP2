
#include <iostream>
#include <ctime>
#include <cstdlib>
#include "stack.h"

void menu();
void checked_int_input(int& input);
void create_random_stacks(Stack& stack, int stack_size);
void create_stack(Stack& stack, int& stack_size);
void push_to_stack(Stack& stack, int& stack_size, bool is_creating);
void push_random_to_stack(Stack& stack, int& stack_size);
void personal_task(Stack& stack, int& stack_size);
void end_of_function();

void checked_int_input(int& input)
{
	while (!(std::cin >> input))
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		std::cout << "Enter valid input: ";
	}
}

void create_random_stack(Stack& stack, int& stack_size)
{
	stack_size = rand() % 15 + 1;

	for (int i = 0; i < stack_size; i++)
		stack.push(rand() % 100);
}

void create_stack(Stack& stack, int& stack_size)
{
	std::cout << "Input size of your stack: ";
	checked_int_input(stack_size);

	for (int i = 0; i < stack_size; i++)
		push_to_stack(stack, stack_size, true);
}

void push_to_stack(Stack& stack, int& stack_size, bool is_creating)
{
	int value_to_push;

	std::cout << "Input value to push to your stack: ";
	checked_int_input(value_to_push);

	stack.push(value_to_push);
	if (!is_creating)
		stack_size++;

	std::cout << "Succesfully pushed!" << std::endl;
	stack.print();
}

void push_random_to_stack(Stack& stack, int& stack_size)
{
	stack.push(rand() % 100);
	std::cout << "Succesfully pushed!" << std::endl;
	stack.print();
	stack_size++;
}

void end_of_function()
{
	system("pause");
	system("cls");
}


void personal_task(Stack& stack, int& stack_size)
{
	stack.print();

	Node* maximum = stack.top;
	Node* minimum = stack.top;
	Node* temp = stack.top;

	while (temp != nullptr)
	{
		if (temp->info < minimum->info)
			minimum = temp;

		if (temp->info > maximum->info)
			maximum = temp;

		temp = temp->next;
	}

	bool between_min_max = false;
	Node* current = stack.top;
	Node* previous = nullptr;

	while (current != nullptr) {
		if (current->info == minimum->info || current->info == maximum->info)
			if (!between_min_max)
				between_min_max = true;
			else
				break;
		else if (between_min_max)
		{
			temp = current;
			current = current->next;
			delete temp;
			previous->next = current;
			continue;
		}
		previous = current;
		current = current->next;
	}

	std::cout << "After deleting:" << std::endl;

	stack.print();
}

void menu()
{
	srand(time(nullptr));

	Stack stack;

	int choice = 0, stack_size = 0;

	std::cout << "Welcome to lab1! Choose your option.\n1 - create random stack\n2 - create your own stack: ";

	while (choice != 1 && choice != 2)
	{
		checked_int_input(choice);
		if (choice != 1 && choice != 2)
			std::cout << "Enter valid input: ";
	}

	switch (choice)
	{
	case 1:
		create_random_stack(stack, stack_size);
		break;
	case 2:
		create_stack(stack, stack_size);
		break;
	}

	system("cls");

	stack.print();

	while (choice != -1)
	{
		choice = 0;

		std::cout << "Choose your task:\n1 - push element to stack\n2 - push random to stack\n3 - pop element from stack\n4 - personal task\n5 - print stack\n-1 - exit: ";

		while (choice != -1 && !(choice > 0 && choice < 6))
		{
			checked_int_input(choice);
			if (choice != -1 && !(choice > 0 && choice < 6))
				std::cout << "Enter valid input: ";
		}

		switch (choice)
		{
		case -1:
			break;
		case 1:
			push_to_stack(stack, stack_size, false);
			end_of_function();
			break;
		case 2:
			push_random_to_stack(stack, stack_size);
			end_of_function();
			break;
		case 3:
			stack.pop();

			if (!stack.is_empty())
				std::cout << "Succesfully poped!" << std::endl;
			stack.print();

			stack_size--;

			end_of_function();
			break;
		case 4:
			personal_task(stack, stack_size);
			end_of_function();
			break;
		case 5:
			stack.print();
			end_of_function();
			break;
		}
	}

	std::cout << "Have a nice day!\n";

	stack.delete_stack();
}



void main()
{
	menu();
}