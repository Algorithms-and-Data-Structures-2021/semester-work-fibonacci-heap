# Здесь вы можете создавать свои исполняемые файлы (executables)
# исполянемый файл = генератор набора данных

# Пример создания генератора данных (исполняемого файла) под названием generate_csv_dataset.
# Исходный код предоставлен в файле generate_csv_dataset.cpp текущей директории.
add_executable(generate_csv_dataset generate_csv_dataset.cpp)
target_link_libraries(generate_csv_dataset PRIVATE project_warnings project_paths)