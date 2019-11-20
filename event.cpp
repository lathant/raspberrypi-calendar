/* Class for events
 * CREATED BY: Abarna Srikantharajah
 * LAST EDITED BY: Abarna Srikantharajah
 * LAST EDITED: 19/11/2019
 * TODO:
 */

#include "event.h"

using namespace std;

Event::Event(string eventName, string details, time_t time){
    eventName = eventName;
    details = details;
    time = time;
}

void Event::set_eventName(string newEventName){
    name = newEventName;
}

void Event::set_details(string newDetails){
    details = newDetails;
}

void Event::set_time(time_t newTime){
    time = newTime;
}
