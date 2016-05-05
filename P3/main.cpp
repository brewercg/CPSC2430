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
  uniform_int_distribution<> dis(1,200);

  
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
  
  // ***insert() test***
  cout << "Inserting \"Test\" into strTree" << endl;
  string testStr = "Test";
  strTree.insert(testStr);
  cout << endl;

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
  cout << endl;

  // ***isEmpty (multiple values) test***
  cout << "Testing non-empty" << endl;
  cout << "int";
  testEmpty(intTree);
  cout << endl;

  // **remove not found test
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
