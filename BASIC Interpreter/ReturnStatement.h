#ifndef RETURN_STATEMENT_INCLUDED
#define RETURN_STATEMENT_INCLUDED

#include "ProgramState.h"
#include "Statement.h"
#include <iostream>

class ReturnStatement : public Statement {
private:
public:
    ReturnStatement();
    ~ReturnStatement() {}
    virtual void execute(ProgramState* state, std::ostream& outf);
};

#endif
