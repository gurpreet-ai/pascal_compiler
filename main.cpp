// http://www.codeproject.com/Articles/833206/Lexical-analyzer-an-example

#include <iostream>
#include <string>
#include <iomanip>
#include "token.h"
#include "scanner.h"
#include "sym_table.h"

using namespace std;

typedef unsigned char BYTE;											// unsigned char can store 1 Bytes (8bits) of data (0-255)

int main (int argc, char* argv[]) {

	/* ----------------------------------------------- */
	/* Read the file as binary and place it into a buf */
	/* ----------------------------------------------- */

	// cout << argc <<endl;											// number of arguments
	// cout << argv[1] <<endl;										// the source file-name

	const char *filePath = "program_testing/assignment.pas";

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
	
	Token tk;
	rewind(file);
	
	// SymbolTable symbol_Table;
	TokenType x = static_cast<TokenType>(5);
	cout << x << endl;

	cout << "SCANNER" <<endl;
	cout << "";
	int line_num = 0, col_num = 0;
	int i = 0;

	do {
		tk = getToken(fileBuf, line_num, col_num);
		i += 1;
		cout << i << setw(10) << cout << tk.token_Type << setw(20) << tk.token_Name << setw(20) << tk.line_num << setw(20) << tk.col_num <<endl;

	} while (tk.token_Type != TK_EOF);

	fclose(file);


	cout << endl;
	return 0;
}







