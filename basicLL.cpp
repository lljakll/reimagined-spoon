

#include <iostream>
#include <string>

using namespace std;

Node class Node{
public:
    Node(){
        next = NULL;
    }
    Node(string passedData, Node *ptr){
        data = passedData;
        next = ptr;
    }
    string data;
    Node *next;

};

class LinkedList{
public:
    LinkedList{
        head = 0;
        tail = 0;
    }
    void addNodeAfterIthNode(int ithNode){
        
    }
    void deleteNode()
    void printNode()
    bool listContains(string searchStr)
    Node searchList(string searchStr)
    void sortList()
    void copyList()
    void destructivelyAppendList()
    void reverseList()
private:
    Node *head, *tail;
};
