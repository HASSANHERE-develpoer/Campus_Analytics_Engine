#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

vector<string> readTXT(const string& filename);
bool appendTXT(const string& filename, const string& row);
string getColumnValue(const string& row, int colIndex);

#endif
