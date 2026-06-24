#include <iostream>
#include <fstream>
#include <string>
#include "course.h"     
#include "student.h"    
#include "filehandler.h"
using namespace std;

// 1. Semester ke active credit hours calculate karna (Max 21 validation ke liye)[span_10](start_span)[span_10](end_span)
int getCreditLoad(const string& rollNo, const string& semester) {
    ifstream file("enrollments.txt");
    if (!file.is_open()) return 0;

    int totalCredits = 0;
    string line;
    getline(file, line); // Header skip[span_11](start_span)[span_11](end_span)

    while (getline(file, line)) {
        if (line == "") continue;
        
        // roll(0), course_code(1), semester(2), status(3)[span_12](start_span)[span_12](end_span)
        if (getColumnValue(line, 0) == rollNo && 
            getColumnValue(line, 2) == semester && 
            getColumnValue(line, 3) == "enrolled") {
            
            string cCode = getColumnValue(line, 1);
            
            // Course ke credit hours dhoondne ke liye courses.txt scan karein[span_13](start_span)[span_13](end_span)
            ifstream cFile("courses.txt");
            if (cFile.is_open()) {
                string cLine;
                getline(cFile, cLine); // skip header
                while (getline(cFile, cLine)) {
                    // code(0), title(1), credits(2)[span_14](start_span)[span_14](end_span)
                    if (getColumnValue(cLine, 0) == cCode) {
                        try {
                            totalCredits += stoi(getColumnValue(cLine, 2));
                        } catch (...) {
                            // Bulletproof protection against bad strings[span_15](start_span)[span_15](end_span)
                        }
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

// 2. Prerequisite course clear hai ya nahi check karna[span_16](start_span)[span_16](end_span)
bool checkPrerequisite(const string& rollNo, const string& courseCode) {
    string prereqCode = "NONE";
    
    // Pehle course ka prereq dhoondein courses.txt se[span_17](start_span)[span_17](end_span)
    ifstream cFile("courses.txt");
    if (!cFile.is_open()) return true;
    
    string line;
    getline(cFile, line);
    while (getline(cFile, line)) {
        if (line == "") continue;
        if (getColumnValue(line, 0) == courseCode) {
            prereqCode = getColumnValue(line, 6); // Sahi Column index 6 kiya (Prereq field)[span_18](start_span)[span_18](end_span)
            break;
        }
    }
    cFile.close();

    if (prereqCode == "NONE" || prereqCode == "") return true;

    // Agar prerequisite hai, to grades.txt me check karein ke pass (Non-F) hai ya nahi[span_19](start_span)[span_19](end_span)
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

// 3. Course Enrollment Core Function[span_20](start_span)[span_20](end_span)
void enrollStudent() {
    string rollNo, courseCode, semester;
    cout << "\n--- Enroll Course Module ---" << endl;
    cout << "Enter Student Roll No: ";
    cin >> rollNo;
    cout << "Enter Course Code: ";
    cin >> courseCode;
    cout << "Enter Current Semester: ";
    cin >> semester;

    // Check 1: Student Active check[span_21](start_span)[span_21](end_span)
    Student stdObj;
    if (!searchByRoll(rollNo, stdObj) || stdObj.status != "active") {
        cout << "Error: Student profile is not active or missing!" << endl;
        return;
    }

    // Check 2: Course existence & capacity evaluation[span_22](start_span)[span_22](end_span)
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
                maxSeats = stoi(getColumnValue(line, 4)); // Sahi Column index 4 kiya (Seats capacity)[span_23](start_span)[span_23](end_span)
                courseCredits = stoi(getColumnValue(line, 2)); // Column index 2 is credit hours[span_24](start_span)[span_24](end_span)
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

    // Check 3: Seat availability check[span_25](start_span)[span_25](end_span)
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

    // Check 4: Credit limits load validation[span_26](start_span)[span_26](end_span)
    int currentLoad = getCreditLoad(rollNo, semester);
    if (currentLoad + courseCredits > 21) {
        cout << "Error: Term overload! Maximum limit of 21 credit hours exceeded." << endl;
        return;
    }

    // Check 5: Prerequisite check[span_27](start_span)[span_27](end_span)
    if (!checkPrerequisite(rollNo, courseCode)) {
        cout << "Error: Prerequisite course checking failed!" << endl;
        return;
    }

    // All clear, write enrollment entry[span_28](start_span)[span_28](end_span)
    ofstream outFile("enrollments.txt", ios::app);
    if (outFile.is_open()) {
        outFile << rollNo << "," << courseCode << "," << semester << ",enrolled\n";
        outFile.close();
        cout << "Success: Course assignment updated in enrollment logs." << endl;
    }
}

// 4. Drop Course Module[span_29](start_span)[span_29](end_span)
void dropCourse() {
    string rollNo, courseCode, semester;
    cout << "\n--- Drop Course Module ---" << endl;
    cout << "Enter Student Roll No: ";
    cin >> rollNo;
    cout << "Enter Course Code: ";
    cin >> courseCode;
    cout << "Enter Current Semester: ";
    cin >> semester;

    // Check: Agar attendance registry me traces hain, to course drop nahi ho sakta[span_30](start_span)[span_30](end_span)
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

    // File rewriting to flip active enrollment state[span_31](start_span)[span_31](end_span)
    ifstream file("enrollments.txt");
    ofstream temp("temp_enrollments.txt");
    if (!file.is_open() || !temp.is_open()) return;

    string line;
    getline(file, line);
    temp << line << "\n"; // Header save

    bool found = false;
    while (getline(file, line)) {
        if (line == "") continue;
        string fRoll = getColumnValue(line, 0);
        string fCourse = getColumnValue(line, 1);
        string fSem = getColumnValue(line, 2);
        string fStatus = getColumnValue(line, 3);

        if (fRoll == rollNo && fCourse == courseCode && fSem == semester && fStatus == "enrolled") {
            fStatus = "dropped"; // Soft state flip[span_32](start_span)[span_32](end_span)
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

// 5. Course me Enrolled Active Students Display Karna[span_33](start_span)[span_33](end_span)
void listEnrolledStudents() {
    string courseCode;
    cout << "Enter Course Code: ";
    cin >> courseCode;

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