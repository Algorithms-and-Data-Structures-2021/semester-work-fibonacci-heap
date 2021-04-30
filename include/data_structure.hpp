#pragma once


#include <ostream>
namespace itis {
 
  struct node {
   public:
    node* prev;
    node* next;
    node* child;
    node* parent;
    int value;    // вес, ключ
    int degree;   // количество дочерних узлов
    bool marked;  // были ли потери нодой дочерних узлов
  };
  class FibonacciHeap {
   protected:
    node* heap; // ссылка на корень

   public:
    FibonacciHeap() {
      heap = _empty();
    }
    ~FibonacciHeap() {
      if (heap) {
        _deleteAll(heap);
      }
    }
    // Добавление нового узла
    node* insert(int value);

    // Соединяет текущую кучу с другой
    void merge(FibonacciHeap& other);

    // Является ли куча пустой
    bool isEmpty();

    // Взятие минимума
    int getMinimum();

    // Удаление минимума
    int removeMinimum();

    // Уменьшение ключа на определенное значение
    void decreaseKey(node* n, int value);

    // Вывод
    void output();

   private:
    // Обнуление
    static node* _empty();

    // Создание новой ноды
    node* _create_node(int value);

    // Соединяет текущую кучу с другой
    node* _merge(node* a, node* b);

    void _deleteAll(node* n);

    // Добавление детей
    void _addChild(node* parent, node* child);

    // Сниманием пометку и убираем родителей
    static void _unMarkAndUnParentAll(node* n);

    // Удаление элемента из кольцевого списка
    node* _removeMinimum(node* n);

    // Удаляем уменьшенную ноду из списка и убираем с него пометку
    node* _cut(node* heap, node* n);

    // уменьшаем узел на определенное значение и возвращаем его
    node* _decreaseKey(node* heap, node* n, int value);

    // Вывод потомков
    void _outputChildren(node* n);
  };
}
