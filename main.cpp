#include "mainwindow.h"
#include <QApplication>

/**
 * @brief The main process for the system that spawns threads to deal with individual users
 *
 * The main process initilizeses all of the required managers and then begins to wait on the GET_FILE
 *      The user console will write a pid to the GET_FILE when this occours main will spawns a thread with the pid as argument and clear GET_FILE
 * @author  Vladimir Zhurov
 * @date    25/11/2019
 */
int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
