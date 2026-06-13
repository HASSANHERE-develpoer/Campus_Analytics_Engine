#include <iostream>
#include <fstream>
#include <string>
#include "finance.h"
#include "filehandler.h"

using namespace std;

// 1. Student apna fee record check kare
void viewFeeStatus(const string& rollNo) {
    ifstream file("fees.txt");
    if (!file.is_open()) {
        cout << "Error: Could not open fees.txt!" << endl;
        return;
    }

    string line;
    getline(file, line); // Header skip

    while (getline(file, line)) {
        if (line == "") continue;

        // fees.txt columns: fee_id(0), roll_no(1), semester(2), total_fee(3), amount_paid(4), status(8)
        string currentRollNo = getColumnValue(line, 1);
        if (currentRollNo == rollNo) {
            cout << "\n--- FEE DETAILS (" << rollNo << ") ---" << endl;
            cout << "Fee ID:         " << getColumnValue(line, 0) << endl;
            cout << "Total Fee:      Rs. " << getColumnValue(line, 3) << endl;
            cout << "Amount Paid:    Rs. " << getColumnValue(line, 4) << endl;
            cout << "Payment Status: " << getColumnValue(line, 8) << endl;
            file.close();
            return;
        }
    }
    file.close();
    cout << "No fee record found for Roll No: " << rollNo << endl;
}

// 2. Student apni fee jama karwaye
void payFee(const string& rollNo, double amount) {
    ifstream file("fees.txt");
    ofstream tempFile("temp_fees.txt");
    
    if (!file.is_open() || !tempFile.is_open()) return;

    string line;
    bool found = false;

    getline(file, line);
    tempFile << line << "\n"; // Header copy

    while (getline(file, line)) {
        if (line == "") continue;

        string feeId = getColumnValue(line, 0);
        string currentRollNo = getColumnValue(line, 1);
        string sem = getColumnValue(line, 2);
        double total = stod(getColumnValue(line, 3));
        double paid = stod(getColumnValue(line, 4));
        string dueDate = getColumnValue(line, 5);
        string payDate = getColumnValue(line, 6);
        string method = getColumnValue(line, 7);
        string status = getColumnValue(line, 8);

        if (currentRollNo == rollNo) {
            paid += amount;
            if (paid >= total) status = "paid";
            else status = "partial";
            payDate = "14-06-2026"; // Aaj ki date lagayi
            method = "Online";
            found = true;
            
            tempFile << feeId << "," << rollNo << "," << sem << "," << total << "," << paid << "," << dueDate << "," << payDate << "," << method << "," << status << "\n";
        } else {
            tempFile << line << "\n";
        }
    }
    file.close();
    tempFile.close();

    remove("fees.txt");
    rename("temp_fees.txt", "fees.txt");

    if (found) cout << "Successfully paid Rs. " << amount << " for Roll No: " << rollNo << endl;
    else cout << "Roll No not found in fee registry." << endl;
}

// 3. Admin total revenue report dekhe
void calculateTotalRevenue() {
    ifstream file("fees.txt");
    if (!file.is_open()) return;

    string line;
    double collected = 0.0;
    double pending = 0.0;

    getline(file, line); // Header skip

    while (getline(file, line)) {
        if (line == "") continue;

        double total = stod(getColumnValue(line, 3));
        double paid = stod(getColumnValue(line, 4));

        collected += paid;
        pending += (total - paid);
    }
    file.close();

    cout << "\n=========================================" << endl;
    cout << "        CAMPUS FINANCIAL OVERVIEW        " << endl;
    cout << "=========================================" << endl;
    cout << "Total Collected Revenue: Rs. " << collected << endl;
    cout << "Total Outstanding Dues:  Rs. " << pending << endl;
    cout << "=========================================" << endl;
}
