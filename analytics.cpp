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

    getline(file, line); // Header skip

    while (getline(file, line)) {
        if (line == "") continue;

        // attendance_log.txt columns: log_id(0), roll_no(1), course_code(2), status(4)
        string currentCourse = getColumnValue(line, 2);
        if (currentCourse == courseCode) {
            totalSessions++;
            string status = getColumnValue(line, 4);
            if (status == "P" || status == "p" || status == "Present") {
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
    // Basic structural tracking arrays (No STL allowed)
    string students[100];
    int presents[100] = {0};
    int studentCount = 0;

    getline(file, line); // Header skip

    while (getline(file, line)) {
        if (line == "") continue;

        string currentCourse = getColumnValue(line, 2);
        if (currentCourse == courseCode) {
            string rollNo = getColumnValue(line, 1);
            string status = getColumnValue(line, 4);

            // Check karo agar student pehle se array me hai
            int foundIndex = -1;
            for (int i = 0; i < studentCount; i++) {
                if (students[i] == rollNo) {
                    foundIndex = i;
                    break;
                }
            }

            // Agar naya student hai toh array me add karo
            if (foundIndex == -1) {
                foundIndex = studentCount;
                students[studentCount] = rollNo;
                studentCount++;
            }

            if (status == "P" || status == "p" || status == "Present") {
                presents[foundIndex]++;
            }
        }
    }
    file.close();

    // Highest presence dhoondna
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
