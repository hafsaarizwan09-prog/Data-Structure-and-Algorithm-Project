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

bool isEmpty() {
    return head == nullptr;
}

Book* findBook(int bookID) {
    if (isEmpty()) return nullptr;

    Book* current = head;
    do {
        if (current->id == bookID) return current;
        current = current->next;
    } while (current != head);

    return nullptr;
}

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

void displayBooks() {
    if (isEmpty()) {
        cout << "\nNo books available.\n";
        return;
    }

    Book* current = head;
    cout << "\n========== ALL BOOKS ==========\n";

    do {
        cout << "Book ID: " << current->id << '\n';
        cout << "Title: " << current->title << '\n';
        cout << "Author: " << current->author << '\n';
        cout << "Status: " << (current->available ? "Available" : "Issued") << '\n';
        if (!current->available) {
            cout << "Issued To: " << current->issuedTo << '\n';
        }
        cout << "------------------------------\n";
        current = current->next;
    } while (current != head);
}

void reverseDisplay() {
    if (isEmpty()) {
        cout << "\nNo books available.\n";
        return;
    }

    Book* current = tail;
    cout << "\n====== BOOKS IN REVERSE ======\n";

    do {
        cout << "Book ID: " << current->id
             << " | Title: " << current->title
             << " | Author: " << current->author << '\n';
        current = current->prev;
    } while (current != tail);
}

int countBooks() {
    if (isEmpty()) return 0;

    int count = 0;
    Book* current = head;
    do {
        count++;
        current = current->next;
    } while (current != head);

    return count;
}

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

    cout << "Book details updated successfully.\n";
}

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
    if (target == head && target == tail) {
        head = nullptr;
        tail = nullptr;
    }
    else if (target == head) {
        head = head->next;
        head->prev = tail;
        tail->next = head;
    }
    else if (target == tail) {
        tail = tail->prev;
        tail->next = head;
        head->prev = tail;
    }
    else {
        target->prev->next = target->next;
        target->next->prev = target->prev;
    }

    delete target;
    cout << "Book deleted successfully.\n";
}

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
        cout << "2. Count Books\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                bookManagementMenu();
                break;
            case 2:
                cout << "\nTotal Books: " << countBooks() << '\n';
                break;
            case 3:
                cout << "Exiting Library Management System...\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 3);
    while (!isEmpty()) {
        Book* temp = head;
        if (head == tail) {
            head = tail = nullptr;
        } else {
            head = head->next;
            head->prev = tail;
            tail->next = head;
        }
        delete temp;
    }

    return 0;
}
