#include <iostream>
#include <fstream>
#include <string>
#include "student.h"
#include "filehandler.h"

using namespace std;

// 1. New Student Add Karna (Admin Function)
void addStudent() {
    ofstream file("students.txt", ios::app); // ios::app taake purana data delete na ho
    if (!file.is_open()) {
        cout << "Error: Could not open students.txt!" << endl;
        return;
    }

    string rollNo, name, dept, sem, cgpa, status;

    cout << "\n--- ADD NEW STUDENT ---" << endl;
    cout << "Enter Roll No (e.g., AI-01): ";
    cin >> rollNo;
    cin.ignore(); // Buffer clear karne ke liye
    cout << "Enter Full Name: ";
    getline(cin, name);
    cout << "Enter Department: ";
    getline(cin, dept);
    cout << "Enter Semester: ";
    cin >> sem;
    cout << "Enter Current CGPA: ";
    cin >> cgpa;
    status = "active"; // Naya student hamesha active hoga

    // Comma-separated format me save karo
    file << rollNo << "," << name << "," << dept << "," << sem << "," << cgpa << "," << status << "\n";
    file.close();

    cout << "\nStudent Record Added Successfully!" << endl;
}

// 2. Student Profile Display Karna (Student/Admin Function)
void displayStudentProfile(const string& rollNo) {
    ifstream file("students.txt");
    if (!file.is_open()) {
        cout << "Error: Could not open students.txt!" << endl;
        return;
    }

    string line;
    getline(file, line); // Header skip

    while (getline(file, line)) {
        if (line == "") continue;

        // columns: roll_no(0), name(1), department(2), semester(3), cgpa(4), status(5)
        string currentRollNo = getColumnValue(line, 0);
        if (currentRollNo == rollNo) {
            cout << "\n=========================================" << endl;
            cout << "            STUDENT PROFILE              " << endl;
            cout << "=========================================" << endl;
            cout << "Roll Number:  " << getColumnValue(line, 0) << endl;
            cout << "Full Name:    " << getColumnValue(line, 1) << endl;
            cout << "Department:   " << getColumnValue(line, 2) << endl;
            cout << "Semester:     " << getColumnValue(line, 3) << endl;
            cout << "Current CGPA: " << getColumnValue(line, 4) << endl;
            cout << "Account Status: " << getColumnValue(line, 5) << endl;
            cout << "=========================================" << endl;
            file.close();
            return;
        }
    }
    file.close();
    cout << "Student with Roll No " << rollNo << " not found!" << endl;
}
