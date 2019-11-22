/* Class representing event factory
 * CREATED BY: Abarna Srikantharajah
 * LAST EDITED BY: Abarna Srikantharajah
 * LAST EDITED: 19/11/2019
 * TODO:
 *   header file that generates events
 */

#ifndef EVENT_FACTORY_H
#define EVENT_FACTORY_H

#include "event.h"

class Event_Factory {
public:
    Event_Factory();
    Event* create_event(std::string eventName, std::string details, std::time_t time,std::string access_t, std::string owner_id, std::string repeatType);
};

#endif /* EVENT_FACTORY_H */
