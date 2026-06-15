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

    string rollNo, name, dept, sem, status;
double cgpa;

cout << "\n--- ADD NEW STUDENT ---" << endl;
cout << "Enter Roll No (e.g., AI-01): ";
cin >> rollNo;
cin.ignore();

cout << "Enter Full Name: ";
getline(cin, name);

cout << "Enter Department: ";
getline(cin, dept);

cout << "Enter Semester: ";
cin >> sem;

cout << "Enter Current CGPA: ";
cin >> cgpa;

if (cgpa < 0.0 || cgpa > 4.0)
{
    cout << "\nInvalid CGPA! CGPA must be between 0 and 4." << endl;
    file.close();
    return;
}

status = "active";
    // Comma-separated standard format me save karo
    file << rollNo << "," << name << "," << dept << "," << sem << "," << cgpa << "," << status << "\n";
    file.close();

    cout << "\nStudent Record Added Successfully!" << endl;
}

// 2. Student Profile Display Karna (Student/Admin Function)
void displayStudentProfile(const string& rollNo) {
    ifstream file("students.txt");

string line;
getline(check, line);

while (getline(check, line))
{
    if (getColumnValue(line, 0) == rollNo)
    {
        cout << "\nStudent already exists!" << endl;
        check.close();
        return;
    }
}

check.close();
    if (!file.is_open()) {
        cout << "Error: Could not open students.txt!" << endl;
        return;
    }

    string line;
    getline(file, line); // Header line skip karne ke liye

    bool found = false;
    while (getline(file, line)) {
        if (line == "") continue;

        // columns: roll_no(0), name(1), department(2), semester(3), cgpa(4), status(5)
        string currentRollNo = getColumnValue(line, 0);
        if (currentRollNo == rollNo) {
            found = true;
            cout << "\n=========================================" << endl;
            cout << "            STUDENT PROFILE              " << endl;
            cout << "=========================================" << endl;
            cout << "Roll Number:    " << currentRollNo << endl;
            cout << "Full Name:      " << getColumnValue(line, 1) << endl;
            cout << "Department:     " << getColumnValue(line, 2) << endl;
            cout << "Semester:       " << getColumnValue(line, 3) << endl;
            cout << "Current CGPA:   " << getColumnValue(line, 4) << endl;
            cout << "Account Status: " << getColumnValue(line, 5) << endl;
            cout << "=========================================" << endl;
            break; // Record mil gaya, loop se baahir aao
        }
    }
    file.close(); // Clean exit
    
    if (!found) {
        cout << "\nStudent with Roll No " << rollNo << " not found!" << endl;
    }
}
