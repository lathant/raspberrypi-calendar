/* Class for the timetable manager
 * CREATED BY: Vladimir Zhurov
 * LAST EDITED BY: David Truong
 * LAST EDITED: 27/11/2019
 * TODO: IMPLEMENT *WIP* Debug
 * @breif Class that changes the timetables in and out of storage
 * @author
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

using namespace std;
/// Initialize begining of file on initial start
static std::string STORAGE_FILE_PATH = "./data/timetable/timetables.csv";
Timetable_Manager* Timetable_Manager::instance = NULL;


/**
 * @breif Function that retrieves an instance of a time table manager
 * If one does not exist already then create
 * @author  David T
 * @date   27/11/2019
 * @param No parameter needed
 * @returns instance of time table manager
 */
Timetable_Manager* Timetable_Manager::get_instance() {

    if (instance == NULL){
        instance = new Timetable_Manager;
    }
    return instance;
}

/**
 * @brief Get timetable from file based on name
 *
 * Search the storage file for the timetable with the matching name provided and return a Timetable Object with it's information
 * @author  Lathan Thangavadivel
 * @param   name                    The name of the timetable
 * @return  table                   The timetable object, Null if not found
 */
Timetable* Timetable_Manager::get_timetable(string name){
    ifstream file_input(STORAGE_FILE_PATH);
    string line, current_timetable_name,checktoken,inname,inaccess,inowner,datestr,memberstr;
    set<string> indate,inmem;
    Timetable* table;
    size_t pos,posEnd;
    while(getline(file_input, line)){
        pos = line.find("^@^");
        current_timetable_name = line.substr(0,pos);
        if (current_timetable_name.compare(name)==0){

            inname = line.substr(0, pos);
            line.erase(0, pos + 3);

            pos = line.find("^@^");
            inaccess = line.substr(0, pos);
            line.erase(0, pos + 3);

            pos = line.find("^@^");
            inowner = line.substr(0, pos);
            line.erase(0, pos + 3);

            pos = line.find("DELIM@DATE");
            posEnd = line.find("DELIM@DATEEND");
            datestr = line.substr(pos + 10, posEnd);
            stringstream scan(datestr);
            while (getline(scan,checktoken,',')){
                indate.insert(checktoken);
            }

            pos = line.find("DELIM@MEMBER");
            posEnd = line.find("DELIM@MEMBEREND");
            datestr = line.substr(pos + 12, posEnd);
            stringstream scan1(memberstr);
            while (getline(scan1,checktoken,',')){
                inmem.insert(checktoken);
            }
            table = new Timetable(inname,inaccess,inowner,inmem,indate);
            file_input.close();
            return table;
        }
    }
    file_input.close();
    return NULL;
}


/**
 * @breif Function that calls the factory method to create a new timetable and write to file
 * If one does exist already do nothing
 * @author  David T
 * @author  Lathan Thangavadivel
 * @author  Vladimir Zhurov
 * @date   28/11/2019
 * @param strings for name, access_t and owner_id
 * @returns 0 on failure, 1 on success
 */
int Timetable_Manager::create_timetable(string name, string access_t, string owner_id){
    Timetable* time_table = get_timetable(name);
    if (time_table != NULL){
        return -1;
    }
    else{
    /* Unused
    Timetable_Factory* factory = new Timetable_Factory();
    Timetable* table = factory->create_timetable(name, access_t, owner_id);
    */
    string table_db_entry = name + "^@^" + access_t + "^@^" +  owner_id + "^@^" +"DELIM@DATE"+ "DELIM@DATEEND"+ "DELIM@MEMBER" + "DELIM@MEMBEREND";
    ofstream out(STORAGE_FILE_PATH, ios::app);
    out << table_db_entry << endl;
    out.close();
    return 1;
    }
}


/**
 * @breif Function that saves timetable to a file or overwrite if needed
 * If one does not exist already then create
 * @author  David T
 * @author  Lathan Thangavadivel
 * @date   27/11/2019
 * @param Timetable
 * @returns 0 on failure, 1 on success
 */
int Timetable_Manager::save_timetable(Timetable table){
    Timetable* time_table= get_timetable(table.get_name());
    ifstream file_input(STORAGE_FILE_PATH);
    string line, current_timetable_name,token,current_event_name;
    string new_database_string = "";
    if (time_table == NULL){
        new_database_string += table.get_name() + "^@^"+ table.get_access_t() + "^@^"+ table.get_owner_id()
                                + "^@^" +"DELIM@DATE"+ "DELIM@DATEEND"+ "DELIM@MEMBER" + "DELIM@MEMBEREND";
    }

    else{

        size_t pos, posEnd;
        while(getline(file_input, line)) {
            new_database_string = "";
            pos = line.find("^@^");
            current_event_name = line.substr(0,pos);

            if (current_timetable_name.compare(table.get_name()) != 0) {
                line = line + "\n";
                new_database_string += line;
            }
            else{
                pos = line.find("DELIM@DATE");
                posEnd = line.find ("DELIM@DATEEND");
                token = line.substr(pos, posEnd + 13);
                new_database_string += table.get_name() + "^@^"+ table.get_access_t() + "^@^"+ table.get_owner_id() + token;

                pos = line.find("DELIM@MEMBER");
                posEnd = line.find("DELIM@MEMBEREND");

                token = line.substr(pos, posEnd + 15);
                new_database_string += token;
            }
        }
    }
    file_input.close();
    ofstream out(STORAGE_FILE_PATH);
    out << new_database_string;
    out.close();

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
            token += "," + event_info;
            if (posEnd - (pos + 10) != 0){
                token += ",";
            }
            newline = line.substr(0,pos + 10) + token + line.substr(pos + 10, line.length());
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
    txt_rep += timetable.get_name() + "," +
        timetable.get_access_t() + "," +
        timetable.get_owner_id() +",DELIM@DATE,";

    // Add all dates to string rep
    set<string> dates = timetable.get_dates();
    for(set<string>::iterator it = dates.begin(); it != dates.end(); it++)
        txt_rep += *it +",";
    txt_rep += "DELIM@DATEEND,DELIM@MEMBER,";

    // Add all members to string rep
    set<string> members = timetable.get_members();
    for(set<string>::iterator it = members.begin(); it != members.end(); it++)
        txt_rep += *it +",";
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
