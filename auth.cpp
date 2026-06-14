#include <iostream>
#include <fstream>
#include <string>
#include "auth.h"
#include "filehandler.h"

using namespace std;

// Function ka naam aur return type main.cpp ke mutabiq strictly match kar di hai
string login(const string& username, const string& password) {
    
    // 1. Admin Login Check (Hardcoded as per requirement)
    if (username == "admin" && password == "admin123") {
        return "admin";
    }

    // 2. Student Login Check: students.txt se data verify karo
    ifstream file("students.txt");
    if (!file.is_open()) {
        cout << "Error: Could not open students.txt file!" << endl;
        return "invalid";
    }

    string line;
    getline(file, line); // Header line skip ki

    while (getline(file, line)) {
        if (line == "") continue;

        // columns: roll_no(0), name(1), department(2), semester(3), cgpa(4), status(5)
        string currentRollNo = getColumnValue(line, 0);
        string status = getColumnValue(line, 5);

        // Standard Default Rule: Student ka Roll No hi uska password hai
        if (currentRollNo == username && currentRollNo == password) {
            if (status == "inactive" || status == "Inactive") {
                cout << "\nAccess Denied: Your student account is inactive!" << endl;
                file.close();
                return "invalid";
            }
            file.close();
            return "student"; // Seedha student role return karo
        }
    }

    file.close();
    return "invalid"; // Agar kuch match na ho toh login fail
}
