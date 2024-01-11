#include <ctime>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
class Book;
class Member;

class Student {
    string MyName;
    string MyEmail;
    string MyAddress;    
    public:
    Student(std:: string MyName,
     std:: string MyEmail,
    std:: string MyAddress);
    virtual ~Student();

    std::string getName(); 
    void setName(std::string MyName);

    std::string getEmail();
    void setEmail(std::string MyEmail);

    std::string getAddress();
    void setAddress(std::string MyAddress);

};

class Librarian {
    private:
    int StaffIDNum;
    int StaffSalary;
    public:

Librarian( int StaffID, 
std::string MyName, 
std::string MyEmail, 
std::string MyAddress, 
int StaffSalary);    

void addMember(){
    string member;
    std::vector<Member*> members;
    int memberID;
    string MyName;
    string MyEmail;
    string MyAddress;


    memberID = members.size();

    cout << "Insert your name: ";
    cin >> MyName;

    cout << "Enter your email: ";

    cin >> MyEmail;

    cout << "Enter your current address: ";

    cin >> MyAddress;

    members.push_back(new Member(memberID++, MyName, MyAddress, MyEmail));

cout << "Library Member Creation Successful";
cout << "ID" << memberID << endl;
cout << "Member Name: " << MyName << endl; 
cout << "Member Address: " << MyAddress << endl;
cout << "Member Email: " << MyEmail << endl; 

};

void issueBook(int memberID, int bookID);
void returnbook(int memberID, int bookID);
void displayBorrowedBooks(int memberID);
void calculateFine(int memberID);

int getStaffID();
void setStaffID(int StaffIDNum);
int getStaffSalary();
void setStaffSalary(int StaffSalary);


};

class Member{
    private:
    int memberID;
    std::vector<Book*> booksLoaned;  
    public:
    Member( int memberID, 
std::string MyName, 
std::string MyEmail, 
std::string MyAddress);
 
  
std::string getMemberID(int memberID);
//Error saying expecected a declaration
// return memberID;
std::vector<Book*>getBooksBorrowed(Book) const;
void setBooksBorrowed(const std::vector<Book*>& Book);
    
     

};

class Book{
    private:
    int bookID;
    std::string bookName;
    std::string authorFirstName;
    std::string authorLastName;
    std::string bookType;
    time_t now = time(0);
    char* dt = ctime (
        &now);
    //borrow: Member
    public:
    Book(int bookID,
    std::string bookName,
    std::string authorFirstName,
    std::string authorLastName);

    std::string getbookID();
    std::string getbookName();
    std::string getAuthorFirstName();
    std::string getAuthorLastName();
    std::string getDueDate(time_t& dt); //: Date
    //setDueDate(dueDate : Date) : void
    //void setDueDate(dueDate);
    void returnBook();
    // void borrowBook(borrower Member, dueDate: Date)


    



    
};


int main() {
//This gets the current date and time within the system
time_t now = time(0);
//This is the convertion turning the date and time into single strings types
char* dt = ctime(&now);


    ofstream file;
    file.open("library_books.csv");
    file << "Book ID, Book Name, Page Count, Author First Name, Author Last Name, Book Type" << endl;
    file.close();
    return 0;

    int user;

    int AddM = 1;
    int SB = 2;
    int SM = 3;

    

    std:: cout << "Hello and Welcome to Cozy's Library " << endl;

    cout << "The current local date and time: " <<dt << endl;

    cout << "-Menu-" << endl;

    cout << "Please select a service from 1 to 3" << endl;

    cin >> user; 

    if (cin.fail()) {
        cout << "Please enter a valid value of from 1 to 3" << endl;
        return -1;
    }

    cout << user << endl;   

    cout << AddM << " AddMember" << endl;

    cout << SB << " Search BookID" << endl;

    cout << SM << " Search MemberID" << endl;

    

//This is for retrieving the time to UCT and converting it into struct
    tm* gmtm = gmtime(&now);

    dt = asctime(gmtm);

    cout << "The UTC date and time is: " << dt << endl;

    std:: cout << "Please enter the Book ID ";

 

     //This is the student object
    // Student MyStudent;
    
    // MyStudent.MyName;
    // MyStudent.MyEmail;
    // MyStudent.MyAddress = "St Gotham City";
    
    // cout << "Enter the student's Name: " << endl;
    // cin >> MyStudent.MyName;
    // cout << "Hello " + MyStudent.MyName << "\n";
    
    // cout << "Enter student's email address: " << endl;
    // cin >> MyStudent.MyEmail;
    
    // cout << MyStudent.MyName << "\n";
    // cout << MyStudent.MyEmail << "\n";
    // cout << MyStudent.MyAddress << "\n";
    
    // cout << endl;
    
    // //This is the librarian object section
    // Librarian StaffID;
    
    // StaffID.StaffName = "Jason Todd";
    // StaffID.StaffAddress = "1 St Metro Square"; 
    // StaffID.StaffEmail = "JT750@hotmail.com";
    // StaffID.StaffIDNum = 00750;
    // StaffID.StaffSalary = 30000;
    
    // cout << "Who will be the Librarian to serve you today?: " << endl;
    
    // cout << "Librarian Data: " << endl;
    // cout << "Name" << StaffID.StaffName << "\n";
    // cout << "Address: " << StaffID.StaffAddress << "\n";
    // cout << "Email: " << StaffID.StaffEmail << "\n";
    // cout << "ID Number: " << StaffID.StaffIDNum << "\n";
    // cout << "Salary: " << StaffID.StaffSalary << "\n";
    
    
    return 0;
}