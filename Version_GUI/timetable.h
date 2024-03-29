/**
  * @brief Class representing timetable
  *
  * A representation of timetable
  * @author Vladimir Zhurov
  * @author Lathan Thangavadivel
  * @date   28/11/2019
  */
#ifndef TIMETABLE_H
#define TIMETABLE_H

#include "string"
#include "set"

class Timetable {
    private:
        std::string name;
        std::string access_t;
        std::string owner_id;
        std::set<std::string> member_id;
        std::set<std::string> dates;

    public:
        Timetable(std::string name, std::string access_t, std::string owner_id);
        Timetable(std::string inname, std::string inaccess_t, std::string inowner_id,
                    std::set<std::string> inmember_id, std::set<std::string> indates){
            name = inname;
            access_t = inaccess_t;
            owner_id = inowner_id;
            member_id = inmember_id;
            dates = indates;
        }
        std::string get_name() const{return name;}
        std::string get_access_t(){return access_t;}
        std::string get_owner_id(){return owner_id;}
        std::set<std::string> get_dates(){return dates;}
        std::set<std::string> get_members(){return member_id;}
        void set_name(std::string name);
        void set_access_t(std::string access_t);
        int add_member(std::string user_id);
        int remove_member(std::string user_id);
        int add_date(std::string date);
        int remove_date(std::string date);
        int is_member(std::string user_id);

};

#endif /* TIMETABLE_H */
