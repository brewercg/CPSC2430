/*
  Cody Brewer
  5/2/2016
  PA3 v0.1
*/

#include "BST.h"
#include <iostream>
#include <random>

using namespace std;

//helper functions to display isEmpty results
void testEmpty( BST<int> &tree);
void testEmpty (BST<string> &tree);

/*
  Test program for the BST class and its
  associated methods. 
 */
int main(){

  //random number generator
  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<> dis(1,99);

  
  //generate random numbers to add to intTree
  // ***multiple insert() testing***
  int testInts[20];
  for(int i = 0; i <20; i++){
	testInts[i] =  dis(gen);
  }
  
  // ***CONSTRUCTOR TEST***
  cout << endl << "Making int tree..." << endl;
  BST<int> intTree = BST<int>();

  cout << "Making string tree..." << endl;
  BST<string> strTree = BST<string>();
  cout << endl;
  
  // ***ISEMPTY(empty)TEST***
  cout << "Testing empty" << endl;
  cout << "int";
  testEmpty(intTree);
  cout << "str";
  testEmpty(strTree);
  cout << endl;

  // ***Empty traversal tests***
  cout << "Empty traversal tests"
	   << endl
	   << "---------------------" << endl;
  strTree.recursivePreorder(cout);
  cout << endl;
  
  // ***empty height test***
  cout << "Testing empty height" << endl;
  cout << "strTree height = " << strTree.height()
	   << endl << endl;

  // ***empty search test***
  cout << "Testing empty search" << endl;
  cout << "Found " << testInts[1] << "?";
  if(intTree.search(testInts[1]))
	cout << " true";
  else
	cout << " false";
  cout << endl << endl;

  // ***empty level tests***
  cout << "Testing empty levels" << endl;
  cout << testInts[3] << " | ";
  cout << intTree.recursiveLevel(testInts[3]) << " | "
	   << intTree.nonrecursiveLevel(testInts[3])
	   << endl << endl;
  
  // ***insert() test***
  cout << "Inserting \"Test\" into strTree" << endl;
  string testStr = "Test";
  strTree.insert(testStr);
  cout << endl;

  // single-level height test
  cout << "Testing single-level height" << endl;
  cout << "strTree height = " << strTree.height()
	   << endl << endl;
    
  // ***isEmpty (non-empty) test***
  cout << "Testing non-empty" << endl;
  cout << "str";
  testEmpty(strTree);
  cout << endl;

  // ***Templating behavior has been verified,
  // proceeding with tests on intTree only.

  
  // ***multiple insert test***
  cout << "Inserting ";
  intTree.insert(testInts[0]);
  cout << testInts[0];

  for(int i = 1; i < 20; i++){
	cout << ", " <<  testInts[i];
	intTree.insert(testInts[i]);
  }
  cout << endl << endl;

  // ***Non-empty traversal tests***
  cout << "Non-empty traversal tests"
	   << endl
	   << "---------------------" << endl;
  cout << "     Recursive Preorder: ";
  intTree.recursivePreorder(cout);

  cout << " Non-recursive Preorder:";
  intTree.nonrecursivePreorder(cout);

  cout << "Non-recursive Postorder: ";
  intTree.postorder(cout);

  cout << "          Top-to-Bottom: ";
  intTree.levelTraversal(cout);
  cout << endl;

  // multi-level height test
  cout << "Testing multi-level height" << endl;
  cout << "intTree height = " << intTree.height()
	   << endl << endl;
  
  // ***isEmpty (multiple values) test***
  cout << "Testing non-empty" << endl;
  cout << "int";
  testEmpty(intTree);
  cout << endl;

  // ***search tests***
  cout << "Testing search (value present)" << endl;
  cout << "Found " << testInts[1] << "?";

  if(intTree.search(testInts[1]))
	cout << " true";
  else
	cout << " false";
  cout << endl;

  cout << "Testing search (value not present)" << endl;
  cout << "Found " << 1000 << "?";
  if(intTree.search(1000))
	cout << " true";
  else
	cout << " false";
  cout << endl << endl;

  // ***level tests***
  //values are present
  cout << "Level testing" << endl;
  cout << "Value | recursive | non-recursive" << endl;
  cout << "---------------------------------" << endl;
  
  for(int i = 0; i < 20; i+=3){
	cout << testInts[i] << "    |     ";
	cout << intTree.recursiveLevel(testInts[i]) << "     |     "
		 << intTree.nonrecursiveLevel(testInts[i]) << endl;
  }
  //value not present
  cout << "1000  |     "
	   << intTree.recursiveLevel(1000) << "    |     "
	   << intTree.nonrecursiveLevel(1000);
  cout << endl << endl;
  
  // **remove not found test**
  cout << "Attempting remove of value that isn't in tree" << endl;
  intTree.remove(1000);
  cout << endl;
  
  // **multiple remove test***
  cout << "Removing ";
  intTree.remove(testInts[0]);
  cout << testInts[0];
  
  for(int i = 1; i < 20; i++){
	cout << ", " << testInts[i];
	intTree.remove(testInts[i]);
  }
  cout << endl << endl;

  // **remove while empty test**
  cout << "Attempting remove from empty tree" << endl;
  intTree.remove(20);
  cout << endl;

  // ***isEmpty (non-empty -> empty) test***
  cout << "Testing empty after removal" << endl;
  cout << "int";
  testEmpty(intTree);
  cout << endl;
  
  return 1;
}

void testEmpty(BST<int> &tree){
  cout << "Tree empty? " ;
  if(tree.empty())
	cout << "true";
  else
	cout << "false";
  cout << endl;
}

void testEmpty(BST<string> &tree){
  cout << "Tree empty? " ;
  if(tree.empty())
	cout << "true";
  else
	cout << "false";
  cout << endl;
}
