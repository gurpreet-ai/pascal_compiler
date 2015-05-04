#include <iostream>
#include <locale>
#include <string>
#include <iomanip>
#include "token.h"
#include "scanner.h"
using namespace std;

// return the TokenType associated with the scanned
// identi, keyword, operator....

Token getToken(BYTE *&filePtr, int &line_num, int &col_num) {

	// RETURN VALUE OF THIS FUNCTION defined in token.h (Token struct)
	Token tk;															// token to return

	// cout << *filePtr << setw(20);

	/* ----------------------------------------------- */
	/* 					ALPHABET 					   */
	/* if read an alphabet letter then verify if it is */
	/* a string_lit, keyword, or an identifier  	   */
	/* 					DIGIT 						   */
	/* if read a digit verify if it is a real integer  */
	/* or a integer literal 						   */
	/* ----------------------------------------------- */

	// if at the end of the line, increment the pointer to next line
	// or the next index in our array
	if (*filePtr == '\n') {
		filePtr++;
		line_num++;
		col_num = 0;
	}

	// get rid of the space between the chars...
	while (isspace(*filePtr) && *filePtr != '~') {
		filePtr++;
	}

	/* The code inside of the if statement verifies that if we scan and alpha,
	we will either tokenize it as a string literal if we begin with a ',
	or we will tokenize it as a keyword if it appears in our keywords array
	or it will be tokenized as a identifier.
	*/
	if (isalpha(*filePtr)) {											// scanned an alpha
		string build_string;											// allocating a string for input
		if (*(filePtr - 1) == '\'') {									// must be a string
			while ((*filePtr != '\'') && (*filePtr != '~')) {			// until the 2nd ' is found
				build_string += *filePtr;
				filePtr++;												// increment the pointer
				col_num++;
			}
			if (*filePtr == '~') {										// didn't find the closing quote
				cout << "Error: Missing closing single quote.";

				tk.token_Name = build_string;
				tk.token_Type = TK_ERROR;
				tk.line_num = line_num;
				tk.col_num = col_num;

				return tk;												// throw an error
			}

			tk.token_Type = TK_STR_LIT;
			tk.token_Name = build_string;
			tk.line_num = line_num;
			tk.col_num = col_num;

			return tk;													// otherwise it must be a string literal
		} 
		else {															// starting string literal check
			while (isalpha(*filePtr) || isdigit(*filePtr) ) {			// must be an identifier or keyword
				if (isalpha(*filePtr)) {								// if alpha
					build_string += toupper(*filePtr);					// append the letter to string
					col_num++;
				} else {												// otherwise
					build_string += *filePtr;							// append to the string being constructed
					col_num++;
				}
				filePtr++;
			}

			string KEYWORDS [] = {										// list of keywords in pascal
				"PROGRAM", "BEGIN", "END.", "PROCEDURE", "IF", "THEN", "ELSE",
				"FOR", "WHILE", "DO", "AND", "OR", "NOT", "REPEAT",
				"BREAK", "FUNCTION", "TYPE", "UNTIL", "LABEL", "VAR", "INTEGER", "REAL"
			};

			if (*filePtr == '.') {
				if (build_string == "END") {
					build_string += *filePtr;
					tk.token_Name = build_string;
					tk.line_num = line_num;
					tk.col_num = col_num;
					filePtr++;
				}
			}
			else {
				tk.token_Name = build_string;
				tk.line_num = line_num;
				tk.col_num = col_num;
			}

			tk.token_Name = build_string;
			tk.line_num = line_num;
			tk.col_num = col_num;

			int KW_size = sizeof(KEYWORDS)/sizeof(KEYWORDS[0]);			// get the size of array of strings

			for (int k = 0; k < KW_size; k++) {							// tokenize the build_string
				if (KEYWORDS[k] == build_string) {
					if (build_string == "PROGRAM") {
						tk.token_Type = TK_PROGRAM;
						return tk;
					} 
					else if (build_string == "VAR") {
						tk.token_Type = TK_VAR;
						return tk;
					}
					else if (build_string == "BEGIN") {
						tk.token_Type = TK_BEGIN;
						return tk;
					}
					else if (build_string == "END.") {
						tk.token_Type = TK_END;
						return tk;
					}
					else if (build_string == "PROCEDURE") {
						tk.token_Type = TK_PROCEDURE;
						return tk;
					}
					else if (build_string == "IF") {
						tk.token_Type = TK_IF;
						return tk;
					}
					else if (build_string == "THEN") {
						tk.token_Type = TK_THEN;
						return tk;
					}
					else if (build_string == "ELSE") {
						tk.token_Type = TK_ELSE;
						return tk;
					}
					else if (build_string == "FOR") {
						tk.token_Type = TK_FOR;
						return tk;
					}
					else if (build_string == "WHILE") {
						tk.token_Type = TK_WHILE;
						return tk;
					}
					else if (build_string == "DO") {
						tk.token_Type = TK_DO;
						return tk;
					}
					else if (build_string == "REAL") {
						tk.token_Type = TK_REAL;
						return tk;
					}
					else if (build_string == "INTEGER") {
						tk.token_Type = TK_INT;
						return tk;
					}
					else if (build_string == "AND") {
						tk.token_Type = TK_AND;
						return tk;
					}
					else if (build_string == "OR") {
						tk.token_Type = TK_OR;
						return tk;
					}
					else if (build_string == "NOT") {
						tk.token_Type = TK_NOT;
						return tk;
					}
					else if (build_string == "REPEAT") {
						tk.token_Type = TK_REPEAT;
						return tk;
					}
					else if (build_string == "BREAK") {
						tk.token_Type = TK_BREAK;
						return tk;
					}
					else if (build_string == "FUNCTION") {
						tk.token_Type = TK_FUNCTION;
						return tk;
					}
					else if (build_string == "TYPE") {
						tk.token_Type = TK_TYPE;
						return tk;
					}
					else if (build_string == "UNTIL") {
						tk.token_Type = TK_UNTIL;
						return tk;
					}
					else if (build_string == "LABEL") {
						tk.token_Type = TK_LABEL;
						return tk;
					}
				}
			}
			tk.token_Type = TK_ID;
			return tk;
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
			col_num++;
		}

		if (*filePtr != '.') {
			tk.token_Name = build_num;
			tk.line_num = line_num;
			tk.col_num = col_num;
			tk.token_Type = TK_INTEGER_LIT;
			return tk;
		}

	} else {															// must be an operator
		string op;

		switch(*filePtr)
		{
			case ';':	{												// if semicolon return token for semicolon
				col_num += 1;
				tk.token_Name = ';';
				tk.line_num = line_num;
				tk.col_num = col_num;
				tk.token_Type = TK_SEMICOLON;
				filePtr++;
				return tk;
			}
			case ':':	{												// if semicolon return token for semicolon
				op += *filePtr;
				filePtr++;
				if (*filePtr == '=') {
					op += *filePtr;
					col_num += 1;
					tk.token_Name = op;
					tk.line_num = line_num;
					tk.col_num = col_num;
					tk.token_Type = TK_ASSIGNMENT;
					filePtr++;
					return tk;
				} else {
					col_num += 1;
					tk.token_Name = ':';
					tk.line_num = line_num;
					tk.col_num = col_num;
					tk.token_Type = TK_COLON;
					return tk;
				}
			}
			case '+':	{
				col_num += 1;
				tk.token_Name = '+';
				tk.line_num = line_num;
				tk.col_num = col_num;
				tk.token_Type = TK_PLUS;
				filePtr++;
				return tk;
			}
			case '-':	{
				col_num += 1;
				tk.token_Name = '-';
				tk.line_num = line_num;
				tk.col_num = col_num;
				tk.token_Type = TK_MINUS;
				filePtr++;
				return tk;
			}
			case '/':	{
				col_num += 1;
				tk.token_Name = '/';
				tk.line_num = line_num;
				tk.col_num = col_num;
				tk.token_Type = TK_DIV;
				filePtr++;
				return tk;
			}
			case '*':	{
				col_num += 1;
				tk.token_Name = '*';
				tk.line_num = line_num;
				tk.col_num = col_num;
				tk.token_Type = TK_MULTI;
				filePtr++;
				return tk;
			}
			case '%':	{
				col_num += 1;
				tk.token_Name = '%';
				tk.line_num = line_num;
				tk.col_num = col_num;
				tk.token_Type = TK_MOD;
				filePtr++;
				return tk;
			}
			case '(':	{
				col_num += 1;
				tk.token_Name = '(';
				tk.line_num = line_num;
				tk.col_num = col_num;
				tk.token_Type = TK_OPEN_PAREN;
				filePtr++;
				return tk;
			}
			case ')':	{
				col_num += 1;
				tk.token_Name = ')';
				tk.line_num = line_num;
				tk.col_num = col_num;
				tk.token_Type = TK_CLOSE_PAREN;
				filePtr++;
				return tk;
			}
			case '<':	{
				col_num += 1;
				tk.token_Name = '<';
				tk.line_num = line_num;
				tk.col_num = col_num;
				tk.token_Type = TK_LESS;
				filePtr++;
				return tk;
			}
			case '>':	{
				col_num += 1;
				tk.token_Name = '>';
				tk.line_num = line_num;
				tk.col_num = col_num;
				tk.token_Type = TK_GREATER;
				filePtr++;
				return tk;
			}
			case '\'':	{
				col_num += 1;
				tk.token_Name = '\'';
				tk.line_num = line_num;
				tk.col_num = col_num;
				tk.token_Type = TK_SINGLE_QUOTE;
				filePtr++;
				return tk;
			}
			case '"':	{
				col_num += 1;
				tk.token_Name = '"';
				tk.line_num = line_num;
				tk.col_num = col_num;
				tk.token_Type = TK_DOUBLE_QUOTE;
				filePtr++;
				return tk;
			}
			case '~':	{
				col_num += 1;
				tk.token_Name = '~';
				tk.line_num = line_num;
				tk.col_num = col_num;
				tk.token_Type = TK_EOF;
				filePtr++;
				return tk;
			}
			case ',':	{
				col_num += 1;
				tk.token_Name = ',';
				tk.line_num = line_num;
				tk.col_num = col_num;
				tk.token_Type = TK_COMMA;
				filePtr++;
				return tk;
			}
			case '=':	{
				col_num += 1;
				tk.token_Name = '=';
				tk.line_num = line_num;
				tk.col_num = col_num;
				tk.token_Type = TK_EQUALS;
				filePtr++;
				return tk;
			}
			default: {
				col_num += 1;
				tk.token_Name = *filePtr;
				tk.line_num = line_num;
				tk.col_num = col_num;
				tk.token_Type = TK_ERROR;
				filePtr++;
				return tk;
			}
		}
	}

	tk.token_Type = UNDEF;
	return tk;

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












