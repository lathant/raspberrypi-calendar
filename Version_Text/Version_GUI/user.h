/* Class representing User
 * CREATED BY: John Jewell
 * LAST EDITED BY: Vladimir Zhurov
 * LAST EDITED: 30/10/2019
 * TODO: IMPLEMENT
 */

#ifndef USER_H
#define USER_H

#include "string"

class User {
    private:
        std::string username;
        std::string password;

    public:
        User(std::string input_username, std::string input_password);
        std::string get_username(){return username;}
        std::string get_password(){return password;}
};

#endif /* USER_H */
