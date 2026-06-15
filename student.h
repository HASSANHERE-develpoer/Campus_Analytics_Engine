#ifndef STUDENT_H
#define STUDENT_H

#include <string>
using namespace std;

struct Student {
    string roll;
    string name;
    string dept;
    string semester;
    double cgpa;
    string status; // active/inactive (soft delete)
};

void addStudent();
bool searchByRoll(const string& rollNo, Student& student);
void searchByName(const string& subStr);
void updateStudent(const string& rollNo, int fieldOption, const string& newValue);
void softDelete(const string& rollNo);
void listActiveStudents();
bool validateRollNumber(const string& rollNo);

#endif
