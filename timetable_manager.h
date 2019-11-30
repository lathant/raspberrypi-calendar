/**
 * @brief Header File for timetable manager
 *
 * The header file that contains all the prototype functions and variables for the timetable manager class
 *
 * @author  Vladimir Zhurov
 * @date	05/11/2019
 */

#ifndef TIMETABLE_MANAGER_H
#define TIMETABLE_MANAGER_H

#include <vector>
#include "timetable_factory.h"

class Timetable_Manager {
    private:
        static Timetable_Manager* instance;
        Timetable_Manager(){};


    public:
        static Timetable_Manager* get_instance();
        Timetable* get_timetable(std::string table_name);
        int create_timetable(std::string name, std::string access_t, std::string owner_id);
        int save_timetable(Timetable table);
        int delete_timetable(std::string table_name);
        int append_date(std::string table_name, std::string event_info);
        int remove_date(std::string table_name, std::string event_info);
        int add_member(std::string table_name, std::string member_id);
        int remove_member(std::string table_name, std::string member_id);
        std::vector<Timetable> get_personal_tables(std::string owner_id);
        std::vector<Timetable> get_shared_tables(std::string owner_id);
        std::vector<Timetable> get_public_tables();
        std::string timetable_to_txt(Timetable timetable);
        std::string compare_timetables(std::string table1name, std::string table2name);

};

#endif /* TIMETABLE_MANAGER_H */
