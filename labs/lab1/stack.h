#pragma once
struct Node
{
	int info;
	Node* next;

	Node(int value)
	{
		info = value;
		next = nullptr;
	}
};

struct Stack
{
	Node* top;

	Stack()
	{
		top = nullptr;
	}

	bool is_empty()
	{
		return top == nullptr;
	}

	void push(int value)
	{
		Node* new_node = new Node(value);

		new_node->next = top;

		top = new_node;
	}

	void pop()
	{
		if (is_empty())
			return;

		Node* temp = top;

		top = top->next;

		delete temp;
	}

	int peek()
	{
		if (is_empty())
			return INT_MIN;

		return top->info;
	}

	void print()
	{
		if (is_empty())
		{
			std::cout << "Stack is empty!" << std::endl;
			return;
		}

		Node* current = top;

		std::cout << "Stack elements: ";

		while (current != nullptr)
		{
			std::cout << current->info << " ";
			current = current->next;
		}

		std::cout << std::endl;
	}

	void delete_stack()
	{
		while (!is_empty())
			pop();
	}
};