#include <fstream>
#include <iostream>

// Node declaration/definition
class DLNode{
public:
	DLNode(){
		prev = NULL;
		next = NULL;
	}

	DLNode(char passed, DLNode *prevPtr = 0, DLNode *nextPtr = 0){
		if(passed != 'X'){
			cell[1][1] = passed;
		}
		else{
			for(int i = 0; i<3;i++)
				for(int j = 0;j<3;j++)
					cell[i][j] = 'X';
		}
		prev = prevPtr;
		next = nextPtr;
	}
	DLNode *prev;
	DLNode *next;
	char cell[3][3] = { {'.','.','.'}, {'.','.','.'},{'.','.','.'} };
	int nodeX, nodeY;
};

// The list that holds the maze data
class DoublyLinkedList {
public:
	DoublyLinkedList() {
		head = 0;
		tail = 0;
	}
	DoublyLinkedList(int row, int col){
		head = 0;
		tail = 0;
		sizeRow = row;
		sizeCol = col;
	}

	// Adds a node to the list.
	void addDLNode(char data, int x, int y) {
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
		}
		else {
			// The list is empty, create a new node and point head/tail at it
			head = tail = new DLNode(data);
			// update x,y of the new node
			head->nodeX = x;
			head->nodeY = y;
		}
	}

	// Updates the contents of node x,y with passed data.
	// All except 'X' are updated in element 1,1.  X causes all
	// elements to be updated
	void updateDLNode(char data, int x, int y){
		DLNode *temp = head;
		
		// Iterate through the list
		while(temp){
			// Find the node with the passed x,y
			if(temp->nodeX == x && temp->nodeY == y){
				// Update the node based on passed data.(all X or 1,1 element)
				if(data !='X') temp->cell[1][1] = data;
				else{
					for(int i=0;i<3;i++){
						for(int j=0;j<3;j++){
							temp->cell[i][j] = data;
						}
					}
				}
			}
			temp = temp->next;
		}
	}

	// This function iterates through each row of the arrays 
	// in the nodes of each row and outputs them one at at time.
	void printNodes() {
		
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
		rowNodeCount=0;
		while(rowNodeCount < sizeRow && temp != NULL){
			// iterate the row of the nodes array
			for(int i=0;i<3;i++){
				std::cout << std::endl;

				// Add row count to first column
				if (i == 1) {
					if (rowNodeCount < 10) { std::cout << rowNodeCount << "  "; }
					else { std::cout << rowNodeCount << " "; }
				}
				else { std::cout << "   "; }
				// Move temp to the 1st node of the current row
				temp = rowPtr;
				colNodeCount=0;
				while(colNodeCount < sizeCol){
					for(int j=0;j<3;j++){
						std::cout << temp->cell[i][j] << " ";
					}
					colNodeCount++;
					// Move temp forward if it is not tail/NULL otherwise
					if(temp != tail)
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
		rowNodeCount=0;
		while(rowNodeCount < sizeRow && temp != NULL){
			// iterate the row of the nodes array
			for(int i=0;i<3;i++){
				outFile << std::endl;

				// Add row count to first column
				if (i == 1) {
					if (rowNodeCount < 10) { outFile << rowNodeCount << "  "; }
					else { outFile << rowNodeCount << " "; }
				}
				else { outFile << "   "; }

				// Move temp to the 1st node of the current row
				temp = rowPtr;
				colNodeCount=0;
				while(colNodeCount < sizeCol){
					for(int j=0;j<3;j++){
						outFile << temp->cell[i][j] << " ";
					}
					colNodeCount++;
					// Move temp forward if it is not tail/NULL otherwise
					if(temp != tail)
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

	DLNode *head, *tail;
	int sizeRow, sizeCol;
};

int main() {

	int rowSize, colSize;
	int startRow, startCol;
	int finishRow, finishCol;
	int wallRow, wallCol;

	// Open and read size and start/finish positions from inputfile
	std::ifstream myFile;
	myFile.open("inputFile");
	myFile >> colSize >> rowSize;
	myFile >> startRow >> startCol >> finishRow >> finishCol;

	// error check the file input
	if(colSize < 0 || rowSize < 0 ||  startCol < 0 || 
		startCol > colSize ||  startRow < 0 || startRow > rowSize || 
		finishCol < 0 || finishCol > colSize||  finishRow < 0 || finishRow > rowSize ){
		std::cout << "There was an error!  Check file contents." 
			<< "One of the input numbers is out of range." 
			<< std::endl << "File input checked: Size, Start, and Finish Coordinates." 
			<< std::endl;
		return 1;
	}

	// Create a Doubly Linked List with default content: "."'s
	DoublyLinkedList* maze = new DoublyLinkedList(rowSize,colSize);
	for (int i = 0; i <  rowSize; i++){
		for(int j = 0; j<colSize; j++){
			maze->addDLNode('.',i,j);
		}
	}

	// update the start and finish coordinages in the list
	// passes the node coordinates(on a grid) to the function to find the node
	maze->updateDLNode('S',startRow,startCol);
	maze->updateDLNode('F',finishRow,finishCol);



	// UpdateCells to walls based on inputFile data
	for (int h = 0; h < 79; h++) {
		myFile >> wallCol >> wallRow;

		// error check the file input
		if (wallCol < 0 || wallCol > colSize || wallRow < 0 || wallRow > rowSize){
			std::cout << "There was an error!  Check file contents." 
				<< "One of the input numbers is out of range." 
				<< std::endl << "File input checked: Wall Cordinates." 
				<< std::endl;
			return 1;
		}
		maze->updateDLNode('X',wallRow,wallCol);
	}
	myFile.close();

	// print and write to file.
	maze->printNodes();
	maze->writeNodes();

	// Press a key
	std::cout << std::endl << "Press <Enter> to continue..." << std::endl;
	std::cin.get();
	
	return 0;
}
