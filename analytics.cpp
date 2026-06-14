#include <iostream>
#include <fstream>
#include <string>
#include "analytics.h"
#include "filehandler.h"

using namespace std;

// 1. Course Average Attendance: attendance_log.txt se poori class ki average attendance nikalna
double calculateCourseAverage(const string& courseCode) {
    ifstream file("attendance_log.txt");
    if (!file.is_open()) return 0.0;

    string line;
    int totalSessions = 0;
    int totalPresents = 0;

    getline(file, line); // Header line skip ki

    while (getline(file, line)) {
        if (line == "") continue;

        // Corrected Column Indexes according to attendance.cpp:
        // RollNo(0), CourseCode(1), Date(2), Status(3)
        string currentCourse = getColumnValue(line, 1);
        if (currentCourse == courseCode) {
            totalSessions++;
            string status = getColumnValue(line, 3);
            if (status == "P" || status == "p" || status == "Present" || status == "present") {
                totalPresents++;
            }
        }
    }
    file.close();

    if (totalSessions == 0) return 0.0;
    return ((double)totalPresents / totalSessions) * 100.0;
}

// 2. Class Topper: Kisi course me sab se zyada Present hone wala Roll No dhoondna
void findCourseTopper(const string& courseCode) {
    ifstream file("attendance_log.txt");
    if (!file.is_open()) return;

    string line;
    // Structural parallel arrays for tracking (Strictly no vectors/OOP)
    string students[100];
    int presents[100] = {0};
    int studentCount = 0;

    getline(file, line); // Header skip

    while (getline(file, line)) {
        if (line == "") continue;

        // Corrected Indexes: CourseCode is 1, RollNo is 0, Status is 3
        string currentCourse = getColumnValue(line, 1);
        if (currentCourse == courseCode) {
            string rollNo = getColumnValue(line, 0);
            string status = getColumnValue(line, 3);

            // Check karo agar student pehle se array me hai
            int foundIndex = -1;
            for (int i = 0; i < studentCount; i++) {
                if (students[i] == rollNo) {
                    foundIndex = i;
                    break;
                }
            }

            // Agar naya student hai aur arrays me space hai toh add karo
            if (foundIndex == -1 && studentCount < 100) {
                foundIndex = studentCount;
                students[studentCount] = rollNo;
                studentCount++;
            }

            // Agar student safely track ho raha hai toh uski presence plus karo
            if (foundIndex != -1) {
                if (status == "P" || status == "p" || status == "Present" || status == "present") {
                    presents[foundIndex]++;
                }
            }
        }
    }
    file.close();

    // Highest presence calculate karna
    int maxPresents = -1;
    string topperRoll = "N/A";
    for (int i = 0; i < studentCount; i++) {
        if (presents[i] > maxPresents) {
            maxPresents = presents[i];
            topperRoll = students[i];
        }
    }

    cout << "\n--- Course Performance Topper (" << courseCode << ") ---" << endl;
    cout << "Top Active Student (Roll No): " << topperRoll << " | Total Classes Attended: " << maxPresents << endl;
}

void printPerformanceReport(const string& courseCode) {
    double avgAttendance = calculateCourseAverage(courseCode);
    
    cout << "\n=========================================" << endl;
    cout << "       ATTENDANCE ANALYTICS: " << courseCode << endl;
    cout << "=========================================" << endl;
    cout << "Overall Class Average Attendance: " << avgAttendance << "%" << endl;
    
    findCourseTopper(courseCode);
    cout << "=========================================" << endl;
}
