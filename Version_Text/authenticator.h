 /**
  * @brief Class representing Authenticator
  *
  * The representing of Authenticator's functions
  * @author  John Jewell
  * @date   29/10/2019
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
