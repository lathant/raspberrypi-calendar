 /**
  * @brief Class implementing timetable
  *
  * An implementing timetable
  * @author Vladimir Zhurov
  * @date   05/11/2019
  */

#include "timetable.h"

using namespace std;

/**
 * @brief Constructor for Timetable
 *
 * The constructor for the Timetable
 * @author Vladimir Zhurov
 * @date   05/11/2019
 * @param   in_name         The timetable name
 * @param   in_access_t     The access type of the timetable
 * @param   in_owner_id     The owner's username
 */
Timetable::Timetable(string in_name, string in_access_t, string in_owner_id){
        name = in_name;
        access_t = in_access_t;
        owner_id = in_owner_id;
}

/**
 * @brief Set name method
 *
 * Update the Timetable's name
 * @author Vladimir Zhurov
 * @date   05/11/2019
 * @param   new_name         The new timetable name
 */
void Timetable::set_name(string new_name){
    name = new_name;
}

/**
 * @brief Set access type method
 *
 * Update the Timetable's access type
 * @author Vladimir Zhurov
 * @date   05/11/2019
 * @param   new_access_t         The new timetable access type
 */
void Timetable::set_access_t(string new_access_t){
    access_t = new_access_t;
}

/**
 * @brief Add member to Timetable
 *
 * Add a member to the timeable's member set, return 0 if already present and 1 on success
 * @author Vladimir Zhurov
 * @date   05/11/2019
 * @param   user_id         The username of the new member
 */
int Timetable::add_member(string user_id){
    if(member_id.find(user_id) != member_id.end())
        return 0;
    member_id.insert(user_id);
    return 1;
}

/**
 * @brief Remove a member from Timetable
 *
 * Remove a member to the timeable's member set, return 0 if already present and 1 on success
 * @author Vladimir Zhurov
 * @date   05/11/2019
 * @param   user_id         The username of the member
 */
int Timetable::remove_member(string user_id){
    if(member_id.find(user_id) != member_id.end())
        return 0;
    member_id.erase(user_id);
    return 1;
}

/**
 * @brief Add a date to Timetable
 *
 * Add a date to the timetable's member set, return 0 if already present and 1 on success
 * @author Vladimir Zhurov
 * @date   05/11/2019
 * @param   date         string rep of date
 */
int Timetable::add_date(string date){
    if(dates.find(date) != dates.end())
        return 0;
    dates.insert(date);
    return 1;
}

/**
 * @brief Remove a date from Timetable
 *
 * Remove a date to the timetable's member set, return 0 if already present and 1 on success
 * @author Vladimir Zhurov
 * @date   05/11/2019
 * @param   date         string rep of date
 */
int Timetable::remove_date(string date){
    if(dates.find(date) != dates.end())
        return 0;
    dates.erase(date);
    return 1;
}

/**
 * @brief Check member in Timetable
 *
 * Check if a member is in the timeable's member set, return 1 if already present and 0 if not
 * @author Vladimir Zhurov
 * @date   05/11/2019
 * @param   user_id         The username of the member
 */
int Timetable::is_member(string user_id){
    if(member_id.find(user_id) != member_id.end())
        return 0;
    return 1;
}
