#pragma once
struct Node
{
	int info;
	Node* next;
	Node* previous;

	Node(int value)
	{
		info = value;
		next = nullptr;
		previous = nullptr;
	}
};

struct Queue
{
	Node* top;
	Node* bottom;

	Queue()
	{
		top = nullptr;
		bottom = nullptr;
	}

	bool is_empty()
	{
		return (top == nullptr && bottom == nullptr);
	}

	void push_top(int value)
	{
		Node* new_node = new Node(value);

		if (is_empty())
		{
			top = new_node;
			bottom = new_node;
		}
		else
		{
			new_node->next = top;
			new_node->previous = nullptr;
			top->previous = new_node;
			top = new_node;
		}
	}

	void push_bottom(int value)
	{
		Node* new_node = new Node(value);

		if (is_empty()) 
		{
			top = new_node;
			bottom = new_node;
		}
		else 
		{
			new_node->previous = bottom;
			new_node->next = nullptr;
			bottom->next = new_node;
			bottom = new_node;
		}
	}

	void pop_top()
	{
		if (is_empty())
			return;

		if (top == bottom)
		{
			delete bottom;
			top = nullptr;
			bottom = nullptr;
		}
		else
		{
			Node* temp = top;
			top = top->next;
			top->previous = nullptr;
			delete temp;
		}
	}

	void pop_bottom()
	{
		if (is_empty())
			return;

		if (top == bottom) 
		{
			delete bottom;
			top = nullptr;
			bottom = nullptr;
		}
		else 
		{
			Node* temp = bottom;
			bottom = bottom->previous;
			bottom->next = nullptr;
			delete temp;
		}
	}

	int peek_top()
	{
		if (is_empty())
			return INT_MIN;

		return top->info;
	}

	int peek_bottom()
	{
		if (is_empty())
			return INT_MIN;

		return bottom->info;
	}

	void print_top()
	{
		if (is_empty())
		{
			std::cout << "Queue is empty!" << std::endl;
			return;
		}

		Node* current = top;

		std::cout << "Queue elements (from top): ";

		while (current != nullptr)
		{
			std::cout << current->info << " ";
			current = current->next;
		}

		std::cout << std::endl;
	}

	void print_bottom()
	{
		if (is_empty())
		{
			std::cout << "Queue is empty!" << std::endl;
			return;
		}

		Node* current = bottom;

		std::cout << "Queue elements (from bottom): ";

		while (current != nullptr)
		{
			std::cout << current->info << " ";
			current = current->previous;
		}

		std::cout << std::endl;
	}

	void delete_queue()
	{
		while (!is_empty())
			pop_top();
	}
};