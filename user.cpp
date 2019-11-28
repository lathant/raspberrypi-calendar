 /**
  * @brief Class implementing User
  *
  * An implementing User
  * @author John Jewell
  * @author Vladimir Zhurov
  * @date   30/10/2019
  */

#include "user.h"

using namespace std;

/**
 * @brief Constructor for User
 *
 * The constructor for the User
 * @author John Jewell
 * @author Vladimir Zhurov
 * @date   30/10/2019
 * @param   input_username      The user's username
 * @param   input_password      The user's password
 */
User::User(string input_username, string input_password) {
    username = input_username;
    password = input_password;
}
