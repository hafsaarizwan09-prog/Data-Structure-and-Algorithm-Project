
#include <iostream>
#include <string>
using namespace std;

// Structure of one book node
struct BookNode
{
    int bookID;
    string title;
    string author;
    bool availability;

    BookNode* next;
    BookNode* prev;
};

// Head and tail pointers
BookNode* head = NULL;
BookNode* tail = NULL;


// Function to add a new book
void addBook()
{
    int id;
    string bookTitle, bookAuthor;

    cout << "\nEnter Book ID: ";
    cin >> id;

    // Check for duplicate Book ID
    if (head != NULL)
    {
        BookNode* temp = head;

        do
        {
            if (temp->bookID == id)
            {
                cout << "\nBook ID already exists!\n";
                return;
            }

            temp = temp->next;

        } while (temp != head);
    }

    cin.ignore();

    cout << "Enter Book Title: ";
    getline(cin, bookTitle);

    cout << "Enter Book Author: ";
    getline(cin, bookAuthor);

    // Create a new node dynamically
    BookNode* newBook = new BookNode;

    newBook->bookID = id;
    newBook->title = bookTitle;
    newBook->author = bookAuthor;
    newBook->availability = true;

    // Case 1: Empty list
    if (head == NULL)
    {
        head = newBook;
        tail = newBook;

        newBook->next = newBook;
        newBook->prev = newBook;
    }

    // Case 2: List already contains books
    else
    {
        newBook->prev = tail;
        newBook->next = head;

        tail->next = newBook;
        head->prev = newBook;

        tail = newBook;
    }

    cout << "\nBook added successfully!\n";
}


// Function to display books from head to tail
void displayBooksForward()
{
    if (head == NULL)
    {
        cout << "\nNo books available!\n";
        return;
    }

    BookNode* temp = head;

    cout << "\n===== BOOKS (FORWARD) =====\n";

    do
    {
        cout << "\nBook ID: " << temp->bookID;
        cout << "\nTitle: " << temp->title;
        cout << "\nAuthor: " << temp->author;

        if (temp->availability == true)
            cout << "\nAvailability: Available\n";
        else
            cout << "\nAvailability: Not Available\n";

        temp = temp->next;

    } while (temp != head);
}


// Function to display books from tail to head
void displayBooksBackward()
{
    if (tail == NULL)
    {
        cout << "\nNo books available!\n";
        return;
    }

    BookNode* temp = tail;

    cout << "\n===== BOOKS (BACKWARD) =====\n";

    do
    {
        cout << "\nBook ID: " << temp->bookID;
        cout << "\nTitle: " << temp->title;
        cout << "\nAuthor: " << temp->author;

        if (temp->availability == true)
            cout << "\nAvailability: Available\n";
        else
            cout << "\nAvailability: Not Available\n";

        temp = temp->prev;

    } while (temp != tail);
}


// Function to count total books
int countBooks()
{
    if (head == NULL)
    {
        return 0;
    }

    int count = 0;
    BookNode* temp = head;

    do
    {
        count++;
        temp = temp->next;

    } while (temp != head);

    return count;
}


// Function to release dynamically allocated memory
void clearBooks()
{
    if (head == NULL)
    {
        return;
    }

    BookNode* current = head->next;

    while (current != head)
    {
        BookNode* temp = current;
        current = current->next;
        delete temp;
    }

    delete head;

    head = NULL;
    tail = NULL;
}


// Main function
int main()
{
    int choice;

    do
    {
        cout << "\n\n===== LIBRARY MANAGEMENT SYSTEM =====\n";
        cout << "1. Add Book\n";
        cout << "2. Display Books Forward\n";
        cout << "3. Display Books Backward\n";
        cout << "4. Count Books\n";
        cout << "5. Exit\n";

        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                addBook();
                break;

            case 2:
                displayBooksForward();
                break;

            case 3:
                displayBooksBackward();
                break;

            case 4:
                cout << "\nTotal Books: " << countBooks() << endl;
                break;

            case 5:
                clearBooks();
                cout << "\nExiting Library Management System...\n";
                break;

            default:
                cout << "\nInvalid choice! Try again.\n";
        }

    } while (choice != 5);

    return 0;
}
