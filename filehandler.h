#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <string>

// Global constant to restrict vector array simulations if required
// structured data parsing without STL split
int parseLineToFields(const std::string& line, std::string fields[], int maxFields);
std::string getColumnValue(const std::string& line, int columnIndex);

#endif
