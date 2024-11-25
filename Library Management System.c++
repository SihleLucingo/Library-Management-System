#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Book {
public:
    string title;
    string author;
    bool isAvailable;

    Book(string t, string a) : title(t), author(a), isAvailable(true) {}
};

class User {
public:
    string name;
    vector<string> borrowedBooks;

    User(string n) : name(n) {}

    void borrowBook(const string& bookTitle) {
        borrowedBooks.push_back(bookTitle);
    }

    void returnBook(const string& bookTitle) {
        for (auto it = borrowedBooks.begin(); it != borrowedBooks.end(); ++it) {
            if (*it == bookTitle) {
                borrowedBooks.erase(it);
                break;
            }
        }
    }

    void displayBorrowedBooks() const {
        cout << "Borrowed Books by " << name << ": ";
        if (borrowedBooks.empty()) {
            cout << "None";
        } else {
            for (const auto& book : borrowedBooks) {
                cout << book << " ";
            }
        }
        cout << endl;
    }
};

class Library {
private:
    vector<Book> books;
    vector<User> users;

public:
    void addBook(const string& title, const string& author) {
        books.emplace_back(title, author);
    }

    void addUser(const string& name) {
        users.emplace_back(name);
    }

    void borrowBook(const string& userName, const string& bookTitle) {
        for (auto& book : books) {
            if (book.title == bookTitle && book.isAvailable) {
                for (auto& user : users) {
                    if (user.name == userName) {
                        user.borrowBook(bookTitle);
                        book.isAvailable = false;
                        cout << userName << " borrowed " << bookTitle << endl;
                        return;
                    }
                }
            }
        }
        cout << "Book is not available or user does not exist." << endl;
    }

    void returnBook(const string& userName, const string& bookTitle) {
        for (auto& book : books) {
            if (book.title == bookTitle && !book.isAvailable) {
                for (auto& user : users) {
                    if (user.name == userName) {
                        user.returnBook(bookTitle);
                        book.isAvailable = true;
                        cout << userName << " returned " << bookTitle << endl;
                        return;
                    }
                }
            }
        }
        cout << "Book was not borrowed by this user." << endl;
    }

    void displayAvailableBooks() const {
        cout << "Available Books in Library:" << endl;
        for (const auto& book : books) {
            if (book.isAvailable) {
                cout << "- " << book.title << " by " << book.author << endl;
            }
        }
    }

    void displayUsers() const {
        cout << "Registered Users:" << endl;
        for (const auto& user : users) {
            cout << "- " << user.name << endl;
            user.displayBorrowedBooks();
        }
    }
};

int main() {
    Library library;

    // Adding books to the library
    library.addBook("1984", "George Orwell");
    library.addBook("To Kill a Mockingbird", "Harper Lee");
    library.addBook("The Great Gatsby", "F. Scott Fitzgerald");

    // Adding users to the library
    library.addUser("Alice");
    library.addUser("Bob");

    // Display available books
    library.displayAvailableBooks();

    // Borrowing and returning books
    library.borrowBook("Alice", "1984");
    library.borrowBook("Bob", "To Kill a Mockingbird");
    
    // Display available books after borrowing
    library.displayAvailableBooks();

    // Returning a book
    library.returnBook("Alice", "1984");
    
    // Display available books after returning
    library.displayAvailableBooks();

    // Display users and their borrowed books
    library.displayUsers();

    return 0;
}