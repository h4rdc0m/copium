add_executable(
  lexer_tests lexer/LexerTests.cpp ${CMAKE_SOURCE_DIR}/src/Token.cpp
              ${CMAKE_SOURCE_DIR}/src/Lexer.cpp)

target_link_libraries(lexer_tests PRIVATE gtest gtest_main LLVMCore LLVMSupport)

target_include_directories(
  lexer_tests PRIVATE ${CMAKE_SOURCE_DIR}/src ${llvm_SOURCE_DIR}/include
                      ${llvm_BINARY_DIR}/include)
add_test(NAME LexerTests COMMAND lexer_tests)
