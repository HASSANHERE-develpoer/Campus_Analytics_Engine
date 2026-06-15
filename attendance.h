#ifndef ATTENDANCE_H
#define ATTENDANCE_H

#include <string>
using namespace std;

void markAttendance(const string& rollNo,
                    const string& courseCode,
                    const string& status);

void viewAttendanceReport(const string& rollNo);

#endif
