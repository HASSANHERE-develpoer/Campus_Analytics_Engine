#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <vector>
#include <sstream>
#include "finance.h"   
#include "student.h"    
#include "filehandler.h"
using namespace std;

// --- Helper Functions ---
bool isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int daysBetween(const string& date1, const string& date2) {
    int d1 = stoi(date1.substr(0, 2)), m1 = stoi(date1.substr(3, 2)), y1 = stoi(date1.substr(6, 4));
    int d2 = stoi(date2.substr(0, 2)), m2 = stoi(date2.substr(3, 2)), y2 = stoi(date2.substr(6, 4));
    return (d2 - d1) + (m2 - m1) * 30 + (y2 - y1) * 365;
}

double computeLateFine(const string& dueDate, const string& paidDate, double dueAmt) {
    int days = daysBetween(dueDate, paidDate);
    if (days > 0) return dueAmt * 0.02; // 2% fine
    return 0.0;
}

// --- Main Functions ---
void recordPayment() {
    string rollNo, semester, paidDate;
    double paymentAmount;

    cout << "\n--- Financial Counter Transaction ---" << endl;
    cout << "Enter Student Roll No: "; cin >> rollNo; clearInput();
    cout << "Enter Semester: "; cin >> semester; clearInput();
    cout << "Enter Amount Paid: Rs. "; cin >> paymentAmount; clearInput();
    cout << "Enter Payment Date (DD-MM-YYYY): "; cin >> paidDate; clearInput();

    ifstream file("fees.txt");
    ofstream temp("temp_fees.txt");
    if (!file.is_open() || !temp.is_open()) return;

    string line;
    getline(file, line); // Header skip
    temp << line << "\n"; 

    bool recordUpdated = false;
    while (getline(file, line)) {
        if (line == "") continue;
        
        if (getColumnValue(line, 1) == rollNo && getColumnValue(line, 2) == semester) {
            double dueAmt = stod(getColumnValue(line, 3));
            double currentPaid = stod(getColumnValue(line, 4));
            string dueDate = getColumnValue(line, 5);

            currentPaid += paymentAmount;
            
            temp << getColumnValue(line, 0) << "," << rollNo << "," << semester << "," 
                 << dueAmt << "," << currentPaid << "," << dueDate << "," 
                 << paidDate << "," << getColumnValue(line, 7) << ",paid" << "\n";
            recordUpdated = true;
        } else {
            temp << line << "\n";
        }
    }
    file.close(); temp.close();
    remove("fees.txt"); rename("temp_fees.txt", "fees.txt");

    if (recordUpdated) cout << "Success: Ledger balances posted safely." << endl;
    else cout << "Error: Financial parameters account profile match undetected." << endl;
}

void generateReceipt() {
    string rollNo, semester;
    cout << "Enter Student Roll No: "; cin >> rollNo; clearInput();
    cout << "Enter Target Semester: "; cin >> semester; clearInput();

    ifstream file("fees.txt");
    string line; getline(file, line); 
    
    while (getline(file, line)) {
        if (line == "") continue;
        if (getColumnValue(line, 1) == rollNo && getColumnValue(line, 2) == semester) {
            double due = stod(getColumnValue(line, 3));
            double paid = stod(getColumnValue(line, 4));
            cout << "\n--- OFFICIAL FEE RECEIPT ---" << endl;
            cout << "Roll No: " << rollNo << " | Semester: " << semester << endl;
            cout << "Total Due: Rs. " << due << " | Total Paid: Rs. " << paid << endl;
            file.close(); return;
        }
    }
    file.close();
    cout << "Ledger Entry Missing." << endl;
}

void getDefaulters() {
    cout << "\n--- Defaulter List ---" << endl;
    ifstream file("fees.txt");
    string line; getline(file, line); // Skip header
    
    while (getline(file, line)) {
        if (line == "") continue;
        double due = stod(getColumnValue(line, 3));
        double paid = stod(getColumnValue(line, 4));

        if (due > paid) {
            cout << "Roll No: " << getColumnValue(line, 1) << " | Outstanding: " << (due - paid) << endl;
        }
    }
    file.close();
}