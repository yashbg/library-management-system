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

    void update(string isbn, Book updated_book){

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
};

class UserDatabase{
    vector<User> users;

    void add(User user){

    }

    void update(string id, User updated_user){

    }

    void remove(string id){

    }

    User search(string id){

    }
};

class Professor: private User{
    int fine_amount;
    vector<Book> books_issued;
    int fine_rate = 5;

public:
    int calculate_fine(int delay){

    }

    void clear_fine_amount(){

    }
};

class Student: private User{
    int fine_amount;
    vector<Book> books_issued;
    int fine_rate = 2;

public:
    int calculate_fine(int delay){

    }

    void clear_fine_amount(){

    }
};

class Librarian: private User{

};

bool check_username(string username){
    if(username == "yash"){
        return true;
    }
    return false;
}

bool check_creds(string username, string password){
    if(username == "yash" && password == "pswd"){
        return true;
    }
    return false;
}

void welcome(){
    cout << "Welcome to Library Management System!" << endl;
    string username, password;
    while(true){
        cout << "Please enter your username: ";
        cin >> username;
        if(!check_username(username)){
            cout << "Incorrect username. " << endl;
            continue;
        }
        cout << "Please enter your password: ";
        cin >> password;
        if(!check_creds(username, password)){
            cout << "Incorrect password. " << endl;
            continue;
        }
        cout << "Successfully logged in!" << endl;
        break;
    }
}

int main(){
    welcome();
    return 0;
}
