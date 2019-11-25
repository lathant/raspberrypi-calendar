/* Class for events
 * CREATED BY: Abarna Srikantharajah
 * LAST EDITED BY: Abarna Srikantharajah
 * LAST EDITED: 19/11/2019
 * TODO:
 */
#include "event.h"

using namespace std;

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
    repeat_type = newRepeatType;
}
