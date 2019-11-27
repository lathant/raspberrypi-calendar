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

 /**
  * @brief the main controling instance for the calandar system
  *
  * The main instance for the calandar system which spawns threads to deal with users and interacts with the manager classes
  * @author  Vladimir Zhurov
  * @date   25/11/2019
  */

#include <iostream>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <thread>
#include <cstdio>
#include <ctime>

#include "user_manager.h"
#include "timetable_manager.h"
#include "event_manager.h"

using namespace std;

static bool TESTING = false;
static string GET_FILE = "getF.txt";
int potatoNum = 1;

User_Manager* user_manager;
Timetable_Manager* timetable_manager;
Event_Manager* event_manager;
/*
private Clock clock;
private Observer_1 observer_1; #rename to descirbe observer when implemented
*/

/**
 * @brief Log in a user
 *
 * Check to see if a user log in information is correct and respond back with a string of either success or failure
 * @author  Vladimir Zhurov
 * @date   25/11/2019
 * @param   parts           A vector of strings containing <LOGIN,username,password>
 * @return  login_text      An output string that says if login success or failure
 */
string user_login(vector<string> parts){
    if(user_manager->check_user(parts.at(1), parts.at(2))){
        string login_text = "LOGIN|SUCCESS|"+parts.at(1)+"|"+parts.at(2);
        return login_text;
    }
    else
        return "LOGIN|FAILURE";
}

/**
 * @brief Create a new user
 *
 * Check to see if a user is already real, if provided information is unique creat a new user
 * @author  Vladimir Zhurov
 * @date   25/11/2019
 * @param   parts           A vector of string containing <CREATE USER,username,password>
 * @return  create_text     An output string that says if user create was success or failure
 */
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

/**
 * @brief Delete an exsisting user
 *
 * Check to see if a user is already real, then delete all the timetables they
 * own, remove them as members from any timetables they have joined, delete
 * any events that they own, remove any reminders pointed at them.
 * @author  Vladimir Zhurov
 * @date   25/11/2019
 * @param   parts           A vector of string containing <DELETE USER,username,password>
 * @return  create_text     An output string that says if user delete was success or failure
 */
string user_delete(vector<string> parts){
    User* user = user_manager->get_user(parts.at(1));
    if(user == NULL)
        return "DELETE USER|FAILURE";
    //Delete all timetables that user owns
    set<Timetable> owns = timetable_manager->get_personal_tables(parts.at(1));
    for(set<Timetable>::iterator it = owns.begin(); it != owns.end(); it++){
        timetable_manager->delete_timetable(it->get_name());
    }

    //Remove user from any timetable that hey are members of
    set<Timetable> uses = timetable_manager->get_shared_tables(parts.at(1));
    for(set<Timetable>::iterator it = uses.begin(); it != uses.end(); it++){
        timetable_manager->remove_member(it->get_name(), parts.at(1));
    }

    //Delete all events that user created and remove from any that is attached to
    vector<Event> storage = event_manager->get_personal_events(parts.at(1));
    for(vector<Event>::iterator it = storage.begin(); it != storage.end(); it++){
        string eName = it->get_eventName();
        event_manager->delete_event(eName);
    }
    delete user;
    user_manager->delete_user(parts.at(1));
    return "DELETE USER|SUCCESS";
}

/**
 * @brief Create a timetable for a given user
 *
 * Assume user is real and create a blank timetable using the given information
 * @author  Vladimir Zhurov
 * @date   25/11/2019
 * @param   parts           A vector of string containing <CREATE TIMETABLE,table_name,access_type,username>
 * @return  create_text     An output string that says if create timetable was success or failure
 */
string timeable_create(vector<string> parts){
    int success = timetable_manager->create_timetable(parts.at(1), parts.at(2), parts.at(3));
    if(success == 0)
        return "CREATE TIMETABLE|FAILURE";
    return "CREATE TIMETABLE|SUCCESS";
}

/**
 * @brief Get a or multiple timetables for a given user
 *
 * if get_type = 0 get all personal timetables
 * if get_type = 1 get all shared timetables
 * if get_type = 2 get all public timetables
 * if get_type = 3 get both personal and shared
 * if get_type = 4 get both shared and public
 * if get_type = 5 get all timetables avalible to given user
 * @author  Vladimir Zhurov
 * @date   25/11/2019
 * @param   parts           A vector of string containing <GET TIMETABLE,get_type,username>
 * @return  create_text     An output string that says if get timetable was success or failure and the timetables in string form
 */
string timetable_get(vector<string> parts){
    int get_type = stoi(parts.at(1));
    set<Timetable> storage;
    string text_output= "GET TIMETABLE";
    if(get_type == 0 || get_type == 3 || get_type == 5){
        storage = timetable_manager->get_personal_tables(parts.at(2));
        text_output += "|PERSONAL";
        for(set<Timetable>::iterator it = storage.begin(); it != storage.end(); it++){
            text_output += "|";
            text_output += timetable_manager->timetable_to_txt(*it);
        }
    }
    if(get_type == 1 || get_type == 3 || get_type == 5){
        storage = timetable_manager->get_shared_tables(parts.at(2));
        text_output += "|SHARED";
        for(set<Timetable>::iterator it = storage.begin(); it != storage.end(); it++){
            text_output += "|";
            text_output += timetable_manager->timetable_to_txt(*it);
        }
    }
    if(get_type == 2 || get_type == 4 || get_type == 5){
        storage = timetable_manager->get_public_tables();
        text_output += "|PUBLIC";
        for(set<Timetable>::iterator it = storage.begin(); it != storage.end(); it++){
            text_output += "|";
            text_output += timetable_manager->timetable_to_txt(*it);
        }
    }
    return text_output;
}

/**
 * @brief delete a timetable for a given user
 *
 * Assume user is real and delete a given timetable
 * @author  Vladimir Zhurov
 * @date   25/11/2019
 * @param   parts           A vector of string containing <DELETE TIMETABLE,table_name>
 * @return  create_text     An output string that says if delete timetable was success or failure
 */
string timetable_delete(vector<string> parts){
    int success = timetable_manager->delete_timetable(parts.at(1));
    if(success == 0)
        return "DELETE TIMETABLE|FAILURE";
    return "DELETE TIMETABLE|SUCCESS";
}

/**
 * @brief compare two timetable
 *
 * Call the compare_timetables() function and return the string rep of the comparison table
 * @author  Vladimir Zhurov
 * @date   25/11/2019
 * @param   parts           A vector of string containing <COMPARE TIMETABLE,table_name1,table_name2>
 * @return  create_text     An output string rep of the comparison table
 */
string timetable_compare(vector<string> parts){
    string cTable = timetable_manager->compare_timetables(parts.at(1), parts.at(2));
    if(cTable.compare("ERROR") == 0)
        return "COMPARE TIMETABLE|FAILURE";
    string text_output = "COMPARE TIMETABLE|SUCCESS|";
    text_output += cTable;
    return text_output;
}

/**
 * @brief add a meber to a timetable
 *
 * @author  Vladimir Zhurov
 * @date    26/11/2019
 * @param   parts           A vector of string containing <ADD MEMBER,table_name,member_name>
 * @return  strings         An output of the result of the attempt to add member to timetable
 */
string timetable_add(vector<string> parts){
    int success = timetable_manager->add_member(parts.at(1), parts.at(2));
    if(success == 0)
        return "ADD MEMBER|FAILURE";
    else if (success == -1)
        return "ADD MEMBER|DUPLICATE";
    return "ADD MEMBER|SUCCESS";
}

/**
 * @brief create an event for a given user
 *
 *
 * @author  Vladimir Zhurov
 * @date   25/11/2019
 * @param   parts           A vector of string containing <CREATE EVENT,eventName,
 *                              details,start_time_string,end_time_string,access_t,username,repeatType>
 * @return  string     An output string that says if create event was success or failure
 */
string event_create(vector<string> parts){
    time_t start_time = stol(parts.at(3));
    time_t end_time = stol(parts.at(4));
    int success = event_manager->create_event(parts.at(1), parts.at(2), start_time,
        end_time, parts.at(5), parts.at(6),parts.at(7));
    if(success == 0)
        return "CREATE EVENT|FAILURE";
    return "CREATE EVENT|SUCCESS";
}

/**
 * @brief get a or multiple events
 *
 * if get_type = 0 get all personal events
 * if get_type = 1 get all public events
 * if get_type = 2 get all events
 *
 * @author  Vladimir Zhurov
 * @date   25/11/2019
 * @param   parts           A vector of string containing <GET EVENT,get_type,username>
 * @return  text_output     An output string that says if get event was success or failure and the events in string form
 */
string event_get(vector<string> parts){
    int get_type = stoi(parts.at(1));
    vector<Event> storage;
    string text_output= "GET TIMETABLE";
    if(get_type == 0 || get_type == 2){
        storage = event_manager->get_personal_events(parts.at(2));
        text_output += "|PERSONAL";
        for(vector<Event>::iterator it = storage.begin(); it != storage.end(); it++){
            text_output += "|";
            text_output += event_manager->event_to_txt(*it);
        }
    }
    if(get_type == 1 || get_type == 2){
        storage = event_manager->get_public_events();
        text_output += "|PUBLIC";
        for(vector<Event>::iterator it = storage.begin(); it != storage.end(); it++){
            text_output += "|";
            text_output += event_manager->event_to_txt(*it);
        }
    }
    return text_output;
}

/**
 * @brief adds an event to a timetable
 *
 * Calls the append_date method from timetable_manager and gives it an event to add to a timetable
 * @author  Vladimir Zhurov
 * @date   25/11/2019
 * @param   parts           A vector of string containing <ADD EVENT,table_name,event_info>
 * @return  string          An output string that says if add event to timetable was success or failure
 */
string event_add(vector<string> parts){
    int success = timetable_manager->append_date(parts.at(1), parts.at(2));
    if(success == 0)
        return "ADD EVENT|FAILURE";
    return "ADD EVENT|SUCCESS";
}

/**
 * @brief remove an event from a timetable
 *
 * Calls the remove_date method from timetable_manager and gives it an event's name that is to be removed from table
 * @author  Vladimir Zhurov
 * @date   25/11/2019
 * @param   parts           A vector of string containing <REMOVE EVENT,table_name,event_name>
 * @return  string          An output string that says if create event was success or failure
 */
string event_remove(vector<string> parts){
    int success = timetable_manager->remove_date(parts.at(1), parts.at(2));
    if(success == 0)
        return "REMOVE EVENT|FAILURE";
    return "REMOVE EVENT|SUCCESS";
}

/**
 * @brief delete an event
 *
 * Delete an event and prevent it from being added to other timetables (does not remove from timetables)
 * @author  Vladimir Zhurov
 * @date   25/11/2019
 * @param   parts           A vector of string containing <DELETE EVENT,event_name>
 * @return  string          An output string that says if create event was success or failure
 */
string event_delete(vector<string> parts){
    int success = event_manager->delete_event(parts.at(1));
    if(success == 0)
        return "DELETE EVENT|FAILURE";
    return "DELETE EVENT|SUCCESS";
}

/**
 * @brief POTATO
 *
 * Sends a string containing the current potato number
 * @author  Vladimir Zhurov
 * @date   25/11/2019
 * @return  potato_text     An output string that contains potato_num
 */
string potato_output(){
    string potato_text = "POTATO|"+to_string(potatoNum);
    potatoNum++;
    return potato_text;
}

/**
 * @brief A thread instance that allows comunication between the user and the system
 *
 * Using the provided pid two files are created for comunication between the user console and the thread instance.
 *      console_control will waits untill user's console writes to its file and then acts upon that input.
 *      Upon compleating it's task console_control writes a response message through it's response file.
 * @author  Vladimir Zhurov
 * @date    25/11/2019
 * @param   pid                 A unique pid id for the user's console
 */
void console_control(string pid){
    string b_file = "b_"+pid+".txt"; // send
    string a_file = "a_"+pid+".txt"; // recive

    ofstream out_stream(b_file.c_str());
    ifstream in_stream;

    usleep(10000);

    out_stream << "START";
    out_stream.close();

    clock_t last_input = clock();
    double time_elapsed;
    string command;
    vector<string> parts;
    bool control = true;
    while (control){
        in_stream.open(a_file.c_str());
        // check to see if file is non-empty
        if(in_stream.peek() != fstream::traits_type::eof()){
            last_input = clock();
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
                else if(parts.at(0).compare("CREATE TIMETABLE") == 0) // CREATE TIMETABLE|table_name|access_type|username
                    out_stream << timeable_create(parts);
                else if(parts.at(0).compare("GET TIMETABLE") == 0) // GET TIMETABLE|get_type|username
                    out_stream << timetable_get(parts);
                else if(parts.at(0).compare("DELETE TIMETABLE") == 0) // DELETE TIMETABLE|table_name|username
                    out_stream << timetable_delete(parts);
                else if (parts.at(0).compare("COMPARE TIMETABLES") == 0) // COMPARE TIMETABLE|table_name1|table_name2
                    out_stream << timetable_compare(parts);
                else if (parts.at(0).compare("ADD MEMBER") == 0) // ADD MEMBER|table_name|member_name
                    out_stream << timetable_add(parts);
                else if(parts.at(0).compare("CREATE EVENT") == 0) // CREATE EVENT|eventName|details|start_time_string|end_time_string|access_t|username|repeatType>
                    out_stream << event_create(parts);
                else if(parts.at(0).compare("GET EVENT") == 0) // GET EVENT|get_type|username
                    out_stream << event_get(parts);
                else if(parts.at(0).compare("ADD EVENT") == 0) // ADD EVENT|table_name|event_info
                    out_stream << event_add(parts);
                else if(parts.at(0).compare("REMOVE EVENT") == 0) // REMOVE EVENT|table_name|event_name
                    out_stream << event_remove(parts);
                else if(parts.at(0).compare("DELETE EVENT") == 0) // DELETE EVENT|event_name
                    out_stream << event_delete(parts);
                else if(parts.at(0).compare("POTATO") == 0) // POTATO
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
        time_elapsed = (clock() - last_input)/(double) CLOCKS_PER_SEC;
        if(time_elapsed >= 240.0) // timeout
            control = false;
    }
    out_stream.close();
}

/**
 * @brief initilize the user_manager
 *
 *
 * @author  Vladimir Zhurov
 * @date    25/11/2019
 */
void init_User_Manager(){
    if (TESTING)
        cout << "User Manager intialized" << endl;
    user_manager = User_Manager::get_instance();
    if (TESTING){
        //implement rigerous tests
    }
}

/**
 * @brief initilize the timetable_manager
 *
 *
 * @author  Vladimir Zhurov
 * @date    25/11/2019
 */
void init_Timetable_Manager(){
    if (TESTING)
        cout << "Time Table Manager intialized" << endl;
    timetable_manager = Timetable_Manager::get_instance();
    if(TESTING){
        //implement rigerous tests
    }
}

/**
 * @brief initilize the event_manager
 *
 *
 * @author  Vladimir Zhurov
 * @date    25/11/2019
 */
void init_Event_Manager(){
    if (TESTING)
        cout << "Event Manager intialized" << endl;
    event_manager = Event_Manager::get_instance();
    if(TESTING){
        //implement rigerous tests
    }
}
//void init_Clock(){if (TESTING)
//    cout << "Clock intialized" << endl;}
//void init_Observers(){if (TESTING)
//    cout << "Observers intialized" << endl;}
//void delete_everything(){ cout << "Everything deleted" << endl;}

/**
 * @brief The main process for the system that spawns threads to deal with individual users
 *
 * The main process initilizeses all of the required managers and then begins to wait on the GET_FILE
 *      The user console will write a pid to the GET_FILE when this occours main will spawns a thread with the pid as argument and clear GET_FILE
 * @author  Vladimir Zhurov
 * @date    25/11/2019
 */
int main(){
    if (TESTING)
        cout << "Calender Planner server is turned on" << endl;
    init_User_Manager();
    init_Timetable_Manager();

    init_Event_Manager();

    //init_Clock();

    //init_Observers();

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
                    //delete_everything();
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
