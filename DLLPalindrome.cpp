
#include <iostream>
using namespace std;
  
class Node{
public:
    Node(){
        prev = NULL;
        next = NULL;
    }
    Node(string passedData, Node *prevPtr = 0, Node *nextPtr = 0){
        prev = prevPtr;
        data = passedData;
        next = nextPtr;
    }
    Node *prev;
    string data;
    Node *next;

};

class DLinkedList{
public:
    DLinkedList(){
        head = 0;
        tail = 0;
    }

    void addNode(string passedData){

        if(tail !=0){
            tail = new Node(passedData,0,tail);
            tail->prev->next = tail;
        }
        else head = tail = new Node(passedData);
    }

    Node *head, *tail;
};

bool isPalindrome(Node* head, Node* tail) {
    if (head == NULL) {
        return false;
    }
    Node *left, *right;

    left = head;
    right = tail;
    
    while(left != right ){
        if(left->data == right->data){
            head = head->next;
            tail = tail->prev;
        }
        else return false;
    }
    return true;
}

int main(){
    DLinkedList myList;

    myList.addNode("r");
    myList.addNode("a");
    myList.addNode("d");
    myList.addNode("a");
    myList.addNode("r");
    bool check = isPalindrome(myList.head, myList.tail);
    cout << check;
}