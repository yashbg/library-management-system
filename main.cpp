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

    bool check_creds(string id, string password){
        return this->id == id && this->password == password;
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

void login(int user_type, Librarian& librarian, UserDatabase& users){
    string id, password;
    while(true){
        cout << "Please enter your ID: ";
        cin >> id;
        cout << "Please enter your password: ";
        cin >> password;
        if(user_type == 1){
            if(!librarian.check_creds(id, password)){
                cout << "Incorrect credentials. " << endl;
                continue;
            }
            cout << "Successfully logged in!" << endl;
            break;
        }
        if(!users.search(user_type, id, password)){
            cout << "Incorrect credentials. " << endl;
            continue;
        }
        cout << "Successfully logged in!" << endl;
        break;
    }
}

void welcome(Librarian& librarian, UserDatabase& users){
    cout << "Welcome to Library Management System!" << endl;
    int user_type;
    while(true){
        cout << "If you are the librarian, enter 1. " << endl;
        cout << "If you are a professor, enter 2. " << endl;
        cout << "If you are a student, enter 3. " << endl;
        cin >> user_type;
        if(!(user_type == 1 || user_type == 2 || user_type == 3)){
            cout << "Please only enter 1, 2 or 3" << endl;
            continue;
        }
        login(user_type, librarian, users);
        break;
    }
}

int main(){
    UserDatabase users;
    Librarian librarian;
    librarian.set_creds("Librarian", "librarian", "password");
    welcome(librarian, users);
    return 0;
}
