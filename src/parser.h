#pragma once
#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include "token.h"

class Parser
{
public:
    Parser(std::vector<Token> tokens);
    bool parse();

private:
    int parse_Expr();
    int parse_Term();
    int parse_Factor();
    void print();
    void declare_var();

    std::vector<Token> tokens;
    std::unordered_map<std::string, Token> vars;
    long unsigned int currentIndex = 0;
};