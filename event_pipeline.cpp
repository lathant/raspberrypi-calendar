/* Class for event pipeline
 * CREATED BY: Lathan Thangavadivel
 * LAST EDITED BY: Abarna Srikantharajah
 * LAST EDITED: 20/11/2019
 * TODO:
 */


#include <queue>

using namespace std;

Event_Pipeline::Event_Pipeline(){}

bool CompareTime (Event const &event1, Event const &event2) {
        double diff = difftime(event1.get_time(),event2.get_time());
        return diff < 0;
    }
    
void Event_Pipeline::enqueue(Event event){
        queue.push(event);
    }
    
Event Event_Pipeline::dequeue(){
        return queue.pop();
    }

};
