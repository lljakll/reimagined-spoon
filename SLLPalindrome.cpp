
#include <iostream>
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
  
void reverseList(Node **head) {
    Node *prev = NULL, *ptr = *head, *temp;
    while (ptr) {
        
        temp = ptr->next;
        ptr->next = prev;
        prev = ptr;
        ptr = temp;
    }
    *head = prev;
}
  
void printList(Node *ptr) {
    while(ptr) {
        cout << ptr->data << ", ";
        ptr = ptr->next;
    }
    cout << endl;
}
  
int isPalindromicLinkedList(Node* head) {
    if (head == NULL) {
        return 1;
    }
    Node *p1, *p2; // two pointer to struct List Node
  
    // find mid
    Node *mid = NULL;
    p1 = p2 = head;
    while (p2) {
        p2 = p2->next;
        if (p2) p2 = p2->next;
        if (p2) p1 = p1->next;
    }
    mid = p1;
  
    reverseList(&(mid->next)); // reverse list ahead of MID
  
    int ans = 1;
    p1 = head;
    p2 = mid->next;
    while (ans == 1 && p2) {
        if (p1->data != p2->data) ans = 0;
        p1 = p1->next;
        p2 = p2->next;
    }
  
    reverseList(&(mid->next)); // reset second half of list to original state.
  
    return ans;
}
  
Node *createListFromArray(int arr[], int n) {
    Node *head = new Node;
    Node *ptr = head;
    for (int i = 0; i < n; i++) {
        ptr->data = arr[i];
        ptr->next = (i == n-1 ? NULL : new Node);
        ptr = ptr->next;
    }
    return head;
}
  
  
int main()
{
    int arr[] = {1, 2, 3, 4, 5, 4, 3, 2, 1};
    cout << "Result 1: " << isPalindromicLinkedList(createListFromArray(arr, 9)) << endl;
  
    int arr2[] =  {1, 2, 2, 1};
    cout << "Result 2: " << isPalindromicLinkedList(createListFromArray(arr2, 4)) << endl;
  
    int arr3[] = {1, 2, 3, 4, 5};
    cout << "Result 3: " << isPalindromicLinkedList(createListFromArray(arr3, 5)) << endl;
  
    return 0;
}
