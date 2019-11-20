/* Class representing event pipeline
 * CREATED BY: Lathan Thangavadivel
 * LAST EDITED BY: Abarna Srikantharajah
 * LAST EDITED: 20/11/2019
 * TODO:
 */

#ifndef EVENT_PIPELINE_H
#define EVENT_PIPELINE_H

#include "event.h"
#include <queue>


class Event_Pipeline{
    private:
        std::queue<event,vector<event>,CompareTime> eventQueue;
                
    public:
        Event_Pipeline();
        std::string get_queue(){return eventqueue;}
        static queue<Event,vector<Event>,CompareTime> eventQueue;
        std::bool CompareTime(std::Event const &event1, std::Event const &event2);
        void enqueue(std::Event event);
        std::Event Event_Pipeline::dequeue();
};

#endif /* EVENT_PIPELINE_H */
