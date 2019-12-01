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

#include "user_manager.h"
#include "event_manager.h"
#include "timetable_manager.h"
#include "control.h"
using namespace std;

User_Manager* user_manager;
Event_Manager* event_manager;
Timetable_Manager* timetable_manager;
static bool TESTING = false;

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
        user = user_manager->create_user(parts.at(1), parts.at(1));
        create_text = "CREATE USER|SUCCESS|"+parts.at(1)+"|"+parts.at(2);
    }
    else
        create_text = "CREATE USER|FAILURE";
    delete user;
    return create_text;
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
    if(get_type == 0){

        storage = event_manager->get_personal_events(parts.at(2));

        text_output += "|PERSONAL";
        for(vector<Event>::iterator it = storage.begin(); it != storage.end(); it++){
            text_output += "|";
            text_output += event_manager->event_to_txt(*it);
        }
    }

    if(get_type == 1 || get_type == 2){

        storage = event_manager->get_public_events();
        cout << "hello" << endl;
        text_output += "|PUBLIC";
        for(vector<Event>::iterator it = storage.begin(); it != storage.end(); it++){
            text_output += "|";
            text_output += event_manager->event_to_txt(*it);
        }
    }
    return text_output;
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
    vector<Timetable> storage;
    string text_output= "GET TIMETABLE";
    if(get_type == 0){
        storage = timetable_manager->get_personal_tables(parts.at(2));
        text_output += "|PERSONAL";
        for(vector<Timetable>::iterator it = storage.begin(); it != storage.end(); it++){
            text_output += "|";
            text_output += timetable_manager->timetable_to_txt(*it);
        }
    }
    if(get_type == 1){
        storage = timetable_manager->get_shared_tables(parts.at(2));
        text_output += "|SHARED";
        for(vector<Timetable>::iterator it = storage.begin(); it != storage.end(); it++){
            text_output += "|";
            text_output += timetable_manager->timetable_to_txt(*it);
        }
    }
    if(get_type == 2){

        storage = timetable_manager->get_public_tables();
        cout << "hello2" << endl;
        text_output += "|PUBLIC";
        for(vector<Timetable>::iterator it = storage.begin(); it != storage.end(); it++){
            text_output += "|";
            text_output += timetable_manager->timetable_to_txt(*it);
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

