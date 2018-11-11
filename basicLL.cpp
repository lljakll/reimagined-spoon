

#include &lt;iostream&gt;
#include &lt;string&gt;

#ifdef __cplusplus__
  #include &lt;cstdlib&gt;
#else
  #include &lt;stdlib.h&gt;
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
            tail-&gt;next = new Node(passedData);
            tail = tail-&gt;next;
        }
        else   
            head = tail = new Node(passedData);
    }

    void printAllNodes(){
        if(head !=0){
            Node *temp;
            // print nodes up to tail.  Figure out how to include tail in this loop
            for(temp = head; temp-&gt;next != NULL; temp = temp-&gt;next){
                cout &lt;&lt; "* " &lt;&lt; temp-&gt;data &lt;&lt; endl;
            }
            // print tail node
            cout &lt;&lt; "* " &lt;&lt; tail-&gt;data &lt;&lt; endl;
        }
    }

    void addNodeAfterIthNode(string passedData, int ithNode){
        Node *temp;
        temp = head;    

        // error if request is greater than 0 and there is only one node
        if(head == tail && ithNode &gt; 0){
            cout &lt;&lt; "\nThere is only one node in the List.\nPress Enter.";
            cin.ignore();
            cin.get();
        }
        // the request is 0 and there is more than 1 node insert a new head
        else if(tail != head && ithNode == 0){
            head = new Node(passedData);
            head-&gt;next = temp;
        }
        // if more than one node and request is not 0
        // set the temp pointer to the ith nodes's address
        // int i = 1 since head is already assigned and is considered node 0
        else{
            for (int i = 1; i &lt; ithNode; i++){
                temp = temp-&gt;next;
            }
            // Insert a node after the ith node
            temp-&gt;next = new Node(passedData, temp-&gt;next);
        }
    }
    void deleteAllNodes(){
        Node *temp = head-&gt;next;
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
            else if(head == tail && ithNode &gt; 0){
                cout &lt;&lt; "\nThere is only one node in the List.\nPress Enter.";
            cin.ignore();
            cin.get();
            }
            // the request is 0 and there is more than 1 node del head and move head to node 1
            else if(tail != head && ithNode == 0){
                head = head-&gt;next;
                delete temp;
            }
            // if more than one and request is not 0
            // set the temp pointer to the ith nodes's address
            // set the prev pointer to the ith - 1 address
            else{
                prev = head, temp = head-&gt;next;

                for (int i = 1; i &lt; ithNode; i++){
                    prev = prev-&gt;next, temp = temp-&gt;next;
                }
                prev-&gt;next = temp-&gt;next;
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
                next = curr-&gt;next;

                // move curr-next ptr to previous addy
                curr-&gt;next = prev;

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

    // Write a stack class in Java, C++, or Python, and implement
// the following methods: push(), pop(), top(), size(), and isEmpty(). 
// The stack should be implemented as an array. 

// Make it OS ambigious
#ifdef __cplusplus__
  #include &lt;cstdlib&gt;
#else
  #include &lt;stdlib.h&gt;
#endif

#include &lt;iostream&gt;
#include &lt;string&gt;

template &lt;class T&gt;
class Stack{
public:

    // Clear the stack
    void Clear(){
        for (int i = this-&gt;Size(); i &gt;= 0; i--)
            values[i] = {};
    }

    // Check for an empty stack
    bool IsEmpty(){
        if(values[0]) 
            return false;
        return true;
    }

    // Push to the stack
    void Push(T element){
        if(values[0]){
            for(int i = this-&gt;Size(); i &gt;= 0; i--){
                values[i] = values[i-1];
            }
        }
        values[0] = element;
    }

    // Pop from the stack
    T Pop(){
        T topElement = values[0];
        for (int i = 0; i &lt; 20; i++){
            values[i] = values[i+1];
        }
        values[20] = {};
        return topElement;
}

    // Return the top value
    T Top(){
        if(values[0]) return values[0];
        else return 0;
}

    // Return the size of the stack
    int Size(){
        if(!values){
            return 0;
        }
        else{
            int arraySize = 0;
            for (int i = 0; i &lt; 20; i++){
                if(values[i]) arraySize++;
            }
            return arraySize;   
        }
    }

    // Output the stack
    void PrintStack(){
        std::cout &lt;&lt; std::endl;
        for(int i = 0; i &lt; this-&gt;Size(); i++){
            std::cout &lt;&lt; "  - " &lt;&lt; values[i] &lt;&lt; std::endl;
        }
        std::cout &lt;&lt; std::endl &lt;&lt; " -&gt; Stack Size: " &lt;&lt; this-&gt;Size() &lt;&lt; std::endl;
        std::cout &lt;&lt; " ____________________" &lt;&lt; std::endl;
        std::cout &lt;&lt; std::endl;
    }

private:
    T values[20] = {};
    
};
    // Driver function for the Stack Class
    void Start(){
        using namespace std;
        char choice;
        char value;
        Stack &lt;char&gt;testStack;
        do{
            if (system("clear")) system("CLS");
            
            cout &lt;&lt; "  (p)ush | p(o)p | (c)lear | (i)sEmpty | (t)op | (q)uit" &lt;&lt; endl &lt;&lt; endl;
            cout &lt;&lt; "  -STACK-" &lt;&lt; endl;
            testStack.PrintStack();
            cout &lt;&lt; endl &lt;&lt; endl;
            cout &lt;&lt; " -&gt; Command: ";

            cin &gt;&gt; choice;
            choice = toupper(choice);

            switch(choice){
                case 'P':
                    cout &lt;&lt; " -&gt; Enter The value to PUSH to the Stack: ";
                    cin &gt;&gt; value;
                    testStack.Push(value);
                break;
                case 'O':
                    value = testStack.Pop();
                    if(value){
                        cout &lt;&lt; endl &lt;&lt; " -&gt; " &lt;&lt; value &lt;&lt; " was Popped from the Stack.\n -&gt; Hit Enter.";
                    }
                    else{
                        cout &lt;&lt; endl &lt;&lt; " -&gt; There are no values in the Stack.\n -&gt; Hit Enter";
                    }
                    cin.ignore();
                    cin.get();
                break;
                case 'C':
                    testStack.Clear();;
                break;
                case 'I':
                    cout &lt;&lt; " -&gt; The Stack is ";

                    if(testStack.IsEmpty()) cout &lt;&lt; "EMPTY";
                    else cout &lt;&lt; "NOT EMPTY";
                    
                    cout &lt;&lt; endl &lt;&lt; "Press Enter";
                    cin.ignore();
                    cin.get();
                break;
                case 'T':
                    if(testStack.Top()) cout &lt;&lt; " -&gt; The Top value is " &lt;&lt; testStack.Top();
                    else cout &lt;&lt; " -&gt; There are no values in the Stack.";

 
                    cout &lt;&lt; endl &lt;&lt; "Press Enter";
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
    return 0;
}