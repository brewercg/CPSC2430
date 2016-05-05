/*
  Cody Brewer
  5/2/2016
  PA3 v.1
*/
#include <iostream>

using namespace std;

/*
  Templated Binary Search Tree
  Stores values of type T in BST form.
  Linked Implementation. 
  Provides non-recursive insertion and removal,
  multiple traversal modes, and recursive search.

  Does not automatically re-balance. Is not
  guarenteed to be complete or balanced.
  Does not accept duplicate values.

  Removal of a node with children will result
  in the next-highest value node taking the
  place of the node that was removed. 
*/
template <typename T>
class BST{

 public:
 BST() : myRoot(0) {} //simple constructor
  BST(const BST& orig); //copy constructor
  ~BST(); // deconstructor
  BST& operator=(const BST& orig); //overloaded assignment operator
  bool empty();
  bool search(const T& item); //recursive search
  void insert(const T& item); //non-recursive insertion
  void remove(const T& item); //non-recursive
  int recursiveLevel(const T& item); //returns -1 if item doesn't exist
  int nonrecursiveLevel(const T& item); //return -1 if item doesn't exist
  void levelTraversal(ostream& out); 
  void recursivePreorder(ostream& out); //recursive
  void nonrecursivePreorder(ostream& out); //non-recursive
  void postorder(ostream& out); //non-recursive
  int height(); // recursive
  
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
  BinNode(T item) : data(item), left(0), right(0) {} // non-empty constructor
	
  }; //end of BinNode
  typedef BinNode* BinNodePtr;

  BinNodePtr myRoot; //root node of tree

}; //END BST CLASS DEFINITION

// Overloaded output operator
template <typename T>
ostream& operator<< (ostream &out, const BST<T> &tree){
  tree.levelTraversal(out);
  return out;
}

/*
  Copy Constructor
  Pre: A tree exists to be copied
  Post: A deep copy of the tree is created
*/
template<typename T>
BST<T>::BST(const BST& orig){}

/*
  Destructor
  Pre: Tree exists
  Post: Tree is deconstructed, memory freed
*/
template<typename T>
BST<T>::~BST<T>(){

}

/*
  Overloaded Assignment Operator
  Pre: LHS and RHS trees exist
  Post: LHS is a deep copy of the RHS tree. LHS is returned after copying.
 */
template<typename T>
BST<T>& BST<T>::operator=(const BST& orig){return *this;} //overloaded assignment operator


/*
  Returns true if empty, false otherwise.
  Pre: BST is instantiated
  Post: Result returned
*/
template <typename T>
bool BST<T>::empty()
{
  if (myRoot == 0)
	return true;

  return false;
}

/*
  Recursively searches the tree for the given item.
  Returns true if the item is found, false otherwise.
  
  Pre: Tree Exists
  Post: Result returned, tree is not modified
*/
template <typename T>
bool BST<T>::search(const T& item){
  return false;
}

/*
  Creates a new node containing the given item and inserts
  it into the tree at the appropriate location. Non-recursive.
  
  Pre:Tree exists
  Post:The given item has been inserted into the tree in
  the proper location. An error message is generated if
  the item is already in the tree. 
*/
template <typename T>
void BST<T>::insert(const T& item){

  BinNodePtr newNode = new BinNode(item);
 
  if(empty()){
	myRoot = newNode;
  }
  else{
	// find where to put the new item
	bool finished = false;
	BinNodePtr currentNode = myRoot;
	  
	while(!finished){

	  // add to empty right
	  if( (newNode->data > currentNode->data) && (currentNode->right == 0))
		{
		  currentNode->right = newNode;
		  finished = true;
		}
	  //add to empty left
	  else if( (newNode->data < currentNode->data) && (currentNode->left == 0))
		{
		  currentNode->left = newNode;
		  finished = true;
		}

	  //go left
	  else if( newNode->data < currentNode->data)
		currentNode = currentNode->left;

	  //go right
	  else if(newNode->data > currentNode->data)
		currentNode = currentNode->right;

	  //duplicate value
	  else{
		cerr << "Duplicate item, insert not performed!" << endl;
		finished = true;
	  }
	}
  }
}

/*
  Removes the given item from the tree. Non recursive.

  Pre:Tree exists
  Post:Item is removed from tree, if present.
*/
template <typename T>
void BST<T>::remove(const T& item){

  //can't remove from empty tree
  if ( empty() ){
	cerr << "Can't remove from empty tree!" << endl;
	return;
  }
  
  BinNodePtr currentNode = myRoot; //node to be removed
  BinNodePtr previousNode = 0; //parent of currentNode

  //tracks which direction to move to reach currentNode
  //from previousNode. True if right, false if left
  bool lastMoveRight = false; 

  //find the item to be removed
  while( currentNode != 0 && currentNode->data != item ){
	if(item > currentNode->data){
	  previousNode = currentNode;
	  currentNode = currentNode->right;
	  lastMoveRight = true;
	}
	else if(item < currentNode->data){
	  previousNode = currentNode;
	  currentNode = currentNode->left;
	  lastMoveRight = false;
	}
  }

  //item not found, display error and return
  if(currentNode == 0){
	cerr << "Item not found, cannot remove!" << endl;
	return;
  }

  //item found, remove it

  //case: currentNode has no children
  if(currentNode->left == 0 && currentNode->right == 0){

	//handle removing root node
	if(currentNode == myRoot){
	  myRoot = 0;
	  delete currentNode;
	}
	else if(lastMoveRight){
	  previousNode->right = 0;
	  delete currentNode;
	}
	else{
	  previousNode->left = 0;
	  delete currentNode;
	}
  }

  //case: currentNode has right child only
  else if(currentNode->left == 0){

	//handle removing root node
	if(currentNode == myRoot){
	  myRoot = myRoot->right;
	  delete currentNode;
	}
	
	else if(lastMoveRight){
	  previousNode->right = currentNode->right;
	  delete currentNode;
	}
	else{
	  previousNode->left = currentNode->right;
	  delete currentNode;
	}
  }

  //case: currentNode has left child only
  else if(currentNode->right == 0){

	//handle removing root node
	if(currentNode == myRoot){
	  myRoot = myRoot->left;
	  delete currentNode;
	}
	else if(lastMoveRight){
	  previousNode->right = currentNode->left;
	  delete currentNode;
	}
	else{
	  previousNode->left = currentNode->left;
	  delete currentNode;
	}
  }

  //case: currentNode has 2 children
  else{

	//find next highest value in tree
	BinNodePtr nextHighest = currentNode->right;
	BinNodePtr nextHparent = currentNode;
	while(nextHighest->left != 0){
	  nextHparent = nextHighest;
	  nextHighest = nextHighest->left;
	}

	//handle removing root node
	if(currentNode == myRoot){
	  myRoot = nextHighest;
	}
	
	else{
	  //link currentNode's parent to nextHighest
	  if(lastMoveRight)
		previousNode->right = nextHighest;
	  else
		previousNode->left = nextHighest;
	}
	
	//link nextHighest to currentNode's left subtree
	nextHighest->left = currentNode->left;

	//ensure nextHparent doesn't link back up the tree
	//and that currentNode's right subtree isn't lost
	if(nextHparent != currentNode){
	  nextHparent->left = nextHighest->right;
	  nextHighest->right = currentNode->right;
	}
	
	delete currentNode;	
  }
}
 
/*
  Returns the level of the tree on which the given item is stored.
  Returns -1 if the item is not present in the tree. Starts with
  the root node as level 0. Recursive.
  Pre:Tree exists
  Post:Item's level is returned, if present. Returns -1 otherwise
*/
template <typename T>
int BST<T>::recursiveLevel(const T& item){return -1;}

/*
  Returns the level of the tree on which the given item is stored.
  Returns -1 if the item is not present in the tree. Starts with
  the root node as level 0. Non-recursive.
  Pre:Tree exists
  Post:Item's level is returned, if present. Returns -1 otherwise
*/
template <typename T>
int BST<T>:: nonrecursiveLevel(const T& item){return -1;}

/*
  Traverses the tree top-to-bottom, left-to-right, beginning at
  the root. Streams contents to given ostream. Non-recursive.
  Pre:Tree exists
  Post:Contents of tree are sent to streaming output.
*/
template <typename T>
void BST<T>::levelTraversal(ostream& out){} 

/*
  Recursive preorder traversal of tree. Contents are streamed
  to given output stream. 
  Pre:Tree exists
  Post:Contents of tree are streamed out in order of traversal.
*/
template <typename T>
void BST<T>::recursivePreorder(ostream& out){
  
}


/*
  Non-recursive preorder traversal of tree. Contents are streamed
  to given output stream. 
  Pre:Tree exists
  Post:Contents of tree are streamed out in order of traversal.
*/
template <typename T>
void BST<T>::nonrecursivePreorder(ostream& out){}

/*
  Non-recursive postorder traversal of tree. Contents are streamed
  to given output stream. 
  Pre:Tree exists
  Post:Contents of tree are streamed out in order of traversal.
*/
template <typename T>
void BST<T>::postorder(ostream& out){}

/*
  Recursively determines the height of the tree. The
  height of the tree is then returned to the console. 
  Pre:Tree exists
  Post:Height of tree is returned
*/
template <typename T>
int BST<T>::height(){return 0;}

