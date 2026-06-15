#ifndef COURSE_H
#define COURSE_H
#include <string>
using namespace std;

enum EnrollResult {
    SUCCESS,
    STUDENT_INACTIVE,
    COURSE_NOT_FOUND,
    NO_SEATS,
    ALREADY_ENROLLED,
    CREDIT_LIMIT_EXCEEDED,
    PREREQ_FAILED
};

void enrollStudent();
void dropCourse();
int getCreditLoad(const string& rollNo, const string& semester);
bool checkPrerequisite(const string& rollNo, const string& courseCode);
void listEnrolledStudents();

#endif
