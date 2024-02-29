//
// Created by Dmytro Borak on 29.02.24.
//

#ifndef GL_DMYTRO_BORAK_MULTITHREADED_FILE_SEARCH_H
#define GL_DMYTRO_BORAK_MULTITHREADED_FILE_SEARCH_H

#include <filesystem>
#include <string>
#include <vector>
#include <atomic>
#include <thread>

namespace fs = std::filesystem;

std::vector<fs::path>  searchForFile(const std::string &fileName, const fs::path &currentPath,
                                     unsigned int maxThreads = std::thread::hardware_concurrency());

#endif //GL_DMYTRO_BORAK_MULTITHREADED_FILE_SEARCH_H
