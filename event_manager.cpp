/**
 * @brief      Class for the event manager
 * @author     Vladimir Zhurov
 * @date       25/11/2019
 */

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
 * @brief       create a new event
 *
 * @author      Vladimir Zhurov
 * @date        25/11/2019
 * @param
 * @param
 * @return
 */
int Event_Manager::create_event(string eventName, string details,
    time_t start_time, time_t end_time,string access_t, string owner_id,
    string repeatType){

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
