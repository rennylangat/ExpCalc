/*
Qipeng Liao and Xiaohang Yin
Assignemnet#4
02/10/2019
main.cpp : This file contains the 'main' function. Program execution begins and ends there.
Qipeng Liao did the check_priority function and conversion to prefix function
Xiaohang Yin did the conversion to postfix function and main function.
*/
#include <iostream>
#include <cstring>
#include<string>
#include<stack>
using namespace std;

class Calculator
{
	
	//Check if character is operator
	bool isOperator(char c)
	{
		return (!isalpha(c) && !isdigit(c));
	}
	
public:
	int check_priority(char ch)
	{
		switch (ch)
		{
		case '/':
			return 2;
		case '*':
			return 2;
		case '+':
			return 1;
		case '-':
			return 1;
		case '%':
			return 3;
		default:
			return 0;
		}
	}


public:
	string infixToPrefix(string infix)
	{
		stack<char> operators;
		stack<string> operands;
		for (size_t j = 0; j < infix.length(); j++)
		{
			if (infix[j] == '(')
			{
				operators.push(infix[j]);
			}
			else if (infix[j] == ')')
			{
				while (!operators.empty() && operators.top() != '(')
				{
					string op1 = operands.top();
					operands.pop();
					string op2 = operands.top();
					operands.pop();
					char op = operators.top();
					operators.pop();
					string tmp = op + op2 + op1;
					operands.push(tmp);
				}
				operators.pop();
			}
			else if (!isOperator(infix[j]))
			{
				operands.push(string(1, infix[j]));
			}
			else {
				while (!operators.empty() && check_priority(infix[j]) <= check_priority(operators.top()))
				{
					string op1 = operands.top();
					operands.pop();
					string op2 = operands.top();
					operands.pop();
					char op = operators.top();
					operators.pop();
					string tmp = op + op2 + op1;
					operands.push(tmp);
				}
				operators.push(infix[j]);
			}
		}
		while (!operators.empty())
		{
			string op1 = operands.top();
			operands.pop();

			string op2 = operands.top();
			operands.pop();
			char op = operators.top();
			operators.pop();
			string tmp = op + op2 + op1;
			operands.push(tmp);

		}
		return operands.top();
	}

public:
	void convert(char infix[], char postfix[], int size)
	{
		stack<char> obj;
		int priority, i, k;
		i = 0;
		k = 0;
		char ch;
		while (i < size)
		{
			ch = infix[i];
			if (ch == '(')
			{
				obj.push(ch);
				i++;
				continue;
			}
			if (ch == ')')
			{
				while (!obj.empty() && obj.top() != '(')
				{
					postfix[k++] = obj.top();
					obj.pop();
				}
				if (!obj.empty())
				{
					obj.pop();
				}
				i++;
				continue;
			}
			priority = check_priority(ch);
			if (priority == 0)
			{
				postfix[k++] = ch;
			}
			else
			{
				if (obj.empty())
				{
					obj.push(ch);
				}
				else
				{
					while (!obj.empty() && obj.top() != '('&&priority <= check_priority(obj.top()))
					{
						postfix[k++] = obj.top();
						obj.pop();
					}
					obj.push(ch);
				}
			}
			i++;
		}
		while (!obj.empty())
		{
			postfix[k++] = obj.top();
			obj.pop();
		}
		postfix[k] = 0;
	}


};

	int main() {
		Calculator obj;
		char infix[12];
		int size;

		cout << "\n++++++++++++++++++++++++++++++++++++++++++++++" << endl;
		cout << "**Program to convert infix expression to postfx**" << endl;
		cout << "\n++++++++++++++++++++++++++++++++++++++++++++++" << endl;
		cout << "Enter the Expression in infix format" << endl;
		cin >> infix;
		size = strlen(infix);
		char postfix[20];
		obj.convert(infix, postfix, size);
		cout << "\nGiven an infix expression " << infix << endl;
		cout << "\nThe Postfix Expression is: " << postfix << endl;
		cout << "\nThe prefix Expression is: " << obj.infixToPrefix(infix) <<endl;
		cin.ignore();
		cin.ignore();
		return 0;
	};
