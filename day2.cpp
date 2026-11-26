#include <iostream>
#include <string>
#include <limits>
using namespace std;

// Structure for storing book information
struct BookNode
{
    int id;
    string title;
    string author;
    bool available;
    string issuedTo;

    BookNode *next;
    BookNode *prev;
};

// Head and tail pointers
BookNode *head = NULL;
BookNode *tail = NULL;

// Check whether a book ID already exists
bool isDuplicate(int bookID)
{
    if (head == NULL)
    {
        return false;
    }

    BookNode *temp = head;

    do
    {
        if (temp->id == bookID)
        {
            return true;
        }

        temp = temp->next;

    } while (temp != head);

    return false;
}

// Day 1: Add a new book
void addBook()
{
    int id;
    string title, author;

    cout << "\nEnter Book ID: ";
    cin >> id;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (isDuplicate(id))
    {
        cout << "\nBook ID already exists! Try another ID.\n";
        return;
    }

    cout << "Enter Book Title: ";
    getline(cin, title);

    cout << "Enter Author Name: ";
    getline(cin, author);

    BookNode *newNode = new BookNode;

    newNode->id = id;
    newNode->title = title;
    newNode->author = author;
    newNode->available = true;
    newNode->issuedTo = "";

    // First book
    if (head == NULL)
    {
        head = newNode;
        tail = newNode;

        newNode->next = head;
        newNode->prev = tail;
    }
    // Additional books
    else
    {
        newNode->next = head;
        newNode->prev = tail;

        tail->next = newNode;
        head->prev = newNode;

        tail = newNode;
    }

    cout << "\nBook added successfully!\n";
}

// Day 2: Display books from head to tail
void displayBooks()
{
    if (head == NULL)
    {
        cout << "\nCatalogue is empty. No books to display.\n";
        return;
    }

    BookNode *temp = head;

    cout << "\n========== ALL BOOKS ==========\n";

    do
    {
        cout << "\nBook ID: " << temp->id;
        cout << "\nTitle: " << temp->title;
        cout << "\nAuthor: " << temp->author;

        if (temp->available == true)
        {
            cout << "\nAvailability: Available\n";
        }
        else
        {
            cout << "\nAvailability: Issued\n";
        }

        cout << "------------------------------\n";

        temp = temp->next;

    } while (temp != head);
}

// Day 2: Display books from tail to head
void displayReverse()
{
    if (head == NULL)
    {
        cout << "\nCatalogue is empty. No books to display.\n";
        return;
    }

    BookNode *temp = tail;

    cout << "\n====== BOOKS IN REVERSE ORDER ======\n";

    do
    {
        cout << "\nBook ID: " << temp->id;
        cout << "\nTitle: " << temp->title;
        cout << "\nAuthor: " << temp->author;

        if (temp->available == true)
        {
            cout << "\nAvailability: Available\n";
        }
        else
        {
            cout << "\nAvailability: Issued\n";
        }

        cout << "------------------------------\n";

        temp = temp->prev;

    } while (temp != tail);
}

// Day 2: Count all books in the circular list
int countBooks()
{
    if (head == NULL)
    {
        return 0;
    }

    int count = 0;
    BookNode *temp = head;

    do
    {
        count++;
        temp = temp->next;

    } while (temp != head);

    return count;
}

// Day 1 and Day 2: Book Management Menu
void bookManagement()
{
    int choice;

    do
    {
        cout << "\n========== BOOK MANAGEMENT ==========\n";
        cout << "1. Add Book\n";
        cout << "2. Display All Books\n";
        cout << "3. Display Books in Reverse\n";
        cout << "4. Back to Main Menu\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice)
        {
            case 1:
                addBook();
                break;

            case 2:
                displayBooks();
                break;

            case 3:
                displayReverse();
                break;

            case 4:
                cout << "\nReturning to Main Menu...\n";
                break;

            default:
                cout << "\nInvalid choice! Try again.\n";
        }

    } while (choice != 4);
}

// Release dynamically allocated memory
void clearCatalogue()
{
    if (head == NULL)
    {
        return;
    }

    BookNode *temp = head;

    while (temp != tail)
    {
        BookNode *nextNode = temp->next;
        delete temp;
        temp = nextNode;
    }

    delete tail;

    head = NULL;
    tail = NULL;
}

int main()
{
    int choice;

    do
    {
        cout << "\n====================================\n";
        cout << "       LIBRARY MANAGEMENT SYSTEM\n";
        cout << "====================================\n";
        cout << "1. Book Management\n";
        cout << "2. Count Books\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice)
        {
            case 1:
                bookManagement();
                break;

            case 2:
                cout << "\nTotal number of books: " << countBooks() << "\n";
                break;

            case 3:
                cout << "\nExiting Library Management System...\n";
                break;

            default:
                cout << "\nInvalid choice! Try again.\n";
        }

    } while (choice != 3);

    clearCatalogue();

    return 0;
}
