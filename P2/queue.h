#include <stdio.h>
#include <time.h>
#include <string>

using namespace std;

typedef unsigned int uint;

class Queue{
 private:

  class Job{
  public:
	Job(int job, uint user, string file,
		time_t tm);
	int jobID;
	uint userID;
	string fileName;
	time_t submitTime;
	Job* next;
  };
  
  Job* last;
  int nextID;
  
 public:
  Queue();
  Queue(const Queue &orig);
  ~Queue();
  const Queue& operator=(const Queue& orig);
  bool isEmpty();
  int enqueue(uint userID, string fileName);
  string dequeue();
  void printQueue();
  Job* front();

};
