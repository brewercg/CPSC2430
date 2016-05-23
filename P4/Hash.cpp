/*
  Cody Brewer
  CPSC 2430
  5/16/16
  v 0.1
*/

#include "Hash.h"
#include <iostream>


/*
  hashNode constructor
*/
hashNode::hashNode(){
  data = -1;
  link = 0;
  deleted = false;
}

/*
  Default constructor

  pre:none
  Post: default size hash created
*/
Hash::Hash(){
  hashArray = new hashNode[20];
  size = 0;
  capacity = 20;
}


/*
  Constructor

  Pre:none
  Post: empty hash table is created
*/
Hash::Hash(int hashSize){
  hashArray = new hashNode[hashSize];
  size = 0;
  capacity = hashSize;
}

/*
  Inserts the given item into the hash table.
  Returns a pointer to the item.
  Returns 0 if the item is already in the table.
  Collisions are resolved via linear probing. 

  Pre: none
  Post: Hash Table contains the item
 */
hashNode* Hash::insert(int item){
  return 0;
}

/*
  Returns true if the hash table contains
  the given item, false otherwise.

  Pre: none
  Post: result is returned, table is not modified.
*/
bool Hash::find(int item){
  return false;
}

/*
  Returns a pointer to the removed item, if it exists.
  Returns 0 if the item is not in the table.

  Pre:none
  Post: item is removed from table
*/
hashNode* Hash:: remove(int item){
  return 0;
}

/*
  Prints the table

  Pre: none
  Post: table is printed to cout
*/
void Hash::print(){
  std::cout << "Hash: ";

  for(int i = 0; i < size; ++i){
	std::cout << hashArray[i].data << " ";
  }

  std::cout << std::endl;
}

/*
  Calculates the hash value for a given key

  Pre: none
  Post: hash value is returned
*/
int hash(int key){
  return (key % 53);
}

/*
  Re-hashes the table into a bigger table

  Pre: Table is >= 70% full
  Post: Table size is doubled, values are re-hashed.
*/
void reHash(){

}
