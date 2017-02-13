//
// Created by Dana Short on 2016-06-21.
//

#include "LineEditor.h"
#include <iostream>
#include <fstream>
using namespace std;


//CONSTRUCTORS

LineEditor::LineEditor(){
    newFile();
};

LineEditor::LineEditor(string fname){
    if (fname == ""){
        newFile();
    }
    else {
        fileName = fname;
        ifstream fin;
        fin.open(fileName);
        if (!fin.is_open()) {
            cout << "File not found" << endl;
            newFile(fileName); //create a new file with the passed name
        }
         //copy the lines into the file
        else {
            string temp;
            while (getline(fin, temp, '\n')) {
                buffer.push_back(temp);
            }
            fin.close();
            current = buffer.end();
            counter = buffer.size();
            //start an editing session
            cout << "\"" + fileName + "\" " << buffer.size() << " line(s)" << endl;
            cout << "Entering command mode." << endl;
            run();
        }
    }

};

//Endless loop to accept commands until quit
void LineEditor::run(){
    string input;
    while (1) {
        cout << ": ";
        getline(cin, input);
            //parse the command and select a function, passing range parameters as appropriate
            char ch = command.parse(input, counter, buffer.size());
            switch(ch) {
                case 'q':
                    quit();
                    break;
                case 'w':
                    write();
                    break;
                case '=':
                    lineAddress();
                    break;
                case 'i':
                    insert(command.getEnd());
                    break;
                case 'a':
                    append(command.getEnd());
                    break;
                case 'd':
                    down(command.getEnd());
                    break;
                case 'u':
                    up(command.getEnd());
                    break;
                case 'r':
                    remove(command.getStart(), command.getEnd());
                    break;
                case 'p':
                    print(command.getStart(), command.getEnd());
                    break;
                case 'n':
                    nprint(command.getStart(), command.getEnd());
                    break;
                case 'c':
                    change(command.getStart(), command.getEnd());
                    break;
                default: cout << "not a valid command character" << endl;
            }
   }
};

void LineEditor::newFile(string name){
    cout <<  "\"" + name + "\" [New File]" << endl;
    cout << "Warning: you must either append (a) or insert (i) content to the led before editing can begin" << endl; //warn user of empty buffer
    cout << "Entering command mode." << endl;
    //start an editing session
    run();
}


//**FUNCTIONS**//


int LineEditor::getCounter() const{
    if(buffer.empty()){
        cout << "Buffer is empty." << endl;
    }
    return counter;
};

void LineEditor::quit() {
    cout << "Do you want to save your file? (y/n)" << endl;
    char c = cin.get();
    cin.ignore(); //flush cin
    if (c == 'y' || c == 'Y'){
        write();
        cout << "Saved!" << endl;
    }
    cout << "Bye!" << endl;
    exit(22);
}

void LineEditor::write() {
    if(fileName.empty()){
        cout << "Enter the name of your new file: " << endl;
        getline(cin, this->fileName, '\n');
    }
    ofstream writeFile(this->fileName, ios::out);
    if(!writeFile){
        cerr<<"File could not be opened" << endl;
    }
    else{
        for(auto it = buffer.begin(); it != buffer.end(); it++){
            writeFile << *it << endl;
        }
    }
    writeFile.close();
}

void LineEditor::lineAddress() const{
    cout << getCounter() << endl;
}

void LineEditor::insert(int a) {
    //If empty, go to pos 1
    if (buffer.size() == 0) {
        cout << "The buffer is current empty, inserting content at position 1. Enter '.' to exit." << endl;
        current = buffer.begin();
        counter = 1;
    }
        //If out of range, escape function
    else if (a < 1 || a > buffer.size()) {
        cout << "Invalid range." << endl;
        return;
    }
    else {
        moveCounter(a);
    }
    cout << "Entering input mode. " << endl;
    string temp;
    while (getline(cin, temp, '\n')) {
        if (temp.compare(".") == 0) {
            //move current and counter to last line entered if exiting input mode
            if(buffer.empty()){
                counter--;
                cout << "Warning: buffer is empty, insert or append lines to continue editing." << endl;
                break;
            }
            else {
                current--;
                counter--;
                break;
            }
        }
        else {
            buffer.insert(current, temp);
            counter++;
        }
    }
}

void LineEditor::append(int a){
    //If empty, go to pos 1
    if (buffer.size() == 0) {
        cout << "The buffer is empty, inserting content at position 1. Enter '.' to exit." << endl;
        current = buffer.begin();
        counter = 1;
    }
        //If out of range, escape function
    else if (a < 1 || a > buffer.size()) {
        cout << "Invalid range (reported from inside append)" << endl;
        return;
    }
        //appending at the end of the file requires special case
    else if(a==buffer.size()){
        moveCounter(a);
        cout << "Entering input mode." << endl;
        string temp;
        while (getline(cin, temp, '\n')) {
            if (temp.compare(".") == 0) {
                break;
            }
            else {
                buffer.push_back(temp);
                current++;
                counter++;
            }
        }
    return;
    }
        //Normal case for append
    else {
        moveCounter(a + 1);
    }
    cout << "Entering input mode." << endl;
    string temp;
    while (getline(cin, temp, '\n')) {
        if (temp.compare(".") == 0) {
            //move current and counter to last line entered
            if(buffer.empty()){
                counter--;
                cout << "Warning: buffer is empty, insert or append lines to continue editing." << endl;
                break;
            }
            else {
                current--;
                counter--;
                break;
            }
        }
        else {
            buffer.insert(current, temp);
            counter++;
        }
    }
}

void LineEditor::up(int a) {
    if (counter - a < 1) {
        cout << "Invalid range" << endl;
    }
    else {
        for (int i = 0; i < a; i++) {
            current--;
            counter--;
        }
    }
}

void LineEditor::down(int a) {
    if (counter + a > buffer.size()) {
        cout << "Invalid range" << endl;
    }
    else {
        for (int i = 0; i < a; i++) {
            current++;
            counter++;
        }
    }
}

void LineEditor::remove(int a, int b) {
    if (validate(a, b)) {
        current = buffer.begin();
        std::advance(current, a - 1);
        auto it2 = buffer.begin();
        std::advance(it2, b);
        current = buffer.erase(current, it2);

        //update current and counter
        if (buffer.size() < a) {
            current--;
            counter = a - 1;
        }
        else counter = a;
    }
    if (buffer.empty())
    {
        cout << "Warning: buffer is empty, insert or append lines to continue editing." << endl;
    }}

void LineEditor::change(int a, int b) {
    if (validate(a, b)) {
        //Get the find & replace text
        string find;
        string replace;
        cout << "Enter the text to be changed: " << endl;
        getline(cin, find, '\n');
        cout << "Enter the replacement text: " << endl;
        getline(cin, replace, '\n');

        //set the ranges
        auto listIt = buffer.begin();
        auto end = buffer.begin();
        std::advance(listIt, a - 1); //starts at 1
        std::advance(end, b);

        //search and replace text
        for (listIt; listIt != end; listIt++) {
            size_t length = find.length();
            size_t pos = listIt->find(find);
            while (pos != string::npos) {
                auto it = listIt->begin();
                std::advance(it, pos);
                auto it2 = std::next(it, length);
                listIt->erase(it, it2);
                listIt->insert(pos, replace);
                pos = listIt->find(find);
            }
        }
    }
}

void LineEditor::print(int a, int b){
    if (validate(a, b)) {
        moveCounter(a);
        while (counter < b) {
            cout << *current << endl;
            current++;
            counter++;
        }
        cout << *current << endl; //print the last line
    }
}

void LineEditor::nprint(int a, int b) {
    if (validate(a, b)) {
        moveCounter(a);
        while (counter < b) {
            cout << counter << '\t' << *current << endl;
            current++;
            counter++;
        }
        cout << counter << '\t' << *current << endl; //print the last line
    }
}

void LineEditor::moveCounter(int a) {
    if (a > buffer.size()) {
        cout << "Invalid range" << endl;
    }
    else {
        current = buffer.begin();
        counter = 1;
        //advance iterator and counter
        while (counter < a) {
            current++;
            counter++;
        }
    }
}

bool LineEditor::validate(int a, int b){
    if(a<1 || a>buffer.size()){
        cout << "Invalid command or range" << endl;
        return 0;
}
    if(b<1 || b>buffer.size() || b<a){
        cout << "Invalid command or range" << endl;
        return 0;
    }
    return 1;
}
