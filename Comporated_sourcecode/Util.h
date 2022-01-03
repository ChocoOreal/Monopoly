#pragma once
#include <vector>
#include <string>
using std::vector;
using std::string;
class Util {
public:
    static vector <string> parse(string stringToParse, string sep, int startPos);
};