#ifndef ATTENDANCE_H
#define ATTENDANCE_H

#include <iostream>
#include <string>

using namespace std;

void markAttendance(const string& rollNo, const string& courseCode, const string& status);
double calculateAttendancePercentage(const string& rollNo, const string& courseCode);
void generateAttendanceReport(const string& courseCode);

#endif
