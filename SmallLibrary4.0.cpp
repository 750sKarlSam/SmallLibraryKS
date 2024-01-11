#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
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

public:
    Librarian(int StaffID, string MyName, string MyEmail, string MyAddress, int StaffSalary)
        : StaffIDNum(StaffID), StaffSalary(StaffSalary) {}

    void addMember() {
        static int memberIDCounter = 1;
        string MyName, MyEmail, MyAddress;

        cout << "Insert your name: ";
        cin >> MyName;

        cout << "Enter your email: ";
        cin >> MyEmail;

        cout << "Enter your current address: ";
        cin >> MyAddress;

        members.push_back(new Member(memberIDCounter++, MyName, MyEmail, MyAddress));

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

    // Add other functions for returning books, displaying borrowed books, calculating fines, etc.

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
        // Implement similar logic to find a book based on its ID
        return nullptr;
    }
};

    time_t now = time(0);
    char* dt = ctime (
        &now);

int main() {


    ifstream file("library_books.csv");

    if (!file.is_open()) {
        cout << "Error opening the file!" << endl;
        return 1; 
    }

    vector<Book*> Books;

    int BookID;
    string BookName;
    int PageCount;
    string AuthorFirstName;
    string AuthorLastName;
    string BookType;

    string tempString;
    string line;

    while (getline(file, line)){
        
        

        stringstream inputString(line);
        //This code will help retrieve the ID of a book within the library achieve
        getline(inputString, tempString, ',');
        BookID = atoi(tempString.c_str());

        getline(inputString, BookName, ',');

        //This code will help retrieve the amount of pages within each book
        getline(inputString, tempString, ',');
        PageCount = atoi(tempString.c_str());

        getline(inputString, AuthorFirstName, ',');
        getline(inputString, AuthorLastName, ',');
        getline(inputString, BookType, ',');


         Books.push_back(new Book(BookID, BookName, AuthorFirstName, AuthorLastName ));

        line = "";
    }

    // Display each book - RM
    cout << "Loaded Books:" << endl;
    for (const auto& book : Books) {
        cout << "Book ID: " << (*book).getBookID() << ", Name: " << (*book).getBookName()
        << ", Author: " << (*book).getAuthorFirstName() << " " << (*book).getAuthorLastName() << endl;
    }





    Librarian librarian(1, "LibrarianName", "LibrarianEmail", "LibrarianAddress", 50000);

    int user;

    int AddM = 1;
    int SB = 2;
    int SM = 3;
    int IB = 4;
    int RB = 5;
    int ES = 6;
    
//This gets the current date and time within the system
    time_t now = time(0);
//This is the convertion turning the date and time into single strings types
    char* dt = ctime(&now);

    cout << "The current local date and time: " <<dt << endl;

    cout << "Hello and Welcome to Cozy's Library " << endl;

    do {
        cout << "[-Menu-]" << endl;
        cout << "Please select a service from 1 to 6" << endl;
        cout << AddM << " Add Member " << endl;
        cout << SB << " Search BookID " << endl;
        cout << SM << " Search MemberID " << endl;
        cout << IB << " Issue A Book " << endl;
        cout << RB << " Return A Book " << endl;
        cout << ES << " End Service " << endl;

        cin >> user;

        switch (user) {
            case 1:
                librarian.addMember();
                break;
            // Add cases for other services
            case 6:
                cout << "Exiting the program." << endl;
                break;
            default:
                cout << "Invalid option. Please try again." << endl;
                break;
        }
    } while (user != 6);

    // Your menu handling and other parts of the main function...

    return 0;
}