/**
 * @brief Class representing Requester
 *
 * A representation of Requester
 * @author Vladimir Zhurov
 * @date   30/10/2019
 */
#ifndef REQUESTER_H
#define REQUESTER_H

#include <iostream>
#include <unistd.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cstdio>
#include <ctime>
#include <string>

class Requester {
    private:
        std::string a_file;
        std::string b_file;
        bool booted;
        void create_instance();
        void send_console_pid(pid_t pid);

    public:
        Requester();
        std::string ask_control(std::string request);
};

#endif /* REQUESTER_H */
