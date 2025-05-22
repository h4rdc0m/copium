#pragma once

#include <string>

#include "token_type.hpp"

namespace copium {
/**
 * @brief Class representing a token in the Copium language.
 */
class Token {
public:
  /**
   * @brief Constructs a new Token
   *
   * @param type The type of the token
   * @param lexeme The lexeme (text) of the token
   * @param line The line number where the token was found
   * @param column The column number where the token was found
   */
  Token(TokenType type, std::string lexeme, int line, int column)
      : type(type), lexeme(std::move(lexeme)), line(line), column(column) {}

  /**
   * @brief Returns the string representation of the token.
   * 
   * @return The string representation of the token
   *         in the format: "Token(type, lexeme, line, column)"
   */
  [[nodiscard]] std::string toString() const;

  /**
   * @brief Returns the string representation of the token type.
   * 
   * @packaged type The type of the token
   * @return The string representation of the token type
   */
  [[nodiscard]] static std::string typeToString(TokenType type);

  // Getters for the token properties

  [[nodiscard]] TokenType getType() const {
    return type;
  }
  [[nodiscard]] const std::string& getLexeme() const {
    return lexeme;
  }
  [[nodiscard]] int getLine() const {
    return line;
  }
  [[nodiscard]] int getColumn() const {
    return column;
  }

private:
  TokenType type;      // The type of the token
  std::string lexeme;  // The lexeme (text) of the token
  int line;            // The line number where the token was found
  int column;          // The column number where the token was found
};
}  // namespace copium