/* Class to terminate control
 * CREATED BY: Vladimir Zhurov
 * LAST EDITED BY: Vladimir Zhurov
 * LAST EDITED: 28/10/2019
 * TODO: NONE
 */

#include <iostream>
#include "unistd.h"
//#include "windows.h" //remove when on pi
#include "iostream"
#include "fstream"
#include "sstream"
#include "vector"
#include "string"

using namespace std;

static string GET_FILE = "getF.txt";

int main(){
    cout << "TERMINATION CALLED ON CALENDER PLANNER" << endl;
    ofstream out_stream(GET_FILE.c_str(), ios::app);
    if(out_stream.is_open()){
        out_stream << "TERMINATE\n";
        out_stream.close();
        cout << "TERMINATION CALL COMPLETE" << endl;
    }
    else
        cout << "TERMINATION CALL COULD NOT FIND INPUT FILE" << endl;
    return 0;
}
