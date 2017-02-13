//
// Created by Dana Short on 2016-06-30.
//
#include <string>
#ifndef INC_5421_A2_GETRANGE_H
#define INC_5421_A2_GETRANGE_H
using namespace std;

class getRange {
private:
    int currentLine;
    int lastLine;
    int start;
    int end;
    int getInt(string);
public:
    int getStart() const;
    int getEnd() const;
    void parseRange(string, int currentLine, int lastLine);
};


#endif //INC_5421_A2_GETRANGE_H
