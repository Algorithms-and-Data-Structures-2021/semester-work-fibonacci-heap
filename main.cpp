#include <iostream>
#include <string>
#include "data_structure.hpp"

using namespace std;

int main(int argc, char *argv[]) {
  for (int index = 0; index < argc; index++) {
    cout << index << ": " << argv[index] << endl;
  }
    itis::FibonacciHeap heap;
    heap.insert(3);
    heap.insert(2);
    heap.insert(8);
    heap.insert(6);
    heap.output();
    heap.removeMinimum();
    heap.output();
//    itis::node* five = heap.insert(5);
//    itis::FibonacciHeap heap2;
//    heap2.insert(9);
//    heap2.insert(1);
//    heap2.insert(7);
//    heap2.insert(3);
//    heap2.insert(8);
//    heap.decreaseKey(five,6);
//    heap.output();
//    heap2.output();
//    heap.merge(heap2);
//    heap.output();
//    heap2.output();
    return 0;
  }