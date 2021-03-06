#include "queue.h"
#include <iostream>
#include <unistd.h>

string passFail(bool test){
  if(test)
   	return "\033[32;40m PASS \033[0m";
  return "\033[31;40m FAIL \033[0m";
}

int main(){
  Queue q = Queue();
  bool test = false;

  cout << endl << "***QUEUE TESTING***" << endl;
  //***EMPTY QUEUE***//
  cout << endl;
  // case: isEmpty on empty queue
  test = (q.isEmpty() == true);
  cout << "isEmpty, empty|  " << passFail(test) << endl;

  // case: dequeue on empty queue
  test = (q.dequeue() == "");
  cout << "dequeue, empty| " << passFail(test) << endl;

  // case: printQueue on empty queue
  cout << "printQueue, empty| returned: ";
  q.printQueue();

  // case: copy constructor on empty queue
  Queue p = q;
  test = (p.front() == 0);
  cout << "copy constructor, empty| " << passFail(test) << endl;

  // case: enqueue on copied queue
  test = (p.enqueue(222, "copytest") == 0);
  cout << "enqueue on copy, empty| " << passFail(test) << endl;

  // case: overloaded assigment on empty queue
  q = p;
  test = (p.front()) != (q.front());
  cout << "assignment operator, empty| " << passFail(test) << endl;

  //***SINGLE JOB QUEUE***//
  cout << endl;
  
  // case: enqueue on single-element queue
  test = (q.enqueue(1234, "testfile") == 0);
  cout << "enqueue, single| " << passFail(test) << endl;

  // case: isEmpty on single-element queue
  test = (q.isEmpty() == false);
  cout << "isEmpty, single| "  << passFail(test) << endl;

  // case: dequeue on single-element queue
  test = (q.dequeue() == "testfile");
  cout << "dequeue, single| " << passFail(test) << endl;

  //***MULTI-JOB QUEUE***//
  cout << endl;

  q.dequeue();
  // case: isEmpty after queue and dequeue
  test = (q.isEmpty() == true);
  cout << "isEmpty, queue/dequeue | " << passFail(test) << endl;
  
  q.enqueue(1234, "testfile ");

  // case: enqueue on non-empty queue
  q.enqueue(2345, "testfile2");
  sleep(3);
  q.enqueue(3456, "testfile3");
  q.enqueue(4567, "testfile4");
  cout << endl;
  cout << "printQueue| 4 jobs expected: " << endl;
  q.printQueue();
  cout << endl;

  // case: copy non-empty queue
  Queue x = q;
  test = (x.front() != q.front());
  cout << "copy constructor, non-empty| " << passFail(test) << endl;
  cout << "copy contains: " << endl;
  x.printQueue();

  // case: self-assignment
  cout << endl;
  x = x;
  cout << "self-assignent (q = q) performed" << endl;
  cout << "self copy contains: " << endl;
  x.printQueue();
  cout << endl;
  
  // case: assigmnemt copy non-empty queue
  p = x;
  test = (p.front() != x.front());
  cout << "overloaded assignment, non-empty| " << passFail(test) << endl;
  cout << "copy contains: " << endl;
  p.printQueue();
  cout << endl;
  
  //case: isEmpty on non-empty queue (multiple jobs)
  test = (q.isEmpty() == false);
  cout << "isEmpty, multiple| "  << passFail(test) << endl;

  //case: dequeue on non-empty queue
  test = (q.dequeue() == "testfile4");
  cout << "dequeue, multiple| " << passFail(test) << endl;

  cout << endl << "emptying queue..." << endl;
  for(int i = 0; i < 4; ++i)
	q.dequeue();


  //***FULL QUEUE***//
  cout << endl << "filling queue..." << endl;
  //fill queue for next test case, arbitrary userID's
  for(int i = 0; i < 10000; ++i)
	q.enqueue(11000 - i, "testfiles");

  //differentiate last file added before full
  q.enqueue(2, "lastFile");

  //case: enqueue on full queue
  test = (q.enqueue(42, "fulltest") == -1);
  cout << "enqueue, full| " << passFail(test) << endl;

  //case: dequeue on full queue
  test = (q.dequeue() == "lastFile");
  cout << "dequeue, full| " << passFail(test) << endl;

  cout << endl << "emptying queue..." << endl;
  for(int i = 0; i < 10000; ++i)
	q.dequeue();

  //case: isEmpty on fully cycled queue
  test = (q.isEmpty() == true);
  cout << "isEmpty, full cycle| " << passFail(test) << endl;

  //case: deconstructor on empty queue
  cout << endl << "deconstructing an empty queue..." << endl;
  q.~Queue();
  cout << "queue destroyed" << endl;

  //case: deconstructor on non-empty queue
    q = Queue();
  q.enqueue(123, "file");
  cout << "deconstructing a non-empty queue..." << endl;
  q.~Queue();
  cout << "queue destroyed" << endl;

  cout << "***END TEST***" << endl;
  
  return 1;
}
