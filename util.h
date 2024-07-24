
#ifndef UTIL_H
#define UTIL_H

#include <string>

using namespace std;

class Util {
public:
    static string toUpper(const string& str);
    static string toLower(const string& str);
    static bool isNumber(const string& str);
};

#endif