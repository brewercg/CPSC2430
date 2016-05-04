#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(){
  string fName;
  fstream inFile, outFile;
  char nextChar;
  int sentences = 0;
  
  cout << "Enter a filename: " << endl;
  cin >> fName;
  
  inFile.open(fName.c_str(), ifstream::in);
  outFile.open("stats.txt",ofstream::out | ofstream::app); //append, not overwrite

  if( !inFile.is_open() || !outFile.is_open() ) {
	cout << "Error: Could not open file!" << endl;
	return 1;
  }

  cout << "***File Contents***" << endl << endl;
  nextChar = inFile.get();
  while(inFile.good()){

	if(nextChar == '.' ||
	   nextChar == '?' ||
	   nextChar == '!' )
	  { ++sentences; }

	cout << nextChar; //copy char to screen
	nextChar = inFile.get(); //get next char in input file
  }


  cout << " Number of Sentences: " << sentences << endl;
  
  outFile << "File Name: " << fName << " Number of Sentences: " << sentences << endl;

  outFile.close();
  inFile.close();
  
  return 0;
}
