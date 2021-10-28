#include "EndStatement.h"

EndStatement::EndStatement() {}

void EndStatement::execute(ProgramState* state, std::ostream& outf) {
    // TODO
    state->stop();  // Call stop
}
