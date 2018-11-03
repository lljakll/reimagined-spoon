#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

int main(){

	int unsortedArray[100];
	srand (time(NULL));
	for (int i = 0; i<100; i++){
		*(unsortedArray + i) = rand() % 10000 + 1;
		cout << *(unsortedArray + i) << " ";
	}

	int largestNum,compSteps = 0;


	for (int j = 0; j < 100; j++){
		if(*(unsortedArray+j) > largestNum){
			largestNum = *(unsortedArray+j);
		}
		compSteps++;
	}

	cout << endl << endl << largestNum << endl << compSteps;
}
