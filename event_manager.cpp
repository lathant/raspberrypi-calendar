/**
 * @brief      Class for the event manager
 * @author     Vladimir Zhurov
 * @date       25/11/2019
 */
 #include <iostream>
 #include <fstream>
 #include <string.h>
 #include <stdio.h>
 #include "string"
 #include "event_manager.h"

using namespace std;

static string STORAGE_FILE_PATH = "./data/events/events.csv";

Event_Manager* Event_Manager::instance = NULL;
/**
 * @brief       returns an instance of Event_Manager
 *
 * returns an instance of Event_Manager and enforces singleton design
 * @Author      Vladimir Zhurov
 * @date        25/11/2019
 */
Event_Manager* Event_Manager::get_instance() {
    if (instance == NULL)
        instance = new Event_Manager;
    return instance;
}

/**
 *
 */
Event* Event_Manager::get_event(string event_name){

}

/**
 * @brief       create a new event
 *
 * @author      Vladimir Zhurov
 * @date        25/11/2019
 * @param       eventName
 * @param       details
 * @param       start_time
 * @param       end_time
 * @param       access_t
 * @param       owner_id
 * @param       repeatType
 * @return      int                 -1 duplicate, 0 on failure, and 1 on success
 */
int Event_Manager::create_event(string eventName, string details, time_t start_time,
    time_t end_time, string access_t, string owner_id, string repeatType){
    Event* event = get_event(eventName);
    if (event != NULL)
        return -1;
    Event_Factory* factory = new Event_Factory();
    event = factory->create_event(eventName, details, start_time, end_time,
        access_t, owner_id, repeatType);
    string event_db_entry = eventName + "," + details + "," + to_string(start_time) +
        "," + to_string(end_time) + "," + access_t + "," + owner_id + "," + repeatType;
    ofstream out(STORAGE_FILE_PATH, ios::app);
    out << event_db_entry << endl;
    out.close();
    return 1;
}

/**
 * @brief       delete a event
 *
 * @author      Vladimir Zhurov
 * @date        25/11/2019
 * @param       event_name          The name of the event
 * @return
 */
int Event_Manager::delete_event(string event_name){

}

/**
 * @brief       get all personal events for a user
 *
 * @author      Vladimir Zhurov
 * @date        25/11/2019
 * @param       owner_id          The name of the user
 * @return
 */
set<Event> Event_Manager::get_personal_events(string owner_id){

}

/**
 * @brief       get all shared events for a user
 *
 * @author      Vladimir Zhurov
 * @date        25/11/2019
 * @param       owner_id          The name of the user
 * @return
 */
set<Event> Event_Manager::get_shared_events(string owner_id){

}

/**
 * @brief       get all public events
 *
 * @author      Vladimir Zhurov
 * @date        25/11/2019
 * @return
 */
set<Event> Event_Manager::get_public_events(){

}

/**
 * @brief       get a text rep for a given event
 *
 * @author      Vladimir Zhurov
 * @date        25/11/2019
 * @param       event          The event
 * @return
 */
string Event_Manager::event_to_txt(Event event){

}
