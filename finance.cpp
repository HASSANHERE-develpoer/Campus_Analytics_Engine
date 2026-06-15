#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include "finance.h"   
#include "student.h"    
#include "filehandler.h"
using namespace std;

// 1. Check if year is leap year (Manual logic)
bool isLeapYear(int year) {
    if (year % 400 == 0) return true;
    if (year % 100 == 0) return false;
    if (year % 4 == 0) return true;
    return false;
}

// 2. Pure Manual Days Calculator without <ctime> library 
int convertToTotalDays(const string& dateStr) {
    // Extract parameters from DD-MM-YYYY [cite: 48, 72]
    int day = stoi(dateStr.substr(0, 2));
    int month = stoi(dateStr.substr(3, 2));
    int year = stoi(dateStr.substr(6, 4));

    int monthDays[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    // Calculate absolute base days from year 0 reference point
    int totalDays = year * 365 + day;

    // Add leap year days for past years
    for (int y = 1; y < year; y++) {
        if (isLeapYear(y)) totalDays++;
    }

    // Add current year's completed months days
    for (int m = 1; m < month; m++) {
        if (m == 2 && isLeapYear(year)) {
            totalDays += 29;
        } else {
            totalDays += monthDays[m];
        }
    }
    return totalDays;
}

int daysBetween(const string& date1, const string& date2) {
    return convertToTotalDays(date2) - convertToTotalDays(date1); // paidDate - dueDate [cite: 72]
}

// 3. Late Fine implementation: 2% per complete week overdue [cite: 72]
double computeLateFine(const string& dueDate, const string& paidDate, double baseAmount) {
    int delay = daysBetween(dueDate, paidDate);
    if (delay <= 0) return 0.0;

    int completeWeeks = delay / 7;
    return (completeWeeks * 0.02) * baseAmount; // 2% per complete week [cite: 72]
}

// 4. Record Payment Processing module [cite: 72]
void recordPayment() {
    string rollNo, semester, paidDate;
    double paymentAmount;

    cout << "\n--- Financial Counter Transaction ---" << endl;
    cout << "Enter Student Roll No: ";
    cin >> rollNo;
    cout << "Enter Semester: ";
    cin >> semester;
    cout << "Enter Amount Paid: Rs. ";
    cin >> paymentAmount;
    cout << "Enter Payment Date (DD-MM-YYYY): ";
    cin >> paidDate;

    // Simple date formatting check
    if (paidDate.length() != 10 || paidDate[2] != '-' || paidDate[5] != '-') {
        cout << "Error: Invalid date presentation layout context!" << endl;
        return;
    }

    ifstream file("fees.txt");
    ofstream temp("temp_fees.txt");
    if (!file.is_open() || !temp.is_open()) return;

    string line;
    getline(file, line);
    temp << line << "\n"; // Preserve header

    bool recordUpdated = false;
    while (getline(file, line)) {
        if (line == "") continue;
        
        // roll(0), semester(1), amount_due(2), amount_paid(3), due_date(4), paid_date(5) [cite: 48]
        if (getColumnValue(line, 0) == rollNo && getColumnValue(line, 1) == semester) {
            double dueAmt = stod(getColumnValue(line, 2));
            double currentPaid = stod(getColumnValue(line, 3));
            string dueDate = getColumnValue(line, 4);

            currentPaid += paymentAmount;
            
            // Calculate penalties if transaction delay is captured [cite: 72]
            double penaltyFine = computeLateFine(dueDate, paidDate, dueAmt);
            if (penaltyFine > 0) {
                cout << "Late Fine Added (2% per overdue week): Rs. " << penaltyFine << endl;
                dueAmt += penaltyFine; // Late fine builds inside current asset dues
            }

            temp << rollNo << "," << semester << "," << dueAmt << "," 
                 << currentPaid << "," << dueDate << "," << paidDate << "\n";
            recordUpdated = true;
        } else {
            temp << line << "\n";
        }
    }
    file.close();
    temp.close();
    remove("fees.txt");
    rename("temp_fees.txt", "fees.txt");

    if (recordUpdated) cout << "Success: Ledger balances posted safely." << endl;
    else cout << "Error: Financial parameters account profile match undetected." << endl;
}

// 5. Generate Receipt Layout using <iomanip> manipulators [cite: 72]
void generateReceipt() {
    string rollNo, semester;
    cout << "Enter Student Roll No: ";
    cin >> rollNo;
    cout << "Enter Target Semester: ";
    cin >> semester;

    ifstream file("fees.txt");
    if (!file.is_open()) return;

    string line;
    getline(file, line);
    
    while (getline(file, line)) {
        if (line == "") continue;
        if (getColumnValue(line, 0) == rollNo && getColumnValue(line, 1) == semester) {
            double due = stod(getColumnValue(line, 2));
            double paid = stod(getColumnValue(line, 3));
            string dueDate = getColumnValue(line, 4);
            string paidDate = getColumnValue(line, 5);

            double fine = computeLateFine(dueDate, paidDate, due);
            double balance = due - paid;

            Student std;
            searchByRoll(rollNo, std);

            cout << "\n" << setfill('=') << setw(45) << "" << endl;
            cout << setfill(' ') << setw(15) << "" << "OFFICIAL FEE RECEIPT" << endl;
            cout << setfill('=') << setw(45) << "" << endl << setfill(' ');
            cout << "Roll No:    " << rollNo << "\t\tSemester: " << semester << endl;
            cout << "Name:       " << std.name << endl;
            cout << "---------------------------------------------" << endl;
            cout << "Base Tuition Fee Due:      Rs. " << (due - fine) << endl;
            cout << "Late Payment Fine Levied:  Rs. " << fine << endl;
            cout << "Total Consolidated Due:    Rs. " << due << endl;
            cout << "Total Amount Deposited:    Rs. " << paid << endl;
            cout << "---------------------------------------------" << endl;
            cout << "Outstanding Net Balance:   Rs. " << (balance < 0 ? 0 : balance) << endl;
            cout << setfill('=') << setw(45) << "" << endl;
            file.close();
            return;
        }
    }
    file.close();
    cout << "Ledger Entry Missing for specified criteria parameters." << endl;
}

// 6. Fee Defaulters sorted by outstanding amount using Bubble Sort [cite: 72]
void getDefaulters() {
    struct DefaulterNode {
        string roll;
        double outstanding;
        int daysOverdue;
    };

    DefaulterNode list[100];
    int count = 0;

    ifstream file("fees.txt");
    if (!file.is_open()) return;

    string line;
    getline(file, line);
    
    // Farzi validation current current comparison checkpoint date (15-06-2026)
    string evaluationDate = "15-06-2026"; 

    while (getline(file, line) && count < 100) {
        if (line == "") continue;
        double due = stod(getColumnValue(line, 2));
        double paid = stod(getColumnValue(line, 3));
        string dueDate = getColumnValue(line, 4);

        if (due > paid) {
            int overdue = daysBetween(dueDate, evaluationDate);
            if (overdue > 0) {
                list[count].roll = getColumnValue(line, 0);
                list[count].outstanding = due - paid;
                list[count].daysOverdue = overdue;
                count++;
            }
        }
    }
    file.close();

    // Bubble Sort based on absolute outstanding money values descending order [cite: 72]
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (list[j].outstanding < list[j + 1].outstanding) {
                DefaulterNode temp = list[j];
                list[j] = list[j + 1];
                list[j + 1] = temp;
            }
        }
    }

    cout << "\n--- Fee Delinquency Registry (Past Due Dates) ---" << endl;
    for (int i = 0; i < count; i++) {
        cout << "Roll: " << list[i].roll 
             << " | Balance Owed: Rs. " << list[i].outstanding 
             << " | Delay: " << list[i].daysOverdue / 7 << " Weeks overdue" << endl;
    }
}
