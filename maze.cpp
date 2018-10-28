

#include <fstream>
#include <cstring>
#include <iostream>
using namespace std;

class Cell {
public:
	// Default constructor that creates a blank cell (3x3 grid of '.')
	Cell(){
		for(int i = 0; i<3; i++){
			for(int j = 0; j<3; j++){
				content[i][j] = '.';
			}
		}
		isAWall,isStart,isFinish,isBarrier,hasBeenVisited = false;
		cellLocX, cellLocY = 0;
	}
	
	// overloaded constructor that accepts a char to add to cell ID (index 1,1)
	Cell(char cellType){
		for(int i = 0; i<3; i++){
			for(int j = 0; j<3; j++){
				// if a wall, 'X' and flag, otherwise '.'
				if (cellType == 'X' || cellType == 'x') { content[i][j] = 'X'; isAWall = true;}
				else { content[i][j] = '.';	}
			}
		}
		if (cellType == 'S' || cellType == 's'){ content[1][1] = 'S'; isStart = true;}
		else if(cellType == 'F' || cellType == 'f'){ content[1][1] = 'F'; isFinish = true;}

		isAWall,isStart,isFinish,isBarrier,hasBeenVisited = false;
		cellLocX, cellLocY = 0;
	}

	void UpdateCellType(char cellType){
		for(int i = 0; i<3; i++){
			for(int j = 0; j<3; j++){
				// if a wall, 'X' and flag, otherwise '.'
				if (cellType == 'X' || cellType == 'x') { content[i][j] = 'X'; isAWall = true;}
				else { content[i][j] = '.';	}
			}
		}
		if (cellType == 'S' || cellType == 's'){ content[1][1] = 'S'; isStart = true;}
		else if(cellType == 'F' || cellType == 'f'){ content[1][1] = 'F'; isFinish = true;}

		isAWall,isStart,isFinish,isBarrier,hasBeenVisited = false;
		cellLocX, cellLocY = 0;
	}
	bool UpdateCellHasBeenVisited(){
		return true;
	}
	char ReturnCellValue(int row, int col){
		return content[row][col];
	}

protected:
	char content[3][3];
	int cellLocX,cellLocY;
	bool isAWall, isStart, isFinish, isBarrier, hasBeenVisited;
};

// Print the array of Cell Objects to STD_OUT
// Need to work on passing 2D array by ref
// So we dont have to define the size of the array here
void PrintArray(Cell array[9][9], int size){
	for (int i = 0; i < size; i++){
		for (int m = 0; m < 3; m++){
			for (int j = 0; j < size; j++){
				for (int n = 0; n < 3; n++){
					cout << array[i][j].ReturnCellValue(m,n) << " ";
				}
			}
			cout << endl;
		}
	}
}

int main() {
	// Create the array of objects
	const int ARR_SZ = 9;
	Cell maze[ARR_SZ][ARR_SZ];

	PrintArray(maze, ARR_SZ);
	cin.get();
	return 0;
}


	// Read from the file
	
	// process the file and update the array of objects with
	// the proper information from the file.
	
	// Display the maze

	

