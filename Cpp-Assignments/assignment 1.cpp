#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
using namespace std;

int main() {

// menu section diplaying the program options
menu:
    cout << "choose your option \n";
    cout << "1) calculate the error between the two sensors recordings and save in the error file \n";
    cout << "2) display the error file information \n";
    cout << "3) quit the program\n";
    int choice;
    cin >> choice; // prompting the user choice 

    if (choice == 1) {
        int tolerance;
        double timerecord = 0; // setting the initial time to 0
        string file1, file2;

        cout << "enter the tolerance value\n";
        cin >> tolerance;
        // to check the tolerance is positive value
        if (tolerance < 0) {
            cout << "invalid tolerance value\n";
            goto menu;
        }
        //ask for the files names and assign them as ifstream objects
        cout << "enter the two files names with extensions\n";
        cin >> file1 >> file2;
        ifstream f1(file1);
        ifstream f2(file2);
        ofstream fout("err.log");

        //check for possible errors in reading files
        if (f1.fail() || f2.fail()) {
            cerr << "could not open input files\n";
            goto menu;
        }
        //while condition to check which file ends first in case of different files sizes
        while (!f1.eof() && !f2.eof()) {
            double x1, y1, z1, x2, y2, z2, distance;
            f1 >> x1 >> y1 >> z1;
            f2 >> x2 >> y2 >> z2;
            timerecord += 0.25;
            distance = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2) + pow(z1 - z2, 2));
            // values of distance and time will be recorded in the err.log file only if the distance is larger than the tolerance
            if (distance > tolerance) {
                fout << distance << " " << timerecord << endl;
            }
        }
        goto menu;
    }
    else if (choice == 2) {
        // err.log file created as ifstream object to display the data
        ifstream fdisplay("err.log");
        //ifconditon to check that the err file exists
        if (fdisplay) {
            cout << setw(10) << "Distance" << setw(10) << "Time" << endl;
            double dist, time;
            //while there are values to take from the file, print them in tabular format
            while (fdisplay >> dist >> time) {
                cout << setw(10) << dist << setw(10) << time << endl;
            }
        }
        else {
            cout << "file does not exist\n";
            goto menu;
        }

    }
    else if (choice == 3) {
        cout << "Thanks for using this program... Program Exitted\n";
    }
    //in case of input other than the three options
    else {
        cout << "Invalid option\n";
        goto menu;
    }

}