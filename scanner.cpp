#include "include/scanner.hpp"

std::string Token::to_string()
{
    std::string t;
    switch (type)
    {
    case OPERAND:
        t = "OPERAND";
        break;
    case OPERATOR:
        t = "OPERATOR";
        break;
    case L_PAREN:
        t = "L_PAREN";
        break;
    case R_PAREN:
        t = "R_PAREN";
        break;
    }

    return "[" + t + " - " + value + "]";
}

Scanner::Scanner(std::string input)
{
    buffer = input;
    start = 0;
    current = 0;
}

std::vector<Token> Scanner::get_tokens()
{
    return tokens;
}

void Scanner::scan()
{
    while (!eof())
    {
        start = current;
        char c = consume();

        if (isdigit(c))
        {
            number();
        }
        else if (isoperator(c))
        {
            op();
        }

        switch (c)
        {
        case '(':
            add_token(L_PAREN, "(");
            break;
        case ')':
            add_token(R_PAREN, ")");
            break;
        }
    }
}

bool Scanner::isspace(char c)
{
    return c == ' ';
}

bool Scanner::isoperator(char c)
{
    switch (c)
    {
    case '+':
    case '-':
    case '/':
    case '*':
    case '^':
        return true;
    }

    return false;
}

char Scanner::consume()
{
    return buffer[current++];
}

char Scanner::peek()
{
    return buffer[current];
}

bool Scanner::eof()
{
    return current >= buffer.length();
}

std::string Scanner::getString()
{
    std::string res = "";

    for (int i = start; i < current; i++)
    {
        res += buffer[i];
    }

    return res;
}

void Scanner::number()
{
    while (isdigit(peek()))
        consume();

    if (peek() == '.')
    {
        consume();

        while (isdigit(peek()))
            consume();
    }

    add_token(OPERAND, getString());
}

void Scanner::add_token(TokenType type, std::string value)
{
    Token t;
    t.type = type;
    t.value = value;
    tokens.push_back(t);
}

void Scanner::op()
{
    add_token(OPERATOR, getString());
}

void Scanner::print()
{
    for (Token t : tokens)
    {
        std::cout << t.to_string() << "\n";
    }
}