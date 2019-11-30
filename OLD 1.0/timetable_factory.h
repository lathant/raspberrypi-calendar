/**
 * @brief Class representing for timetable factory methods
 *
 * Representing for timetable factory methods
 * @author  Vladimir Zhurov
 * @date    05/11/2019
 */
#ifndef TIMETABLE_FACTORY_H
#define TIMETABLE_FACTORY_H

#include "timetable.h"

class Timetable_Factory {
    public:
        Timetable_Factory();
        Timetable* create_timetable(std::string name, std::string access_t, std::string owner_id);
        Timetable* create_timetable(std::string name, std::string access_t, std::string owner_id,
        std::set<std::string> inmember_id, std::set<std::string> indates);
};

#endif /* TIMETABLE_FACTORY_H */
