#include "Lexer.hpp"
#include <iostream>

namespace Copium
{
    Lexer::Lexer() = default;
    Lexer::~Lexer() = default;

    void Lexer::tokenize(const std::string_view input)
    {
        tokens.clear();
        currentInput = input;
        currentIndex = 0;
        currentChar = currentInput[currentIndex];

        LexerToken tokenType;
        do {
            std::string identifierStr;
            std::optional<double> numberValue;

            tokenType = getNextToken();

            if (tokenType == LexerToken::Identifier || tokenType == LexerToken::Number) {
                tokens.push_back({tokenType, identifierStr, numberValue});
            } else {
                tokens.push_back({tokenType, std::string(1, static_cast<char>(tokenType)), std::nullopt});
            }
        } while(tokenType != LexerToken::Eof);
    }

    void Lexer::printTokens() const
    {
        for (const auto& token : tokens) {
            std::cout << "Token: ";
            switch (token.token) {
                case LexerToken::Eof:
                    std::cout << "Eof";
                    break;
                case LexerToken::Def:
                    std::cout << "Def";
                    break;
                case LexerToken::Extern:
                    std::cout << "Extern";
                    break;
                case LexerToken::Identifier:
                    std::cout << "Identifier: " << token.lexeme;
                    break;
                case LexerToken::Number:
                    std::cout << "Number: " << token.value.value();
                    break;
                default:
                    std::cout << "'" << static_cast<char>(static_cast<int>(token.token)) << "'";
                    break;
            }
            std::cout << std::endl;
        }
    }

    char Lexer::advance()
    {
        currentIndex++;
        if (currentIndex < currentInput.size()) {
            currentChar = currentInput[currentIndex];
        } else {
            currentChar = EOF;
        }
        return currentChar;
    }

    char Lexer::peek() const
    {
        if (currentIndex + 1 < currentInput.size()) {
            return currentInput[currentIndex + 1];
        }
        return EOF;
    }

    LexerToken Lexer::getNextToken()
    {
        // Skip whitespace
        while (std::isspace(static_cast<unsigned char>(currentChar))) {
            advance();
        }

        // Handle identifiers: [a-zA-Z][a-zA-Z0-9]*
        if (std::isalpha(static_cast<unsigned char>(currentChar))) {
            std::string identifierStr;
            identifierStr += currentChar;

            while(std::isalnum(static_cast<unsigned char>(advance()))) {
                identifierStr += currentChar;
            }

            // Check for keywords
            if (identifierStr == "def") {
                return LexerToken::Def;
            }
            if (identifierStr == "extern") {
                return LexerToken::Extern;
            }

            tokens.back().lexeme = std::move(identifierStr); // Update the last token with the identifier
            return LexerToken::Identifier;
        }

        // Handle numbers: [0-9.]+
        if (std::isdigit(static_cast<unsigned char>(currentChar)) || currentChar == '.') {
            std::string numberStr;
            
            do {
                numberStr += currentChar;
                advance();
            } while (std::isdigit(static_cast<unsigned char>(currentChar)) || currentChar == '.');

            double value = std::stod(numberStr);
            tokens.back().value = value; // Update the last token with the number value
            tokens.back().lexeme = std::move(numberStr); // Update the last token with the number string
            return LexerToken::Number;
        }

        // Handle comments: '#.*'
        if (currentChar == '#') {
            do {
                advance();
            } while (currentChar != '\n' && currentChar != EOF && currentChar != '\r');

            if (currentChar != EOF) {
                return getNextToken(); // Continue to the next token
            }
        }

        // Handle end of file
        if (currentChar == EOF) {
            return LexerToken::Eof;
        }

        // Handle other characters (ASCII values)
        char thisChar = currentChar;
        advance();
        return static_cast<LexerToken>(thisChar);
    }
}