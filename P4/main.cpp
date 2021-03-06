/*
  Cody Brewer
  CPSC 2430
  5/25/16
  v 1.0
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
  cout << "h.print(): " << endl;
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
  cout << "h.print(): " << endl;
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

  //Test:print      Case: after add/remove operations
  cout << "h.print(): " << endl;
  h.print();
  
  //Test:deleteMin  Case: non-empty
  cout << "h.deleteMin(): ";
  cout <<  h.deleteMin() << " | Expected: 1" << endl;

  //Test:print      Case: after add/remove operations
  cout << "h.print(): " << endl;
  h.print();

  //Deleteing minimum until Heash contains a single value
  cout << "h.deleteMin(): ";
  cout <<  h.deleteMin() << " | Expected: 10" << endl;
  cout << "h.deleteMin(): ";
  cout <<  h.deleteMin() << " | Expected: 11" << endl;
  cout << "h.deleteMin(): ";
  cout <<  h.deleteMin() << " | Expected: 23" << endl;

  cout << "h.print(): " << endl;
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

  
  cout << "***Re-Hash Test***" << endl << endl;
	
  //add pseudo-random values to fill to just under 70% full
  cout << "Adding values for reHash test...";
  for(int i = 1; i < 16 ; ++i ){
	h.insert(13*i + 7);
  }
  cout << " done. " << endl;
  

  cout << "Before Re-Hash: " << endl;

  /*cout << "fullness = size / capacity = "
	<< float(size) / float(capacity) << endl;*/
  h.print();

  //add single value to trigger re-hash
  cout << "h.insert(50); " << endl;
  h.insert(50);
  
  //rehash should have triggered
  cout << "After Re-Hash: " << endl;
  h.print();

  /*cout << "fullness = size / capacity = "
	   << float(size) / float(capacity) << endl;
  */
  
  cout << "***End Heash Testing***" << endl;
  
  return 1;
}
