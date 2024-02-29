//
// Created by dima on 29.02.24.
//

#include "multithreaded_file_search.h"

namespace fs = std::filesystem;

void searchInSubDirectory(const std::string &fileName, const fs::path &currentPath, std::vector<fs::path> &foundPaths,
                          std::atomic<bool> &stopSearch);

void searchForFile(const std::string &fileName, const fs::path &currentPath, std::vector<fs::path> &foundPaths,
                   unsigned int maxThreads) {
    std::atomic<bool> stopSearch(false);

    std::vector<std::thread> threads;
        for (const auto &entry: fs::directory_iterator(currentPath)) {
            if (stopSearch) {
                break;
            }

//            try {
                if (entry.is_directory()) {
                    if (threads.size() < maxThreads) {
                        threads.emplace_back(
                                std::thread(searchInSubDirectory, fileName, entry.path(), std::ref(foundPaths),
                                            std::ref(stopSearch)));
                    } else {
                        searchInSubDirectory(fileName, entry.path(), foundPaths, std::ref(stopSearch));
                    }
                } else if (entry.is_regular_file() && entry.path().filename() == fileName) {
                    foundPaths.push_back(entry.path());
                    stopSearch = true; // Signal other threads to stop searching
                    break;
                }
//            } catch (const fs::filesystem_error &e) { // todo make work from /
//            std::cerr << "Error accessing directory: " << e.what() << std::endl;
//            }
        }

    for (auto &thread: threads) {
        thread.join();
    }
}

void searchInSubDirectory(const std::string &fileName, const fs::path &currentPath, std::vector<fs::path> &foundPaths,
                          std::atomic<bool> &stopSearch) {
    for (const auto &entry: fs::directory_iterator(currentPath)) {
        if (stopSearch) {
            break;
        }
        if (entry.is_directory()) {
            searchInSubDirectory(fileName, entry.path(), foundPaths, stopSearch);
        } else if (entry.is_regular_file() && entry.path().filename() == fileName) {
            foundPaths.push_back(entry.path());
            stopSearch = true; // Signal other threads to stop searching
            break;
        }
    }
}