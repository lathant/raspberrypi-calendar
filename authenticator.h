/* Header for class representing Authenticator
 * CREATED BY: John Jewell
 * LAST EDITED BY: John Jewell
 * LAST EDITED: 29/10/2019
 * TODO: IMPLEMENT
 */

#ifndef AUTHENTICATOR_H
#define AUTHENTICATOR_H

#include "string"
#include "iostream"

class Authenticator {
    private:
        std::string key;

    public:
        std::string encrypt(std::string encrypted_password);
        std::string decrypt(std::string encrypted_password);
};

#endif /* AUTHENTICATOR_H */
