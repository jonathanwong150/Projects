#ifndef END_STATEMENT_INCLUDED
#define END_STATEMENT_INCLUDED

#include "ProgramState.h"
#include "Statement.h"
#include <iostream>

class EndStatement : public Statement {
private:
public:
    EndStatement();
    ~EndStatement() {}
    virtual void execute(ProgramState* state, std::ostream& outf);
};

#endif
