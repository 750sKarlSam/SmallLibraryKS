#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <ctime>
#include <unistd.h>

using namespace std;

class Person {
    private:
    string name;
    string address;
    string email;
    public:
    Person(string name, string address, string email);

    
    string getName() { return name; };

    
     void setName(string name) { this->name; };

    string getAddress() { return address; };

    void setAddress(string address) { this->address; };

    string getEmail() { return email; };


    void setEmail(string email){ this->email; }
    
    };


class Book {
private:
    int bookID;
    string bookName;
    string authorFirstName;
    string authorLastName;
    time_t issueDate;  // New member variable to store the issue date

public:
    Book(int bookID, string bookName, string authorFirstName, string authorLastName)
        : bookID(bookID), bookName(bookName), authorFirstName(authorFirstName), authorLastName(authorLastName) {
        // Assume the book is issued when the object is created
        issueDate = time(0);
    }

    int getBookID() const { return bookID; }
    string getBookName() const { return bookName; }
    string getAuthorFirstName() const { return authorFirstName; }
    string getAuthorLastName() const { return authorLastName; }
    time_t getIssueDate() const { return issueDate; }  // Getter for issue date
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

    // void setBooksBorrowed(const vector<Book*>& books) {
    //     booksLoaned = books;
    // void setBooksBorrowed(const Book &book) {
    //     booksLoaned.push_back(new Book(book));
    void setBooksBorrowed(Book* book) {
    booksLoaned.push_back(book);
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
            vector<Book*> getBooksBorrowed = member->getBooksBorrowed();
            member->setBooksBorrowed(book);
            cout << "Book issued successfully." << endl;
            cout << "Member Data: " << endl;
            cout << "Member ID: " << member->getMemberID() << endl;
            cout << "Book Data" << endl;
            cout << "Book ID: " << book->getBookID() << endl;
            cout << "Book Name: " << book->getBookName() << endl;
            cout << "Author: " << book->getAuthorFirstName() << " " << book->getAuthorLastName() << endl;
            // cout << "Issue Date and Time: " << ctime(&(book->getIssueDate()));  // Display the issue date
        } else {
            cout << "Member or book not found." << endl;
        }
    }

    void displayBorrowedBooks(int memberID) {
        Member* member = findMemberByID(memberID);
        vector<Book*> getBooksBorrowed = member->getBooksBorrowed();

           cout << "Loaded Books:" << endl;
    for (const auto& book : getBooksBorrowed) {
        cout << "Book ID: " << (*book).getBookID() << ", Name: " << (*book).getBookName()
        << ", Author: " << (*book).getAuthorFirstName() << " " << (*book).getAuthorLastName() << endl;
    }

    }

    void returnBook(int memberID, int bookID) {
        Member* member = findMemberByID(memberID);
        Book* book = findBookByID(bookID);

        if (member && book) {
            // Assume the book is returned today
            time_t returnDate = time(0);

            // Calculate fines based on return date and due date
            int fine = calculateFine(member, book, returnDate);

            if (fine > 0) {
                cout << "Late return fine: " << fine << " pounds." << endl;
            } else {
                cout << "Book returned successfully." << endl;
            }

            // Display the issue date and time
            // cout << "Issue Date and Time: " << ctime(&(book->getIssueDate()));

            // Display the return date and time
            cout << "Return Date and Time: " << ctime(&returnDate);

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

        time_t dueDate = book->getIssueDate();
        struct tm* dueDateStruct = localtime(&dueDate);
        dueDateStruct->tm_mday += daysAllowed;

        // Calculate the difference in days
        int daysLate = returnDate - mktime(dueDateStruct) / (60 * 60 * 24);

        if (daysLate > 0) {
            return daysLate * finePerDay;
        }

        return 0; // No fine if returned on or before the due date
    }
};

time_t now = time(0);
char* dt = ctime(&now);

int main() {
    int userMemberID;
    int userBookID;

    ifstream file("library_books.csv");

    if (!file.is_open()) {
        cout << "Error opening the file!" << endl;
        return 1;
    }

    Librarian librarian(1, "LibrarianName", "LibrarianEmail", "LibrarianAddress", 50000);

    int BookID;
    string BookName;
    int PageCount;
    string AuthorFirstName;
    string AuthorLastName;
    string BookType;

    string tempString;
    string line;

    while (getline(file, line)) {
        stringstream inputString(line);
        getline(inputString, tempString, ',');
        BookID = atoi(tempString.c_str());

        getline(inputString, BookName, ',');
        getline(inputString, tempString, ',');
        PageCount = atoi(tempString.c_str());
        getline(inputString, AuthorFirstName, ',');
        getline(inputString, AuthorLastName, ',');
        getline(inputString, BookType, ',');

        librarian.getBooks().push_back(new Book(BookID, BookName, AuthorFirstName, AuthorLastName));

        line = "";
    }

    cout << "Loaded Books:" << endl;
    for (const auto& book : librarian.getBooks()) {
        cout << "Book ID: " << book->getBookID() << ", Name: " << book->getBookName()
             << ", Author: " << book->getAuthorFirstName() << " " << book->getAuthorLastName() << endl;
    }

    int user;

    int AddM = 1;
    int SB = 2;
    int SM = 3;
    int IB = 4;
    int RB = 5;
    int SBID = 6;  // Search Book by ID
    int ES = 7;

    cout << "The current local date and time: " << dt << endl;

    cout << "Hello and Welcome to Cozy's Library " << endl;

    do {
        cout << "[-Menu-]" << endl;
        cout << "Please select a service from 1 to 7" << endl;
        cout << AddM << " Add Member " << endl;
        cout << SB << " Search BookID " << endl;
        cout << SM << " Search MemberID " << endl;
        cout << IB << " Issue A Book " << endl;
        cout << RB << " Return A Book " << endl;
        cout << SBID << " Display Book by ID " << endl;
        cout << ES << " End Service " << endl;

        cin >> user;

        switch (user) {
            case 1:
                librarian.addMember();
                break;
            case 2:
                cout << "Enter Book ID" << endl;
                cin >> userBookID;
                librarian.searchBookByID(userBookID);
                break;
            case 3:
                cout << "Enter member ID" << endl;
                cin >> userMemberID;
                // Implement member search logic
                break;
            case 4:
                cout << "Enter member ID" << endl;
                cin >> userMemberID;
                cout << "Enter Book ID" << endl;
                cin >> userBookID;
                librarian.issueBook(userMemberID, userBookID);
                break;
            case 5:
                cout << "Enter member ID" << endl;
                cin >> userMemberID;
                cout << "Enter Book ID" << endl;
                cin >> userBookID;
                librarian.returnBook(userMemberID, userBookID);
                break;
            case 6:
                cout << "Enter member ID" << endl;
                cin >> userMemberID;
                librarian.displayBorrowedBooks(userMemberID);
                break;
            case 7:
                cout << "Exiting the program." << endl;
                break;
            default:
                cout << "Invalid option. Please try again." << endl;
                break;
        }
    } while (user != 7);

    return 0;
}
