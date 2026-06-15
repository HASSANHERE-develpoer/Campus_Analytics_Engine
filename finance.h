#ifndef FEE_TRACKER_H
#define FEE_TRACKER_H

#include <string>
using namespace std;

void recordPayment();
int daysBetween(const string& date1, const string& date2);
double computeLateFine(const string& dueDate, const string& paidDate, double baseAmount);
void generateReceipt();
void getDefaulters();
bool isLeapYear(int year);

#endif
