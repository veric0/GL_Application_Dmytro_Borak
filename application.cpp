#include <iostream>
#include "multithreaded_file_search.h"

/**
 * @brief Requests the user to enter the folder path and the file name to search for.
 *
 * @param[out] folderPath The variable to store folder path.
 * @param[out] fileName The variable to store file name for search.
 * @return true if the input is correct;
 *         false if the input was incorrect or the user canceled the input.
 */
bool getInput(std::string &folderPath, std::string &fileName) {
    std::cout << "Enter the folder path: ";
    std::getline(std::cin, folderPath);
    if (!fs::is_directory(folderPath)) {
        std::cerr << "Error: Invalid folder path." << std::endl;
        return false;
    }

    std::cout << "Enter the file name to search for: ";
    std::getline(std::cin, fileName);
    if (fileName.empty()) {
        std::cerr << "Error: File name cannot be empty." << std::endl;
        return false;
    }

    return true;
}

/**
 * example of usage searchForFile
 * @return
 */
int main() {
    // Number of threads available
    unsigned int cores = std::thread::hardware_concurrency();
    std::cout << "Number of cores ( =threads for search): " << cores << std::endl;

    std::string directoryPath;
    std::string fileName;

    // Input path and filename or use default names
    if (!getInput(directoryPath, fileName)) {
        directoryPath = "/home";
//    directoryPath = "/home/dima/CLionProjects";
        fileName = "GL_Application_Dmytro_Borak";
    }

    std::cout << "Directory path: " << directoryPath << std::endl;
    std::cout << "File name: " << fileName << std::endl;

    std::vector<fs::path> foundPaths = searchForFile(fileName, directoryPath);

    if (!foundPaths.empty()) {
        std::cout << "Found " << foundPaths.size() << " occurrences of " << fileName << ":\n";
        for (const auto &path: foundPaths) {
            std::cout << path << '\n';
        }
    } else {
        std::cout << "File " << fileName << " not found in " << directoryPath << " or its subdirectories.\n";
    }

    return 0;
}
