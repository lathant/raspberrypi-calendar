#ifndef CONTROL_H
#define CONTROL_H

#include "mainwindow.h"
#include <QApplication>
#include <iostream>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <thread>
#include <cstdio>
#include <ctime>
#include <set>

#include "user_manager.h"
#include "event_manager.h"
#include "timetable_manager.h"

std::string user_login(std::vector<std::string> parts);

std::string user_create(std::vector<std::string> parts);

std::string event_create(std::vector<std::string> parts);

std::string event_get(std::vector<std::string> parts);

std::string event_delete(std::vector<std::string> parts);

std::string timeable_create(std::vector<std::string> parts);

std::string timetable_get(std::vector<std::string> parts);

std::string event_add(std::vector<std::string> parts);

void init_User_Manager();

void init_Event_Manager();

#endif // CONTROL_H
