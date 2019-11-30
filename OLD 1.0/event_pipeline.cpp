 
/* Class for event pipeline
 * CREATED BY: Lathan Thangavadivel
 * LAST EDITED BY: Abarna Srikantharajah
 * LAST EDITED: 20/11/2019
 * TODO:
 */


#include "event_pipeline.h"


using namespace std;

void Event_Pipeline::enqueue(Reminder event){
        pipe.push_front(event);
    }

Reminder Event_Pipeline::dequeue(){
    list <Reminder> :: iterator scan;
    list <Reminder> :: iterator smallest;
    smallest = pipe.begin();
    Reminder smallestValue;
    for (scan = pipe.begin(); scan != pipe.end(); ++scan) {
        Reminder scanValue = *scan;
        smallestValue = *smallest;
        if (difftime(scanValue.get_remind_time(),smallestValue.get_remind_time())<0){
            smallest = scan;
        }
    }
    pipe.erase(smallest);
    return smallestValue;
    }


Reminder Event_Pipeline::peak(){
    list <Reminder> :: iterator scan;
    list <Reminder> :: iterator smallest;
    smallest = pipe.begin();
    Reminder smallestValue;
    for (scan = pipe.begin(); scan != pipe.end(); ++scan) {
        Reminder scanValue = *scan;
        smallestValue = *smallest;
        if (difftime(scanValue.get_remind_time(),smallestValue.get_remind_time())<0){
            smallest = scan;
        }
    }
    return smallestValue;
};

bool Event_Pipeline::contains(Reminder event){
    list <Reminder> :: iterator scan;
    for (scan = pipe.begin(); scan != pipe.end(); ++scan) {
        Reminder scanValue = *scan;

        if (scanValue.get_event().get_eventName().compare(event.get_event().get_eventName())){
            if(difftime(scanValue.get_remind_time(),event.get_remind_time()) == 0){
                return true;
            }
        }
    }
    return false;
};
