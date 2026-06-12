#ifndef AUTH_H
#define AUTH_H

#include <iostream>
#include <string>

using namespace std;

// Module 1: Authentication Functions
bool loginUser(const string& email, const string& password, string& loggedInId, string& role);

#endif
