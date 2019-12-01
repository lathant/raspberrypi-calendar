 /**
  * @brief Class implementing User_Manager
  *
  * The implementation of User_Manager
  * @author John Jewell
  * @date   29/10/2019
  */

#include "user_manager.h"

using namespace std;

static string DATABASE_FILE_PATH = "./storage/database.csv";


User_Manager* User_Manager::instance = NULL;

/**
 * @brief get the username from a line
 *
 * read untill the ',' a username
 * @author John Jewell
 * @date   29/10/2019
 * @param  line         A line of text
 * @return username     A username
 */
string User_Manager::line_to_username(string line) {
    int length = line.length();
    string username = "";
    for (int i = 0; i < length && line[i] != ','; i++) {
        username += line[i];
    }

    return username;
}

/**
 * @brief get the username from a line
 *
 * read after the ',' a password
 * @author John Jewell
 * @date   29/10/2019
 * @param  line         A line of text
 * @return username     A password
 */
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

 /**
  * @brief get the instance of User_Manager
  *
  * Gets the singleton instance of the User_Manager
  * @author John Jewell
  * @date   29/10/2019
  * @return instance     The instance of User_Manager
  */
User_Manager* User_Manager::get_instance() {
    if (instance == NULL)
        instance = new User_Manager;
    return instance;
}

/**
 * @brief create a new User
 *
 * Create a new User object and save the information to the storage file
 * @author John Jewell
 * @date   29/10/2019
 * @param  username     A username
 * @param  password     A password
 * @return new_user     A User object containing the provided information
 */
User * User_Manager::create_user(string username, string password) {
    User * user = get_user(username);
    if (user != NULL)
        return NULL;

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

/**
 * @brief Get a User
 *
 * Search the storage file for a matching user and return it
 * @author John Jewell
 * @date   29/10/2019
 * @param  username     A username
 * @return User         A User object containing the required information or NULL if no User found
 */
User* User_Manager::get_user(string username) {
    ifstream file_input(DATABASE_FILE_PATH);
    string line;
    while(getline(file_input, line)) {
        string current_username = line_to_username(line);
        string current_password = line_to_password(line);
        if (current_username.compare(username) == 0)
            return new User(current_username, current_password);
    }
    return NULL;
}

/**
 * @brief Check a User
 *
 * Search the storage file for a matching user and check if the password matches
 * @author John Jewell
 * @date   29/10/2019
 * @param  username     A password
 * @param  username     A username
 * @return bool         true if match, else false
 */
bool User_Manager::check_user(string username, string password) {
    User * user = get_user(username);
    if (user == NULL)
        return false;
    string user_encrypted_password = user->get_password();
    Authenticator * auth = new Authenticator;
    string user_password = auth->decrypt(user_encrypted_password);
    if (password.compare(user_password))
        return true;
    else
        return false;
}

/**
 * @brief Delete a User
 *
 * Search the storage file for a matching user and delete it
 * @author John Jewell
 * @date   29/10/2019
 * @param  username     A username
 * @return bool         true if success, else false
 */
bool User_Manager::delete_user(string username) {
    User * user = get_user(username);
    if (user == NULL)
        return false;

    ifstream file_input(DATABASE_FILE_PATH);
    string line;
    string new_database_string = "";
    while(getline(file_input, line)) {
        string current_username = line_to_username(line);
		if (current_username.compare(username) != 0) {
            line = line + "\n";
            new_database_string += line;
        }
    }
    file_input.close();
    remove(DATABASE_FILE_PATH.c_str());
    ofstream out(DATABASE_FILE_PATH);
    out << new_database_string;
    out.close();

    return true;
}
