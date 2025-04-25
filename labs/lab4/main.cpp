
#include <iostream>
#include <string>
#include <vector>
#include "checked_input.h"

struct game
{
	int price;

	std::string name;

	game();

	explicit game(int price);

	explicit game(const std::string& name);

	game(int price, const std::string& name);
};

game::game() { price = 1; name = "Unnamed"; }

game::game(const int price) { this->price = price; name = "Unnamed"; }

game::game(const std::string& name) { price = 1; this->name = name; }

game::game(const int price, const std::string& name) { this->price = price; this->name = name; }

struct tree
{
	game info;
	tree* left, * right;

	explicit tree(const game& info);
};

tree::tree(const game& info)
{
	this->info = info;
	this->right = nullptr;
	this->left = nullptr;
}

void add_to_tree(tree* root, const game& info);

tree* min_value_node(tree* node);

tree* delete_node(tree* root, int price);

void clear();

void bubble_sort(std::vector<game>& games);

tree* sorted_vector_to_bst(std::vector<game>& games, int start, int end);

void find_and_print(const tree* root, int price);

void print_preorder(const tree* root);

void print_postorder(const tree* root);

void print_inorder(const tree* root);

void add_game_to_tree(tree* root);

void delete_game_from_tree(tree* root);

void find_game_in_tree(const tree* root);

int count_names_starting_with(const tree* root, char letter);

void count_names_by_letter(const tree* root);

void add_to_tree(tree* root, const game& info)
{
	if (info.price > root->info.price)
	{
		if (root->right != nullptr)
			add_to_tree(root->right, info);
		else
			root->right = new tree(info);
	}
	else if (info.price < root->info.price)
	{
		if (root->left != nullptr)
			add_to_tree(root->left, info);
		else
			root->left = new tree(info);
	}
}

tree* min_value_node(tree* node)
{
	tree* current = node;

	while (current && current->left != nullptr)
		current = current->left;

	return current;
}

tree* delete_node(tree* root, const int price)
{
	if (root == nullptr)
		return root;

	if (price < root->info.price)
		root->left = delete_node(root->left, price);
	else if (price > root->info.price)
		root->right = delete_node(root->right, price);
	else 
	{
		if (root->left == nullptr) 
		{
			tree* temp = root->right;
			delete root;
			return temp;
		}

		if (root->right == nullptr) 
		{
			tree* temp = root->left;
			delete root;
			return temp;
		}

		const tree* temp = min_value_node(root->right);

		root->info = temp->info;

		root->right = delete_node(root->right, temp->info.price);
	}
	return root;
}

void bubble_sort(std::vector<game>& games)
{
	const int n = static_cast<int>(games.size());

	for (int i = 0; i < n - 1; i++) 
	{
		for (int j = 0; j < n - i - 1; j++) 
		{
			if (games[j].price > games[j + 1].price) 
			{
				const game temp = games[j];
				games[j] = games[j + 1];
				games[j + 1] = temp;
			}
		}
	}
}

tree* sorted_vector_to_bst(std::vector<game>& games, const int start, const int end)
{
	if (start > end)
		return nullptr;

	const int mid = (start + end) / 2;
	tree* root = new tree(games[mid]);

	root->left = sorted_vector_to_bst(games, start, mid - 1);
	root->right = sorted_vector_to_bst(games, mid + 1, end);

	return root;
}

void clear_tree(const tree* root)
{
	if (root != nullptr)
	{
		clear_tree(root->left);
		clear_tree(root->right);
		delete root;
	}
	std::cout << "Tree was cleared!";
}

void find_and_print(const tree* root, const int price)
{
	if (root == nullptr)
	{
		std::cout << "Game with price " << price << " wasn't found!\n";
		return;
	}

	if (price < root->info.price)
		find_and_print(root->left, price);
	else if (price > root->info.price)
		find_and_print(root->right, price);
	else
		std::cout << "Game found: " << "Name: " << root->info.name << ", Price: " << root->info.price << '\n';
}

void print_preorder(const tree* root)
{
	if (root != nullptr) 
	{
		std::cout << "Name: " << root->info.name << ", Price: " << root->info.price << '\n';
		print_preorder(root->left);
		print_preorder(root->right);
	}
}

void print_postorder(const tree* root)
{
	if (root != nullptr) 
	{
		print_postorder(root->left);
		print_postorder(root->right);
		std::cout << "Name: " << root->info.name << ", Price: " << root->info.price << '\n';
	}
}

void print_inorder(const tree* root)
{
	if (root != nullptr) 
	{
		print_inorder(root->left);
		std::cout << "Name: " << root->info.name << ", Price: " << root->info.price << '\n';
		print_inorder(root->right);
	}
}

void add_game_to_tree(tree* root)
{
	std::string name;

	int price;

	clear_input();

	std::cout << "Enter game to add name: ";
	std::getline(std::cin, name);

	std::cout << "Enter game to add price: ";
	checked_input(price);

	add_to_tree(root, game(price, name));
}

void delete_game_from_tree(tree* root)
{
	int price;

	std::cout << "Enter game to delete price: ";
	checked_input(price);

	delete_node(root, price);
}

void find_game_in_tree(const tree* root)
{
	int price;

	std::cout << "Enter game to find price: ";
	checked_input(price);

	find_and_print(root, price);
}

int count_names_starting_with(const tree* root, const char letter)
{
	if (root == nullptr)
		return 0;

	int count = (root->info.name[0] == letter) ? 1 : 0;

	count += count_names_starting_with(root->left, letter);
	count += count_names_starting_with(root->right, letter);

	return count;
}

void count_names_by_letter(const tree* root)
{
	char letter;

	std::cout << "Enter letter to find: ";
	std::cin >> letter;

	const int number = count_names_starting_with(root, letter);

	if (number != 0)
		std::cout << "Number of founded: " << number << '\n';
	else
		std::cout << "There's no such elements!\n";
}


void clear()
{
	system("pause");
	system("cls");
}

int main()
{
	int steam_size;

	std::cout << "Enter your Steam size: ";
	checked_input(steam_size);

	std::vector<game> steam_vector;

	for (int i = 0; i < steam_size; i++)
	{
		clear_input();

		std::string name;

		int price;
		
		std::cout << "Enter name of game No " << i + 1 << ": ";
		std::getline(std::cin, name);

		std::cout << "Enter price of game No " << i + 1 << ": ";
		checked_input(price);

		steam_vector.emplace_back(price, name);
	}

	bubble_sort(steam_vector);

	std::cout << "Your game array (sorted):\n";
	for (int i = 0; i < steam_size; i++)
		std::cout << "No: " << i + 1 << ", Name: " << steam_vector[i].name << ", Price: " << steam_vector[i].price << '\n';

	tree* steam_tree = sorted_vector_to_bst(steam_vector, 0,  static_cast<int>(steam_vector.size()) - 1);

	steam_vector.clear();

	std::cout << "Tree was formed and balanced!\n";

	clear();

	int choice = 0;

	do
	{
		std::cout << steam_tree->info.price << '\n';
		std::cout << "Enter your choice:\n1 - add element to tree\n2 - delete element from tree\n3 - find game in tree\n4 - print preorder\n5 - print postorder\n6 - print inorder\n7 - personal task\n-1 - exit: ";
		checked_input(choice);

		switch (choice)
		{
		case -1:
			break;
		case 1:
			add_game_to_tree(steam_tree);
			clear();
			break;
		case 2:
			delete_game_from_tree(steam_tree);
			clear();
			break;
		case 3:
			find_game_in_tree(steam_tree);
			clear();
			break;
		case 4:
			print_preorder(steam_tree);
			clear();
			break;
		case 5:
			print_postorder(steam_tree);
			clear();
			break;
		case 6:
			print_inorder(steam_tree);
			clear();
			break;
		case 7:
			count_names_by_letter(steam_tree);
			clear();
			break;
		default:
			std::cout << "Enter valid input!";
			clear();
		}
	} while (choice != -1);

	clear_tree(steam_tree);

	std::cout << "Have a nice day!";
	
	return 0;
}