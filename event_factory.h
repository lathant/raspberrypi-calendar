/* Header File for generating event entities 
 * CREATED BY: Abarna Srikantharajah
 * LAST EDITED BY: Abarna Srikantharajah
 * LAST EDITED: 19/11/2019
 * @brief the file that contains all the prototype functions and variables for the event factory class
 *
 * @author  Abarna Srikantharajah
 * @date   19/11/2019
 */

#ifndef EVENT_FACTORY_H
#define EVENT_FACTORY_H

#include "event.h"

class Event_Factory {
public:
    Event_Factory();
    Event* create_event(std::string eventName, std::string details, std::time_t start_time,std::time_t end_time,std::string access_t, std::string owner_id, std::string repeatType);
};

#endif /* EVENT_FACTORY_H */
