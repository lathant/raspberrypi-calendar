 /**
  * @brief      Class representing event manager
  * @author     Vladimir Zhurov
  * @date       25/11/2019
  */

#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H

#include "event_factory.h"
#include "set"

class Event_Manager {
    private:
        static Event_Manager* instance;
        Event_Manager(){};

    public:
        static Event_Manager* get_instance();
        int create_event(std::string eventName, std::string details,
            time_t start_time, time_t end_time, std::string access_t,
            std::string owner_id, std::string repeatType);
        int delete_event(std::string event_name);
        std::set<Event> get_personal_events(std::string owner_id);
        std::set<Event> get_shared_events(std::string owner_id);
        std::set<Event> get_public_events();
        std::string event_to_txt(Event event);

};

#endif /* EVENT_MANAGER_H */
