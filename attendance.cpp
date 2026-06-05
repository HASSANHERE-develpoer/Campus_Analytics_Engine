#include <iostream>
#include <fstream>
#include <string>
#include "attendance.h"
#include "filehandler.h"

using namespace std;

// 1. Mark Attendance: User ka data file me jor kar likhna
void markAttendance(const string& rollNo, const string& courseCode, const string& status) {
    string row = rollNo + "," + courseCode + "," + status;
    appendTXT("attendance.txt", row);
    cout << "Attendance marked for " << rollNo << endl;
}

// 2. Calculate Percentage: Loop chala kar ginti karna
double calculateAttendancePercentage(const string& rollNo, const string& courseCode) {
    ifstream file("attendance.txt");
    if (!file.is_open()) return 0.0;

    string line;
    int total = 0;
    int present = 0;

    getline(file, line); // Pehli line (Header) skip kar di

    while (getline(file, line)) {
        if (line == "") continue;

        string r = getColumnValue(line, 0); 
        string c = getColumnValue(line, 1); 
        string s = getColumnValue(line, 2); 

        if (r == rollNo && c == courseCode) {
            total++; 
            if (s == "P" || s == "p") {
                present++; 
            }
        }
    }
    file.close();

    if (total == 0) return 0.0;
    return ((double)present / total) * 100.0; 
}

// 3. Generate Report: Screen par show karna
void generateAttendanceReport(const string& courseCode) {
    ifstream file("attendance.txt");
    if (!file.is_open()) return;

    string line;
    cout << "\n--- Attendance Report for " << courseCode << " ---" << endl;
    cout << "Roll No\t\tStatus" << endl;
    cout << "-----------------------------------" << endl;

    getline(file, line); 

    while (getline(file, line)) {
        if (line == "") continue;

        string c = getColumnValue(line, 1);
        if (c == courseCode) {
            string r = getColumnValue(line, 0);
            string s = getColumnValue(line, 2);
            cout << r << "\t\t" << s << endl;
        }
    }
    file.close();
}
