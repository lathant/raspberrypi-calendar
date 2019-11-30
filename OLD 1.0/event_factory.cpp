/**
 * Class that generates events
 * CREATED BY: Abarna Srikantharajah
 * LAST EDITED BY: Abarna Srikantharajah
 * LAST EDITED: 19/11/2019
 * @brief creates an instance of an event using the factory method
 *
 * @author  Abarna Srikantharajah
 * @date   19/11/2019
 */

#include "event_factory.h"

using namespace std;

/**
 * @brief constructor for Event_Factory
 *
 * @author  Abarna Srikantharajah
 * @date   19/11/2019
 */
Event_Factory::Event_Factory(){};

/**
 * @brief Create a new Event
 *
 * Call the Event object constructor
 * @author  Abarna Srikantharajah
 * @date    19/11/2019
 * @param   eventName       The event name
 * @param   details         The event details
 * @param   start_time      The event start time
 * @param   end_time        The event end time
 * @param   access_t        The access type of the event
 * @param   owner_id        The username of the creator
 * @param   repeatType      How often does the event repeat
 * @return  event           A new Event object
 */
Event* Event_Factory::create_event(string eventName, string details, time_t start_time,
    time_t end_time, string access_t, string owner_id, string repeatType) {
    Event* event = new Event(eventName, details, start_time, end_time, access_t, owner_id, repeatType);
    return event;
}
