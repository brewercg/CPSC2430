/*
  Cody Brewer
  CPSC 2430
  5/24/16
  v 0.5
*/

#define DEFAULT_SIZE 53 //due to hash algorithm

#include "Heash.h"
#include <iostream>

using namespace std;

/*
  Simple constructor. Makes an empty Heash of default size.

  Pre: none
  Post: Empty Heash created
*/
Heash::Heash(){
  heap = new Node[DEFAULT_SIZE];
  hashTable = new Node[DEFAULT_SIZE];
  capacity = DEFAULT_SIZE;
  size = 0;
}

/*
  Default Node constructor. Values signify an uninitialized node.

  Pre: none
  Post: "empty" node constructed
*/
Heash::Node::Node(){
  data = -1;
  link = 0;
  deleted = false;
}

/*
  Removes the given item from the heash. Returns true if the
  item was found and removed, false otherwise.

  Pre: none
  Post: item is removed from the Heash
 */
bool Heash::remove(int item){

  //item not found, return false
  if( !find(item))
	return false;

  //find item in hash table
  int hashValue = hash(item);
  int tableLocation = hashValue;
  bool itemFound = false;
  
  //search hashTable using linear probing
  for(int i = hashValue; i < capacity; ++i){
	//item found
	if(hashTable[i].data == item && !hashTable[i].deleted){
	  tableLocation = i;
	  itemFound = true;
	  break;
	}
  }

  
  //wrap around to beginning and continue search
  if( !itemFound){
	for(int i = 1; i < hashValue; ++i){
	  //item found
	  if(hashTable[i].data == item && !hashTable[i].deleted){
		tableLocation = i;
		itemFound = true;
		break;
	  }
	}
  }

  //remove item from hash table
  hashTable[tableLocation].deleted = true;

  int heapLocation = hashTable[tableLocation].link;

  //remove item from heap
  //replace removed item with last item in heap
  heap[heapLocation] = heap[size];
  --size;

  //update link in hashTable
  hashTable[heap[heapLocation].link].link = heapLocation;

  //percolate down
  int hole = heapLocation;
  int bigger;
  Node temp = heap[hole];

  while(hole <= size/2){
	//determine if left or right child is bigger
	heap[hole*2].data > heap[hole*2+1].data ? bigger = hole*2 : bigger = hole*2+1;

	temp = heap[hole]; //hold parent in temp
	heap[hole] = heap[bigger]; //move bigger child up
	hashTable[heap[hole].link].link = hole; //update link in hash table
	heap[bigger] = temp; //move parent into gap left by child
	hashTable[heap[bigger].link].link = bigger; //update link in hash table
  }
  
  
  return true;
  
}

/*
  Adds the given item to the Heash. Returns true if
  the item is added, false if the item is already in the heash

  Pre: none
  Post: Heash contains item
 */
bool Heash::insert(int item){

  //return false if already in heash
  //TODO:this can be done more efficiently during insert instead of as a separate call!
  if(find(item))
	return false;
  
  //add item to hash table
  int hashValue = hash(item);
  int tableLocation = hashValue;

  //use linear probing to find next free space

  //scan to end of table
  while(hashTable[tableLocation].data != -1 && !hashTable[tableLocation].deleted
		&& tableLocation < capacity){
	++tableLocation;
  }

  //free space not found, continue scanning from beginning
  if((hashTable[tableLocation].data != -1 && !hashTable[tableLocation].deleted) || tableLocation >= capacity){
	tableLocation = 0;

	//scan until free space found or original hashValue is reached
	// if original value is reached:
	//the heash is full and did not resize <- THIS SHOULD NEVER HAPPEN, reHash()
	//should occur first
	while(hashTable[tableLocation].data != -1 && !hashTable[tableLocation].deleted
		  && tableLocation <= hashValue){
	  ++tableLocation;
	}
  }

  //add item to the free space that was found in the table
  hashTable[tableLocation].data = item;
  hashTable[tableLocation].deleted = false;


  //add item to heap
  int hole = ++size;
  Node node;
  node.data = item;
  node.link = tableLocation;
  
  heap[hole] = node;
  hashTable[tableLocation].link = hole;

  //percolate up
  for( ; (hole > 1) && (node.data < heap[hole/2].data); hole /= 2){

	//move larger value down
	heap[hole] = heap[hole/2];

	//update link in hash table for value that was moved
	hashTable[heap[hole].link].link = hole;

	//place item into hole that was created
	heap[hole/2] = node;

	//update link in hash table for value that was moved
	hashTable[heap[hole/2].link].link = hole/2;
  }

  
  
  return true;
}

/*
  Returns true if the item is in the heash, false otherwise

  Pre: none
  Post: Returns true if found, false otherwise. Heash is not
         modified
 */
bool Heash::find(int item){
  int hashValue = hash(item);
  
  //search hashTable using linear probing
  for(int i = hashValue; i < capacity; ++i){
	//item found
	if(hashTable[i].data == item && !hashTable[i].deleted)
	  return true;

	//ran into an uninitialized space, item is not in table
	if(hashTable[i].data == -1)
	  return false;
  }

  //wrap around to beginning and continue search
  for(int i = 0; i < hashValue; ++i){
	//item found
	if(hashTable[i].data == item && !hashTable[i].deleted)
	  return true;
	//ran into an uninitialized space, item is not in table
	if(hashTable[i].data == -1)
	  return false;	
  }

  //item not found
  return false;
}

/*
  Deletes the smallest-value item in the Heash.
  Returns the value of the removed item.
  Returns -1 if the heash is empty.

  Pre: none
  Post: smallest-value item is removed from the Heash
*/
int Heash::deleteMin(){

  //return -1 if empty
  if(size == 0)
	return -1;
  
  //get minimum item from heap for return value
  int item = heap[1].data;

  //delete from hashTable
  hashTable[heap[1].link].deleted = true;
  
  //replace smallest item with last item in heap
  heap[1] = heap[size];
  --size;

  //update link in hashTable
  hashTable[heap[1].link].link = 1;

  //percolate down
  int hole = 1;
  int smaller;
  Node temp = heap[hole];

  while(hole <= size/2
		&& (heap[hole*2+1].data < heap[hole].data || heap[hole*2].data < heap[hole].data)){
	//determine if left or right child is bigger
	heap[hole*2].data < heap[hole*2+1].data ? smaller = hole*2 : smaller = hole*2+1;

	temp = heap[hole]; //hold parent in temp
	heap[hole] = heap[smaller]; //move smaller child up
	hashTable[heap[hole].link].link = hole; //update link in hash table
	heap[smaller] = temp; //move parent into gap left by child
	hashTable[heap[smaller].link].link = smaller; //update link in hash table
	hole = smaller; //update hole location
  }

  return item;
  
}

/*
  Prints the hash table and heap.

  Pre: none
  Post: Heash contents printed to cout
*/
void Heash::print(){

  //print hash table
  cout << "**Hash Table**" << endl;
  cout << "(index : value : link)" << endl;
  for(int i = 0; i < capacity; ++i){
	//only print occupied spaces
	if(hashTable[i].data != -1 && !hashTable[i].deleted){
	  cout << "( " << i << " : " << hashTable[i].data
		   << " : " << hashTable[i].link << " )" << endl;
	}
  }
  cout << endl;

  //print minHeap
  cout << "**minHeap**" << endl;
  cout << "Contents printed in array order, (link : value)" << endl;
  for(int i = 1; i <= size; i++){
	cout << "( " << heap[i].link << " :  " << heap[i].data << " )" << endl;
  }
  cout << endl;
}

/*
  Calculates the hash value for the given item.

  Pre: item is a positive integer (includes zero)
  Post: hash value for the item is returned
*/
int Heash::hash(int item){
  if(item < 0){
	cerr << "Invalid value, hash not performed!" << endl;
	return -1;
  }
  return (53 % item);
}

/*
  Expands the size of the Heash and re-hashes the hash table

  Pre: heash is at least 70% full
  Post: heash is doubled in size and the hash table has been rehashed 
*/
void Heash::reHash(){
  
}
