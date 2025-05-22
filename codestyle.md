# Copium Code Style Quick Reference

## Naming

- **Classes/Structs**: `PascalCase` (e.g., `LexicalAnalyzer`)
- **Functions/Methods**: `camelCase` (e.g., `parseExpression`)
- **Variables**: `camelCase` (e.g., `tokenStream`)
- **Constants**: `SCREAMING_SNAKE_CASE` (e.g., `MAX_IDENTIFIER_LENGTH`)
- **Namespaces**: `lowercase` (e.g., `copium::ast`)
- **Enums**: `PascalCase` with `SCREAMING_SNAKE_CASE` values
- **Files**: `PascalCase.hpp/cpp` for class implementations, `lowercase.hpp/cpp` for utilities

## Formatting

- **Indentation**: 2 spaces
- **Line Length**: 100 characters max
- **Braces**: Same line (Attach style)
- **Comments**: Line up with code they describe

## Documentation

All public APIs must have Doxygen-style documentation:

```cpp
/**
 * @brief Brief description
 *
 * Detailed description
 *
 * @param paramName Parameter description
 * @return Description of return value
 * @throws ExceptionType Description of when exception is thrown
 */
```

## Includes

Order includes as follows:
1. Standard library headers
2. External library headers
3. Project headers

## Example

```cpp
#include <string>  // Standard library
#include <llvm/IR/Value.h>  // External library
#include "Lexer.hpp"  // Project header

namespace copium {

/**
 * @brief Parses expressions in the Copium language
 * 
 * This class is responsible for parsing expressions according to
 * the language grammar.
 */
class ExpressionParser {
 public:
  /**
   * @brief Creates a new expression parser
   * @param lexer The lexer to use for obtaining tokens
   */
  explicit ExpressionParser(Lexer& lexer);
  
  /**
   * @brief Parses a binary expression
   * @return The parsed expression or nullptr on error
   */
  std::unique_ptr<Expression> parseBinaryExpression();
  
 private:
  Lexer& lexer_;
  Token currentToken_;
  
  void advanceToken();
};

}  // namespace copium
```

See the full style guide in CONTRIBUTING.md for more details.