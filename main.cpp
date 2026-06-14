#include <iostream>
#include <string>
#include "auth.h"
#include "student.h"
#include "course.h"
#include "attendance.h"
#include "analytics.h"
#include "finance.h"

using namespace std;

void showAdminMenu() {
    int choice;
    do {
        cout << "\n=== ADMIN DASHBOARD ===" << endl;
        cout << "1. Add New Student" << endl;
        cout << "2. Add New Course" << endl;
        cout << "3. View Course Catalog" << endl;
        cout << "4. View Total Revenue" << endl;
        cout << "5. View Course Attendance Analytics" << endl;
        cout << "6. Logout" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) addStudent();
        else if (choice == 2) addCourse();
        else if (choice == 3) viewCourseCatalog();
        else if (choice == 4) calculateTotalRevenue();
        else if (choice == 5) {
            string cCode;
            cout << "Enter Course Code for Analytics (e.g., CS-101): ";
            cin >> cCode;
            printPerformanceReport(cCode);
        }
    } while (choice != 6);
}

void showStudentMenu(const string& rollNo) {
    int choice;
    do {
        cout << "\n=== STUDENT PORTAL ===" << endl;
        cout << "1. View Profile" << endl;
        cout << "2. View Attendance Report" << endl;
        cout << "3. View Fee Status" << endl;
        cout << "4. Pay Fee Online" << endl;
        cout << "5. Logout" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) displayStudentProfile(rollNo);
        else if (choice == 2) viewAttendanceReport(rollNo);
        else if (choice == 3) viewFeeStatus(rollNo);
        else if (choice == 4) {
            double amt;
            cout << "Enter Amount to Pay: Rs. ";
            cin >> amt;
            payFee(rollNo, amt);
        }
    } while (choice != 5);
}

int main() {
    int choice;
    do {
        cout << "\n=========================================" << endl;
        cout << "      WELCOME TO CAMPUS ANALYTICS ENGINE " << endl;
        cout << "=========================================" << endl;
        cout << "1. Login" << endl;
        cout << "2. Exit System" << endl;
        cout << "Enter option: ";
        cin >> choice;

        if (choice == 1) {
            string user, pass;
            cout << "Enter Username / Roll No: ";
            cin >> user;
            cout << "Enter Password: ";
            cin >> pass;

            string role = login(user, pass);
            if (role == "admin") {
                showAdminMenu();
            } else if (role == "student") {
                showStudentMenu(user);
            } else {
                cout << "\nInvalid Credentials! Try Again." << endl;
            }
        }
    } while (choice != 2);

    cout << "\nThank you for using Campus Analytics Engine. Goodbye!" << endl;
    return 0;
}
