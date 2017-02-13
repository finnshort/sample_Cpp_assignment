//
// Created by Dana Short on 2016-06-21.
//

#include "Command.h"
#include <string>
#include <iostream>
using namespace std;

char Command::parse(string input, int current, int last) {
    //reset start/end/command
    rangeStart = -1;
    rangeEnd = -1;
    command = '\0';
    if (input.empty()) {
        command = 'd';
        rangeEnd = 1;
    }
    else {
        prepareCommand(input);
            if (input.back() == 'q'){
                command = 'q';
        }
            else if (input.back() == 'w'){
                command = 'w';
        }
        else if (input.back() == '=') {
            command = '=';
        }
        else if (input.length() == 1 && (symbols.find(input.at(0)) != -1)) { //if length is one and the character is . $ or ,
            switch(input.back()){
                case '.' :
                    command = 'p';
                    rangeStart = current;
                    rangeEnd = current;
                    break;
                case '$':
                    command = 'p';
                    rangeStart = last;
                    rangeEnd = last;
                    break;
                case ',':
                    command = 'p';
                    rangeStart = 1;
                    rangeEnd = last;
                    break;
                default: cout << "not a valid char" << endl;
            }
        }

        else if (validCommands.find(input.back()) != -1) {
            //call one of the letter functions
            command = input.back();
            gr.parseRange(input.substr(0, (input.length()-1)), current, last);
            rangeStart = gr.getStart();
            rangeEnd = gr.getEnd();
        }
        else {
            //assume the command is print and any futher error checking happens in getRange
            //only valid other option is x, y (or ,. . "" , ., n, ,y x,)
            command = 'p';
            gr.parseRange(input, current, last);
            rangeStart = gr.getStart();
            rangeEnd = gr.getEnd();
        }
    }
    return command;
}


int Command::getStart() const{
    return rangeStart;
}

int Command::getEnd() const{
    return rangeEnd;
}

void Command::prepareCommand(string& input){
    std::transform(input.begin(), input.end(), input.begin(), ::tolower); //converts command to lower case
    input.erase(std::remove(input.begin(), input.end(), '\t'), input.end()); //removes tab characters
    input.erase(std::remove(input.begin(), input.end(), ' '), input.end()); //removes space characters
}
