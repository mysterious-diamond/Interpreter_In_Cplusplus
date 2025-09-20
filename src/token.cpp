#include "token.h"

Token::Token(TokenType t, const std::string& v)
    : type(t), value(v) {}