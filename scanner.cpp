/* 	The Scanner
	
	The scanner's job is to read the source file one character at a time. 
	For each character, it keeps track of the line and character position 
	where the character was found. Each time the scanner is called, it reads 
	the next character from the file and returns it.

*/

#include "scanner.h"
#include <iostream>
using namespace std;

Scanner::Scanner (std::string f_n) {
	file_name = f_n;
}

Scanner::~Scanner() {

}

void Scanner::print () {
	cout << file_name;
}