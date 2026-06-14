#include <iostream>
#include <string>
#include "auth.h"
#include "student.h"
#include "course.h"
#include "analytics.h"
#include "finance.h"

using namespace std;

void showAdminMenu() {
    int choice;
    do {
        cout << "\n=========================================" << endl;
        cout << "            ADMIN MAIN DASHBOARD         " << endl;
        cout << "=========================================" << endl;
        cout << "1. Register New Student" << endl;
        cout << "2. View Student Profile" << endl;
        cout << "3. Add New Campus Course" << endl;
        cout << "4. View Official Course Catalog" << endl;
        cout << "5. View Course Attendance Analytics" << endl;
        cout << "6. View Campus Financial Overview" << endl;
        cout << "7. Logout" << endl;
        cout << "Enter your choice (1-7): ";
        cin >> choice;

        string rollNo, courseCode;
        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                cout << "Enter Student Roll No to search: ";
                cin >> rollNo;
                displayStudentProfile(rollNo);
                break;
            case 3:
                addCourse();
                break;
            case 4:
                viewCourseCatalog();
                break;
            case 5:
                cout << "Enter Course Code for full report: ";
                cin >> courseCode;
                printPerformanceReport(courseCode);
                break;
            case 6:
                calculateTotalRevenue();
                break;
            case 7:
                cout << "Logging out from Admin Session..." << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 7);
}

void showStudentMenu(const string& studentRollNo) {
    int choice;
    do {
        cout << "\n=========================================" << endl;
        cout << "           STUDENT MAIN DASHBOARD        " << endl;
        cout << "=========================================" << endl;
        cout << "Welcome Student! Roll No: " << studentRollNo << endl;
        cout << "-----------------------------------------" << endl;
        cout << "1. View My Personal Profile" << endl;
        cout << "2. View Campus Course Catalog" << endl;
        cout << "3. Check My Fee Payment Status" << endl;
        cout << "4. Make Online Fee Payment" << endl;
        cout << "5. Logout" << endl;
        cout << "Enter your choice (1-5): ";
        cin >> choice;

        double amount;
        switch (choice) {
            case 1:
                displayStudentProfile(studentRollNo);
                break;
            case 2:
                viewCourseCatalog();
                break;
            case 3:
                viewFeeStatus(studentRollNo);
                break;
            case 4:
                cout << "Enter Amount to pay: Rs. ";
                cin >> amount;
                payFee(studentRollNo, amount);
                break;
            case 5:
                cout << "Logging out from Student Session..." << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 5);
}

int main() {
    int mainChoice;
    do {
        cout << "\n=========================================" << endl;
        cout << "        WELCOME TO CAMPUS ENGINE         " << endl;
        cout << "=========================================" << endl;
        cout << "1. Portal Secure Login" << endl;
        cout << "2. Exit System" << endl;
        cout << "Enter choice: ";
        cin >> mainChoice;

        if (mainChoice == 1) {
            string user, pass, loggedInId, role;
            cout << "\n--- PORTAL SECURE LOGIN ---" << endl;
            cout << "Enter User ID / Roll No: ";
            cin >> user;
            cout << "Enter Password: ";
            cin >> pass;

            if (loginUser(user, pass, loggedInId, role)) {
                cout << "\nLogin Successful! Redirecting..." << endl;
                if (role == "admin") {
                    showAdminMenu();
                } else if (role == "student") {
                    showStudentMenu(loggedInId);
                }
            } else {
                cout << "\nLogin Failed! Invalid Credentials or Inactive Account." << endl;
            }
        } else if (mainChoice == 2) {
            cout << "\nThank you for using Campus Analytics Engine. Goodbye!" << endl;
        } else {
            cout << "Invalid option!" << endl;
        }
    } while (mainChoice != 2);

    return 0;
}
