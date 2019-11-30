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
 * @breif Function that saves timetable to a file or overwrite if needed
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
 * @breif Function that checks to see if the timetable object's owner_id matches the owner_id
 * then deletes the object and the data from the file
 * If one does not exist already do nothing
 * @author  David T
 * @date   27/11/2019
 * @param string of tablename
 * @returns 0 on failure, 1 on success
 */
int Timetable_Manager::delete_timetable(string table_name){
    Timetable* time_table = get_timetable(table_name);
    if (time_table == NULL)
        return 0;
    ifstream file_input(STORAGE_FILE_PATH);
    string line, current_timetable_name;
    string new_database_string = "";

    size_t pos;
    while(getline(file_input, line)) {
        pos = line.find("^@^");
        current_timetable_name = line.substr(0,pos);

        if (current_timetable_name.compare(table_name) != 0) {
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
 * @breif Function that checks to see if the event_info is not already part of the timetable
 * Append the event to the set inside table and update the file
 * If one does not exist already create
 * @author  David T
 * @author  Lathan Thangavadivel
 * @date   27/11/2019
 * @param string of tablename, string of event info
 * @returns 0 on failure, 1 on success
 */
int Timetable_Manager::append_date(string table_name, string event_info){
    Timetable* time_table = get_timetable(table_name);
    if (time_table == NULL){return 0;}
    ifstream file_input(STORAGE_FILE_PATH);
    string line, current_timetable_name,newline;
    string new_database_string = "";
    string token = "";

    size_t pos,posEnd;
    while(getline(file_input, line)) {
        pos = line.find("^@^");
        current_timetable_name = line.substr(0,pos);

        if (current_timetable_name.compare(table_name) != 0) {
            line = line + "\n";
            new_database_string += line;
        }

        else{
            pos = line.find("DELIM@DATE");
            posEnd = line.find ("DELIM@DATEEND");
            token = line.substr(pos + 10, posEnd);
            if (posEnd - (pos + 10) != 0){
                token += ",";
            }
            token += "," + event_info;
            newline = line.substr(0,pos + 10) + token + line.substr(pos + 10, line.length()) + "\n";
            new_database_string += newline;
        }
    }
    file_input.close();
    ofstream out(STORAGE_FILE_PATH);
    out << new_database_string;
    out.close();

    return 1;
}


/**
  * @breif Function that checks to see if the event_info is not already part of the timetable
  * Append the event to the set inside table and update the file
  * If one does not exist already create
  * @author  David T
  * @author  Lathan Thangavadivel
  * @date   27/11/2019
  * @param string of tablename, string of event info
  * @returns 0 on failure, 1 on success
  */
int Timetable_Manager::remove_date(string table_name, string event_info){ // adjust
    Timetable* time_table = get_timetable(table_name);
    if (time_table == NULL){return 0;}
    ifstream file_input(STORAGE_FILE_PATH);
    string line, current_timetable_name,checktoken,token;
    string new_database_string = "";
    string finalDates = "";

    size_t pos,posEnd;
    while(getline(file_input, line)) {
        pos = line.find("^@^");
        current_timetable_name = line.substr(0,pos);

        if (current_timetable_name.compare(table_name) != 0) {
            line = line + "\n";
            new_database_string += line;
        }

        else{
            pos = line.find("DELIM@DATE");
            posEnd = line.find ("DELIM@DATEEND");
            token = line.substr(pos + 10, posEnd);
            stringstream edit(token);
            while(getline(edit,checktoken,',')){
                if (checktoken.compare(event_info) != 0){
                    if(finalDates.length() != 0){
                        finalDates += ",";
                    }
                    finalDates += checktoken;
                }
            }
            string newline = line.substr(0,pos + 10) + finalDates + line.substr(posEnd, line.length());
            new_database_string += newline;
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
  * @breif Function that adds a new user to the members of the table if the owner_id matches and if they are not already present
  * If one does exist already do nothing
  * @author  David T
  * @author  Lathan Thangavadivel
  * @date   27/11/2019
  * @param string of tablename, string of member id
  * @returns 0 on failure, 1 on success, -1 if owner_id match fail
  */
int Timetable_Manager::add_member(string tablename, string member_id){
    Timetable* time_table = get_timetable(tablename);
    if (time_table == NULL){
        return 0;
    }
    else{
        ifstream file_input(STORAGE_FILE_PATH);
        string line, current_timetable_name,finalMems,checktoken;
        string new_database_string = "";
        string token = "";

        size_t pos,posEnd;
        while(getline(file_input, line)) {
        pos = line.find("^@^");
        current_timetable_name = line.substr(0,pos);

        if (current_timetable_name.compare(tablename) != 0) {
            line = line + "\n";
            new_database_string += line;
        }

        else{
            pos = line.find("DELIM@MEMBER");
            posEnd = line.find ("DELIM@MEMBEREND");
            token = line.substr(pos + 12, posEnd);
            stringstream edit(token);
            while(getline(edit,checktoken,',')){
                if (checktoken.compare(member_id) != 0){
                    if(finalMems.length() != 0){
                        finalMems += ",";
                    }
                    finalMems += checktoken;
                }
                else{return -1;}
            }
            string newline = line.substr(0,pos + 12) + finalMems + line.substr(posEnd, line.length());
            new_database_string += newline;
        }
    }
    file_input.close();
    remove(STORAGE_FILE_PATH.c_str());
    ofstream out(STORAGE_FILE_PATH);
    out << new_database_string;
    out.close();

    return 1;
    }
}

/**
  * @breif Function that removes a user to the members of the table if the owner_id matches and if they are already present
  * If one does exist already do nothing
  * @author  David T
  * @author  Lathan Thangavadivel
  * @date   27/11/2019
  * @param string of member id
  * @returns 0 on failure, 1 on success, -1 if owner_id match fail
  */
int Timetable_Manager::remove_member(string tablename, string member_id){
    Timetable* time_table = get_timetable(tablename);
    if (time_table == NULL){return 0;}
    ifstream file_input(STORAGE_FILE_PATH);
    string line, current_timetable_name,checktoken,token;
    string new_database_string = "";
    string finalMems = "";
    bool memExists =false;

    size_t pos,posEnd;
    while(getline(file_input, line)) {
        pos = line.find("^@^");
        current_timetable_name = line.substr(0,pos);

        if (current_timetable_name.compare(tablename) != 0) {
            line = line + "\n";
            new_database_string += line;
        }

        else{
            pos = line.find("DELIM@MEMBER");
            posEnd = line.find ("DELIM@MEMBEREND");
            token = line.substr(pos + 12, posEnd);
            stringstream edit(token);
            while(getline(edit,checktoken,',')){
                if (checktoken.compare(member_id) != 0){
                    if(finalMems.length() != 0){
                        finalMems += ",";
                    }
                    finalMems += checktoken;
                }
                else{memExists = true;}
            }

            string newline = line.substr(0,pos + 12) + finalMems + line.substr(posEnd, line.length());
            new_database_string += newline;
        }
        if (!memExists) {return -1;}
    }
    file_input.close();
    remove(STORAGE_FILE_PATH.c_str());
    ofstream out(STORAGE_FILE_PATH);
    out << new_database_string;
    out.close();

    return 1;
}

/**
 * @brief get a vector of all a user's personal timetables
 *
 * Scans the storage file for all timetable's that have owner_id's that match
 * @author  Lathan Thangavadivel
 * @param   owner_id                The owner's username
 * @return  output                  A vector<Timetable>
 */
vector<Timetable> Timetable_Manager::get_personal_tables(string owner_id){
    ifstream file_input(STORAGE_FILE_PATH);
    string line, current_timetable_name,checktoken,inname,inaccess,inowner;
    size_t pos;
    vector<Timetable> output;
    Timetable* table;
    while(getline(file_input, line)){
        pos = line.find("^@^");

        inname = line.substr(0, pos);
        line.erase(0, pos + 3);

        pos = line.find("^@^");
        inaccess = line.substr(0, pos);
        line.erase(0, pos + 3);

        pos = line.find("^@^");
        inowner = line.substr(0, pos);
        line.erase(0, pos + 3);

        if (inowner.compare(owner_id)==0){
            table = get_timetable(inname);
            output.push_back(*table);
        }
    }
    return output;
}

/**
 * @brief get a vector of all a user's shared timetables
 *
 * Scans the storage file for all timetable's that have user as a member
 * @author  Lathan Thangavadivel
 * @param   owner_id                The user's username
 * @return  output                  A vector<Timetable>
 */
vector<Timetable> Timetable_Manager::get_shared_tables(string owner_id){
    ifstream file_input(STORAGE_FILE_PATH);
    string line, current_timetable_name,checktoken,inname, memline;
    size_t pos, posEnd;
    vector<string> row;
    vector<Timetable> output;
    Timetable* table;
    while(getline(file_input, line)){
        pos = line.find("^@^");
        inname = line.substr(0, pos);

        pos = line.find("DELIM@MEMBER");
        posEnd = line.find("DELIM@MEMBEREND");

        memline = line.substr(pos + 12,posEnd);

        stringstream scan(memline);

        while(getline(scan,checktoken,',')){
            if (checktoken.compare(owner_id)){
                table = get_timetable(inname);
                output.push_back(*table);
                break;
            }
        }
    }
    return output;
}

/**
 * @brief get a vector of all public timetables
 *
 * Scans the storage file for all timetable's that are public
 * @author  Lathan Thangavadivel
 * @return  output                  A vector<Timetable>
 */
vector<Timetable> Timetable_Manager::get_public_tables(){

    ifstream file_input(STORAGE_FILE_PATH);
    string line, current_timetable_name,checktoken,inname,inaccess;
    size_t pos;
    vector<Timetable> output;
    Timetable* table;
    while(getline(file_input, line)){
        pos = line.find("^@^");

        inname = line.substr(0, pos);
        line.erase(0, pos + 3);

        pos = line.find("^@^");
        inaccess = line.substr(0, pos);
        line.erase(0, pos + 3);

        if (inaccess.compare("public")==0){
            table = get_timetable(inname);
            output.push_back(*table);
        }
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
 * @brief       takes two tables combines and returns the string output of the
 *              combined table while highlighting conflicts
 *
 * @author      Lathan Thangavadivel
 * @date        25/11/2019
 * @param       table1              name of the first table
 * @param       table2              name of second table
 * @return      string              string output of the combined tables
 */
string Timetable_Manager::compare_timetables(string table1, string table2){
    Timetable* firstTable = get_timetable(table1);
    Timetable* secondTable = get_timetable(table2);

    if (firstTable ==NULL || secondTable ==NULL){
        string error = "ERROR";
        return error;
    }

    set<string> firstDates = firstTable->get_dates();
    set<string> secondDates = secondTable->get_dates();
    string times,timetoken;
    time_t starttime,endtime;

    set<string>::iterator firstitr;
    set<string>::iterator seconditr;
    vector<tuple<string,time_t,time_t>>::iterator finalitr;
    vector<tuple<string,time_t,time_t>> final;
    tuple<string,time_t,time_t> temp;
    size_t pos_start, pos_end;
    int fIndex,fIndexPrev,fIndexNext;
    bool inserted=false;

    //first table
    for (firstitr = firstDates.begin(); firstitr != firstDates.end();firstitr++){
        pos_start = firstitr->find("DELIM@START");
        pos_end = firstitr->find("DELIM@END");
        times = firstitr->substr(pos_start + 11, pos_end);

        stringstream s(times);

        getline(s,timetoken,',');
        starttime = stol(timetoken);

        getline (s,timetoken,',');
        endtime = stol(timetoken);

        temp = make_tuple(*firstitr,starttime,endtime);

        //insert into values from first table final vector in a ordered manner
        if (final.empty()){
            final.push_back(temp);
        }

        else{
            fIndex = 0;
            while (!inserted && (fIndex < final.size())){
                if (difftime(get<1>(final[fIndex]),starttime) < 0){
                    fIndex += 1;
                }

                else{
                    finalitr = final.begin() + fIndex;
                    final.insert(finalitr,temp);
                    inserted = true;
                }

            }
            if (!inserted){
                final.push_back(temp);
            }
        }

    }

    //second table
    inserted = false;
     for (seconditr = secondDates.begin(); seconditr != secondDates.end();seconditr++){
        pos_start = seconditr->find("DELIM@START");
        pos_end = seconditr->find("DELIM@END");
        times = seconditr->substr(pos_start + 11, pos_end);

        stringstream s(times);

        getline(s,timetoken,',');
        starttime = stol(timetoken);

        getline (s,timetoken,',');
        endtime = stol(timetoken);

        temp = make_tuple(*firstitr,starttime,endtime);

        //insert into final vector in a ordered manner
        if (final.empty()){
            final.push_back(temp);
        }

        else{
            fIndex = 0;

            while (!inserted && (fIndex < final.size())){
                if (difftime(get<1>(final[fIndex]),starttime) < 0){
                    fIndex += 1;
                }

                else{
                    finalitr = final.begin() + fIndex;
                    final.insert(finalitr,temp);
                    inserted = true;
                }

            }
            if (!inserted){
                final.push_back(temp);
            }
        }

    }


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
            finaloutput+= eventDetail + "DELIM@START" + startDetails + "," + endDetails + "DELIM@END" + "\n";
        }
        else{
            pos_start = eventDetail.find("DELIM@START");
            pos_end = eventDetail.find("DELIM@END");

            prevDelim = eventDetail.substr(0,pos_start + 11);
            postDelim = eventDetail.substr(pos_end,eventDetail.length());

            finaloutput += prevDelim + startDetails + "," + endDetails + postDelim +"\n";
        }
        finalitr+= 1;
    }
    return finaloutput;

}
