cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

# Определите название вашего проекта (должно совпадать с названием репозитория).
# Примечание: замените символ '-' на '_'.
project(semester_work_template CXX)

# === Определение стандарта C++ для всего проекта ===

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# === "Включение" предупреждений компилятора (target) ===
# Предупреждения полезны тем, что они позволяют обнаружить потенциальные баги в вашем коде.

# создание интерфейсной библиотеки (т.е. библиотеки без исходных файлов)
add_library(project_warnings INTERFACE)

# установка параметров компиляции для библиотеки
include(cmake/CompilerWarnings.cmake)   # добавление содержимого CompilerWarnings.cmake в этот файл
set_project_warnings(project_warnings)  # set_project_warnings - определена в файле cmake/CompilerWarnings.cmake

# Примечание: теперь мы можем линковать project_warnings с другими библиотеками и исполняемыми файлами,
# тем самым "включая" у них предупреждения компилятора.

# === Добавление переменных пути (target) ===
add_library(project_paths INTERFACE)

target_compile_definitions(project_paths INTERFACE
        PROJECT_SOURCE_DIR="${CMAKE_SOURCE_DIR}"
        PROJECT_DATASET_DIR="${CMAKE_SOURCE_DIR}/dataset/data")

# === Библиотека со структурой данных (target) ===
# Это самое главное, что вы должны реализовать в рамках семестрового проекта.

add_library(${PROJECT_NAME} STATIC
        src/data_structure.cpp
        include/data_structure.hpp)

# включить предупреждения компилятора для библиотеки (линковка)
target_link_libraries(${PROJECT_NAME} PRIVATE project_warnings)

# обозначить директорию с заголовочными файлами для библиотеки
target_include_directories(${PROJECT_NAME} PUBLIC include)

# === Подключение подмодулей проекта ===

add_subdirectory(dataset)
add_subdirectory(examples)
add_subdirectory(benchmark)

# === main (target) ===
add_executable(main main.cpp)
target_link_libraries(main PRIVATE project_warnings ${PROJECT_NAME})
