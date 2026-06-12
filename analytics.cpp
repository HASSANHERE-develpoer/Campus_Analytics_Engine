#include <iostream>
#include <fstream>
#include <string>
#include "analytics.h"
#include "filehandler.h"

using namespace std;

// 1. Course Average Marks: enrollments.txt se kisi CourseID ka average nikalna
double calculateCourseAverage(const string& courseId) {
    ifstream file("enrollments.txt");
    if (!file.is_open()) return 0.0;

    string line;
    double totalMarks = 0.0;
    int studentCount = 0;

    getline(file, line); // Header skip kiya

    while (getline(file, line)) {
        if (line == "") continue;

        //  Column 2 is CourseID, Column 3 is Marks
        string currentCourseId = getColumnValue(line, 2); 
        if (currentCourseId == courseId) {
            string marksStr = getColumnValue(line, 3); // Marks
            totalMarks += stod(marksStr);
            studentCount++;
        }
    }
    file.close();

    if (studentCount == 0) return 0.0;
    return totalMarks / studentCount;
}

// 2. Class Ka Topper: enrollments.txt me se highest marks wala StudentID dhoondna
void findCourseTopper(const string& courseId) {
    ifstream file("enrollments.txt");
    if (!file.is_open()) return;

    string line;
    double highestMarks = -1.0;
    string topperStudentId = "N/A";

    getline(file, line); // Header skip

    while (getline(file, line)) {
        if (line == "") continue;

        string currentCourseId = getColumnValue(line, 2);
        if (currentCourseId == courseId) {
            string studentId = getColumnValue(line, 1); // StudentID
            double currentMarks = stod(getColumnValue(line, 3)); // Marks

            if (currentMarks > highestMarks) {
                highestMarks = currentMarks;
                topperStudentId = studentId;
            }
        }
    }
    file.close();

    cout << "\n--- Course Topper for " << courseId << " ---" << endl;
    cout << "Student ID: " << topperStudentId << " | Highest Marks: " << highestMarks << endl;
}

// 3. Performance Summary Print Karna
void printPerformanceReport(const string& courseId) {
    double avg = calculateCourseAverage(courseId);
    
    cout << "\n=========================================" << endl;
    cout << "        PERFORMANCE ANALYTICS: " << courseId << endl;
    cout << "=========================================" << endl;
    cout << "Class Average Marks: " << avg << endl;
    
    findCourseTopper(courseId);
    cout << "=========================================" << endl;
}
