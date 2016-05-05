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

  /*
  //generate random numbers to add to intTree
  // ***multiple insert() testing***
  int testInts[20];
  for(int i = 0; i <20; i++){
	testInts[i] =  dis(gen);
  }
  */

  int testInts[20] = {193,3,77,50,14,79,77,89,78,176,166,155,156,86,32,124,126,96,9,176};
  
  // ***CONSTRUCTOR TEST***
  cout << "Making int tree..." << endl;
  BST<int> intTree = BST<int>();

  cout << "Making string tree..." << endl;
  BST<string> strTree = BST<string>();


  // ***ISEMPTY(empty)TEST***
  cout << "int";
  testEmpty(intTree);
  cout << "str";
  testEmpty(strTree);

  
  // ***insert() test***
  string testStr = "Testing1";
  strTree.insert(testStr);

  // ***isEmpty (non-empty) test***
  cout << "str";
  testEmpty(strTree);


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
  cout << "int";
  testEmpty(intTree);
  
  // **multiple remove test***
  cout << "Removing " << endl;
  intTree.remove(testInts[0]);
  cout << testInts[0];
  
  for(int i = 1; i < 21; i++){
	cout << ", " << endl << testInts[i];
	intTree.remove(testInts[i]);
  }
  cout << endl;

  // ***isEmpty (non-empty -> empty) test***
  cout << "int";
  testEmpty(intTree);
  
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
