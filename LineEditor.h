//
// Created by Dana Short on 2016-06-21.
//
#include<string>
#include <list>
#include "Command.h"
#ifndef INC_5421_A2_LINEEDITOR_H
#define INC_5421_A2_LINEEDITOR_H
using namespace std;

class LineEditor {
private:
    string fileName;
    void newFile(string name = "?");

    list<string> buffer;
    list<string>::iterator current; //iterator to access current string in the buffer
    int counter = 0; //list does not support random access so need a counter
    Command command;

    //Commands
    void quit();
    void write(); //not const : could modify string fileName
    void lineAddress() const;
    void insert(int);
    void append(int);
    void up(int);
    void down(int);
    void remove(int, int);
    void change(int, int);
    void print(int, int);
    void nprint(int, int);
    void moveCounter(int);
    bool validate(int, int);

public:
    LineEditor(); //constructor with no file name
    LineEditor(string); //constructor with file name
    void run();
    int getCounter() const;
};


#endif //INC_5421_A2_LINEEDITOR_H
