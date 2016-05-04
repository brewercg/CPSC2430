#include <iostream>
#include <ctime>

using namespace std;

void foo(int n, int val){

  int b,c;

  for( int j=4; j<n; j++){
	for(int i=0; i<j; i++){
	  b = b * val;
	  
	  for(int k=0; k<n; ++k)
		c = b+c;
	}
  }
}


int main(){

  /*
	Outer loop (j) : executes n-4 times
	Middle loop (i): worst case executes (n-4)*(n-1) times
	Inner loop (k) : worst case executes n*(n-4)*(n-1) times

	Bottleneck in k: executes n^3 - 5n^2 + 4n times

	=> foo() is O(n^3)

  */
  clock_t startTime, endTime;
  int val;
  
  cout << "Enter a value: ";
  cin >> val;
  cout << endl;

  startTime = time(NULL);
  foo(100, val);
  endTime = time(NULL);

  cout << "n = 100, val = " << val
	   << ", elapsed time (sec) = "
	   << difftime(endTime, startTime) << endl;
  
  startTime = time(NULL);
  foo( 300, val);
  endTime = time(NULL);
  
  cout << "n = 300, val = " << val
	   << ", elapsed time (sec) = "
	   << difftime(endTime,startTime) << endl;

  startTime = time(NULL);
  foo( 700, val);
  endTime = time(NULL);
  
  cout << "n = 700, val = " << val
	   << ", elapsed time (sec) = "
	   << difftime( endTime, startTime) << endl;

  startTime = time(NULL);
  foo( 1000, val);
  endTime = time(NULL);
  
  cout << "n = 1000, val = " << val
	   << ", elapsed time (sec) = "
	   << difftime( endTime, startTime) << endl;

  startTime = time(NULL);
  foo( 2000, val);
  endTime = time(NULL);
  
  cout << "n = 2000, val = " << val
	   << ", elapsed time (sec) = "
	   << difftime( endTime, startTime) << endl;

  startTime = time(NULL);
  foo( 2200, val);
  endTime = time(NULL);
  
  cout << "n = 2200, val = " << val
	   << ", elapsed time (sec) = "
	   << difftime( endTime, startTime) << endl;

  
  startTime = time(NULL);
  foo( 2500, val);
  endTime = time(NULL);
  
  cout << "n = 2500, val = " << val
	   << ", elapsed time (sec) = "
	   << difftime( endTime, startTime) << endl;
  
  return 1;
}
