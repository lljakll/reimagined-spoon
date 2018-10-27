

#include <fstream>
#include <cstring>
#include <iostream>
using namespace std;

class Cell {
public:
	Cell(){
		cellLocX, cellLocY = 0;
		isAWall,isStart,isFinish,isBarrier,hasBeenVisited = false;
	}
	
	Cell(int locationX, int locationY){
		cellLocX = locationX;
		cellLocY = locationY;
		isAWall,isStart,isFinish,isBarrier,hasBeenVisited = false;
	}
//	void visitCell();
	void UpdateCellLoc(int x, int y){
		cellLocX = x;
		cellLocY = y;
	}
protected:
	int cellLocX, cellLocY;
	bool isAWall, isStart, isFinish, isBarrier, hasBeenVisited;
};


int main() {
	// Create the array of objects, update their x,y loc
	Cell maze[12][12];
	
	for (int row = 0; row < 12; row++){
		for (int col = 0; col < 12; col++){
			maze[row,col]->UpdateCellLoc(row,col);
		}
	}
	
	// Read from the file
	
	// process the file and update the array of objects with
	// the proper information from the file.
	
	// Display the maze

	
	cin.get();
	return 0;
}
