#ifndef GOTO_STATEMENT_INCLUDED
#define GOTO_STATEMENT_INCLUDED

#include "ProgramState.h"
#include "Statement.h"
#include <iostream>

class GoToStatement : public Statement {
private:
    int m_value;

public:
    GoToStatement(int val);
    ~GoToStatement() {}
    virtual void execute(ProgramState* state, std::ostream& outf);
};

#endif
