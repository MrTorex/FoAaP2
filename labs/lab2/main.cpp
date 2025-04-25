
#include <iostream>
#include <ctime>
#include <cstdlib>
#include "queue.h"

void menu();
void checked_int_input(int& input);
void create_random_queue(Queue& queue, int& queue_size);
void create_queue_top(Queue& queue, int& queue_size);
void create_queue_bottom(Queue& queue, int& queue_size);
void push_to_queue(Queue& queue, int& queue_size, bool is_creating, bool from_top);
void push_random_to_queue(Queue& queue, int& queue_size, bool from_top);
void personal_task(Queue& queue, int& queue_size);
void end_of_function();
void pop_min_max(Node& node);

void checked_int_input (int& input)
{
	while (!(std::cin >> input))
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		std::cout << "Enter valid input: ";
	}
}

void create_random_queue(Queue& queue, int& queue_size)
{
	queue_size = rand() % 15 + 1;
	for (int i = 0; i < queue_size; i++)
	{
		if (rand() % 2 == 1)
			queue.push_top(rand() % 100);
		else
			queue.push_bottom(rand() % 100);
	}
}

void create_queue_top(Queue& queue, int& queue_size)
{
	std::cout << "Input size of your queue: ";
	checked_int_input(queue_size);

	for (int i = 0; i < queue_size; i++)
		push_to_queue(queue, queue_size, true, true);
}

void create_queue_bottom(Queue& queue, int& queue_size)
{
	std::cout << "Input size of your queue: ";
	checked_int_input(queue_size);

	for (int i = 0; i < queue_size; i++)
		push_to_queue(queue, queue_size, true, false);
}

void push_to_queue(Queue& queue, int& queue_size, bool is_creating, bool from_top)
{
	int value_to_push;

	std::cout << "Input value to push to your queue: ";
	checked_int_input(value_to_push);

	if (from_top)
		queue.push_top(value_to_push);
	else
		queue.push_bottom(value_to_push);

	if (!is_creating)
		queue_size++;

	std::cout << "Succesfully pushed!" << std::endl;
	queue.print_top();
}

void push_random_to_queue(Queue& queue, int& queue_size, bool from_top)
{
	if (from_top)
		queue.push_top(rand() % 100);
	else
		queue.push_bottom(rand() % 100);

	std::cout << "Succesfully pushed!" << std::endl;
	queue.print_top();
	queue_size++;
}

void end_of_function()
{
	system("pause");
	system("cls");
}

void pop_min_max(Node* node)
{
	node = node->next;
	node->previous = nullptr;
	delete node;
}

void personal_task(Queue& queue, int& queue_size)
{
	queue.print_top();

	Node* maximum = queue.top;
	Node* minimum = queue.top;
	Node* temp = queue.top;

	while (temp != nullptr)
	{
		if (temp->info < minimum->info)
			minimum = temp;

		if (temp->info > maximum->info)
			maximum = temp;

		temp = temp->next;
	}

	bool between_min_max = false;
	Node* current = queue.top;
	Node* previous = nullptr;

	while (current != nullptr) {
		if (current->info == minimum->info || current->info == maximum->info)
		{
			if (!between_min_max)
				between_min_max = true;
			else
				break;
		}
		else if (between_min_max) 
		{
			temp = current;
			current = current->next;
			current->previous = current->previous->previous;
			delete temp;
			previous->next = current;
			continue;
		}
		previous = current;
		current = current->next;
	}

	std::cout << "After deleting:" << std::endl;

	queue.print_top();
}

void menu()
{
	srand(time(nullptr));

	Queue queue;

	int choice = 0, queue_size = 0;

	std::cout << "Welcome to lab1! Choose your option.\n1 - create random queue\n2 - create your own queue (from top)\n3 - create your own queue (from bottom): ";

	while (choice != 1 && choice != 2 && choice != 3)
	{
		checked_int_input(choice);
		if (choice != 1 && choice != 2 && choice != 3)
			std::cout << "Enter valid input: ";
	}

	switch (choice)
	{
	case 1:
		create_random_queue(queue, queue_size);
		break;
	case 2:
		create_queue_top(queue, queue_size);
		break;
	case 3:
		create_queue_bottom(queue, queue_size);
		break;
	}

	system("cls");

	queue.print_top();

	while (choice != -1)
	{
		choice = 0;

		std::cout << "Choose your task:\n1 - push element to queue (from top)\n2 - push element to queue (from bottom)\n3 - push random to queue (from top)\n4 - push random to queue (from bottom)\n5 - pop element from queue (from top)\n6 - pop element from queue (from bottom)\n7 - personal task\n8 - print queue (from top)\n9 - print queue (from bottom)\n-1 - exit: ";

		while (choice != -1 && !(choice > 0 && choice < 10))
		{
			checked_int_input(choice);
			if (choice != -1 && !(choice > 0 && choice < 10))
				std::cout << "Enter valid input: ";
		}

		switch (choice)
		{
		case -1:
			break;
		case 1:
			push_to_queue(queue, queue_size, false, true);
			end_of_function();
			break;
		case 2:
			push_to_queue(queue, queue_size, false, false);
			end_of_function();
			break;
		case 3:
			push_random_to_queue(queue, queue_size, true);
			end_of_function();
			break;
		case 4:
			push_random_to_queue(queue, queue_size, false);
			end_of_function();
			break;
		case 5:
			queue.pop_top();

			if (!queue.is_empty())
				std::cout << "Succesfully poped!" << std::endl;
			queue.print_top();

			queue_size--;

			end_of_function();
			break;
		case 6:
			queue.pop_bottom();

			if (!queue.is_empty())
				std::cout << "Succesfully poped!" << std::endl;
			queue.print_top();

			queue_size--;

			end_of_function();
			break;
		case 7:
			personal_task(queue, queue_size);
			end_of_function();
			break;
		case 8:
			queue.print_top();
			end_of_function();
			break;
		case 9:
			queue.print_bottom();
			end_of_function();
			break;
		}
	}

	std::cout << "Have a nice day!";

	queue.delete_queue();
}



int main()
{
	menu();

	return 0;
}