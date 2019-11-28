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


Timetable* Timetable_Manager::get_timetable(string table_name){
     // File pointer
    fstream fin;

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

        if (row[0].compare(timetable_name) == 0){
            Timetable_Factory* factory = new Timetable_Factory();
            Timetable* table = factory->create_timetable(row[0], row[1], stoi(row[2]), stoi(row[3]), // adjust 
                    row[4], row[5], row[6]);
            return table;

        }

    return NULL;

    }
}

/**
  * @breif Function that calls the factory method to create a new timetable and write to file   
  * If one does exist already do nothing 
  * @author  David T 
  * @date   27/11/2019
  * @param strings for name, access_t and owner_id 
  * @returns 0 on failure, 1 on success
  */
int create_timetable(string name, string access_t, string owner_id){
    Timetable* time_table = get_timetable(timetable_name);
    if (table != NULL)
        return -1;
    Timetable_Factory* factory = new Timetable_Factory();
    table = factory->create_timetable(timetable_name, access_t, owner_id);
    string table_db_entry = timetable_name + "^@^" + access_t + "^@^" +  owner_id + "^@^";
    ofstream out(STORAGE_FILE_PATH, ios::app);
    out << table_db_entry << endl;
    out.close();
    return 1;
}


/**
  * @breif Function that saves timetable to a file or overwrite if needed  
  * If one does not exist already then create 
  * @author  David T 
  * @date   27/11/2019
  * @param Timetable  
  * @returns 0 on failure, 1 on success
  */
int save_timetable(Timetable table){
    Timetable* time_table = get_timetable(table_name);
    if (time_table == NULL)
        return 0;
    ifstream file_input(STORAGE_FILE_PATH);
    string line, current_timetable_name;
    string new_database_string = "";

    size_t pos;
    while(getline(file_input, line)) {
        pos = line.find("^@^");
        current_event_name = line.substr(0,pos);

        if (current_timetable_name.compare(table_name) != 0) {
            line = line + "\n";
            new_database_string += line;
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
int delete_timetable(string table_name){
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
  * @date   27/11/2019
  * @param string of tablename, string of event info 
  * @returns 0 on failure, 1 on success
  */
int append_date(string table_name, string event_info){ // adjust 
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

        if (current_time_name.compare(table_name) != 0) {
            line = line + "\n";
            new_database_string += line;
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
  * @date   27/11/2019
  * @param string of tablename, string of event info 
  * @returns 0 on failure, 1 on success
  */
int remove_date(string table_name, string event_info){ // adjust
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

        if (current_time_name.compare(table_name) != 0) {
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
  * @breif Function that adds a new user to the members of the table if the owner_id matches and if they are not already present
  * If one does exist already do nothing 
  * @author  David T 
  * @date   27/11/2019
  * @param string of tablename, string of member id 
  * @returns 0 on failure, 1 on success, -1 if owner_id match fail
  */
int add_member(string tablename, string member_id){
    Timetable* time_table = get_timetable(tablename);
    if (time_table = NULL){
	    return -1; 
	}
	if (time_table -> is_member(member_id)){
	   time_table -> add_member(member_id); 
	   return 1;
	}
	return 0;
}

/**
  * @breif Function that removes a user to the members of the table if the owner_id matches and if they are already present
  * If one does exist already do nothing 
  * @author  David T 
  * @date   27/11/2019
  * @param string of member id 
  * @returns 0 on failure, 1 on success, -1 if owner_id match fail
  */
int remove_member(string tablename, string member_id){
	Timetable* time_table = get_timetable(tablename);
	if (time_table = NULL){
	    return 0; 
	}
	if (time_table -> is_member(member_id)){
	   time_table -> remove_member(member_id);
	   return 1;
	}
	else{
	    return 0;
	}    
}

vector<Timetable> Timetable_Manager::get_personal_tables(string owner_id){
    // read file line by line and create event objects feed all event objects where owner matches into set

    // File pointer
    fstream fin;
    vector<Timetable> output;
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
        if (row[5].compare(owner_id) == 0){
            Timetable_Factory* factory = new Timetable_Factory();
            Timetable* new_Table = factory->create_timetable(row[0], row[1], stoi(row[2]));
            output.push_back(*new_Table);
        }
    }
    return output;
}

vector<Timetable> Timetable_Manager::get_shared_tables(string owner_id){
    // read file line by line and create event objects feed all event objects where owner matches into set

    // File pointer
    fstream fin;
    vector<Timetable> output;
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
        if (row[5].compare(owner_id) == 0){
            Timetable_Factory* factory = new Timetable_Factory();
            Timetable* new_Table = factory->create_timetable(row[0], row[1], stoi(row[2]));
            output.push_back(*new_Table);
        }
    }
    return output;
}

vector<Timetable> Timetable_Manager::get_public_tables(){
    // File pointer
    fstream fin;
    vector<Timetable> output;
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
        if (row[6].compare("public") == 0){
            Timetable_Factory* factory = new Timetable_Factory();
            Timetable* new_Table = factory->create_timetable(row[0], row[1], stoi(row[2]));
            output.push_back(*new_Table);
        }
    }
    return output;
}

string timetable_to_txt(Timetable timetable){
    string txt_rep = "";
    txt_rep += timetable.get_name() + "," +
        timetable.get_access_t() + "," +
        timetable.get_owner_id();
    return txt_rep;
}