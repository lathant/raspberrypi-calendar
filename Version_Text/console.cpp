/* Source of instanced user inputs for calandar system
 * CREATED BY: Vladimir Zhurov
 * LAST EDITED BY: Vladimir Zhurov
 * LAST EDITED: 28/10/2019
 * TODO: Improve comments and add more robust error checking
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

//give control the console pid to create IO_File
void send_console_pid(pid_t pid){

    string send = to_string(pid) + '\n';

    ofstream out_stream(GET_FILE.c_str(), ios_base::app);
    out_stream << send;

    out_stream.close();
}

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
