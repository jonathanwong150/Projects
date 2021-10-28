#ifndef PRINTALL_STATEMENT_INCLUDED
#define PRINTALL_STATEMENT_INCLUDED

#include "ProgramState.h"
#include "Statement.h"
#include <iostream>

class PrintAllStatement : public Statement {
private:
public:
    PrintAllStatement();
    ~PrintAllStatement() {}
    virtual void execute(ProgramState* state, std::ostream& outf);
};

#endif
