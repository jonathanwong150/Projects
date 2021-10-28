#include "IfStatement.h"

IfStatement::IfStatement(std::string var, std::string op, std::string RHS, int val)
        : m_variableName(var), m_operator(op), m_RHS(RHS), m_value(val) {}

void IfStatement::execute(ProgramState* state, std::ostream& outf) {
    // TODO
    state->ifJump(m_variableName, m_operator, m_RHS, m_value);
}
