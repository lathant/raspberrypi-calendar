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
#include "event_manager.h"

using namespace std;

static bool TESTING = true;
static string GET_FILE = "getF.txt";
int potatoNum = 1;

User_Manager* user_manager;
Timetable_Manager* timetable_manager;
Event_Manager* event_manager;
/*
private Clock clock;
private Observer_1 observer_1; #rename to descirbe observer when implemented
*/

string user_login(vector<string> parts){
    if(user_manager->check_user(parts.at(1), parts.at(2))){
        string login_text = "LOGIN|SUCCESS|"+parts.at(1)+"|"+parts.at(2);
        return login_text;
    }
    else
        return "LOGIN|FAILURE";
}

string user_create(vector<string> parts){
    string create_text;
    User* user = user_manager->get_user(parts.at(1));
    if(user == NULL){
        user = user_manager->create_user(parts.at(1), parts.at(2));
        create_text = "CREATE USER|SUCCESS|"+parts.at(1)+"|"+parts.at(2);
    }
    else
        create_text = "CREATE USER|FAILURE";
    delete user;
    return create_text;
}

string user_delete(vector<string> parts){
    User* user = user_manager->get_user(parts.at(1));
    if(user == NULL)
        return "DELETE USER|FAILURE";
    //Delete all timetables that user owns
    set<Timetable> owns = timetable_manager->get_personal_tables("username");
    for(set<Timetable>::iterator it = owns.begin(); it != owns.end(); it++){
        timetable_manager->delete_timetable(*it, "username");
        delete *it;
    }

    //Remove user from any timetable that hey are members of
    set<Timetable> uses = timetable_manager->get_shared_tables("username");
    for(set<Timetable>::iterator it = uses.begin(); it != uses.end(); it++){
        timetable_manager->remove_member(*it, "username");
        delete *it;
    }

    //Delete all events that user created and remove from any that is attached to
    delete user;
    user_manager->delete_user(parts.at(1));
    return "DELETE USER|SUCCESS";
}



string potato_output(){
    string potato_text = "POTATO|"+to_string(potatoNum);
    potatoNum++;
    return potato_text;
}

void console_control(string pid){
    string b_file = "b_"+pid+".txt"; // send
    string a_file = "a_"+pid+".txt"; // recive

    ofstream out_stream(b_file.c_str());
    ifstream in_stream;

    usleep(10000);

    out_stream << "START";
    out_stream.close();

    string command;
    vector<string> parts;
    bool control = true;
    while (control){
        in_stream.open(a_file.c_str());
        // check to see if file is non-empty
        if(in_stream.peek() != fstream::traits_type::eof()){
       	    // read in each line for commands
            while(getline(in_stream, command)){
                stringstream ss (command);
                while(getline(ss, command, '|'))
                    parts.push_back(command);

                out_stream.open(b_file.c_str());
                if(parts.at(0).compare("EXIT") == 0)
                    control = false;
                else if(parts.at(0).compare("LOGIN") == 0) // LOGIN|username|password
                    out_stream << user_login(parts);
                else if(parts.at(0).compare("CREATE USER") == 0) // CREATE USER|username|password
                    out_stream << user_create(parts);
                else if(parts.at(0).compare("DELETE USER") == 0) // DELETE USER|username|password
                    out_stream << user_delete(parts);
                else if(parts.at(0).compare("CREATE TIMETABLE") == 0) // CREATE TIMETABLE|
                    out_stream << timeable_create(parts);
                else if(parts.at(0).compare("GET TIMETABLES") == 0)
                    out_stream << timetable_get(parts);
                else if(parts.at(0).compare("GET TIMETABLE#") == 0)
                    out_stream << timetable_get(parts);
                else if(parts.at(0).compare("DELETE TIMETABLE#") == 0)
                    out_stream << timetable_delete(parts);
                else if (parts.at(0).compare("COMPARE TIMETABLES") == 0)
                    out_stream << timetable_compare(parts);
                else if(parts.at(0).compare("CREATE EVENT") == 0)
                    out_stream << event_create(parts);
                else if(parts.at(0).compare("GET EVENTS") == 0)
                    out_stream << event_get(parts);
                else if(parts.at(0).compare("GET EVENT#") == 0)
                    out_stream << event_get(parts);
                else if(parts.at(0).compare("ADD EVENT") == 0)
                    out_stream << event_add(parts);
                else if(parts.at(0).compare("DELETE EVENT") == 0)
                    out_stream << event_delete(parts);
                else if(parts.at(0).compare("REMOVE EVENT") == 0)
                    out_stream << event_remove(parts);
                else if(parts.at(0).compare("POTATO") == 0)
                    out_stream << potato_output();
                else
                    out_stream << "INVALID COMMAND TYPE";
                parts.clear();
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

void init_Time_Table_Manager(){
    if (TESTING)
        cout << "Time Table Manager intialized" << endl;
    time_table_manager = Timetable_Manager::get_instance();
    if(TESTING){
        //implement rigerous tests
    }
}


void init_Event_Manager(){
    if (TESTING)
        cout << "Event Manager intialized" << endl;
    event_manager = Event_Manager::get_instance();
    if(TESTING){
        //implement rigerous tests
    }
}
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
