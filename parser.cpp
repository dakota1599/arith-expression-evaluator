#include "include/parser.hpp"

Parser::Parser(std::vector<Token> toks)
{
    tokens = toks;
}

std::string Parser::applyOp(float f1, float f2, std::string op)
{

    if (op == "+")
        return std::to_string(f1 + f2);

    if (op == "-")
        return std::to_string(f1 - f2);

    if (op == "*")
        return std::to_string(f1 * f2);

    return std::to_string(f1 / f2);
}

std::string Parser::applyOp(int i1, int i2, std::string op)
{

    if (op == "+")
        return std::to_string(i1 + i2);

    if (op == "-")
        return std::to_string(i1 - i2);

    if (op == "*")
        return std::to_string(i1 * i2);

    return std::to_string(i1 / i2);
}

// Parse method using the Shunting Yard Algorithm by Edgar Dijkstra.
std::string Parser::parse()
{
    for (int i = 0; i < tokens.size(); i++)
    {
        // If L Paren.
        if (is_l_paren(tokens[i]))
        {
            ops.push(tokens[i].value);
        }

        else if (isoperand(tokens[i]))
        {
            values.push(tokens[i].value);
        }

        // Closing paren found, solve entire section.
        else if (is_r_paren(tokens[i]))
        {
            while (!ops.empty() && ops.top() != "(")
            {
                std::string val2 = values.top();
                values.pop();

                std::string val1 = values.top();
                values.pop();

                std::string op = ops.top();
                ops.pop();

                if (isfloat(val1) || isfloat(val2))
                {
                    values.push(applyOp(std::stof(val1), std::stof(val2), op));
                }
                else
                {
                    values.push(applyOp(std::stoi(val1), std::stoi(val2), op));
                }
            }

            // Pop opening paren.
            if (!ops.empty())
            {
                ops.pop();
            }
        }

        // If not the above, must be an operator.
        else
        {
            // While top of 'ops' has same or greater precedence to current token, which is an operator.
            // Apply operator on top of 'ops' to top two elements in values stack.
            while (!ops.empty() && precedence(ops.top()) >= precedence(tokens[i].value))
            {
                std::string val2 = values.top();
                values.pop();

                std::string val1 = values.top();
                values.pop();

                std::string op = ops.top();
                ops.pop();

                if (isfloat(val1) || isfloat(val2))
                {
                    values.push(applyOp(std::stof(val1), std::stof(val2), op));
                }
                else
                {
                    values.push(applyOp(std::stoi(val1), std::stoi(val2), op));
                }
            }

            ops.push(tokens[i].value);
        }
    }

    while (!ops.empty())
    {
        std::string val2 = values.top();
        values.pop();

        std::string val1 = values.top();
        values.pop();

        std::string op = ops.top();
        ops.pop();

        if (isfloat(val1) || isfloat(val2))
        {
            values.push(applyOp(std::stof(val1), std::stof(val2), op));
        }
        else
        {
            values.push(applyOp(std::stoi(val1), std::stoi(val2), op));
        }
    }

    return values.top();
}

bool Parser::isoperator(Token nt)
{
    return nt.type == OPERATOR;
}

bool Parser::isoperand(Token nt)
{
    return nt.type == OPERAND;
}

bool Parser::is_r_paren(Token nt)
{
    return nt.type == R_PAREN;
}

bool Parser::is_l_paren(Token nt)
{
    return nt.type == L_PAREN;
}

int Parser::precedence(std::string op)
{
    if (op == "+" || op == "-")
        return 1;

    if (op == "*" || op == "/")
        return 2;

    return 0;
}