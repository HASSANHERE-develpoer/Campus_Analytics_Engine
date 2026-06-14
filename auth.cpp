#include <iostream>
#include <fstream>
#include <string>
#include "auth.h"
#include "filehandler.h"

using namespace std;

string login(const string& username, const string& password) {
    // 1. Direct Admin Check (Hardcoded)
    if (username == "admin" && password == "admin123") {
        return "admin";
    }

    // 2. Student Check via Text File
    ifstream file("students.txt");
    if (!file.is_open()) {
        // Agar file nahi milti toh loop me phasne ke bajaye invalid return kare
        return "invalid";
    }

    string line;
    getline(file, line); // Header line skip ki

    while (getline(file, line)) {
        if (line == "") continue;

        // columns: roll_no(0), name(1), department(2), semester(3), cgpa(4), status(5)
        string currentRollNo = getColumnValue(line, 0);
        string status = getColumnValue(line, 5);

        if (currentRollNo == username && currentRollNo == password) {
            if (status == "inactive" || status == "Inactive") {
                cout << "\nAccess Denied: Your student account is inactive!" << endl;
                file.close();
                return "invalid";
            }
            file.close();
            return "student";
        }
    }

    file.close();
    return "invalid";
}
