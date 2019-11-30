/* Class representing event pipeline
 * CREATED BY: Lathan Thangavadivel
 * LAST EDITED BY: Abarna Srikantharajah
 * LAST EDITED: 20/11/2019
 * TODO:
 */

#ifndef EVENT_PIPELINE_H
#define EVENT_PIPELINE_H

#include "event.h"
#include "reminder.h"
#include <list>
#include <iterator>


class Event_Pipeline{
    private:
        std::list<Reminder> pipe;
                
    public:
        Event_Pipeline(){};
        void enqueue(Reminder event);
        Reminder dequeue();
        Reminder peak();
        bool contains(Reminder event);
};

#endif /* EVENT_PIPELINE_H */
