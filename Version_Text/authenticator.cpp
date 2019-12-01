 /**
  * @brief Implementation of Authenticator
  *
  * The implementation of Authenticator's functions
  * @author  John Jewell
  * @date   29/10/2019
  */
#include "authenticator.h"

using namespace std;

/**
 * @brief encrypt a password
 *
 * Aplies a simple encryption to a given string
 * @author  John Jewell
 * @date    29/10/2019
 * @param   password                The string to be encrypted
 * @return  encrypted_password      The encrypted string
 */
string Authenticator::encrypt(string password) {
    int length = password.length();
    string encrypted_password;
    for (int i = 0; i < length && password[i] != '\0'; i++)
        encrypted_password += password[i] + 2;
    return encrypted_password;
}

/**
 * @brief decrypt a password
 *
 * Aplies a simple decryption to a given string
 * @author  John Jewell
 * @date    29/10/2019
 * @param   encrypted_password      The string to be decrypted
 * @return  encrypted_password      The decrypted string
 */
string Authenticator::decrypt(string encrypted_password) {
    int length = encrypted_password.length();
    string password;
    for (int i = 0; i < length && encrypted_password[i] != '\0'; i++)
        password += encrypted_password[i] - 2;
    return password;
}
