/* Class for event factory methods
 * CREATED BY: Abarna Srikantharajah
 * LAST EDITED BY: Abarna Srikantharajah
 * LAST EDITED: 19/11/2019
 * TODO:
 */

#include "event_factory.h"

using namespace std;

//implement factory method
Event_Factory::Event_Factory(){};

Event* Event_Factory::create_event(string eventName, string details, time_t start_time,time_t end_time,string access_t, string owner_id, string repeatType) {
    Event* event = new Event(eventName, details, start_time, end_time, access_t, owner_id, repeatType);
    return event;
}
