#include <iostream>
#include <string>
#include <limits>
using namespace std;

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

BookNode *head = NULL;
BookNode *tail = NULL;

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

    if (head == NULL)
    {
        head = newNode;
        tail = newNode;

        newNode->next = head;
        newNode->prev = tail;
    }
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

void bookManagement()
{
    int choice;

    do
    {
        cout << "\n========== BOOK MANAGEMENT ==========\n";
        cout << "1. Add Book\n";
        cout << "2. Back to Main Menu\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice)
        {
            case 1:
                addBook();
                break;

            case 2:
                cout << "\nReturning to Main Menu...\n";
                break;

            default:
                cout << "\nInvalid choice! Try again.\n";
        }

    } while (choice != 2);
}
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
        cout << "2. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice)
        {
            case 1:
                bookManagement();
                break;

            case 2:
                cout << "\nExiting Library Management System...\n";
                break;

            default:
                cout << "\nInvalid choice! Try again.\n";
        }

    } while (choice != 2);

    clearCatalogue();

    return 0;
}
