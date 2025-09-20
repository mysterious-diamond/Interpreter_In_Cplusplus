#include <iostream>
#include <vector>
#include <sstream>
#include "lexer.h"
#include "parser.h"

int main()
{
    std::stringstream buffer;
    buffer << std::cin.rdbuf();
    const std::string TEXT = buffer.str();

    Lexer lexer = Lexer(TEXT);
    std::vector<Token> tokens = lexer.tokenize();
    for (Token token : tokens)
    {
        std::cout << static_cast<int>(token.type) << " : " << token.value << '\n';
    }

    std::cout << "START OF FILE I/O\n\n";
    Parser parser = Parser(tokens);
    bool error = parser.parse();

    if (error)
        std::cout << "An error has occured.";

    return 0;
}