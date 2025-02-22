#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

class Book {
public:
    int id;
    string title;
    string author;
    string status; 
    string issuedTo;

   
    Book() : id(0), title(""), author(""), status("available"), issuedTo("") {}

  
    Book(int id, const string &title, const string &author)
        : id(id), title(title), author(author), status("available"), issuedTo("") {}
};

class Library {
private:
    vector<Book> books;

    void merge(vector<Book> &books, int left, int mid, int right) {
        int n1 = mid - left + 1;
        int n2 = right - mid;

        vector<Book> leftArray(n1);
        vector<Book> rightArray(n2);

        for (int i = 0; i < n1; i++)
            leftArray[i] = books[left + i];
        for (int i = 0; i < n2; i++)
            rightArray[i] = books[mid + 1 + i];

        int i = 0, j = 0, k = left;
        while (i < n1 && j < n2) {
            if (leftArray[i].id <= rightArray[j].id) {
                books[k] = leftArray[i];
                i++;
            } else {
                books[k] = rightArray[j];
                j++;
            }
            k++;
        }

        while (i < n1) {
            books[k] = leftArray[i];
            i++;
            k++;
        }

        while (j < n2) {
            books[k] = rightArray[j];
            j++;
            k++;
        }
    }

    void mergeSort(vector<Book> &books, int left, int right) {
        if (left < right) {
            int mid = left + (right - left) / 2;

            mergeSort(books, left, mid);
            mergeSort(books, mid + 1, right);

            merge(books, left, mid, right);
        }
    }

public:
    void addBook(int id, const string &title, const string &author) {
        Book newBook(id, title, author);
        books.push_back(newBook);
    }

    Book* searchBookById(int id) {
        for (vector<Book>::iterator it = books.begin(); it != books.end(); ++it) {
            if (it->id == id) {
                return &(*it);
            }
        }
        return NULL;
    }

    Book* searchBookByTitle(const string &title) {
        for (vector<Book>::iterator it = books.begin(); it != books.end(); ++it) {
            if (it->title == title) {
                return &(*it);
            }
        }
        return NULL;
    }

    void issueBook(int id, const string &studentName) {
        Book* book = searchBookById(id);
        if (book != NULL && book->status == "available") {
            book->status = "issued";
            book->issuedTo = studentName;
        } else {
            cout << "Book not available.\n";
        }
    }

    void returnBook(int id) {
        Book* book = searchBookById(id);
        if (book != NULL && book->status == "issued") {
            book->status = "available";
            book->issuedTo = "";
        } else {
            cout << "Book not issued.\n";
        }
    }

    void listBooks() {
        mergeSort(books, 0, books.size() - 1);
        for (vector<Book>::iterator it = books.begin(); it != books.end(); ++it) {
            cout << "ID: " << it->id << ", Title: " << it->title << ", Author: " << it->author << ", Status: " << it->status << "\n";
        }
    }

    void deleteBook(int id) {
        for (vector<Book>::iterator it = books.begin(); it != books.end(); ) {
            if (it->id == id) {
                it = books.erase(it);
            } else {
                ++it;
            }
        }
    }
};

int main() {
    Library library;
    int choice;

    do {
        cout << "\nLibrary Management System\n";
        cout << "1. Add Book to your account\n";
        cout << "2. Search Book by ID\n";
        cout << "3. Search Book by Title\n";
        cout << "4. Issued Book\n";
        cout << "5. Return Book\n";
        cout << "6. List of Books\n";
        cout << "7. Delete Book from your account\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int id;
                string title, author;
                cout << "Enter book ID: ";
                cin >> id;
                cin.ignore();
                cout << "Enter book title: ";
                getline(cin, title);
                cout << "Enter book author: ";
                getline(cin, author);
                library.addBook(id, title, author);
                break;
            }
            case 2: {
                int id;
                cout << "Enter book ID: ";
                cin >> id;
                Book* book = library.searchBookById(id);
                if (book != NULL) {
                    cout << "Book found: " << book->title << "\n";
                } else {
                    cout << "Book not found.\n";
                }
                break;
            }
            case 3: {
                string title;
                cout << "Enter book title: ";
                cin.ignore();
                getline(cin, title);
                Book* book = library.searchBookByTitle(title);
                if (book != NULL) {
                    cout << "Book found: " << book->title << "\n";
                } else {
                    cout << "Book not found.\n";
                }
                break;
            }
            case 4: {
                int id;
                string studentName;
                cout << "Enter book ID: ";
                cin >> id;
                cin.ignore();
                cout << "Enter student name: ";
                getline(cin, studentName);
                library.issueBook(id, studentName);
                break;
            }
            case 5: {
                int id;
                cout << "Enter book ID: ";
                cin >> id;
                library.returnBook(id);
                break;
            }
            case 6: {
                library.listBooks();
                break;
            }
            case 7: {
                int id;
                cout << "Enter book ID: ";
                cin >> id;
                library.deleteBook(id);
                break;
            }
            case 8: {
                cout << "Exiting...\n";
                break;
            }
            default: {
                cout << "Invalid choice. Please try again.\n";
            }
        }
    } while (choice != 8);

    return 0;
}
