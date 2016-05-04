/*
  Cody Brewer
  5/2/2016
  Lab5 v1
*/

#include "BST.h"
#include <iostream>

using namespace std;

/*
  Creates two BST objects using the
  default constructor. Calls isEmpty()
  on both, prints results to console.
  Expected that both will be empty. 
 */
int main(){

  cout << "Making int tree..." << endl;
  BST<int> intTree = BST<int>();

  cout << "Making string tree..." << endl;
  BST<string> strTree = BST<string>();

  cout << "intTree empty? " ;
  if(intTree.isEmpty())
	cout << "true";
  else
	cout << "false";
  cout << endl;
	
  cout << "strTree empty? ";
  if(strTree.isEmpty())
	cout << "true";
  else
	cout << "false";
  cout << endl;
  
  return 1;
}
