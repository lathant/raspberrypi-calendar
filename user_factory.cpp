/**
 * @brief Class implementing User_Factory
 *
 * The implementation of User_Factory
 * @author John Jewell
 * @author Vladimir Zhurov
 * @date   30/10/2019
 */
#include "user_factory.h"

using namespace std;

/**
 * @brief constructor for User_Factory
 *
 * @author  John Jewell
 * @date    29/10/2019
 */
User_Factory::User_Factory(){};

/**
 * @brief Create a new user
 *
 * Call the User object constructor
 * @author  John Jewell
 * @author  Vladimir Zhurov
 * @date    30/10/2019
 * @param   input_username      Username
 * @param   input_password      User password
 * @return  usr                 User Object
 */
User* User_Factory::create_user(string input_username, string input_password) {
    User* usr = new User(input_username, input_password);
    return usr;
}
