/* Class for the timetable manager
 * CREATED BY: Vladimir Zhurov
 * LAST EDITED BY: David Truong
 * LAST EDITED: 23/11/2019
 * TODO: IMPLEMENT *WIP* need to adjust for other already made cpp and headers since I had made my own
 */

#include "timetable_manager.h"
#include "string"

using namespace std;

static string STORAGE_FILE_PATH = "./data/timetable/timetables.csv";

Timetable_Manager* Timetable_Manager::instance = NULL;

// Create instance of timetable manager
Timetable_Manager* Timetable_Manager::get_instance() {
    if (instance == NULL)
        instance = new Timetable_Manager;
    return instance;
}

/* Int = 1 success
 * Int = 0 Failure
 */


//Calls the factory method and writes to the file a new timetable
int Timetable_Manager::create_timetable(std::string in_name, std::string in_access_t, std::string in_owner_id){
	Timetable * table = get_personal_tables(in_owner_id);
	if (table != NULL){
			return 0; // already exists
	}
	else {
		Timetable_Factory* factory = new Timetable_Factory;
		Timetable * new_table = factory->create_timetable(in_name, in_access_t, in_owner_id);
		string user_timetable = timetable_to_txt(Timetable timetable);
		ofstream out(STORAGE_FILE_PATH, ios::app);
		out << user_timetable << end1;
		out.close();
		return 1;
	}
}

//Save the given timetable into file or overwrite exsisting version
int save_timetable(Timetable table){
	if (table != NULL){
		user_timetable = timetable_to_txt(table);
		ofstream out(STORAGE_FILE_PATH, ios::app);
		out << user_timetable << end1;
		out.close();
		return 1;
	}
	else{
		return 0;
	}
}

//Checks to see if the owner_id matches the table's owner_id then deletes it from the file
int Timetable_Manager::delete_timetable(std::string table_name){ // fix with new table name
/* if owner_id and table owner_id match then,
 * 		remove the time table from file
 *	else then return error
 */
	Timetable * table = get_personal_tables(table_name);
	if (table = NULL){
		return 0;
	}
	if (table.owner_id = owner_id){
		Timetable * new_table = factory->create_timetable(NULL, NULL, NULL); // temp for now till it can be removed
			string user_timetable = timetable_to_txt(Timetable timetable);
			ofstream out(STORAGE_FILE_PATH, ios::app);
			out << user_timetable << end1;
			out.close();
			return 1;
	}
}

//Checks to see if the timetable object's owner_id matches the owner_id then deletes the object and the data from the file
int Timetable_Manager::delete_timetable(std::string table_name){
/* if owner_id matches owner id given
 * 		then remove the timetable and data
 * else return error
 */
	if (table = NULL){
		return 0;
	}
	if (table.owner_id = owner_id){
		Timetable * new_table = factory->create_timetable(NULL, NULL, NULL); // temp for now till it can be removed
			string user_timetable = timetable_to_txt(Timetable timetable);
			ofstream out(STORAGE_FILE_PATH, ios::app);
			out << user_timetable << end1;
			out.close();
			return 1;
	}
}

/*Event_info = time_start,time_end,desription(short),event_id
 *Check to see if the event_info is not already part of the timetable
 *Append the event to the set inside table and update the file
 */
int Timetable_Manager::append_date(std::string table_name, std::string event_info){ // come back to this
	// check if the table exists
		// then see if the info is in table
			// if yes then do not add_member
		// append the data for the table

	if (table != NULL){
	    if ( = 0){ // if in table TBD
		table.add_date(event_info); // need to find way to sort through the data in a timetable
	    }
	}
}

//Add a new user to the members of the table if the owner_id matches and if they are not already present
//Return -1 if owner_id match fail
//Retturn 0 for normal fail
int add_member(std::string tablename, std::string member_id){
	// check if owner id matches
		// yes then check if user is not in members
			// add the user with table method
		// return error
	// return error

	if (table = NULL){
	    return 0; // doesnt exist
	}
	if (table.is_member(member_id) = 0){
	   add_member(member_id);
	   return 1;
	}
	return 0;
}

//Remove a user from the members of the table if the owner_id matches and if they are already present
//Return -1 if owner_id match fail
//Retturn 0 for normal fail
int remove_member(std::string tablename, std::string member_id){
	// check if owner id matches
		// yes then check if user is in members
			// remove the user with table method
		// return error
	// return error
	if (table = NULL){
	    return 0; // doesnt exist
	}
	if (table.is_member(member_id) = 0){
	   remove_member(member_id);
	   return 1;
	}
	return 0;
}

//Get all tables where owner_id matches
std::set<Timetable> Timetable_Manager::get_personal_tables(std::string owner_id){
	// check if the table with owner id exists
		// if yes go through list of tables
			// if match add to list
		// else error
	// return the list


}

//Get all tables where owner_id is part of members but not equal to the table's owner_id
std::set<Timetable> Timetable_Manager::get_shared_tables(std::string owner_id){
	// check if the table with owner id exists
		// if yes go through list of tables
			// if match for members and not owner add to list
		// else error
	// return the list
}

//Get all tables that have access_t equal to public
std::set<Timetable> Timetable_Manager::get_public_tables(){
	// check if the table with owner id exists
		// if yes go through list of tables
			// if match add to list
		// else error
	// return the list
}

//Convert the Timetable object into a string for output to user interface
std::string Timetable_Manager::timetable_to_txt(Timetable timetable){

}

/*Create a timetable that is the comparison of two timetables, events that match are shown,
 *events that do not match are shown but information is hidden
 *events that overlap have sudo event present in overlap section
 *timetable is not stored in file
 */
string Timetable_Manager::compare_timetables(std::string table1name, std::string table2name){

}
