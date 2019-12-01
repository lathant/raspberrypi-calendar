/* Class representing User
 * CREATED BY: John Jewell
 * LAST EDITED BY: Vladimir Zhuurov
 * LAST EDITED: 30/10/2019
 * TODO: IMPLEMENT
 */

#include "user_factory.h"

using namespace std;

//implement to store value for factory opperation method
User_Factory::User_Factory(){};

User* User_Factory::create_user(string input_username, string input_password) {
    User* usr = new User(input_username, input_password);
    return usr;
}
