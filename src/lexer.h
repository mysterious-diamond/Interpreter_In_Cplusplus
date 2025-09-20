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
    size_t currentIndex;
    std::string text;
    const std::vector<std::string> KEYWORDS = {"let"};
};