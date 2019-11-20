

#include <queue>

using namespace std;



bool CompareTime (Event const & event1, Event const & event2) {
        double diff = std::difftime(std::event1.get_time(),std::event2..get_time());
        return diff < 0;
    }

static queue<Event,vector<Event>,CompareTime>;
    
void Event_Pipeline::enqueue(std::Event){
        queue.push(Event);
    }
    
Event Event_Pipeline::dequeue(){
        return queue.pop()
    }

};
