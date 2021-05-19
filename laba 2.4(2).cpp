// laba 2.4(2).cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
/*Реалізувати перевід рядка у expression tree (змінні, дійсні числа, операції +,-
,*,/. Символьно продиференціювати вираз по вибраній змінній та вивести на
екран строку-результат.*/
#include <iostream>
#include <stack>
using namespace std;
#define COUNT 20

struct expr
{
	char exp;
	expr* right;
	expr* left;
};

bool IsOperator(char op)
{
	if (op == '+' || op == '/' || op == '*' || op == '-')
	{
		return true;
	}
	return false;
}

int Prior(char op)
{
	if (op == '+' || op == '/') return 1;
	if (op == '*' || op == '-') return 1;
	if (op >= '0' || op <= '9') return 2;
	if (op >= 'a' || op <= 'z') return 3;
}

int OperationPrior(char op)
{
	if (op == '+' || op == '/') return 1;
	if (op == '*' || op == '-') return 2;
}

void Print(expr* tree)
{
	if (tree != NULL)
	{
		Print(tree->left);
		cout << tree->exp;
		Print(tree->right);
	}
}

expr* New(expr*& tree, char exp)
{
	int flag = Prior(exp);
	if (!tree)
	{
		tree = new expr;
		tree->exp = exp;
		tree->left = NULL;
		tree->right = NULL;
	}
	else if (flag == 2 || flag == 3)
	{
		if (tree->left == NULL)
		{

			New(tree->left, exp);
		}
		else
		{
			New(tree->right, exp);
		}
	}
	else if (flag == 1)
	{
		OperationPrior(exp);
		if (!tree)
		{
			tree = new expr;
			tree->exp = exp;
			tree->left = NULL;
			tree->right = NULL;
		}
		else if (tree->left == NULL)
		{
			New(tree->left, exp);
		}
		else
		{
			New(tree->right, exp);
		}
	}
	return tree;
}

double f(double x)
{
	return 5 * x + 3 - 2 * x;
}

int main()
{
	char data[10] = "5*x+3-2*x";
	cout << "Expression: 5*x+3-2*x";
	cout << endl;
	expr* tree = NULL;
	for (int i = 0; i < sizeof(data); i++)
	{
		New(tree, data[i]);
	}

	cout << "Expression tree: ";
	Print(tree);

	cout << endl;
	expr* tr = NULL;
	cout << "Derivative of an expression: ";
	double h = 0.1, x = 3;
	double fc = (f(x + h) - f(x - h)) / (2 * h); 
	cout << fc;
}