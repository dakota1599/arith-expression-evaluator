#ifndef SCANNER
#define SCANNER
#include <iostream>
#include <string>
#include <vector>

enum TokenType
{
    NONE,
    OPERAND,
    OPERATOR,
    L_PAREN,
    R_PAREN
};

struct Token
{
    TokenType type;
    std::string value;

    std::string to_string();
};

class Scanner
{

private:
    std::vector<Token> tokens;
    std::string buffer;
    int start;
    int current;

public:
    Scanner(std::string input);

    std::vector<Token> get_tokens();

    void scan();

    bool isspace(char c);

    bool isoperator(char c);

    char consume();

    char peek();

    bool eof();

    std::string getString();

    void number();

    void add_token(TokenType type, std::string value);

    void op();

    void print();
};

#endif