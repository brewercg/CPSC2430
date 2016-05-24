/*
  Cody Brewer
  CPSC 2430
  5/16/16
  v 0.1
*/

#include "Heash.h"
#include <iostream>

using namespace std;

/*
  Test client for Heash data structure
*/

int main(){
  cout << "Heash h = Heash()" << endl << endl;
  Heash h = Heash();

  cout << "***Empty Heash Tests***" << endl;
  //Test:find       Case: empty
  cout << "h.find(10): ";
  cout <<  h.find(10) << endl;
 
  //Test:remove     Case: empty
  cout << "h.remove(10): ";
  cout <<  h.remove(10) << endl;

  //Test:deleteMin  Case: empty
  cout << "h.deleteMin(): ";
  cout <<  h.deleteMin() << endl;

  //Test:print      Case: empty
  cout << "h.print(): ";
  h.print();

  //Test:insert     Case: empty
  cout << "h.insert(10): ";
  cout <<  h.insert(10) << endl << endl;

  cout << "***Non-Empty Tests***" << endl;

  //Test:insert     Case: duplicate
  cout << "h.insert(10): ";
  cout <<  h.insert(10) << endl;
  
  //Test:insert     Case: non-duplicate
  cout << "h.insert(15): ";
  cout <<  h.insert(15) << endl;
  cout << "h.insert(32): ";
  cout <<  h.insert(32) << endl;
  cout << "h.insert(11): ";
  cout <<  h.insert(11) << endl;
  cout << "h.insert(23): ";
  cout <<  h.insert(23) << endl;
  cout << "h.insert(1): ";
  cout <<  h.insert(1) << endl;
		
  //Test:print      Case: non-empty
  cout << "h.print(): ";
  h.print();
  
  //Test:find       Case: found
  cout << "h.find(10): ";
  cout <<  h.find(10) << endl;

  //Test:find       Case: not found
  cout << "h.find(20): ";
  cout <<  h.find(20) << endl;

  //Test:remove     Case: not found
  cout << "h.remove(20): ";
  cout <<  h.remove(20) << endl;

  //Test:remove     Case: found
  cout << "h.remove(15): ";
  cout <<  h.remove(15) << endl;

  //Test:deleteMin  Case: non-empty
  cout << "h.deleteMin(): ";
  cout <<  h.deleteMin() << " | Expected: 1" << endl;

  //Test:print      Case: after add/remove operations
  cout << "h.print(): ";
  h.print();

  //Deleteing minimum until Heash contains a single value
  cout << "h.deleteMin(): ";
  cout <<  h.deleteMin() << " | Expected: 10" << endl;
  cout << "h.deleteMin(): ";
  cout <<  h.deleteMin() << " | Expected: 11" << endl;
  cout << "h.deleteMin(): ";
  cout <<  h.deleteMin() << " | Expected: 23" << endl;

  cout << "h.print(): ";
  h.print();
	
  //Test:deleteMin  Case: single value
  cout << "h.deleteMin(): ";
  cout <<  h.deleteMin() << " | Expected: 32" << endl;

  //Added to test remove function
  cout << "h.insert(30): ";
  cout <<  h.insert(30) << endl;

  //Test:remove     Case: single value
  cout << "h.remove(30): ";
  cout <<  h.remove(30) << endl << endl;

  
  cout << "***Re-Hash Test***" << endl;

  //add values to fill to just under 70% full
  //70% full is 14 values, given default capacity of 20
  for(int i = 1; i < 14 ; ++i ){
	h.insert(i);
  }

  //heash now contains 13 values

  cout << "Before Re-Hash: ";
  h.print();

  cout << "h.insert(15)" << "h.insert(16)" << endl;

  h.insert(15);
  h.insert(16);

  //heash now contains 15 values

  cout << "After Re-Hash: ";
  h.print();

  cout << "***End Heash Testing***" << endl;
  
  return 1;
}
