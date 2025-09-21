#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <unordered_map>

enum class TokenType
{
    NUMBER,
    IDENTIFIER,
    PLUS,
    MINUS,
    STAR,
    SLASH,
    LPAREN,
    RPAREN,
    END
};

struct Token
{
    TokenType type;
    std::string value;
};

class Recursive_Parser
{
    std::vector<Token> tokens;
    int current = 0;

    Token peek() { return tokens[current]; }
    Token advance() { return tokens[current++]; }
    bool match(TokenType t)
    {
        if (peek().type == t)
        {
            advance();
            return true;
        }
        return false;
    }

public:
    Recursive_Parser(std::vector<Token> tokens) : tokens(tokens) {}

    // expr -> term ( ( + | - ) term )*
    int parseExpr()
    {
        int value = parseTerm();
        while (true)
        {
            if (match(TokenType::PLUS))
                value += parseTerm();
            else if (match(TokenType::MINUS))
                value -= parseTerm();
            else
                break;
        }
        return value;
    }

    // term -> factor ( ( * | / ) factor )*
    int parseTerm()
    {
        int value = parseFactor();
        while (true)
        {
            if (match(TokenType::STAR))
                value *= parseFactor();
            else if (match(TokenType::SLASH))
                value /= parseFactor();
            else
                break;
        }
        return value;
    }

    // factor -> NUMBER | ( expr )
    int parseFactor()
    {
        if (match(TokenType::NUMBER))
        {
            return std::stoi(tokens[current - 1].value);
        }
        else if (match(TokenType::LPAREN))
        {
            int value = parseExpr();
            if (!match(TokenType::RPAREN))
                throw std::runtime_error("Missing )");
            return value;
        }
        throw std::runtime_error("Unexpected token in factor");
    }
};
