#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char *argv[]) {
    // Check if the user provided a filename as an argument
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }

    // Open the file
    std::ifstream file(argv[1]);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << argv[1] << std::endl;
        return 1;
    }

    // Read the file line by line
    std::string line;
    while (std::getline(file, line)) {
        std::cout << line << std::endl; // Print each line to the console
    }

    // Close the file
    file.close();
    return 0;
}