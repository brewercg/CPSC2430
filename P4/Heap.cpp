/*
  Cody Brewer
  CPSC 2430
  5/16/16
  v 0.1
*/

#include "Heap.h"
#include <iostream>
#include "Hash.h"

/*
  heapNode constructor
*/
heapNode::heapNode(){
  data = -1;
  link = 0;
}

/*
  Default constructor
*/
Heap::Heap(){
  heapArray = new heapNode[20];
  size = 0;
  capacity = 20;
}

/*
  Constructor

  Pre: none
  Post: Empty heap of given size is created.
*/
Heap::Heap(int heapSize){
  heapArray = new heapNode[heapSize];
  size = 0;
  capacity = heapSize;
}

/*
  Inserts a new value into the heap.
  Returns a pointer to the value's location, if insert
  was successful.

  Pre: none
  Post: Heap contains the item
*/
heapNode* Heap::insert(int item){
  int hole = ++size;

  heapNode node;
  node.data = item;

  //heap was empty
  if(hole == 1){
	heapArray[hole] = node;
  }
  
  //percolate up
  for( ; (hole > 1) && (node.data < heapArray[hole/2].data); hole /= 2){

	//move larger value down
	heapArray[hole] = heapArray[hole/2];

	//update link in hash table for value that was moved
	heapArray[hole].link->link = &heapArray[hole];

	//place item into hole that was created
	heapArray[hole/2] = node;
  }

  return &heapArray[hole];
}

/*
  Removes the smallest-value item from the heap.
  Returns the vale of the item that was removed.
  Returns -1 if the heap is empty.

  Pre: Heap contains at least one value
  Post: Smallest value is removed from heap.
  TODO: just call remove() on heapArray[1]
*/
int Heap::deleteMin(){

  // return -1 if empty
  if(size == 0)
	return -1;

  //get smallest value from top of heap
  int smallest = heapArray[1].data;

  //replace smallest value with last value in heap
  heapArray[1] = heapArray[size];
  --size;

  //update link in hash table
  heapArray[1].link->link = &heapArray[1];
  
  //percolate down
  int hole = 1;
  int bigger;
  heapNode temp = heapArray[hole];

  while(hole <= size/2){
	//determine if left or right child is bigger
	heapArray[hole*2].data > heapArray[hole*2+1].data ? bigger = hole*2 : bigger = hole*2+1;
  
	temp = heapArray[hole]; //hold parent in temp
	heapArray[hole] = heapArray[bigger]; //move bigger child up
	heapArray[hole].link->link = &heapArray[hole]; //update link in hash table
	heapArray[bigger] = temp; //move parent into gap left by child
	heapArray[bigger].link->link = &heapArray[bigger];//update link in hash table

	hole = bigger;
  }
  
  return smallest;
  
}

/*
  Removes the item at the given location from the heap.

  Pre: param node is a pointer to a value inside the heap.
  Post: node is removed from the heap.
  TODO: modify deleteMin() to delete any node
*/
void Heap::remove(heapNode* node){

  // return -1 if empty
  if(size == 0)
	return -1;

  //get smallest value from top of heap
  int smallest = heapArray[1].data;

  //replace smallest value with last value in heap
  heapArray[1] = heapArray[size];
  --size;

  //update link in hash table
  heapArray[1].link->link = &heapArray[1];
  
  //percolate down
  int hole = 1;
  int bigger;
  heapNode temp = heapArray[hole];

  while(hole <= size/2){
	//determine if left or right child is bigger
	heapArray[hole*2].data > heapArray[hole*2+1].data ? bigger = hole*2 : bigger = hole*2+1;
  
	temp = heapArray[hole]; //hold parent in temp
	heapArray[hole] = heapArray[bigger]; //move bigger child up
	heapArray[hole].link->link = &heapArray[hole]; //update link in hash table
	heapArray[bigger] = temp; //move parent into gap left by child
	heapArray[bigger].link->link = &heapArray[bigger];//update link in hash table

	hole = bigger;
  }  
  
}

/*
  Prints the heap.

  Pre: none
  Post: heap is printed to cout.
*/
void Heap::print(){
  std::cout << "Heap: ";
  
  for(int i = 0; i < size; ++i){
	std::cout << heapArray[i].data << " ";
  }

  std::cout << std::endl;
}

