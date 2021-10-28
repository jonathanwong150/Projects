#include "ProgramState.h"
#include "Statement.h"

#ifndef ADD_STATEMENT_INCLUDED
#define ADD_STATEMENT_INCLUDED

class AddStatement : public Statement {
private:
    std::string m_variableName;
    std::string m_RHS;

public:
    AddStatement(std::string variableName, std::string RHS);
    ~AddStatement() {}
    virtual void execute(ProgramState* state, std::ostream& outf);
};

#endif