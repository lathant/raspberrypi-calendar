/* Class representing User
 * CREATED BY: John Jewell
 * LAST EDITED BY: John Jewell
 * LAST EDITED: 29/10/2019
 * TODO: IMPLEMENT
 *   method to check if a user is already logged in
 */

#include "user_manager.h"

using namespace std;

static string DATABASE_FILE_PATH = "./data/user/database.csv";

User_Manager* User_Manager::instance = NULL;

string User_Manager::line_to_username(string line) {
    int length = line.length();
    string username = "";
    for (int i = 0; i < length && line[i] != ','; i++) {
        username += line[i];
    }

    return username;
}

string User_Manager::line_to_password(string line) {
    int length = line.length();
    string password = "";
    bool password_index = false;
    for (int i = 0; i < length; i++) {
        if (password_index == true) {
            password += line[i];
        }
        if (line[i] == ',') {
            password_index = true;
        }
    }
    return password;
 }

User_Manager* User_Manager::get_instance() {
    if (instance == NULL)
        instance = new User_Manager;
    return instance;
}

User * User_Manager::create_user(string username, string password) {
    User * user = get_user(username);
    if (user != NULL)
        return user;

    User_Factory* factory = new User_Factory;
    Authenticator* auth = new Authenticator;
    string encrypted_password = auth->encrypt(password);

    User* new_user = factory->create_user(username, encrypted_password);

    string user_db_entry = username + "," + encrypted_password;
    ofstream out(DATABASE_FILE_PATH, ios::app);
    out << user_db_entry << endl;
    out.close();

    return new_user;
}

User* User_Manager::get_user(string username) {
    ifstream file_input(DATABASE_FILE_PATH);
    string line;
    while(getline(file_input, line)) {
        string current_username = line_to_username(line);
        string current_password = line_to_password(line);
        if (current_username == username)
            return new User(current_username, current_password);
    }
    return NULL;
}

bool User_Manager::check_user(string username, string password) {
    User * user = get_user(username);
    if (user == NULL)
        return false;
    string user_encrypted_password = user->get_password();
    Authenticator * auth = new Authenticator;
    string user_password = auth->decrypt(user_encrypted_password);
    if (password == user_password)
        return true;
    else
        return false;
}

bool User_Manager::delete_user(string username) {
    User * user = get_user(username);
    if (user == NULL)
        return false;

    ifstream file_input(DATABASE_FILE_PATH);
    string line;
    string new_database_string = "";
    while(getline(file_input, line)) {
        string current_username = line_to_username(line);

        string current_password = line_to_password(line);
        if (current_username != username) {
            line = line + "\n";
            new_database_string += line;
        }
    }
    file_input.close();
    remove(STORAGE_FILE_PATH.c_str());
    ofstream out(DATABASE_FILE_PATH);
    out << new_database_string;
    out.close();

    return true;
}
