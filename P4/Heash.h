/*
  Cody Brewer
  CPSC 2430
  5/25/16
  v 1.0
*/
#ifndef __HEASH_H
#define __HEASH_H

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
  struct Node{
	Node(); //simple constructor
	int data; //value to store
	int link; //index in related array
	bool deleted; //flag for lazy deletion (used in hashTable only)
  };
  
  Node* heap; //minHeap
  Node* hashTable; //hash table
  int capacity; //current capacity of Heash
  int size; //current number of items in Heash

  int hash(int item); //calculate and return hash value for item
  void reHash(); //expand heash and re-hash table
};

#endif
