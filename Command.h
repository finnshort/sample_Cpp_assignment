//
// Created by Dana Short on 2016-06-21.
//

#ifndef INC_5421_A2_COMMAND_H
#define INC_5421_A2_COMMAND_H
#include <string>
#include "getRange.h"
using namespace std;
class Command {
private:
    char command;
    int rangeStart;
    int rangeEnd;
    void prepareCommand(string&);
    const string symbols= ".$,";
    const string validCommands = "airpncud";
    getRange gr;
public:
    char parse(string, int, int);
    int getStart() const;
    int getEnd() const;

};
#endif //INC_5421_A2_COMMAND_H
