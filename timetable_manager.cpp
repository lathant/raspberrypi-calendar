 /**
  * @brief Implementation of timetable manager
  *
  * The implementation for a methods that interact with the timetable storage file
  * @author	Vladimir Zhurov
  * @author	David Truong
  * @author Lathan Thangavadivel
  * @date	30/11/2019
  */

#include "timetable_manager.h"
#include "string"
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <unistd.h>
#include <set>
#include <tuple>
#include <time.h>
#include <algorithm>
//#include <QStandardPaths>

using namespace std;
/// Initialize begining of file on initial start
//static string STORAGE_FILE_PATH = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation).toStdString() + "/timetable.csv";
Timetable_Manager* Timetable_Manager::instance = NULL;
Timetable_Factory* factory;
//Timetable* table = factory->create_timetable(name, access_t, owner_id);

static string STORAGE_FILE_PATH = "";
/**
 * @brief Function that retrieves an instance of a time table manager
 * If one does not exist already then create
 * @author  David T
 * @date   27/11/2019
 * @param No parameter needed
 * @returns instance of time table manager
 */
Timetable_Manager* Timetable_Manager::get_instance() {

    if (instance == NULL){
        instance = new Timetable_Manager;
        factory = new Timetable_Factory();
    }
    return instance;
}

/**
 * @brief Get timetable from file based on name
 *
 * Search the storage file for the timetable with the matching name provided and return a Timetable Object with it's information
 * @author  Lathan Thangavadivel
 * @author  Vladimir Zhurov
 * @date    30/11/2019
 * @param   name                    The name of the timetable
 * @return  table                   The timetable object, Null if not found
 */
Timetable* Timetable_Manager::get_timetable(string name){
    string line;
    vector<string> parts;
    ifstream timetable_file(STORAGE_FILE_PATH);
    if(!timetable_file.is_open())
        return NULL; // Error occoured
    while(getline(timetable_file, line)){
            // parse in the name
            stringstream ss (line);
            getline(ss, line, '&');
            parts.push_back(line);
            // If event_name matches return Event
            if (name.compare(parts[0]) == 0){
                // parse in rest of string
                while(getline(ss, line, '&'))
                    parts.push_back(line);
                set<string> dates,members;
                int position = 4;
                bool control = true;
                // Reads in dates untill "DELIM@DATEEND" is reached
                while(control){
                    if (parts[position].compare("DELIM@DATEEND") == 0){
                        position += 2;
                        break;
                    }
                    else{
                        dates.insert(parts[position]);
                        position++;
                    }
                }
                // Reads in members untill "DELIM@MEMBEREND" is reached
                while(control){
                    if (parts[position].compare("DELIM@MEMBEREND") == 0){
                        break;
                    }
                    else{
                        members.insert(parts[position]);
                        position++;
                    }
                }
                return factory->create_timetable(parts[0], parts[1], parts[2], dates, members);
            }
            parts.clear(); // Clean up parts for next line
        }
        return NULL; // Not found
}


/**
 * @brief Function that calls the factory method to create a new timetable and write to file
 *
 * If one does exist already do nothing
 * @author  David T
 * @author  Lathan Thangavadivel
 * @author  Vladimir Zhurov
 * @date    30/11/2019
 * @param   name                    The timetable's name
 * @param   access_t                The timetable's access permissions
 * @param   owner_id                The timetable's owner's username
 * @returns int                     -1 on duplicate, 0 on failure, and 1 on success
 */
int Timetable_Manager::create_timetable(string name, string access_t, string owner_id){
    Timetable* time_table = get_timetable(name);
    if (time_table != NULL){
        return -1;
    }
    string table_db_entry = name + "&" + access_t + "&" +  owner_id + "&" +"DELIM@DATE&DELIM@DATEEND&DELIM@MEMBER&DELIM@MEMBEREND";
    ofstream timetable_file(STORAGE_FILE_PATH, ios::app);
    if(!timetable_file.is_open())
        return 0; // Error occoured
    timetable_file << table_db_entry << endl;
    timetable_file.close();
    return 1;
}


/**
 * @brief Function that saves timetable to a file or overwrite if needed
 *
 * Saves a timetable object to the timetable file
 * @author  David T
 * @author  Lathan Thangavadivel
 * @author  Vladimir Zhurov
 * @date    30/11/2019
 * @param   Timetable               Timetable to be saved
 * @returns int                     0 on failure, 1 on success
 */
int Timetable_Manager::save_timetable(Timetable table){
    string table_db_entry = timetable_to_txt(table);
    ofstream timetable_file(STORAGE_FILE_PATH, ios::app);
    if(!timetable_file.is_open())
        return 0; // Error occoured
    if (get_timetable(table.get_name()) != NULL)
        delete_timetable(table.get_name());
    timetable_file << table_db_entry << endl;
    timetable_file.close();
    return 1;
}


/**
 * @brief Delete a timetable form the storage file
 *
 * Searches the storage file for a matching timetable and removes it
 * @author  David T
 * @author  Vladimir Zhurov
 * @date    30/11/2019
 * @param   table_name      The name of the table
 * @returns int             0 on failure, 1 on success
 */
int Timetable_Manager::delete_timetable(string table_name){
    Timetable* time_table = get_timetable(table_name);
    if (time_table == NULL)
        return 0;

    string line, name, new_database_string = "";
    size_t length;
    int success = 0;

    ifstream timetable_file(STORAGE_FILE_PATH);
    if(!timetable_file.is_open())
        return success; // Error occoured
    while(getline(timetable_file, line)){
        length = line.find("&"); // Length of timetable_name
        name = line.substr(0, length);
        if(name.compare(table_name) != 0)
            new_database_string += line + "\n"; // Write non matching timetable to string
        else
            success = 1;
    }
    timetable_file.close();
    remove(STORAGE_FILE_PATH.c_str()); // Remove file (deletes matching timetables)
    ofstream out(STORAGE_FILE_PATH);
    out << new_database_string; // Make new file and write all non matching timetables to it
    out.close();
    return success;
}

/**
 * @brief Add a event to a timetable
 *
 * Gets the timetable and then saves it after adding the event
 * @author  David T
 * @author  Lathan Thangavadivel
 * @author  Vladimir Zhurov
 * @date    30/11/2019
 * @param   table_name              The name of the timetable
 * @param   event_info              Text rep of an event
 * @returns int                     0 on failure, and 1 on success
 */
int Timetable_Manager::append_date(string table_name, string event_info){
    Timetable* time_table = get_timetable(table_name);
    if (time_table == NULL)
        return 0;
    if(time_table->add_date(event_info) == 1)
        return save_timetable(*time_table);
    else
        return 0;
}


/**
 * @brief Remove a event to a timetable
 *
 * Gets the timetable and then saves it after removeing the event
 * @author  David T
 * @author  Lathan Thangavadivel
 * @author  Vladimir Zhurov
 * @date    30/11/2019
 * @param   table_name              The name of the timetable
 * @param   event_info              Text rep of an event
 * @returns int                     0 on failure, and 1 on success
 */
int Timetable_Manager::remove_date(string table_name, string event_info){
    Timetable* time_table = get_timetable(table_name);
    if (time_table == NULL)
        return 0;
    if(time_table->remove_date(event_info) == 1)
        return save_timetable(*time_table);
    else
        return 0;
}

/**
 * @brief Add a member to a timetable
 *
 * Gets the timetable and then saves it after adding the member
 * @author  David T
 * @author  Lathan Thangavadivel
 * @author  Vladimir Zhurov
 * @date    30/11/2019
 * @param   table_name              The name of the timetable
 * @param   member_id               The member's username
 * @returns int                     0 on failure, and 1 on success
 */
int Timetable_Manager::add_member(string table_name, string member_id){
    Timetable* time_table = get_timetable(table_name);
    if (time_table == NULL)
        return 0;
    if(time_table->add_member(member_id) == 1)
        return save_timetable(*time_table);
    else
        return 0;
}

/**
 * @brief Remove a member to a timetable
 *
 * Gets the timetable and then saves it after removeing the member
 * @author  David T
 * @author  Lathan Thangavadivel
 * @author  Vladimir Zhurov
 * @date    30/11/2019
 * @param   table_name              The name of the timetable
 * @param   member_id               The member's username
 * @returns int                     0 on failure, and 1 on success
 */
int Timetable_Manager::remove_member(string table_name, string member_id){
    Timetable* time_table = get_timetable(table_name);
    if (time_table == NULL)
        return 0;
    if(time_table->remove_member(member_id) == 1)
        return save_timetable(*time_table);
    else
        return 0;
}

/**
 * @brief get a vector of all a user's personal timetables
 *
 * Scans the storage file for all timetable's that have owner_id's that match
 * @author  Lathan Thangavadivel
 * @author  Vladimir Zhurov
 * @date    30/11/2019
 * @param   owner_id                The owner's username
 * @return  output                  A vector<Timetable>
 */
vector<Timetable> Timetable_Manager::get_personal_tables(string owner_id){
    vector<Timetable> output;
    vector<string> parts;
    string line;

    ifstream timetable_file(STORAGE_FILE_PATH);
    if(!timetable_file.is_open())
        return output; // Error occoured
    while(getline(timetable_file, line)){
        // Parse string into componants
        stringstream ss (line);
        while(getline(ss, line, '&'))
            parts.push_back(line);
        // If owner_id matches add to collection
        if (parts[1].compare(owner_id) == 0){
            Timetable* time_table = get_timetable(parts[0]);
            output.push_back(*time_table);
        }
        parts.clear(); // Clean up parts for next line
    }
    return output;
}

/**
 * @brief get a vector of all a user's shared timetables
 *
 * Scans the storage file for all timetable's that have user as a member
 * @author  Lathan Thangavadivel
 * @author  Vladimir Zhurov
 * @date    30/11/2019
 * @param   owner_id                The user's username
 * @return  output                  A vector<Timetable>
 */
vector<Timetable> Timetable_Manager::get_shared_tables(string owner_id){
    vector<Timetable> output;
    vector<string> parts;
    string line, table_name;
    size_t length, pos;

    ifstream timetable_file(STORAGE_FILE_PATH);
    if(!timetable_file.is_open())
        return output; // Error occoured
    while(getline(timetable_file, line)){
        length = line.find("&"); // Length of timetable_name
        table_name = line.substr(0, length);
        pos = line.find("DELIM@MEMBER");
        line = line.substr(pos); // Truncate line so that it only contains member info
        // Parse member names into parts
        stringstream ss (line);
        while(getline(ss, line, '&'))
            parts.push_back(line);
        // Check for matches
        for(unsigned int i = 0; i < parts.size(); i++)
            if(parts[i].compare(owner_id) == 0){
                //owner_id matched add to collection
                Timetable* time_table = get_timetable(table_name);
                output.push_back(*time_table);
            }
        parts.clear(); // Clean up parts for next line
    }
    return output;
}

 /**
  * @brief get a vector of all public timetables
  *
  * Scans the storage file for all timetable's that are public
  * @author  Lathan Thangavadivel
  * @author  Vladimir Zhurov
  * @date    30/11/2019
  * @param   owner_id                The user's username
  * @return  output                  A vector<Timetable>
  */
vector<Timetable> Timetable_Manager::get_public_tables(){
    vector<Timetable> output;
    vector<string> parts;
    string line;

    ifstream timetable_file(STORAGE_FILE_PATH);
    if(!timetable_file.is_open())
        return output; // Error occoured
    while(getline(timetable_file, line)){
        // Parse string into componants
        stringstream ss (line);
        while(getline(ss, line, '&'))
            parts.push_back(line);
        // If owner_id matches add to collection
        if (parts[2].compare("public") == 0){
            Timetable* time_table = get_timetable(parts[0]);
            output.push_back(*time_table);
        }
        parts.clear(); // Clean up parts for next line
    }
    return output;
}

/**
 * @brief convert timetable to string
 *
 * Create a string representation of a timetable object
 * @author  Lathan  Thangavadivel
 * @author  Vladimir Zhurov
 * @param   time_table              The timetable to be converted
 * @return  txt_rep                 A text representation of the timetable
 */
string Timetable_Manager::timetable_to_txt(Timetable timetable){
    string txt_rep = "";
    txt_rep += timetable.get_name() + "&" +
        timetable.get_access_t() + "&" +
        timetable.get_owner_id() +"&DELIM@DATE&";

    // Add all dates to string rep
    set<string> dates = timetable.get_dates();
    for(set<string>::iterator it = dates.begin(); it != dates.end(); it++)
        txt_rep += *it +"&";
    txt_rep += "DELIM@DATEEND&DELIM@MEMBER&";

    // Add all members to string rep
    set<string> members = timetable.get_members();
    for(set<string>::iterator it = members.begin(); it != members.end(); it++)
        txt_rep += *it +"&";
    txt_rep += "DELIM@MEMBEREND";

    return txt_rep;
}

/**
 * @brief comparison for tuple<string,time_t,time_t> sort function
 * @author  Vladimir Zhurov
 * @date    30/11/2019
 * @param   a               first tuple<string,time_t,time_t>
 * @param   b               second tuple<string,time_t,time_t>
 * @return  bool            true if difftime(get<1>(a), get<1>(b)) < 0
 */
bool tuple_sort(tuple<string,time_t,time_t> a, tuple<string,time_t,time_t> b){
    return (difftime(get<1>(a), get<1>(b)) < 0);
}

/**
 * @brief       takes two tables combines and returns the string output of the
 *              combined table while highlighting conflicts
 *
 * @author      Lathan Thangavadivel
 * @date        25/11/2019
 * @param       table1              name of the first table
 * @param       table2              name of second table
 * @return      string              string output of the combined tables
 */
string Timetable_Manager::compare_timetables(string table_name1, string table_name2){
    Timetable* table1 = get_timetable(table_name1);
    Timetable* table2 = get_timetable(table_name2);

    if (table1 == NULL || table2 == NULL)
        return "ERROR";

    set<string> dates1 = table1->get_dates();
    set<string> dates2 = table2->get_dates();
    tuple<string,time_t,time_t> temp;
    vector<tuple<string,time_t,time_t>> final;
    time_t start_time, end_time;
    string temp_s;
    // Get all event times for table1
    int index = 0;
    for(set<string>::iterator it = dates1.begin(); it != dates1.end(); it++){
        stringstream ss (*it);
        getline(ss, temp_s, '^');
        getline(ss, temp_s, '^');
        getline(ss, temp_s, '^');
        start_time = stol(temp_s);
        getline(ss, temp_s, '^');
        end_time = stol(temp_s);
        temp = make_tuple(index++, start_time, end_time);
        final.push_back(temp);
    }

    // Get all event times for table2
    index = -1; // index for table2 events are negitive actual index = |+1|
    for(set<string>::iterator it = dates2.begin(); it != dates2.end(); it++){
        stringstream ss (*it);
        getline(ss, temp_s, '^');
        getline(ss, temp_s, '^');
        getline(ss, temp_s, '^');
        start_time = stol(temp_s);
        getline(ss, temp_s, '^');
        end_time = stol(temp_s);
        temp = make_tuple(index--, start_time, end_time);
        final.push_back(temp);
    }
    sort(final.begin(), final.end(), tuple_sort);
    // final contains all event tuples

    //search for conflicts
    finalitr = final.begin();
    finalitr +=1;
    time_t timediff;
    //if statement for if there are less than 2 items in final
    if (final.size()>1){
        while ( finalitr != final.end()){
            timediff = difftime(get<2>(*(finalitr - 1)),get<1>(*finalitr));
            if (timediff > 0){
                get<2>(*(finalitr - 1)) -= timediff;
                get<1>(*finalitr) += timediff;
                temp = make_tuple("CONFLICT",get<2>(*(finalitr - 1)),get<1>(*finalitr));
                final.insert(finalitr,temp);
            }
            finalitr+=1;
        }
    }


    //print out the comparison Timetable

    string finaloutput ="";
    finalitr = final.begin();
    string eventDetail,startDetails,endDetails,prevDelim, postDelim;
    while (finalitr != final.end()){
        eventDetail = get<0>(*finalitr);
        startDetails = to_string(get<1>(*finalitr));
        endDetails = to_string(get<2>(*finalitr));

        if (eventDetail.compare("CONFLICT") == 0){
            finaloutput+= eventDetail + "DELIM@START" + startDetails + "^" + endDetails + "DELIM@END" + "\n";
        }
        else{
            pos_start = eventDetail.find("DELIM@START");
            pos_end = eventDetail.find("DELIM@END");

            prevDelim = eventDetail.substr(0,pos_start + 11);
            postDelim = eventDetail.substr(pos_end,eventDetail.length());

            finaloutput += prevDelim + startDetails + "^" + endDetails + postDelim +"\n";
        }
        finalitr+= 1;
    }
    return finaloutput;

}
