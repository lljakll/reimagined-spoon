#include <fstream>

#include <iostream>



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

	void addDLNode(char data, int x, int y) {
		if (tail != 0) {
			DLNode *temp = tail;

			tail->next = new DLNode(data);

			tail = tail->next;
			tail->prev = temp;
			tail->nodeX = x;
			tail->nodeY = y;
		}
		else {
			head = tail = new DLNode(data);
			head->nodeX = x;
			head->nodeY = y;
		}
	}

	void updateDLNode(char data, int x, int y){
		DLNode *temp = head;
		
		while(temp){
			if(temp->nodeX == x && temp->nodeY == y){
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

	void printNodes(int rowSize, int colSize) {
		DLNode *temp = head;
		
		while(temp){
			for (int i = 0; i < rowSize; i++){
				for(int j = 0; j < colSize; j++){
					std::cout << temp->cell[i][j];
						
				}
				
				std::cout << std::endl;
			}
			temp = temp->next;
		}
	}

	DLNode *head, *tail;
	int sizeRow, sizeCol;
};

/*
// Print the array of Cell Objects to STD_OUT
// Need to work on passing 2D array by ref
// So we dont have to define the size of the array here
void printNodes(int rowSize, int colSize) {
	// Add numerical header to displayed grid
	std::cout << "   ";
	for (int i = 0; i < colSize; i++) {
		if (i < 10) {
			std::cout << "  " << i << "   ";
		}
		else {
			std::cout << "  " << i << "  ";
		}
	}
	std::cout << std::endl;
	// iterating through the array
	for (int i = 0; i < rowSize; i++) {
		for (int m = 0; m < 3; m++) {
			// Add row count to first column
			if (m == 1) {
				if (i < 10) { std::cout << i << "  "; }
				else { std::cout << i << " "; }
			}
			else { std::cout << "   "; }
			for (int j = 0; j < colSize; j++) {
				for (int n = 0; n < 3; n++) {
					std::cout << array[i][j].ReturnCellValue(m, n) << " ";
				}
			}
			std::cout << std::endl;
		}
	}
}

// Write the Array to the Output File
void WriteArray(Cell ** array, int rowSize, int colSize) {

	ofstream outFile;
	outFile.open("outputFile");

	// Add numerical header to displayed grid
	std::cout << "   ";
	for (int i = 0; i < colSize; i++) {
		if (i < 10) {
			outFile << "  " << i << "   ";
		}
		else {
			outFile << "  " << i << "  ";
		}
	}
	outFile << std::endl;
	// iterating through the array
	for (int i = 0; i < rowSize; i++) {
		for (int m = 0; m < 3; m++) {
			// Add row count to first column
			if (m == 1) {
				if (i < 10) { outFile << i << "  "; }
				else { outFile << i << " "; }
			}
			else { outFile << "   "; }
			for (int j = 0; j < colSize; j++) {
				for (int n = 0; n < 3; n++) {
					outFile << array[i][j].ReturnCellValue(m, n) << " ";
				}
			}
			outFile << std::endl;
		}
	}
	outFile.close();
}
*/
int main() {

// Dirty read/parse file (must be all ints)
// want to move to function and parse no matter the content
	int rowSize, colSize;
	int startRow, startCol;
	int finishRow, finishCol;
	int wallRow, wallCol;

	// Open and read size and start/finish positions from inputfile
	std::ifstream myFile;
	myFile.open("inputFile");
	myFile >> colSize >> rowSize;
	myFile >> startCol >> startRow >> finishCol >> finishRow;

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

	// Create a Doubly Linked List
	DoublyLinkedList* maze = new DoublyLinkedList(rowSize,colSize);
	for (int i = 0; i <  rowSize; i++){
		for(int j = 0; j<colSize; j++){
			maze->addDLNode('.',i,j);
		}
	}

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
	
	maze->printNodes(rowSize, colSize);

	// Close File
	myFile.close();

	// Print to the Screen


	// Write to file


	// Press a key
	std::cout << std::endl << "Press <Enter> to continue..." << std::endl;

	std::cin.get();
	
	return 0;
}
