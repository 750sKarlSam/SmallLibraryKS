#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <ctime>
#include <unistd.h>

using namespace std;

class Book {
private:
    int bookID;
    string bookName;
    string authorFirstName;
    string authorLastName;

public:
    Book(int bookID, string bookName, string authorFirstName, string authorLastName)
        : bookID(bookID), bookName(bookName), authorFirstName(authorFirstName), authorLastName(authorLastName) {}

    int getBookID() const { return bookID; }
    string getBookName() const { return bookName; }
    string getAuthorFirstName() const { return authorFirstName; }
    string getAuthorLastName() const { return authorLastName; }
};

class Member {
private:
    int memberID;
    vector<Book*> booksLoaned;

public:
    Member(int memberID, string MyName, string MyEmail, string MyAddress)
        : memberID(memberID) {}

    int getMemberID() const { return memberID; }
    vector<Book*> getBooksBorrowed() const { return booksLoaned; }

    void setBooksBorrowed(const vector<Book*>& books) {
        booksLoaned = books;
    }
};

class Librarian {
private:
    int StaffIDNum;
    int StaffSalary;
    vector<Member*> members;
    vector<Book*> Books;

public:
    Librarian(int StaffID, string MyName, string MyEmail, string MyAddress, int StaffSalary)
        : StaffIDNum(StaffID), StaffSalary(StaffSalary) {}

    vector<Book*>& getBooks() { return Books; }

    void addMember() {
        static int memberIDCounter = 1;
        string MyName, MyEmail, MyAddress;

        cout << "Insert your name: ";
        cin >> MyName;

        cout << "Enter your email: ";
        cin >> MyEmail;

        cout << "Enter your current address: ";
        cin >> MyAddress;

        Member* newMember = new Member(memberIDCounter++, MyName, MyEmail, MyAddress);
        members.push_back(newMember);

        cout << "Library Member Creation Successful" << endl;
        cout << "ID: " << memberIDCounter - 1 << endl;
        cout << "Member Name: " << MyName << endl;
        cout << "Member Address: " << MyAddress << endl;
        cout << "Member Email: " << MyEmail << endl;
    }

    void issueBook(int memberID, int bookID) {
        Member* member = findMemberByID(memberID);
        Book* book = findBookByID(bookID);

        if (member && book) {
            member->getBooksBorrowed().push_back(book);
            cout << "Book issued successfully." << endl;
        } else {
            cout << "Member or book not found." << endl;
        }
    }

    void returnBook(int memberID, int bookID) {
        Member* member = findMemberByID(memberID);
        Book* book = findBookByID(bookID);

        if (member && book) {
            // Assume the book is returned today
            time_t now = time(0);

            // Calculate fines based on return date and due date
            int fine = calculateFine(member, book, now);
            
            if (fine > 0) {
                cout << "Late return fine: " << fine << " pounds." << endl;
            } else {
                cout << "Book returned successfully." << endl;
            }
        } else {
            cout << "Member or book not found." << endl;
        }
    }

    void searchBookByID(int bookID) {
        Book* book = findBookByID(bookID);
        if (book) {
            cout << "Book ID: " << book->getBookID() << ", Name: " << book->getBookName()
                 << ", Author: " << book->getAuthorFirstName() << " " << book->getAuthorLastName() << endl;
        } else {
            cout << "Book not found." << endl;
        }
    }

private:
    Member* findMemberByID(int memberID) {
        for (Member* member : members) {
            if (member->getMemberID() == memberID) {
                return member;
            }
        }
        return nullptr;
    }

    Book* findBookByID(int bookID) {
        for (Book* book : Books) {
            if (book->getBookID() == bookID) {
                return book;
            }
        }
        return nullptr;
    }

    int calculateFine(Member* member, Book* book, time_t returnDate) {
        // Assuming the due date is 3 days after issue
        const int daysAllowed = 3;
        const int finePerDay = 1;

        vector<Book*> borrowedBooks = member->getBooksBorrowed();

        for (const auto& borrowedBook : borrowedBooks) {
            if (borrowedBook == book) {
                time_t dueDate = returnDate;
                struct tm* dueDateStruct = localtime(&dueDate);
                dueDateStruct->tm_mday += daysAllowed;

                // Calculate the difference in days
                int daysLate = returnDate - mktime(dueDateStruct) / (60 * 60 * 24);

                if (daysLate > 0) {
                    return daysLate * finePerDay;
                }
            }
        }

        return 0; // No fine if returned on or before the due date
    }
};