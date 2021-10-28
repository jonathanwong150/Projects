#include "GoSubStatement.h"

GoSubStatement::GoSubStatement(int val) : m_value(val) {}

void GoSubStatement::execute(ProgramState* state, std::ostream& outf) {
    // TODO
    state->jumpSub(m_value);
}
