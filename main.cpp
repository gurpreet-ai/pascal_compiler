// http://www.codeproject.com/Articles/833206/Lexical-analyzer-an-example

#include <iostream>
#include <string>
#include <iomanip>
#include "token.h"
#include "scanner.h"
#include "sym_table.h"
#include "node.h"
#include "util.cpp"
#include <list>

using namespace std;

typedef unsigned char BYTE;											// unsigned char can store 1 Bytes (8bits) of data (0-255)

int main (int argc, char* argv[]) {

	/* ------------------------------------------------------------------------------------------------ */
	/* -------------------- 											   ---------------------------- */
	/* 						Read the file as binary and place it into a buf 						    */
	/* ---------------------												---------------------------	*/
	/* ------------------------------------------------------------------------------------------------ */
	
	// cout << argc <<endl;											// number of arguments
	// cout << argv[1] <<endl;										// the source file-name

	const char *filePath = "program_testing/test.pas";

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

	/* ------------------------------------------------------------------------------------------------ */
	/* ---------------------------------				----------------------------------------------- */
	/* 										SCANNER 						      						*/
	/* ---------------------------------				----------------------------------------------	*/
	/* ------------------------------------------------------------------------------------------------ */
	
	Token tk;
	rewind(file);

	int line_num = 1, col_num = 0;
	
	std::list<Token> token_list;

	do {
		tk = getToken(fileBuf, line_num, col_num);
		token_list.push_back(tk);
	} while (tk.token_Type != TK_EOF);

	print_scanner_output(token_list);									// util.cpp - print the scanner output

	fclose(file);

	cout << endl;
	return 0;
}







