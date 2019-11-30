/**
 * @brief Class implementing Requester
 *
 * Allows for comunicattion between GUI and control allowing for multiple concurent users
 * @author  Vladimir Zhurov
 * @date    30/10/2019
 */

#include "requester.h"

using namespace std;

static string GET_FILE = "getF.txt";

/**
 * @brief Constructor for Requester
 *
 * @author  Vladimir Zhurov
 * @date    30/10/2019
 */
Requester::Requester() {
        booted = false;
        create_instance();
}

/**
 * @brief Requests creation of thread for comunication
 *
 * Sends the pid of this instance over to the GET_FILE
 * control main will read it and spawn a thread
 * @author  Vladimir Zhurov
 * @date    30/10/2019
 * @param   pid             The pid of the instance requestting comunication
 */
void Requester::send_console_pid(pid_t pid){
    string send = to_string(pid) + '\n';
    ofstream out_stream(GET_FILE.c_str(), ios_base::app);
    out_stream << send;
    out_stream.close();
}

/**
 * @brief handles creation of comunication instance
 *
 * Gives comunication files names and sets booted to true
 * @author  Vladimir Zhurov
 * @date    30/10/2019
 */
void Requester::create_instance(){
    pid_t pid = getpid();
    send_console_pid(pid); // Create comunication thread
    usleep(10000);
    a_file = "a_"+to_string(pid)+".txt"; // send
    b_file = "b_"+to_string(pid)+".txt"; // receive
    ifstream in_stream;
    string line;
    bool control = true;
    while(control){
        in_stream.open(b_file.c_str());
        // check to see if file is non-empty
        if(in_stream.peek() != fstream::traits_type::eof()){
            getline(in_stream, line); // Read in initilization message
            control = false;
        }
        if(in_stream)
            in_stream.close();
        usleep(10000);
    }
    booted = true;
}

/**
 * @brief Pass requests to thread
 *
 * writes request to send file and reads response from return file
 * @author  Vladimir Zhurov
 * @date    30/10/2019
 * @param   request         The request
 * @return  response        The response
 */
string Requester::ask_control(string request){
    if(!booted){
        create_instance();
    }
    ofstream out_stream;
    out_stream.open(a_file.c_str());
    out_stream << request;
    out_stream.close();

    ifstream in_stream;
    string response;
    bool control = true;
    while(control){
        in_stream.open(b_file.c_str());
        // check to see if file is non-empty
        if(in_stream.peek() != fstream::traits_type::eof()){
            getline(in_stream, response);
            control = false;
        }
        if(in_stream)
            in_stream.close();
        usleep(10000);
    }
    return response;
}
