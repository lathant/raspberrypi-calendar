/**
 * @brief   Allows user to access control's functionality
 *
 * Spawns an instance for tthe user and comunicates using sender and reciever files
 * @author  Vladimir Zhurov
 * @date    30/11/2019
 */

#include <iostream>
#include <unistd.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cstdio>
#include <ctime>

using namespace std;

static string GET_FILE = "getF.txt";

/**
 * @brief   contacts control with pid info
 *
 * sends a message to control to spawn a thread instance for given pid
 * @author  Vladimir Zhurov
 * @date    28/10/2019
 */
void send_console_pid(pid_t pid){
    string send = to_string(pid) + '\n';
    ofstream out_stream(GET_FILE.c_str(), ios_base::app);
    out_stream << send;
    out_stream.close();
}

/**
 * @brief   Main user input handler
 *
 * Send and recieve comunication between the user and their person comunication thread in control through use of comunication files
 * @author  Vladimir Zhurov
 * @date    30/11/2019
 */
int main(){
    pid_t pid = getpid();

    string a_file = "a_"+to_string(pid)+".txt"; // send
    string b_file = "b_"+to_string(pid)+".txt"; // receive

    // remove residual files
    remove(a_file.c_str());
    remove(b_file.c_str());

    send_console_pid(pid);

    ofstream out_stream(a_file.c_str(), ios_base::app);
    ifstream in_stream;

    //sync up
    out_stream << " ";
    out_stream.close();
    usleep(10000);

    clock_t last_input = clock();
    double time_elapsed;
    string line, command;
    bool control = true;
    while (control){
        in_stream.open(b_file.c_str());
        // check to see if file is non-empty
        if(in_stream.peek() != fstream::traits_type::eof()){
            last_input = clock();
            // read in each line and output
            while(getline(in_stream, line))
                cout << endl << line;
            cout << endl;
	    cout << "Input: ";
            cin >> command;
            out_stream.open(a_file.c_str());
            out_stream << command;
	        out_stream.close();
            if(command.compare("EXIT") == 0)
                control = false;
            command = "";
            in_stream.close();
            remove(b_file.c_str());
    	}
        if(in_stream)
            in_stream.close();
        usleep(10000);
        time_elapsed = (clock() - last_input)/(double) CLOCKS_PER_SEC;
        if(time_elapsed >= 240.0) //timeout
            control = false;
    }
    out_stream.close();

    //delete the io files
    remove(a_file.c_str());
    remove(b_file.c_str());

    cout << "Console instance "+to_string(pid)+" terminated" << endl;
    return 0;
}
