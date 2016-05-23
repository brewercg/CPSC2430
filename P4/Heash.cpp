/*
  Cody Brewer
  CPSC 2430
  5/16/16
  v 0.1
*/

#define DEFAULT_SIZE 20

#include "Heash.h"

/*
  Simple constructor. Makes an empty Heash of default size.

  Pre: none
  Post: Empty Heash created
*/
Heash::Heash(){
  heap = Heap(DEFAULT_SIZE);
  hash = Hash(DEFAULT_SIZE);
  capacity = DEFAULT_SIZE;
  size = 0;
}

/*
  Removes the given item from the heash. Returns true if the
  item was found and removed, false otherwise.

  Pre: none
  Post: item is removed from the Heash
 */
bool Heash::remove(int item){

  //attempt to remove item from hash table
  hashNode* hashLocation = hash.remove(item);

  //item not found, return false
  if(hashLocation == 0)
	return false;

  //remove item from heap
  heap.remove(hashLocation->link);

  return true;
  
}

/*
  Adds the given item to the Heash. Returns true if
  the item is added, false if the item is already in the heash

  Pre: none
  Post: Heash contains item
 */
bool Heash::insert(int item){

  //add item to hash table
  hashNode* tableLocation = hash.insert(item);

  //return false if item is already in hash table
  if(tableLocation == 0)
	return false;

  //add item to heap
  heapNode* heapLocation = heap.insert(item);

  //link table to heap and vice versa
  heapLocation->link = tableLocation;
  tableLocation->link = heapLocation;
	
  return true;
}

/*
  Returns true if the item is in the heash, false otherwise

  Pre: none
  Post: Returns true if found, false otherwise. Heash is not
         modified
 */
bool Heash::find(int item){
  return hash.find(item);
}

/*
  Deletes the smallest-value item in the Heash.
  Returns the value of the removed item.
  Returns -1 if the heash is empty.

  Pre: none
  Post: smallest-value item is removed from the Heash
*/
int Heash::deleteMin(){
  //deleted minimum item from heap
  int item = heap.deleteMin();

  //heash was empty
  if(item == -1)
	return -1;

  hash.remove(item);
  --size;

  return item;
  
}

void Heash::print(){
  hash.print();
  heap.print();
}
