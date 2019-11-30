 /**
  * @brief A termination process for the main program
  *
  * A program that sends a terminate message to the main program through its get file
  * @author  Vladimir Zhurov
  * @date   28/10/2019
 */

#include <iostream>
#include "unistd.h"
#include "iostream"
#include "fstream"
#include "sstream"
#include "vector"
#include "string"

using namespace std;

static string GET_FILE = "getF.txt";

/**
 * @brief A termination process for the main program
 *
 * A program that sends a terminate message to the main program through its get file
 * @author  Vladimir Zhurov
 * @date   28/10/2019
*/
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
