#include "reminder.h"

using namespace std;

void Reminder::set_event(string newEvent){
    Reminder::event = newEvent;
}

void Reminder::set_destination(string newDestination){
    destination = newDestination;
}

void Reminder::set_remind_time(time_t newRemindTime){
    remind_time = newRemindTime;
}
