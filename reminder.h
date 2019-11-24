#ifndef REMINDER_H
#define REMINDER_H

#include "event.h"

class Reminder {
    private:
            std::string event;
            std::string destination
            std::time_t remind_time
    public:
            std::string get_event(){return event;}
            std::string get_destination(){return destination;}
            std::time_t get_remind_time(){return remind_time;}
            void set_event(std::string newEvent);
            void set_destination(std::string newDestination);
            void set_remind_time(std::time_t newTime);
};

#endif /* REMINDER_H */
