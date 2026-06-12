# Campus Analytics Engine (BS AI - Programming Fundamentals Project)

A multi-file, menu-driven data analytics and management system built using fundamental C++ constructs. The system processes real-world campus data logs for student profiles, course enrollments, attendance, and financial records directly from text files without using advanced database engines.

## 🚀 Project Features & Module Status

- **Module 1: User Authentication & Role Management**
  - [x] Secured login verification system for Admin and Students via `students.txt`.
- **Module 2: Student Record Management**
  - [ ] View student profiles and dynamically append new student records.
- **Module 3: Course & Enrollment Management**
  - [ ] Manage campus course listings and track active student enrollments.
- **Module 4: Attendance Management Engine**
  - [x] Log daily session attendance and calculate active percentages based on `attendance_log.txt`.
- **Module 5: Student & Course Analytics Engine**
  - [x] Parse class performance summaries, track course averages, and identify toppers using `enrollments.txt`.
- **Module 6: Financial & Fee Management Engine**
  - [ ] Track fee payment status, process direct student dues, and generate overall revenue logs.
- **Module 7: Console User Interface (UI) Dashboard**
  - [ ] Role-based multi-tier command menus for comprehensive system testing.

## 🛠️ Tech Stack & Constraints
- **Language:** C++ (Procedural Programming Focus)
- **File I/O:** Standard `<fstream>` file streams for data persistence.
- **Strict Syllabus Constraints:** - Strictly **NO** Object-Oriented Programming (`class` keyword is forbidden; structures are used).
  - Strictly **NO** Standard Template Library containers or algorithms (`<vector>`, `<map>`, `<algorithm>`, or `sort()` are completely absent).
  - Built entirely using basic loops, dynamic checking, and raw file streams as per core course requirements.

## 📁 Multi-File Architecture Overview
- `filehandler.h` / `filehandler.cpp` - Core custom utilities for comma-separated string tokenization and file appending.
- `auth.h` / `auth.cpp` - Verification mechanics mapping student emails and admin rules.
- `attendance.h` / `attendance.cpp` - Engine parsing logs to evaluate attendance statistics.
- `analytics.h` / `analytics.cpp` - Performance calculator evaluating course metrics and highest achievers.
-
