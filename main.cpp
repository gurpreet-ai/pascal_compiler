// http://www.codeproject.com/Articles/833206/Lexical-analyzer-an-example

#include <iostream>
#include <string>
#include "token.h"
#include "scanner.cpp"

using namespace std;

typedef unsigned char BYTE;											// unsigned char can store 1 Bytes (8bits) of data (0-255)

int main (int argc, char* argv[]) {

	/* ----------------------------------------------- */
	/* Read the file as binary and place it into a buf */
	/* ----------------------------------------------- */

	// cout << argc <<endl;											// number of arguments
	// cout << argv[1] <<endl;										// the source file-name

	const char *filePath = "test.pas";

	BYTE *fileBuf;													// pointer to our buffered data
	FILE *file = NULL;												// file pointer

	if ((file = fopen(filePath, "rb")) == NULL)
		cout << "Could not open specified file" << endl;
	else
		cout << "File opened successfully" << endl;

	fseek(file, 0L, SEEK_END);										// get the file size
	int fileSize = ftell(file);
	fseek(file, 0L, SEEK_SET);

	cout << "File Size " << fileSize << endl;

	fileBuf = new BYTE[fileSize + 1];								// allocate space in the buffer for the whole file
	fileBuf[fileSize + 1] = '~';									// ~ to the end the file

	fread(fileBuf, fileSize, 1, file);								// read the file in to the buffer

	// Now that we have the entire file buffered, we can take a look at some binary infomation
	// Lets take a look in hexadecimal
	// for (int i = 0; i < fileSize; i++)
	// 	printf("%X "; fileBuf[i]);

	/* ------------------------------------------------ */
	/* 					SCANNER 						*/
	/* ------------------------------------------------	*/
	
	TokenType tokenType = UNDEF;
	rewind(file);
	
	// int x = 0;
	// while ( (tokenType = getTokenType(file, x)) != TK_EOF) {
	// 	x += 1;
	// }
	//fileBuf++;
	do {
		tokenType = getToken(fileBuf);
		cout << " " << tokenType << endl;
		// printToken();

	} while (tokenType != TK_EOF);

	fclose(file);
	cout << endl;
	return 0;
}







