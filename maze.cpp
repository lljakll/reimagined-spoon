#include <fstream>
#include <cstring>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

class Cell {
public:
	// Default constructor that creates a blank cell (3x3 grid of '.')
	Cell() {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				content[i][j] = '.';
			}
		}
		isAWall, isStart, isFinish, isBarrier, hasBeenVisited = false;
		cellLocX, cellLocY = 0;
	}

	// overloaded constructor that accepts a char to add to cell ID (index 1,1)
	Cell(char cellType) {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				// if a wall, 'X' and flag, otherwise '.'
				if (cellType == 'X' || cellType == 'x') { content[i][j] = 'X'; isAWall = true; }
				else { content[i][j] = '.'; }
			}
		}
		// Set flags based on passed cellType
		if (cellType == 'S' || cellType == 's') { content[1][1] = 'S'; isStart = true; }
		else if (cellType == 'F' || cellType == 'f') { content[1][1] = 'F'; isFinish = true; }

		isBarrier, hasBeenVisited = false;
		cellLocX, cellLocY = 0;
	}

	void UpdateCellType(char cellType) {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				// if a wall, 'X' and flag, otherwise '.'
				if (cellType == 'X' || cellType == 'x') { content[i][j] = 'X'; isAWall = true; }
				else { content[i][j] = '.'; }
			}
		}
		// Set flags based on passed cellType
		if (cellType == 'S' || cellType == 's') { content[1][1] = 'S'; isStart = true; }
		else if (cellType == 'F' || cellType == 'f') { content[1][1] = 'F'; isFinish = true; }

		isBarrier, hasBeenVisited = false;
		cellLocX, cellLocY = 0;
	}
	bool UpdateCellHasBeenVisited() {
		hasBeenVisited = true;
	}
	char ReturnCellValue(int row, int col) {
		return content[row][col];
	}

protected:
	char content[3][3];
	int cellLocX, cellLocY;
	bool isAWall, isStart, isFinish, isBarrier, hasBeenVisited;
};

// Print the array of Cell Objects to STD_OUT
// Need to work on passing 2D array by ref
// So we dont have to define the size of the array here
void PrintArray(Cell ** array, int rowSize, int colSize) {
	// Add numerical header to displayed grid
	cout << "   ";
	for (int i = 0; i < colSize; i++) {
		if (i < 10) {
			cout << "  " << i << "   ";
		}
		else {
			cout << "  " << i << "  ";
		}
	}
	cout << endl;
	for (int i = 0; i < rowSize; i++) {
		for (int m = 0; m < 3; m++) {
			// Add row count to first column
			if (m == 1) {
				if (i < 10) { cout << i << "  "; }
				else { cout << i << " "; }
			}
			else { cout << "   "; }
			for (int j = 0; j < colSize; j++) {
				for (int n = 0; n < 3; n++) {
					cout << array[i][j].ReturnCellValue(m, n) << " ";
				}
			}
			cout << endl;
		}
	}
}

// Write the Array to the Output File
void WriteArray(Cell ** array, int rowSize, int colSize) {

	ofstream outFile;
	outFile.open("outputFile");

	// Add numerical header to displayed grid
	cout << "   ";
	for (int i = 0; i < colSize; i++) {
		if (i < 10) {
			outFile << "  " << i << "   ";
		}
		else {
			outFile << "  " << i << "  ";
		}
	}
	outFile << endl;
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
			outFile << endl;
		}
	}
	outFile.close();
}

// stream entire file to a string.  Maybe use this later.  will have to 
// parse the string to get input for the array
/*string ReadFile(){
	ifstream myFile("inputFile", ios::in | ios::binary | ios::ate);

	ifstream::pos_type fileSize = myFile.tellg();
	myFile.seekg(0, ios::beg);

	vector<char> bytes(fileSize);
	myFile.read(bytes.data(), fileSize);

	return string(bytes.data(), fileSize);
}*/

int main() {

// Dirty read/parse file (must be all ints)
	int rowSize, colSize;
	int startRow, startCol;
	int finishRow, finishCol;
	int wallRow, wallCol;

	// Open and read size and start/finish positions from inputfile
	ifstream myFile;
	myFile.open("inputFile");
	myFile >> colSize >> rowSize;
	myFile >> startCol >> startRow >> finishCol >> finishRow;

	// Create the array of objects
	Cell** maze;
	maze = new Cell*[rowSize];
	for (int i = 0; i < rowSize; i++) { maze[i] = new Cell[colSize]; }

	// UpdateCells to walls based on inputFile data
	for (int h = 0; h < 79; h++) {
		myFile >> wallCol >> wallRow;
		maze[wallRow][wallCol].UpdateCellType('X');
	}
	
	// UpdateCells to start/finish
	maze[startCol][startRow].UpdateCellType('S');
	maze[finishCol][finishRow].UpdateCellType('F');

	// Close File
	myFile.close();

	// Print to the Screen
	PrintArray(maze, rowSize, colSize);

	// Write to file
	WriteArray(maze, rowSize, colSize);

	// Press a key
	cout << endl << "Press <Enter> to continue..." << endl;
	cin.get();
	
	return 0;
}
