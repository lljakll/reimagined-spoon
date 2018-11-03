// Chapter 5.12 Question 11
// 

#include <iostream>
using namespace std;

int GCD(int n, int m){

    if (m <= n && n % m == 0){
        cout << m;
        return m;
    }
    else if(n < m){
        cout << "2Sending " << m << " and " << n;
        GCD(m, n);
    }
    else{
        cout << "3Sending " << m << " and " << n%m;
        GCD(m, n % m);
    }

}

int main(){
    int n, m, gcd = 0;

    cout << "\nEnter the first number: ";
    cin >> n;
    cout << "\nEnter the second number: ";
    cin >> m;
    gcd = GCD(n,m);
        cout << "\nThe GCD is: " << gcd << endl;
}