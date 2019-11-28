 /**
  * @brief Class for timetable factory methods
  *
  * Implementation for timetable factory methods
  * @author  Vladimir Zhurov
  * @date    06/11/2019
  */

#include "timetable_factory.h"

using namespace std;

/**
 * @brief constructor for Timetable_Factory
 *
 * @author  Vladimir Zhurov
 * @date    06/11/2019
 */
Timetable_Factory::Timetable_Factory(){};

/**
 * @brief Create a new timetable
 *
 * Call the timetable object constructor
 * @author  Vladimir Zhurov
 * @date    06/11/2019
 * @param   in_name         The timetable name
 * @param   in_access_t     The access type of the timetable
 * @param   in_owner_id     The owner's username
 * @return  timetable       A new timetable object
 */
Timetable* Timetable_Factory::create_timetable(string in_name, string in_access_t, string in_owner_id) {
    Timetable* timetable = new Timetable(in_name, in_access_t, in_owner_id);
    return timetable;
}
