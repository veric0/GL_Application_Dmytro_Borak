#include <iostream>
#include "multithreaded_file_search.h"

// example of use searchForFile
int main() {

    unsigned int cores = std::thread::hardware_concurrency();
    std::cout << "Number of cores ( =threads for search): " << cores << std::endl;

//    std::string directoryPath = "/";
    std::string directoryPath = "/home/dima/CLionProjects";
    std::string fileName = "GL_Application_Dmytro_Borak";

    std::vector<fs::path> foundPaths;
    searchForFile(fileName, directoryPath, foundPaths);

    if (!foundPaths.empty()) {
        std::cout << "Found " << foundPaths.size() << " occurrences of " << fileName << ":\n";
        for (const auto& path : foundPaths) {
            std::cout << path << '\n';
        }
    } else {
        std::cout << "File " << fileName << " not found in " << directoryPath << " or its subdirectories.\n";
    }

    return 0;
}
