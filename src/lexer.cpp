#include <iostream>
#include <cctype>
#include "lexer.h"

Lexer::Lexer(const std::string TEXT)
{
    this->text = TEXT;
    currentIndex = 0;
}

std::string Lexer::getString()
{
    std::string res;
    while (currentIndex < text.size() && text[currentIndex] != '"')
    {
        res += text[currentIndex];
        currentIndex++;
    }
    return res;
}

std::string Lexer::getDigits()
{
    std::string res;
    while (currentIndex < text.size() && isdigit(text[currentIndex]))
    {
        res += text[currentIndex];
        currentIndex++;
    }
    return res;
}

std::string Lexer::getChars()
{
    std::string res;
    while (currentIndex < text.size() && isalpha(text[currentIndex]))
    {
        res += text[currentIndex];
        currentIndex++;
    }
    return res;
}

void Lexer::classify_keyword(std::string check)
{
    if (check == "let")
        tokens.push_back(Token(TokenType::LET, check));
    else if (check == "print")
        tokens.push_back(Token(TokenType::PRINT, check));
    else
        tokens.push_back(Token(TokenType::IDENTIFIER, check));
}

void Lexer::tokenizer_loop(char c)
{
    if (isspace(c))
    {
        currentIndex++;
    }
    else if (isalpha(c))
    {
        std::string current(1, c);
        currentIndex++;
        current += this->getChars();

        classify_keyword(current);
    }
    else if (isdigit(c))
    {
        std::string current(1, c);
        currentIndex++;
        current += this->getDigits();

        tokens.push_back(Token(TokenType::NUMBER, current));
    }
    else if (c == '"')
    {
        std::string current;
        currentIndex++;
        current = this->getString();
        currentIndex++;
        tokens.push_back(Token(TokenType::STRING, current));
    }
    else if (c == '=')
    {
        tokens.push_back(Token(TokenType::EQUAL, "="));
        currentIndex++;
    }
    else if (c == '(')
    {
        tokens.push_back(Token(TokenType::LPAREN, "("));
        currentIndex++;
    }
    else if (c == ')')
    {
        tokens.push_back(Token(TokenType::RPAREN, ")"));
        currentIndex++;
    }
    else if (c == '+')
    {
        tokens.push_back(Token(TokenType::PLUS, "+"));
        currentIndex++;
    }
    else
    {
        std::cout << "Unexpected character : " << c << '\n';
    }
}

std::vector<Token> Lexer::tokenize()
{
    // Lexer/Tokenizer loop
    while (currentIndex < text.size())
    {
        char c = text[currentIndex];

        this->tokenizer_loop(c);
    }
    return tokens;
}
