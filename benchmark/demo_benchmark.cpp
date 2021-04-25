#include <fstream>      // ifstream
#include <iostream>     // cout
#include <string>       // string, stoi
#include <string_view>  // string_view
#include <chrono>       // high_resolution_clock, duration_cast, nanoseconds
#include <sstream>      // stringstream

// подключаем вашу структуру данных
#include "data_structure.hpp"

using namespace std;
using namespace itis;

// абсолютный путь до набора данных и папки проекта
static constexpr auto kDatasetPath = string_view{PROJECT_DATASET_DIR};
static constexpr auto kProjectPath = string_view{PROJECT_SOURCE_DIR};

int main(int argc, char **argv) {

  // Tip 1: входные аргументы позволяют более гибко контролировать работу вашей программы.
  // Можете передать путь до входного/выходного тестового файла в качестве аргумента программы.

  for (int index = 0; index < argc; index++) {
    cout << "Arg: " << argv[index] << '\n';
  }

  // Tip 2: для перевода строки в число можете использовать функцию stoi (string to integer)

  // можете использовать функционал класса stringstream для обработки строки
  auto ss = stringstream("0 1 2");  // передаете строку (входной аргумент или строку из файла) и обрабатываете ее

  int number = 0;
  ss >> number;  // number = 0
  ss >> number;  // number = 1
  ss >> number;  // number = 2

  // работа с набором данных
  const auto path = string(kDatasetPath);
  cout << "Path to the 'dataset/' folder: " << path << endl;

  auto input_file = ifstream(path + "/dataset-example.csv");

  if (input_file) {
    // чтение и обработка набора данных ...
  }

  // Контрольный тест: операции добавления, удаления, поиска и пр. над структурой данных

  // Tip 3: время работы программы (или участка кода) можно осуществить
  // как изнутри программы (std::chrono), так и сторонними утилитами

  const auto time_point_before = chrono::steady_clock::now();

  // здесь находится участок кода, время которого необходимо замерить

  const auto time_point_after = chrono::steady_clock::now();

  // переводим время в наносекунды
  const auto time_diff = time_point_after - time_point_before;
  const auto time_elapsed_ns = chrono::duration_cast<chrono::nanoseconds>(time_diff).count();

  cout << "Time elapsed (ns): " << time_elapsed_ns << '\n';

  return 0;
}
