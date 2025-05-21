cmake_minimum_required(VERSION 3.22)

project(
  CopiumLang
  VERSION 0.0.1
  DESCRIPTION "A simple programming language"
  LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)
# Configure LLVM options before fetching
set(LLVM_ENABLE_PROJECTS "")
set(LLVM_TARGETS_TO_BUILD "X86")
set(LLVM_ENABLE_RTTI ON)
set(LLVM_ENABLE_EH ON)
set(LLVM_BUILD_TOOLS OFF)
set(LLVM_INCLUDE_TOOLS OFF)
set(LLVM_INCLUDE_TESTS OFF)
set(LLVM_INCLUDE_EXAMPLES OFF)
set(LLVM_INCLUDE_BENCHMARKS OFF)
set(LLVM_ENABLE_DUMP ON)
FetchContent_Declare(
  llvm
  GIT_REPOSITORY https://github.com/llvm/llvm-project.git
  GIT_TAG llvmorg-20.1.5
  GIT_SHALLOW ON
  SOURCE_SUBDIR llvm)
FetchContent_MakeAvailable(llvm)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.17.0
  GIT_SHALLOW ON)

# For Windows: Prevent overriding the parent project's compiler/linker
set(gtest_force_shared_crt
    ON
    CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Documentation generation with Doxygen
find_package(Doxygen)
if(DOXYGEN_FOUND)
    add_custom_target(docs
        ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/docs/doxygen.config
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "Generating API documentation with Doxygen" VERBATIM
    )
endif()

include(CTest)
enable_testing()

add_executable(copium src/main.cpp src/Lexer.hpp src/Lexer.cpp)

target_link_libraries(copium PRIVATE LLVMCore LLVMSupport LLVMMC LLVMIRReader)

# Include LLVM headers
target_include_directories(copium PRIVATE ${llvm_SOURCE_DIR}/include
                                          ${llvm_BINARY_DIR}/include)

add_subdirectory(tests)
