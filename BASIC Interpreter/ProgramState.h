// ProgramState.h
//
// CS 104 / Fall 2021
//
// The ProgramState class encapsulates the state of an executing Facile
// program.  The state of a BASIC program consists of three parts:
//
//    * The program counter, which specifies the line number of the
//      statement that will execute next.
//    * A map, as explained by the problem writeup.
//    * A stack of integers, which is used to hold return lines for GOSUB
//      statements.
//
// We've provided you a start on this class, but you'll need to add methods
// to it as you go along.  In particular, you'll need methods to access and
// modify the state; these methods will be called primarily by the various
// execute() methods in the Statement subclasses, to allow the execution of
// a statement to change the state of a program.  For example, executing a
// GOTO statement will cause the program counter to be changed.

#ifndef PROGRAM_STATE_INCLUDED
#define PROGRAM_STATE_INCLUDED
#include <cmath>
#include <iostream>
#include <iterator>
#include <map>
#include <stack>
#include <stdexcept>
#include <string>

class ProgramState {
public:
    ProgramState(int numLines);

    // You'll need to add a variety of methods here.  Rather than trying to
    // think of what you'll need to add ahead of time, add them as you find
    // that you need them.
    void addPair(std::string var, int val);
    void incrementLines();
    void incrementVar(std::string var, std::string RHS);
    void decrementVar(std::string var, std::string RHS);
    void divideVar(std::string var, std::string RHS);
    void multVar(std::string var, std::string RHS);
    void print(std::string var, std::ostream& outf);
    void printAll(std::ostream& outf);
    void jumpLine(int val);
    void jumpSub(int val);
    void jumpBack();
    void ifJump(std::string var, std::string op, std::string RHS, int val);
    void stop();
    int getCount();

private:
    int m_numLines;
    std::map<std::string, int> m;
    int lineCount;
    std::stack<int> s;
};

#endif
