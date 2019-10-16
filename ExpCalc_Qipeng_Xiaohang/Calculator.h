#ifndef CALCULATOR_H

#define  CALCULATOR_H

#include <iostream>
#include <cstring>
#include<stack>
using namespace std;

class Calculator
{
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
		case '$':
			return 3;
		default:
			return 0;
		}
	}
public:
	void convert(char infix[], char postfix[], int size)
	{
		stack<char> obj;
		int priority, i, k;
		i = 0;
		k = 0;
		char ch;
		while (i<size)
		{
			ch = infix[i];
			if (ch=='(')
			{
				obj.push(ch);
				i++;
				continue;
			}
			if (ch== ')')
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
			if (priority==0)
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
					while (!obj.empty()&&obj.top()!='('&&priority<=check_priority(obj.top()))
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

	cout <<"\n++++++++++++++++++++++++++++++++++++++++++++++"<<endl;
	cout << "**Program to convert infix expression to postfx**" << endl;
	cout << "\n++++++++++++++++++++++++++++++++++++++++++++++" << endl;
	cout << "Enter the Expression in infix format" << endl;
	cin >> infix;
	size = strlen(infix);
	char postfix[20];
	obj.convert(infix, postfix, size);
	cout <<"\nGiven an infix expression " << infix << endl;
	cout << "\nThe Postfix Expression is: " << postfix << endl;

};
#endif
#pragma once
