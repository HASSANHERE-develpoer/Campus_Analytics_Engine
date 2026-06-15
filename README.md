# Campus Analytics Engine (BSAI Project)

A high-performance, modular, and enterprise-grade command-line application built entirely in fundamental C++ to manage and analyze educational campus records.

## 🚀 Key Architectural Highlights
- **Zero OOP Frameworks:** Developed strictly using primitive data types, custom structures (`struct`), and structural programming guidelines.
- **No STL Algorithms or Containers:** Built manually without `#include <algorithm>`, `<vector>`, `<map>`, or `<set>`. All processing, substring searching, matching, and data splitting loops are engineered from scratch.
- **Custom Database Parsing:** Implemented absolute manual character scanning and token parsing workflows to manage relationships across `.txt` storage ledgers.
- **Pure Arithmetic Utilities:** Features manual month-length leap-year verification workflows for late fine calculation without the `<ctime>` library.

---

## 📂 Core Modules Reference
- **M1: Filehandler Module (`filehandler.h/.cpp`)** — Handles lower-level parsing, tracking separators, and processing records manually.
- **M2: Student Registry Management (`student_ops.h/.cpp`)** — Implements roll number format validation (`BSAI-YY-XXX`), soft-delete flag masking, and custom data lookups.
- **M3: Course Allocations & Prerequisites (`course_ops.h/.cpp`)** — Manages active course enrollment logs, checks section capacities, and strictly enforces a 21-credit hour limit.
- **M4: Attendance Tracker Sheet (`attendance.h/.cpp`)** — Logs daily roll calls, monitors shortages below 75%, and supports a transactional undo/rollback feature via a manual backup snapshot buffer.
- **M5: Auth Grading Engine (`auth.h/.cpp`)** — Processes custom quiz drop logic (best 3-of-5), scales weighted distributions, and automatically overrides performance to a failing 'F' grade for attendance defaulters.
- **M6: Fee Tracker & Financial Ledger (`fee_tracker.h/.cpp`)** — Manages balance tuition deposits, imposes a weekly 2% overdue fine layout, and prints cleanly spaced tabular receipts.
- **M7: Analytics Insights Engine (`analytics.h/.cpp`)** — Computes structural metrics (Class Mean and Median via bubble sort) and exports analytical headcount trends to `system_export_report.txt`.
- **M0: Central Controller Dashboard (`main.cpp`)** — Integrates all components into an interactive, 3-level nested CLI terminal interface.

---

## 💾 Core Data Repositories (.txt Databases)
The application dynamically targets and updates the following data states:
1. `students.txt` - Student profiles directory
2. `courses.txt` - Curriculum configuration rules
3. `enrollments.txt` - Registered structural credit maps
4. `attendance_log.txt` - Date-wise attendance entries
5. `fees.txt` - Accounts balances and late checkpoints

---

## 🛠️ Compilation and Execution Instructions

### Prerequisites
Ensure you have the GCC/MinGW compiler toolchain installed on your operating system environment.

### 1. Unified Compilation Command
Execute the following unified command in your terminal/command prompt inside the repository folder to compile all modules securely:
```bash
g++ main
