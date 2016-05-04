/* CPSC 2430
   This is the Linked List Implementation of Stacks
*/


using namespace std;

#include "Stack.h"


//--- Definition of Stack constructor
Stack::Stack()
  : myTop(0)
{}

//--- Definition of Stack copy constructor
Stack::Stack(const Stack & original)
{
  //copy top node
  myTop = new Stack::Node( original.top(), 0 );

  NodePointer originalPointer = original.myTop->next;
  NodePointer newPointer = myTop;

  // copy rest of stack
  while(originalPointer != 0){
	newPointer ->next = new Stack::Node(originalPointer->data, 0);
	newPointer = newPointer->next;
	originalPointer = originalPointer->next;
  }
}

//--- Definition of Stack destructor
Stack::~Stack()
{
  cout << "destructing a stack" << endl;
  Stack::NodePointer ptr = myTop;
  while ( !empty() ){
	cout << "deleting " << myTop->data << endl;
	ptr = myTop -> next;
	delete myTop;
	myTop = ptr;
  }

  cout << "stack deleted" << endl;
}


//--- Definition of assignment operator
Stack & Stack::operator=(const Stack & original)
{
  //prevent self-assignment
  if (this->myTop != original.myTop ) {

	//delete current stack
	Stack::NodePointer ptr = myTop;
	while ( !empty() ){
	  cout << "deleting " << myTop->data << endl;
	  ptr = myTop -> next;
	  delete myTop;
	  myTop = ptr;
	}
	
	//copy top node
	myTop = new Stack::Node( original.top(), 0 );

	NodePointer originalPointer = original.myTop->next;
	NodePointer newPointer = myTop;

	// copy rest of stack
	while(originalPointer != 0){
	  newPointer ->next = new Stack::Node(originalPointer->data, 0);
	  newPointer = newPointer->next;
	  originalPointer = originalPointer->next;
	}
  }
  return *this;
}

//--- Definition of empty()
bool Stack::empty() const
{
  return (myTop == 0);
}

//--- Definition of push()
void Stack::push(const StackElement & value)
{
  
	myTop = new Stack::Node(value, myTop);
}

//--- Definition of display()
void Stack::display(ostream & out) const
{
  Stack::NodePointer ptr;
  for (ptr = myTop; ptr != 0; ptr = ptr->next)
	out << ptr->data << endl;
}

//--- Definition of top()
StackElement Stack::top() const
{
  if (!empty())
	return (myTop->data);
  else
	{
	  cerr << "*** Stack is empty "
		" -- returning garbage ***\n";
	  return *(new StackElement);   // "Garbage" value
	}
}

//--- Definition of pop()
void Stack::pop()
{
  if (!empty())
	{
	  Stack::NodePointer ptr = myTop;
	  myTop = myTop->next;
	  delete ptr;
	}
  else
	cerr << "*** Stack is empty -- can't remove a value ***\n";
} 
