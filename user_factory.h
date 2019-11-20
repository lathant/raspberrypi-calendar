/* Class representing User
* CREATED BY: John Jewell
* LAST EDITED BY: Vladimir Zhurov
* LAST EDITED: 30/10/2019
* TODO: IMPLEMENT
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
