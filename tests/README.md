\source\repos\copium\tests\README.md
# Testing Guidelines for Copium

This document describes how to write and run tests for the Copium language project.

## Test Structure

Tests are organized into the following categories:

- **Unit Tests**: Tests for individual components (lexer, parser, etc.)
- **Integration Tests**: Tests for component interactions
- **End-to-End Tests**: Tests for the complete compiler pipeline

## Writing Unit Tests

1. Create a new test file in the appropriate subdirectory (e.g., `tests/unit/lexer/`)
2. Include Google Test and the component you're testing:

```cpp
#include <gtest/gtest.h>
#include "ComponentToTest.hpp"
```

3. Write test cases using the `TEST` macro:

```cpp
TEST(TestSuiteName, TestName) {
    // Arrange
    ComponentToTest component;
    
    // Act
    auto result = component.someMethod();
    
    // Assert
    EXPECT_EQ(result, expectedValue);
}
```

## Running Tests

To run all tests:

```bash
cd build
ctest
```

To run a specific test:

```bash
cd build
ctest -R TestName
```

To run tests with verbose output:

```bash
cd build
ctest -V
```

## Test Coverage

We aim for high test coverage. Consider adding tests for:

- Normal cases
- Edge cases
- Error conditions
- Boundary conditions

## Continuous Integration

Tests are automatically run on all pull requests and pushes to the main branch.