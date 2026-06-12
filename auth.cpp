#include <iostream>
#include <fstream>
#include <string>
#include "auth.h"
#include "filehandler.h"

using namespace std;

// Login check karne ka function
bool loginUser(const string& email, const string& password, string& loggedInId, string& role) {
    // 1. Pehle Admin credentials check karo (Hardcoded as per requirement)
    if (email == "admin@umt.edu.pk" && password == "admin123") {
        loggedInId = "ADMIN";
        role = "admin";
        return true;
    }

    // 2. Agar admin nahi hai, toh students.txt file check karo
    ifstream file("students.txt");
    if (!file.is_open()) {
        cout << "Error: Could not open students.txt file!" << endl;
        return false;
    }

    string line;
    getline(file, line); // Header line skip ki

    while (getline(file, line)) {
        if (line == "") continue;

        //  file ke columns: StudentID, Name, Age, Email, Password, Department
        string currentId = getColumnValue(line, 0);
        string currentEmail = getColumnValue(line, 3);
        string currentPassword = getColumnValue(line, 4);

        // Agar email aur password dono match ho jayein
        if (currentEmail == email && currentPassword == password) {
            loggedInId = currentId; // Bache ki ID save kar li (taake baad me kaam aaye)
            role = "student";       // Role student set kar diya
            file.close();
            return true;
        }
    }

    file.close();
    return false; // Agar kuch match na hua toh login fail
}
