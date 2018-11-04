// Write a function to determine whether the contents of a singly linked list are a palindrome. 
// Then, write a function to determine whether the contents of a doubly linked list are a palindrome. 
// Focus on yourfunction’s efficiency. 
// Defend your efficiency in your comments section.

// Jackie Adair
// CST-201
// Week 2 Individual Assignment
// This is my own code

#include <iostream>
#include <string>

using namespace std;

// The SLNode definition
class SLNode {
public:
	SLNode() {
		next = NULL;
	}

	SLNode(char value, SLNode *ptr = 0) {
		data = value;
		next = ptr;
		}
	char data;
	SLNode *next;
};
// The DLNode definition
class DLNode {
public:
	DLNode() {
		prev = NULL;
		next = NULL;
	}
	DLNode(char value, DLNode *prevPtr = 0, DLNode *nextPtr = 0) {
		data = value;
		prev = prevPtr;
		next = nextPtr;
	}
	char data;
	DLNode *prev;
	DLNode *next;
};

class SinglyLinkedList{
public:
	SinglyLinkedList() {
		head = 0;
		tail = 0;
	}

	void addSLNode(char value) {
		 // if tail is not null
		if (tail != 0) {
			 // Assign current SLNode next to the new SLNode
			tail->next = new SLNode(value);
			 // assign new SLNode as tail
			tail = tail->next;
		}
		else {
			head = tail = new SLNode(value);
		}
	}


	void printList() {
		SLNode *temp;
		temp = head;

		while (temp) {
			cout << " " << temp->data;
			temp = temp->next;
		}
		cout << endl;
	}

	 // passes pointer to "head".  Any SLNode in the list can be passed
	 // allows segments to be reversed or swapped
	void ReverseTheList(SLNode **start) {
		SLNode *prev = NULL;
		SLNode *ptr = *start, *temp;
		 // Make sure there are some SLNodes
		while (ptr) {
			temp = ptr->next;
			ptr->next = prev;
			prev = ptr;
			ptr = temp;
		}
		// what abou
		*start = prev;
	}

	bool IsSLLPalindrome() {
		if (head == NULL) {
			return true;
		}
		SLNode *p1, *p2;

		 // find mid using slow and fast iteration
		SLNode *mid = NULL;
		p1 = p2 = head;
		 // p2 moves at 2x the speed of p1 since its incrementer is doubled
		while (p2) {
			p2 = p2->next;
			if (p2) p2 = p2->next;
			if (p2) p1 = p1->next;
		}
		 // p1 is midway since it moved at half the speed of p2 
		 // when it reached the end of the list
		mid = p1;

		 // reverse the second half of the list after mid
		ReverseTheList(&(mid->next));

		bool isPal = true;
		p1 = head;
		p2 = mid->next;
		 // iterate through the modified list
		while (isPal == true && p2) {
			 // check for palindrome while iterating
			if (p1->data != p2->data) {
				isPal = false;
			}
			p1 = p1->next;
			p2 = p2->next;
		}

		// put the list back together.
		ReverseTheList(&(mid->next));

		return isPal;
	}
	
	SLNode *head, *tail;
};

class DoublyLinkedList {
public:
	DoublyLinkedList() {
		head = 0;
		tail = 0;
	}

	void addDLNode(char value) {
		// if tail is not null
		if (tail != 0) {
			DLNode *temp = tail;
			// Assign current DLNode next to the new SLNode
			tail->next = new DLNode(value);
			// assign new DLNode as tail
			tail = tail->next;
			tail->prev = temp;
		}
		else {
			head = tail = new DLNode(value);
		}
	}

	void printList() {
		DLNode *temp;
		temp = head;

		while (temp) {
			cout << " " << temp->data;
			temp = temp->next;
		}
		cout << endl;
	}

	bool IsDLLPalindrome() {
		bool isPal = true;
		DLNode *left = head;
		DLNode *right = tail;
		if (left == NULL) return true;

		 // iterate towards center comparing until they meet or isPal is false
		while (isPal && left != right) {
			if (left->data == right->data) {
				isPal = true;
				 // move the pointers
				left = left->next;
				right = right->prev;
			}
			else {
				isPal = false;
			}
		}
		return isPal;
	}


	DLNode *head, *tail;
};
int main() {
	SinglyLinkedList myList;
	SinglyLinkedList yourList;
	DoublyLinkedList thatList;
	DoublyLinkedList theirList;

	myList.addSLNode('R');
	myList.addSLNode('A');
	myList.addSLNode('R');
	yourList.addSLNode('R');
	yourList.addSLNode('A');
	yourList.addSLNode('D');
	thatList.addDLNode('J');
	thatList.addDLNode('A');
	thatList.addDLNode('J');
	theirList.addDLNode('J');
	theirList.addDLNode('A');
	theirList.addDLNode('K');

	cout << "Singly Linked List 'myList' = ";
	myList.printList();
	cout << "Singly Linked List 'yourList' = ";
	yourList.printList();
	cout << "Doubly Linked List 'thatList' = ";
	thatList.printList();
	cout << "Doubly Linked List 'theirList' = ";
	theirList.printList();

	if (myList.IsSLLPalindrome()) {
		cout << "\n'myList' IS Palindrome!";
	}
	else {
		cout << "\n'myList' is NOT Palindrome!";
	}

	if (yourList.IsSLLPalindrome()) {
		cout << "\n'yourList' IS Palindrome!";
	}
	else {
		cout << "\n'yourList' is NOT Palindrome!";
	}

	if (thatList.IsDLLPalindrome()) {
		cout << "\n'thatList' IS Palindrome!";
	}
	else {
		cout << "\n'thatList' is NOT Palindrome!";
	}

	if (theirList.IsDLLPalindrome()) {
		cout << "\n'theirList' IS Palindrome!";
	}
	else {
		cout << "\n'theirList' is NOT Palindrome!";
	}

//	cin.ignore();
	cin.get();
}