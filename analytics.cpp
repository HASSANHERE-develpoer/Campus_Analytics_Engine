#include <iostream>
#include <fstream>
#include <string>
#include "analytics.h"
#include "filehandler.h"

using namespace std;

// 1. Course Average Marks Nikalne Ke Liye
double calculateCourseAverage(const string& courseCode) {
    ifstream file("marks.txt");
    if (!file.is_open()) return 0.0;

    string line;
    double totalMarks = 0.0;
    int studentCount = 0;

    getline(file, line); // Header skip kiya

    while (getline(file, line)) {
        if (line == "") continue;

        string c = getColumnValue(line, 1); // Course Code
        if (c == courseCode) {
            // string ko double me convert karne ke liye stod use kiya (Sir's style)
            string marksStr = getColumnValue(line, 2); // Marks Column
            totalMarks += stod(marksStr);
            studentCount++;
        }
    }
    file.close();

    if (studentCount == 0) return 0.0;
    return totalMarks / studentCount;
}


void findCourseTopper(const string& courseCode) {
    ifstream file("marks.txt");
    if (!file.is_open()) return;

    string line;
    double highestMarks = -1.0;
    string topperRoll = "N/A";

    getline(file, line); // Header skip

    while (getline(file, line)) {
        if (line == "") continue;

        string c = getColumnValue(line, 1);
        if (c == courseCode) {
            string r = getColumnValue(line, 0); // Roll No
            double currentMarks = stod(getColumnValue(line, 2));

            
            if (currentMarks > highestMarks) {
                highestMarks = currentMarks;
                topperRoll = r;
            }
        }
    }
    file.close();

    cout << "\n--- Course Topper for " << courseCode << " ---" << endl;
    cout << "Roll Number: " << topperRoll << " | Marks: " << highestMarks << endl;
}


void printPerformanceReport(const string& courseCode) {
    double avg = calculateCourseAverage(courseCode);
    
    cout << "\n=========================================" << endl;
    cout << "        PERFORMANCE ANALYTICS: " << courseCode << endl;
    cout << "=========================================" << endl;
    cout << "Class Average Marks: " << avg << endl;
    
    findCourseTopper(courseCode);
    cout << "=========================================" << endl;
}
