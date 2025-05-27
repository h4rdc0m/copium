#include <cstdlib>
#include <iostream>
#include <sstream>

int main(int argc, char *argv[]) {
    std::ostringstream oss;
    oss << "Copium v0.0.1\n";
    oss << "Usage: copium <INPUT FILE> [options]\n";
    oss << "Options:\n";
    oss << "  --help          Show this help message\n";
    oss << "  --version       Show version information\n";
    oss << "  --verbose       Enable verbose output\n";
    oss << "  --output <file> Specify output file\n";
    oss << "  --debug         Enable debug mode\n";

    std::cout << oss.str();
    if (argc > 1) {
        for (int i = 1; i < argc; ++i) {
            if (std::string(argv[i]) == "--help") {
                std::cout << "Help: Use copium with the specified options.\n";
                return EXIT_SUCCESS;
            } else if (std::string(argv[i]) == "--version") {
                std::cout << "Copium version 0.0.1\n";
                return EXIT_SUCCESS;
            } else if (std::string(argv[i]) == "--verbose") {
                std::cout << "Verbose mode enabled.\n";
            } else if (std::string(argv[i]) == "--output") {
                if (i + 1 < argc) {
                    std::cout << "Output file specified: " << argv[++i] << "\n";
                } else {
                    std::cerr << "Error: No output file specified after --output\n";
                    return EXIT_FAILURE;
                }
            } else if (std::string(argv[i]) == "--debug") {
                std::cout << "Debug mode enabled.\n";
            } else {
                std::cerr << "Unknown option: " << argv[i] << "\n";
                return EXIT_FAILURE;
            }
        }
    }
    return EXIT_SUCCESS;
}