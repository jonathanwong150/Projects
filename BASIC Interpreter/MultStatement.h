#include "ProgramState.h"
#include "Statement.h"

#ifndef MULT_STATEMENT_INCLUDED
#define MULT_STATEMENT_INCLUDED

class MultStatement : public Statement {
private:
    std::string m_variableName;
    std::string m_RHS;

public:
    MultStatement(std::string variableName, std::string RHS);
    ~MultStatement() {}
    virtual void execute(ProgramState* state, std::ostream& outf);
};

#endif