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
    for (int i = 5; i <= 6; i++) { if (rollNo[i] < '0' || rollNo[i] > '9') return false; }
    for (int i = 8; i <= 10; i++) { if (rollNo[i] < '0' || rollNo[i] > '9') return false; }
    return true;
}

void addStudent() {
    string rollNo, name, dept, sem;
    double cgpa;
    cout << "\n--- Add New Student Record ---" << endl;
    cout << "Enter Roll No (BSAI-YY-XXX): ";
    cin >> rollNo;
    clearInput(); // Crash-proof fix
    cin.ignore();
    if (!validateRollNumber(rollNo)) {
        cout << "Error: Invalid Roll Number Format!" << endl;
        return;
    }

    ifstream checkFile("students.txt");
    if (checkFile.is_open()) {
        string line;
        getline(checkFile, line);
        while (getline(checkFile, line)) {
            if (line == "") continue;
            if (getColumnValue(line, 0) == rollNo) {
                cout << "Error: Roll Number already exists!" << endl;
                checkFile.close();
                return;
            }
        }
        checkFile.close();
    }

    cout << "Enter Full Name: "; getline(cin, name);
    cout << "Enter Department: "; getline(cin, dept);
    cout << "Enter Semester: "; cin >> sem;
    clearInput(); // Crash-proof fix
    cout << "Enter CGPA: "; cin >> cgpa;
    clearInput(); // Crash-proof fix

    ofstream file("students.txt", ios::app);
    file << rollNo << "," << name << "," << dept << "," << sem << "," << cgpa << ",active\n";
    file.close();
    cout << "Student successfully appended!" << endl;
}

bool searchByRoll(const string& rollNo, Student& student) {
    ifstream file("students.txt");
    if (!file.is_open()) return false;
    string line;
    getline(file, line);
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
    getline(file, line);

    string lowerSubStr = subStr;
    for(size_t i=0; i<lowerSubStr.length(); i++) lowerSubStr[i] = tolower(lowerSubStr[i]);

    cout << "\nMatching Search Results:" << endl;
    bool found = false;
    while (getline(file, line)) {
        if (line.empty()) continue;
        string name = getColumnValue(line, 1);
        string lowerName = name;
        for(size_t i=0; i<lowerName.length(); i++) lowerName[i] = tolower(lowerName[i]);

        if (lowerName.find(lowerSubStr) != string::npos) {
            cout << "Roll: " << getColumnValue(line, 0) << " | Name: " << name << " | Status: " << getColumnValue(line, 5) << endl;
            found = true;
        }
    }
    if(!found) cout << "No matches found." << endl;
    file.close();
}

void updateStudent(const string& rollNo, int fieldOption, const string& newValue) {
    ifstream file("students.txt");
    ofstream temp("temp_students.txt");
    if (!file.is_open()) return;
    string line;
    getline(file, line);
    temp << line << "\n";
    bool updated = false;
    while (getline(file, line)) {
        if (line == "") continue;
        string fields[6];
        parseLineToFields(line, fields, 6);
        if (fields[0] == rollNo) {
            if (fieldOption >= 1 && fieldOption <= 4) {
                fields[fieldOption] = newValue;
                updated = true;
            }
            temp << fields[0] << "," << fields[1] << "," << fields[2] << "," << fields[3] << "," << fields[4] << "," << fields[5] << "\n";
        } else temp << line << "\n";
    }
    file.close(); temp.close();
    remove("students.txt"); rename("temp_students.txt", "students.txt");
    if (updated) cout << "Updated successfully!" << endl;
    else cout << "Record not found." << endl;
}

void softDelete(const string& rollNo) {
    ifstream file("students.txt");
    ofstream temp("temp_students.txt");
    string line;
    getline(file, line);
    temp << line << "\n";
    while (getline(file, line)) {
        if (line == "") continue;
        string fields[6];
        parseLineToFields(line, fields, 6);
        if (fields[0] == rollNo) fields[5] = "inactive";
        temp << fields[0] << "," << fields[1] << "," << fields[2] << "," << fields[3] << "," << fields[4] << "," << fields[5] << "\n";
    }
    file.close(); temp.close();
    remove("students.txt"); rename("temp_students.txt", "students.txt");
    cout << "Status changed to inactive." << endl;
}

void listActiveStudents() {
    Student activeList[200];
    int count = 0;
    ifstream file("students.txt");
    if (!file.is_open()) return;
    string line;
    getline(file, line);
    while (getline(file, line) && count < 200) {
        if (line.empty()) continue;
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

    cout << "\n--- Active Students Registry ---" << endl;
    for (int i = 0; i < count; i++) {
        cout << activeList[i].roll << " | " << activeList[i].name
             << " | Dept: " << activeList[i].dept
             << " | Sem: " << activeList[i].semester
             << " | CGPA: " << activeList[i].cgpa << endl;
    }
}