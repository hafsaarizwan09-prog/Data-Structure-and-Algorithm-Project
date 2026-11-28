#include <iostream>
#include <string>
#include <limits>
using namespace std;

struct Book {
    int id;
    string title;
    string author;
    bool available;
    string issuedTo;
    Book* next;
    Book* prev;
};

Book* head = nullptr;
Book* tail = nullptr;

// Check whether the Circular Doubly Linked List is empty.
bool isEmpty() {
    return head == nullptr;
}

// Search helper used by update and delete.
Book* findBook(int bookID) {
    if (isEmpty()) {
        return nullptr;
    }

    Book* current = head;
    do {
        if (current->id == bookID) {
            return current;
        }
        current = current->next;
    } while (current != head);

    return nullptr;
}

// Display all information of one book.
void displayBookInfo(Book* book) {
    cout << "\n---------- BOOK INFORMATION ----------\n";
    cout << "Book ID: " << book->id << '\n';
    cout << "Title: " << book->title << '\n';
    cout << "Author: " << book->author << '\n';
    cout << "Status: " << (book->available ? "Available" : "Issued") << '\n';

    if (!book->available) {
        cout << "Issued To: " << book->issuedTo << '\n';
    } else {
        cout << "Issued To: Not issued\n";
    }

    cout << "--------------------------------------\n";
}

// Day 1: Add a new book at the end of the list.
void addBook() {
    int id;
    cout << "\nEnter Book ID: ";
    cin >> id;

    if (findBook(id) != nullptr) {
        cout << "A book with this ID already exists.\n";
        return;
    }

    Book* newBook = new Book;
    newBook->id = id;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Enter Book Title: ";
    getline(cin, newBook->title);

    cout << "Enter Author Name: ";
    getline(cin, newBook->author);

    newBook->available = true;
    newBook->issuedTo = "";

    if (isEmpty()) {
        head = tail = newBook;
        newBook->next = newBook;
        newBook->prev = newBook;
    } else {
        newBook->prev = tail;
        newBook->next = head;
        tail->next = newBook;
        head->prev = newBook;
        tail = newBook;
    }

    cout << "Book added successfully.\n";
}

// Display books from head to tail.
void displayBooks() {
    if (isEmpty()) {
        cout << "\nNo books available.\n";
        return;
    }

    Book* current = head;
    cout << "\n========== ALL BOOKS ==========\n";

    do {
        displayBookInfo(current);
        current = current->next;
    } while (current != head);
}

// Display books from tail to head.
void reverseDisplay() {
    if (isEmpty()) {
        cout << "\nNo books available.\n";
        return;
    }

    Book* current = tail;
    cout << "\n====== BOOKS IN REVERSE ======\n";

    do {
        displayBookInfo(current);
        current = current->prev;
    } while (current != tail);
}

// Count total nodes in the list.
int countBooks() {
    if (isEmpty()) {
        return 0;
    }

    int count = 0;
    Book* current = head;

    do {
        count++;
        current = current->next;
    } while (current != head);

    return count;
}

// Day 3: Update title and author without changing other book information.
void updateBook() {
    if (isEmpty()) {
        cout << "\nLibrary is empty. No book to update.\n";
        return;
    }

    int id;
    cout << "\nEnter Book ID to update: ";
    cin >> id;

    Book* current = findBook(id);

    if (current == nullptr) {
        cout << "Book not found.\n";
        return;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Current Title: " << current->title << '\n';
    cout << "Enter New Title: ";
    getline(cin, current->title);

    cout << "Current Author: " << current->author << '\n';
    cout << "Enter New Author: ";
    getline(cin, current->author);

    // ID, availability and issuedTo remain unchanged.
    cout << "Book details updated successfully.\n";
}

// Day 3: Delete a book, if it is not issued.
void deleteBook() {
    if (isEmpty()) {
        cout << "\nLibrary is empty. No book to delete.\n";
        return;
    }

    int id;
    cout << "\nEnter Book ID to delete: ";
    cin >> id;

    Book* target = findBook(id);

    if (target == nullptr) {
        cout << "Book not found.\n";
        return;
    }

    if (!target->available) {
        cout << "Cannot delete this book. It is currently issued to "
             << target->issuedTo << ".\n";
        return;
    }

    // Case 1: The list contains only one node.
    if (target == head && target == tail) {
        head = nullptr;
        tail = nullptr;
    }
    // Case 2: Delete the first node.
    else if (target == head) {
        head = head->next;
        head->prev = tail;
        tail->next = head;
    }
    // Case 3: Delete the last node.
    else if (target == tail) {
        tail = tail->prev;
        tail->next = head;
        head->prev = tail;
    }
    // Case 4: Delete a middle node.
    else {
        target->prev->next = target->next;
        target->next->prev = target->prev;
    }

    delete target;
    cout << "Book deleted successfully.\n";
}

// Day 4: Search for a book using its ID.
void searchByID() {
    if (isEmpty()) {
        cout << "\nLibrary is empty. No books to search.\n";
        return;
    }

    int id;
    cout << "\nEnter Book ID to search: ";
    cin >> id;

    Book* current = head;

    // Linear traversal through the circular list.
    do {
        if (current->id == id) {
            cout << "\nBook found successfully.\n";
            displayBookInfo(current);
            return;
        }

        current = current->next;
    } while (current != head);

    cout << "Book Not Found.\n";
}

// Day 4: Search using exact title matching.
void searchByTitle() {
    if (isEmpty()) {
        cout << "\nLibrary is empty. No books to search.\n";
        return;
    }

    string searchTitle;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "\nEnter complete Book Title: ";
    getline(cin, searchTitle);

    Book* current = head;

    // Exact comparison: case and spaces must match.
    do {
        if (current->title == searchTitle) {
            cout << "\nBook found successfully.\n";
            displayBookInfo(current);
            return;
        }

        current = current->next;
    } while (current != head);

    cout << "Book Not Found.\n";
}

// Search Books submenu.
void searchBooksMenu() {
    int choice;

    do {
        cout << "\n========== SEARCH BOOKS ==========\n";
        cout << "1. Search by Book ID\n";
        cout << "2. Search by Book Title\n";
        cout << "3. Back to Main Menu\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                searchByID();
                break;

            case 2:
                searchByTitle();
                break;

            case 3:
                cout << "Returning to Main Menu...\n";
                break;

            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 3);
}

// Book Management submenu from previous days.
void bookManagementMenu() {
    int choice;

    do {
        cout << "\n====== BOOK MANAGEMENT ======\n";
        cout << "1. Add Book\n";
        cout << "2. Display All Books\n";
        cout << "3. Display Books in Reverse\n";
        cout << "4. Update Book\n";
        cout << "5. Delete Book\n";
        cout << "6. Back to Main Menu\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addBook();
                break;

            case 2:
                displayBooks();
                break;

            case 3:
                reverseDisplay();
                break;

            case 4:
                updateBook();
                break;

            case 5:
                deleteBook();
                break;

            case 6:
                cout << "Returning to Main Menu...\n";
                break;

            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 6);
}

int main() {
    int choice;

    do {
        cout << "\n======= LIBRARY MANAGEMENT SYSTEM =======\n";
        cout << "1. Book Management\n";
        cout << "2. Search Books\n";
        cout << "3. Count Books\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                bookManagementMenu();
                break;

            case 2:
                searchBooksMenu();
                break;

            case 3:
                cout << "\nTotal Books: " << countBooks() << '\n';
                break;

            case 4:
                cout << "Exiting Library Management System...\n";
                break;

            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 4);

    // Release all dynamically allocated nodes before program termination.
    while (!isEmpty()) {
        Book* temp = head;

        if (head == tail) {
            head = nullptr;
            tail = nullptr;
        } else {
            head = head->next;
            head->prev = tail;
            tail->next = head;
        }

        delete temp;
    }

    return 0;
}
