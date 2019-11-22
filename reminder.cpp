#include "reminder.h"

using namespace std;

Reminder::Reminder(Event in_event, string in_destination, time_t in_remind_time){
    event = in_event
    destination = in_destination;
    remind_time = in_remind_time
}

void Reminder::set_event(string newEvent){
    event = newEvent;
}

void Event::set_destination(string newDestination){
    destination = newDestination;
}

void Event::set_remind_time(time_t newRemindTime){
    remind_time = newRemindTime;
}
