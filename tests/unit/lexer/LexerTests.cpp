#include <gtest/gtest.h>

#include "lexer.hpp"

using namespace copium;

// Test basic tokenization of literals
TEST(LexerTest, BasicLiterals) {
    Lexer lexer("42 3.14 \"Hello\" true false null");
    auto tokens = lexer.scanTokens();
    
    ASSERT_EQ(tokens.size(), 7); // 6 literals + EOF

    EXPECT_EQ(tokens[0].getType(), TokenType::INTEGER_LITERAL);
    EXPECT_EQ(tokens[0].getLexeme(), "42");

    EXPECT_EQ(tokens[1].getType(), TokenType::FLOAT_LITERAL);
    EXPECT_EQ(tokens[1].getLexeme(), "3.14");

    EXPECT_EQ(tokens[2].getType(), TokenType::STRING_LITERAL);
    EXPECT_EQ(tokens[2].getLexeme(), "Hello");

    EXPECT_EQ(tokens[3].getType(), TokenType::BOOLEAN_LITERAL);
    EXPECT_EQ(tokens[3].getLexeme(), "true");

    EXPECT_EQ(tokens[4].getType(), TokenType::BOOLEAN_LITERAL);
    EXPECT_EQ(tokens[4].getLexeme(), "false");

    EXPECT_EQ(tokens[5].getType(), TokenType::NULL_LITERAL);
    EXPECT_EQ(tokens[5].getLexeme(), "null");

    EXPECT_EQ(tokens[6].getType(), TokenType::END_OF_FILE);
}

// Test keywords and identifiers
TEST(LexerTest, KeywordsAndIdentifiers) {
  Lexer lexer("fn main() { let x = 10; return x; }");
  auto tokens = lexer.scanTokens();
  
  ASSERT_GE(tokens.size(), 12); // At least 12 tokens (not counting EOF)
  
  EXPECT_EQ(tokens[0].getType(), TokenType::FN);
  EXPECT_EQ(tokens[1].getType(), TokenType::IDENTIFIER);
  EXPECT_EQ(tokens[1].getLexeme(), "main");
  EXPECT_EQ(tokens[2].getType(), TokenType::LEFT_PAREN);
  EXPECT_EQ(tokens[3].getType(), TokenType::RIGHT_PAREN);
  EXPECT_EQ(tokens[4].getType(), TokenType::LEFT_BRACE);
  EXPECT_EQ(tokens[5].getType(), TokenType::LET);
  EXPECT_EQ(tokens[6].getType(), TokenType::IDENTIFIER);
  EXPECT_EQ(tokens[6].getLexeme(), "x");
  EXPECT_EQ(tokens[7].getType(), TokenType::EQUAL);
  EXPECT_EQ(tokens[8].getType(), TokenType::INTEGER_LITERAL);
  EXPECT_EQ(tokens[8].getLexeme(), "10");
  EXPECT_EQ(tokens[9].getType(), TokenType::SEMICOLON);
  EXPECT_EQ(tokens[10].getType(), TokenType::RETURN);
  EXPECT_EQ(tokens[11].getType(), TokenType::IDENTIFIER);
  EXPECT_EQ(tokens[11].getLexeme(), "x");
}

// Test operators
TEST(LexerTest, Operators) {
  Lexer lexer("+ - * / % == != < <= > >= = += -= *= /= && || !");
  auto tokens = lexer.scanTokens();
  
  ASSERT_EQ(tokens.size(), 20); // 18 operators + EOF
  
  EXPECT_EQ(tokens[0].getType(), TokenType::PLUS);
  EXPECT_EQ(tokens[1].getType(), TokenType::MINUS);
  EXPECT_EQ(tokens[2].getType(), TokenType::STAR);
  EXPECT_EQ(tokens[3].getType(), TokenType::SLASH);
  EXPECT_EQ(tokens[4].getType(), TokenType::PERCENT);
  EXPECT_EQ(tokens[5].getType(), TokenType::EQUAL_EQUAL);
  EXPECT_EQ(tokens[6].getType(), TokenType::NOT_EQUAL);
  EXPECT_EQ(tokens[7].getType(), TokenType::LESS);
  EXPECT_EQ(tokens[8].getType(), TokenType::LESS_EQUAL);
  EXPECT_EQ(tokens[9].getType(), TokenType::GREATER);
  EXPECT_EQ(tokens[10].getType(), TokenType::GREATER_EQUAL);
  EXPECT_EQ(tokens[11].getType(), TokenType::EQUAL);
  EXPECT_EQ(tokens[12].getType(), TokenType::PLUS_EQUAL);
  EXPECT_EQ(tokens[13].getType(), TokenType::MINUS_EQUAL);
  EXPECT_EQ(tokens[14].getType(), TokenType::STAR_EQUAL);
  EXPECT_EQ(tokens[15].getType(), TokenType::SLASH_EQUAL);
  EXPECT_EQ(tokens[16].getType(), TokenType::AND);
  EXPECT_EQ(tokens[17].getType(), TokenType::OR);
  EXPECT_EQ(tokens[18].getType(), TokenType::NOT);
}

// Test comments
TEST(LexerTest, Comments) {
  Lexer lexer("// This is a comment\nx // Another comment\n/* Multi-line\ncomment */y");
  auto tokens = lexer.scanTokens();
  for(auto t : tokens) {
    // Debugging output removed to keep test output clean.
  }
  
  ASSERT_EQ(tokens.size(), 3); // x, y, and EOF
  
  EXPECT_EQ(tokens[0].getType(), TokenType::IDENTIFIER);
  EXPECT_EQ(tokens[0].getLexeme(), "x");
  EXPECT_EQ(tokens[0].getLine(), 2);
  
  EXPECT_EQ(tokens[1].getType(), TokenType::IDENTIFIER);
  EXPECT_EQ(tokens[1].getLexeme(), "y");
  EXPECT_EQ(tokens[1].getLine(), 4);
}

// Test error handling
TEST(LexerTest, ErrorHandling) {
  Lexer lexer("@#$");
  auto tokens = lexer.scanTokens();
  
  EXPECT_TRUE(lexer.hasError());
  EXPECT_FALSE(lexer.getErrors().empty());
  
  EXPECT_EQ(tokens[0].getType(), TokenType::ERROR);
  EXPECT_EQ(tokens[1].getType(), TokenType::ERROR);
  EXPECT_EQ(tokens[2].getType(), TokenType::ERROR);
  EXPECT_EQ(tokens[3].getType(), TokenType::END_OF_FILE);
}

// Test line and column tracking
TEST(LexerTest, LineColumnTracking) {
  Lexer lexer("let x = 10;\nlet y = 20;");
  auto tokens = lexer.scanTokens();
  
  EXPECT_EQ(tokens[0].getLine(), 1);
  EXPECT_EQ(tokens[0].getColumn(), 1);
  
  EXPECT_EQ(tokens[5].getLine(), 2);
  EXPECT_EQ(tokens[5].getColumn(), 1);
}