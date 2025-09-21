#include "parser.h"

Parser::Parser(std::vector<Token> tokens)
    : tokens(tokens) {}

int Parser::parse_Expr()
{
    int val = this->parse_Term();
    while (true)
    {
        if (tokens[currentIndex].type == TokenType::PLUS)
        {
            currentIndex++;
            val += this->parse_Term();
        }
        else if (tokens[currentIndex].type == TokenType::MINUS)
        {
            currentIndex++;
            val -= this->parse_Term();
        }
        else
            break;
    }
    return val;
}

int Parser::parse_Term()
{
    int val = parse_Factor();
    while (true)
    {
        if (tokens[currentIndex].type == TokenType::STAR)
        {
            currentIndex++;
            val *= this->parse_Factor();
        }
        else if (tokens[currentIndex].type == TokenType::SLASH)
        {
            currentIndex++;
            val /= this->parse_Factor();
        }
        else
            break;
    }
    return val;
}

int Parser::parse_Factor()
{
    if (tokens[currentIndex].type == TokenType::NUMBER)
    {
        currentIndex++;
        return std::stoi(tokens[currentIndex - 1].value);
    }
    else if (tokens[currentIndex].type == TokenType::LPAREN)
    {
        currentIndex++;
        int val = this->parse_Expr();
        if (tokens[currentIndex].type != TokenType::RPAREN)
        {
            throw std::runtime_error("Missing ')'");
        }
        currentIndex++;
        return val;
    }
    else if (tokens[currentIndex].type == TokenType::IDENTIFIER)
    {
        std::string name = tokens[currentIndex].value;
        currentIndex++;
        if (vars.find(name) == vars.end())
        {
            throw std::runtime_error("Undefined variable: " + name);
        }
        return std::stoi(vars[name].value);
    }

    throw std::runtime_error("Unexpected token in parse_Factor()");
}

bool Parser::parse()
{
    while (currentIndex < tokens.size())
    {
        if (tokens[currentIndex].type == TokenType::LET)
        {
            currentIndex++;
            std::string name = tokens[currentIndex].value;

            currentIndex++;
            if (tokens[currentIndex].type != TokenType::EQUAL)
                throw std::runtime_error("Missing '=' after variable declaration");

            currentIndex++;
            int res = this->parse_Expr();
            vars[name] = Token(TokenType::NUMBER, std::to_string(res));

            continue;
        }
        else if (tokens[currentIndex].type == TokenType::PRINT)
        {
            currentIndex++;
            if (tokens[currentIndex].value != "(")
                return 1;
            currentIndex++;

            if (tokens[currentIndex].type == TokenType::IDENTIFIER)
            {
                std::cout << vars[tokens[currentIndex].value].value << '\n';
                currentIndex++;
                currentIndex++;
                continue;
            }
            else if (tokens[currentIndex].type == TokenType::STRING)
            {
                std::cout << tokens[currentIndex].value << '\n';
                currentIndex++;
                currentIndex++;
                continue;
            }
        }
    }

    return 0;
}