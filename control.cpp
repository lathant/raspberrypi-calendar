/* Main instance for calandar system that handles users
 * CREATED BY: Vladimir Zhurov
 * LAST EDITED BY: Vladimir Zhurov
 * LAST EDITED: 30/10/2019
 * TODO: fix output text format
 * 	add more robust error checking
 * 	connect and implement other classes
 * 	improve comments
 *  add timeout functionality in threads to prevent memory leak from idel threads
 *  seperate some of console_control thread opperations into seperate functions
 *  expand exsisting functionality in console_control
 */

#include <iostream>
#include "iostream"
#include "fstream"
#include "sstream"
#include "vector"
#include "string"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <thread>

#include "user_manager.h"
#include "timetable_manager.h"

using namespace std;

static bool TESTING = true;
static string GET_FILE = "getF.txt";
int potatoNum = 1;

User_Manager* user_manager;
/*
private Time_Table_Manager time_table_manager;
private Event_Manager event_manager;
private Clock clock;
private Observer_1 observer_1; #rename to descirbe observer when implemented
*/


string potato_output(string username){
    string potato_text = "potato has been called " + to_string(potatoNum) + " times \n["+username+"]: ";
    potatoNum++;
    return potato_text;
}

string help_output(string username){
    string help_text = "Commands: \n"
    "-help\n\tDisplay all valid commands \n"
    "potato\n\tDisplay the potato num \n"
    "EXIT\n\tClose down this console \n"
    "["+username+"]: ";
    return help_text;
}

void console_control(string pid){
    User* user;
    string username, password;
    bool expect_i, expect_un, expect_p, create_flag;

    string b_file = "b_"+pid+".txt"; // send
    string a_file = "a_"+pid+".txt"; // recive

    ofstream out_stream(b_file.c_str());
    ifstream in_stream;

    string command;
    bool control = true;

    usleep(10000);

    expect_i = true;
    out_stream << "Create or LogIn: ";
    out_stream.close();
    while (control){
        in_stream.open(a_file.c_str());
        // check to see if file is non-empty
        if(in_stream.peek() != fstream::traits_type::eof()){
       	    // read in each line for commands
            while(getline(in_stream, command)){
                out_stream.open(b_file.c_str());
                if(expect_i) // expect that first input is related to logging in or create
                {
                    //can be reformated to remove unneeded lines
                    if(command.compare("Create") == 0) // temporarly treated as the same as log in
                    {
                        expect_i = false;
                        expect_un = true;
                        create_flag = true;
                        out_stream << "Username: ";
                    }
                    else if(command.compare("LogIn") == 0){
                        expect_i = false;
                        expect_un = true;
                        create_flag = false;
                        out_stream << "Username: ";
                    }
                    else
                        out_stream << "Create OR LogIn: ";
                }
                else if(expect_un) //expect that the input is a username
                {
                    expect_un = false;
                    username = command;
                    expect_p = true;
                    out_stream << "Password: ";
                }
                else if(expect_p) //expect that the input is a password
                {
                    expect_p = false;
                    if(create_flag)// create a new user after checking to see if they are not already real
                    {
                        user = user_manager->get_user(username);
                        if(user == NULL){
                            user = user_manager->create_user(username, password);
                            out_stream << "USER CREATED\n["+username+"]: ";
                        }
                        else{
                            delete user;
                            expect_i = true;
			    out_stream << "USER ALREADY IS REAL\nCreate or LogIn: " ;
                        }
                    }
                    else // check to see if the user info is correct if else output the it failed and ask to create or log in again
                    {
                        if(user_manager->check_user(username, password)){
                            user = user_manager->get_user(username);
                            out_stream << "LOG IN SUCCESS\n["+username+"]: ";
                        }
                        else{
                            expect_i = true;
                            out_stream << "LOG IN FAILURE\nCreate or LogIn: ";
                        }
                    }
                }
                else if(command.compare("EXIT") == 0)
                    control = false;
                else if (command.compare("potato") == 0)
                    out_stream << potato_output(username);
                else if(command.compare("-help") == 0)
                    out_stream << help_output(username);
                else
		            out_stream << "INVALID COMMAND TYPE -help FOR LIST OF COMMANDS\n["+username+"]: ";
            }
	        out_stream.close();
            in_stream.close();
            remove(a_file.c_str());
    	}
        if(in_stream)
            in_stream.close();
        usleep(10000);
    }
    out_stream.close();
}

//initilize the user_manager instance
void init_User_Manager(){
    if (TESTING)
        cout << "User Manager intialized" << endl;
    user_manager = User_Manager::get_instance();
    if (TESTING){
        //implement rigerous tests
    }
}

void init_Time_Table_Manager(){if (TESTING)
    cout << "Time Table Manager intialized" << endl;}
void init_Event_Manager(){if (TESTING)
    cout << "Event Manager intialized" << endl;}
void init_Clock(){if (TESTING)
    cout << "Clock intialized" << endl;}
void init_Observers(){if (TESTING)
    cout << "Observers intialized" << endl;}
void delete_everything(){ cout << "Everything deleted" << endl;}

int main(){
    if (TESTING)
        cout << "Calender Planner server is turned on" << endl;
    init_User_Manager();

    init_Time_Table_Manager();

    init_Event_Manager();

    init_Clock();

    init_Observers();

    //Make sure IN_FILE and OUT_FILE are empty
    remove(GET_FILE.c_str());
    ifstream in_stream;

    string line;
    while (true){
        in_stream.open(GET_FILE.c_str());
        // check to see if file is non-empty
        if(in_stream.peek() != fstream::traits_type::eof()){
	    // read in each line
            while(getline(in_stream, line)){
                if(line.compare("TERMINATE") == 0){
                    cout << "Calender Planner TERMINATING" << endl;
                    in_stream.close();
                    delete_everything();
                    return 0;
                }
		thread threads(console_control, line);
		threads.detach();
	    }
            in_stream.close();
            remove(GET_FILE.c_str());
    	}
        if(in_stream)
            in_stream.close();
        usleep(10000);
    }

    return 0;
}
