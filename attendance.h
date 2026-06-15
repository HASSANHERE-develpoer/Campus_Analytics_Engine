#ifndef ATTENDANCE_H
#define ATTENDANCE_H

#include <string>
using namespace std;

struct TempAttendance {
    string roll;
    string course;
    string date;
    string status;
};

void markAttendance();
double getAttendancePct(const string& rollNo, const string& courseCode);
void getShortageList();
bool undoLastSession();
void printDailySheet();

#endif
