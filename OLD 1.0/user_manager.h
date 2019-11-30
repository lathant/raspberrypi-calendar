 /**
  * @brief Class representing User_Manager
  *
  * A representation of User_Manager
  * @author John Jewell
  * @date   29/10/2019
  */

#ifndef USER_MANAGER_H
#define USER_MANAGER_H

#include <iostream>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include "string"
#include "user.h"
#include "user_factory.h"
#include "authenticator.h"

class User_Manager {
    private:
        static User_Manager* instance;
        User_Manager(){};
        std::string line_to_username(std::string line);
        std::string line_to_password(std::string line);

    public:
        static User_Manager* get_instance();
        User* create_user(std::string username, std::string password);
        User* get_user(std::string username);
        bool check_user(std::string username, std::string password);
        bool delete_user(std::string username);
};

#endif /* USER_MANAGER_H */
