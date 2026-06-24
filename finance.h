#ifndef FINANCE_H
#define FINANCE_H
#include <string>
using namespace std;

void recordPayment();
int daysBetween(const string& date1, const string& date2);
// Yahan "dueAmt" karo taake .cpp se match kare
double computeLateFine(const string& dueDate, const string& paidDate, double dueAmt); 
void generateReceipt();
void getDefaulters();
bool isLeapYear(int year);

#endif