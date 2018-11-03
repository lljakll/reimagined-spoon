

#include <iostream>
#include <string>

#ifdef __cplusplus__
  #include <cstdlib>
#else
  #include <stdlib.h>
#endif

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

class SLinkedList{
public:
    SLinkedList(){
        head = 0;
        tail = 0;
    }

    // Page 79
    void addNodeToHead(string passedData){

        head = new Node(passedData, head);
        if (tail == 0)
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

    void printAllNodes(){
        if(head !=0){
            Node *temp;
            // print nodes up to tail.  Figure out how to include tail in this loop
            for(temp = head; temp->next != NULL; temp = temp->next){
                cout << "* " << temp->data << endl;
            }
            // print tail node
            cout << "* " << tail->data << endl;
        }
    }

    void addNodeAfterIthNode(string passedData, int ithNode){
        Node *temp;
        temp = head;    

        // error if request is greater than 0 and there is only one node
        if(head == tail && ithNode > 0){
            cout << "\nThere is only one node in the List.\nPress Enter.";
            cin.ignore();
            cin.get();
        }
        // the request is 0 and there is more than 1 node insert a new head
        else if(tail != head && ithNode == 0){
            head = new Node(passedData);
            head->next = temp;
        }
        // if more than one node and request is not 0
        // set the temp pointer to the ith nodes's address
        // int i = 1 since head is already assigned and is considered node 0
        else{
            for (int i = 1; i < ithNode; i++){
                temp = temp->next;
            }
            // Insert a node after the ith node
            temp->next = new Node(passedData, temp->next);
        }
    }
    void deleteAllNodes(){
        Node *temp = head->next;
        delete head;
        head = temp;
    }

    void deleteIthNode(int ithNode){
        Node *temp, *prev;
        // is List empty?
        if(head != 0){
            // delete if there is only one node and request is node 0
            if(head == tail && ithNode == 0){
                delete head;
                head = tail = 0;
            }
            // error if request is greater than 0 and there is only one node
            else if(head == tail && ithNode > 0){
                cout << "\nThere is only one node in the List.\nPress Enter.";
            cin.ignore();
            cin.get();
            }
            // the request is 0 and there is more than 1 node del head and move head to node 1
            else if(tail != head && ithNode == 0){
                head = head->next;
                delete temp;
            }
            // if more than one and request is not 0
            // set the temp pointer to the ith nodes's address
            // set the prev pointer to the ith - 1 address
            else{
                prev = head, temp = head->next;

                for (int i = 1; i < ithNode; i++){
                    prev = prev->next, temp = temp->next;
                }
                prev->next = temp->next;
                // Move tail if necessary
                if(temp == tail)
                    tail = prev;

                delete temp;
            }
        }
    }

    void reverseList(){
        // check to see if list has any nodes.
        if(head != 0){
            // declare and initialize 3 pointers 
            Node *curr = head;
            Node *prev = NULL, *next = NULL;

            // assign tail to head( using curr for consistency)
            tail = curr;
            // curr is not at the end of the list
            while(curr != NULL){
                // move next ptr to next node
                next = curr->next;

                // move curr-next ptr to previous addy
                curr->next = prev;

                // move prev ptr to curr addy/then curr ptr to next addy
                prev = curr;
                curr = next;
            }
            // assign previous (last in original list) as head.
            head = prev;
        }
    }

    void destructivelyAppendList(){

    }


//    bool listContains(string searchStr)
//    Node searchList(string searchStr)
//    void sortListAscending()

private:
    Node *head, *tail;
};


int main(){
    SLinkedList myList;
    SLinkedList yourList;

    char choice;
    string value;
    int ithPosition;

    do{
        if (system("clear")) system("CLS");

        cout << "LIST 1:" << endl;
        myList.printAllNodes();
        cout << endl << endl;
        cout << "LIST 2:" << endl;
        yourList.printAllNodes();
        cout << endl << endl;
        cout << "------------MENU------------" << endl;
        cout << "A)dd Node to Head" << endl;
        cout << "Add (N)ode to Tail" << endl;
        cout << "I)nsert Node after a postion" << endl;
        cout << "D)elete Node from a position" << endl;
        cout << "R)everse List" << endl;
        cout << "C)opy List 1 to List 2" << endl;
        cout << "Q)uit" << endl << endl << "Command: ";

        cin >> choice;
        choice = toupper(choice);

        switch(choice){
            case 'A':
                cout << "Enter The value to add: ";
                cin >> value;
                myList.addNodeToHead(value);
            break;
            case 'N':
                cout << "Enter The value to add: ";
                cin >> value;
                myList.addNodeToTail(value);
            break;
            case 'I':
                cout << "Enter The value to add: ";
                cin >> value;
                cout << "Enter The Position: ";
                cin >> ithPosition;
                myList.addNodeAfterIthNode(value, ithPosition);
            break;
            case 'D':
                cout << "Enter The Position to Delete: ";
                cin >> ithPosition;
                myList.deleteIthNode(ithPosition);            
            break;
            case 'R':
                myList.reverseList();
            break;
            case 'C':
                yourList = myList;
        }
    }
    while(choice != 'Q');
    return 0;
}