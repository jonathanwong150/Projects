#include "ProgramState.h"
#include "Statement.h"

#ifndef SUB_STATEMENT_INCLUDED
#define SUB_STATEMENT_INCLUDED

class SubStatement : public Statement {
private:
    std::string m_variableName;
    std::string m_RHS;

public:
    SubStatement(std::string variableName, std::string RHS);
    ~SubStatement() {}
    virtual void execute(ProgramState* state, std::ostream& outf);
};

#endif