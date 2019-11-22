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
    std::string access_t;
    std::string owner_id;
    std::string repeat_type;
    
    
public:
    Event(std::string eventName, std::string details, std::time_t time);
    std::string get_eventName(){return eventName;}
    std::string get_details(){return details;}
    std::time_t get_time(){return time;}
    std::string get_access_t(){return access_t;}
    std::string get_owner_id(){return owner_id;}
    std::string get_repeat_type(){return repeat_type;}
    void set_eventName(std::string newEventName);
    void set_details(std::string newDetails);
    void set_time(std::time_t newTime);
    void set_access_t(std::string newAccess);
    void set_owner_id(std::string newOwner);
    void set_repeat_type(std::string newRepeat);
    
};

#endif /* EVENT_H */
