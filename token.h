/* ----------------------------------------------- 	*/
/*               TOKEN.H		                   	*/
/* define the token types, and a token struct 		*/
/* ----------------------------------------------- 	*/

#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>
#include <locale>
#include <string>
#include <iomanip>

/* ------------------------------------------------ */
/*               TOKEN TYPES		             	*/
/* ------------------------------------------------	*/

typedef enum {
	
	/* ----------------------------------------------- */
	/*               IDENTIFIER	                   	   */
	/* ----------------------------------------------- */
	TK_ID, 													

	/* ----------------------------------------------- */
	/*               KEYWORDS		                   */
	/* ----------------------------------------------- */
	
	TK_PROGRAM, TK_BEGIN, 	TK_END, 	TK_PROCEDURE,					
	TK_WHILE, 	TK_FOR, 	TK_DO, 		TK_REPEAT, 
	TK_TYPE, 	TK_IF, 		TK_THEN, 	TK_ELSE, 
	TK_UNTIL, 	TK_FUNCTION, 			TK_BREAK, 
	TK_LABEL, 	TK_END_CODE,

	/* ----------------------------------------------- */
	/*               OPERATORS		                   */
	/* ----------------------------------------------- */

	TK_PLUS, 	TK_MINUS, 	TK_MULTI, 	TK_DIV,					
	TK_GREATER, TK_LESS, 	TK_LESS_EQ, TK_GREATER_EQ,
	TK_MOD,		TK_EQUALS,	TK_NOT_EQ, 	TK_EXCLAMATION,
	TK_AND,		TK_XOR,		TK_OR,		TK_NOT,
	TK_ASSIGNMENT, 			TK_DIV_FLOAT,

	/* ----------------------------------------------- */
	/*               DELIMITERS		                   */
	/* ----------------------------------------------- */
	TK_SEMICOLON, 		TK_OPEN_PAREN,		TK_CLOSE_PAREN,
	TK_CLOSE_BRACKET,	TK_BEGIN_COMMENT,	TK_END_COMMENT,
    TK_COMMA,			TK_OPEN_BRACKET,	TK_SINGLE_QUOTE,
    TK_DOUBLE_QUOTE,

	/* ----------------------------------------------- */
	/*               LITERALS		                   */
	/* ----------------------------------------------- */
	TK_INTEGER_LIT, TK_REAL_LIT, TK_STR_LIT,

	/* ----------------------------------------------- */
	/*               EOLN		                   	   */
	/* ----------------------------------------------- */
	TK_ELON,

	/* ----------------------------------------------- 	*/
	/*               EOF		                   		*/
	/* ----------------------------------------------- 	*/
	TK_EOF,

	/* ----------------------------------------------- 	*/
	/*               ERROR		                   		*/
	/* ----------------------------------------------- 	*/
	
	UNDEF, TK_ERROR

} TokenType;

/* ------------------------------------------------ */
/*               TOKEN Struct		             	*/
/* ------------------------------------------------	*/

typedef struct {
	TokenType token_Type;
	std::string token_Name;
	int line_num;
	int col_num;
} Token;

#endif


