

#include <iostream>
#include <string>

using namespace std;

class Node{
public:
    Node(){
        next = NULL;
    }
    Node(string passedData, Node *ptr = 0){
        data = passedData;
        next = ptr;
    }
    string data;
    Node *next;

};

class LinkedList{
public:
    LinkedList(){
        head = 0;
        tail = 0;
    }

    // Page 79
    void addNodeToHead(string passedData){
        head = new Node(passedData, head);
        if (tail ==0)
            tail = head;
    }
    
    // Page 79
    void addNodeToTail(string passedData){
        if (tail !=0){
            tail->next = new Node(passedData);
            tail = tail->next;
        }
        else   
            head = tail = new Node(passedData);
    }

 /*   void addNodeAfterIthNode(int ithNode, string passedData){
        // check to make sure there are nodes to insert this 
        // node after...
        if (tail != 0 && head != 0){
            // set the temp pointer to the ith nodes's address
            for (int ii = 0; ii < ithNode; II++){
                temp->next = 
            }
        }

    }*/

//    void deleteIthNode(int ithNode){
//    void printNode()
//    bool listContains(string searchStr)
//    Node searchList(string searchStr)
//    void sortList()
//    void copyList()
//    void destructivelyAppendList()
//    void reverseList()

private:
    Node *head, *tail;
};

int main(){
    LinkedList myList;
    myList.addNodeToHead("jackie");

    string wait;
    cin >> wait;
    return 0;

}