#include <iostream>
#include <fstream>
#include <string>
#include "auth.h"
#include "student.h"   
#include "attendance.h"
#include "filehandler.h"

using namespace std;

// 1. Quizzes me se worst 2 ko exclude karke baki 3 ka average nikalna (Strict Constraint: No Sort)
double bestThreeOfFive(double quizzes[], int n) {
    if (n < 3) {
        double sum = 0;
        for (int i = 0; i < n; i++) sum += quizzes[i];
        return (n == 0) ? 0.0 : (sum / n);
    }

    double q1 = quizzes[0], q2 = quizzes[1], q3 = quizzes[2], q4 = quizzes[3], q5 = quizzes[4];
    double totalSum = q1 + q2 + q3 + q4 + q5;
    
    // Find two lowest values manually
    double lowest1 = q1;
    int lowest1Idx = 0;
    
    for(int i = 1; i < 5; i++) {
        if(quizzes[i] < lowest1) {
            lowest1 = quizzes[i];
            lowest1Idx = i;
        }
    }
    
    double lowest2 = -1;
    bool assigned = false;
    for(int i = 0; i < 5; i++) {
        if(i == lowest1Idx) continue;
        if(!assigned) {
            lowest2 = quizzes[i];
            assigned = true;
        } else if(quizzes[i] < lowest2) {
            lowest2 = quizzes[i];
        }
    }

    return (totalSum - lowest1 - lowest2) / 3.0;
}

// 2. Weighted Total calculations (Quiz: 10%, Assignment: 10%, Mid: 30%, Final: 50%)
double computeWeightedTotal(double quizAvg, double asgnAvg, double mid, double finalExam) {
    return (quizAvg * 0.10) + (asgnAvg * 0.10) + (mid * 0.30) + (finalExam * 0.50);
}

// 3. Absolute Letter Grade Authorization Map
string getLetterGrade(double totalMarks) {
    if (totalMarks >= 85.0) return "A";
    if (totalMarks >= 80.0) return "B+";
    if (totalMarks >= 70.0) return "B";
    if (totalMarks >= 65.0) return "C+";
    if (totalMarks >= 60.0) return "C";
    if (totalMarks >= 50.0) return "D";
    return "F";
}

// 4. Points Mapping for GPA Matrix
double gradeToPoints(const string& grade) {
    if (grade == "A") return 4.0;
    if (grade == "B+") return 3.5;
    if (grade == "B") return 3.0;
    if (grade == "C+") return 2.5;
    if (grade == "C") return 2.0;
    if (grade == "D") return 1.0;
    return 0.0;
}

// 5. Secure Academic Entry & Enrollment Attendance Check
void enterMarks() {
    string rollNo, courseCode, semester;
    cout << "\n--- Auth: Secure Grade Entry Assessment ---" << endl;
    cout << "Enter Student Roll No: ";
    cin >> rollNo;
    cout << "Enter Course Code: ";
    cin >> courseCode;
    cout << "Enter Semester: ";
    cin >> semester;

    // Attendance Verification Constraint (Eligibility Check)
    double attPct = getAttendancePct(rollNo, courseCode);
    bool attendanceDefaulter = (attPct < 75.0);

    double quizzes[5] = {0};
    int qCount;
    cout << "Enter number of quizzes taken (up to 5): ";
    cin >> qCount;
    if (qCount > 5) qCount = 5;

    for (int i = 0; i < qCount; i++) {
        cout << "  Quiz " << i + 1 << " Marks (out of 100): ";
        cin >> quizzes[i];
    }
    double quizAvg = bestThreeOfFive(quizzes, qCount);

    double asgn, mid, finalExam;
    cout << "Enter Assignments Average Marks (out of 100): ";
    cin >> asgn;
    cout << "Enter Mid Exam Marks (out of 100): ";
    cin >> mid;
    cout << "Enter Final Exam Marks (out of 100): ";
    cin >> finalExam;

    double weightedTotal = computeWeightedTotal(quizAvg, asgn, mid, finalExam);
    string finalGrade = getLetterGrade(weightedTotal);

    // Dynamic Attendance Block: Override grade to F automatically
    if (attendanceDefaulter) {
        finalGrade = "F";
        cout << "\n⚠️ Auth Authorization Breach: Student attendance is " << attPct << "% (<75%). Access Restricted. Grade forced to F!" << endl;
    }

    ofstream file("grades.txt", ios::app);
    if (file.is_open()) {
        file << rollNo << "," << courseCode << "," << semester << "," 
             << weightedTotal << "," << finalGrade << "\n";
        file.close();
        cout << "Success: Verified transaction logged. Grade committed: " << finalGrade << endl;
    }
}

// 6. Semester Dynamic Credit Weight GPA Engine
double computeGPA(const string& rollNo, const string& semester) {
    ifstream file("grades.txt");
    if (!file.is_open()) return 0.0;

    string line;
    getline(file, line); // header

    double totalPoints = 0.0;
    int totalCredits = 0;

    while (getline(file, line)) {
        if (line == "") continue;
        if (getColumnValue(line, 0) == rollNo && getColumnValue(line, 2) == semester) {
            string courseCode = getColumnValue(line, 1);
            string grade = getColumnValue(line, 4);
            
            int crHrs = 3; 
            ifstream cFile("courses.txt");
            if (cFile.is_open()) {
                string cLine;
                getline(cFile, cLine);
                while (getline(cFile, cLine)) {
                    if (cLine == "") continue;
                    if (getColumnValue(cLine, 0) == courseCode) {
                        crHrs = stoi(getColumnValue(cLine, 2));
                        break;
                    }
                }
                cFile.close();
            }

            totalPoints += (gradeToPoints(grade) * crHrs);
            totalCredits += crHrs;
        }
    }
    file.close();

    if (totalCredits == 0) return 0.0;
    return totalPoints / totalCredits;
}

// 7. Class Performance Evaluation Reports (Median & Mean)
void computeClassStats() {
    string courseCode, semester;
    cout << "Enter Course Code for Statistical Analytics: ";
    cin >> courseCode;
    cout << "Enter Semester: ";
    cin >> semester;

    ifstream file("grades.txt");
    if (!file.is_open()) return;

    double scoreArray[200];
    int count = 0;
    string line;
    getline(file, line);

    while (getline(file, line) && count < 200) {
        if (line == "") continue;
        if (getColumnValue(line, 1) == courseCode && getColumnValue(line, 2) == semester) {
            scoreArray[count++] = stod(getColumnValue(line, 3));
        }
    }
    file.close();

    if (count == 0) {
        cout << "Notice: No valid entries processed for current selection parameters." << endl;
        return;
    }

    // Pure Bubble Sort for Metrics calculations
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (scoreArray[j] > scoreArray[j + 1]) {
                double temp = scoreArray[j];
                scoreArray[j] = scoreArray[j + 1];
                scoreArray[j + 1] = temp;
            }
        }
    }

    double minScore = scoreArray[0];
    double maxScore = scoreArray[count - 1];
    double sum = 0;
    for (int i = 0; i < count; i++) sum += scoreArray[i];
    double mean = sum / count;

    double median;
    if (count % 2 == 0) {
        median = (scoreArray[count / 2 - 1] + scoreArray[count / 2]) / 2.0;
    } else {
        median = scoreArray[count / 2];
    }

    cout << "\n--- Verified Performance Audits (" << courseCode << ") ---" << endl;
    cout << "  Highest Authenticated Score: " << maxScore << endl;
    cout << "  Lowest Authenticated Score:  " << minScore << endl;
    cout << "  Class Authorized Mean:       " << mean << endl;
    cout << "  Class Authorized Median:     " << median << endl;
}
