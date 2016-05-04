#include "Browser.h"
#include <iostream>

using namespace std;

Browser::Browser()
{
  rows = 800;
  columns = 600;
}

// set new browser size
void Browser::resize(int row, int col)
{
  rows = row;
  columns = col;
}

// display the current size of the browser as Rows x Columns
void Browser::displaySize()
{
  cout << "Current Size : " << getRows() << " x " << getCols() << "\n";
}

int Browser::getRows()
{
  return rows;
}

int Browser::getCols()
{
  return columns;
}
