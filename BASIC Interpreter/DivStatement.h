#include "ProgramState.h"
#include "Statement.h"

#ifndef DIV_STATEMENT_INCLUDED
#define DIV_STATEMENT_INCLUDED

class DivStatement : public Statement {
private:
    std::string m_variableName;
    std::string m_RHS;

public:
    DivStatement(std::string variableName, std::string RHS);
    ~DivStatement() {}
    virtual void execute(ProgramState* state, std::ostream& outf);
};

#endif