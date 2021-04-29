
#include <fstream>      // ifstream
#include <iostream>     // cout
#include <string>       // string, stoi
#include <string_view>  // string_view
#include <chrono>       // high_resolution_clock, duration_cast, nanoseconds
#include <vector>

// подключаем вашу структуру данных
#include "data_structure.hpp"

using namespace std;
using namespace itis;

// абсолютный путь до набора данных и папки проекта
static constexpr auto kDatasetPath = string_view{PROJECT_DATASET_DIR};
static constexpr auto kProjectPath = string_view{PROJECT_SOURCE_DIR};

int main() {

  // Tip 1: входные аргументы позволяют более гибко контролировать параметры вашей программы
  const auto path = string(kDatasetPath);
  const auto output_path = string(kProjectPath) + "/benchmark/result/benchmark_insert_result.csv";

  // работа с набором данных
  vector <string> folders = {"01", "02", "03", "04", "05", "06", "07", "08", "09", "10"};
  vector <string> files = {"100", "500", "1000", "5000", "10000", "50000", "100000", "500000", "1000000", "5000000"};
  itis::FibonacciHeap heap;
  for (string file : files) { // Проходим по всем 10 .csv файлам
    for (string folder : folders) { // Проходим по всем 10 папкам с файлами
      for (int i = 1; i < 11; i++) { // Запускаем замерку времени 10 раз
        string line = "1";
        auto input_file = ifstream(path + "/" + "insert/" + folder + "/" + file + ".csv");
        auto time_diff_insert = chrono::nanoseconds::zero();
        cout << (path + "/" + "insert/" + folder + "/" + file) << endl;
        // здесь находится участок кода, время которого необходимо замерить
        if (input_file) {
          while (line != "") {
            getline(input_file, line);

            if (line == "") {
              break;
            }
            const auto time_point_before_insert = chrono::steady_clock::now();
            heap.insert(stoi(line));
            const auto time_point_after_insert = chrono::steady_clock::now();
            time_diff_insert += time_point_after_insert - time_point_before_insert;
          }
        }

        const auto time_elapsed_ns_insert = chrono::duration_cast<chrono::nanoseconds>(time_diff_insert).count();
        cout << time_elapsed_ns_insert << endl;

        input_file.close();

        // Открываем файл для записи и вносим полученые данные
        auto output_file = fstream(output_path, ios::app);
        output_file << folder << "," << file << "," << i << "," << time_elapsed_ns_insert << endl;
        output_file.close();
      }
    }
  }
  return 0;
}