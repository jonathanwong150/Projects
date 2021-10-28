#include "SubStatement.h"

SubStatement::SubStatement(std::string variableName, std::string RHS) : m_variableName(variableName), m_RHS(RHS) {}

void SubStatement::execute(ProgramState* state, std::ostream& outf) {
    // TODO
    state->decrementVar(m_variableName, m_RHS);  // Call Helper
    state->incrementLines();
}
