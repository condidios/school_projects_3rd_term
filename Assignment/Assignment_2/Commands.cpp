#include "Commands.h"
#include <iostream>

using namespace std;

void Commands::printMenu() {
    cout << "____ Employee Recording System ____ \nPlease select for the following Menu Operation:\n1) Appointment of a new employee\n2) Appointment of a transferred employee\n"
            "3) Updating the title and salary coefficient of an employee\n4) Deletion of an employee\n"
            "5) Listing the information of an employee\n6) Listing employees ordered by employee number\n"
            "7) Listing employees ordered by appointment date\n8) Listing employees appointed after a certain date\n"
            "9) Listing employees assigned in a given year\n10) Listing employees born before a certain date\n"
            "11) Listing employees born in a particular month\n12) Listing the information of the last assigned employee with a given title\n";
}
int Commands::takeInput(){
    int input;
    cout << "\nPlease enter the number of operation you want to execute:";
    cin >> input;
    return input;
}
