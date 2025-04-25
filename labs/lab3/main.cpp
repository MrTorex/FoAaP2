
#include "stack.h"
#include "checked_input.h"
#include <iostream>
#include <string>

void get_expression(std::string& expression);
void convert_to_ppn(const std::string& expression, std::string& ppn);
short unsigned check_operators_stack(stack<char>& stack);
short unsigned get_priority_of_operator(char operator_to_check);
long double count_result(const std::string& ppn, double a, double b, double c, double d, double e);
void get_values(double& a, double& b, double& c, double& d, double& e);

void get_expression(std::string& expression)
{
    std::cout << "Enter your expression: ";
    std::getline(std::cin, expression);
}

void get_values(double& a, double& b, double& c, double& d, double& e)
{
    std::cout << "Enter a: ";
    checked_input(a);

    std::cout << "Enter b: ";
    checked_input(b);

    std::cout << "Enter c: ";
    checked_input(c);

    std::cout << "Enter d: ";
    checked_input(d);

    std::cout << "Enter e: ";
    checked_input(e);
}


void convert_to_ppn(const std::string& expression, std::string& ppn)
{
    const std::string operators = "+-*/(", operators_first_priority = "*/", operators_second_priority = "+-";

    stack<char> stack;

	for (const char it : expression)
	{
		if (operators.find(it) != std::string::npos)
        {
            const short unsigned priority = get_priority_of_operator(it);

            if (it == '(')
                stack.push(it);

            else if (stack.is_empty() || priority > get_priority_of_operator(stack.peek()))
                stack.push(it);

            else
            {
                while (!stack.is_empty() && get_priority_of_operator(stack.peek()) >= priority)
                {
                    ppn += stack.peek();
                    stack.pop();
                }

                if (stack.is_empty() || priority > get_priority_of_operator(stack.peek()))
                    stack.push(it);
            }
        }

        else if (it == ')')
        {
            while (stack.peek() != '(')
            {
                ppn += stack.peek();
                stack.pop();
            }
            stack.pop();
        }

        else
            ppn += it;
	}

    while (!stack.is_empty())
    {
        ppn += stack.peek();
        stack.pop();
    }
}

short unsigned get_priority_of_operator(const char operator_to_check)
{
    const std::string operators_first_priority = "*/", operators_second_priority = "+-";

    if (operators_first_priority.find(operator_to_check) != std::string::npos)
        return 3;

    if (operators_second_priority.find(operator_to_check) != std::string::npos)
        return 2;

    return 1;
}

long double count_result(const std::string& ppn, const double a, const double b, const double c, const double d, const double e)
{
    stack<long double> stack;

    for (const char it : ppn)
    {
	    if (it >= 97 && it <= 101)
	    {
		    switch (it)
		    {
		    case 97:
                stack.push(a);
                break;
		    case 98:
                stack.push(b);
                break;
		    case 99:
                stack.push(c);
                break;
		    case 100:
                stack.push(d);
                break;
		    case 101:
                stack.push(e);
                break;
		    }
            continue;
	    }

        long double to_push_element = 0;

	    switch (it)
	    {
	    case '+':
            to_push_element = stack.peek();
            stack.pop();
            to_push_element += stack.peek();
            stack.pop();
            break;
        case '-':
            to_push_element = stack.peek();
            stack.pop();
            to_push_element = stack.peek() - to_push_element;
            stack.pop();
            break;
        case '*':
            to_push_element = stack.peek();
            stack.pop();
            to_push_element *= stack.peek();
            stack.pop();
            break;
        case '/':
            to_push_element = stack.peek();
            stack.pop();
            to_push_element = stack.peek() / to_push_element;
            stack.pop();
            break;
        }

        stack.push(to_push_element);
    }

    const long double to_return = stack.peek();

    stack.delete_stack();

    return to_return;
}

int main()
{
    std::string expression, ppn;

    double a, b, c, d, e;

    get_expression(expression);

    get_values(a, b, c, d, e);

    expression.erase(std::remove_if(expression.begin(), expression.end(), isspace), expression.end());

    convert_to_ppn(expression, ppn);

    std::cout << "Your expression in PPN: " << ppn << '\n';

    std::cout << "Result: " << count_result(ppn, a, b, c, d, e);

    return 0;
}