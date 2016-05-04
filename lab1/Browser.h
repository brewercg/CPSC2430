#ifndef BROWSER_H
#define BROWSER_H

class Browser
{
 private:
  int rows;
  int columns;

 public:

  Browser();

  void resize(int row, int col);
  void displaySize();
  int  getRows();
  int  getCols();
};

#endif
