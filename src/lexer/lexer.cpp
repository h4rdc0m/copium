#include "lexer.hpp"

#include <sstream>

namespace copium {
std::unordered_map<std::string, TokenType> Lexer::keywords = {{"fn", TokenType::FN},
                                                              {"var", TokenType::VAR},
                                                              {"let", TokenType::LET},
                                                              {"const", TokenType::CONST},
                                                              {"if", TokenType::IF},
                                                              {"else", TokenType::ELSE},
                                                              {"while", TokenType::WHILE},
                                                              {"for", TokenType::FOR},
                                                              {"return", TokenType::RETURN},
                                                              {"class", TokenType::CLASS},
                                                              {"interface", TokenType::INTERFACE},
                                                              {"impl", TokenType::IMPL},
                                                              {"alias", TokenType::ALIAS},
                                                              {"import", TokenType::IMPORT},
                                                              {"export", TokenType::EXPORT},
                                                              {"module", TokenType::MODULE},
                                                              {"pub", TokenType::PUB},
                                                              {"true", TokenType::TRUE},
                                                              {"false", TokenType::FALSE},
                                                              {"null", TokenType::NULL_KEYWORD},
                                                              {"async", TokenType::ASYNC},
                                                              {"await", TokenType::AWAIT}};

Lexer::Lexer(std::string source) : source(std::move(source)) {}

std::vector<Token> Lexer::scanTokens() {
  std::vector<Token> tokens;

  while (!isAtEnd()) {
    // Start of the next token
    start = current;
    Token token = scanToken();
    tokens.push_back(token);
  }

  // Add the end of file token
  tokens.emplace_back(TokenType::END_OF_FILE, "", line, column);
  return tokens;
}

Token Lexer::scanToken() {
  skipWhitespace();

  start = current;

  if (isAtEnd()) {
    return Token(TokenType::END_OF_FILE, "", line, column);
  }

  char c = advance();

  // Handle identifiers
  if (std::isalpha(c) || c == '_') {
    scanIdentifier();

    std::string text = source.substr(start, current - start);
    TokenType type = TokenType::IDENTIFIER;

    // Check if the identifier is a keyword
    auto it = keywords.find(text);
    if (it != keywords.end()) {
      type = it->second;
    }

    return Token(type, text, line, column);
  }

  // Handle numbers
  if (std::isdigit(c)) {
    scanNumber();
    std::string text = source.substr(start, current - start);
    TokenType type =
        text.find('.') != std::string::npos ? TokenType::FLOAT_LITERAL : TokenType::INTEGER_LITERAL;
    return Token(type, text, line, column);
  }

  // Handle single-character tokens
  switch (c) {
    case '(':
      return Token(TokenType::LEFT_PAREN, "(", line, column - 1);
    case ')':
      return Token(TokenType::RIGHT_PAREN, ")", line, column - 1);
    case '{':
      return Token(TokenType::LEFT_BRACE, "{", line, column - 1);
    case '}':
      return Token(TokenType::RIGHT_BRACE, "}", line, column - 1);
    case '[':
      return Token(TokenType::LEFT_BRACKET, "[", line, column - 1);
    case ']':
      return Token(TokenType::RIGHT_BRACKET, "]", line, column - 1);
    case '.':
      return Token(TokenType::DOT, ".", line, column - 1);
    case ',':
      return Token(TokenType::COMMA, ",", line, column - 1);
    case ';':
      return Token(TokenType::SEMICOLON, ";", line, column - 1);
    case '%':
      return Token(TokenType::PERCENT, "%", line, column - 1);

    // Handle two-character tokens
    case '!':
      if (match('=')) {
        return Token(TokenType::NOT_EQUAL, "!=", line, column - 2);
      }
      return Token(TokenType::NOT, "!", line, column - 1);
    case '=':
      if (match('=')) {
        return Token(TokenType::EQUAL_EQUAL, "==", line, column - 2);
      }
      return Token(TokenType::EQUAL, "=", line, column - 1);
    case '<':
      if (match('=')) {
        return Token(TokenType::LESS_EQUAL, "<=", line, column - 2);
      }
      return Token(TokenType::LESS, "<", line, column - 1);
    case '>':
      if (match('=')) {
        return Token(TokenType::GREATER_EQUAL, ">=", line, column - 2);
      }
      return Token(TokenType::GREATER, ">", line, column - 1);
    case '+':
      if (match('=')) {
        return Token(TokenType::PLUS_EQUAL, "+=", line, column - 2);
      }
      return Token(TokenType::PLUS, "+", line, column - 1);
    case '-':
      if (match('>')) {
        return Token(TokenType::ARROW, "->", line, column - 2);
      }
      if (match('=')) {
        return Token(TokenType::MINUS_EQUAL, "-=", line, column - 2);
      }
      return Token(TokenType::MINUS, "-", line, column - 1);
    case '*':
      if (match('=')) {
        return Token(TokenType::STAR_EQUAL, "*=", line, column - 2);
      }
      return Token(TokenType::STAR, "*", line, column - 1);
    case '/':
      if (match('/')) {
        // A comment goes until the end of the line
        char t = peek();
        while (t != '\n' && !isAtEnd()) {
          advance();
        }
        return scanToken();  // Skip the comment
      }
      if (match('*')) {
        // Handle multi-line comment
        skipComment();
        return scanToken();  // Skip the comment
      }
      if (match('=')) {
        return Token(TokenType::SLASH_EQUAL, "/=", line, column - 2);
      }
      return Token(TokenType::SLASH, "/", line, column - 1);
    case '&':
      if (match('&')) {
        return Token(TokenType::AND, "&&", line, column - 2);
      }
      errorToken("Unexpected character: '&', did you mean '&&'?");
      return Token(TokenType::ERROR, "&", line, column - 1);
    case '|':
      if (match('|')) {
        return Token(TokenType::OR, "||", line, column - 2);
      }
      errorToken("Unexpected character: '|', did you mean '||'?");
      return Token(TokenType::ERROR, "|", line, column - 1);
    case ':':
      if (match(':')) {
        return Token(TokenType::COLON_COLON, "::", line, column - 2);
      }
      return Token(TokenType::COLON, ":", line, column - 1);
    case '"':
      scanString();
      if (isAtEnd() || peek() != '"') {
        errorToken("Unterminated string.");
        return Token(TokenType::ERROR,
                     source.substr(start, current - start),
                     line,
                     column - (current - start));
      }
      // Consume the closing quote
      advance();
      return Token(TokenType::STRING_LITERAL,
                   source.substr(start + 1, current - start - 2),
                   line,
                   column - (current - start));
    default:
      // Handle unexpected characters
      errorToken("Unexpected character: '" + std::string(1, c) + "'");
      return Token(TokenType::ERROR, std::string(1, c), line, column - 1);
  }
}

bool Lexer::isAtEnd() const {
  return current >= source.length();
}

char Lexer::advance() {
  column++;
  return source[current++];
}

bool Lexer::match(char expected) {
  if (isAtEnd() || source[current] != expected) {
    return false;
  }
  current++;
  column++;
  return true;
}

char Lexer::peek() const {
  if (isAtEnd()) {
    return '\0';
  }
  return source[current];
}

char Lexer::peekNext() const {
  if (current + 1 >= source.length()) {
    return '\0';
  }
  return source[current + 1];
}

void Lexer::errorToken(const std::string& message) {
  hadError = true;
  std::stringstream ss;
  ss << "Line " << line << ", Column " << column << ": " << message;
  errorMessages.push_back(ss.str());
}

void Lexer::scanString() {
  while (peek() != '"' && !isAtEnd()) {
    if (peek() == '\n') {
      line++;
      column = 1;
    }
    advance();
  }
}

void Lexer::scanNumber() {
  while (std::isdigit(peek())) {
    advance();
  }

  // Look for a fractional part
  if (peek() == '.' && std::isdigit(peekNext())) {
    advance();  // Consume the '.'
    while (std::isdigit(peek())) {
      advance();
    }
  }
}

void Lexer::scanIdentifier() {
  while (std::isalnum(peek()) || peek() == '_') {
    advance();
  }
}

void Lexer::skipWhitespace() {
  while (true) {
    char c = peek();
    switch (c) {
      case ' ':
      case '\r':
      case '\t':
        advance();
        break;
      case '\n':
        line++;
        column = 1;
        advance();
        break;
      default:
        return;
    }
  }
}

void Lexer::skipComment() {
    int nesting = 1;
    while(nesting > 0 && !isAtEnd()) {
        if (peek() == '*' && peekNext() == '/') {
            advance(); // Consume '*'
            advance(); // Consume '/'
            nesting--;
        } else if (peek() == '/' && peekNext() == '*') {
            advance(); // Consume '/'
            advance(); // Consume '*'
            nesting++;
        } else if (peek() == '\n') {
            line++;
            column = 1;
            advance();
        } else {
            advance();
        }
    }

    if(nesting > 0) {
        errorToken("Unterminated multi-line comment.");
    }
}
}  // namespace copium