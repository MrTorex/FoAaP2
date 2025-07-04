#include <iostream>

// Определение структуры для элемента двунаправленной очереди
struct spis2
{
	int info;            // Информационное поле элемента (целое число)
	spis2* prev = nullptr, * next = nullptr;  // Указатели на предыдущий и следующий элементы
};

// Функция проверки пустоты очереди
bool is_empty(spis2* begin, spis2* end)
{
	return begin == nullptr && end == nullptr;  // Возвращает true, если начало и конец очереди равны nullptr
}

// Функция добавления элемента в начало очереди
void add_begin(spis2*& begin, spis2*& end, int add)
{
	spis2* new_el = new spis2;  // Выделяем память под новый элемент
	new_el->info = add;         // Записываем значение в информационное поле нового элемента

	if (is_empty(begin, end))   // Если очередь пуста
	{
		begin = new_el;    // Начало и конец очереди указывают на новый элемент
		end = new_el;
	}
	else
	{
		new_el->next = begin;    // Устанавливаем связь нового элемента с текущим началом очереди
		begin->prev = new_el;    // Устанавливаем связь текущего начала очереди с новым элементом
		begin = new_el;          // Обновляем указатель на начало очереди
	}
}

// Функция добавления элемента в конец очереди
void add_end(spis2*& begin, spis2*& end, int add)
{
	spis2* new_el = new spis2;  // Выделяем память под новый элемент
	new_el->info = add;         // Записываем значение в информационное поле нового элемента

	if (is_empty(begin, end))   // Если очередь пуста
	{
		begin = new_el;    // Начало и конец очереди указывают на новый элемент
		end = new_el;
	}
	else
	{
		new_el->prev = end;      // Устанавливаем связь нового элемента с текущим концом очереди
		end->next = new_el;      // Устанавливаем связь текущего конца очереди с новым элементом
		end = new_el;            // Обновляем указатель на конец очереди
	}
}

// Функция печати элементов очереди, начиная с начала
void print_begin(spis2* begin)
{
	spis2* t = begin;  // Временный указатель на начало очереди

	while(t)  // Пока не достигнут конец очереди (t не nullptr)
	{
		std::cout << t->info << ' ';  // Выводим значение текущего элемента
		t = t->next;                  // Переходим к следующему элементу в очереди
	}
}

// Функция печати элементов очереди, начиная с конца
void print_end(spis2* end)
{
	spis2* t = end;  // Временный указатель на конец очереди

	while(t)  // Пока не достигнуто начало очереди (t не nullptr)
	{
		std::cout << t->info << ' ';  // Выводим значение текущего элемента
		t = t->prev;                  // Переходим к предыдущему элементу в очереди
	}
}

// Функция освобождения памяти, выделенной под элементы очереди
void clear(spis2*& begin, spis2*& end)
{
	while(begin)  // Пока очередь не пуста
	{
		if (is_empty(begin, end))  // Если очередь пуста, выходим из функции
			return;

		if (begin == end)  // Если в очереди остался только один элемент
		{
			delete begin;  // Освобождаем память, выделенную под этот элемент
			begin = nullptr;
			end = nullptr;
		}
		else  // Если в очереди больше одного элемента
		{
			spis2* t = begin;     // Временный указатель на начало очереди
			begin = begin->next;  // Переходим к следующему элементу в очереди
			begin->prev = nullptr;  // Обнуляем указатель prev у нового начала очереди
			delete t;             // Освобождаем память, выделенную под предыдущий начальный элемент
		}
	}
}

// Функция задания: удаление всех нечетных по значению элементов из очереди
void task(spis2*& begin, spis2*& end)
{
	spis2* t = begin;  // Указатель для итерации по очереди

	while(t)  // Пока не достигнут конец очереди (t не nullptr)
	{
		if(t->info % 2 == 1 || t->info % 2 == -1)  // Если значение текущего элемента нечетное
		{
			if (t == begin)  // Если текущий элемент - начало очереди
			{
				begin = begin->next;  // Перемещаем указатель начала на следующий элемент
				delete t;             // Удаляем текущий элемент
				t = begin;            // Обновляем указатель для итерации
				continue;             // Переходим к следующей итерации
			}

			if (t == end)  // Если текущий элемент - конец очереди
			{
				end = end->prev;      // Перемещаем указатель конца на предыдущий элемент
				end->next = nullptr;  // Обнуляем указатель next у нового конца очереди
				delete t;             // Удаляем текущий элемент
				break;                // Выходим из цикла
			}

			t->prev->next = t->next;  // Устанавливаем связь между предыдущим и следующим элементами от текущего
			t->next->prev = t->prev;  // Устанавливаем связь между следующим и предыдущим элементами от текущего
			spis2* t1 = t;            // Временный указатель на текущий элемент
			t = t->next;              // Переходим к следующему элементу в очереди
			delete t1;                // Удаляем текущий элемент
			continue;                 // Переходим к следующей итерации
		}
		t = t->next;  // Переходим к следующему элементу в очереди
	}
}

// Основная функция программы
int main()
{
	spis2* begin = nullptr, * end = nullptr;  // Инициализация указателей на начало и конец очереди
	int size = 9;  // Размер очереди

	for (int i = 0; i < size; i++)  // Цикл для добавления элементов в очередь
	{
		int add;
		std::cin >> add;          // Ввод элемента с клавиатуры
		add_begin(begin, end, add);  // Добавление элемента в начало очереди
	}
	
	print_begin(begin);  // Вывод элементов очереди с начала до изменений
	std::cout << '\n';
	task(begin, end);   // Выполнение задания: удаление всех нечетных элементов
	print_begin(begin);  // Вывод элементов очереди с начала после изменений

	clear(begin, end);   // Освобождение памяти, выделенной под элементы очереди

	return 0;  // Возврат из функции main
}
