#include "data_structure.hpp"

// файл с определениями
namespace itis {
  
  
  node* FibonacciHeap::insert(int value) {
    node* result = _create_node(value);  // Создаем узел
    heap = _merge(heap, result);       // Мерджи его в кучу
    return result;
  }
  
  
  bool FibonacciHeap::isEmpty() {
    return heap == nullptr;
  }
  

  void FibonacciHeap::merge(FibonacciHeap& other) {
    heap = _merge(heap, other.heap);
    other.heap = _empty();
  }
  
  
  void FibonacciHeap::decreaseKey(node* n, int value) {
    heap = _decreaseKey(heap,n,value);
  }
  
  
  int FibonacciHeap::getMinimum() {
    return heap->value;
  }
  
  
  int FibonacciHeap::removeMinimum() {
    node* old = heap;
    heap = _removeMinimum(heap);
    int result = old->value;
    delete old;
    return result;
  }
  
  
  node* FibonacciHeap::_merge(node* a, node* b) {
    if (a == nullptr) {
      return b;
    }
    if (b == nullptr) {
      return a;
    }
    if (a->value > b->value) {
      node* temp = a;
      a = b;
      b = temp;
    }
    node* aNext = a->next;
    node* bPrev = b->prev;
    a->next = b;
    b->prev = a;
    aNext->prev = bPrev;
    bPrev->next = aNext;
    return a;
  }
  
  
  node* FibonacciHeap::_empty() {
    return nullptr;
  }
  
  
  void FibonacciHeap::_deleteAll(node* n) {  //Ругается на рекурсию
    if (n != nullptr) {
      node* current = n;
      do {  // Идет по кольцевому списку и удаляет следующий до тех пор,
        node* temp = current;  // пока не дойдет до начала
        current = current->next;
        _deleteAll(temp->child);
        delete temp;
      } while (current != n);
    }
  }
  
  
  node* FibonacciHeap::_create_node(int value){  // create Node with value
    node* n = new node;
    n->value = value;
    n->prev = n->next = n;
    n->degree = 0;
    n->marked = false;
    n->child = nullptr;
    n->parent = nullptr;
    return n;
  }
  
  
  node* FibonacciHeap::_removeMinimum(node* n) {
    _unMarkAndUnParentAll(n->child);
    if (n->next == n) {
      n = n->child;
    } else {
      n->next->prev = n->prev;
      n->prev->next = n->next;
      n = _merge(n->next, n->child);
    }
    if (n == nullptr)
      return n;
    node* trees[64] = {nullptr};
    while (true) {
      if (trees[n->degree] != nullptr) {
        node* t = trees[n->degree];
        if (t == n)
          break;
        trees[n->degree] = nullptr;
        if (n->value < t->value) {
          t->prev->next = t->next;
          t->next->prev = t->prev;
          _addChild(n, t);
        } else {
          t->prev->next = t->next;
          t->next->prev = t->prev;
          if (n->next == n) {
            t->next = t->prev = t;
            _addChild(t, n);
            n = t;
          } else {
            n->prev->next = t;
            n->next->prev = t;
            t->next = n->next;
            t->prev = n->prev;
            _addChild(t, n);
            n = t;
          }
        }
        continue;
      } else {
        trees[n->degree] = n;
      }
      n = n->next;
    }
    node* min = n;
    node* start = n;
    do {
      if (n->value < min->value)
        min = n;
      n = n->next;
    } while (n != start);
    return min;
  }
  
  
  void FibonacciHeap::_unMarkAndUnParentAll(node* n) {
    if (n == nullptr)
      return;
    node* current = n;
    do {
      current->marked = false;
      current->parent = nullptr;
      current = current->next;
    } while (current != n);
  }
  
 
  void FibonacciHeap::_addChild(node* parent, node* child) {
    child->prev = child->next = child;  //??
    child->parent = parent;
    parent->degree++;
    parent->child = _merge(parent->child, child);
  }
  
  
  node * FibonacciHeap::_decreaseKey(node* heap, node* n, int value) {
    if (n ->value < value) return heap;
    n ->value = value;
    if ( n -> parent) {
      if (n -> value < n -> parent -> value) {
        heap = _cut(heap,n);
        node* parent = n ->parent;
        n -> parent = nullptr;
        while (parent != nullptr && parent ->marked){
          heap = _cut(heap,parent);
          n = parent;
          parent = n ->parent;
          n -> parent = nullptr;
        }
        if (parent != nullptr && parent -> parent != nullptr) parent -> marked = true;
      }
    } else {
      if (n ->value < heap ->value) heap = n;
    }
    return heap;
  }
  
  
  node * FibonacciHeap::_cut(node* heap, node* n) {
    if (n->next == n) {
      n->parent->child = nullptr;
    } else {
      n->next->prev = n->prev;
      n->prev->next = n->next;
      n->parent->child = n->next;
    }
    n->next = n->prev = n;
    n->marked = false;
    return _merge(heap, n);
  }
  
  
  void FibonacciHeap::output() {
    printf("FibHeap {\n");
    if(heap==NULL) {
      printf("empty;\n}\n");
      return;
    }
    printf("minimum -> ",heap);
    node* c=heap;
    do {
      _outputChildren(c);
      c=c->next;
    } while(c!=heap);
    printf("}\n");
  }
  
  
  void FibonacciHeap::_outputChildren(node* n) {
    printf("\"%p\" [value=%d];\n",n,n->value);
    if(n->child) {
      node* c=n->child;
      do {
        printf("\"%p\" -> \"%p\";\n",n,c);
        _outputChildren(c);
        c=c->next;
      } while(c!=n->child);
    }
  }
}
