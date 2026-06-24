#include <string>
#include <iostream>
#include "filehandler.h"
#include "student.h"    
#include "course.h"   
#include "attendance.h"
#include "auth.h"
#include "finance.h"    
#include "analytics.h"

using namespace std;
void displayMainMenu();
void studentMenu();
void courseMenu();
void attendanceMenu();
void gradeMenu();
void feeMenu();
void reportMenu();

int main() {
    int mainChoice = 0;
    while (true) {
        displayMainMenu();
        cout << "Enter Dashboard Selection Module: ";
        cin >> mainChoice;

        if (mainChoice == 7) {
            cout << "\nThank you for using Campus Analytics Engine. System shutting down cleanly." << endl;
            break;
        }

        switch (mainChoice) {
            case 1: studentMenu(); break;
            case 2: courseMenu(); break;
            case 3: attendanceMenu(); break;
            case 4: gradeMenu(); break;
            case 5: feeMenu(); break;
            case 6: reportMenu(); break;
            default: cout << "Invalid Selection routing context! Try again." << endl;
        }
    }
    return 0;
}

void displayMainMenu() {
    cout << "\n=============================================" << endl;
    cout << "      CAMPUS ANALYTICS ENGINE DASHBOARD      " << endl;
    cout << "=============================================" << endl;
    cout << "1. Student Profile Registry Management" << endl;
    cout << "2. Course Allocations & Prerequisites" << endl;
    cout << "3. Academic Attendance Tracker Sheet" << endl;
    cout << "4. Auth Grading & Performance Evaluation" << endl;
    cout << "5. Accounts Ledger & Fee Transactions" << endl;
    cout << "6. Institutional Analytics & Export Logs" << endl;
    cout << "7. Terminate Application Instance" << endl;
    cout << "=============================================" << endl;
}

void studentMenu() {
    int choice;
    while (true) {
        cout << "\n--- Student Registry Operations ---" << endl;
        cout << "1. Append New Student Profile" << endl;
        cout << "2. Search Profile by Roll Number" << endl;
        cout << "3. Search Profile Substring by Name" << endl;
        cout << "4. Update Profile Attribute Fields" << endl;
        cout << "5. Soft Delete Student Entry" << endl;
        cout << "6. Sort and Print Active Registry" << endl;
        cout << "7. Return to Main Dashboard Menu" << endl;
        cout << "Selection: ";
        cin >> choice;

        if (choice == 7) break;
        string inputStr;
        Student s;

        switch (choice) {
            case 1: addStudent(); break;
            case 2:
                cout << "Enter Roll Number to fetch: ";
                cin >> inputStr;
                if (searchByRoll(inputStr, s)) {
                    cout << "Found: " << s.name << " | Dept: " << s.dept << " | CGPA: " << s.cgpa << " | Status: " << s.status << endl;
                } else cout << "No profile asset mapped to roll number." << endl;
                break;
            case 3:
                cout << "Enter name prefix/substring: ";
                cin.ignore();
                getline(cin, inputStr);
                searchByName(inputStr);
                break;
            case 4: {
                int opt; string val;
                cout << "Enter Roll Number: "; cin >> inputStr;
                cout << "Select Field (1:Name, 2:Dept, 3:Semester, 4:CGPA): "; cin >> opt;
                cout << "Enter New Value string content: "; cin.ignore(); getline(cin, val);
                updateStudent(inputStr, opt, val);
                break;
            }
            case 5:
                cout << "Enter Target Roll Number to disconnect: "; cin >> inputStr;
                softDelete(inputStr);
                break;
            case 6: listActiveStudents(); break;
            default: cout << "Invalid operation configuration parameters!" << endl;
        }
    }
}

void courseMenu() {
    int choice;
    while (true) {
        cout << "\n--- Course Allocations Menu ---" << endl;
        cout << "1. Enroll Active Student into Course Allocation" << endl;
        cout << "2. Drop Course Allocation Instance" << endl;
        cout << "3. List Members Enrolled in Target Course Asset" << endl;
        cout << "4. Return to Main Dashboard Menu" << endl;
        cout << "Selection: "; cin >> choice;

        if (choice == 4) break;
        switch (choice) {
            case 1: enrollStudent(); break;
            case 2: dropCourse(); break;
            case 3: listEnrolledStudents(); break;
            default: cout << "Invalid allocation execution routing option!" << endl;
        }
    }
}

void attendanceMenu() {
    int choice;
    while (true) {
        cout << "\n--- Attendance Logs Sheet ---" << endl;
        cout << "1. Initialize Roll Call Session Mark" << endl;
        cout << "2. Print Daily Evaluation Session Sheet Table" << endl;
        cout << "3. Fetch Shortage Defaulters List (< 75%)" << endl;
        cout << "4. Revert/Undo Last Session Operations Snapshot" << endl;
        cout << "5. Return to Main Dashboard Menu" << endl;
        cout << "Selection: "; cin >> choice;

        if (choice == 5) break;
        switch (choice) {
            case 1: markAttendance(); break;
            case 2: printDailySheet(); break;
            case 3: getShortageList(); break;
            case 4: undoLastSession(); break;
            default: cout << "Invalid tracker matrix option context!" << endl;
        }
    }
}

void gradeMenu() {
    int choice;
    while (true) {
        cout << "\n--- Auth Evaluation & Grading Menu ---" << endl;
        cout << "1. Authorize Entry of Evaluated Student Marks" << endl;
        cout << "2. Compute Verified Class Analytical Statistics" << endl;
        cout << "3. Return to Main Dashboard Menu" << endl;
        cout << "Selection: "; cin >> choice;

        if (choice == 3) break;
        switch (choice) {
            case 1: enterMarks(); break;
            case 2: computeClassStats(); break;
            default: cout << "Invalid authorized evaluator option entry!" << endl;
        }
    }
}

void feeMenu() {
    int choice;
    while (true) {
        cout << "\n--- Accounts Ledger Desk ---" << endl;
        cout << "1. Log Received Balance Tuition Deposit" << endl;
        cout << "2. Print Official Formatted Fee Receipt Structure" << endl;
        cout << "3. Compile Delinquency Defaulters List Matrix" << endl;
        cout << "4. Return to Main Dashboard Menu" << endl;
        cout << "Selection: "; cin >> choice;

        if (choice == 4) break;
        switch (choice) {
            case 1: recordPayment(); break;
            case 2: generateReceipt(); break;
            case 3: getDefaulters(); break;
            default: cout << "Invalid ledger operational processing choice!" << endl;
        }
    }
}

void reportMenu() {
    int choice;
    while (true) {
        cout << "\n--- Analytics Insights Reports ---" << endl;
        cout << "1. Generate Institutional Departmental Headcount Summary" << endl;
        cout << "2. Print Top 10 High Academic Merit Standings" << endl;
        cout << "3. Export Core System State Diagnostics Document" << endl;
        cout << "4. Return to Main Dashboard Menu" << endl;
        cout << "Selection: "; cin >> choice;

        if (choice == 4) break;
        switch (choice) {
            case 1: generateDepartmentSummary(); break;
            case 2: generateMeritList(); break;
            case 3: exportSystemStatus(); break;
            default: cout << "Invalid insight reporting engine option selection!" << endl;
        }
    }
}