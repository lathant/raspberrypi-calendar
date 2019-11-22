#ifndef REMINDER_FACTORY_H
#define REMINDER_FACTORY_H

#include "event_factory.h"

class Reminder_Factory {
public:
    Reminder_Factory();
    Reminder* create_reminder(std::Event e, std::time_t remind_time, std::string destination);
};

#endif /* REMINDER_FACTORY_H */