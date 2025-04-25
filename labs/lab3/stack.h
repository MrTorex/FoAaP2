
#pragma once
#include <iostream>

template <typename T>
struct node
{
	T info;
	node* next;

	explicit node(T value)
	{
		info = value;
		next = nullptr;
	}
};

template <typename T>
struct stack
{
	node<T>* top;

	stack()
	{
		top = nullptr;
	}

	bool is_empty() const
	{
		return top == nullptr;
	}

	void push(const T value)
	{
		const auto new_node = new node<T>(value);

		new_node->next = top;

		top = new_node;
	}

	void pop()
	{
		if (is_empty())
			return;

		const node<T>* temp = top;

		top = top->next;

		delete temp;
	}

	T peek() const
	{
		if (is_empty())
			throw std::overflow_error("Stack is empty!");

		return top->info;
	}

	void print()
	{
		if (is_empty())
		{
			std::cout << "Stack is empty!\n";
			return;
		}

		node<T>* current = top;

		std::cout << "Stack elements: ";

		while (current != nullptr)
		{
			std::cout << current->info << ' ';
			current = current->next;
		}

		std::cout << '\n';
	}

	void delete_stack()
	{
		while (!is_empty())
			pop();
	}
};