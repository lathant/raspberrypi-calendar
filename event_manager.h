/* Header File for event manager entities
 * CREATED BY: Lathan Thangavadivel
 * LAST EDITED BY: Lathan Thangavadivel
 * LAST EDITED: 25/11/2019
 * @brief the file that contains all the prototype functions and variables for the event manager class
 *
 * @author  Lathan Thangavadivel
 * @date   25/11/2019
 */

#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H

#include "event_factory.h"
#include <vector>

class Event_Manager {
    private:
        static Event_Manager* instance;
        //initialize event manager class
        Event_Manager(){};
        Event* get_event(std::string event_name);

    public:
        static Event_Manager* get_instance();
        int create_event(std::string eventName, std::string details,
            time_t start_time, time_t end_time, std::string access_t,
            std::string owner_id, std::string repeatType);
        int delete_event(std::string event_name);
        std::vector<Event> get_personal_events(std::string owner_id);
        std::vector<Event> get_public_events();
        std::string event_to_txt(Event event);

};

#endif /* EVENT_MANAGER_H */
