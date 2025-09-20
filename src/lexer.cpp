#include <iostream>
#include <cctype>
#include "lexer.h"

Lexer::Lexer(const std::string TEXT)
{
    this->text = TEXT;
    currentIndex = 0;
}

std::vector<Token> Lexer::tokenize()
{
    std::vector<Token> tokens;

    // Lexer/Tokenizer loop
    while (currentIndex < text.size())
    {
        char c = text[currentIndex];

        if (isspace(c))
        {
            currentIndex++;
            continue;
        }
        else if (isalpha(c))
        {
            std::string current(1, c);
            currentIndex++;
            while (currentIndex < text.size() && isalpha(text[currentIndex]))
            {
                current += text[currentIndex];
                currentIndex++;
            }

            if (current == "let")
                tokens.push_back(Token(TokenType::LET, current));
            else if (current == "print")
                tokens.push_back(Token(TokenType::PRINT, current));
            else
                tokens.push_back(Token(TokenType::IDENTIFIER, current));
            continue;
        }
        else if (isdigit(c))
        {
            std::string current(1, c);
            currentIndex++;
            while (currentIndex < text.size() && isdigit(text[currentIndex]))
            {
                current += text[currentIndex];
                currentIndex++;
            }

            tokens.push_back(Token(TokenType::NUMBER, current));
            continue;
        }
        else if (c == '"')
        {
            std::string current;
            currentIndex++;
            while (currentIndex < text.size() && text[currentIndex] != '"')
            {
                current += text[currentIndex];
                currentIndex++;
            }
            currentIndex++;
            tokens.push_back(Token(TokenType::STRING, current));
        }
        else if (c == '=')
        {
            tokens.push_back(Token(TokenType::EQUAL, "="));
            currentIndex++;
            continue;
        }
        else if (c == '(')
        {
            tokens.push_back(Token(TokenType::LPAREN, "("));
            currentIndex++;
            continue;
        }
        else if (c == ')')
        {
            tokens.push_back(Token(TokenType::RPAREN, ")"));
            currentIndex++;
            continue;
        }
    }
    return tokens;
}
