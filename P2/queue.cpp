#include "queue.h"
#include <iostream>

Queue::Queue(){
  nextID = 0;
  last = 0;
}


Queue::~Queue(){
  //queue already empty
  if(last == 0)
	return;
  
  Job* ptr;

  while (ptr != last){
	ptr = last->next;
	last->next = last->next->next;
	delete ptr;
  }
  delete last;
}

/*
  Job constructor
 */
Queue::Job::Job(int job, uint user, string file,
				time_t tm)
{
  jobID = job;
  userID = user;
  fileName = file;
  submitTime = tm;
  next = NULL;
}

/*
Copy constructor
*/
Queue::Queue(const Queue &orig){
  nextID = orig.nextID;
  
  if(orig.last == 0){
	last = 0;
	return;
  }
  
  Job* newPtr;
  Job* oldPtr = orig.last;

  //copy last Job
  newPtr = new Job(oldPtr->jobID, oldPtr->userID, oldPtr->fileName, oldPtr->submitTime);

  last = newPtr;

  oldPtr = oldPtr->next;
  while(oldPtr != orig.last){
	//copy jobs
	newPtr->next = new Job(oldPtr->jobID, oldPtr->userID, oldPtr->fileName, oldPtr->submitTime);
	oldPtr = oldPtr->next;
	newPtr = newPtr->next;
  }

  newPtr->next = last;
}

/*
Overloaded assignment operator
*/ 
const Queue& Queue::operator=(const Queue& orig){
  //check for self-copy
  if(this == &orig)
	return *this;

  //check for newly-initialied queue
  if(orig.last == 0){
	last = 0;
	nextID = 0;
	return *this;
  }

  //non-empty, non-self assignment
  if(!isEmpty()){
	// clear LHS queue before copying
	Job* ptr;
	while (ptr != last){
	  ptr = last->next;
	  last->next = last->next->next;
	  delete ptr;
	}
  }
  
  //deep copy RHS to LHS
  Job* newPtr;
  Job* oldPtr = orig.last;

  //copy last Job
  newPtr = new Job(oldPtr->jobID, oldPtr->userID, oldPtr->fileName, oldPtr->submitTime);

  last = newPtr;

  oldPtr = oldPtr->next;
  while(oldPtr != orig.last){
	//copy jobs
	newPtr->next = new Job(oldPtr->jobID, oldPtr->userID, oldPtr->fileName, oldPtr->submitTime);
	oldPtr = oldPtr->next;
	newPtr = newPtr->next;
  }
  newPtr->next = last;

  return *this;
}

/*
  Returns 1 if the queue is empty, else returns 0

  Pre: Queue instantiated
  Post: value returned
*/
bool Queue::isEmpty(){
  return last == 0;
}

/*
  This function is responsible for adding new jobs
  to the end of the queue and assigning them a
  submission time and jobID.

  Pre: Queue instantiated
  Post: Job added to queue if not full, jobID returned.
        Returns -1 if queue is full.
*/
int Queue::enqueue(uint userID, string fileName){

  if(nextID == 10000){
	cerr << "Cannot enqueue, queue is full." << endl;
	return -1;
  }
  
  time_t subTime = time(NULL);

  Job *j = new Job(nextID++, userID, fileName, subTime);

  if(isEmpty()){
	last = j;
    j->next = j;
	return j->jobID;
  }

  j->next = last->next;
  last->next = j;

  return j->jobID;
}


/*
  This function is responsible for removing the
  first-in-line job from the queue.

  Pre: Queue contains at least one job
  Post: The job at the front of the queue
        is removed, and its fileName returned
*/
string Queue::dequeue(){
  //empty queue
  if ( isEmpty() ){
	cerr << "Cannot dequeue, queue is empty." << endl;
	return "";
  }

  //single-job queue
  if( last->next == last){
    string fName = last->fileName;
	delete last;
	last = 0;
	--nextID;
	return fName;
  }

  //multi-job queue
  Job* first = last->next;
  string fName = first->fileName;

  last->next = first->next;
  delete first;
  --nextID;
  return fName;
}


/*
  This function displays the contents of the
  queue

  Pre: Queue instantiated
  Post: userID and fileName of each job is
        printed to screen in queue order
*/
void Queue::printQueue(){

  if( isEmpty() ){
	cout << "Queue is empty" << endl;
	return;
  }
  
  Job* ptr = last->next;

  string localTime = "";
  
  while(ptr != last){
	localTime = asctime(localtime(&ptr->submitTime));
	
	cout << "FileName: " << ptr->fileName
		 <<" | UserID: " << ptr->userID
		 <<" | Time: "   << localTime;

	ptr = ptr->next;
	
  }

  //print last job
  cout << "FileName: " << ptr->fileName
	   << " | UserID: " << ptr->userID
	   << " | Time: "
	   << asctime(localtime(&ptr->submitTime));
}

/*
  This method returns the job at the front of the queue

  Pre: Queue instantiated
  Post: returns first job in line, or NULL if queue is empty
*/
Queue::Job* Queue::front(){
  if(last == 0)
	return NULL;
  
  return last->next;
}
