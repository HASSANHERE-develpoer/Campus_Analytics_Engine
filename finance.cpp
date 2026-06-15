#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include "finance.h"
#include "filehandler.h"

using namespace std;

void viewFeeStatus(const string& rollNo) {
    ifstream file("fees.txt");
    if (!file.is_open()) return;
    string line;
    getline(file, line);
    while (getline(file, line)) {
        if (line == "") continue;
        if (getColumnValue(line, 1) == rollNo) {
            cout << "\n--- FEE PAYMENT STATUS ---" << endl;
            cout << "Roll Number:    " << rollNo << endl;
            cout << "Total Amount:   Rs. " << getColumnValue(line, 3) << endl;
            cout << "Paid Amount:    Rs. " << getColumnValue(line, 4) << endl;
            cout << "Status:         " << getColumnValue(line, 8) << endl;
            break;
        }
    }
    file.close();
}

void payFee(const string& rollNo, double amount) {
    ifstream file("fees.txt");
    ofstream tempFile("temp_fees.txt");
    if (!file.is_open() || !tempFile.is_open()) return;

    string line;
    getline(file, line);
    tempFile << line << "\n";

    while (getline(file, line)) {
        if (line == "") continue;
        string currentRollNo = getColumnValue(line, 1);
        if (currentRollNo == rollNo) {
            double total = atof(getColumnValue(line, 3).c_str());
           double paid = atof(getColumnValue(line, 4).c_str());

paid += amount;

if (paid > total)
{
    paid = total;
}
            cout << "\nPayment Successful!" << endl;
            string status = (paid >= total) ? "paid" : "partial";
            tempFile << getColumnValue(line, 0) << "," << currentRollNo << "," << getColumnValue(line, 2) << ","
                     << total << "," << paid << "," << getColumnValue(line, 5) << ","
                     << "14-06-2026,Online Portal," << status << "\n";
        } else {
            tempFile << line << "\n";
        }
    }
    file.close(); tempFile.close();
    remove("fees.txt"); rename("temp_fees.txt", "fees.txt");
}

void calculateTotalRevenue() {
    ifstream file("fees.txt");
    if (!file.is_open()) return;
    string line; getline(file, line);
    double totalExpected = 0, totalCollected = 0;
    while (getline(file, line)) {
        if (line == "") continue;
        totalExpected += atof(getColumnValue(line, 3).c_str());
        totalCollected += atof(getColumnValue(line, 4).c_str());
    }
    file.close();
    cout << "\nTotal Expected: Rs. " << totalExpected << " | Total Collected: Rs. " << totalCollected << endl;
}
