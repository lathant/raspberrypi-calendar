#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <unistd.h>
#include <string>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <sstream>
#include <vector>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_12_clicked();

    void on_toolButton_clicked();

    void on_pushButton_14_clicked();

    void on_pushButton_15_clicked();

private:
    Ui::MainWindow *ui;
    std::string current_user;
    std::string current_timetables;
    std::string current_table_name;
    std::string current_timetable;
    std::string current_type;
    std::string current_type_str_int;
    void update_table();

};

#endif // MAINWINDOW_H
