/**
 * Class that sets attributes for event entities
 * CREATED BY: Abarna Srikantharajah
 * LAST EDITED BY: Abarna Srikantharajah
 * LAST EDITED: 19/11/2019
 * @brief the file that contains the setter functions for the attributes of an event entity
 *
 * @author  Abarna Srikantharajah
 * @date   19/11/2019
 */

#include "event.h"

using namespace std;

/**
 * @brief sets the current eventname string of the current event object with the given new eventname string
 *
 * @author                 Abarna Srikantharajah
 * @param  newEventName    new eventname attribute
 */
void Event::set_eventName(string newEventName){
    eventName = newEventName;
}

/**
 * @brief sets the current details string of the current event object with the given new details string
 *
 * @author                 Abarna Srikantharajah
 * @param  newDetails      new details attribute
 */
void Event::set_details(string newDetails){
    details = newDetails;
}

/**
 * @brief sets the current start time time_t datatype of the current event object with the given new start time attribute
 *
 * @author                 Abarna Srikantharajah
 * @param  newStartTime    new start time attribute
 */
void Event::set_start_time(time_t newStartTime){
    start_time = newStartTime;
}

/**
 * @brief sets the current end time time_t datatype of the current event object with the given new end time attribute
 *
 * @author                 Abarna Srikantharajah
 * @param  newEndTime      new end time attribute
 */
void Event::set_end_time(time_t newEndTime){
    end_time = newEndTime;
}

/**
 * @brief sets the current access string of the current event object with the given new access string that determines whether
 * the event has public or private access
 *
 * @author                 Abarna Srikantharajah
 * @param  newAccess       new access attribute
 */
void Event::set_access_t (string newAccess){
    access_t = newAccess;
}

/**
 * @brief sets the current owner id string of the current event object with the given new owner id string
 *
 * @author                 Abarna Srikantharajah
 * @param  newOwner        new owner id attribute
 */
void Event::set_owner_id(string newOwner){
    owner_id = newOwner;
}

/**
 * @brief sets the current repeat type string of the current event object with the given new repeat type string
 *
 * @author                 Abarna Srikantharajah
 * @param  newRepeatType   new repeat type attribute
 */
void Event::set_repeat_type(string newRepeatType){
    repeat_type = newRepeatType;
}
