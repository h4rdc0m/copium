#include "token.hpp"

#include <sstream>

namespace copium {
std::string Token::toString() const {
    std::stringstream ss;
    ss << "Token(" << typeToString(type) << ", " << lexeme << ", " << line << ", " << column << ")";
    return ss.str();
}

std::string Token::typeToString(TokenType type) {
  switch (type) {
    case TokenType::END_OF_FILE: return "EOF";
    case TokenType::INTEGER_LITERAL: return "INTEGER";
    case TokenType::FLOAT_LITERAL: return "FLOAT";
    case TokenType::STRING_LITERAL: return "STRING";
    case TokenType::BOOLEAN_LITERAL: return "BOOLEAN";
    case TokenType::NULL_LITERAL: return "NULL";
    case TokenType::IDENTIFIER: return "IDENTIFIER";
    case TokenType::FN: return "FN";
    case TokenType::VAR: return "VAR";
    case TokenType::LET: return "LET";
    case TokenType::CONST: return "CONST";
    case TokenType::IF: return "IF";
    case TokenType::ELSE: return "ELSE";
    case TokenType::WHILE: return "WHILE";
    case TokenType::FOR: return "FOR";
    case TokenType::RETURN: return "RETURN";
    case TokenType::CLASS: return "CLASS";
    case TokenType::INTERFACE: return "INTERFACE";
    case TokenType::IMPL: return "IMPL";
    case TokenType::ALIAS: return "ALIAS";
    case TokenType::IMPORT: return "IMPORT";
    case TokenType::EXPORT: return "EXPORT";
    case TokenType::MODULE: return "MODULE";
    case TokenType::PUB: return "PUB";
    case TokenType::TRUE: return "TRUE";
    case TokenType::FALSE: return "FALSE";
    case TokenType::NULL_KEYWORD: return "NULL";
    case TokenType::ASYNC: return "ASYNC";
    case TokenType::AWAIT: return "AWAIT";
    case TokenType::PLUS: return "PLUS";
    case TokenType::MINUS: return "MINUS";
    case TokenType::STAR: return "STAR";
    case TokenType::SLASH: return "SLASH";
    case TokenType::PERCENT: return "PERCENT";
    case TokenType::EQUAL_EQUAL: return "EQUAL_EQUAL";
    case TokenType::NOT_EQUAL: return "NOT_EQUAL";
    case TokenType::LESS: return "LESS";
    case TokenType::LESS_EQUAL: return "LESS_EQUAL";
    case TokenType::GREATER: return "GREATER";
    case TokenType::GREATER_EQUAL: return "GREATER_EQUAL";
    case TokenType::EQUAL: return "EQUAL";
    case TokenType::PLUS_EQUAL: return "PLUS_EQUAL";
    case TokenType::MINUS_EQUAL: return "MINUS_EQUAL";
    case TokenType::STAR_EQUAL: return "STAR_EQUAL";
    case TokenType::SLASH_EQUAL: return "SLASH_EQUAL";
    case TokenType::AND: return "AND";
    case TokenType::OR: return "OR";
    case TokenType::NOT: return "NOT";
    case TokenType::DOT: return "DOT";
    case TokenType::COMMA: return "COMMA";
    case TokenType::SEMICOLON: return "SEMICOLON";
    case TokenType::COLON: return "COLON";
    case TokenType::COLON_COLON: return "COLON_COLON";
    case TokenType::ARROW: return "ARROW";
    case TokenType::LEFT_PAREN: return "LEFT_PAREN";
    case TokenType::RIGHT_PAREN: return "RIGHT_PAREN";
    case TokenType::LEFT_BRACE: return "LEFT_BRACE";
    case TokenType::RIGHT_BRACE: return "RIGHT_BRACE";
    case TokenType::LEFT_BRACKET: return "LEFT_BRACKET";
    case TokenType::RIGHT_BRACKET: return "RIGHT_BRACKET";
    case TokenType::ERROR: return "ERROR";
    default: return "UNKNOWN";
  }
}  // namespace copium