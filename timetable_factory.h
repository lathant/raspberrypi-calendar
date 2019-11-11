/* Class representing timetable factory
* CREATED BY: Vladimir Zhurov
* LAST EDITED BY: Vladimir Zhurov
* LAST EDITED: 05/11/2019
* TODO: Expand
*/

#ifndef TIMETABLE_FACTORY_H
#define TIMETABLE_FACTORY_H

#include "timetable.h"

class Timetable_Factory {
    public:
        Timetable_Factory();
        Timetable* create_timetable(std::string name, std::string access_t, std::string owner_id);
};

#endif /* TIMETABLE_FACTORY_H */
