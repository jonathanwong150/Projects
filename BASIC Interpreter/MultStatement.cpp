#include "MultStatement.h"

MultStatement::MultStatement(std::string variableName, std::string RHS) : m_variableName(variableName), m_RHS(RHS) {}

void MultStatement::execute(ProgramState* state, std::ostream& outf) {
    // TODO
    state->multVar(m_variableName, m_RHS);  // Call Helper
    state->incrementLines();
}
