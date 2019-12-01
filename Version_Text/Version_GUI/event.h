/**
 * Header File for event entities
 * CREATED BY: Abarna Srikantharajah
 * LAST EDITED BY: Abarna Srikantharajah
 * LAST EDITED: 19/11/2019
 * @brief the file that contains all the prototype functions and variables for the events class
 *
 * @author  Abarna Srikantharajah
 * @date   19/11/2019
 */


#ifndef EVENT_H
#define EVENT_H

#include <ctime>
#include "string"

class Event {
private:
    std::string eventName;
    std::string details;
    std::string access_t;
    std::string owner_id;
    std::string repeat_type;
    std::time_t start_time;
    std::time_t end_time;


public:
    Event(){};
    //initialize event class
    Event(std::string in_eventName, std::string in_details,
        std::time_t in_start_time,std::time_t in_end_time,
        std::string in_access_t, std::string in_owner_id,
        std::string in_repeatType){
            eventName = in_eventName;
            details = in_details;
            start_time = in_start_time;
            end_time = in_end_time;
            access_t = in_access_t;
            owner_id = in_owner_id;
            repeat_type = in_repeatType;
    };

   /**
    * @brief get the event name attribute from an event object
    *
    * @author             Abarna Srikantharajah
    * @return  eventName  current eventName attribute as a string
    */
    std::string get_eventName() const {return eventName;}

   /**
    * @brief get the details attribute
    *
    * @author             Abarna Srikantharajah
    * @return  details    current details attribute as a string
    */
    std::string get_details(){return details;}

   /**
    * @brief get the start time attribute
    *
    * @author             Abarna Srikantharajah
    * @return start_time  current start time attribute as a time_t datatype
    */
    std::time_t get_start_time(){return start_time;}

   /**
    * @brief get the end time attribute
    *
    * @author             Abarna Srikantharajah
    * @return  end_time   current end time attribute as a time_t datatype
    */
    std::time_t get_end_time(){return end_time;}

   /**
    * @brief get the access attribute
    *
    * @author             Abarna Srikantharajah
    * @return  access_t   current access attribute as a string to determine if event has public or private access
    */
    std::string get_access_t(){return access_t;}

   /**
    * @brief get the owner id attribute
    *
    * @author             Abarna Srikantharajah
    * @return  owner_id   current owner id attribute as a string
    */
    std::string get_owner_id(){return owner_id;}

   /**
    * @brief get the repeat type attribute
    *
    * @author               Abarna Srikantharajah
    * @return  repeat_type  current repeat type attribute as a string
    */
    std::string get_repeat_type(){return repeat_type;}
    void set_eventName(std::string newEventName);
    void set_details(std::string newDetails);
    void set_start_time(std::time_t newStartTime);
    void set_end_time(std::time_t newEndTime);
    void set_access_t(std::string newAccess);
    void set_owner_id(std::string newOwner);
    void set_repeat_type(std::string newRepeat);

};

#endif /* EVENT_H */
