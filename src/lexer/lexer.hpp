#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "token.hpp"
#include "token_type.hpp"

namespace copium {

/**
 * @brief Lexer for the Copium programming language.
 *
 * Converts source code into a stream of tokens.
 */
class Lexer {
public:
  /**
   * @brief Constructs a lexer for the given source code.
   *
   * @param source The source code to be lexed
   */
  explicit Lexer(std::string source);

  /**
   * @brief Scans the next token from the source code.
   *
   * @return The next token
   */
  Token scanToken();

  /**
   * @brief Scans all tokens from the source code.
   *
   * @return A vector of all tokensin the source code
   */
  std::vector<Token> scanTokens();

  /**
   * @brief Returns whether the lexer has encountered an error.
   * 
   * @return true if an error has occurred, false otherwise
   */
  bool hasError() const {
    return hadError;
  }

  /**
   * @brief Returns the error messages encountered during lexing.
   * 
   * @return A vector of error messages
   */
  const std::vector<std::string>& getErrors() const {
    return errorMessages;
  }

private:
  std::string source;  // The source code to be lexed

  size_t start = 0;       // The starting position of the current token
  size_t current = 0;     // The current position in the source code
  int line = 1;           // The current line number
  int column = 1;         // The current column number
  bool hadError = false;  // Flag to indicate if an error has occurred

  std::vector<std::string> errorMessages;  // List of error messages

  static std::unordered_map<std::string, TokenType> keywords;  // Keyword lookup table

  // Helper methods

  bool isAtEnd() const;
  char advance();
  bool match(char expected);
  char peek() const;
  char peekNext() const;
  void errorToken(const std::string& message);

  // Token scanners

  void scanString();
  void scanNumber();
  void scanIdentifier();
  void skipWhitespace();
  void skipComment();
};
}  // namespace copium