#include "ReturnStatement.h"

ReturnStatement::ReturnStatement() {}

void ReturnStatement::execute(ProgramState* state, std::ostream& outf) {
    // TODO
    state->jumpBack();
    state->incrementLines();
}
