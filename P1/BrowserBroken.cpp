/*
 * CPSC 2430 - Data Structures
 * Spring 2016
 * Initial version of this file was created by Tribelhorn, Ben on 9/25/13
 *
 * Description: Programming Assignment 1 ***Complete the description of this assignment ***
 *
 * Students Name: Cody Brewer
 * Date: 
 */


#include "Browser.h"


/* Default constructor
   Initializes the browser size to default values
*/

Browser::Browser()
  : numColumns(40), numRows(6), displayText("")
{
}

/*
  This function is responsible for opening an html file, reading each lines
  and passing the text along to be parsed.

  pre-conditions: file is not open, buffer is empty
  post-conditions: text is read into a buffer; file is closed

*/

void Browser::loadHTML(string filename)
{
  string str;
  string allText = "";
  ifstream infile;
  infile.open(filename.c_str());
  if( !infile.is_open() )
	{
	  cout << "ERROR Loading HTML file!\n";
	  return;
	}
  while(!infile.eof()) // To get you all the lines.
	{
	  getline(infile,str); // Saves the line in STRING.
	  allText += str + "\n";
	}
  infile.close();

  // add the current page as the 0-th link
  links[0] = filename;

  // ensure pages is initialized in case parse fails
  pages[0] = ""; 
  
  parseHTML(allText);

  displayText = pages[0];
}

/*
  This function is responsible for parsing the text.
  *** Complete the function description ***

  pre-conditions: unformatted HTML has been loaded

  post-conditions: HTML document has been formatted and
                  split into pages that are ready to display

*/


void Browser::parseHTML(string encodedText)
{
  unsigned int currentRow = 0, currentCol = 0, wordLength = 0;
  unsigned int writingPage = 0; // page currently being written to 
  unsigned int wordStart = 0, wordEnd; // used to find the next word
  string currentWord;
  
  currentPage = 0;
  numPages = 0;
  numLinks = 0;
  
  // traverse entire string
  while(wordStart < encodedText.length()){
	wordEnd = wordStart;
	currentWord = "";
	
	// find end of word, end of file, or an HTML tag
	while(encodedText[wordEnd] != ' ' &&
		  encodedText[wordEnd + 1] != '<' &&
		  encodedText[wordEnd] != '\n' &&
		  wordEnd <= encodedText.length())
	  {
		++wordEnd;
	  }

	// found the end of a word or end of file
	if(encodedText[wordEnd] == ' '  ||
	   encodedText[wordEnd] == '\n' ||
	   encodedText[wordEnd + 1] == '<' ||
	   wordEnd >= encodedText.length())
	  {
		wordLength = wordEnd - wordStart + 1;

		// get current word
		for(unsigned int currentChar = wordStart; currentChar <= wordEnd; currentChar++){
		  // don't copy extra whitespace
		  if(encodedText[currentChar] != '\n' && encodedText[currentChar] != ' '){
			//		  pages[writingPage] += encodedText[currentChar];
			currentWord += encodedText[currentChar];
		  }
		}
		currentWord += ' '; // add a space after each word
	  }

	// found an HTML tag
	else if(encodedText[wordEnd] == '<'){

	  // copy word up to beginning of tag
	  for (unsigned int currentChar = wordStart; currentChar < wordEnd; currentChar++){
		//		pages[writingPage] += encodedText[currentChar];
		currentWord += encodedText[currentChar];
	  }

	  wordStart = wordEnd;

	  // look for end of tag
	  unsigned int tagBegin = wordEnd, tagEnd = wordEnd;
	  
	  while(encodedText[tagEnd] != '>' && tagEnd <= encodedText.size() ){
		++tagEnd;
	  }

	  // reached end of document without closing tag
	  if (tagEnd > encodedText.size()) {
		// don't parse; not a proper tag
		//		pages[writingPage] += '<';
		currentWord = '<';
		++wordEnd;
		wordStart = wordEnd;
	  }
	  else{
		//parse the tag
		string tag;
		for (unsigned int currentChar = tagBegin; currentChar <= tagEnd; currentChar++){
		  tag += encodedText[currentChar];
		}
		
		string parsed = parseTag(tag);

		//		pages[writingPage] += parsed;
		currentWord = parsed;
		wordStart = ++tagEnd;
	  }
	}

	// found a duplicate space, skip it
	else if(encodedText[wordStart] == ' ' &&
			encodedText[wordEnd] == ' ')
	  {
		wordStart++;
	  }

	wordLength = currentWord.size();
	
	// word fits on current line
	if(wordLength + currentCol < numColumns){
	  //update position in current line
	  currentCol += wordLength;
	}

	// word doesn't fit on current line, but a
	// new line will fit on the current page
	else if(currentRow < numRows){
	  // add a new line and update positions
	  pages[writingPage] += '\n';
	  ++currentRow;
	  currentCol = wordLength;
	}

	// word doesn't fit on current line, and a new
	// line will not fit on the current page
	else{
	  // initialize a new page and update positions
	  pages[++writingPage] = "";	
	  currentRow = 0;
	  currentCol = wordLength;
	}

	// move to beginning of next word
	wordStart = wordEnd + 1;
  

	// write current word to current page
	pages[writingPage] += currentWord;
  }
  numPages = writingPage; 
}

/*
  This function is responsible for parsing the HTML tags.
  *** Complete the function description ***

  pre-conditions: an HTML tag has been detected

  post-conditions: the tag has been replaced with the appropriate formatting

*/

string Browser::parseTag(string tag)
{
  string parsed = "";

  // scrub whitespace and brackets
  for(unsigned int currentChar = 0; currentChar < tag.size(); ++currentChar)
	{
	  if(tag[currentChar] != ' ' &&
		 tag[currentChar] != '<' &&
		 tag[currentChar] != '>')
		{
		  parsed += tag[currentChar];
		}
	}

  string linkURL = "";
  bool inQuotes = false;
  stringstream convert;
  switch(parsed[0])
	{
	case 'p':
	  // case insensitive
	case 'P':
	  parsed = "\n\n";
	  break;
	case 'b':
	  // case insensitive
	case 'B':
	  parsed = "\n";
	  break;
	case 'a':
	  //case insensitive
	case 'A':

	  // scan for part in quotes
	  for(unsigned int currentChar = 0; currentChar < parsed.size(); ++currentChar)
		{
		  //turn off quotes before copying final ' " '
		  if( parsed[currentChar] == '"' && inQuotes )
			{
			  inQuotes = false;
			}

		  if (inQuotes)
			{
			  linkURL += parsed[currentChar];
			}

		  //turn on quotes without copying initial ' " '
		  if( parsed[currentChar] == '"' && !inQuotes )
			{
			  inQuotes = true;
			}
		}
	  // add part in quotes to links
	  links[++numLinks] = linkURL;

	  //start of link marker
	  convert << numLinks;
	  parsed = "[" + convert.str() + "]";
	  break;

	case '/':
	  //link closing tag
	  if(parsed[1] == 'a' || parsed[1] == 'A'){
		parsed = "[]";
	  }

	  //unrecognized closing tag
	  else{
		parsed = "";
	  }
	  break;
	  
	default:
	  parsed = "";
	  break;
	}
  return parsed;
}

/*
  This function is responsible for displaying the text.
  *** Complete the function description ***

  pre-conditions:

  post-conditions:

*/
void Browser::display(ostream &out) const
{
  out << displayText << endl;
  out << "quit | file | link | next | previous | resize" << endl;
  out << message << endl;
}


/*
  This function overrides the output operation "<<" for
  the Browser class.

  pre-conditions: none
  post-conditions: none

*/
ostream& operator<<(ostream& out, const Browser &rhs)
{
  rhs.display(out);
  return out;
}

// Navigate to given link number 
void Browser::link(unsigned int linkNumber)
{
  if(linkNumber >= 0 && linkNumber <= numLinks){
	loadHTML(links[linkNumber]);
  }
  else{
	message = "Invalid Link";
  }
}

// Navigate to next page
void Browser::next()
{
  if( currentPage < numPages){
	displayText = pages[++currentPage];
	message = "";
  }
  else{
	message = "Last Page";
  }
}

// Navigate to previous page
void Browser::previous()
{
  if(currentPage > 0){
	displayText = pages[--currentPage];
	message = "";
  }
  else{
	message = "First Page";
  }
}

void Browser::resize(unsigned int rows, unsigned int columns){
  numRows = rows;
  numColumns = columns;

  // re-display current page with new sizes
  link(0);
  message = "Resized";
}



