/*
 * CPSC 2430 - Data Structures
 * Spring 2016
 * Initial version of this file was created by Tribelhorn, Ben on 9/25/13
 *
 * Description: Programming Assignment 1 - Textbased HTML browser
 *
 * Students Name: Cody Brewer
 * Date: 4/14/2016
 */


#include "Browser.h"


/* Default constructor
   Initializes the browser size to default values
*/

Browser::Browser()
  : numColumns(40), numRows(6),currentPage(0),
    displayText("Text Browser\nPlease enter a command: ")
	
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
  This function traverses encodedText, scrubbing
  excess whitespace and parsing HTML tags. This
  parsed string is then formatted into rows and
  pages according to browser dimensions

  pre-conditions: unformatted HTML has been loaded

  post-conditions: HTML document has been formatted and
                  split into pages that are ready to display

*/


void Browser::parseHTML(string encodedText)
{
  unsigned int currentRow = 0, currentCol = 0, wordLength = 0;
  unsigned int writingPage = 0; // page currently being written to 
  unsigned int startPtr = 0, endPtr = 0, stringPtr = 0;
  string parsedString = "", currentWord = "", tag = "";
  bool extraSpace = false;
  
  currentPage = 0;
  numPages = 0;
  numLinks = 0;
  
  // traverse entire string, while
  // ignoring extra whitespace and
  // sending html tags to be parsed
  while(stringPtr < encodedText.length()){

	// found an opening tag
	if(encodedText[stringPtr] == '<')
	  {
		tag = "";
		//scan for closing tag or end of document
		while (encodedText[stringPtr] != '>' &&
			   stringPtr < encodedText.length())
		  {
			tag += encodedText[stringPtr];		     
			++stringPtr;
		  }

		//included closing > in tag
		tag += encodedText[stringPtr];
		
		// reached end of document with no closing tag
		if (encodedText[stringPtr] != '>' &&
			stringPtr >= encodedText.length())
		  {
			//opening '<' was not for a valid tag, copy as is
		  }
		
		// reached end of tag, send to parse
		else
		  {
			tag = parseTag(tag);
			++stringPtr; // move stringPtr past closing '>'
		  }

		parsedString += tag;
		extraSpace = false;
	  }

	else
	  {
		// scan for an opening tag
		while( encodedText[stringPtr] != '<' &&
			   stringPtr <= encodedText.length())
		  {
			if( (encodedText[stringPtr] == ' ' && extraSpace) ||
				encodedText[stringPtr] == '\n')
			  {
				//skip extra whitespace, treat newlines as single spaces
				if(encodedText[stringPtr] == '\n' && !extraSpace)
				  {
					parsedString += ' ';
					extraSpace = true;
				  }
			  }
			else if(encodedText[stringPtr] == ' ' && !extraSpace)
			  {
				//copy single space
				parsedString += encodedText[stringPtr];
				extraSpace = true;
			  }
			else
			  {
				//copy current non-space character
				parsedString += encodedText[stringPtr];
				extraSpace = false;
			  }
		
			++stringPtr;
		  }
	  }
  }

  // traverse entire parsed string, while
  // dividing parsed string into lines and
  // pages as required by browser dimensions
  while(startPtr < parsedString.length())
	{
	  startPtr = endPtr;
	  currentWord = "";
	  // find the end of the current word
	  while( parsedString[endPtr] != ' '  &&
			 parsedString[endPtr] != '\n' &&
			 endPtr < parsedString.length() )
		{
		  currentWord += parsedString[endPtr];
		  ++endPtr;
		}

	  // include trailing space in current word
	  currentWord += parsedString[endPtr];
	  
	  // size of word not including trailing space or \n
	  wordLength = endPtr - startPtr;

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

	  if(parsedString[endPtr] == '\n')
		{
		  currentCol = 0;
		  ++currentRow;
		}

	  // copy current word to current page
	  pages[writingPage] += currentWord;
	  
	  // advance pointer past trailing space or \n
	  ++endPtr;
		
	}

  //total pages = the last page that was written to 
  numPages = writingPage;
}

/*
  This function is responsible for parsing the HTML tags.

  This function parses <P>, <B>, <A>, and </A> tags. Case insensitive.
  The appropriate formatting is returned by this function as a string.
  <P> returns two newlines
  <B> returns one newline
  <A> returns a "start link" marker, and adds the link to 
  </A> returns an "end link" marker

  <A> tags also result in a link being added to 
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
	case 'H':
	  // case insensitive
	case 'h':
	  // <HR> horizontal rule tag
	  if(parsed[1] == 'R' || parsed[1] == 'r'){
		parsed = "\n";
		for(unsigned int i = 0; i < numColumns; ++i){
		  parsed += '-';
		}
	  }
	  else
		parsed = "";
	  break;
	case 'p':
	  // case insensitive
	case 'P':
	  parsed = "\n\n";
	  break;
	case 'b':
	  // case insensitive
	case 'B':
	  // <BR> break tag
	  if(parsed[1] == 'R' || parsed[1] == 'r')
		  parsed = "\n";
	  else
		parsed = "";
	  break;
	case 'a':
	  //case insensitive
	case 'A':

	  // scan for part in quotes
	  for(unsigned int currentChar = 0; currentChar < parsed.size(); ++currentChar)
		{
		  //turn off quotes before copying final ' " '
		  if( parsed[currentChar] == '"' && inQuotes )
			  inQuotes = false;

		  if (inQuotes)
			  linkURL += parsed[currentChar];

		  //turn on quotes without copying initial ' " '
		  if( parsed[currentChar] == '"' && !inQuotes )
			  inQuotes = true;
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

  pre-conditions:Parsed HTML has been loaded into the
  browser

  post-conditions:Formatted page and command menu are
  displayed to the user

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


/*
  This function navigates to the given link number.

  pre-conditions: any HTML document has been loaded
  post-conditions: the linked document is displayed
  to the user

*/
void Browser::link(unsigned int linkNumber)
{
  if(linkNumber >= 0 && linkNumber <= numLinks){
	loadHTML(links[linkNumber]);
	message = "";
  }
  else
	message = "Invalid Link";
}

/*
  This function navigates the browser to next page

  pre-conditions: an HTML document has been loaded

  post-conditions: the next page of the document is
  displayed to the user, or the user is informed
  that they have reached the end of the document
  
*/
void Browser::next()
{
  if( currentPage < numPages){
	displayText = pages[++currentPage];
	message = "";
  }
  else
	message = "Last Page";
}

/*
  This function navigates the browser to the previous
  page

  pre-conditions: an HTML document has been loaded

  post-conditions: the previous page of the document
  is displayed to the user, or the user is informed
  that they have reached the beginning of the document
  
*/
void Browser::previous()
{
  if(currentPage > 0){
	displayText = pages[--currentPage];
	message = "";
  }
  else
	message = "First Page";
}

/*
  This function allows the user to resize the browser to
  the given dimensions at any time

  pre-conditions:none

  post-conditions: the browser has been resized to the
  given dimensions
  
 */
void Browser::resize(unsigned int rows, unsigned int columns){

  if(numRows > 0 && numColumns > 0)
	{
	  // re-display current page with new sizes
	  numRows = rows;
	  numColumns = columns;
	  link(0);
	  message = "Resized";
	}
  else
	message = "Invalid Size";
}



