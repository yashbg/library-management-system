#include <bits/stdc++.h>
using namespace std;

class Book{
    string title;
    string author;
    string isbn;
    string publication;
    bool is_available;

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
};

class UserDatabase{
    map<string, Professor> professors;
    map<string, Student> students;

public:
    void add(string user_type, string name, string id, string password){
        if(user_type == "professor"){
            Professor professor;
            professor.set_creds(name, id, password);
            professors[id] = professor;
        }
        else if(user_type == "student"){
            Student student;
            student.set_creds(name, id, password);
            students[id] = student;
        }
    }

    bool exists(string id){

    }

    void update(string id, User& updated_user){

    }

    void remove(string id){

    }

    User search(int user_type, string id){
        if(user_type == "professor"){
            return 
        }
        else if(user_type == "student"){
            Student student;
            student.set_creds(name, id, password);
            students[id] = student;
        }
    }
};

class Professor: public User{
    int fine_amount;
    vector<Book> books_issued;
    int fine_rate = 5;

public:
    int calculate_fine(int delay){

    }

    void clear_fine_amount(){

    }
};

class Student: public User{
    int fine_amount;
    vector<Book> books_issued;
    int fine_rate = 2;

public:
    int calculate_fine(int delay){

    }

    void clear_fine_amount(){

    }
};

class Librarian: public User{

};

bool check_id(int user_type, string id, UserDatabase& users){
    // if(id == "yash"){
    //     return true;
    // }
    // return false;

    switch(user_type){
    case 1:
        users.search()
        break;
    
    case 2:
        login_professor();
        break;
    
    case 3:
        login_student();
        break;

    default:
        continue;
    }
}

bool check_creds(int user_type, string id, string password, UserDatabase& users){
    if(id == "yash" && password == "pswd"){
        return true;
    }
    return false;
}

bool login(int user_type, UserDatabase& users){
    string id, password;
    while(true){
        cout << "Please enter your ID: ";
        cin >> id;
        if(!check_id(user_type, id, users)){
            cout << "Incorrect ID. " << endl;
            continue;
        }
        cout << "Please enter your password: ";
        cin >> password;
        if(!check_creds(user_type, id, password, users)){
            cout << "Incorrect password. " << endl;
            continue;
        }
        cout << "Successfully logged in!" << endl;
        break;
    }
}

void welcome(UserDatabase& users){
    cout << "Welcome to Library Management System!" << endl;
    int user_type;
    while(true){
        cout << "If you are the librarian, enter 1. " << endl;
        cout << "If you are a professor, enter 2. " << endl;
        cout << "If you are a student, enter 3. " << endl;
        cin >> user_type;
        if(!(user_type == 1 || user_type == 2 || user_type == 3)){
            continue;
        }
        login(user_type, users);
    }
}

int main(){
    UserDatabase users;
    Librarian librarian;
    librarian.set_creds("Librarian", "librarian", "password");
    welcome(users);
    if()
    return 0;
}
