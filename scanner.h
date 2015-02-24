/* 	The Scanner
	
	The scanner's job is to read the source file one character at a time. 
	For each character, it keeps track of the line and character position 
	where the character was found. Each time the scanner is called, it reads 
	the next character from the file and returns it.

*/

#include <iostream>
#include <stdio.h>
#include <fstream>
#include <String>

typedef unsigned char BYTE;

class Scanner
{

private:
	const char *filePath;							// file_path
	BYTE *fileBuf;
	int line_num;
	int col_num;
	long fileSize;

public:
	Scanner(char *f_p);								// constructor
	~Scanner();										// destructor

	void read_next();
	void print();

};