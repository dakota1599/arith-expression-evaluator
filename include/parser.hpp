#ifndef PARSER
#define PARSER
#include <vector>
#include <stack>
#include <string>
#include "scanner.hpp"
class Parser
{
private:
    std::vector<Token> tokens;

    std::stack<std::string> values;

    std::stack<std::string> ops;

    bool isoperator(Token t);

    bool isoperand(Token t);

    bool is_r_paren(Token t);

    bool is_l_paren(Token t);

    int precedence(std::string op);

    bool isfloat(std::string s)
    {
        return s.find(".") != std::string::npos;
    }

    std::string applyOp(float f1, float f2, std::string op);

    std::string applyOp(int i1, int i2, std::string op);

public:
    Parser(std::vector<Token> toks);

    std::string parse();

    std::string to_string();
};

#endif