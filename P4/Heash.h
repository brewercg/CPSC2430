/*
  Cody Brewer
  CPSC 2430
  5/16/16
  v 0.1
*/
#ifndef __HEASH_H
#define __HEASH_H

#include "Heap.h"
#include "Hash.h"

/*
  Combined hash table and heap
*/

class Heash{
 public:
  Heash(); //simple constructor
  bool remove(int item); // removes given item, returns false if non-existant
  bool insert(int item); // inserts given item, returns false if duplicate
  bool find(int item); // returns true if heash contains item, false otherwise
  int deleteMin(); //removes smallest item, returns its value. 
  void print(); // prints the heash
  
 private:
  Heap heap;
  Hash hash;
  int capacity; //current capacity of Heash
  int size; //current number of items in Heash
};

#endif
