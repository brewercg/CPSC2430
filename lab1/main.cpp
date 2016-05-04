#include "Browser.h"
#include <iostream>

using namespace std;

int main()
{
  Browser browser = Browser();

  browser.displaySize();
  
  int newRows;
  int newCols;

  cout << "Enter new # of rows: ";
  cin >> newRows;
  cout << "Enter new # of columns: ";
  cin >> newCols;

  browser.resize(newRows, newCols);

  browser.displaySize();
  
  return 0;
  
}
