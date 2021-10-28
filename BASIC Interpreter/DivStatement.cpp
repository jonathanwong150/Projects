#include "DivStatement.h"

DivStatement::DivStatement(std::string variableName, std::string RHS) : m_variableName(variableName), m_RHS(RHS) {}

void DivStatement::execute(ProgramState* state, std::ostream& outf) {
    // TODO
    state->divideVar(m_variableName, m_RHS);  // Call Helper
    state->incrementLines();
}
