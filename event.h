/* Class representing events
 * CREATED BY: Abarna Srikantharajah
 * LAST EDITED BY: Abarna Srikantharajah
 * LAST EDITED: 19/11/2019
 * TODO:
 */

#ifndef EVENT_H
#define EVENT_H

#include <ctime>
#include "string"

class Event {
private:
    std::string eventName;
    std::string details;
    std::time_t time;
    
public:
    Event(std::string eventName, std::string details, std::time_t time);
    std::string get_eventName(){return eventName;}
    std::string get_details(){return details;}
    std::time_t get_time(){return time;}
    void set_eventName(std::string newEventName);
    void set_details(std::string newDetails);
    void set_time(std::time_t newTime);
    
};

#endif /* EVENT_H */
