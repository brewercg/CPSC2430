/*
  Cody Brewer
  CPSC 2430
  5/16/16
  v 0.1
*/

#ifndef __HASH_H
#define __HASH_H

//fwd declaration for links to heap
struct heapNode;


/*
  Array-based implementation of a hash table
*/

struct hashNode{
  hashNode(); //default constructor
  int data;//item to be stored
  heapNode* link; //link to the associated minHeap
  bool deleted; //marks if the node has been deleted
};

class Hash{
 public:
  Hash(); //default constructor
  Hash(int hashSize); // construct a hash table of size hashSize
  hashNode* insert(int item); //inserts a new value into the hash table
  bool find(int item); //returns true if successful

  //returns a pointer to the removed item, if it exists. Otherwise returns 0.
  hashNode* remove(int item);
  void print(); //prints the hash table

 private:
  hashNode* hashArray; //actual structure of heap
  int hash(int key); //calculate hash value for given key
  void reHash(); //reHash table into a larger array
  int capacity; //size of hash table
  int size; //number of things in hash table
};


#endif
