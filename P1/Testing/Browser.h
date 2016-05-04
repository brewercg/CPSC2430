/*
 * CPSC 2430 - Data Structures
 * Spring 2016
 * Initial version of this file was created by Tribelhorn, Ben on 9/25/13
 *
 * Description: Programming Assignment 1 ***Complete the description of this assignment ***
 *
 * Students Name: Cody Brewer
 * Date: 4/14/2016
 */


#ifndef ____html__
#define ____html__

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

/*
  Class Description:

  A simple text-based browser that can display HTML
  documents. The browser can parse <B>, <A>, and <P>
  tags appropriately, and will ignore any other tags.
*/
class Browser
{
 public:
  Browser();

  void loadHTML(string filename);
  void display(ostream &out) const;
  void link(unsigned int linkNumber);
  void resize(unsigned int rows, unsigned int columns);
  void next();
  void previous();
  
 private:
  unsigned int numColumns, numRows, numPages, numLinks;
  unsigned int currentPage;
  string displayText, message;
  string links[50], pages[30];
  
  string parseTag(string tag);
  void parseHTML(string encodedText);
  void writePhrase(string phrase);
};

ostream& operator<<(ostream& out, const Browser &rhs);

#endif /* defined(____html__) */

