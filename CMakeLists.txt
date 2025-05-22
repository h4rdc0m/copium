cmake_minimum_required(VERSION 3.22)

project(
  CopiumLang
  VERSION 0.0.1
  DESCRIPTION "A simple programming language"
  LANGUAGES C CXX)
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
        URL https://github.com/llvm/llvm-project/releases/download/llvmorg-20.1.5/llvm-20.1.5.src.tar.xz
        SOURCE_SUBDIR llvm
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(llvm)
find_package(LLVM REQUIRED CONFIG)

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
  add_custom_target(
    docs
    ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/docs/doxygen.config
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Generating API documentation with Doxygen"
    VERBATIM)
endif()

include(CTest)
enable_testing()

add_executable(copium src/main.cpp src/token.cpp src/lexer.cpp)

target_link_libraries(copium PRIVATE LLVMCore LLVMSupport LLVMMC LLVMIRReader)

# Include LLVM headers
target_include_directories(copium PRIVATE ${LLVM_INCLUDE_DIRS})

add_subdirectory(tests)
