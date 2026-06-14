#include <iostream>
#include <fstream>
#include <string>
#include "attendance.h"
#include "filehandler.h"

using namespace std;

void markAttendance(const string& rollNo, const string& courseCode, const string& status) {
    ofstream file("attendance_log.txt", ios::app);
    if (!file.is_open()) return;
    file << rollNo << "," << courseCode << ",14-06-2026," << status << "\n";
    file.close();
    cout << "\nAttendance marked as [" << status << "] for " << rollNo << endl;
}

void viewAttendanceReport(const string& rollNo) {
    ifstream file("attendance_log.txt");
    if (!file.is_open()) return;
    string line; getline(file, line);
    cout << "\n--- ATTENDANCE LOG ---" << endl;
    while (getline(file, line)) {
        if (line == "") continue;
        if (getColumnValue(line, 0) == rollNo) {
            cout << "Course: " << getColumnValue(line, 1) << " | Date: " << getColumnValue(line, 2) << " | Status: " << getColumnValue(line, 3) << endl;
        }
    }
    file.close();
}
