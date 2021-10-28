// LetStatement.cpp:
#include "LetStatement.h"

LetStatement::LetStatement(std::string variableName, int value)
        : m_variableName(variableName),
          m_value(value)  // Create variables
{}

// The LetStatement version of execute() should make two changes to the
// state of the program:
//
//    * set the value of the appropriate variable
//    * increment the program counter
void LetStatement::execute(ProgramState* state, std::ostream& outf) {
    // TODO
    state->addPair(m_variableName, m_value);  // Call addpair
    state->incrementLines();                  // Increment
}
