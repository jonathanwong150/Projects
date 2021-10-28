#include "ProgramState.h"

ProgramState::ProgramState(int numLines) {  // Constructor
    m_numLines = numLines;                  // Set how many lines are in the program
    lineCount = 1;                          // Start at the first line
}
void ProgramState::incrementLines() {
    lineCount++;  // Go to next line
}
void ProgramState::addPair(std::string var, int num) {
    std::map<std::string, int>::iterator it;
    it = m.find(var);  // Find if the variable already exists in map
    if (it != m.end()) {
        it->second = num;  // If yes, update value
    } else {
        m.insert(std::pair<std::string, int>(var, num));  // If no, insert the pair
    }
}
void ProgramState::incrementVar(std::string var, std::string RHS) {
    std::map<std::string, int>::iterator it;
    it = m.find(RHS);  // Check if RHS value is a variable name
    int temp;
    if (it != m.end()) {
        temp = it->second;  // If it exists in the map already, it is a name and we should find the value of it
    } else {
        temp = stoi(RHS);  // If it is not in the map, it must be an int so we will cast it
    }
    it = m.find(var);    // Find the first variable
    it->second += temp;  // Add
}
void ProgramState::decrementVar(std::string var, std::string RHS) {  // Same concept as Add
    std::map<std::string, int>::iterator it;
    it = m.find(RHS);
    int temp;
    if (it != m.end()) {
        temp = it->second;
    } else {
        temp = stoi(RHS);
    }
    it = m.find(var);
    it->second -= temp;
}
void ProgramState::divideVar(std::string var, std::string RHS) {  // Same concept as add
    std::map<std::string, int>::iterator it;
    it = m.find(RHS);
    int temp;
    if (it != m.end()) {
        temp = it->second;
    } else {
        temp = stoi(RHS);
    }
    if (temp == 0) {  // Check if there is a divide by 0 error
        throw std::logic_error("Divide by Zero Error.");
    }
    it = m.find(var);
    it->second = floor((double)it->second / (double)temp);  // Make sure the floor works. Edge case
}
void ProgramState::multVar(std::string var, std::string RHS) {
    std::map<std::string, int>::iterator it;
    it = m.find(RHS);
    int temp;
    if (it != m.end()) {
        temp = it->second;
    } else {
        temp = stoi(RHS);
    }
    it = m.find(var);
    it->second *= temp;
}
void ProgramState::print(std::string var, std::ostream& outf) {
    std::map<std::string, int>::iterator it;
    it = m.find(var);  // Find the variable we want to print
    if (it != m.end()) {
        outf << it->second << std::endl;  // If it exists print it
    } else {
        outf << "0" << std::endl;  // If not print 0
    }
}
void ProgramState::printAll(std::ostream& outf) {
    std::map<std::string, int>::iterator it;
    for (it = m.begin(); it != m.end(); it++) {  // Loop through the map and print key and value
        outf << it->first << " " << it->second << std::endl;
    }
}
void ProgramState::jumpLine(int val) {
    if (val < 0 || val >= m_numLines) {  // Exception handling
        throw std::out_of_range("Illegal jump instruction.");
    }
    lineCount = val;  // Jump to line and dont look back
}
void ProgramState::jumpSub(int val) {
    if (val < 0 || val >= m_numLines) {
        throw std::out_of_range("Illegal jump instruction.");
    }
    s.push(lineCount);  // Keep track of the goSub statement and then jump
    lineCount = val;
}
void ProgramState::jumpBack() {
    if (s.empty()) {
        stop();  // Treat return as end statement if it does not have a corresponding goSub
    } else {
        lineCount = s.top();  // Otherwise, jump back and pop
        s.pop();
    }
}
void ProgramState::ifJump(std::string var, std::string op, std::string RHS, int val) {
    if (val < 0 || val >= m_numLines) {
        throw std::out_of_range("Illegal jump instruction.");
    }
    int comp = stoi(RHS);  // cast the int we are comparing to
    std::map<std::string, int>::iterator it;
    it = m.find(var);  // Find our variable
    int temp;
    if (it != m.end()) {
        temp = it->second;
    }
    if (op == "<") {  // Check if operaor is true, if so, jump
        if (temp < comp) {
            jumpLine(val);
        }
    }
    if (op == "<=") {
        if (temp <= comp) {
            jumpLine(val);
        }
    }
    if (op == ">") {
        if (temp > comp) {
            jumpLine(val);
        }
    }
    if (op == ">=") {
        if (temp >= comp) {
            jumpLine(val);
        }
    }
    if (op == "=") {
        if (temp == comp) {
            jumpLine(val);
        }
    }
    if (op == "<>") {
        if (temp != comp) {
            jumpLine(val);
        }
    }
}
void ProgramState::stop() {  // Sets the lineCount to index 0 which is a nulll pointer
    lineCount = 0;
}
int ProgramState::getCount() {
    return lineCount;  // Returns what line we are on
}