// Interpreter.cpp
#include "AddStatement.h"
#include "DivStatement.h"
#include "EndStatement.h"
#include "GoSubStatement.h"
#include "GoToStatement.h"
#include "IfStatement.h"
#include "LetStatement.h"
#include "MultStatement.h"
#include "PeriodStatement.h"
#include "PrintAllStatement.h"
#include "PrintStatement.h"
#include "ProgramState.h"
#include "ReturnStatement.h"
#include "Statement.h"
#include "SubStatement.h"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

// parseProgram() takes a filename as a parameter, opens and reads the
// contents of the file, and returns an vector of pointers to Statement.
void parseProgram(istream& inf, vector<Statement*>& program);

// parseLine() takes a line from the input file and returns a Statement
// pointer of the appropriate type.  This will be a handy method to call
// within your parseProgram() method.
Statement* parseLine(string line);

// interpretProgram() reads a program from the given input stream
// and interprets it, writing any output to the given output stream.
// Note:  you are required to implement this function!
void interpretProgram(istream& inf, ostream& outf);

int main() {
    cout << "Enter BASIC program file name: ";
    string filename;
    getline(cin, filename);
    ifstream infile(filename.c_str());
    if (!infile) {
        cout << "Cannot open " << filename << "!" << endl;
        return 1;
    }
    interpretProgram(infile, cout);
}

void parseProgram(istream& inf, vector<Statement*>& program) {
    program.push_back(NULL);

    string line;
    while (!inf.eof()) {
        getline(inf, line);
        program.push_back(parseLine(line));
    }
}

Statement* parseLine(string line) {
    Statement* statement;
    stringstream ss;
    string type;
    string var;
    int val;
    string RHS;      // Use for math classes
    string op;       // Operator string
    int trash;       // Line numbers
    string garbage;  // Handles THEN in IfStatement

    ss << line;
    ss >> trash;  // Get rid of all the line numbers
    ss >> type;   // Check what type of statement is on the line

    if (type == "LET") {
        ss >> var;  // Take in variables and values needed for that statement
        ss >> val;
        // Note:  Because the project spec states that we can assume the file
        //	  contains a syntactically legal program, we know that
        //	  any line that begins with "LET" will be followed by a space
        //	  and then a variable and then an integer value.
        statement = new LetStatement(var, val);  // Create statement
    }

    // Incomplete;  TODO:  Finish this function!

    if (type == "ADD") {
        ss >> var;  // Take in variable name and right hand variable as string
        ss >> RHS;
        statement = new AddStatement(var, RHS);
    }
    if (type == "SUB") {
        ss >> var;  // Same as addition
        ss >> RHS;
        statement = new SubStatement(var, RHS);
    }
    if (type == "DIV") {
        ss >> var;  // Same as addition
        ss >> RHS;
        statement = new DivStatement(var, RHS);
    }
    if (type == "MULT") {
        ss >> var;  // Same as addition
        ss >> RHS;
        statement = new MultStatement(var, RHS);
    }
    if (type == "PRINT") {
        ss >> var;  // Take the variable we want to print
        statement = new PrintStatement(var);
    }
    if (type == "PRINTALL") {  // No variables needed
        statement = new PrintAllStatement();
    }
    if (type == "GOTO") {
        ss >> val;  // Take line number we want to jump to
        statement = new GoToStatement(val);
    }
    if (type == "GOSUB") {
        ss >> val;
        statement = new GoSubStatement(val);
    }
    if (type == "RETURN") {
        statement = new ReturnStatement();
    }
    if (type == "IF") {
        ss >> var;  // Take in a variable name, operator type, right hand side string, and a line to jump to
        ss >> op;
        ss >> RHS;      // Compared integer
        ss >> garbage;  // THEN
        ss >> val;      // Line to jump to
        statement = new IfStatement(var, op, RHS, val);
    }
    if (type == "END") {
        statement = new EndStatement();
    }
    if (type == ".") {
        statement = new PeriodStatement();
    }

    return statement;
}

void interpretProgram(istream& inf, ostream& outf) {
    vector<Statement*> program;
    parseProgram(inf, program);

    // Incomplete;  TODO:  Finish this function!
    ProgramState* state
            = new ProgramState(program.size());   // Initialize a new program state that is the size of program
    while (program[state->getCount()] != NULL) {  // Loop through program vector
        try {                                     // Exception handling
            program[state->getCount()]->execute(state, outf);  // Execute statement
        } catch (out_of_range& e) {                            // Jumping out of range
            outf << e.what() << std::endl;
            state->stop();
        } catch (logic_error& e) {  // Dividing by 0
            outf << e.what() << std::endl;
            state->stop();
        }
    }
    for (unsigned int i = 0; i < program.size(); i++) {  // Deletion
        delete program[i];
    }
    delete state;
}