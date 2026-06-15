#ifndef AUTH_H
#define AUTH_H

#include <string>
using namespace std;

struct Stats {
    double highest;
    double lowest;
    double mean;
    double median;
};

void enterMarks();
double bestThreeOfFive(double quizzes[], int n);
double computeWeightedTotal(double quizAvg, double asgnAvg, double mid, double finalExam);
string getLetterGrade(double totalMarks);
double computeGPA(const string& rollNo, const string& semester);
void computeClassStats();

#endif
