#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "control.h"
#include <QMessageBox>
#include <map>
#include <QDateTime>
#include <ctime>
#include "string"
#include <QPen>
#include <QBrush>
#include <QColor>
#include <QPainter>


using namespace std;

/**
 * @brief returns instance of the MainWindow clas
 *
 * @author   John Jewell
 * @author   John Jewell
 * @date     30/11/2019
 * @return   Main Window
 */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    string current_user = "";
    string current_table_name = "";
    current_type_str_int = "";
    string current_timetables = "";

}
/**
 * @brief destructor for call MainWindow
 *
 * @author   John Jewell
 * @author   John Jewell
 * @date     30/11/2019
 * @return   Main Window
 */
MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * @brief handles the log in event
 *
 * @author   John Jewell
 * @author   John Jewell
 * @date     30/11/2019
 */
void MainWindow::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

/**
 * @brief handles the sign in event
 *
 * @author   John Jewell
 * @author   John Jewell
 * @date     30/11/2019
 */
void MainWindow::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

/**
 * @brief Logs user in
 *
 * @author   John Jewell
 * @author   John Jewell
 * @date     30/11/2019
 */
void MainWindow::on_pushButton_3_clicked()
{
    string request, response;
    vector<string> in_parts, out_parts;
    string username = ui->lineEdit->text().toStdString();
    string password = ui->lineEdit_2->text().toStdString();
    if (username == "" || password == "") {
        QMessageBox::warning(this, "Warning", "Must Specify Username And Password");
        return;
    }
    request = "LOGIN|" + username + "|" + password;
    stringstream out_ss (request.c_str());
    while (getline(out_ss, request, '|'))
        out_parts.push_back(request);
    response = user_login(out_parts);

    stringstream in_ss(response);
    while (getline(in_ss, response, '|'))
        in_parts.push_back(response);

    if(in_parts.at(1).compare("SUCCESS") == 0) {
        current_user = username;
        ui->stackedWidget->setCurrentIndex(3);
     } else {
       QMessageBox::warning(this, "Warning", "No Such User");
     }
}

/**
 * @brief Create new user
 *
 * @author   John Jewell
 * @author   John Jewell
 * @date     30/11/2019
 */
void MainWindow::on_pushButton_4_clicked()
{
    string request, response;
    vector<string> in_parts, out_parts;
    string username = ui->lineEdit_3->text().toStdString();
    string password = ui->lineEdit_4->text().toStdString();
    if (username == "" || password == "") {
        QMessageBox::warning(this, "Warning", "Must Specify Username And Password");
        return;
    }
    request = "CREATE USER|" + username + "|" + password;
    stringstream out_ss (request.c_str());
    while (getline(out_ss, request, '|'))
        out_parts.push_back(request);
     response = user_create(out_parts);

     stringstream in_ss(response);
     while (getline(in_ss, response, '|'))
         in_parts.push_back(response);

     if(in_parts.at(1).compare("SUCCESS") == 0) {
         ui->stackedWidget->setCurrentIndex(3);
         current_user = username;
      } else {
        QMessageBox::warning(this, "Warning", "Account Exists");
      }
}

/**
 * @brief handles the exit of the application
 *
 * @author   John Jewell
 * @author   John Jewell
 * @date     30/11/2019
 */
void MainWindow::on_pushButton_7_clicked()
{
    QApplication::quit();
}

/**
 * @brief bring user to the main menu
 *
 * @author   John Jewell
 * @author   John Jewell
 * @date     30/11/2019
 */
void MainWindow::on_pushButton_8_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}

/**
 * @brief Creates public timetable
 *
 * @author   John Jewell
 * @author   John Jewell
 * @date     30/11/2019
 */
void MainWindow::on_pushButton_9_clicked()
{
    string request, response;
    vector<string> in_parts, out_parts;
    string table_name = ui->lineEdit_5->text().toStdString();
    string access_type = "public";
    if (table_name == "") {
        QMessageBox::warning(this, "Warning", "Table must have name");
        return;
    }

    request = "CREATE TIMETABLE|" + table_name + "|" + access_type + "|" + current_user;
    stringstream out_ss (request.c_str());
    while (getline(out_ss, request, '|'))
        out_parts.push_back(request);
     response = timeable_create(out_parts);

     stringstream in_ss(response);
     while (getline(in_ss, response, '|'))
         in_parts.push_back(response);

     if(in_parts.at(1).compare("SUCCESS") == 0) {
         ui->stackedWidget->setCurrentIndex(3);
      } else {
        QMessageBox::warning(this, "Warning", "Table Exists");
      }

}

/**
 * @brief Creates private timetable
 *
 * @author   John Jewell
 * @author   John Jewell
 * @date     30/11/2019
 */
void MainWindow::on_pushButton_10_clicked()
{
    string request, response;
    vector<string> in_parts, out_parts;
    string table_name = ui->lineEdit_5->text().toStdString();
    string access_type = "nonpublic";
    if (table_name == "") {
        QMessageBox::warning(this, "Warning", "Table must have name");
        return;
    }

    request = "CREATE TIMETABLE|" + table_name + "|" + access_type + "|" + current_user;
    stringstream out_ss (request.c_str());
    while (getline(out_ss, request, '|'))
        out_parts.push_back(request);
     response = timeable_create(out_parts);

     stringstream in_ss(response);
     while (getline(in_ss, response, '|'))
         in_parts.push_back(response);

     if(in_parts.at(1).compare("SUCCESS") == 0) {
         ui->stackedWidget->setCurrentIndex(3);
      } else {
        QMessageBox::warning(this, "Warning", "Table Exists");
      }
}

/**
 * @brief Creates shared timetbale
 *
 * @author   John Jewell
 * @author   John Jewell
 * @date     30/11/2019
 */
void MainWindow::on_pushButton_11_clicked()
{
    string request, response;
    vector<string> in_parts, out_parts;
    string table_name = ui->lineEdit_5->text().toStdString();
    string access_type = "shared";
    if (table_name == "") {
       QMessageBox::warning(this, "Warning", "Table must have name");
       return;
    }

    request = "CREATE TIMETABLE|" + table_name + "|" + access_type + "|" + current_user;
    stringstream out_ss (request.c_str());
    while (getline(out_ss, request, '|'))
        out_parts.push_back(request);
    response = timeable_create(out_parts);

    stringstream in_ss(response);
    while (getline(in_ss, response, '|'))
        in_parts.push_back(response);

    if(in_parts.at(1).compare("SUCCESS") == 0) {
        ui->stackedWidget->setCurrentIndex(3);
    } else {
        QMessageBox::warning(this, "Warning", "Table Exists");
    }
}

/**
 * @brief Go to public timetables
 *
 * @author   John Jewell
 * @author   John Jewell
 * @date     30/11/2019
 */
void MainWindow::on_pushButton_5_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
    current_type = "public";
    current_type_str_int = "2";
    string request, response;
    vector<string> in_parts, out_parts;

    request = "GET TIMETABLE|2|" + current_user;
    stringstream out_ss (request.c_str());
    while (getline(out_ss, request, '|'))
        out_parts.push_back(request);

    response = timetable_get(out_parts);

    current_timetables = response;
    stringstream in_ss(response.c_str());
    while (getline(in_ss, response, '|'))
        in_parts.push_back(response);

    if (in_parts.size() == 2) {
        QMessageBox::warning(this, "Warning", "No Public Tables");
        ui->stackedWidget->setCurrentIndex(4);
        return;
    }

    for (int i=2; i < in_parts.size(); i++) {
        vector<string> table_parts;
        string table_string = in_parts.at(i);
        stringstream table_ss(table_string.c_str());
        while (getline(table_ss, table_string, '&'))
            table_parts.push_back(table_string);
        string table_name = table_parts.at(0);
        ui->comboBox->addItem(QString::fromStdString(table_name));
    }
}

/**
 * @brief Allows user to view timetable
 *
 * @author   John Jewell
 * @author   John Jewell
 * @date     30/11/2019
 */
void MainWindow::on_pushButton_13_clicked()
{
    ui->stackedWidget->setCurrentIndex(6);
    string selected_table_name = ui->comboBox->currentText().toStdString();
    current_table_name = selected_table_name;
    string current_tables = current_timetables;
    vector<string> parts;
    stringstream out_ss (current_tables.c_str());
    while (getline(out_ss, current_tables, '|'))
        parts.push_back(current_tables);


    for (int i=2; i < parts.size(); i++) {
        vector<string> table_parts;
        string table_string = parts.at(i);
        string  table_string2 = table_string;
        stringstream table_ss(table_string.c_str());
        while (getline(table_ss, table_string, ','))
            table_parts.push_back(table_string);
        string table_name = table_parts.at(0);
        if (table_name == current_table_name) {

            current_timetable = table_string2;
            update_table();
            return;
        }
    }


}
/**
 * @brief Allows user to view private time tables
 *
 * @author   John Jewell
 * @author   John Jewell
 * @date     30/11/2019
 */
void MainWindow::on_pushButton_6_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
    current_type = "private";
    current_type_str_int = "0";
    string request, response;
    vector<string> in_parts, out_parts;

    request = "GET TIMETABLE|0|" + current_user;
    stringstream out_ss (request.c_str());
    while (getline(out_ss, request, '|'))
        out_parts.push_back(request);

    response = timetable_get(out_parts);
    current_timetables = response;
    stringstream in_ss(response.c_str());
    while (getline(in_ss, response, '|'))
        in_parts.push_back(response);

    if (in_parts.size() == 2) {
        QMessageBox::warning(this, "Warning", "No Public Tables");
        ui->stackedWidget->setCurrentIndex(4);
        return;
    }

    for (int i=2; i < in_parts.size(); i++) {
        vector<string> table_parts;
        string table_string = in_parts.at(i);
        stringstream table_ss(table_string.c_str());
        while (getline(table_ss, table_string, '&'))
            table_parts.push_back(table_string);
        string table_name = table_parts.at(0);
        ui->comboBox->addItem(QString::fromStdString(table_name));
    }
}
/**
 * @brief Allows user to view private time tables
 *
 * @author   John Jewell
 * @author   John Jewell
 * @date     30/11/2019
 */
void MainWindow::on_pushButton_12_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
    current_type = "shared";
    current_type_str_int = "1";
    string request, response;
    vector<string> in_parts, out_parts;

    request = "GET TIMETABLE|1|" + current_user;
    stringstream out_ss (request.c_str());
    while (getline(out_ss, request, '|'))
        out_parts.push_back(request);

    response = timetable_get(out_parts);
    current_timetables = response;
    stringstream in_ss(response.c_str());
    while (getline(in_ss, response, '|'))
        in_parts.push_back(response);

    if (in_parts.size() == 2) {
        QMessageBox::warning(this, "Warning", "No Public Tables");
        ui->stackedWidget->setCurrentIndex(4);
        return;
    }

    for (int i=2; i < in_parts.size(); i++) {
        vector<string> table_parts;
        string table_string = in_parts.at(i);
        stringstream table_ss(table_string.c_str());
        while (getline(table_ss, table_string, '&'))
            table_parts.push_back(table_string);
        string table_name = table_parts.at(0);
        ui->comboBox->addItem(QString::fromStdString(table_name));
    }
}

/**
 * @brief Brings user to create event screen
 *
 * @author   John Jewell
 * @author   John Jewell
 * @date     30/11/2019
 */
void MainWindow::on_toolButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(7);
}

/**
 * @brief Allows user to create event
 *
 * @author   John Jewell
 * @author   John Jewell
 * @date     30/11/2019
 */
void MainWindow::on_pushButton_14_clicked()
{
    string name = ui->lineEdit_6->text().toStdString();
    string details = ui->lineEdit_7->text().toStdString();
    string repeat_type = "NONE";
    if (name == "" || details == "") {
        QMessageBox::warning(this, "Warning", "Event cannot span multiple days");
        return;
    }
    time_t start_time = QDateTime(ui->dateTimeEdit->dateTime()).toTime_t();
    time_t end_time = QDateTime(ui->dateTimeEdit->dateTime()).toTime_t();
    string start_time_t_string = to_string(start_time);
    string end_time_t_string = to_string(end_time);
    char *start_time_chararr = ctime(&start_time);
    char *end_time_chararr = ctime(&end_time);

    string start_time_string = "";
    for (int i = 0; i < strlen(start_time_chararr); i++)
        start_time_string += start_time_chararr[i];

    string end_time_string = "";
    for (int i = 0; i < strlen(end_time_chararr); i++)
         end_time_string += end_time_chararr[i];

    vector<string> start_parts, end_parts;
    stringstream start_ss(start_time_string);
    while (getline(start_ss, start_time_string, ' '))
        start_parts.push_back(start_time_string);

    stringstream end_ss(end_time_string);
    while (getline(end_ss, end_time_string, ' '))
        end_parts.push_back(end_time_string);


    if (start_parts.at(1) != end_parts.at(1) || start_parts.at(2) != end_parts.at(2) || start_parts.at(4) != end_parts.at(4)) {
        QMessageBox::warning(this, "Warning", "Event cannot span multiple days");
        return;
    }

    string type;
    if (current_type == "shared" || current_type == "public")
        type = "public";
    else
        type = "private";


    string request, response;
    vector<string> in_parts, out_parts;
    request = "CREATE_EVENT|" + name + "|" + details + "|" + start_time_t_string + "|" + end_time_t_string + "|" + type + "|" + current_user + "|" + repeat_type;
    stringstream out_ss (request.c_str());
    while (getline(out_ss, request, '|'))
        out_parts.push_back(request);

    response = event_create(out_parts);
    stringstream in_ss(response.c_str());
    while (getline(in_ss, response, '|'))
        in_parts.push_back(response);

    if(in_parts.at(1).compare("SUCCESS") != 0) {
        QMessageBox::warning(this, "Warning", "Could not create event");
        return;
    }


    string request2, response2;
    vector<string> in_parts2, out_parts2;

    request2 = "ADD EVENT|" + current_table_name + "|" + name + "^" + details + "^" + start_time_t_string + "^" + end_time_t_string + "^" + type + "^" + current_user + "^" + repeat_type;
    stringstream out_ss2 (request2.c_str());
    while (getline(out_ss2, request2, '|'))
        out_parts2.push_back(request2);

    response2 = event_add(out_parts2);
    stringstream in_ss2(response2.c_str());
    while (getline(in_ss2, response2, '|'))
        in_parts2.push_back(response2);

    if(in_parts2.at(1).compare("SUCCESS") != 0) {
        QMessageBox::warning(this, "Warning", "Could not create event");
        return;
    }

    ui->stackedWidget->setCurrentIndex(6);

}

/**
 * @brief Brings user back to view timetable from events scren
 *
 * @author   John Jewell
 * @author   John Jewell
 * @date     30/11/2019
 */
void MainWindow::on_pushButton_15_clicked()
{
    ui->stackedWidget->setCurrentIndex(6);
}

