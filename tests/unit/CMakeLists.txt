add_executable(
  lexer_tests lexer/LexerTests.cpp ${CMAKE_SOURCE_DIR}/src/token.cpp
              ${CMAKE_SOURCE_DIR}/src/lexer.cpp)

target_link_libraries(lexer_tests PRIVATE gtest gtest_main ${LLVM_LIBS})

target_compile_definitions(lexer_tests PRIVATE ${LLVM_DEFINITIONS})
target_include_directories(
  lexer_tests PRIVATE ${CMAKE_SOURCE_DIR}/src ${LLVM_INCLUDE_DIRS})
add_test(NAME LexerTests COMMAND lexer_tests)
