

#include <fstream>
#include <cstring>
#include <iostream>
using namespace std;

class Cell {
public:
	Cell();
	Cell(int locationX, int locationY);
	void visitCell();
	void UpdateCellLoc(int x, y)
protected:
	int cellLocX, cellLocY;
	bool isAWall, isStart, isFinish, isBarrier, hasBeenVisited;
}

int main() {
	// Create the array of objects, update their x,y loc
	Cell[12][12] maze;
	
	for (int row = 0; row < 12; row++){
		for (int col = 0; col < 12; col++){
			maze[row,col].UpdateCellLoc(row,col);
		}
	}
	
	// Read from the fileb
	
	// process the file and update the array of objects with
	// the proper information from the file.
	
	
	
	cin.get();
	return 0;
}
