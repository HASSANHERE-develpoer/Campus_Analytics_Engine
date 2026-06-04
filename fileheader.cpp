#include "filehandler.h"

// 1. readTXT: File se data read karne ke liye
vector<string> readTXT(const string& filename) {
    vector<string> rows;
    ifstream file(filename);
    
    if (!file.is_open()) {
        return rows; 
    }
    
    string line;
    getline(file, line); // Pehli line (Header) mita di / skip ki
    
    while (getline(file, line)) {
        if (line != "") {
            rows.push_back(line); // Aik aik line array me daal di
        }
    }
    
    file.close();
    return rows;
}

// 2. appendTXT: File me naya data likhne ke liye
bool appendTXT(const string& filename, const string& row) {
    ofstream file(filename, ios::app); // ios::app ka matlab hai end me add karna
    
    if (!file.is_open()) {
        return false;
    }
    
    file << row << "\n"; // Nayi row file me write kar di
    file.close();
    return true;
}

// 3. getColumnValue: Comma (,) dhoond kar column alag karne ka aasan tarika
string getColumnValue(const string& row, int colIndex) {
    string currentField = "";
    int commaCount = 0;
    
    // Simple loop jo poori line ke aik aik character ko check karega
    for (int i = 0; i < row.length(); i++) {
        if (row[i] == ',') {
            if (commaCount == colIndex) {
                return currentField; // Agar target column mil gaya toh return karo
            }
            currentField = ""; // Agle column ke liye string khali karo
            commaCount++;      // Commas ki ginti barhao
        } else {
            currentField += row[i]; // Character ko jorte jao
        }
    }
    
    if (commaCount == colIndex) {
        return currentField; // Aakhri column ke liye
    }
    return "";
}
