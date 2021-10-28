#include "AddStatement.h"

AddStatement::AddStatement(std::string variableName, std::string RHS) : m_variableName(variableName), m_RHS(RHS) {}

void AddStatement::execute(ProgramState* state, std::ostream& outf) {
    // TODO
    state->incrementVar(m_variableName, m_RHS);  // Call helper
    state->incrementLines();
}
