#include <iostream>
#include <fstream>
#include <string>
#include "course.h"
#include "filehandler.h"

using namespace std;

// 1. Naya Course Add Karna (Admin Function)
void addCourse() {
    ofstream file("courses.txt", ios::app); // Append mode taake purana data urray na
    if (!file.is_open()) {
        cout << "Error: Could not open courses.txt!" << endl;
        return;
    }

    string courseCode, courseName, creditHours, dept;

    cout << "\n--- ADD NEW CAMPUS COURSE ---" << endl;
    cout << "Enter Course Code (e.g., CS-101): ";
    cin >> courseCode;
    cin.ignore(); // Buffer clear taake getline smoothly chale
    
    cout << "Enter Course Name: ";
    getline(cin, courseName);
    
    cout << "Enter Credit Hours: ";
    cin >> creditHours;
    cin.ignore(); // Buffer clear
    
    cout << "Enter Offering Department: ";
    getline(cin, dept);

    // Standard Comma-separated line save karo
    file << courseCode << "," << courseName << "," << creditHours << "," << dept << "\n";
    file.close();

    cout << "\nCourse Added to Catalog Successfully!" << endl;
}

// 2. Poora Course Catalog Display Karna (Student/Admin Function)
void viewCourseCatalog() {
    ifstream check("courses.txt");

string line;
getline(check, line);

while (getline(check, line))
{
    if (getColumnValue(line, 0) == courseCode)
    {
        cout << "\nCourse already exists!" << endl;
        check.close();
        return;
    }
}

check.close();
    if (!file.is_open()) {
        cout << "Error: Could not open courses.txt!" << endl;
        return;
    }

    string line;
    cout << "\n=================================================================" << endl;
    cout << "                    OFFICIAL COURSE CATALOG                      " << endl;
    cout << "=================================================================" << endl;
    cout << "Sr.\tCode\t\tCredit Hours\tCourse Name [Department]" << endl;
    cout << "-----------------------------------------------------------------" << endl;
    
    getline(file, line); // Header skip
    
    int count = 0;
    while (getline(file, line)) {
        if (line == "") continue;

        count++;
        // columns: course_code(0), course_name(1), credit_hours(2), department(3)
        string code = getColumnValue(line, 0);
        string name = getColumnValue(line, 1);
        string hrs = getColumnValue(line, 2);
        string dpt = getColumnValue(line, 3);

        // Tabular and neat output display
        cout << count << ".\t" << code << "\t\t" << hrs << "\t\t" << name << " [" << dpt << "]" << endl;
    }
    file.close();

    if (count == 0) {
        cout << "No active courses found in the catalog." << endl;
    }
    cout << "=================================================================" << endl;
}
