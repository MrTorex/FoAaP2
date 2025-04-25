
#pragma once

struct production
{
	std::string name;
	unsigned amount;
	unsigned workshop_number;
	unsigned id;
	std::string material;

	production(const std::string& name, unsigned amount, unsigned workshop_number, unsigned id, const std::string& material);
};

void create_new_production();
void set_new_ids(unsigned id_to_delete);
void print_productions();
void delete_production();
bool is_empty();
void write_to_file();
void read_from_file();
void clear();
void sort_by_amount();
void bubble_sort_by_amount(unsigned type);
void selection_sort_by_amount(unsigned type);
void quick_sort_by_amount(unsigned low, unsigned high, unsigned type);
void bubble_sort_by_id(unsigned type);
void sort_by_id();
void selection_sort_by_id(unsigned type);
void quick_sort_by_id(unsigned low, unsigned high, unsigned type);
void find();
void find_linear(unsigned amount_to_find);
void find_binary(unsigned amount_to_find);
void find_interpolation(unsigned amount_to_find);
void individual_task();