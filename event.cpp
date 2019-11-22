/* Class for events
 * CREATED BY: Abarna Srikantharajah
 * LAST EDITED BY: Abarna Srikantharajah
 * LAST EDITED: 19/11/2019
 * TODO:
 */
#include "event.h"

using namespace std;

Event::Event(string in_eventName, string in_details, time_t in_start_time,time_t in_end_time,string in_access_t, string in_owner_id, string in_repeatType){
    eventName = in_eventName;
    details = in_details;
    start_time = in_start_time;
    end_time = in_end_time;
    access_t = in_access_t;
    owner_id = in_owner_id;
    repeatType = in_repeatType;
}

void Event::set_eventName(string newEventName){
    eventName = newEventName;
}

void Event::set_details(string newDetails){
    details = newDetails;
}

void Event::set_start_time(time_t newStartTime){
    start_time = newStartTime;
}

void Event::set_end_time(time_t newEndTime){
    end_time = newEndTime;
}

void Event::set_access_t (string newAccess){
    access_t = newAccess;
}

void Event::set_owner_id(string newOwner){
    owner_id = newOwner;
}

void Event::set_repeat_type(string newRepeatType){
    repeatType = newRepeatType;
}
