//
// Created by Dmytro Borak on 29.02.24.
//

#include "multithreaded_file_search.h"

void searchInSubDirectory(const std::string &fileName, const fs::path &currentPath, std::vector<fs::path> &foundPaths,
                          std::atomic<bool> &stopSearch);

// todo fix: infinite links like in /usr/bin/X11 or /run/udev/watch/b7:27
std::vector<fs::path> searchForFile(const std::string &fileName, const fs::path &currentPath, unsigned int maxThreads) {
    std::vector<fs::path> foundPaths;
    std::atomic<bool> stopSearch(false);
    std::vector<std::thread> threads;

    // Iterating over each 1 level subdirectory of the current directory.
    for (const auto &entry: fs::directory_iterator(currentPath,
                                                   std::filesystem::directory_options::skip_permission_denied)) {
        if (stopSearch) {
            break;
        }
        if (entry.is_directory()) {
            if (threads.size() < maxThreads) { // Creating a limited number of parallel threads.
                threads.emplace_back(searchInSubDirectory, fileName, entry.path(),
                                     std::ref(foundPaths), std::ref(stopSearch));
            } else { // If there are too many threads, continue sorting in the current thread.
                searchInSubDirectory(fileName, entry.path(), foundPaths, stopSearch);
            }
        } else if (entry.is_regular_file() && entry.path().filename() == fileName) { // Stop the search if this is the file we are looking for
            foundPaths.push_back(entry.path());
            stopSearch = true; // Signal other threads to stop searching
            break;
        }
    }

    for (auto &thread: threads) {
        thread.join(); // Wait for all threads to stop
    }
    return std::move(foundPaths);
}

void searchInSubDirectory(const std::string &fileName, const fs::path &currentPath, std::vector<fs::path> &foundPaths,
                          std::atomic<bool> &stopSearch) {
    // Iterating over each subdirectory and file of the current directory.
    for (const auto &entry: fs::recursive_directory_iterator(currentPath,
                                                             std::filesystem::directory_options::skip_permission_denied)) {
        if (stopSearch) {
            break;
        }
        if (entry.is_regular_file() && entry.path().filename() == fileName) { // Stop the search if this is the file we are looking for
            foundPaths.push_back(entry.path());
            stopSearch = true; // Signal other threads to stop searching
            break;
        }
    }
}