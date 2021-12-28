#include "Util.h"
#include <vector>
#include <string>
using std::vector;
using std::string;
vector <string> Util::parse(string stringToParse, string sep, int startPos) {
    vector <string> info;
    size_t foundPos = stringToParse.find(sep, startPos);
    int lenSep = sep.length();
    while (foundPos != string::npos) {
        int lenString = foundPos - startPos;
        string token = stringToParse.substr(startPos, lenString);
        info.push_back(token);
        startPos = foundPos + lenSep;
        foundPos = stringToParse.find(sep, startPos);
    }
    int lenString = stringToParse.size() - startPos;
    info.push_back(stringToParse.substr(startPos, lenString));
    return info;
    
}