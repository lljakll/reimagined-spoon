// Jackie Adair
// CST-201
// Week 7 Assignment
// This is my own work
//
#include "pch.h"
#include <cstdlib>
#include <iostream>
#include <stack>
#include <queue>
#include <fstream>
#include <vector>
#include <deque>
#include <sstream>
#include <Windows.h>
#include <chrono>
#include <thread>

// *************DECLARATIONS*********************************************************

class Node {
public:
	Node() {
		prev = NULL;
		next = NULL;
	}

	Node(char passed, Node *prevPtr = 0, Node *nextPtr = 0) {
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
	

	Node *prev;
	Node *next;
	Node *mzUp;
	Node *mzDown;
	Node *mzLeft;
	Node *mzRight;

	char cell[3][3] = { {' ',' ',' '}, {' ',' ',' '},{' ',' ',' '} };
	int nodeX, nodeY;
	bool visited, backTrack;
	bool up = true;
	bool right = true;
	bool down = true;
	bool left = true;
	int mzCellNum = 0;
	int manhattanDistanceToFinish = 0;
};

class DoublyLinkedList {
public:
	DoublyLinkedList();
	DoublyLinkedList(int row, int col);

	Node *head, *tail;
	int numRows, numCols;
};

//Add node to the List
void AddNode(DoublyLinkedList* maze, char data, int x, int y, int cellNum);
//Update node type and coords
void UpdateNode(DoublyLinkedList* maze, char data, int x, int y);
// check for valid moves
void UpdateValidMovementDirections(DoublyLinkedList* maze, int rowSize, int colSize);
// utilize a queue to perform a breadth first search
void BreadthFirstSolution(DoublyLinkedList* maze);
// utilize a stack to perform a depth first search
void DepthFirstSolution(DoublyLinkedList* maze);
// Create the string stream for output
std::string CreateStringStream(DoublyLinkedList* tempList, int numRows, int numCols);
// Update the Screen
std::string BufferedScreenUpdate(std::string currentScreen, std::string newScreen);
// Set the cursor postion(helper) only useful in windows.
void setCursorPosition(int x, int y);
// Read all of the data from the file
DoublyLinkedList ReadFileInputToList();
// Game Start menu
void StartGame();



//***************Fixed Def's*********************************************************

DoublyLinkedList::DoublyLinkedList() {
	head = 0;
	tail = 0;
}

DoublyLinkedList::DoublyLinkedList(int row, int col) {
	head = 0;
	tail = 0;
	numRows = row;
	numCols = col;
}

void AddNode(DoublyLinkedList* maze, char data, int x, int y, int cellNum) {
	// If there are nodes, point at the end
	if (maze->tail != 0) {
		Node *temp = maze->tail;
		// Create the new node with passed data. Point at it with tail->next
		maze->tail->next = new Node(data);
		// Point tail at that new node
		maze->tail = maze->tail->next;
		// Point that node's prev at the current node
		maze->tail->prev = temp;
		// update x,y of the new node
		maze->tail->nodeX = x;
		maze->tail->nodeY = y;
		// update cell number
		maze->tail->mzCellNum = cellNum;
	}
	else {
		// The list is empty, create a new node and point head/tail at it
		maze->head = maze->tail = new Node(data);
		// update x,y of the new node
		maze->head->nodeX = x;
		maze->head->nodeY = y;
		maze->head->mzCellNum = cellNum;
	}
}

void UpdateNode(DoublyLinkedList* maze, char data, int x, int y) {
	Node *temp = maze->head;

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

void UpdateValidMovementDirections(DoublyLinkedList* maze, int rowSize, int colSize) {
	Node *temp = maze->head;
	Node *point = temp;
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

void BreadthFirstSolution(DoublyLinkedList *maze) {
	std::queue <int> solutionQueue;
	std::deque <int> queueDisplay;
	Node *temp = maze->head;
	Node *currentNode = maze->head;
	int gameMode = 1;
	std::string prevScreen = "";
	std::string currScreen = "";

	currScreen = CreateStringStream(maze, maze->numRows, maze->numCols);
	prevScreen = BufferedScreenUpdate(currScreen, prevScreen);


	// loop until event occurs (0 lose, 2 win)
	while (gameMode == 1) {
		// sleep for .2 seconds
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
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
		setCursorPosition(0, 2);
		std::cout << "Queue: ";
		std::deque <int> ::iterator it;
		for (it = queueDisplay.begin(); it != queueDisplay.end(); ++it) {
			std::cout << " < " << *it;
		}
		std::cout << "                                                                            ";
		// redraw the screen after updates to currScreen
		currScreen = CreateStringStream(maze, maze->numRows, maze->numCols);
		prevScreen = BufferedScreenUpdate(currScreen, prevScreen);

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
			temp = maze->head;
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

	setCursorPosition(0, 4);

	// if gamemode 0 lose
	if (gameMode == 0) {
		std::cout << std::endl << "Game Over.  There is no path through the maze";
	}
	// else if gamemode = 2 win
	else if (gameMode == 2) {
		std::cout << "Game Over. Path Found! Press Enter";
		std::cin.ignore();
		std::cin.get();
	}
	else {
		std::cout << "GAME OVER.  Something Broke!";
	}

}

void DepthFirstSolution(DoublyLinkedList* maze) {
	std::stack <int> solutionStack;
	std::vector <int> stackDisplay;
	Node *temp = maze->head;
	Node *currentNode = maze->head;
	int gameMode = 1;
	int deadEnd = 0;
	std::string prevScreen = "";
	std::string currScreen = "";

	currScreen = CreateStringStream(maze, maze->numRows, maze->numCols);
	prevScreen = BufferedScreenUpdate(currScreen, prevScreen);

	// loop until event occurs (0 lose, 2 win)
	while (gameMode == 1) {

		// sleep for .2 seconds
		std::this_thread::sleep_for(std::chrono::milliseconds(100));

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
				temp = maze->head;
				// pop the stack
				solutionStack.pop();
				// remove that cell from the stack display
				stackDisplay.pop_back();
				// set the current node backtrack since we've moved back a cell.
				currentNode->backTrack = true;
			}
		}

		// output the stack while running
		setCursorPosition(0, 2);
		std::cout << "Solution Path: ";
		for (std::vector<int>::const_iterator iter = stackDisplay.begin(); iter != stackDisplay.end(); ++iter)
		{
			std::cout << *iter << " ";
		}
		std::cout << "                                                                             ";

		// redraw the screen after updates to currScreen
		currScreen = CreateStringStream(maze, maze->numRows, maze->numCols);
		prevScreen = BufferedScreenUpdate(currScreen, prevScreen);

	}
	setCursorPosition(0, 4);

	// if gamemode 0 lose
	if (gameMode == 0) {
		std::cout << "Game Over.  There is no path through the maze";
	}
	// else if gamemode = 2 win
	else if (gameMode == 2) {
		std::cout << "Game Over. Path Found! Press Enter";
		std::cin.ignore();
		std::cin.get();
	}
	else {
		std::cout << "GAME OVER.  Something Broke!";
	}

}

void setCursorPosition(int x, int y)
{
	static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	std::cout.flush();
	COORD coord = { (SHORT)x, (SHORT)y };
	SetConsoleCursorPosition(hOut, coord);
}

std::string CreateStringStream(DoublyLinkedList* tempList, int numRows, int numCols)
{
	std::stringstream displayString;
	
	// Add top Wall
	displayString << " ";
	for (int i = 0; i < numCols; i++)
	{
		displayString << "------";
	}

	// Create pointers for row and temp
	Node *rowPtr = tempList->head;
	int rowNodeCount, colNodeCount;
	Node *temp = tempList->head;

	// Which node on the row are we at.  Used for condition check
	rowNodeCount = 0;
	while (rowNodeCount < numRows && temp != NULL) {
		// iterate the row of the nodes array
		for (int i = 0; i < 3; i++) {
			displayString << std::endl;
			
			// Move temp to the 1st node of the current row
			temp = rowPtr;
			colNodeCount = 0;
			// Add Left wall
			displayString << "| ";
			// print the cells
			while (colNodeCount < numCols) {
				for (int j = 0; j < 3; j++) {
					if (!temp->visited && !temp->backTrack) {
						displayString << temp->cell[i][j] << " ";
					}
					else if (temp->visited && !temp->backTrack) {
						if (i == 1)
						{
							if (j == 1)
								displayString << "*" << " ";
							else
								displayString << " " << " ";
						}
						else {
							displayString << temp->cell[i][j] << " ";

						}
					}
					else if (temp->visited && temp->backTrack) {
						if (i == 1) {
							if (j == 1)
								displayString << "*" << " ";
							else
								displayString << " " << " ";
						}
						else
						{
							if (j == 1 && i == 0
)
								displayString << "<" << " ";
							else
								displayString << " " << " ";
						}
					}

				}
				colNodeCount++;
				// Move temp forward if it is not tail/NULL otherwise
				if (temp != tempList->tail)
					temp = temp->next;
				else
					temp = NULL;
			}
			// Add Right wall
			displayString << "|";
		}
		colNodeCount = 0;
		// Move the rowPtr to the first node after numCols
		// This simulates the next row of the Maze.
		rowPtr = temp;
		rowNodeCount++;
	}
	// Add bottom Wall
	
	displayString << std::endl << " ";
	for (int i = 0; i < numCols; i++)
	{
		displayString << "------";
	}


	return displayString.str();

}

std::string BufferedScreenUpdate(std::string currentScreen, std::string previousScreen)
{

	int x = 0;
	int y = 6;
	setCursorPosition(x, y);
	for (int iter = 0; iter < currentScreen.length(); iter++)
	{
		if (previousScreen.length() == currentScreen.length())
		{
			if (currentScreen[iter] == previousScreen[iter])
			{
				if (currentScreen[iter] == '\n')
				{
					y++;
					x = -1;
				}
				x++;
				continue;
			}
		}
		setCursorPosition(x, y);
		std::cout << currentScreen[iter];
		x++;
		if (currentScreen[iter] == '\n')
		{
			y++;
			x = 0;
		}
	}
	std::cout.flush();
	
	return currentScreen;
}

DoublyLinkedList ReadFileInputToList()
{
	int rowSize, colSize;
	int startRow, startCol;
	int finishRow, finishCol;
	int wallRow, wallCol;

	// Open and read size and start/finish positions from inputfile
	std::ifstream myFile;
	myFile.open("inputFile");
	if (!myFile) { std::cout << "Bad File"; }
	myFile >> colSize >> rowSize;
	myFile >> startRow >> startCol >> finishRow >> finishCol;

	// error check the file input
	if (colSize < 0 || rowSize < 0 || startCol < 0 ||
		startCol > colSize || startRow < 0 || startRow > rowSize ||
		finishCol < 0 || finishCol > colSize || finishRow < 0 || finishRow > rowSize) {
		std::cout << "There was an error!  Check file contents."
			<< "One of the input numbers is out of range."
			<< std::endl << "File input checked: Size, Start, and Finish Coordinates."
			<< std::endl;
		return {};
	}



	// Create a Doubly Linked List with default content: "."'s
	DoublyLinkedList* maze = new DoublyLinkedList(rowSize, colSize);
	int cellNum = 1;
	for (int i = 0; i < rowSize; i++) {
		for (int j = 0; j < colSize; j++) {
			AddNode(maze,' ', i, j, cellNum);
			cellNum++;
		}
	}

	// update the start and finish coordinages in the list
	// passes the node coordinates(on a grid) to the function to find the node
	UpdateNode(maze, 'S', startRow, startCol);
	UpdateNode(maze, 'F', finishRow, finishCol);



	// UpdateCells to walls based on inputFile data
	for (int h = 0; h < 79; h++) {
		myFile >> wallCol >> wallRow;

		// error check the file input
		if (wallCol < 0 || wallCol > colSize || wallRow < 0 || wallRow > rowSize) {
			std::cout << "There was an error!  Check file contents."
				<< "One of the input numbers is out of range."
				<< std::endl << "File input checked: Wall Cordinates."
				<< std::endl;
			return {};
		}
		UpdateNode(maze, 'X', wallRow, wallCol);
	}
	myFile.close();

	return *maze;

}

void StartGame()
{
	using namespace std;
	char choice;
	do
	{
		DoublyLinkedList maze;
		maze = ReadFileInputToList();
		UpdateValidMovementDirections(&maze, maze.numCols, maze.numRows);
		std::string currScreen = "";
		currScreen = CreateStringStream(&maze, maze.numRows, maze.numCols);

		BufferedScreenUpdate(currScreen, "");

		setCursorPosition(0, 0);
		std::cout << "Q)uit | B)readth First Search | D)epth First Search:  ";
		cin >> choice;
		choice = toupper(choice);
		switch (choice)
		{
		case 'B':
			BreadthFirstSolution(&maze);
			system("CLS");
			break;

		case 'D':
			DepthFirstSolution(&maze);
			system("CLS");
			break;

		}
	} while (choice != 'Q');
}

// ****************MAIN********************************************************

int main() {
	using namespace std;

	// Warn to mazimixe the screen then clear the warning.
	cout << "Maximize this window if necessary, then Press Enter to start...";
	cin.get();
	setCursorPosition(0, 0);
	cout << "                                                                   ";

	// Call the Game Start
	StartGame();

	// Press a key
	cout << endl << "Press <Enter> to continue...";
	cin.get();

	return 0;
}