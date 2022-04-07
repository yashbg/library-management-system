#include <bits/stdc++.h>
using namespace std;

const int STUDENT_MAX_BOOKS = 5;
const int PROFESSOR_FINE_RATE = 5;
const int STUDENT_FINE_RATE = 2;

class Book{
    string title;
    string author;
    string isbn;
    string publication;
    bool is_available;
    string issued_to_id;

public:
    void book_request(string isbn){
        
    }

    string show_duedate(string isbn){

    }
};

class BookDatabase{
    vector<Book> books;

public:
    void add(Book book){

    }

    void update(string isbn, Book& updated_book){

    }

    void remove(string isbn){

    }

    Book search(string isbn){

    }

    vector<Book> display(){

    }
};

class User{
protected:
    string name;
    string id;
    string password;
    // string type;
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
};

class Student: public User{
    int fine_amount;
    vector<Book> books_issued;

public:
    int calculate_fine(int delay){

    }

    void clear_fine_amount(){

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
};

UserDatabase users;
Librarian librarian;
BookDatabase books;

void login(int user_type){
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
            cout << "Successfully logged in!" << endl;
            break;
        }
        if(!users.search(user_type, id, password)){
            cout << "Incorrect credentials." << endl;
            continue;
        }
        cout << "Successfully logged in!" << endl << endl;
        break;
    }
}

int welcome(){
    cout << "Welcome to Library Management System!" << endl;
    int input;
    while(true){
        cout << "If you are the librarian, enter 1." << endl;
        cout << "If you are a professor, enter 2." << endl;
        cout << "If you are a student, enter 3." << endl;
        cout << "If you want to exit, enter 4." << endl;
        cin >> input;
        if(input == 4){
            return -1;
        }
        int user_type = input;
        if(!(user_type == 1 || user_type == 2 || user_type == 3)){
            cout << "Please enter 1, 2 or 3 only." << endl;
            continue;
        }
        login(user_type);
        return user_type;
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

void professor_flow(){
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
            break;
        
        case 2:
            break;
        
        case 3:
            break;
        
        case 4:
            return;
        
        default:
            cout << "Please enter 1, 2, 3 or 4 only." << endl;
            continue;
        }
    }
}

void student_flow(){
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
            break;
        
        case 2:
            break;
        
        case 3:
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
        int input = welcome();
        if(input == -1){
            return 0;
        }
        int user_type = input;
        switch(user_type){
        case 1:
            librarian_flow();
            break;
        
        case 2:
            professor_flow();
            break;
        
        case 3:
            student_flow();
            break;
        
        default:
            break;
        }
    }
    return 0;
}
