#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "reports.h"
#include "student.h"
#include "filehandler.h"

using namespace std;

// 1. Department Summary Report: Average CGPA and Headcount
void generateDepartmentSummary() {
    ifstream file("students.txt");
    if (!file.is_open()) return;

    string line;
    getline(file, line); // Header skip

    string depts[50];
    double gpaSums[50] = {0};
    int counts[50] = {0};
    int distinctDepts = 0;

    while (getline(file, line)) {
        if (line == "") continue;
        if (getColumnValue(line, 5) != "active") continue;

        string dName = getColumnValue(line, 2);
        double cgpa = stod(getColumnValue(line, 4));

        // Manual search if department already indexed
        int foundIdx = -1;
        for (int i = 0; i < distinctDepts; i++) {
            if (depts[i] == dName) {
                foundIdx = i;
                break;
            }
        }

        if (foundIdx != -1) {
            gpaSums[foundIdx] += cgpa;
            counts[foundIdx]++;
        } else if (distinctDepts < 50) {
            depts[distinctDepts] = dName;
            gpaSums[distinctDepts] = cgpa;
            counts[distinctDepts] = 1;
            distinctDepts++;
        }
    }
    file.close();

    cout << "\n=====================================================" << endl;
    cout << "          INSTITUTIONAL DEPARTMENTAL SUMMARY         " << endl;
    cout << "=====================================================" << endl;
    cout << left << setw(25) << "Department Name" << setw(15) << "Total Students" << setw(15) << "Average CGPA" << endl;
    cout << "-----------------------------------------------------" << endl;

    for (int i = 0; i < distinctDepts; i++) {
        double avgGpa = gpaSums[i] / counts[i];
        cout << left << setw(25) << depts[i] 
             << setw(15) << counts[i] 
             << setw(15) << fixed << setprecision(2) << avgGpa << endl;
    }
    cout << "=====================================================" << endl;
}

// 2. Merit List Top Students (Sorted by CGPA using Bubble Sort)
void generateMeritList() {
    Student activeList[200];
    int count = 0;

    ifstream file("students.txt");
    if (!file.is_open()) return;

    string line;
    getline(file, line);

    while (getline(file, line) && count < 200) {
        if (line == "") continue;
        if (getColumnValue(line, 5) == "active") {
            activeList[count].roll = getColumnValue(line, 0);
            activeList[count].name = getColumnValue(line, 1);
            activeList[count].dept = getColumnValue(line, 2);
            activeList[count].semester = getColumnValue(line, 3);
            activeList[count].cgpa = stod(getColumnValue(line, 4));
            count++;
        }
    }
    file.close();

    if (count == 0) {
        cout << "No active student entries available to evaluate merit." << endl;
        return;
    }

    // Bubble Sort by CGPA Descending
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (activeList[j].cgpa < activeList[j + 1].cgpa) {
                Student temp = activeList[j];
                activeList[j] = activeList[j + 1];
                activeList[j + 1] = temp;
            }
        }
    }

    cout << "\n====================================================================" << endl;
    cout << "                       CAMPUS MERIT LOG (TOP 10)                    " << endl;
    cout << "====================================================================" << endl;
    cout << left << setw(5) << "Pos" << setw(15) << "Roll No" << setw(25) << "Student Name" << setw(10) << "CGPA" << endl;
    cout << "--------------------------------------------------------------------" << endl;

    int limit = (count < 10) ? count : 10;
    for (int i = 0; i < limit; i++) {
        cout << left << setw(5) << (i + 1) 
             << setw(15) << activeList[i].roll 
             << setw(25) << activeList[i].name 
             << setw(10) << fixed << setprecision(2) << activeList[i].cgpa << endl;
    }
    cout << "====================================================================" << endl;
}

// 3. Export System Audit Metrics to external text file
void exportSystemStatus() {
    ofstream out("system_export_report.txt");
    if (!out.is_open()) {
        cout << "Error creating export file asset." << endl;
        return;
    }

    out << "CAMPUS ANALYTICS ENGINE - DATA SUMMARY EXPORT\n";
    out << "Generated Security Timestamp Checkpoint context\n";
    out << "-----------------------------------------------------\n";

    // Count lines manually across registry assets
    string logs[] = {"students.txt", "courses.txt", "enrollments.txt", "attendance_log.txt", "fees.txt"};
    string titles[] = {"Total Registered Student Rows: ", "Total Loaded Course Assets: ", "Total Enrollment Mappings: ", "Total Attendance Logs Filed: ", "Total Financial Ledgers: "};

    for (int i = 0; i < 5; i++) {
        ifstream f(logs[i]);
        int count = 0;
        if (f.is_open()) {
            string l;
            getline(f, l); // header
            while (getline(f, l)) {
                if (l != "") count++;
            }
            f.close();
        }
        out << titles[i] << count << "\n";
    }

    out.close();
    cout << "Success: Enterprise system metrics exported to 'system_export_report.txt' safely." << endl;
}
