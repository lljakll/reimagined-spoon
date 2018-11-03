// basic linked list example
// https://www.youtube.com/watch?v=3F931zdWPGw
#ifdef __cplusplus__
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif

#include <iostream>
#include <string>
#include <limits>

using namespace std;

// set up self-ref struct
struct Book{
    string title;
    Book *next;
};

Book *add_node(Book *in_root);
void print_list( Book *in_root );

int main()
{
    Book *head = NULL;

    char choice;

    do{
        if (system("CLS")) system("clear");
        cout << "A)dd node" << endl;
        cout << "P)rint list" << endl;
        cout << "Q)uit program" << endl;
        cin >> choice;
    
        choice = toupper(choice);

        switch(choice)
        {
            case 'A':
                head = add_node( head );
                break;
            case 'P':
                print_list( head );
                break;
            case 'Q':
                break;
            default:
                cout << "Invalid choice..." << endl;
        }
    }
    while(choice != 'Q');
    return 0;
}

Book *add_node(Book *in_root)
// ======================================
// ADD A NEW NODE
// ======================================
{
    Book *next_ptr = NULL;
    Book *prev_ptr = NULL;

    if( in_root == NULL )
    {
        // list is empty
        if( (in_root = new Book) != NULL)
        {
            next_ptr = in_root;

            cout << "Title: ";
            cin >> next_ptr->title;

            next_ptr->next = NULL;
        }
        else
        {
            cout << "ERROR: unable to allocate memory." << endl;
            return NULL;
        }
        return next_ptr;
    }
    else
    {
        // list has members
        next_ptr = in_root;
        while( next_ptr->next !=NULL)
        {
            next_ptr = next_ptr->next;
        }
        prev_ptr = next_ptr;

        if( (next_ptr = new Book) != NULL)
        {
            prev_ptr->next = next_ptr;

            cout << "Title: ";
            cin >> next_ptr->title;

            next_ptr->next = NULL;
        }
        else{
            cout << "ERROR: Unable to allocate memory" << endl;
        }
        return in_root;
    }
}

void print_list( Book *in_root )
// =====================================
// PRINT LIST CONTENTS
// =====================================
{
    Book *next_ptr;

    next_ptr = in_root;

    if( next_ptr == NULL )
    {
        cout << "EMPTY LIST: No nodes to print..." << endl;

    }
    else
    {
        while( next_ptr != NULL )
        {
            cout << next_ptr->title << endl;
            next_ptr = next_ptr->next;
        }
    }
    cout << "Press Enter to continue." << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}
