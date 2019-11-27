/* Class that generates reminders
 * CREATED BY: Lathan Thangavadivel
 * LAST EDITED BY: Lathan Thangavadivel
 * LAST EDITED: 25/11/2019
 * @brief creates an instance of a reminder using the factory method
 *
 * @author  Lathan Thangavadivel
 * @date   25/11/2019
 */

#include "reminder_factory.h"

using namespace std;

//implement factory method
Reminder_Factory::Reminder_Factory(){};

Reminder* Reminder_Factory::create_reminder(Event e,time_t remind_time, string destination){
    Reminder* reminder = new Reminder(Event e, time_t remind_time, string destination);
    return reminder;
}
