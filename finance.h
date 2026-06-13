#ifndef FINANCE_H
#define FINANCE_H

#include <iostream>
#include <string>

using namespace std;

// Module 6: Financial Management Functions (As per real fees.txt)
void viewFeeStatus(const string& rollNo);
void payFee(const string& rollNo, double amount);
void calculateTotalRevenue();

#endif
