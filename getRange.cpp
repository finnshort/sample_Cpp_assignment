#include "getRange.h"
#include <string>
#include <iostream>
using namespace std;

int getRange::getStart() const{
    return start;
}
int getRange::getEnd() const{
    return end;
}
void getRange::parseRange(string range, int c, int l){
    currentLine = c;
    lastLine = l;
    start = 0;
    end = 0;

    if(range.length() == 0){
        start = currentLine;
        end = currentLine;
    }
    else if(range.length() == 1){
        if(range.front() == '.'){
            start = currentLine;
            end = currentLine;
        }
        else if(range.front() == '$'){
            start = lastLine;
            end = lastLine;
        }
        else if(range.front() == ','){
            start = currentLine;
            end = currentLine;
        }
        else{
            start = getInt(range);
            end = getInt(range);
        }
    }

    else {
        int separator;
        separator = range.find_first_of(',');
        if (separator == string::npos) {
            //no separator, has to be a multi digit integer or invalid
            start = getInt(range);
            end = getInt(range);
        }
        else if (separator == 0) {//',' is the first char
            start = currentLine;
            range.erase(range.begin());
            end = getInt(range);
        }
        else if (separator == range.length()-1){ //',' is the last char
            end = currentLine;
            range.pop_back();
            start = getInt(range);
        }
        else{ //separate into two number ranges
            string startStr = range.substr(0, separator);
                start = getInt(startStr);
            string endStr = range.substr(separator+1, string::npos);
            end = getInt(endStr);
            }
        }
}

int getRange::getInt(string s){
    if(s.find_first_of("$")!=string::npos){
        return lastLine;
    }
    if(s.find_first_of(".")!=string::npos){
        return currentLine;
    }
    int i;
    try {
    i = stoi(s);
    }
catch (const invalid_argument& ia){
    //Invalid range
    i = -1;
}
    return i;
}