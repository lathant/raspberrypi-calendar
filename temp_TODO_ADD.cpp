//response = ask_control(request)
// grant greatter scope
static string GET_FILE = "getF.txt";
string a_file, b_file;

/**
 * @author  Vladimir Zhurov
 */
void send_console_pid(pid_t pid){

    string send = to_string(pid) + '\n';

    ofstream out_stream(GET_FILE.c_str(), ios_base::app);
    out_stream << send;

    out_stream.close();
}

// call when launching GUI
/**
 * @author  Vladimir Zhurov
 */
string create_instance(){
    pid_t pid = getpid();
    send_console_pid(pid);
    usleep(10000);
    a_file = "a_"+to_string(pid)+".txt"; // send
    b_file = "b_"+to_string(pid)+".txt"; // receive
}

// call instead of control method
/**
 * @author  Vladimir Zhurov
 */
string ask_control(string request){
    out_stream.open(a_file.c_str());
    out_stream << request;
    out_stream.close();
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

// add back in old control.cpp inroduce methods into required sections.
