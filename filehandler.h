#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <string>
#include <iostream>
#include <limits>

// Global constant to restrict vector array simulations if required
// structured data parsing without STL split
int parseLineToFields(const std::string& line, std::string fields[], int maxFields);
std::string getColumnValue(const std::string& line, int columnIndex);

// Crash-proof input handler (Adding this for your project stability)
inline void clearInput() {
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

#endif