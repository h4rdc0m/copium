#pragma once

namespace copium {

/**
 * @brief Enum class representing the different types of tokens in the lexer.
 */
enum class TokenType {
  // End of file
  END_OF_FILE,

  // Literals
  INTEGER_LITERAL,
  FLOAT_LITERAL,
  STRING_LITERAL,
  BOOLEAN_LITERAL,
  NULL_LITERAL,

  // Identifiers
  IDENTIFIER,

  // Keywords
  FN,
  VAR,
  LET,
  CONST,
  IF,
  ELSE,
  WHILE,
  FOR,
  RETURN,
  CLASS,
  INTERFACE,
  IMPL,
  ALIAS,
  IMPORT,
  EXPORT,
  MODULE,
  PUB,
  TRUE,
  FALSE,
  NULL_KEYWORD,
  ASYNC,
  AWAIT,

  // Operators
  PLUS,     // +
  MINUS,    // -
  STAR,     // *
  SLASH,    // /
  PERCENT,  // %

  // Comparison operators
  EQUAL_EQUAL,    // ==
  NOT_EQUAL,      // !=
  LESS,           // <
  LESS_EQUAL,     // <=
  GREATER,        // >
  GREATER_EQUAL,  // >=

  // Assignment operators
  EQUAL,        // =
  PLUS_EQUAL,   // +=
  MINUS_EQUAL,  // -=
  STAR_EQUAL,   // *=
  SLASH_EQUAL,  // /=

  // Logical operators
  AND,  // &&
  OR,   // ||
  NOT,  // !

  // Punctuation
  DOT,          // .
  COMMA,        // ,
  SEMICOLON,    // ;
  COLON,        // :
  COLON_COLON,  // ::
  ARROW,        // ->

  // Brackets
  LEFT_PAREN,     // (
  RIGHT_PAREN,    // )
  LEFT_BRACE,     // {
  RIGHT_BRACE,    // }
  LEFT_BRACKET,   // [
  RIGHT_BRACKET,  // ]

  // Special tokens
  ERROR,  // Used for lexical errors
};
}  // namespace copium