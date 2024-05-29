#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>

namespace fs = std::filesystem;

void listDirectory(const fs::path& path) {
    try {
        for (const auto& entry : fs::directory_iterator(path)) {
            std::cout << (entry.is_directory() ? "[DIR] " : "[FILE] ") << entry.path().filename().string() << std::endl;
        }
    } catch (fs::filesystem_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

void viewFile(const fs::path& path) {
    std::ifstream file(path);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::cout << line << std::endl;
        }
        file.close();
    } else {
        std::cerr << "Unable to open file: " << path << std::endl;
    }
}

void createDirectory(const fs::path& path) {
    if (fs::create_directory(path)) {
        std::cout << "Directory created: " << path << std::endl;
    } else {
        std::cerr << "Unable to create directory: " << path << std::endl;
    }
}

void copyFile(const fs::path& source, const fs::path& destination) {
    try {
        fs::copy_file(source, destination, fs::copy_options::overwrite_existing);
        std::cout << "File copied from " << source << " to " << destination << std::endl;
    } catch (fs::filesystem_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

void moveFile(const fs::path& source, const fs::path& destination) {
    try {
        fs::rename(source, destination);
        std::cout << "File moved from " << source << " to " << destination << std::endl;
    } catch (fs::filesystem_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

int main() {
    std::string command;
    std::string path;
    std::string destination;

    while (true) {
        std::cout << "Enter command (list, view, mkdir, copy, move, exit): ";
        std::cin >> command;

        if (command == "list") {
            std::cout << "Enter directory path: ";
            std::cin >> path;
            listDirectory(path);
        } else if (command == "view") {
            std::cout << "Enter file path: ";
            std::cin >> path;
            viewFile(path);
        } else if (command == "mkdir") {
            std::cout << "Enter directory path: ";
            std::cin >> path;
            createDirectory(path);
        } else if (command == "copy") {
            std::cout << "Enter source file path: ";
            std::cin >> path;
            std::cout << "Enter destination path: ";
            std::cin >> destination;
            copyFile(path, destination);
        } else if (command == "move") {
            std::cout << "Enter source file path: ";
            std::cin >> path;
            std::cout << "Enter destination path: ";
            std::cin >> destination;
            moveFile(path, destination);
        } else if (command == "exit") {
            break;
        } else {
            std::cerr << "Unknown command" << std::endl;
        }
    }

    return 0;
}
