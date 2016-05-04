/*
  Cody Brewer
  5/2/2016
  PA3 v0.1
*/

#include "BST.h"
#include <iostream>

using namespace std;

/*
  Test program for the BST class and its
  associated methods. 
 */
int main(){

  cout << "Making int tree..." << endl;
  BST<int> intTree = BST<int>();

  cout << "Making string tree..." << endl;
  BST<string> strTree = BST<string>();

  cout << "intTree empty? " ;
  if(intTree.empty())
	cout << "true";
  else
	cout << "false";
  cout << endl;
	
  cout << "strTree empty? ";
  if(strTree.empty())
	cout << "true";
  else
	cout << "false";
  cout << endl;
  
  return 1;
}
