/* 	The Scanner
	
	The scanner's job is to read the source file one character at a time. 
	For each character, it keeps track of the line and character position 
	where the character was found. Each time the scanner is called, it reads 
	the next character from the file and returns it.

*/

typedef unsigned char BYTE;												// unsigned char can store 1 Bytes (8bits) of data (0-255)

TokenType getToken(BYTE *&filePtr);