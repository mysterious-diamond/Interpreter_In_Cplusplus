#pragma once
#include <vector>
#include <algorithm>
#include "token.h"

class Lexer
{
public:
    Lexer(const std::string TEXT);
    std::vector<Token> tokenize();

private:
    void tokenizer_loop(char c);
    void classify_keyword(std::string check);
    std::string getChars();
    std::string getDigits();
    std::string getString();

    size_t currentIndex;
    std::string text;
    const std::vector<std::string> KEYWORDS = {"let"};
    std::vector<Token> tokens;
};