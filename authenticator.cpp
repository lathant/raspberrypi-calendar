/* Class representing Authenticator
 * CREATED BY: John Jewell
 * LAST EDITED BY: John Jewell
 * LAST EDITED: 29/10/2019
 * TODO: IMPLEMENT
 */

#include "authenticator.h"

using namespace std;

//Basic encryption
string Authenticator::encrypt(string password) {
    int length = password.length();
    string encrypted_password;
    for (int i = 0; i < length && password[i] != '\0'; i++)
        encrypted_password += password[i] + 2;
    return encrypted_password;
}

//Basic decryption
string Authenticator::decrypt(string encrypted_password) {
    int length = encrypted_password.length();
    string password;
    for (int i = 0; i < length && encrypted_password[i] != '\0'; i++)
        password += encrypted_password[i] - 2;
    return password;
}
