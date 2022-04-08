#include <bits/stdc++.h>
using namespace std;
using namespace chrono;

typedef chrono::_V2::steady_clock::time_point _time;

const int PROFESSOR_ISSUE_DURATION = 60;
const int PROFESSOR_FINE_RATE = 5;
const int STUDENT_MAX_BOOKS = 5;
const int STUDENT_ISSUE_DURATION = 30;
const int STUDENT_FINE_RATE = 2;
const int PROFESSOR_USER_TYPE = 2;
const int STUDENT_USER_TYPE = 3;
const string LIBRARIAN_NAME = "Librarian";
const string LIBRARIAN_ID = "librarian";
const string LIBRARIAN_PASSWORD = "password";

class Book{
    string title;
    string author;
    string isbn;
    string publication;
    bool is_available = true;
    int issued_to_type;
    string issued_to_id;

public:
    void set_details(string title, string author, string isbn, string publication){
        this->title = title;
        this->author = author;
        this->isbn = isbn;
        this->publication = publication;
    }

    void book_request(int issued_to_type, string issued_to_id){
        is_available = false;
        this->issued_to_type = issued_to_type;
        this->issued_to_id = issued_to_id;
    }

    void display(){
        cout << "Title: " << title << endl;
        cout << "Author: " << author << endl;
        cout << "ISBN: " << isbn << endl;
        cout << "Publication: " << publication << endl;
        cout << "Availability: " << (is_available ? "Available" : "Not available") << endl << endl;
    }

    bool check_availability(){
        return is_available;
    }

    pair<int, string> check_book_issued_to(){
        return {issued_to_type, issued_to_id};
    }
};

class BookDatabase{
    map<string, Book> books;

public:
    void add(string title, string author, string isbn, string publication){
        Book book;
        book.set_details(title, author, isbn, publication);
        books[isbn] = book;
    }

    void update(string isbn, string new_title, string new_author, string new_publication){
        Book book = books.find(isbn)->second;
        book.set_details(new_title, new_author, isbn, new_publication);
    }

    void remove(string isbn){
        books.erase(isbn);
    }

    bool search(string isbn){
        return books.find(isbn) != books.end();
    }

    void display(){
        cout << "There are " << books.size() << " books in total." << endl;
        if(!books.size()){
            cout << endl;
            return;
        }
        cout << "Here is a list of all the books:" << endl << endl;
        int i = 1;
        for(auto& book_item : books){
            cout << "Book " << i << ":" << endl;
            book_item.second.display();
            i++;
        }
    }

    bool check_availability(string isbn){
        return books.find(isbn)->second.check_availability();
    }

    pair<int, string> check_book_issued_to(string isbn){
        return books.find(isbn)->second.check_book_issued_to();
    }

    Book get_book(string isbn){
        return books.find(isbn)->second;
    }
};

BookDatabase books;

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

    void display(){
        cout << "Name: " << name << endl;
        cout << "ID: " << id << endl << endl;
    }
};

class Professor: public User{
    long long old_books_fine = 0;
    long long fine_paid = 0;
    map<string, pair<Book, _time>> books_issued;

public:
    long long calculate_fine(){
        long long fine = 0;
        _time now = steady_clock::now();
        for(auto& book_item : books_issued){
            _time issued_time = book_item.second.second;
            long long duration = duration_cast<seconds>(now - issued_time).count();
            if(duration > PROFESSOR_ISSUE_DURATION){
                long long delay = duration - PROFESSOR_ISSUE_DURATION;
                fine += delay * PROFESSOR_FINE_RATE;
            }
        }
        return fine + old_books_fine - fine_paid;
    }

    void clear_fine_amount(){
        long long fine = calculate_fine();
        fine_paid += fine;
    }

    void display_issued_books(){
        cout << "You have issued " << books_issued.size() << " books." << endl;
        if(!books_issued.size()){
            cout << endl;
            return;
        }
        cout << "Here is a list of the books:" << endl << endl;
        int i = 1;
        for(auto& book_item : books_issued){
            Book book = book_item.second.first;
            cout << "Book " << i << ":" << endl;
            book.display();
            cout << endl;
            i++;
        }
    }

    void issue_book(string isbn){
        Book book = books.get_book(isbn);
        book.book_request(PROFESSOR_USER_TYPE, id);
        _time issued_time = steady_clock::now();
        books_issued[isbn] = {book, issued_time};
    }

    void return_book(string isbn){
        _time issued_time = books_issued[isbn].second;
        _time now = steady_clock::now();
        long long duration = duration_cast<seconds>(now - issued_time).count();
        if(duration > PROFESSOR_ISSUE_DURATION){
            long long delay = duration - PROFESSOR_ISSUE_DURATION;
            old_books_fine += delay * PROFESSOR_FINE_RATE;
        }
        books_issued.erase(isbn);
    }

    bool check_issued_book(string isbn){
        return books_issued.find(isbn) != books_issued.end();
    }

    void show_duedate(string isbn){
        _time issued_time = books_issued.find(isbn)->second.second;
        _time now = steady_clock::now();
        long long time_rem = duration_cast<seconds>(issued_time - now).count() + PROFESSOR_ISSUE_DURATION;
        if(time_rem < 0){
            cout << "The due date for this book was " << -time_rem << " days ago. Please return this book as soon as possible." << endl << endl;
        }
        else if(time_rem == 0){
            cout << "The due date for this book is today. Please return this book as soon as possible." << endl << endl;
        }
        else{
            cout << "The due date for this book is after " << time_rem << " days. Please return this book before the due date." << endl << endl;
        }
    }
};

class Student: public User{
    long long old_books_fine = 0;
    long long fine_paid = 0;
    map<string, pair<Book, _time>> books_issued;

public:
    long long calculate_fine(){
        long long fine = 0;
        _time now = steady_clock::now();
        for(auto& book_item : books_issued){
            _time issued_time = book_item.second.second;
            long long duration = duration_cast<seconds>(now - issued_time).count();
            if(duration > STUDENT_ISSUE_DURATION){
                long long delay = duration - STUDENT_ISSUE_DURATION;
                fine += delay * STUDENT_FINE_RATE;
            }
        }
        return fine + old_books_fine - fine_paid;
    }

    void clear_fine_amount(){
        long long fine = calculate_fine();
        fine_paid += fine;
    }

    void display_issued_books(){
        cout << "You have issued " << books_issued.size() << " books." << endl;
        if(!books_issued.size()){
            cout << endl;
            return;
        }
        cout << "Here is a list of the books:" << endl << endl;
        int i = 1;
        for(auto& book_item : books_issued){
            Book book = book_item.second.first;
            cout << "Book " << i << ":" << endl;
            book.display();
            cout << endl;
            i++;
        }
    }

    int get_num_books_issued(){
        return books_issued.size();
    }

    void issue_book(string isbn){
        Book book = books.get_book(isbn);
        book.book_request(STUDENT_USER_TYPE, id);
        _time issued_time = steady_clock::now();
        books_issued[isbn] = {book, issued_time};
    }

    void return_book(string isbn){
        _time issued_time = books_issued[isbn].second;
        _time now = steady_clock::now();
        long long duration = duration_cast<seconds>(now - issued_time).count();
        if(duration > STUDENT_ISSUE_DURATION){
            long long delay = duration - STUDENT_ISSUE_DURATION;
            old_books_fine += delay * STUDENT_FINE_RATE;
        }
        books_issued.erase(isbn);
    }

    bool check_issued_book(string isbn){
        return books_issued.find(isbn) != books_issued.end();
    }

    void show_duedate(string isbn){
        _time issued_time = books_issued.find(isbn)->second.second;
        _time now = steady_clock::now();
        long long time_rem = duration_cast<seconds>(issued_time - now).count() + STUDENT_ISSUE_DURATION;
        if(time_rem < 0){
            cout << "The due date for this book was " << -time_rem << " days ago. Please return this book as soon as possible." << endl << endl;
        }
        else if(time_rem == 0){
            cout << "The due date for this book is today. Please return this book as soon as possible." << endl << endl;
        }
        else{
            cout << "The due date for this book is after " << time_rem << " days. Please return this book before the due date." << endl << endl;
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
        if(user_type == PROFESSOR_USER_TYPE){
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

    void update(int user_type, string id, string new_name, string new_password){
        if(user_type == PROFESSOR_USER_TYPE){
            Professor professor = professors.find(id)->second;
            professor.set_creds(new_name, id, new_password);
        }
        else{
            Student student = students.find(id)->second;
            student.set_creds(new_name, id, new_password);
        }
    }

    void remove(int user_type, string id){
        user_type == PROFESSOR_USER_TYPE ? professors.erase(id) : students.erase(id);
    }

    bool search(int user_type, string id){
        if(user_type == PROFESSOR_USER_TYPE){
            return professors.find(id) != professors.end();
        }
        return students.find(id) != students.end();
    }

    bool check_creds(int user_type, string id, string password){
        if(user_type == PROFESSOR_USER_TYPE){
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
        if(user_type == PROFESSOR_USER_TYPE){
            Professor professor = professors.find(id)->second;
            professor.display_issued_books();
        }
        else{
            Student student = students.find(id)->second;
            student.display_issued_books();
        }
    }

    void display_by_id(int user_type, string id){
        if(user_type == PROFESSOR_USER_TYPE){
            professors.find(id)->second.display();
        }
        else{
            students.find(id)->second.display();
        }
    }

    void display(){
        cout << "There are " << professors.size() << " professors and " << students.size() << " students." << endl;
        if(!(professors.size() + students.size())){
            cout << endl;
            return;
        }
        if(professors.size()){
            cout << "Here is a list of the professors:" << endl << endl;
            int i = 1;
            for(auto& professor_item : professors){
                cout << "Professor " << i << ":" << endl;
                professor_item.second.display();
                i++;
            }
        }
        if(students.size()){
            cout << "Here is a list of the students:" << endl << endl;
            int i = 1;
            for(auto& student_item : students){
                cout << "Student " << i << ":" << endl;
                student_item.second.display();
                i++;
            }
        }
    }

    bool issue_book(int user_type, string id, string isbn){
        if(user_type == PROFESSOR_USER_TYPE){
            professors.find(id)->second.issue_book(isbn);
            return true;
        }
        Student student = students.find(id)->second;
        if(student.get_num_books_issued() > STUDENT_MAX_BOOKS - 1){
            return false;
        }
        student.issue_book(isbn);
        return true;
    }

    void calculate_dues(int user_type, string id){
        if(user_type == PROFESSOR_USER_TYPE){
            long long fine = professors.find(id)->second.calculate_fine();
            cout << "You have to pay " << fine << " rupees. Please clear your dues as soon as possible!" << endl << endl;
        }
        else{
            long long fine = students.find(id)->second.calculate_fine();
            cout << "You have to pay " << fine << " rupees. Please clear your dues as soon as possible!" << endl << endl;
        }
    }

    void clear_dues(int user_type, string id){
        if(user_type == PROFESSOR_USER_TYPE){
            professors.find(id)->second.clear_fine_amount();
            cout << "Thanks for clearing your dues!" << endl << endl;
        }
        else{
            students.find(id)->second.clear_fine_amount();
            cout << "Thanks for clearing your dues!" << endl << endl;
        }
    }

    bool check_issued_book(int user_type, string id, string isbn){
        if(user_type == PROFESSOR_USER_TYPE){
            return professors.find(id)->second.check_issued_book(isbn);
        }
        else{
            return students.find(id)->second.check_issued_book(isbn);
        }
    }

    void return_book(int user_type, string id, string isbn){
        if(user_type == PROFESSOR_USER_TYPE){
            professors.find(id)->second.return_book(isbn);
        }
        else{
            students.find(id)->second.return_book(isbn);
        }
    }

    void show_duedate(int user_type, string id, string isbn){
        if(user_type == PROFESSOR_USER_TYPE){
            professors.find(id)->second.show_duedate(isbn);
        }
        else{
            students.find(id)->second.show_duedate(isbn);
        }
    }
};

UserDatabase users;
Librarian librarian;

pair<int, string> login(){
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
        string id, password;
        cout << "Please enter your ID: ";
        cin >> id;
        cout << "Please enter your password: ";
        cin >> password;
        if(user_type == 1){
            if(!librarian.check_creds(id, password)){
                cout << "Incorrect credentials." << endl << endl;
                continue;
            }
            cout << "Successfully logged in!" << endl << endl;
            return {user_type, id};
        }
        if(!users.check_creds(user_type, id, password)){
            cout << "Incorrect credentials." << endl << endl;
            continue;
        }
        cout << "Successfully logged in!" << endl << endl;
        return {user_type, id};
    }
}

void add_user(){
    string id, name, password;
    int input;
    while(true){
        cout << "If you want to add a new professor, enter 1." << endl;
        cout << "If you want to add a new student, enter 2." << endl;
        cout << "If you want to go back, enter 3." << endl;
        cin >> input;
        if(input == 3){
            return;
        }
        if(!(input == 1 || input == 2)){
            cout << "Please enter 1, 2 or 3 only." << endl;
            continue;
        }
        int user_type = input + 1;
        cout << "Please enter the ID of the " << (user_type == PROFESSOR_USER_TYPE ? "professor" : "student") << ": ";
        cin >> id;
        if(users.search(user_type, id)){
            cout << "A " << (user_type == PROFESSOR_USER_TYPE ? "professor" : "student") << " with this ID already exists." << endl;
            continue;
        }
        cout << "Now, please enter the credentials of the " << (user_type == PROFESSOR_USER_TYPE ? "professor." : "student.") << endl;
        cout << "Name: ";
        cin >> name;
        cout << "Password: ";
        cin >> password;
        users.add(user_type, name, id, password);
        cout << (user_type == PROFESSOR_USER_TYPE ? "Professor" : "Student") << " added!" << endl << endl;
        break;
    }
}

void update_user(){
    string id, new_name, new_password;
    int input;
    while(true){
        cout << "If you want to update a professor, enter 1." << endl;
        cout << "If you want to update a student, enter 2." << endl;
        cout << "If you want to go back, enter 3." << endl;
        cin >> input;
        if(input == 3){
            return;
        }
        if(!(input == 1 || input == 2)){
            cout << "Please enter 1, 2 or 3 only." << endl;
            continue;
        }
        int user_type = input + 1;
        cout << "Please enter the ID of the " << (user_type == PROFESSOR_USER_TYPE ? "professor" : "student") << ": ";
        cin >> id;
        if(!users.search(user_type, id)){
            cout << (user_type == PROFESSOR_USER_TYPE ? "Professor" : "Student") << " not found." << endl;
            continue;
        }
        cout << "Now, please enter the new credentials of the " << (user_type == PROFESSOR_USER_TYPE ? "professor." : "student.") << endl;
        cout << "Name: ";
        cin >> new_name;
        cout << "Password: ";
        cin >> new_password;
        users.update(user_type, id, new_name, new_password);
        cout << (user_type == PROFESSOR_USER_TYPE ? "Professor" : "Student") << " updated!" << endl << endl;
        break;
    }
}

void delete_user(){
    string id;
    int input;
    while(true){
        cout << "If you want to delete a professor, enter 1." << endl;
        cout << "If you want to delete a student, enter 2." << endl;
        cout << "If you want to go back, enter 3." << endl;
        cin >> input;
        if(input == 3){
            return;
        }
        if(!(input == 1 || input == 2)){
            cout << "Please enter 1, 2 or 3 only." << endl;
            continue;
        }
        int user_type = input + 1;
        cout << "Please enter the ID of the " << (user_type == PROFESSOR_USER_TYPE ? "professor" : "student") << ": ";
        cin >> id;
        if(!users.search(user_type, id)){
            cout << (user_type == PROFESSOR_USER_TYPE ? "Professor" : "Student") << " not found." << endl;
            continue;
        }
        users.remove(user_type, id);
        break;
    }
}

void display_issued_books(){
    string id;
    int input;
    while(true){
        cout << "If you want to list all books issued to a professor, enter 1." << endl;
        cout << "If you want to list all books issued to a student, enter 2." << endl;
        cout << "If you want to go back, enter 3." << endl;
        cin >> input;
        if(input == 3){
            return;
        }
        if(!(input == 1 || input == 2)){
            cout << "Please enter 1, 2 or 3 only." << endl;
            continue;
        }
        int user_type = input + 1;
        cout << "Please enter the ID of the " << (user_type == PROFESSOR_USER_TYPE ? "professor" : "student") << ": ";
        cin >> id;
        if(!users.search(user_type, id)){
            cout << (user_type == PROFESSOR_USER_TYPE ? "Professor" : "Student") << " not found." << endl;
            continue;
        }
        users.display_issued_books(user_type, id);
        break;
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
            users.display();
            break;
        
        case 2:
            add_user();
            break;
        
        case 3:
            update_user();
            break;
        
        case 4:
            delete_user();
            break;
        
        case 5:
            display_issued_books();
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
    string isbn, title, author, publication;
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
        cout << "Please enter the ISBN of the book: ";
        cin >> isbn;
        if(books.search(isbn)){
            cout << "This book already exists." << endl;
            continue;
        }
        cout << "Now, please enter the details of the book." << endl;
        cout << "Title: ";
        cin >> title;
        cout << "Author: ";
        cin >> author;
        cout << "Publication: ";
        cin >> publication;
        books.add(title, author, isbn, publication);
        cout << "Book added!" << endl << endl;
        break;
    }
}

void update_book(){
    string isbn, new_title, new_author, new_publication;
    int input;
    while(true){
        cout << "If you want to update a book, enter 1." << endl;
        cout << "If you want to go back, enter 2." << endl;
        cin >> input;
        if(input == 2){
            return;
        }
        if(input != 1){
            cout << "Please enter 1 or 2 only." << endl;
            continue;
        }
        cout << "Please enter the ISBN of the book: ";
        cin >> isbn;
        if(!books.search(isbn)){
            cout << "Book not found." << endl;
            continue;
        }
        cout << "Now, please enter the new details of the book." << endl;
        cout << "Title: ";
        cin >> new_title;
        cout << "Author: ";
        cin >> new_author;
        cout << "Publication: ";
        cin >> new_publication;
        books.update(isbn, new_title, new_author, new_publication);
        cout << "Book updated!" << endl << endl;
        break;
    }
}

void delete_book(){
    string isbn;
    int input;
    while(true){
        cout << "If you want to delete a book, enter 1." << endl;
        cout << "If you want to go back, enter 2." << endl;
        cin >> input;
        if(input == 2){
            return;
        }
        if(input != 1){
            cout << "Please enter 1 or 2 only." << endl;
            continue;
        }
        cout << "Please enter the ISBN of the book: ";
        cin >> isbn;
        if(!books.search(isbn)){
            cout << "Book not found." << endl;
            continue;
        }
        books.remove(isbn);
        break;
    }
}

void check_book_issued_to(){
    string isbn;
    int input;
    while(true){
        cout << "If you want to check which user a book is issued to, enter 1." << endl;
        cout << "If you want to go back, enter 2." << endl;
        cin >> input;
        if(input == 2){
            return;
        }
        if(input != 1){
            cout << "Please enter 1 or 2 only." << endl;
            continue;
        }
        cout << "Please enter the ISBN of the book: ";
        cin >> isbn;
        if(!books.search(isbn)){
            cout << "Book not found." << endl;
            continue;
        }
        if(books.check_availability(isbn)){
            cout << "The book is not issued to anyone." << endl << endl;
            break;
        }
        auto [user_type, id] = books.check_book_issued_to(isbn);
        users.display_by_id(user_type, id);
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
            update_book();
            break;
        
        case 4:
            delete_book();
            break;
        
        case 5:
            check_book_issued_to();
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

void issue_book(int user_type, string id){
    int input;
    while(true){
        cout << "If you want to issue a book, enter 1." << endl;
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
        cout << "Enter the ISBN of the book you want to issue: ";
        cin >> isbn;
        if(!books.search(isbn)){
            cout << "Book not found." << endl;
            continue;
        }
        if(!books.check_availability(isbn)){
            cout << "Book not available." << endl;
            continue;
        }
        if(!users.issue_book(user_type, id, isbn)){
            cout << "You have already issued " << STUDENT_MAX_BOOKS << " books. You cannot issue any more books." << endl << endl;
            return;
        }
        cout << "Book issued! Please return the book in " << (user_type == PROFESSOR_USER_TYPE ? PROFESSOR_ISSUE_DURATION : STUDENT_ISSUE_DURATION) << " days." << endl << endl;
        break;
    }
}

void return_book(int user_type, string id){
    int input;
    while(true){
        cout << "If you want to return a book, enter 1." << endl;
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
        cout << "Enter the ISBN of the book you want to return: ";
        cin >> isbn;
        if(!books.search(isbn)){
            cout << "Book not found." << endl;
            continue;
        }
        if(!users.check_issued_book(user_type, id, isbn)){
            cout << "You have not issued this book." << endl;
            continue;
        }
        users.return_book(user_type, id, isbn);
        break;
    }
}

void show_duedate(int user_type, string id){
    int input;
    while(true){
        cout << "If you want to know the due date for a book, enter 1." << endl;
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
        cout << "Enter the ISBN of the book you want to know the due date of: ";
        cin >> isbn;
        if(!books.search(isbn)){
            cout << "Book not found." << endl;
            continue;
        }
        if(!users.check_issued_book(user_type, id, isbn)){
            cout << "You have not issued this book." << endl;
            continue;
        }
        users.show_duedate(user_type, id, isbn);
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
        cout << "4 to issue a book" << endl;
        cout << "5 to return a book" << endl;
        cout << "6 to know the due date for a book" << endl;
        cout << "7 to know your current dues" << endl;
        cout << "8 to clear your dues" << endl;
        cout << "9 to logout" << endl;
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
            issue_book(user_type, id);
            break;
        
        case 5:
            return_book(user_type, id);
            break;
        
        case 6:
            show_duedate(user_type, id);
            break;
        
        case 7:
            users.calculate_dues(user_type, id);
            break;
        
        case 8:
            users.clear_dues(user_type, id);
            break;

        case 9:
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
        cout << "4 to issue a book" << endl;
        cout << "5 to return a book" << endl;
        cout << "6 to know the due date for a book" << endl;
        cout << "7 to know your current dues" << endl;
        cout << "8 to clear your dues" << endl;
        cout << "9 to logout" << endl;
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
            issue_book(user_type, id);
            break;
        
        case 5:
            return_book(user_type, id);
            break;
        
        case 6:
            show_duedate(user_type, id);
            break;
        
        case 7:
            users.calculate_dues(user_type, id);
            break;
        
        case 8:
            users.clear_dues(user_type, id);
            break;

        case 9:
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
        auto [input, id] = login();
        if(input == -1){
            return 0;
        }
        int user_type = input;
        switch(user_type){
        case 1:
            librarian_flow();
            break;
        
        case PROFESSOR_USER_TYPE:
            professor_flow(user_type, id);
            break;
        
        case STUDENT_USER_TYPE:
            student_flow(user_type, id);
            break;
        
        default:
            break;
        }
    }
    return 0;
}
