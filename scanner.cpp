#include <iostream>
#include <locale>
#include <string>
#include "token.h"
using namespace std;

typedef unsigned char BYTE;												// unsigned char can store 1 Bytes (8bits) of data (0-255)

// return the TokenType associated with the scanned
// identi, keyword, operator....

TokenType getToken(BYTE *&filePtr) {

	/* ----------------------------------------------- */
	/* 					ALPHABET 					   */
	/* if read an alphabet letter then verify if it is */
	/* a string_lit, keyword, or an identifier  	   */
	/* ----------------------------------------------- */

	// get rid of the space between the chars...
	while (isspace(*filePtr) && *filePtr != '~') {
		filePtr++;
	}

	// if at the end of the line, increment the pointer to next line
	// or the next index in our array
	if (*filePtr == '\n')
		filePtr++;

	/* The code inside of the if statement verifies that if we scan and alpha,
	we will either tokenize it as a string literal if we begin with a ',
	or we will tokenize it as a keyword if it appears in our keywords array
	or it will be tokenized as a identifier.
	*/
	if (isalpha(*filePtr)) {											// scanned an alpha
		if (*(filePtr - 1) == '\'') {									// must be a string
			while ((*filePtr != '\'') && (*filePtr != '~')) {			// until the 2nd ' is found
				filePtr++;												// increment the pointer
			}
			if (*filePtr == '~') {										// didn't find the closing quote
				cout << "Error: Missing closing single quote.";
				return TK_ERROR;										// throw an error
			}
			return TK_STR_LIT;											// otherwise it must be a string literal
		} 
		else {															// starting string literal check
			string build_string;										// allocating a string for input
			while (isalpha(*filePtr) || isdigit(*filePtr) ) {			// must be an identifier or keyword
				if (isalpha(*filePtr)) {								// if alpha
					build_string += toupper(*filePtr);					// append the letter to string
				} else {												// otherwise
					build_string += *filePtr;							// append to the string being constructed
				}
				filePtr++;
			}

			// cout << build_string;

			string KEYWORDS [] = {										// list of keywords in pascal
				"PROGRAM", "BEGIN", "END", "PROCEDURE", "IF", "THEN", "ELSE",
				"FOR", "WHILE", "DO", "AND", "OR", "NOT", "REPEAT",
				"BREAK", "FUNCTION", "TYPE", "UNTIL", "LABEL", "VAR"
			};

			int KW_size = sizeof(KEYWORDS)/sizeof(KEYWORDS[0]);			// get the size of array of strings

			for (int k = 0; k < KW_size; k++) {							// tokenize the build_string
				if (KEYWORDS[k] == build_string) {
					if (build_string == "PROGRAM")
						return TK_PROGRAM;
					else if (build_string == "BEGIN")
						return TK_BEGIN;
					else if (build_string == "END")
						return TK_END;
					else if (build_string == "PROCEDURE")
						return TK_PROCEDURE;
					else if (build_string == "IF")
						return TK_IF;
					else if (build_string == "THEN")
						return TK_THEN;
					else if (build_string == "ELSE")
						return TK_ELSE;
					else if (build_string == "FOR")
						return TK_FOR;
					else if (build_string == "WHILE")
						return TK_WHILE;
					else if (build_string == "DO")
						return TK_DO;
					else if (build_string == "AND")
						return TK_AND;
					else if (build_string == "OR")
						return TK_OR;
					else if (build_string == "NOT")
						return TK_NOT;
					else if (build_string == "REPEAT")
						return TK_REPEAT;
					else if (build_string == "BREAK")
						return TK_BREAK;
					else if (build_string == "FUNCTION")
						return TK_FUNCTION;
					else if (build_string == "TYPE")
						return TK_TYPE;
					else if (build_string == "UNTIL")
						return TK_UNTIL;
					else if (build_string == "LABEL")
						return TK_LABEL;
				}
			}
			return TK_ID;
		}	
	}

	/* The code inside of the else if verifies that if it is a digit
		is a integer literal or a real literal.
		*/
	else if (isdigit(*filePtr)) {										// must be a digit
		string build_num;												// create string to store the digits
		while (isdigit(*filePtr) && *filePtr != '~') {					// until we read a int
			build_num += *filePtr;										// add it on to the string
			filePtr++;
		}

		if (*filePtr != '.') {
			return TK_INTEGER_LIT;
		}
	} else {															// must be an operator
		switch(*filePtr)
		{
			case ';':	{												// if semicolon return token for semicolon
				filePtr++;
				return TK_SEMICOLON;
			}
			case '+':	{
				filePtr++;
				return TK_PLUS;
			}
			case '-':	{
				filePtr++;
				return TK_MINUS;
			}
			case '/':	{
				filePtr++;
				return TK_DIV;
			}
			case '*':	{
				filePtr++;
				return TK_MULTI;
			}
			case '%':	{
				filePtr++;
				return TK_MOD;
			}
			case '(':	{
				filePtr++;
				return TK_OPEN_PAREN;
			}
			case ')':	{
				filePtr++;
				return TK_CLOSE_PAREN;
			}
			case '\'':	{
				filePtr++;
				return TK_SINGLE_QUOTE;
			}
			case '"':	{
				filePtr++;
				return TK_DOUBLE_QUOTE;
			}
			case '~':	{
				return TK_EOF;
			}
			default: {
				filePtr++;
				return TK_ERROR;
			}
		}
	}

	return UNDEF;

	// else if () {

	// }

	// INCREMENT TO THE NEXT VALUE POINTED BY POINTER filePtr
	// filePtr++;
	// cout << *filePtr;
	// char x = *(filePtr - 1);
	// cout << x;
	// cout << *filePtr;

	// return TK_EOF;
}












