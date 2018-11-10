// Write a queue class in Java, C++, or Python, and implement
// the following methods: queue(), dequeue(), top(), size(), and isEmpty(). 
// The queue should be implemented as an array. 

// Make it OS ambigious
#ifdef __cplusplus__
  #include <cstdlib>
#else
  #include <stdlib.h>
#endif

#include <iostream>
#include <string>

template <class T>
class Queue{
public:

    // Clear the queue
    void Clear(){
        for (int i = this->Size(); i >= 0; i--)
            values[i] = {};
    }

    // Check for an empty queue
    bool IsEmpty(){
        if(values[0]) 
            return false;
        return true;
    }

    // Queue an element to the queue
    void QueueItem(T element){
        if(values[0]){
            values[this->Size()] = element;
        }
        else{
            values[0] = element;
        }
    }

    // Dequeue from the queue
    T Dequeue(){
        T frontElement = values[0];
        for (int i = 0; i < 20; i++){
            values[i] = values[i+1];
        }
        values[20] = {};
        return frontElement;
}

    // Return the top value
    T Top(){
        if(values[0]) return values[0];
        else return 0;
}

    // Return the size of the queue
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

    // Output the queue
    void PrintQueue(){
        std::cout << std::endl;
        for(int i = 0; i < this->Size(); i++){
            std::cout << "  - " << values[i] << std::endl;
        }
        std::cout << std::endl << " -> Queue Size: " << this->Size() << std::endl;
        std::cout << " ____________________" << std::endl;
        std::cout << std::endl;
    }

private:
    T values[20] = {};
    
};
    // Driver function for the Queue Class
    void Start(){
        using namespace std;
        char choice;
        char value;
        Queue <char>testQueue;
        do{
            if (system("clear")) system("CLS");
            
            cout << "  (q)ueue | (d)equeue | (c)lear | (i)sEmpty | (t)op | e(x)it" << endl << endl;
            cout << "  -QUEUE-" << endl;
            testQueue.PrintQueue();
            cout << endl << endl;
            cout << " -> Command: ";

            cin >> choice;
            choice = toupper(choice);

            switch(choice){
                case 'Q':
                    cout << " -> Enter The value to QUEUE: ";
                    cin >> value;
                    testQueue.QueueItem(value);
                break;
                case 'D':
                    value = testQueue.Dequeue();
                    if(value){
                        cout << endl << " -> " << value << " was DEQUEUED from the Queue.\n -> Hit Enter.";
                    }
                    else{
                        cout << endl << " -> There are no values in the Queueu.\n -> Hit Enter";
                    }
                    cin.ignore();
                    cin.get();
                break;
                case 'C':
                    testQueue.Clear();;
                break;
                case 'I':
                    cout << " -> The Queue is ";

                    if(testQueue.IsEmpty()) cout << "EMPTY";
                    else cout << "NOT EMPTY";
                    
                    cout << endl << "Press Enter";
                    cin.ignore();
                    cin.get();
                break;
                case 'T':
                    if(testQueue.Top()) cout << " -> The Top value is " << testQueue.Top();
                    else cout << " -> There are no values in the Queue.";

 
                    cout << endl << "Press Enter";
                    cin.ignore();
                    cin.get();
                break;
            }
        }
        while(choice != 'X');
            
    }

int main(){
    
    Start();

    return 0;
}