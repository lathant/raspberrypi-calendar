/* Header File for reminder generating entities
 * CREATED BY: Lathan Thangavadivel
 * LAST EDITED BY: Lathan Thangavadivel
 * LAST EDITED: 25/11/2019
 * @brief the file that contains the constructor for the reminder factory class
 *
 * @author  Lathan Thangavadivel
 * @date   25/11/2019
 */

#ifndef REMINDER_FACTORY_H
#define REMINDER_FACTORY_H

#include "event_factory.h"

class Reminder_Factory {
public:
    Reminder_Factory();
    Reminder* create_reminder(std::Event e, std::time_t remind_time, std::string destination);
};

#endif /* REMINDER_FACTORY_H */
