/*
  Cody Brewer
  CPSC 2430
  5/16/16
  v 0.1
*/

#ifndef __HEAP_H
#define __HEAP_H

struct hashNode; //forward declaration for link to hashtable

/*
  Array implementation of a priority queue (min heap).
*/

struct heapNode{
  heapNode();
  int data;
  hashNode* link;
};

class Heap{
 public:
  Heap(); //default constructor
  Heap(int heapSize); //construct a heap of size heapSize
  heapNode* insert(int item); //inserts a new value into the heap
  int deleteMin(); //deletes the top (smallest) item and returns its value
  void remove(heapNode* node); //removes the given item from the heap
  void print(); //displays the heap to cout

 private:
  heapNode* heapArray; //actual structure of heap
  int size; //current number of items stored in heap
  int capacity; //size of heap
};

#endif
