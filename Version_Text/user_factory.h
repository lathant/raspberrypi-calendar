/**
 * @brief Class representing User_Factory
 *
 * A representation of User_Factory
 * @author John Jewell
 * @author Vladimir Zhurov
 * @date   30/10/2019
 */

#ifndef USER_FACTORY_H
#define USER_FACTORY_H

#include "string"
#include "user.h"

class User_Factory {
    public:
        User_Factory();
        User * create_user(std::string input_username, std::string input_password);
};

#endif /* USER_FACTORY_H */
