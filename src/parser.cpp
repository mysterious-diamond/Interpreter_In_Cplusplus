#include "parser.h"

Parser::Parser(std::vector<Token> tokens)
    : tokens(tokens) {}

bool Parser::parse()
{
    while (currentIndex < tokens.size())
    {
        if (tokens[currentIndex].type == TokenType::LET)
        {
            currentIndex++;
            std::string name = tokens[currentIndex].value;

            currentIndex++;
            if (tokens[currentIndex].value != "=")
                return 1;

            currentIndex++;
            Token val = tokens[currentIndex];

            vars.insert({name, val});
            currentIndex++;
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