#include <iostream>
#include <fstream>
#include <string>
#include "attendance.h"
#include "filehandler.h"

using namespace std;

// 1. Mark Attendance: Sir ki file me columns hain -> LogID,EnrollmentID,Date,Status
void markAttendance(const string& logId, const string& enrollId, const string& date, const string& status) {
    // Columns ko comma se jor kar line banayi
    string row = logId + "," + enrollId + "," + date + "," + status;
    
    // Asal file attendance_log.txt me save kar diya
    appendTXT("attendance_log.txt", row);
    cout << "Attendance logged successfully for Enrollment ID: " << enrollId << endl;
}

// 2. Calculate Percentage: Loop chala kar kisi 1 Enrollment ID ki percentage nikalna
double calculateAttendancePercentage(const string& enrollId) {
    ifstream file("attendance_log.txt");
    if (!file.is_open()) return 0.0;

    string line;
    int total = 0;
    int present = 0;

    getline(file, line); // Header line skip ki

    while (getline(file, line)) {
        if (line == "") continue;

        // Sir ki file ke mutabiq: Column 1 is EnrollmentID, Column 3 is Status
        string currentEnrollId = getColumnValue(line, 1); 
        string currentStatus = getColumnValue(line, 3); 

        if (currentEnrollId == enrollId) {
            total++; 
            if (currentStatus == "Present" || currentStatus == "P" || currentStatus == "p") {
                present++; 
            }
        }
    }
    file.close();

    if (total == 0) return 0.0;
    return ((double)present / total) * 100.0; 
}

// 3. Generate Report: Sir ki file ka data saaf suthra screen par dikhana
void generateAttendanceReport(const string& enrollId) {
    ifstream file("attendance_log.txt");
    if (!file.is_open()) return;

    string line;
    cout << "\n--- Attendance Log for Enrollment ID: " << enrollId << " ---" << endl;
    cout << "Log ID\t\tDate\t\tStatus" << endl;
    cout << "-------------------------------------------" << endl;

    getline(file, line); 

    while (getline(file, line)) {
        if (line == "") continue;

        string currentEnrollId = getColumnValue(line, 1);
        if (currentEnrollId == enrollId) {
            string logId = getColumnValue(line, 0);
            string date = getColumnValue(line, 2);
            string status = getColumnValue(line, 3);
            cout << logId << "\t\t" << date << "\t\t" << status << endl;
        }
    }
    file.close();
}
