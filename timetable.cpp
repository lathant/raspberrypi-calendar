/* Class for timetable object
 * CREATED BY: Vladimir Zhurov
 * LAST EDITED BY: Vladimir Zhurov
 * LAST EDITED: 05/11/2019
 * TODO: ...
 */

#include "timetable.h"

using namespace std;

Timetable::Timetable(string in_name, string in_access_t, string in_owner_id){
        name = in_name;
        access_t = in_access_t;
        owner_id = in_owner_id;
        member_id.insert(in_owner_id);
}

void Timetable::set_name(string new_name){
    name = new_name;
}

void Timetable::set_access_t(string new_access_t){
    access_t = new_access_t;
}

int Timetable::add_member(string user_id){
    if(member_id.find(user_id) != member_id.end())
        return 0;
    member_id.insert(user_id);
    return 1;
}

int Timetable::remove_member(string user_id){
    if(member_id.find(user_id) != member_id.end())
        return 0;
    member_id.erase(user_id);
    return 1;
}

int Timetable::add_date(string date){
    if(dates.find(date) != dates.end())
        return 0;
    dates.insert(date);
    return 1;
}

int Timetable::remove_date(string date){
    if(dates.find(date) != dates.end())
        return 0;
    dates.erase(date);
    return 1;
}

int Timetable::is_member(string user_id){
    if(member_id.find(user_id) != member_id.end())
        return 0;
    return 1;
}
