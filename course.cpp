#include <iostream>
#include <fstream>
#include <string>
#include "course.h"     
#include "student.h"    
#include "filehandler.h"
using namespace std;

// 1. Semester ke active credit hours calculate karna
int getCreditLoad(const string& rollNo, const string& semester) {
    ifstream file("enrollments.txt");
    if (!file.is_open()) return 0;

    int totalCredits = 0;
    string line;
    getline(file, line); 

    while (getline(file, line)) {
        if (line == "") continue;
        if (getColumnValue(line, 0) == rollNo && 
            getColumnValue(line, 2) == semester && 
            getColumnValue(line, 3) == "enrolled") {
            
            string cCode = getColumnValue(line, 1);
            ifstream cFile("courses.txt");
            if (cFile.is_open()) {
                string cLine;
                getline(cFile, cLine); 
                while (getline(cFile, cLine)) {
                    if (getColumnValue(cLine, 0) == cCode) {
                        try {
                            totalCredits += stoi(getColumnValue(cLine, 2));
                        } catch (...) {}
                        break;
                    }
                }
                cFile.close();
            }
        }
    }
    file.close();
    return totalCredits;
}

// 2. Prerequisite course clear hai ya nahi check karna
bool checkPrerequisite(const string& rollNo, const string& courseCode) {
    string prereqCode = "NONE";
    ifstream cFile("courses.txt");
    if (!cFile.is_open()) return true;
    
    string line;
    getline(cFile, line);
    while (getline(cFile, line)) {
        if (line == "") continue;
        if (getColumnValue(line, 0) == courseCode) {
            prereqCode = getColumnValue(line, 6); 
            break;
        }
    }
    cFile.close();

    if (prereqCode == "NONE" || prereqCode == "") return true;

    ifstream gFile("grades.txt");
    if (!gFile.is_open()) return false; 

    getline(gFile, line);
    while (getline(gFile, line)) {
        if (line == "") continue;
        if (getColumnValue(line, 0) == rollNo && getColumnValue(line, 1) == prereqCode) {
            string grade = getColumnValue(line, 2);
            if (grade != "F" && grade != "f") {
                gFile.close();
                return true; 
            }
        }
    }
    gFile.close();
    return false;
}

// 3. Course Enrollment Core Function
void enrollStudent() {
    string rollNo, courseCode, semester;
    cout << "\n--- Enroll Course Module ---" << endl;
    cout << "Enter Student Roll No: "; cin >> rollNo; clearInput();
    cout << "Enter Course Code: "; cin >> courseCode; clearInput();
    cout << "Enter Current Semester: "; cin >> semester; clearInput();

    Student stdObj;
    if (!searchByRoll(rollNo, stdObj) || stdObj.status != "active") {
        cout << "Error: Student profile is not active or missing!" << endl;
        return;
    }

    ifstream cFile("courses.txt");
    if (!cFile.is_open()) return;
    
    string line;
    bool courseExists = false;
    int maxSeats = 0, courseCredits = 0;
    
    getline(cFile, line);
    while (getline(cFile, line)) {
        if (line == "") continue;
        if (getColumnValue(line, 0) == courseCode) {
            courseExists = true;
            try {
                maxSeats = stoi(getColumnValue(line, 4)); 
                courseCredits = stoi(getColumnValue(line, 2)); 
            } catch (...) {
                maxSeats = 0;
                courseCredits = 0;
            }
            break;
        }
    }
    cFile.close();

    if (!courseExists) {
        cout << "Error: Target course code not found in directory!" << endl;
        return;
    }

    ifstream eFile("enrollments.txt");
    int enrolledCount = 0;
    bool alreadyEnrolled = false;
    
    if (eFile.is_open()) {
        getline(eFile, line);
        while (getline(eFile, line)) {
            if (line == "") continue;
            if (getColumnValue(line, 1) == courseCode && getColumnValue(line, 3) == "enrolled") {
                enrolledCount++;
            }
            if (getColumnValue(line, 0) == rollNo && getColumnValue(line, 1) == courseCode && getColumnValue(line, 3) == "enrolled") {
                alreadyEnrolled = true;
            }
        }
        eFile.close();
    }

    if (alreadyEnrolled) {
        cout << "Error: Student is already actively enrolled in this course!" << endl;
        return;
    }
    if (enrolledCount >= maxSeats) {
        cout << "Error: Allocation failed! Course sections are fully full." << endl;
        return;
    }

    int currentLoad = getCreditLoad(rollNo, semester);
    if (currentLoad + courseCredits > 21) {
        cout << "Error: Term overload! Maximum limit of 21 credit hours exceeded." << endl;
        return;
    }

    if (!checkPrerequisite(rollNo, courseCode)) {
        cout << "Error: Prerequisite course checking failed!" << endl;
        return;
    }

    ofstream outFile("enrollments.txt", ios::app);
    if (outFile.is_open()) {
        outFile << rollNo << "," << courseCode << "," << semester << ",enrolled\n";
        outFile.close();
        cout << "Success: Course assignment updated in enrollment logs." << endl;
    }
}

// 4. Drop Course Module
void dropCourse() {
    string rollNo, courseCode, semester;
    cout << "\n--- Drop Course Module ---" << endl;
    cout << "Enter Student Roll No: "; cin >> rollNo; clearInput();
    cout << "Enter Course Code: "; cin >> courseCode; clearInput();
    cout << "Enter Current Semester: "; cin >> semester; clearInput();

    ifstream attFile("attendance_log.txt");
    if (attFile.is_open()) {
        string line;
        getline(attFile, line);
        while (getline(attFile, line)) {
            if (line == "") continue;
            if (getColumnValue(line, 0) == rollNo && getColumnValue(line, 1) == courseCode) {
                cout << "Error: Drop request rejected! Attendance logs exist for this instance." << endl;
                attFile.close();
                return;
            }
        }
        attFile.close();
    }

    ifstream file("enrollments.txt");
    ofstream temp("temp_enrollments.txt");
    if (!file.is_open() || !temp.is_open()) return;

    string line;
    getline(file, line);
    temp << line << "\n"; 

    bool found = false;
    while (getline(file, line)) {
        if (line == "") continue;
        string fRoll = getColumnValue(line, 0);
        string fCourse = getColumnValue(line, 1);
        string fSem = getColumnValue(line, 2);
        string fStatus = getColumnValue(line, 3);

        if (fRoll == rollNo && fCourse == courseCode && fSem == semester && fStatus == "enrolled") {
            fStatus = "dropped"; 
            found = true;
        }
        temp << fRoll << "," << fCourse << "," << fSem << "," << fStatus << "\n";
    }
    file.close();
    temp.close();
    remove("enrollments.txt");
    rename("temp_enrollments.txt", "enrollments.txt");

    if (found) cout << "Success: Enrollment instance dropped safely." << endl;
    else cout << "Notification: No matching active enrollment record found." << endl;
}

// 5. Course me Enrolled Active Students Display Karna
void listEnrolledStudents() {
    string courseCode;
    cout << "Enter Course Code: "; cin >> courseCode; clearInput();

    ifstream file("enrollments.txt");
    if (!file.is_open()) return;

    string line;
    getline(file, line);
    cout << "\n--- Enrolled Members Vector (" << courseCode << ") ---" << endl;
    
    int count = 0;
    while (getline(file, line)) {
        if (line == "") continue;
        if (getColumnValue(line, 1) == courseCode && getColumnValue(line, 3) == "enrolled") {
            string roll = getColumnValue(line, 0);
            Student std;
            if (searchByRoll(roll, std)) {
                cout << ++count << ". " << std.roll << " \t " << std.name << " [" << std.dept << "]" << endl;
            }
        }
    }
    file.close();
    if (count == 0) cout << "No student records associated with this course asset." << endl;
}