#ifndef ATTENDANCE_H
#define ATTENDANCE_H

#include <iostream>
#include <string>

using namespace std;


void markAttendance(const string& logId, const string& enrollId, const string& date, const string& status);
double calculateAttendancePercentage(const string& enrollId);
void generateAttendanceReport(const string& enrollId);

#endif
