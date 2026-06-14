#include <iostream>
#include <string>
#include "filehandler.h"

using namespace std;

string getColumnValue(const string& line, int columnIndex) {
    string value = "";
    int currentColumn = 0;
    
    for (size_t i = 0; i < line.length(); i++) {
        if (line[i] == ',') {
            currentColumn++;
        } else if (currentColumn == columnIndex) {
            if (line[i] != '\r' && line[i] != '\n') {
                value += line[i];
            }
        } else if (currentColumn > columnIndex) {
            break;
        }
    }
    return value;
}
