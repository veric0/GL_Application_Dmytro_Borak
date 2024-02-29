cmake_minimum_required(VERSION 3.22)
project(GL_test_Dmytro_Borak)

set(CMAKE_CXX_STANDARD 17)

#add_executable(GL_Application_Dmytro_Borak main.cpp
#        multithreaded_file_search.cpp
#        multithreaded_file_search.h)


# Створюємо статичну бібліотеку
add_library(MultithreadedFileSearch STATIC multithreaded_file_search.cpp)

# Додаємо виконавчий файл для демонстрації використання бібліотеки
add_executable(GL_Application_Dmytro_Borak application.cpp)

# Підключаємо бібліотеку до виконавчого файлу
target_link_libraries(GL_Application_Dmytro_Borak MultithreadedFileSearch)
