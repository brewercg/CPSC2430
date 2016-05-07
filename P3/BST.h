/*
  Cody Brewer
  5/6/2016
  PA3 v1.0
*/
#include <iostream>
#include <stack>

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

  //recursive helper functions
  void copyHelper(BinNodePtr origRoot, BinNodePtr copyRoot);
  bool searchHelper(BinNodePtr root, const T& item);
  int recursiveLvlHelper(BinNodePtr root, const T& item);
  int heightHelper(BinNodePtr root);
  void recPreHelper(BinNodePtr root, ostream& out);
}; //END BST CLASS DEFINITION



// Overloaded output operator
template <typename T>
ostream& operator<< (ostream &out,  BST<T> &tree){
  tree.levelTraversal(out);
  return out;
}

/*
  Copy Constructor
  Pre: A tree exists to be copied
  Post: A deep copy of the tree is created
*/
template<typename T>
BST<T>::BST(const BST& orig){

  //copying an empty tree
  if(orig.myRoot == 0){
	myRoot = 0;
	return;
  }

  //copy root
  myRoot = new BinNode(orig.myRoot->data);

  //copy rest of tree
  copyHelper(orig.myRoot, myRoot);
  
}

template<typename T>
void BST<T>::copyHelper(BinNodePtr origRoot, BinNodePtr copyRoot){
  //copy left subtree
  if(origRoot->left != 0){
	copyRoot->left = new BinNode(origRoot->left->data);
	copyHelper(origRoot->left, copyRoot->left);
  }

  //copy right subtree
  if(origRoot->right != 0){
	copyRoot->right = new BinNode(origRoot->right->data);
	copyHelper(origRoot->right, copyRoot->right);
  }
  
}

/*
  Destructor
  Pre: Tree exists
  Post: Tree is deconstructed, memory freed
*/
template<typename T>
BST<T>::~BST<T>(){
  while(!empty()){
	remove(myRoot->data);
  }
}

/*
  Overloaded Assignment Operator
  Pre: LHS and RHS trees exist
  Post: LHS is a deep copy of the RHS tree. LHS is returned after copying.
 */
template<typename T>
BST<T>& BST<T>::operator=(const BST& orig){

  //prevent self-assignment
  if(myRoot == orig.myRoot)
	return *this;
  
  //clear LHS tree before copying
  while(!empty()){
	remove(myRoot->data);
  }
  
  //copy root
  myRoot = new BinNode(orig.myRoot->data);

  //copy rest of tree
  copyHelper(orig.myRoot, myRoot);
  
  return *this;

}


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
  return searchHelper(myRoot, item);
}

/*
  Helper for search() function
*/
template <typename T>
bool BST<T>::searchHelper(BinNodePtr root, const T& item){

  if(root == NULL)
	return false;
  if(root->data == item)
	return true;
  else if(item > root->data)
	return searchHelper(root->right, item);
  else if(item < root->data)
	return searchHelper(root->left , item);
  
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
  If the removed item was not a leaf, it is replaced by
  the next highest value item in the tree. 

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
	if(currentNode == myRoot)
	  myRoot = 0;

	//set appropriate parent link to 0
	else if(lastMoveRight)
	  previousNode->right = 0;
	else
	  previousNode->left = 0;

	//remove item
	delete currentNode;
  }

  //case: currentNode has right child only
  else if(currentNode->left == 0){

	//handle removing root node
	if(currentNode == myRoot)
	  myRoot = myRoot->right;

	//redirect appropriate parent link
	else if(lastMoveRight)
	  previousNode->right = currentNode->right;
	else
	  previousNode->left = currentNode->right;

	//remove item
	delete currentNode;
  }

  //case: currentNode has left child only
  else if(currentNode->right == 0){

	//handle removing root node
	if(currentNode == myRoot)
	  myRoot = myRoot->left;

	//redirect appropriate parent link
	else if(lastMoveRight)
	  previousNode->right = currentNode->left;
	else
	  previousNode->left = currentNode->left;
	
	delete currentNode;
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
	if(currentNode == myRoot)
	  myRoot = nextHighest;
	
	else{
	  //redirect appropriate parent link
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

	//remove item
	delete currentNode;	
  }
}
 
/*
  Returns the level of the tree on which the given item is stored.
  Returns -1 if the item is not present in the tree. Starts with
  the myRoot node as level 0. Recursive.
  Pre:Tree exists
  Post:Item's level is returned, if present. Returns -1 otherwise
*/
template <typename T>
int BST<T>::recursiveLevel(const T& item){
  return recursiveLvlHelper(myRoot, item);
}

template <typename T>
int BST<T>::recursiveLvlHelper(BinNodePtr root, const T& item){
  if(root == NULL)
	return -1;
  if(root->data == item)
	return 0;

  else if(item > root->data){
	int right = recursiveLvlHelper(root->right, item);

	if(right == -1)
	  return -1;
	
	return right + 1;
  }
  
  else if(item < root->data){
	int left = recursiveLvlHelper(root->left, item);

	if(left == -1)
	  return -1;
  
	return left + 1;
  }
  return -1;
}

/*
  Returns the level of the tree on which the given item is stored.
  Returns -1 if the item is not present in the tree. Starts with
  the root node as level 0. Non-recursive.
  Pre:Tree exists
  Post:Item's level is returned, if present. Returns -1 otherwise
*/
template <typename T>
int BST<T>:: nonrecursiveLevel(const T& item){
  if(empty())
	return -1;

  int level = 0;//track level
  BinNodePtr currentNode = myRoot;//traverse tree

  //search for item
  while(currentNode != 0 && currentNode->data != item){

	//look right
	if(item > currentNode->data){
	  currentNode = currentNode->right;
	  ++level;
	}

	//look left
	else{
	  currentNode = currentNode->left;
	  ++level;
	}
  }

  //item not found
  if(currentNode == 0)
	return -1;

  //item found
  return level;
}

/*
  Traverses the tree top-to-bottom, left-to-right, beginning at
  the root. Streams contents to given ostream. Non-recursive.
  Pre:Tree exists
  Post:Contents of tree are sent to streaming output.
*/
template <typename T>
void BST<T>::levelTraversal(ostream& out){

  
  if(empty()){
	out << "Empty Tree" << endl;
	return;
  }
  

  BinNodePtr currentNode = myRoot;
  stack<BinNodePtr> currentLevel, nextLevel;
  
  currentLevel.push(myRoot);

  //go until tree is fully traversed
  while( !currentLevel.empty() ){
	//get child nodes of all current-level nodes
	while( !currentLevel.empty() ){
	  currentNode = currentLevel.top();

	  //display current level value
	  out << currentNode->data << " ";

	  //add child nodes
	  if(currentNode->left != 0)
		nextLevel.push(currentNode->left);
	  if(currentNode->right != 0)
		nextLevel.push(currentNode->right);

	  currentLevel.pop();
	}

	//transfer nextLevel into currentLevel, reverse order
	while(!nextLevel.empty()){
	  currentLevel.push(nextLevel.top());
	  nextLevel.pop();
	}
  }
  
  out << endl;
  
} 

/*
  Recursive preorder traversal of tree. Contents are streamed
  to given output stream. 
  Pre:Tree exists
  Post:Contents of tree are streamed out in order of traversal.
*/
template <typename T>
void BST<T>::recursivePreorder(ostream& out){
  recPreHelper(myRoot, out);
  out << endl;
}

/*
  Helper for recursivePreorder()
*/
template <typename T>
void BST<T>::recPreHelper(BinNodePtr root, ostream& out){
  if(root != 0){
	out << root->data << " ";
	recPreHelper(root->left, out);
	recPreHelper(root->right, out);
  }
}


/*
  Non-recursive preorder traversal of tree. Contents are streamed
  to given output stream. 
  Pre:Tree exists
  Post:Contents of tree are streamed out in order of traversal.
  TODO:possibly use a copy and remove leaves as they're printed?
*/
template <typename T>
void BST<T>::nonrecursivePreorder(ostream& out){

  if(empty()){
	out << "Empty Tree" << endl;
	return;
  }
  
  BinNodePtr currentNode = myRoot;
  stack<BinNodePtr> nodeStack;
  nodeStack.push(myRoot);
  
  do{
	//push left and right children to stack
	if(currentNode->right != 0)
	  nodeStack.push(currentNode->right);
	if(currentNode->left != 0)
	  nodeStack.push(currentNode->left);

	//display current node data
	out << " " <<  currentNode->data;

	//move to next node
	currentNode = nodeStack.top();
	nodeStack.pop();
	
  }while(!nodeStack.empty());
  
  out << endl;
}

/*
  Non-recursive postorder traversal of tree. Contents are streamed
  to given output stream. 
  Pre:Tree exists
  Post:Contents of tree are streamed out as Left-Right-Parent.
*/
template <typename T>
void BST<T>::postorder(ostream& out){
  
  if(empty()){
	out << "Empty Tree" << endl;
	return;
  }
  
  BinNodePtr currentNode = myRoot;
  stack<BinNodePtr> nodeStack;
  stack<BinNodePtr> valueStack;
  
  nodeStack.push(myRoot);
  
  do{
	//push left and right children to stack
	if(currentNode->left != 0)
	  nodeStack.push(currentNode->left);
	if(currentNode->right != 0)
	  nodeStack.push(currentNode->right);
	
	//display current node data
	//	out << " " <<  currentNode->data;

	//move to next node
	valueStack.push(currentNode);
	currentNode = nodeStack.top();
	nodeStack.pop();
	
  }while(!nodeStack.empty());

  //display values in post-order
  while(!valueStack.empty()){
	out << valueStack.top()->data << " ";
	valueStack.pop();
  }
  
  out << endl;
}

/*
  Recursively determines the height of the tree. The
  height of the tree is then returned to the console. 
  Pre:Tree exists
  Post:Height of tree is returned
*/
template <typename T>
int BST<T>::height(){
  return heightHelper(myRoot);
}


/*
Helper for height
*/
template <typename T>
int BST<T>::heightHelper(BinNodePtr root){
  if(root == NULL)
	return 0;

  else if(heightHelper(root->right) > heightHelper(root->left))
	return heightHelper(root->right) + 1;

  else
	return heightHelper(root->left) + 1;
}

