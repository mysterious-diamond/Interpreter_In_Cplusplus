#pragma once
#include <iostream>

enum class TokenType
{
    // literals
    IDENTIFIER,
    NUMBER,
    STRING,

    // keywords
    LET,
    PRINT,
    IF,
    ELSE,
    WHILE,
    RETURN,

    // arithmetic
    PLUS,
    MINUS,
    STAR,
    SLASH,
    MODULO,

    // comparison
    EQUAL_EQUAL,
    NOT_EQUAL,
    LESS,
    GREATER,
    LESS_EQUAL,
    GREATER_EQUAL,

    // logical
    AND,
    OR,
    NOT,

    // assignment
    EQUAL,

    // punctuation
    LPAREN,
    RPAREN,
    LBRACE,
    RBRACE,

    END_OF_FILE
};

class Token
{
public:
    Token(TokenType t, const std::string &v = "");
    Token() : type(TokenType::END_OF_FILE), value("") {}
    TokenType type;
    std::string value;
};