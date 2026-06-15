#include <iostream>
#include <fstream>
#include <string>
#include "filehandler.h"

using namespace std;

// Character loop ke zariye line ko commas par split karne ka manual tareeqa (No external split library)
int parseLineToFields(const string& line, string fields[], int maxFields) {
    int fieldCount = 0;
    string currentField = "";
    bool insideQuotes = false;

    for (size_t i = 0; i < line.length(); i++) {
        char ch = line[i];

        if (ch == '"') {
            insideQuotes = !insideQuotes; // Handle fields wrapped in quotes
        } else if (ch == ',' && !insideQuotes) {
            if (fieldCount < maxFields) {
                fields[fieldCount++] = currentField;
            }
            currentField = "";
        } else {
            if (ch != '\r' && ch != '\n') {
                currentField += ch;
            }
        }
    }
    // Last field add karne ke liye
    if (fieldCount < maxFields) {
        fields[fieldCount++] = currentField;
    }
    return fieldCount;
}

// Kisi bhi text line se specific column index ki value nikalna
string getColumnValue(const string& line, int columnIndex) {
    string fields[20]; 
    int total = parseLineToFields(line, fields, 20);
    if (columnIndex >= 0 && columnIndex < total) {
        return fields[columnIndex];
    }
    return "";
}
