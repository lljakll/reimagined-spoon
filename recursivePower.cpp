#include <iostream>
using namespace std;

double power (double x, unsigned int n){
	if (n == 0)
		return 1.0;
	else
		return x*power(x,n-1);
}

int main(){
	char choice = 'y';
do{
	double base = 0.0;
	int pwr = 0;
	cout << endl << "Enter the base: ";
	cin >> base;
	cout << endl << "Enter the power: ";
	cin >> pwr;
	cout.precision(0);
	cout << fixed << endl << base << " to the " << pwr << " power is: " << power(base,pwr) << endl;
	cout << "Again?";
	cin >> choice;
}
while(choice != 'n' || choice != 'N');

}
