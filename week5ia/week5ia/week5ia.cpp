// 6.14.4 - Design an algorithm to test whether a binary tree is a binary search tree.
//          This algorithm is located in the file: bstTest.docx
// 6.14.10. Write a function to create a mirror of a binary tree.
//			This function is also listed in bstTest.docx
// 6.14.16. Apply the function balance() to the English alphabet to create a balanced tree.
//			This algorithm and diagram are in bstTest.docx
// 6.15.1.  Write a program that accepts an arithmetic expression written in prefix (Polish) 
//          notation, builds an expression tree, and then traverses the tree to evaluate the 
//          expression. The evaluation should start after a complete expression has been entered.

#include "pch.h"
#include <iostream>
#include <cstdlib>

using namespace std;

// Nodes for the Trees
class Node
{
public:
	char info;
	Node* left;
	Node* right;

	Node(char key)  // Constructor
	{
		info = key;
		left = NULL;
		right = NULL;
	}
};

//  Creates stack
class ExpTreeStack
{
public:
	Node* head;
	ExpTreeStack* next;

	ExpTreeStack(Node* ptr)
	{
		head = ptr;
		next = NULL;
	}
};

// The tree to store the expression
class ExpressionTree
{
private:
	ExpTreeStack* top;  // top of the stack

public:
	ExpressionTree()
	{
		top = NULL;
	}

	// push Passed node into the Stack
	void push(Node* ptr)
	{
		if (top == NULL) // does the stack exist
		{
			top = new ExpTreeStack(ptr);
		}
		else
		{   // push the top node down the stack, then assign the new node as top.
			ExpTreeStack *nxtPtr = new ExpTreeStack(ptr);
			nxtPtr->next = top;
			top = nxtPtr;
		}
	}

	// pop the stack
	Node* pop()
	{
		if (top == NULL)  // is there a stack?
		{
			cout << "There are no nodes to pop!";
		}
		else
		{   // return/remove top, move next into top

			Node* ptr = top->head;
			top = top->next;
			return ptr;
		}
	}
	
	// insert values into the stack using stack functions (push)
	// passed string from user input
	void createTree(string passedVal)
	{
		// iterated downward through the string as a char array
		for (int i = passedVal.length() - 1; i >= 0; i--)
		{
			// if the element contains a number
			if (passedVal[i] >= '0' && passedVal[i] <= '9')
			{
				Node* nxtPtr = new Node(passedVal[i]); // create new node with it
				push(nxtPtr); // push to the stack
			}
			// if the element contains an operator
			else if (passedVal[i] == '+' || passedVal[i] == '-' ||
				passedVal[i] == '*' || passedVal[i] == '/')
			{
				Node* nxtPtr = new Node(passedVal[i]); // create a new node with it
				nxtPtr->left = pop(); //pop the stack to the left
				nxtPtr->right = pop(); // pop the stack to the right
				push(nxtPtr); // push this node to the stack
			}
			else
			{
				cout << "Malformed expression.  Polish Form dictates operators before operands:";
				return;
			}
		}
	}

	// run evaluate using head node if none is passed
	double evaluate()
	{
		return evaluate(top->head);
	}

	// evaluate the EpressionTree and return a value
	double evaluate(Node* ptr)
	{
		// empty tree
		if (ptr->left == NULL && ptr->right == NULL)
		{
			return (ptr->info) - '0';
		}
		else
		{
			double result = 0.0;
			double left = evaluate(ptr->left); // evaluate the left branches recursively
			double right = evaluate(ptr->right); // evaluate the right branches recursively
			char symbol = ptr->info; // assign the nodes value (info)
			// which operation to perform
			switch (symbol) 
			{
			case '+':
				result = left + right;
				break;
			case '-':
				result = left - right;
				break;
			case '*':
				result = left * right;
				break;
			case '/':
				result = left / right;
				break;
			default:
				result = left + right;
				break;
			}
			return result;
		}
	}
};

int main()
{
	char choice;

	do
	{	
		cout << "Expression Tree (Single Digits Only) -- Q)uit || E)valuate --";
		cin >> choice;
		choice = toupper(choice);
		switch (choice)
		{
		case('E'):
			char s[10];

			ExpressionTree et;
			cout << endl << "Enter a Polish Form Equation: ";
			cin >> s;
			et.createTree(s);
			cout << endl << endl << "Result: " << et.evaluate() << endl << endl;
			break;
		}
	} while (choice != 'Q');
	return 0;
}