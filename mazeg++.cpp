// week4.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Jackie Adair
// CST-201
// Week 4 Assignment
// This is my own work
//
// #include "pch.h"
#include <cstdlib>
#include <iostream>
#include <stack>
#include <queue>
#include <fstream>
#include <vector>
#include <deque>
// #include <Windows.h>

// Node declaration/definition
class DLNode {
public:
	DLNode() {
		prev = NULL;
		next = NULL;
	}

	DLNode(char passed, DLNode *prevPtr = 0, DLNode *nextPtr = 0) {
		if (passed != 'X') {
			cell[1][1] = passed;
		}
		else {
			for (int i = 0; i < 3; i++)
				for (int j = 0; j < 3; j++)
					cell[i][j] = 'X';
		}
		prev = prevPtr;
		next = nextPtr;
	}


	DLNode *prev;
	DLNode *next;
	DLNode *mzUp;
	DLNode *mzDown;
	DLNode *mzLeft;
	DLNode *mzRight;

	char cell[3][3] = { {' ',' ',' '}, {' ',' ',' '},{' ',' ',' '} };
	int nodeX, nodeY;
	bool visited, backTrack;
	bool up = true;
	bool right = true;
	bool down = true;
	bool left = true;
	int mzCellNum = 0;
};


// The list that holds the maze data
class DoublyLinkedList {
public:
	DoublyLinkedList() {
		head = 0;
		tail = 0;
	}
	DoublyLinkedList(int row, int col) {
		head = 0;
		tail = 0;
		sizeRow = row;
		sizeCol = col;
	}

	// Adds a node to the list.
	void addDLNode(char data, int x, int y, int cellNum) {
		// If there are nodes, point at the end
		if (tail != 0) {
			DLNode *temp = tail;
			// Create the new node with passed data. Point at it with tail->next
			tail->next = new DLNode(data);
			// Point tail at that new node
			tail = tail->next;
			// Point that node's prev at the current node
			tail->prev = temp;
			// update x,y of the new node
			tail->nodeX = x;
			tail->nodeY = y;
			// update cell number
			tail->mzCellNum = cellNum;
		}
		else {
			// The list is empty, create a new node and point head/tail at it
			head = tail = new DLNode(data);
			// update x,y of the new node
			head->nodeX = x;
			head->nodeY = y;
			head->mzCellNum = cellNum;
		}
	}

	// Updates the contents of node x,y with passed data.
	// All except 'X' are updated in element 1,1.  X causes all
	// elements to be updated
	void updateDLNode(char data, int x, int y) {
		DLNode *temp = head;

		// Iterate through the list
		while (temp) {
			// Find the node with the passed x,y
			if (temp->nodeX == x && temp->nodeY == y) {
				// Update the node based on passed data.(all X or 1,1 element)
				if (data != 'X') temp->cell[1][1] = data;
				else {
					for (int i = 0; i < 3; i++) {
						for (int j = 0; j < 3; j++) {
							temp->cell[i][j] = data;
						}
					}
				}
			}
			temp = temp->next;
		}
	}

	void updateVisited(bool visit, int x, int y) {
		DLNode *temp = head;

		// Iterate through the list
		while (temp) {
			// Find the node with the passed x,y
			if (temp->nodeX == x && temp->nodeY == y) {
				// Update the node
				temp->visited = visit;
			}
			temp = temp->next;
		}
	}

	void updateBackTrack(bool back, int x, int y) {
		DLNode *temp = head;

		// Iterate through the list
		while (temp) {
			// Find the node with the passed x,y
			if (temp->nodeX == x && temp->nodeY == y) {
				// Update the node
				temp->backTrack = back;
			}
			temp = temp->next;
		}
	}
	void updateValidMovementDirections(int rowSize, int colSize) {
		DLNode *temp = head;
		DLNode *point = temp;
		int cellNum = 1;

		// Iterate through the list
		while (temp) {
			// assign mzUp to cell above it
			if (cellNum > rowSize) {
				for (int i = 1; i < rowSize; i++) {
					point = point->prev;
				}
				temp->mzUp = point;
				point = temp;
			}
			else {
				temp->mzUp = nullptr;
				temp->up = false;
				point = temp;
			}

			// mzDown
			if (cellNum <= rowSize * colSize - (rowSize)) {
				for (int i = 1; i < rowSize + 1; i++) {
					point = point->next;
				}
				temp->mzDown = point;
				point = temp;
			}
			else {
				temp->mzDown = nullptr;
				temp->down = false;
				point = temp;
			}

			// mzRight

			if ((cellNum % rowSize > 0)) {
				temp->mzRight = temp->next;
			}
			else {
				temp->mzRight = nullptr;
				temp->right = false;
			}

			// mzLeft
			if (cellNum % rowSize != 1) {
				temp->mzLeft = temp->prev;;
			}
			else {
				temp->mzLeft = nullptr;
				temp->left = false;
			}

			temp = temp->next;
			cellNum++;
			//std::cout << std::endl << cellNum;
		}

	}

	// This function iterates through each row of the arrays 
	// in the nodes of each row and outputs them one at at time.
	void printNodes() {

		system("clear");
		std::cout << std::endl << std::endl;
		// Add numerical header to displayed grid
		std::cout << "   ";
		for (int i = 0; i < sizeCol; i++) {
			if (i < 10) {
				std::cout << "  " << i << "   ";
			}
			else {
				std::cout << "  " << i << "  ";
			}
		}

		// Create pointers for row and temp
		DLNode *rowPtr = head;
		int rowNodeCount, colNodeCount;
		DLNode *temp = head;

		// Which node on the row are we at.  Used for condition check
		rowNodeCount = 0;
		while (rowNodeCount < sizeRow && temp != NULL) {
			// iterate the row of the nodes array
			for (int i = 0; i < 3; i++) {
				std::cout << std::endl;

				// Add row count to first column
				if (i == 1) {
					if (rowNodeCount < 10) { std::cout << rowNodeCount << "  "; }
					else { std::cout << rowNodeCount << " "; }
				}
				else { std::cout << "   "; }
				// Move temp to the 1st node of the current row
				temp = rowPtr;
				colNodeCount = 0;
				// print the cells
				while (colNodeCount < sizeCol) {
					for (int j = 0; j < 3; j++) {
						if (!temp->visited && !temp->backTrack) {
							std::cout << temp->cell[i][j] << " ";
						}
						else if (temp->visited && !temp->backTrack) {
							if (i == 1)
							{
								if (j == 1)
									std::cout << "*" << " ";
								else
									std::cout << " " << " ";
							}
							else {
								std::cout << temp->cell[i][j] << " ";

							}
						}
						else if (temp->visited && temp->backTrack) {
							if (i == 1) {
								if (j == 1)
									std::cout << "*" << " ";
								else
									std::cout << " " << " ";
							}
							else
							{
								if (j == 1)
									std::cout << "=" << " ";
								else
									std::cout << " " << " ";
							}
						}

					}
					colNodeCount++;
					// Move temp forward if it is not tail/NULL otherwise
					if (temp != tail)
						temp = temp->next;
					else
						temp = NULL;
				}
			}
			colNodeCount = 0;
			// Move the rowPtr to the first node after sizeCol
			// This simulates the next row of the Maze.
			rowPtr = temp;
			rowNodeCount++;
		}
	}

	// This function iterates through each row of the arrays 
	// in the nodes of each row and outputs them one at at time.
	void writeNodes() {
		std::ofstream outFile;
		outFile.open("outputFile");

		// Add numerical header to displayed grid
		outFile << "   ";
		for (int i = 0; i < sizeCol; i++) {
			if (i < 10) {
				outFile << "  " << i << "   ";
			}
			else {
				outFile << "  " << i << "  ";
			}
		}

		// Create pointers for row and temp
		DLNode *rowPtr = head;
		int rowNodeCount, colNodeCount;
		DLNode *temp = head;

		// Which node on the row are we at.  Used for condition check
		rowNodeCount = 0;
		while (rowNodeCount < sizeRow && temp != NULL) {
			// iterate the row of the nodes array
			for (int i = 0; i < 3; i++) {
				outFile << std::endl;

				// Add row count to first column
				if (i == 1) {
					if (rowNodeCount < 10) { outFile << rowNodeCount << "  "; }
					else { outFile << rowNodeCount << " "; }
				}
				else { outFile << "   "; }

				// Move temp to the 1st node of the current row
				temp = rowPtr;
				colNodeCount = 0;
				while (colNodeCount < sizeCol) {
					for (int j = 0; j < 3; j++) {
						outFile << temp->cell[i][j] << " ";
					}
					colNodeCount++;
					// Move temp forward if it is not tail/NULL otherwise
					if (temp != tail)
						temp = temp->next;
					else
						temp = NULL;
				}
			}
			colNodeCount = 0;
			// Move the rowPtr to the first node after sizeCol
			// This simulates the next row of the Maze.
			rowPtr = temp;
			rowNodeCount++;
		}
		outFile.close();
	}

	// utilize a queue to perform a breadth first search
	void BreadthFirstSolution() {
		std::queue <int> solutionQueue;
		std::deque <int> queueDisplay;
		DLNode *temp = head;
		DLNode *currentNode = head;
		int gameMode = 1;
		this->printNodes();

		// loop until event occurs (0 lose, 2 win)
		while (gameMode == 1) {
			// set the current node to visited
			currentNode->visited = 1;

			// check Up for a node
			if (currentNode->up) {
				// check for valid move
				if (currentNode->mzUp->visited == false && currentNode->mzUp->cell[1][1] != 'X') {
					// push mzUp cell number to queue
					solutionQueue.push(currentNode->mzUp->mzCellNum);
					// push this cell number to vector for queue display
					queueDisplay.push_back(currentNode->mzUp->mzCellNum);
				}
			}

			// check Right for a node <see above for comments>
			if (currentNode->right) {
				if (currentNode->mzRight->visited == false && currentNode->mzRight->cell[1][1] != 'X') {
					solutionQueue.push(currentNode->mzRight->mzCellNum);
					queueDisplay.push_back(currentNode->mzRight->mzCellNum);
				}
			}

			// check Down for a node <see above for comments>
			if (currentNode->down) {
				if (currentNode->mzDown->visited == false && currentNode->mzDown->cell[1][1] != 'X') {
					solutionQueue.push(currentNode->mzDown->mzCellNum);
					queueDisplay.push_back(currentNode->mzDown->mzCellNum);
				}
			}

			// check Left for a node <see above for comments>
			if (currentNode->left) {
				if (currentNode->mzLeft->visited == false && currentNode->mzLeft->cell[1][1] != 'X') {
					solutionQueue.push(currentNode->mzLeft->mzCellNum);
					queueDisplay.push_back(currentNode->mzLeft->mzCellNum);
				}
			}

			// Check the queue.  If empty, game over
			if (solutionQueue.empty()) {
				gameMode = 0;
			}
			// Output the Queue while running.
			std::cout << std::endl << "Queue: ";
			std::deque <int> ::iterator it;
			for (it = queueDisplay.begin(); it != queueDisplay.end(); ++it) {
				std::cout << " < " << *it;
			}

			this->printNodes();
			// if the queue is empty, bypass all of this and end game
			if (!solutionQueue.empty()) {
				// set current cell number to next number in queue
				int curCell = solutionQueue.front();

				// bool to keep from having to iterate the entire list
				bool jump = true;
				// loop until find cell num in the list and set it as current node
				while (jump) {
					if (temp->mzCellNum == curCell) {
						currentNode = temp;
						jump = false;
					}
					temp = temp->next;
				}
				// reset temp back to head
				temp = head;
				// remove that cell from the queue's display
				queueDisplay.pop_front();
				// pop the queue
				solutionQueue.pop();

				// if winner.  set gamemode
				if (currentNode->cell[1][1] == 'F') {
					gameMode = 2;
				}
			}
		}

		// if gamemode 0 lose
		if (gameMode == 0) {
			std::cout << std::endl << "Game Over.  There is no path through the maze" << std::endl;
		}
		// else if gamemode = 2 win
		else if (gameMode == 2) {
			std::cout << std::endl << "Game Over.  Path Found!" << std::endl;
		}
		else {
			std::cout << std::endl << "GAME OVER.  Something Broke!" << std::endl;
		}

	}

	// utilize a stack to perform a depth first search
	void DepthFirstSolution() {
		std::stack <int> solutionStack;
		std::vector <int> stackDisplay;
		DLNode *temp = head;
		DLNode *currentNode = head;
		int gameMode = 1;
		int deadEnd = 0;
		this->printNodes();

		// loop until event occurs (0 lose, 2 win)
		while (gameMode == 1) {
			// set the current node to visited
			currentNode->visited = 1;

			// check Up for a node
			if (currentNode->up) {
				// check for valid move
				if (currentNode->mzUp->visited == false && currentNode->mzUp->cell[1][1] != 'X') {
					// push this cell number to stack
					solutionStack.push(currentNode->mzCellNum);
					// push this cell number to vector for stack display
					stackDisplay.push_back(currentNode->mzCellNum);
					// move to valid cell
					currentNode = currentNode->mzUp;
					// check for finish line
					if (currentNode->cell[1][1] == 'F') { gameMode = 2; }
				}
				// set current cells up flag to false if up is not a good move
				else { currentNode->up = false; }
			}

			// check Right for a node <see above for comments>
			else if (currentNode->right) {
				if (currentNode->mzRight->visited == false && currentNode->mzRight->cell[1][1] != 'X') {
					solutionStack.push(currentNode->mzCellNum);
					stackDisplay.push_back(currentNode->mzCellNum);
					currentNode = currentNode->mzRight;
					if (currentNode->cell[1][1] == 'F') { gameMode = 2; }
				}
				else { currentNode->right = false; }
			}

			// check Down for a node <see above for comments>
			else if (currentNode->down) {
				if (currentNode->mzDown->visited == false && currentNode->mzDown->cell[1][1] != 'X') {
					solutionStack.push(currentNode->mzCellNum);
					stackDisplay.push_back(currentNode->mzCellNum);
					currentNode = currentNode->mzDown;
					if (currentNode->cell[1][1] == 'F') { gameMode = 2; }
				}
				else { currentNode->down = false; }
			}

			// check Left for a node <see above for comments>
			else if (currentNode->left) {
				if (currentNode->mzLeft->visited == false && currentNode->mzLeft->cell[1][1] != 'X') {
					solutionStack.push(currentNode->mzCellNum);
					stackDisplay.push_back(currentNode->mzCellNum);
					currentNode = currentNode->mzLeft;
					if (currentNode->cell[1][1] == 'F') { gameMode = 2; }
				}
				else { currentNode->left = false; }
			}

			// if no valid node or move
			if (!currentNode->up && !currentNode->right && !currentNode->down && !currentNode->left) {
				// if the stack is empty, there is no solution end game
				if (solutionStack.empty()) {
					gameMode = 0;
				}
				else {
					// set current node backTrack flag
					currentNode->backTrack = true;
					// get previous cell nubmer from stack
					int curCell = solutionStack.top();
					// bool to keep from having to iterate the entire list
					bool jump = true;
					// loop until find cell num in the list and set it as current node
					// pretty much, just go to the top node of the list in the stack
					while (jump) {
						if (temp->mzCellNum == curCell) {
							currentNode = temp;
							jump = false;
						}
						temp = temp->next;
					}
					// reset temp back to head
					temp = head;
					// pop the stack
					solutionStack.pop();
					// remove that cell from the stack display
					stackDisplay.pop_back();
					// set the current node backtrack since we've moved back a cell.
					currentNode->backTrack = true;
				}
			}
			std::cout << std::endl << "Solution Path: ";
			int iter;
			for (std::vector<int>::const_iterator iter = stackDisplay.begin(); iter != stackDisplay.end(); ++iter)
				std::cout << *iter << " ";
			this->printNodes();
		}

		// if gamemode 0 lose
		if (gameMode == 0) {
			std::cout << std::endl << "Game Over.  There is no path through the maze" << std::endl;
		}
		// else if gamemode = 2 win
		else if (gameMode == 2) {
			std::cout << std::endl << "Game Over.  Path Found!" << std::endl;
		}
		else {
			std::cout << std::endl << "GAME OVER.  Something Broke!" << std::endl;
		}

	}

	DLNode *head, *tail;
	int sizeRow, sizeCol;
};



int main() {
	using namespace std;

	cout << "Maximize this window if necessary, then Press Enter to start...";
	cin.get();

	int rowSize, colSize;
	int startRow, startCol;
	int finishRow, finishCol;
	int wallRow, wallCol;

	// Open and read size and start/finish positions from inputfile
	ifstream myFile;
	myFile.open("inputFile");
	if (!myFile) { cout << "Bad File"; }
	myFile >> colSize >> rowSize;
	myFile >> startRow >> startCol >> finishRow >> finishCol;

	// error check the file input
	if (colSize < 0 || rowSize < 0 || startCol < 0 ||
		startCol > colSize || startRow < 0 || startRow > rowSize ||
		finishCol < 0 || finishCol > colSize || finishRow < 0 || finishRow > rowSize) {
		cout << "There was an error!  Check file contents."
			<< "One of the input numbers is out of range."
			<< endl << "File input checked: Size, Start, and Finish Coordinates."
			<< endl;
		return 1;
	}

	// Create a Doubly Linked List with default content: "."'s
	DoublyLinkedList* maze = new DoublyLinkedList(rowSize, colSize);
	int cellNum = 1;
	for (int i = 0; i < rowSize; i++) {
		for (int j = 0; j < colSize; j++) {
			maze->addDLNode(' ', i, j, cellNum);
			cellNum++;
		}
	}

	// update the start and finish coordinages in the list
	// passes the node coordinates(on a grid) to the function to find the node
	maze->updateDLNode('S', startRow, startCol);
	maze->updateDLNode('F', finishRow, finishCol);



	// UpdateCells to walls based on inputFile data
	for (int h = 0; h < 79; h++) {
		myFile >> wallCol >> wallRow;

		// error check the file input
		if (wallCol < 0 || wallCol > colSize || wallRow < 0 || wallRow > rowSize) {
			cout << "There was an error!  Check file contents."
				<< "One of the input numbers is out of range."
				<< endl << "File input checked: Wall Cordinates."
				<< endl;
			return 1;
		}
		maze->updateDLNode('X', wallRow, wallCol);
	}
	myFile.close();

	// update the lists valid movements per cell
	maze->updateValidMovementDirections(colSize, rowSize);

	// run stack solver (Depth First)
	//maze->DepthFirstSolution();

	// run stack solver (Breadth First)
	maze->BreadthFirstSolution();

	// Press a key
	cout << endl << "Press <Enter> to continue..." << endl;
	cin.get();

	return 0;
}