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
        cout << "1. View Total Revenue" << endl;
        cout << "2. View System Analytics" << endl;
        cout << "3. Logout" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) calculateTotalRevenue();
        else if (choice == 2) cout << "\n[Feature coming soon in Next Sprint]" << endl;
    } while (choice != 3);
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
