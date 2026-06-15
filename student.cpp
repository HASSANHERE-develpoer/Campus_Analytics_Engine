#include <iostream>
#include <fstream>
#include <string>
#include "student.h"
#include "filehandler.h"

using namespace std;

// BSAI-YY-XXX Validation Function
bool validateRollNumber(const string& rollNo) {
    if (rollNo.length() != 11) return false;
    if (rollNo.substr(0, 5) != "BSAI-") return false;
    if (rollNo[7] != '-') return false;
    
    // Check if YY and XXX are digits
    for (int i = 5; i <= 6; i++) {
        if (rollNo[i] < '0' || rollNo[i] > '9') return false;
    }
    for (int i = 8; i <= 10; i++) {
        if (rollNo[i] < '0' || rollNo[i] > '9') return false;
    }
    return true;
}

void addStudent() {
    string rollNo, name, dept, sem;
    double cgpa;

    cout << "\n--- Add New Student Record ---" << endl;
    cout << "Enter Roll No (BSAI-YY-XXX): ";
    cin >> rollNo;
    cin.ignore();

    if (!validateRollNumber(rollNo)) {
        cout << "Error: Invalid Roll Number Format! (Must be BSAI-YY-XXX)" << endl;
        return;
    }

    // Duplicate Check
    ifstream checkFile("students.txt");
    if (checkFile.is_open()) {
        string line;
        getline(checkFile, line); // Header skip
        while (getline(checkFile, line)) {
            if (line == "") continue;
            if (getColumnValue(line, 0) == rollNo) {
                cout << "Error: Student with this Roll Number already exists!" << endl;
                checkFile.close();
                return;
            }
        }
        checkFile.close();
    }

    cout << "Enter Full Name (No Digits): ";
    getline(cin, name);
    
    // Name content check
    for (size_t i = 0; i < name.length(); i++) {
        if (name[i] >= '0' && name[i] <= '9') {
            cout << "Error: Name cannot contain numeric digits!" << endl;
            return;
        }
    }

    cout << "Enter Department: ";
    getline(cin, dept);
    cout << "Enter Semester: ";
    cin >> sem;
    cout << "Enter CGPA (0.0 to 4.0): ";
    cin >> cgpa;

    if (cgpa < 0.0 || cgpa > 4.0) {
        cout << "Error: Invalid CGPA bounds!" << endl;
        return;
    }

    ofstream file("students.txt", ios::app);
    if (!file.is_open()) return;
    
    file << rollNo << "," << name << "," << dept << "," << sem << "," << cgpa << ",active\n";
    file.close();
    cout << "Student successfully appended to registry!" << endl;
}

bool searchByRoll(const string& rollNo, Student& student) {
    ifstream file("students.txt");
    if (!file.is_open()) return false;

    string line;
    getline(file, line); // Skip Header

    while (getline(file, line)) {
        if (line == "") continue;
        if (getColumnValue(line, 0) == rollNo) {
            student.roll = getColumnValue(line, 0);
            student.name = getColumnValue(line, 1);
            student.dept = getColumnValue(line, 2);
            student.semester = getColumnValue(line, 3);
            student.cgpa = stod(getColumnValue(line, 4));
            student.status = getColumnValue(line, 5);
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}

void searchByName(const string& subStr) {
    ifstream file("students.txt");
    if (!file.is_open()) return;

    string line;
    getline(file, line); // Skip header
    cout << "\nMatching Search Results:" << endl;
    
    while (getline(file, line)) {
        if (line == "") continue;
        string name = getColumnValue(line, 1);
        
        // Manual substring find logic without <algorithm>
        bool found = false;
        if (subStr.length() <= name.length()) {
            for (size_t i = 0; i <= name.length() - subStr.length(); i++) {
                if (name.substr(i, subStr.length()) == subStr) {
                    found = true;
                    break;
                }
            }
        }
        
        if (found) {
            cout << "Roll: " << getColumnValue(line, 0) << " | Name: " << name << " | Status: " << getColumnValue(line, 5) << endl;
        }
    }
    file.close();
}

void updateStudent(const string& rollNo, int fieldOption, const string& newValue) {
    ifstream file("students.txt");
    ofstream temp("temp_students.txt");
    if (!file.is_open() || !temp.is_open()) return;

    string line;
    getline(file, line);
    temp << line << "\n"; // Header preserve

    bool updated = false;
    while (getline(file, line)) {
        if (line == "") continue;
        string fields[6];
        parseLineToFields(line, fields, 6);

        if (fields[0] == rollNo) {
            // fieldOption maps: 1=Name, 2=Dept, 3=Semester, 4=CGPA
            if (fieldOption >= 1 && fieldOption <= 4) {
                fields[fieldOption] = newValue;
                updated = true;
            }
            temp << fields[0] << "," << fields[1] << "," << fields[2] << "," << fields[3] << "," << fields[4] << "," << fields[5] << "\n";
        } else {
            temp << line << "\n";
        }
    }
    file.close();
    temp.close();
    remove("students.txt");
    rename("temp_students.txt", "students.txt");

    if (updated) cout << "Record updated successfully!" << endl;
    else cout << "Record not found or invalid field selection." << endl;
}

void softDelete(const string& rollNo) {
    ifstream file("students.txt");
    ofstream temp("temp_students.txt");
    if (!file.is_open() || !temp.is_open()) return;

    string line;
    getline(file, line);
    temp << line << "\n";

    while (getline(file, line)) {
        if (line == "") continue;
        string fields[6];
        parseLineToFields(line, fields, 6);

        if (fields[0] == rollNo) {
            fields[5] = "inactive"; // Soft delete toggled
        }
        temp << fields[0] << "," << fields[1] << "," << fields[2] << "," << fields[3] << "," << fields[4] << "," << fields[5] << "\n";
    }
    file.close();
    temp.close();
    remove("students.txt");
    rename("temp_students.txt", "students.txt");
    cout << "Student account status switched to inactive." << endl;
}

void listActiveStudents() {
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
            activeList[count].status = "active";
            count++;
        }
    }
    file.close();

    // Selection Sort by Roll Number manually
    for (int i = 0; i < count - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < count; j++) {
            if (activeList[j].roll < activeList[minIdx].roll) {
                minIdx = j;
            }
        }
        if (minIdx != i) {
            Student tempStud = activeList[i];
            activeList[i] = activeList[minIdx];
            activeList[minIdx] = tempStud;
        }
    }

    cout << "\n--- Active Students Registry ---" << endl;
    for (int i = 0; i < count; i++) {
        cout << activeList[i].roll << " | " << activeList[i].name << " | " << activeList[i].dept << " | Sem: " << activeList[i].semester << " | CGPA: " << activeList[i].cgpa << endl;
    }
}
