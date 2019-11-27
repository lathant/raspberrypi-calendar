/* Class for the timetable manager
 * CREATED BY: Vladimir Zhurov
 * LAST EDITED BY: David Truong
 * LAST EDITED: 23/11/2019
 * TODO: IMPLEMENT *WIP* need to adjust for other already made cpp and headers since I had made my own
 */

/* Int = 1 success
 * Int = 0 Failure
 */

#include "timetable_manager.h"
#include "string"

/// initialize begining of file on initial start 
static string STORAGE_FILE_PATH = "./data/timetable/timetables.csv";
Timetable_Manager* Timetable_Manager::instance = NULL;


/**
  * Function that retrieves an instance of a time table manager 
  * If one does not exist already then create 
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
  * Function that calls the factory method to create a new timetable and write to file   
  * If one does exist already do nothing 
  * @param strings for name, access_t and owner_id 
  * @returns 0 on failure, 1 on success
  */
int Timetable_Manager::create_timetable(std::string name, std::string access_t, std::string owner_id){
	Timetable * table = get_personal_tables(owner_id);
	if (table != NULL){
			return 0; 
	}
	else {
		Timetable_Factory* factory = new Timetable_Factory;
		Timetable * new_table = factory->create_timetable(name, access_t, owner_id);
		string user_timetable = timetable_to_txt(timetable);
		ofstream out(STORAGE_FILE_PATH, ios::app);
		out << user_timetable << end1;
		out.close();
		return 1;
	}
}


/**
  * Function that saves timetable to a file or overwrite if needed  
  * If one does not exist already then create 
  * @param Timetable  
  * @returns 0 on failure, 1 on success
  */
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



/**
  * Function that Checks to see if the timetable object's owner_id matches the owner_id 
  * then deletes the object and the data from the file 
  * If one does not exist already do nothing 
  * @param string of tablename 
  * @returns 0 on failure, 1 on success
  */
int Timetable_Manager::delete_timetable(std::string table_name){
	if (table_name = NULL){
		return 0;
	}
	if (table.owner_id = owner_id){
		Timetable * new_table = factory->create_timetable(NULL, NULL, NULL); // NOTE: temp for now till it can be removed
			string user_timetable = timetable_to_txt(Timetable timetable);
			ofstream out(STORAGE_FILE_PATH, ios::app);
			out << user_timetable << end1;
			out.close();
			return 1;
	}
}

// NOTE: a symbol needed to break up events ie: "^"

/**
  * Function that Check to see if the event_info is not already part of the timetable
  * Append the event to the set inside table and update the file
  * If one does not exist already create 
  * @param string of tablename, string of event info 
  * @returns 0 on failure, 1 on success
  */
int Timetable_Manager::append_date(std::string table_name, std::string event_info){
    Timetable * table = get_personal_tables(owner_id);
	if (table_name != NULL){
		table.add_date(event_info); // NOTE: need to find way to sort through the data in a timetable
	    }
	}
}

/**
  * Function that Add a new user to the members of the table if the owner_id matches and if they are not already present
  * If one does exist already do nothing 
  * @param string of tablename, string of member id 
  * @returns 0 on failure, 1 on success, -1 if owner_id match fai
  */
int add_member(std::string tablename, std::string member_id){
	if (tablename = NULL){
	    return -1; 
	}
	if (Timetable::is_member(member_id) = 0){
	   Timetable::add_member(member_id); 
	   return 1;
	}
	return 0;
}

//Remove a user from the members of the table if the owner_id matches and if they are already present
//Return -1 if owner_id match fail
//Return 0 for normal fail
int remove_member(std::string tablename, std::string member_id){
	// check if owner id matches
		// yes then check if user is in members
			// remove the user with table method
		// return error
	// return error                                                              
	if (tablename = NULL){
	    return 0; // doesnt exist
	}
	if (Timetable::is_member(member_id) = 0){
	   Timetable::remove_member(member_id);  // fix 
	   return 1;
	}
	return 0;
}

/* read in line 
while(getline(in_stream, command)){
                stringstream ss (command);
                while(getline(ss, command, '|'))
                    parts.push_back(command);
*/
//Get all tables where owner_id matches
std::set<Timetable> Timetable_Manager::get_personal_tables(std::string owner_id){
	// check if the table with owner id exists
		// if yes go through list of tables
			// if match add to list
		// else error
	// return the list
    
    if (owner_id != NULL){
        while(getline(STORAGE_FILE_PATH, tables)){
                stringstream ss (tables);
                while(getline(ss, tables, ',')){
                    if (getline(ss, tablels) = owner_id){
                        parts.push_back(tables);
                    }
                }
        }
    }
    else {
        // catch error 
    }

}

//Get all tables where owner_id is part of members but not equal to the table's owner_id
std::set<Timetable> Timetable_Manager::get_shared_tables(std::string owner_id){
	// check if the table with owner id exists
		// if yes go through list of tables
			// if match for members and not owner add to list
		// else error
	// return the list
	
    if owner_id != NULL){
        while(getline(STORAGE_FILE_PATH, table)){
            stringstream ss (table);
            while(getline(ss, table, ',')){
                if (getline(ss, tables) = Timetable::is_member(owner_id)){
                    parts.push_back(command);
                }
            }
        }        
    }
    else {
        // catch error  
    }
}

//Get all tables that have access_t equal to public
std::set<Timetable> Timetable_Manager::get_public_tables(){
	// check if the table with owner id exists
		// if yes go through list of tables
			// if match add to list
		// else error
	// return the list
	

    if (table != NULL){
        while(getline(STORAGE_FILE_PATH, table)){
            stringstream ss (table);
            while(getline(ss, table, ',')){
                parts.push_back(table);
            }
            
        }
        
    }
    else {
        // return error 
    }
}

// read in file line, get name and sort to get the line 
//Convert the Timetable object into a string for output to user interface
std::string Timetable_Manager::timetable_to_txt(Timetable timetable){
    
    if (timetable != NULL){
        while(getline(STORAGE_FILE_PATH, table)){
            stringstream ss (table);
            while(getline(ss, table, ',')){
                parts.push_back(table);
            }
        }
    }
}

// Compare time tables; return time table as comparison, read in events for 1 and 2, if 
// event over laps (time), create free events, b is overlap, a is the same as 1, return timetable
// of events 1 + 2 + overlap (dont create events, create strings), OVERLAP

/*Create a timetable that is the comparison of two timetables, events that match are shown,
 *events that do not match are shown but information is hidden
 *events that overlap have sudo event present in overlap section
 *timetable is not stored in file
 */
Timetable* Timetable_Manager::compare_timetables(std::string table1name, std::string table2name){
    
    
    if (timetable != NULL){
        while(getline(STORAGE_FILE_PATH, table1)){
            stringstream ss (table1);
            while(getline(ss, table1, ',')){
                parts.push_back(table1);
            }
        }
    }
}

// errors in control pointer issues can be fixed, some functions not on windows 