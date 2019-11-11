/* Class for the timetable manager
 * CREATED BY: Vladimir Zhurov
 * LAST EDITED BY: Vladimir Zhurov
 * LAST EDITED: 05/11/2019
 * TODO: IMPLEMENT
 */

#include "timetable_manager.h"

using namespace std;

static string STORAGE_FILE_PATH = "./data/timetable/timetables.csv";

Timetable_Manager* Timetable_Manager::instance = NULL;

Timetable_Manager* Timetable_Manager::get_instance() {
    if (instance == NULL)
        instance = new Timetable_Manager;
    return instance;
}

/* Int = 1 success
 * Int = 0 Failure
 */


//Calls the factory method and writes to the file a new timetable
int Timetable_Manager::create_timetable(std::string name, std::string access_t, std::string owner_id){

}

//Save the given timetable into file or overwrite exsisting version
int save_timetable(Timetable table){

}

//Checks to see if the owner_id matches the table's owner_id then deletes it from the file
int Timetable_Manager::delete_timetable(std::string name, std::string owner_id){

}

//Checks tto see if the timetable object's owner_id matches the owner_id then deletes the objectt and the data from the file
int Timetable_Manager::delete_timetable(Timetable* table, std::string owner_id){

}

/*Event_info = time_start,time_end,desription(short),event_id
 *Check to see if the event_info is not already part of the timetable
 *Append the event to the set inside table and update the file
 */
int Timetable_Manager::append_date(Timetable table, std::string event_info){

}

//Get all tables where owner_id matches
std::set<Timetable> Timetable_Manager::get_personal_tables(std::string owner_id){

}

//Get all tables where owner_id is part of members butt not equal to the table's owner_id
std::set<Timetable> Timetable_Manager::get_shared_tables(std::string owner_id){

}

//Get all tables that have access_t equal to public
std::set<Timetable> Timetable_Manager::get_public_tables(){

}

//Convert the Timetable object into a string for output to user interface
std::string Timetable_Manager::timetable_to_txt(Timetable timetable){

}

/*Create a timetable that is the comparison of two timetables, events that match are shown,
 *events that do not match are shown but information is hidden
 *events that overlap have sudo event present in overlap section
 *timetable is not stored in file
 */
Timetable* Timetable_Manager::compare_timetables(Timetable table1, Timetable table2){

}
