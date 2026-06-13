#include <iostream>
#include <fstream>
#include <string>
#include "auth.h"
#include "filehandler.h"

using namespace std;

bool loginUser(const string& username, const string& password, string& loggedInId, string& role) {
    // 1. Admin Login (As per requirement)
    if (username == "admin" && password == "admin123") {
        loggedInId = "ADMIN";
        role = "admin";
        return true;
    }

    // 2. Student Login: students.txt se check karo ke Roll No exist karta hai ya nahi
    ifstream file("students.txt");
    if (!file.is_open()) {
        cout << "Error: Could not open students.txt file!" << endl;
        return false;
    }

    string line;
    getline(file, line); // Header skip ki

    while (getline(file, line)) {
        if (line == "") continue;

        // students.txt columns: roll_no(0), name(1), department(2), status(5)
        string currentRollNo = getColumnValue(line, 0);
        string status = getColumnValue(line, 5);

        // Agar bacha apna Roll No sahi daalta hai aur password me bhi Roll No daalta hai
        if (currentRollNo == username && currentRollNo == password) {
            if (status == "inactive") {
                cout << "Access Denied: Your student account is inactive." << endl;
                file.close();
                return false;
            }
            loggedInId = currentRollNo; // Roll No save kar liya
            role = "student";
            file.close();
            return true;
        }
    }

    file.close();
    return false; // Login Failed
}
