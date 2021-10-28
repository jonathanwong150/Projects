#ifndef IF_STATEMENT_INCLUDED
#define IF_STATEMENT_INCLUDED

#include "ProgramState.h"
#include "Statement.h"
#include <iostream>

class IfStatement : public Statement {
private:
    std::string m_variableName;
    std::string m_operator;
    std::string m_RHS;
    int m_value;

public:
    IfStatement(std::string var, std::string op, std::string RHS, int val);
    ~IfStatement() {}
    virtual void execute(ProgramState* state, std::ostream& outf);
};

#endif
