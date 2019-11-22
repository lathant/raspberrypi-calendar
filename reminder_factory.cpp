#include "reminder_factory.h"

using namespace std;

//implement factory method
Reminder_Factory::Reminder_Factory(){};

Reminder* Reminder_Factory::create_reminder(Event e,time_t remind_time, string destination){
    Reminder* reminder = new Reminder(Event e, time_t remind_time, string destination);
    return reminder;
}