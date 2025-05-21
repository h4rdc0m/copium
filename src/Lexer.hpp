#pragma once
#include <string_view>
#include <string>
#include <optional>
#include <vector>

namespace Copium
{
    enum class LexerToken {
        Eof = -1,

        // commands
        Def = -2,
        Extern = -3,

        // operators
        Identifier = -4,
        Number = -5,

        // ASCII chars represented by their values (0-255)
    };

    class Lexer
    {
    public:
        Lexer();
        ~Lexer();

        void tokenize(const std::string_view input);
        void printTokens() const;

    private:
        // Token representation with value information
        struct TokenInfo {
            LexerToken token;
            std::string lexeme;
            std::optional<double> value; // Optional value for NUMBER tokens
        };

        std::vector<TokenInfo> tokens; // Vector to store tokens

        // Lexer state
        std::string_view currentInput; // Current input string
        size_t currentIndex{0}; // Current index in the input string
        char currentChar{0}; // Current character being processed

        // Token parsing helpers
        LexerToken getNextToken();
        char advance();
        char peek() const;
    };
} // namespace name
