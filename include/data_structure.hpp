#pragma once

// Заголовочный файл с объявлением структуры данных
#include <ostream>
namespace itis {
  // Tip 1: объявите здесь необходимые структуры, функции, константы и прочее
  // Пример: объявление константы времени компиляции в заголовочном файле
  inline constexpr auto kStringConstant = "Hello, stranger!";
  // Пример: объявление структуры с полями и методами
  struct node {
   public:
    node* prev;
    node* next;
    node* child;
    node* parent;
    int value;  // Кратчайший путь
    int degree;
    bool marked;
    friend class FibonacciHeap;
  };
  class FibonacciHeap {
   protected:
    node* heap;

   public:

    FibonacciHeap() {
      heap = _empty();
    }
    ~FibonacciHeap() {
      if (heap) {
        _deleteAll(heap);
      }
    }
    node* insert(int value);
    void merge(FibonacciHeap& other);
    bool isEmpty();
    int getMinimum();
    int removeMinimum();
    void decreaseKey(node* n, int value);
    void output();

   private:
    static node* _empty();
    node* _singleton(int value);
    node* _merge(node* a, node* b);
    void _deleteAll(node* n);
    void _addChild(node* parent, node* child);
    static void _unMarkAndUnParentAll(node* n);
    node* _removeMinimum(node* n);
    node* _cut(node* heap, node* n);
    node* _decreaseKey(node* heap, node* n, int value);
    void _outputChildren(node* n);
  };
}
// Tip 2: На начальном этапе разработки структуры данных можете определения методов задавать в
// заголовочном файле, как только работа будет завершена, можно будет оставить здесь только объявления.