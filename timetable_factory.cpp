/* Class for timetable factory methods
 * CREATED BY: Vladimir Zhurov
 * LAST EDITED BY: Vladimir Zhuurov
 * LAST EDITED: 06/11/2019
 * TODO: Expand
 */

#include "timetable_factory.h"

using namespace std;

//implement to store value for factory opperation method
Timetable_Factory::Timetable_Factory(){};

Timetable* Timetable_Factory::create_timetable(string in_name, string in_access_t, string in_owner_id) {
    Timetable* timetable = new Timetable(in_name, in_access_t, in_owner_id);
    return timetable;
}
