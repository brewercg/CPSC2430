/*
  Cody Brewer
  5/2/2016
  Lab5 v1
*/
#include <iostream>

using namespace std;

template <typename T>
class BST{

 public:
 BST() : myRoot(0) {} //simple constructor

  /*
	Returns true if empty, false otherwise.
	Pre: BST is instantiated
	Post: Result returned
  */
  bool isEmpty()
  {
	if (myRoot == 0)
	  return true;

	return false;
  }

 private:

  /*
	Node for the BST. Each node includes a data
	member of the templated type, and a link to
	up to 2 other BinNodes. 
   */
  class BinNode {
  public:
	T data;
	BinNode* left;
	BinNode* right;
  BinNode() : left(0), right(0) {} //simple BinNode constructor

  // construct a BinNode with the given item
  BinNode(T item) : data(item), left(0), right(0) {}
  }; //end of BinNode

  typedef BinNode* BinNodePtr;

  BinNodePtr myRoot; //root node of tree

};


  
