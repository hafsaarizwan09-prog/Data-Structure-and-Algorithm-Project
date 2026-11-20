
#include <iostream>
#include <string>
using namespace std;

struct BookNode
{
    int bookID;
    string title;
    string author;
    bool availability;

    BookNode* next;
    BookNode* prev;
};

BookNode* head = NULL;
BookNode* tail = NULL;

void addBook()
{
    int id;
    string bookTitle, bookAuthor;

    cout << "\nEnter Book ID: ";
    cin >> id;

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

    BookNode* newBook = new BookNode;

    newBook->bookID = id;
    newBook->title = bookTitle;
    newBook->author = bookAuthor;
    newBook->availability = true;

    if (head == NULL)
    {
        head = newBook;
        tail = newBook;

        newBook->next = newBook;
        newBook->prev = newBook;
    }

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


void displayBooksForward()
{
    if (head == NULL)
    {
        cout << "\nNo books available!\n";
        return;
    }

    BookNode* temp = head;

    cout << "\n===== BOOKS FORWARD =====\n";

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
void displayBooksBackward()
{
    if (tail == NULL)
    {
        cout << "\nNo books available!\n";
        return;
    }

    BookNode* temp = tail;

    cout << "\n===== BOOKS BACKWARD =====\n";

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

void deleteBook(int id)
{
    if (head == NULL)
    {
        cout << "\nLibrary is empty. No book to delete!\n";
        return;
    }

    BookNode* temp = head;

    do
    {
        if (temp->bookID == id)
        {
            break;
        }

        temp = temp->next;

    } while (temp != head);

    if (temp == head && temp->bookID != id)
    {
        cout << "\nBook ID not found!\n";
        return;
    }

    if (head == tail)
    {
        delete temp;

        head = NULL;
        tail = NULL;
    }

    else if (temp == head)
    {
        head = head->next;

        head->prev = tail;
        tail->next = head;

        delete temp;
    }

    else if (temp == tail)
    {
        tail = tail->prev;

        tail->next = head;
        head->prev = tail;

        delete temp;
    }

    else
    {
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;

        delete temp;
    }

    cout << "\nBook deleted successfully!\n";
}

void updateBook(int id)
{
    if (head == NULL)
    {
        cout << "\nLibrary is empty. No book to update!\n";
        return;
    }

    BookNode* temp = head;

    do
    {
        if (temp->bookID == id)
        {
            cout << "\nBook Found!\n";

            cout << "Current Title: " << temp->title << endl;
            cout << "Current Author: " << temp->author << endl;

            cin.ignore();

            cout << "\nEnter New Title: ";
            getline(cin, temp->title);

            cout << "Enter New Author: ";
            getline(cin, temp->author);

            cout << "\nBook updated successfully!\n";

            return;
        }

        temp = temp->next;

    } while (temp != head);

    cout << "\nBook ID not found!\n";
}


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
    int id;

    do
    {
        cout << "\n\n===== LIBRARY MANAGEMENT SYSTEM =====\n";
        cout << "1. Add Book\n";
        cout << "2. Display Forward\n";
        cout << "3. Display Backward\n";
        cout << "4. Count Books\n";
        cout << "5. Delete Book\n";
        cout << "6. Update Book\n";
        cout << "7. Exit\n";

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
                cout << "\nTotal Books: "
                     << countBooks() << endl;
                break;

            case 5:
                cout << "\nEnter Book ID to delete: ";
                cin >> id;

                deleteBook(id);
                break;

            case 6:
                cout << "\nEnter Book ID to update: ";
                cin >> id;

                updateBook(id);
                break;

            case 7:
                clearBooks();

                cout << "\nExiting Library Management System...\n";
                break;

            default:
                cout << "\nInvalid choice! Try again.\n";
        }

    } while (choice != 7);

    return 0;
}
