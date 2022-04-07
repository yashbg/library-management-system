#include <bits/stdc++.h>
using namespace std;

const int STUDENT_MAX_BOOKS = 5;
const int PROFESSOR_FINE_RATE = 5;
const int STUDENT_FINE_RATE = 2;
const string LIBRARIAN_NAME = "Librarian";
const string LIBRARIAN_ID = "librarian";
const string LIBRARIAN_PASSWORD = "password";

class Book{
    string title;
    string author;
    string isbn;
    string publication;
    bool is_available = true;
    string issued_to_id;

public:
    void set_details(string title, string author, string isbn, string publication){
        this->title = title;
        this->author = author;
        this->isbn = isbn;
        this->publication = publication;
    }

    void book_request(string isbn){
        
    }

    string show_duedate(string isbn){

    }

    void display(){
        cout << "Title: " << title << endl;
        cout << "Author: " << author << endl;
        cout << "ISBN: " << isbn << endl;
        cout << "Publication: " << publication << endl;
        cout << "Availability: " << (is_available ? "Available" : "Not available") << endl;
    }

    bool check_availability(){
        return is_available;
    }
};

class BookDatabase{
    map<string, Book> books;

public:
    void add(string isbn, Book book){
        books[isbn] = book;
    }

    void update(string isbn, Book& updated_book){

    }

    void remove(string isbn){

    }

    bool search(string isbn){
        return books.find(isbn) != books.end();
    }

    void display(){
        cout << "There are " << books.size() << " books in total." << endl;
        cout << "Here is a list of all the books:" << endl;
        int i = 0;
        for(auto book_item : books){
            cout << "Book " << i << ":" << endl;
            book_item.second.display();
            cout << endl;
            i++;
        }
    }

    bool check_availability(string isbn){
        Book book = books.find(isbn)->second;
        return book.check_availability();
    }
};

class User{
protected:
    string name;
    string id;
    string password;
public:
    void set_creds(string name, string id, string password){
        this->name = name;
        this->id = id;
        this->password = password;
    }

    bool check_creds(string id, string password){
        return this->id == id && this->password == password;
    }
};

class Professor: public User{
    int fine_amount;
    vector<Book> books_issued;

public:
    int calculate_fine(int delay){

    }

    void clear_fine_amount(){

    }

    void display_issued_books(){
        cout << "You have issued " << books_issued.size() << " books." << endl;
        cout << "Here is a list of the books:" << endl;
        int i = 0;
        for(auto book : books_issued){
            cout << "Book " << i << ":" << endl;
            book.display();
            cout << endl;
            i++;
        }
    }
};

class Student: public User{
    int fine_amount;
    vector<Book> books_issued;

public:
    int calculate_fine(int delay){

    }

    void clear_fine_amount(){

    }

    void display_issued_books(){
        cout << "You have issued " << books_issued.size() << " books." << endl;
        cout << "Here is a list of the books:" << endl;
        int i = 0;
        for(auto book : books_issued){
            cout << "Book " << i << ":" << endl;
            book.display();
            cout << endl;
            i++;
        }
    }
};

class Librarian: public User{

};

class UserDatabase{
    map<string, Professor> professors;
    map<string, Student> students;

public:
    void add(int user_type, string name, string id, string password){
        if(user_type == 2){
            Professor professor;
            professor.set_creds(name, id, password);
            professors[id] = professor;
        }
        else{
            Student student;
            student.set_creds(name, id, password);
            students[id] = student;
        }
    }

    void update(string id, User& updated_user){

    }

    void remove(string id){

    }

    bool search(int user_type, string id, string password){
        if(user_type == 2){
            auto professor_itr = professors.find(id);
            if(professor_itr == professors.end()){
                return false;
            }
            Professor professor = professor_itr->second;
            return professor.check_creds(id, password);
        }
        auto student_itr = students.find(id);
        if(student_itr == students.end()){
            return false;
        }
        Student student = student_itr->second;
        return student.check_creds(id, password);
    }

    void display_issued_books(int user_type, string id){
        if(user_type == 2){
            Professor professor = professors.find(id)->second;
            professor.display_issued_books();
        }
        else{
            Student student = students.find(id)->second;
            student.display_issued_books();
        }
    }
};

UserDatabase users;
Librarian librarian;
BookDatabase books;

string login(int user_type){
    string id, password;
    while(true){
        cout << "Please enter your ID: ";
        cin >> id;
        cout << "Please enter your password: ";
        cin >> password;
        if(user_type == 1){
            if(!librarian.check_creds(id, password)){
                cout << "Incorrect credentials." << endl;
                continue;
            }
            cout << "Successfully logged in!" << endl << endl;
            return id;
        }
        if(!users.search(user_type, id, password)){
            cout << "Incorrect credentials." << endl;
            continue;
        }
        cout << "Successfully logged in!" << endl << endl;
        return id;
    }
}

pair<int, string> welcome(){
    cout << "Welcome to Library Management System!" << endl;
    int input;
    while(true){
        cout << "If you are the librarian, enter 1." << endl;
        cout << "If you are a professor, enter 2." << endl;
        cout << "If you are a student, enter 3." << endl;
        cout << "If you want to exit, enter 4." << endl;
        cin >> input;
        if(input == 4){
            return make_pair(-1, "");
        }
        int user_type = input;
        if(!(user_type == 1 || user_type == 2 || user_type == 3)){
            cout << "Please enter 1, 2 or 3 only." << endl;
            continue;
        }
        string id = login(user_type);
        return {user_type, id};
    }
}

void librarian_user_tasks(){
    int sub_task;
    while(true){
        cout << "Please enter:" << endl;
        cout << "1 to list all users" << endl;
        cout << "2 to add a new user" << endl;
        cout << "3 to update a user" << endl;
        cout << "4 to delete a user" << endl;
        cout << "5 to list all books issued to a user" << endl;
        cout << "6 to go back" << endl;
        cin >> sub_task;
        switch(sub_task){
        case 1:
            break;
        
        case 2:
            break;
        
        case 3:
            break;
        
        case 4:
            break;
        
        case 5:
            break;
        
        case 6:
            return;
        
        default:
            cout << "Please enter 1, 2, 3, 4, 5 or 6 only." << endl;
            continue;
        }
    }
}

void add_book(){
    string title, author, isbn, publication;
    int input;
    while(true){
        cout << "If you want to add a new book, enter 1." << endl;
        cout << "If you want to go back, enter 2." << endl;
        cin >> input;
        if(input == 2){
            return;
        }
        if(input != 1){
            cout << "Please enter 1 or 2 only." << endl;
            continue;
        }
        cout << "Please enter the title of the book: ";
        cin >> title;
        cout << "Please enter the name of the author: ";
        cin >> author;
        cout << "Please enter the ISBN of the book: ";
        cin >> isbn;
        cout << "Please enter the publication of the book: ";
        cin >> publication;
        if(books.search(isbn)){
            cout << "This book already exists." << endl;
            continue;
        }
        Book book;
        book.set_details(title, author, isbn, publication);
        books.add(isbn, book);
        break;
    }
}

void librarian_book_tasks(){
    int sub_task;
    while(true){
        cout << "Please enter:" << endl;
        cout << "1 to list all books" << endl;
        cout << "2 to add a new book" << endl;
        cout << "3 to update a book" << endl;
        cout << "4 to delete a book" << endl;
        cout << "5 to check which user a book is issued to" << endl;
        cout << "6 to go back" << endl;
        cin >> sub_task;
        switch(sub_task){
        case 1:
            books.display();
            break;
        
        case 2:
            add_book();
            break;
        
        case 3:
            break;
        
        case 4:
            break;
        
        case 5:
            break;
        
        case 6:
            return;
        
        default:
            cout << "Please enter 1, 2, 3, 4, 5 or 6 only." << endl;
            continue;
        }
    }
}

void librarian_flow(){
    cout << "Hello librarian!" << endl;
    int task;
    while(true){
        cout << "Please enter:" << endl;
        cout << "1 for users" << endl;
        cout << "2 for books" << endl;
        cout << "3 to logout" << endl;
        cin >> task;
        switch(task){
        case 1:
            librarian_user_tasks();
            break;
        
        case 2:
            librarian_book_tasks();
            break;
        
        case 3:
            return;
        
        default:
            cout << "Please enter 1, 2 or 3 only." << endl;
            continue;
        }
    }
}

void check_book_availability(){
    int input;
    while(true){
        cout << "If you want to check if a book is available for issue, enter 1." << endl;
        cout << "If you want to go back, enter 2." << endl;
        cin >> input;
        if(input == 2){
            return;
        }
        if(input != 1){
            cout << "Please enter 1 or 2 only." << endl;
            continue;
        }
        string isbn;
        cout << "Enter the ISBN of the book you want to check the availability of: ";
        cin >> isbn;
        if(!books.search(isbn)){
            cout << "Book not found." << endl;
            continue;
        }
        bool is_available = books.check_availability(isbn);
        cout << "The book is " << (is_available ? "available." : "not available.") << endl << endl;
        break;
    }
}

void professor_flow(int user_type, string id){
    cout << "Hello Professor!" << endl;
    int task;
    while(true){
        cout << "Please enter:" << endl;
        cout << "1 to see all books" << endl;
        cout << "2 to list all books you have" << endl;
        cout << "3 to check if a book is available for issue" << endl;
        cout << "4 to logout" << endl;
        cin >> task;
        switch(task){
        case 1:
            books.display();
            break;
        
        case 2:
            users.display_issued_books(user_type, id);
            break;
        
        case 3:
            check_book_availability();
            break;
        
        case 4:
            return;
        
        default:
            cout << "Please enter 1, 2, 3 or 4 only." << endl;
            continue;
        }
    }
}

void student_flow(int user_type, string id){
    cout << "Hello Student!" << endl;
    int task;
    while(true){
        cout << "Please enter:" << endl;
        cout << "1 to see all books" << endl;
        cout << "2 to list all books you have" << endl;
        cout << "3 to check if a book is available for issue" << endl;
        cout << "4 to logout" << endl;
        cin >> task;
        switch(task){
        case 1:
            books.display();
            break;
        
        case 2:
            users.display_issued_books(user_type, id);
            break;
        
        case 3:
            check_book_availability();
            break;
        
        case 4:
            return;
        
        default:
            cout << "Please enter 1, 2, 3 or 4 only." << endl;
            continue;
        }
    }
}

int main(){
    librarian.set_creds("Librarian", "librarian", "password");
    while(true){
        auto [input, id] = welcome();
        if(input == -1){
            return 0;
        }
        int user_type = input;
        switch(user_type){
        case 1:
            librarian_flow();
            break;
        
        case 2:
            professor_flow(user_type, id);
            break;
        
        case 3:
            student_flow(user_type, id);
            break;
        
        default:
            break;
        }
    }
    return 0;
}
