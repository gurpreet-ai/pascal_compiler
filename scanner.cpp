/* 	The Scanner
	
	The scanner's job is to read the source file one character at a time. 
	For each character, it keeps track of the line and character position 
	where the character was found. Each time the scanner is called, it reads 
	the next character from the file and returns it.

*/

#include "scanner.h"
using namespace std;

Scanner::Scanner (char *f_p) {
	filePath = f_p;

	FILE *file = NULL;
	
	cout << "-------------------------------\n";
	cout << "File Path: " << filePath <<endl;
	
	if ((file = fopen(filePath, "rb")) == NULL)
		cout << "Could not open specified file" << endl;
	else
		cout << "File opened successfully" << endl;

	// Find the file size
	fseek(file, 0L, SEEK_END);
	fileSize = ftell(file);
	fseek(file, 0L, SEEK_SET);

	cout << "File Size: " << fileSize << endl;

	// Allocate space in the buffer for the whole file
	fileBuf = new BYTE[fileSize + 1];
	fileBuf[fileSize + 1] = '\0';

	// Read the file in to the buffer
	fread(fileBuf, fileSize, 1, file);

	fclose(file); 
	cout << "-------------------------------\n";
}

Scanner::~Scanner() {
	delete[] fileBuf;
}

void Scanner::print () {
	cout << "-------------------------------\n";
	for (int i = 0; i < fileSize + 2; i++)
		printf("%c", fileBuf[i]);
	cout << "\n-------------------------------\n";
}




