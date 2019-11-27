/* Class that sets attributes for reminder entities 
 * CREATED BY: Lathan Thangavadivel
 * LAST EDITED BY: Lathan Thangavadivel
 * LAST EDITED: 25/11/2019
 * @brief the file that contains the setter functions for the attributes of a reminder entity
 *
 * @author  Lathan Thangavadivel
 * @date   25/11/2019
 */

#include "reminder.h"

using namespace std;

/*
* @brief sets the event string with the given new event string 
*
* @author             Lathan Thangavadivel
* @param  newEvent    new event attribute
*/
void Reminder::set_event(string newEvent){
    Reminder::event = newEvent;
}

/*
* @brief sets the destination string with the given new destination string 
*
* @author                   Lathan Thangavadivel
* @param  newDestination    new destination attribute
*/
void Reminder::set_destination(string newDestination){
    destination = newDestination;
}

/*
* @brief sets the remind time attribute with the given new time 
*
* @author            Lathan Thangavadivel
* @param  newTime    new reminder time attribute
*/
void Reminder::set_remind_time(time_t newRemindTime){
    remind_time = newRemindTime;
}
