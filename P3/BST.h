/*
  Cody Brewer
  5/2/2016
  PA3 v.1
*/
#include <iostream>

using namespace std;

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

// Overloaded node comparison operator
template <typename T>
bool operator< (const typename BST<T>::BinNode &node1,
				const typename BST<T>::BinNode &node2)
{
  return (node1.data < node2.data);
}


// Overloaded node comparison operator
template <typename T>
bool operator> (const typename BST<T>::BinNode &node1,
				const typename BST<T>::BinNode &node2)
{
  return (node1.data > node2.data);
}

// Overloaded node comparison operator
template <typename T>
bool operator== (const typename BST<T>::BinNode &node1,
				 const typename BST<T>::BinNode &node2)
{
  return (node1.data == node2.data);
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
       the proper location. 
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
	  if( (newNode > currentNode) && (currentNode->right == 0))
		{
		  currentNode->right = newNode;
		  finished = true;
		}
	  //add to empty left
	  else if( (newNode <= currentNode) && (currentNode->left == 0))
		{
		  currentNode->left = newNode;
		  finished = true;
		}

	  //go left
	  else if( newNode < currentNode)
		currentNode = currentNode->left;

	  //go right
	  else if(newNode > currentNode)
		currentNOde = currentNode->right;

	  //duplicate value
	  else{
		newNode->left = currentNode->left;
		currentNode->left = newNode;
		finished = true;
	  }
	}
  }
}
/*
  Removes the given item from the tree. Non recursive.
  Pre:Tree exists
  Post:Item is removed from tree, if present.

  TODO:FIND OUT IF SINGLE OR MULTIPLE REMOVE REQUIRED
*/
template <typename T>
void BST<T>::remove(const T& item){

  //can't remove from empty tree
  if ( empty() ){
	cerr << "Can't remove from empty tree." << endl;
	return;
  }
  
  BinNodePointer currentNode = myRoot;

  // ***Removing Root Node ***
  // root will be replaced by next highest value
  if(myRoot->data == item){

	//root was highest value in tree
	if(myRoot->right == 0){
	  myRoot = myRoot->left;
	  delete currentNode;
	}

	//root->right is next highest value in tree
	else if(myRoot->right->left == 0){
	  currentNode = myRoot->right;
	  currentNode->left = myRoot->left;
	  delete myRoot;
	  myRoot = currentNode;
	}
	
	//some other value is next largest
	else{
	  
	  //find next largest value in tree that is not root.
	  currentNode = myRoot->right;
	  BinNodePointer previousNode = myRoot;
	  
	  while(currentNode->left != 0){
		previousNode = currentNode;
		currentNode = currentNode->left;
	  }

	  //move next largest value to root, delete original root
	  currentNode->left  = myRoot->left;
	  currentNode->right = myRoot->right;
	  previousNode->left = 0;
	  delete myRoot;
	  myRoot = currentNode;
	}
  }

  
  //***Removing Non-root Node***

  //find node to be removed
  BinNodePointer previousNode = myRoot;
  bool lastMove = false; //false = left, true = right
  
  while( (currentNode->data != item) && (currentNode != 0) ){
	if(item > currentNode->data){
	  previousNode = currentNode;
	  currentNode = currentNode->right;
	  lastMove = true;
	}
	else{
	  previousNode = currentNode;
	  currentNode = currentNode->left;
	  lastMove = false;
	}
  }

  //item was not in tree
  if(currentNode == 0)
	return;

  //item was in tree; remove it

  //TODO: remove non-root node once found
  /*possibly re-use root removal algo, refactor so it works the
	same for root or non-root removal. Probably necessary because
	the non-root removal still requires that the next highest
	value replaces the removed node (for cases where non-root
	node has children) */

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
void BST<T>::recursivePreorder(ostream& out){}

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

