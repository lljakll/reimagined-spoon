// Write a stack class in Java, C++, or Python, and implement
// the following methods: push(), pop(), top(), size(), and isEmpty(). 
// The stack should be implemented as an array. 

#ifdef __cplusplus__
  #include <cstdlib>
#else
  #include <stdlib.h>
#endif

#include <iostream>
#include <string>

template <class T>
class Stack{
public:

    void Clear(){
        for (int i = this->Size(); i >= 0; i--)
            values[i] = {};
    }  
    bool IsEmpty(){
        if(values[0]) 
            return false;
        return true;
    }
    void Push(T element){
        if(values[0]){
            for(int i = this->Size(); i >= 0; i--){
                values[i] = values[i-1];
            }
        }
        values[0] = element;
    }  
    T Pop(){
        T topElement = values[0];
        for (int i = 0; i < 20; i++){
            values[i] = values[i+1];
        }
        values[20] = {};
        return topElement;
}
    T Top(){
        if(values[0]) return values[0];
        else return 0;
}

    int Size(){
        if(!values){
            return 0;
        }
        else{
            int arraySize = 0;
            for (int i = 0; i < 20; i++){
                if(values[i]) arraySize++;
            }
            return arraySize;   
        }
    }

    void PrintStack(){
        std::cout << std::endl;
        for(int i = 0; i < this->Size(); i++){
            std::cout << "  - " << values[i] << std::endl;
        }
        std::cout << std::endl << " -> Stack Size: " << this->Size() << std::endl;
        std::cout << " ____________________" << std::endl;
        std::cout << std::endl;
    }

private:
    T values[20] = {};
    
};

    void Start(){
        using namespace std;
        char choice;
        char value;
        Stack <char>testStack;
        do{
            if (system("clear")) system("CLS");
            
            cout << "  (p)ush | p(o)p | (c)lear | (i)sEmpty | (t)op | (q)uit" << endl << endl;
            cout << "  -STACK-" << endl;
            testStack.PrintStack();
            cout << endl << endl;
            cout << " -> Command: ";

            cin >> choice;
            choice = toupper(choice);

            switch(choice){
                case 'P':
                    cout << " -> Enter The value to PUSH to the Stack: ";
                    cin >> value;
                    testStack.Push(value);
                break;
                case 'O':
                    value = testStack.Pop();
                    if(value){
                        cout << endl << " -> " << value << " was Popped from the Stack.\n -> Hit Enter.";
                    }
                    else{
                        cout << endl << " -> There are no values in the Stack.\n -> Hit Enter";
                    }
                    cin.ignore();
                    cin.get();
                break;
                case 'C':
                    testStack.Clear();;
                break;
                case 'I':
                    cout << " -> The Stack is ";

                    if(testStack.IsEmpty()) cout << "EMPTY";
                    else cout << "NOT EMPTY";
                    
                    cout << endl << "Press Enter";
                    cin.ignore();
                    cin.get();
                break;
                case 'T':
                    if(testStack.Top()) cout << " -> The Top value is " << testStack.Top();
                    else cout << " -> There are no values in the Stack.";

 
                    cout << endl << "Press Enter";
                    cin.ignore();
                    cin.get();
                break;
            }
        }
        while(choice != 'Q');
            
    }

int main(){
    
    Start();

    return 0;
}