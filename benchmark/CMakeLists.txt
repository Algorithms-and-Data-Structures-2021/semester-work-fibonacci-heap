# Здесь вы можете создавать свои исполняемые файлы (executables)
# исполянемый файл = контрольный тест

# Пример создания контрольного теста (исполняемого файла) под названием demo_benchmark.
# Исходный код предоставлен в файле demo_benchmark.cpp текущей директории.
add_executable(benchmark_insert benchmark_insert.cpp)
add_executable(benchmark_remove benchmark_remove.cpp)
add_executable(benchmark_merge benchmark_merge.cpp)

# Примечание: Не забываем подключить (прилинковать) библиотеку ${PROJECT_NAME} с реализацией структуры данных.
target_link_libraries(benchmark_insert PRIVATE project_paths project_warnings ${PROJECT_NAME})
target_link_libraries(benchmark_remove PRIVATE project_paths project_warnings ${PROJECT_NAME})
target_link_libraries(benchmark_merge PRIVATE project_paths project_warnings ${PROJECT_NAME})