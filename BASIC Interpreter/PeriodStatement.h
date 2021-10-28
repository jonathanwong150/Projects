#ifndef PERIOD_STATEMENT_INCLUDED
#define PERIOD_STATEMENT_INCLUDED

#include "ProgramState.h"
#include "Statement.h"
#include <iostream>

class PeriodStatement : public Statement {
private:
public:
    PeriodStatement();
    ~PeriodStatement() {}
    virtual void execute(ProgramState* state, std::ostream& outf);
};

#endif
