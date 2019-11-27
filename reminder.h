/* Header File for reminder entities 
 * CREATED BY: Lathan Thangavadivel
 * LAST EDITED BY: Lathan Thangavadivel
 * LAST EDITED: 25/11/2019
 * @brief the file that contains all the prototype functions and variables for the reminders class
 *
 * @author  Lathan Thangavadivel
 * @date   25/11/2019
 */


#ifndef REMINDER_H
#define REMINDER_H

#include "event.h"

class Reminder {
    private:
            std::string event;
            std::string destination;
            std::time_t remind_time;
    public:
            Reminder(){};
            //initialize reminder class
            Reminder(std::string in_event, std::string in_destination, std::time_t in_remind_time){
                event = in_event;
                destination = in_destination;
                remind_time = in_remind_time;
            }
           /*
            * @brief get the event attribute
            *
            * @author             Lathan Thangavadivel
            * @return  event      event attribute
            */
            std::string get_event(){return event;}
    
            /*
            * @brief get the destination attribute
            *
            * @author                   Lathan Thangavadivel
            * @return  destination      destination attribute
            */
            std::string get_destination(){return destination;}
    
           /*
            * @brief get the reminder time attribute
            *
            * @author                   Lathan Thangavadivel
            * @return  remind_time      reminder time attribute
            */
            std::time_t get_remind_time(){return remind_time;}
            void set_event(std::string newEvent);
            void set_destination(std::string newDestination);
            void set_remind_time(std::time_t newTime);
};

#endif /* REMINDER_H */
