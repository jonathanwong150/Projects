#include "GoToStatement.h"

GoToStatement::GoToStatement(int val) : m_value(val) {}

void GoToStatement::execute(ProgramState* state, std::ostream& outf) {
    // TODO
    state->jumpLine(m_value);  // Call helper and do not increment lines because we are jumping
}
