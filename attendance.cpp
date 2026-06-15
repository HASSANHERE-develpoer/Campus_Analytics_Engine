#include <iostream>
#include <fstream>
#include <string>
#include "attendance.h"
#include "student.h"    
#include "filehandler.h"
using namespace std;

// Last marked session state logging track arrays (Backup Simulator for Undo) 
TempAttendance backupBuffer[100];
int backupCount = 0;
bool standardBackupAvailable = false;

// 1. Mark Attendance Routine 
void markAttendance() {
    string courseCode, sessionDate;
    cout << "\n--- Attendance Call Manager ---" << endl;
    cout << "Enter Course Code: ";
    cin >> courseCode;
    cout << "Enter Session Date (DD-MM-YYYY): ";
    cin >> sessionDate;

    ifstream file("enrollments.txt");
    if (!file.is_open()) return;

    string line;
    getline(file, line); // Skip Header

    // Reset old state data tracking backup pointers 
    backupCount = 0; 

    while (getline(file, line)) {
        if (line == "") continue;
        if (getColumnValue(line, 1) == courseCode && getColumnValue(line, 3) == "enrolled") {
            string rollNo = getColumnValue(line, 0);
            Student stdObj;
            if (searchByRoll(rollNo, stdObj) && stdObj.status == "active") {
                string statusInput;
                cout << "Roll: " << rollNo << " | Name: " << stdObj.name << " (P/A/L): ";
                cin >> statusInput;

                // Validate input formats manually 
                while (statusInput != "P" && statusInput != "A" && statusInput != "L" &&
                       statusInput != "p" && statusInput != "a" && statusInput != "l") {
                    cout << "Invalid status context! Re-enter (P/A/L): ";
                    cin >> statusInput;
                }

                // Add to temporary local runtime structure array 
                if (backupCount < 100) {
                    backupBuffer[backupCount].roll = rollNo;
                    backupBuffer[backupCount].course = courseCode;
                    backupBuffer[backupCount].date = sessionDate;
                    backupBuffer[backupCount].status = statusInput;
                    backupCount++;
                }
            }
        }
    }
    file.close();

    if (backupCount == 0) {
        cout << "No active enrolled student entities target detected for processing." << endl;
        return;
    }

    // Flush runtime structures to storage logs [cite: 34, 67]
    ofstream logFile("attendance_log.txt", ios::app);
    if (!logFile.is_open()) return;

    for (int i = 0; i < backupCount; i++) {
        logFile << backupBuffer[i].roll << "," 
                << backupBuffer[i].course << "," 
                << backupBuffer[i].date << "," 
                << backupBuffer[i].status << "\n";
    }
    logFile.close();
    standardBackupAvailable = true; // Flag snapshot stored securely 
    cout << "Success: Course attendance logged successfully. Snapshot cached." << endl;
}

// 2. Attendance % Calculator Loop 
double getAttendancePct(const string& rollNo, const string& courseCode) {
    ifstream file("attendance_log.txt");
    if (!file.is_open()) return 0.0;

    string line;
    getline(file, line); // header

    int totalSessions = 0;
    double presentWeight = 0.0;

    while (getline(file, line)) {
        if (line == "") continue;
        if (getColumnValue(line, 0) == rollNo && getColumnValue(line, 1) == courseCode) {
            totalSessions++;
            string status = getColumnValue(line, 3);
            if (status == "P" || status == "p") {
                presentWeight += 1.0;
            } else if (status == "L" || status == "l") {
                presentWeight += 0.5; // 0.5 Late allocation formula 
            }
        }
    }
    file.close();

    if (totalSessions == 0) return 100.0; // Return full default status if no session data captured yet
    return (presentWeight / totalSessions) * 100.0;
}

// 3. Shortage Defaulters List (<75%) 
void getShortageList() {
    string courseCode;
    cout << "Enter Course Code to check shortages: ";
    cin >> courseCode;

    ifstream file("enrollments.txt");
    if (!file.is_open()) return;

    string line;
    getline(file, line);
    cout << "\n--- Attendance Defaulters List (< 75%) ---" << endl;

    while (getline(file, line)) {
        if (line == "") continue;
        if (getColumnValue(line, 1) == courseCode && getColumnValue(line, 3) == "enrolled") {
            string rollNo = getColumnValue(line, 0);
            double pct = getAttendancePct(rollNo, courseCode);
            if (pct < 75.0) {
                Student std;
                searchByRoll(rollNo, std);
                cout << rollNo << " | " << std.name << " | Percentage: " << pct << "%" << endl;
            }
        }
    }
    file.close();
}

// 4. Undo Last Marked Session 
bool undoLastSession() {
    if (!standardBackupAvailable || backupCount == 0) {
        cout << "System Error: No valid session cached in local application memory!" << endl;
        return false;
    }

    ifstream file("attendance_log.txt");
    ofstream temp("temp_attendance.txt");
    if (!file.is_open() || !temp.is_open()) return false;

    string line;
    getline(file, line);
    temp << line << "\n"; // Preserve header row [cite: 57]

    // Purani entries collect karte waqt un structural combinations ko drop karna jo snapshot matching me hain
    while (getline(file, line)) {
        if (line == "") continue;
        string fRoll = getColumnValue(line, 0);
        string fCourse = getColumnValue(line, 1);
        string fDate = getColumnValue(line, 2);

        bool matchedInBackup = false;
        for (int i = 0; i < backupCount; i++) {
            if (backupBuffer[i].roll == fRoll && backupBuffer[i].course == fCourse && backupBuffer[i].date == fDate) {
                matchedInBackup = true;
                break;
            }
        }

        if (!matchedInBackup) {
            temp << line << "\n";
        }
    }
    file.close();
    temp.close();
    remove("attendance_log.txt");
    rename("temp_attendance.txt", "attendance_log.txt");

    standardBackupAvailable = false; // Reset status flag state
    backupCount = 0;
    cout << "Success: Last interactive transaction rolled back across database logs." << endl;
    return true;
}

// 5. Print Daily Sheet Table Format 
void printDailySheet() {
    string courseCode, targetDate;
    cout << "Enter Course Code: ";
    cin >> courseCode;
    cout << "Enter Evaluation Date (DD-MM-YYYY): ";
    cin >> targetDate;

    ifstream file("attendance_log.txt");
    if (!file.is_open()) return;

    string line;
    getline(file, line);
    cout << "\n=============================================" << endl;
    cout << "   DAILY ATTENDANCE SHEET: " << courseCode << " (" << targetDate << ")" << endl;
    cout << "=============================================" << endl;
    cout << "Roll Number \t Status Context" << endl;
    cout << "---------------------------------------------" << endl;

    int totalInstances = 0;
    while (getline(file, line)) {
        if (line == "") continue;
        if (getColumnValue(line, 1) == courseCode && getColumnValue(line, 2) == targetDate) {
            cout << getColumnValue(line, 0) << " \t\t [" << getColumnValue(line, 3) << "]" << endl;
            totalInstances++;
        }
    }
    file.close();
    if (totalInstances == 0) cout << "No transactions processed under specific parameters." << endl;
    cout << "=============================================" << endl;
}
