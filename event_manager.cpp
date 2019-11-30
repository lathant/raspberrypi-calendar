/**
 * @brief implementation of event manager
 *
 * The implementation of methods that manipulatet the Event storage file
 * @author  Lathan Thangavadivel
 * @author  Vladimir Zhurov
 * @date    30/11/2019
 */

#include <iostream>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <vector>
#include <sstream>
#include "string"
#include "event_manager.h"
#include <QStandardPaths>

using namespace std;

static string STORAGE_FILE_PATH = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation).toStdString() + "/events.csv";
Event_Manager* Event_Manager::instance = NULL;
Event_Factory* factory;
/**
 * @brief   returns an instance of Event_Manager
 *
 * returns an instance of Event_Manager and enforces singleton design
 * @Author  Vladimir Zhurov
 * @date    30/11/2019
 */
Event_Manager* Event_Manager::get_instance() {
    if (instance == NULL){
        instance = new Event_Manager;
        factory = new Event_Factory();
    }
    return instance;
}

/**
 * @brief gets the event attribute string
 *
 * @author   Lathan Thangavadivel
 * @author   Vladimir Zhurov
 * @date     30/11/2019
 * @param    event_name      event name as a string
 * @return   event           event attribute
 */
Event* Event_Manager::get_event(string event_name){
    string line, name;
    vector<string> parts;

    ifstream event_file(STORAGE_FILE_PATH);
    if(!event_file.is_open())
        return NULL; // Error occoured

    while(getline(event_file, line)){
            // Parse string into componants
            stringstream ss (line);
            while(getline(ss, line, '^'))
                parts.push_back(line);
            // If event_name matches return Event
            if (parts[0].compare(event_name) == 0){
                return factory->create_event(parts[0], parts[1], stol(parts[2]), stol(parts[3]),
                    parts[4], parts[5], parts[6]);
            }
            parts.clear(); // Clean up parts for next line
    }
    return NULL; // Not found
}

/**
 * @brief       create a new event
 *
 * @author      Vladimir Zhurov
 * @date        30/11/2019
 * @param       eventName
 * @param       details
 * @param       start_time
 * @param       end_time
 * @param       access_t
 * @param       owner_id
 * @param       repeatType
 * @return      int                 -1 duplicate, 0 on failure, and 1 on success
 */
int Event_Manager::create_event (string eventName, string details, time_t start_time,
    time_t end_time, string access_t, string owner_id, string repeatType){
    // Check if event is already in file
    Event* event = get_event(eventName);
    if (event != NULL) {
        return -1;
    }
    delete event; // free memory
    // Write string rep to file;
    string event_db_entry = eventName + "^" + details + "^" + to_string(start_time) +
        "^" + to_string(end_time) + "^" + access_t + "^" + owner_id + "^" + repeatType;
    ofstream out(STORAGE_FILE_PATH, ios::app);
    if(!out.is_open())
        return 0;
    out << event_db_entry << endl;
    out.close();
    return 1;
}

/**
 * @brief       delete a event
 *
 * removes the given event from the storage file
 * @author      Vladimir Zhurov
 * @date        30/11/2019
 * @param       event_name          The name of the event
 * @return      int                 0 on failure, 1 on success
 */
int Event_Manager::delete_event(string event_name){
    string line, name, new_database_string = "";
    size_t length;
    int success = 0;

    ifstream event_file(STORAGE_FILE_PATH);
    if(!event_file.is_open())
        return success; // Error occoured
    while(getline(event_file, line)){
        length = line.find("^"); // Length of event_name
        name = line.substr(0, length);
        if(name.compare(event_name) != 0)
            new_database_string += line + "\n"; // Write non matching event to string
        else
            success = 1;
    }
    event_file.close();
    remove(STORAGE_FILE_PATH.c_str()); // Remove file (deletes matching events)
    ofstream out(STORAGE_FILE_PATH);
    out << new_database_string; // Make new file and write all non matching events to it
    out.close();
    return success;
}

/**
 * @brief       get all personal events
 *
 * Reads through all stored Events in file and collects all that have matching owner_id
 * @author      Lathan Thangavadivel
 * @author      Vladimit Zhurov
 * @date        30/11/2019
 * @param       owner_id                The username of the owner
 * @return      output                  A vector of Event objects that have  matching owner_id
 */
vector<Event> Event_Manager::get_personal_events(string owner_id){
    vector<Event> output;
    vector<string> parts;
    string line;

    ifstream event_file(STORAGE_FILE_PATH);
    if(!event_file.is_open())
        return output; // Error occoured
    while(getline(event_file, line)){
        // Parse string into componants
        stringstream ss (line);
        while(getline(ss, line, '^'))
            parts.push_back(line);
        // If owner_id matches add to collection
        if (parts[5].compare(owner_id) == 0){
            Event* newEvent = factory->create_event(parts[0], parts[1], stol(parts[2]), stol(parts[3]),
                                                    parts[4], parts[5], parts[6]);
            output.push_back(*newEvent);
        }
        parts.clear(); // Clean up parts for next line
    }
    return output;
}

/**
 * @brief       get all public events
 *
 * Reads through all stored Events in file and collects all that are public
 * @author      Lathan Thangavadivel
 * @author      Vladimit Zhurov
 * @date        30/11/2019
 * @return      output                  A vector of Event objects that have public access
 */
vector<Event> Event_Manager::get_public_events(){
    vector<Event> output;
    vector<string> parts;
    string line;

    ifstream event_file(STORAGE_FILE_PATH);
    if(!event_file.is_open())
        return output; // Error occoured
    while(getline(event_file, line)){
        // Parse string into componants
        stringstream ss (line);
        while(getline(ss, line, '^'))
            parts.push_back(line);
        // If access if public add to collection
        if (parts[4].compare("public") == 0){
            Event* newEvent = factory->create_event(parts[0], parts[1], stol(parts[2]), stol(parts[3]),
                                                    parts[4], parts[5], parts[6]);
            output.push_back(*newEvent);
        }
        parts.clear(); // Clean up parts for next line
    }
    return output;
}

/**
 * @brief       get a text rep for a given event
 *
 * @author      Vladimir Zhurov
 * @date        30/11/2019
 * @param       event          The event
 * @return      txt_rep        A text representation of a given event object
 */
string Event_Manager::event_to_txt(Event event){
    string txt_rep = "";
    txt_rep += event.get_eventName() + "^" +
        event.get_details() + "^" +
        to_string(event.get_start_time()) + "^" +
        to_string(event.get_end_time()) + "^" +
        event.get_access_t() + "^" +
        event.get_owner_id() + "^" +
        event.get_repeat_type();
    return txt_rep;
}
