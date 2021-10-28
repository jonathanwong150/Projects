// PrintAllStatement.cpp:
#include "PrintAllStatement.h"

PrintAllStatement::PrintAllStatement() {}

void PrintAllStatement::execute(ProgramState* state, std::ostream& outf) {
    state->printAll(outf);  // Call helper
    state->incrementLines();
}
