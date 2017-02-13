#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <algorithm>
#include "LineEditor.h"
#include "Command.h"
#include "getRange.h"
using namespace std;


//MAIN THAT WORKS IN TERMINAL IF LINKER IS WORKING

int main(int argc, char * argv[]) {
    string s;
switch (argc) {
    case 1: //no file name
    {
        LineEditor ed = LineEditor("");
        break;
    }
    case 2:
    {
        s = argv[1];
        LineEditor ed = LineEditor(s);
        break;
    }
    default:
        cout << "too many arguments, all discarded" << endl;
        s.clear();
        break;
}
    return 0;

}

//IF LINKER NOT WORKING, THIS MAIN WORKS INSIDE IDE, PASS FILENAME UPON RUN
/*
int main(){
    string s;
    cout << "Please enter the filename: " << endl;
    cin >> s;
    cin.ignore(); //flushes cin
    LineEditor ed = LineEditor(s);
}
*/
