/* Class for the event manager
 * CREATED BY: Lathan Thangavadivel
 * LAST EDITED BY: Lathan Thangavadivel
 * LAST EDITED: 25/11/2019
 * @brief the file that contains the functions to handle events
 *
 * @author  Lathan Thangavadivel, Vladimir Zhurov
 * @date   25/11/2019
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

/*
* @brief gets the event attribute string
*
* @author             Lathan Thangavadivel
* @param  event_name  event name as a string
* @return event      event attribute
*/
Event* Event_Manager::get_event(string event_name){
     // File pointer

    ifstream fin (STORAGE_FILE_PATH.c_str());

    if (fin.good() == false) {
        fin.close();
        return NULL;
    }


    // Open an existing file
    fin.open(STORAGE_FILE_PATH, ios::in);

    // Read the Data from the file
    // as String Vector
    vector<string> row;
    string line, word, temp,token;
    string delimiter = "^@^";
    size_t pos;

    while (fin >> temp) {

        row.clear();

        // read an entire row and
        // store it in a string variable 'line'

        getline(fin, line);

        pos = 0;

        while ((pos = line.find(delimiter)) != string::npos) {
            token = line.substr(0, pos);
            row.push_back(token);
            line.erase(0, pos + delimiter.length());
        }


        if (row[0].compare(event_name) == 0){
            Event_Factory* factory = new Event_Factory();
            Event* event = factory->create_event(row[0], row[1], stoi(row[2]), stoi(row[3]), row[4], row[5], row[6]);
            fin.close();
            return event;

        }
        if (fin.eof()) {
            fin.close();
            return NULL;
        }

    }
    fin.close();
    return NULL;
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
int Event_Manager::create_event (string eventName, string details, time_t start_time,
    time_t end_time, string access_t, string owner_id, string repeatType){
    Event* event = get_event(eventName);

    if (event != NULL) {
        return -1;
    }
    Event_Factory* factory = new Event_Factory();
    event = factory->create_event(eventName, details, start_time, end_time,
        access_t, owner_id, repeatType);
    string event_db_entry = eventName + "^@^" + details + "^@^" + to_string(start_time) +
        "^@^" + to_string(end_time) + "^@^" + access_t + "^@^" + owner_id + "^@^" + repeatType;

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
 * @return      int                 0 on failure, 1 on success
 */
int Event_Manager::delete_event(string event_name){
    Event* event = get_event(event_name);
    if (event == NULL)
        return 0;
    ifstream file_input(STORAGE_FILE_PATH);
    string line, current_event_name;
    string new_database_string = "";

    size_t pos;
    while(getline(file_input, line)) {
        pos = line.find("^@^");
        current_event_name = line.substr(0,pos);

        if (current_event_name.compare(event_name) != 0) {
            line = line + "\n";
            new_database_string += line;
        }
    }
    file_input.close();
    remove(STORAGE_FILE_PATH.c_str());
    ofstream out(STORAGE_FILE_PATH);
    out << new_database_string;
    out.close();

    return 1;
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
    ifstream event_file;
    event_file.open(STORAGE_FILE_PATH);
    while(getline(event_file, line)){
        // Parse string into componants
        stringstream ss (line);
        while(getline(ss, line, "^@^"))
            parts.push_back(line);
        // if owner_id matches add to collection
        if (parts[5].compare(owner_id) == 0){
            Event_Factory* factory = new Event_Factory();
            Event* newEvent = factory->create_event(parts[0], parts[1], stol(parts[2]), stol(parts[3]),
                                                    parts[4], parts[5], parts[6]);
            output.push_back(*newEvent);
        }
        parts.clear(); // clean up parts for next line
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
    ifstream event_file;
    event_file.open(STORAGE_FILE_PATH);
    while(getline(event_file, line)){
        // Parse string into componants
        stringstream ss (line);
        while(getline(ss, line, "^@^"))
            parts.push_back(line);
        // if access if public add to collection
        if (parts[4].compare("public") == 0){
            Event_Factory* factory = new Event_Factory();
            Event* newEvent = factory->create_event(parts[0], parts[1], stol(parts[2]), stol(parts[3]),
                                                    parts[4], parts[5], parts[6]);
            output.push_back(*newEvent);
        }
        parts.clear(); // clean up parts for next line
    }
    return output;
}

/**
 * @brief       get a text rep for a given event
 *
 * @author      Vladimir Zhurov
 * @date        25/11/2019
 * @param       event          The event
 * @return      txt_rep        A text representation of a given event object
 */
string Event_Manager::event_to_txt(Event event){
    string txt_rep = "";
    txt_rep += event.get_eventName() + "^@^" +
        event.get_details() + "^@^" +
        to_string(event.get_start_time()) + "^@^" +
        to_string(event.get_end_time()) + "^@^" +
        event.get_access_t() + "^@^" +
        event.get_owner_id() + "^@^" +
        event.get_repeat_type();
    return txt_rep;
}
