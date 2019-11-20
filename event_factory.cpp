/* Class for event factory methods
 * CREATED BY: Abarna Srikantharajah
 * LAST EDITED BY: Abarna Srikantharajah
 * LAST EDITED: 19/11/2019
 * TODO:
 */

#include "event_factory.h"

using namespace std;

//implement to store value for factory opperation method
Event_Factory::Event_Factory(){};

Event* Event_Factory::create_event(string eventName) {
    Event* event = new Event(string eventName);
    return event;
}
