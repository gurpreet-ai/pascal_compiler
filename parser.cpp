#include <iostream>
#include <string>
#include <iomanip>
#include "token.h"
#include "scanner.h"
#include <list>
using namespace std;

bool match(int t, int cur_token) {
	return (t == cur_token);
}

void parser (std::list<Token> token_list) {	
/*	<program> ->
		<program header>
		<declarations>
		<begin-statement>
		<halt> */

	/* ------------------------------------------------------------------------------------------------ */
	/* ---------------------------------				----------------------------------------------- */
	/* 									PARSE The PROGRAM Header 	 						      		*/
	/* ---------------------------------				----------------------------------------------	*/
	/* ------------------------------------------------------------------------------------------------ */

	Token program = token_list.front();											// get the token
	token_list.pop_front();														// pop is from the list

	int cur_token = program.token_Type;											// cur_token here is TK_PROGRAM
	bool flag = match(cur_token, TK_PROGRAM);									// match the first token with PROGRAM 

	if (flag) {										
		Token program_name = token_list.front();								// next token should be an identifier (name of program)
		token_list.pop_front();													// pop it from the list
	
		cur_token = program_name.token_Type;									// next token should be an identifier (name of program)
		flag = match(cur_token, TK_ID);
		if (flag) {
			Token semi_colon = token_list.front();								// next token should be the name of the program
			token_list.pop_front();												// pop that from the list
	
			cur_token = semi_colon.token_Type;								
			flag = match(cur_token, TK_SEMICOLON);								// match it token	
			if (flag) {
				cout << "Program header looks good" << endl;					// 
			} else {
				cout << "error 3" << endl;										// error 3 display
			}
		} else {
			cout << "error 2" << endl;											// error 2 display
		}
	} else {
		cout << "error 1" << endl;												// error 1 display
	}

	/* ------------------------------------------------------------------------------------------------ */
	/* ---------------------------------				----------------------------------------------- */
	/* 									PARSE The Declarations	 						      			*/
	/* ---------------------------------				----------------------------------------------	*/
	/* ------------------------------------------------------------------------------------------------ */

	Token var_decl = token_list.front();										// get the token
	token_list.pop_front();														// pop is from the list
	cur_token = var_decl.token_Type;											// cur_token here is TK_VAR
	flag = match(cur_token, TK_VAR);											// match the first token with PROGRAM 

	if (flag) {																	// variable declaration
		Token var_name = token_list.front();									// next token should be the name of the variable/identifier
		token_list.pop_front();													// pop that from the list
		cur_token = var_name.token_Type;								
		flag = match(cur_token, TK_ID);											// match token with TK_Identifier

		if (flag) {
			cout << var_name.token_Name << " | TK_ID" << endl;

			Token comma_or_colon = token_list.front();							// next token should be comma or colon
			token_list.pop_front();												// pop that from the list
			cur_token = comma_or_colon.token_Type;									
			flag = match(cur_token, TK_COMMA);
			if (flag) {															// it was a comma
				
			} else {
				flag = match(cur_token, TK_COLON);
				if (flag) {
					cout << comma_or_colon.token_Name << " | TK_COLON" << endl;

					Token type = token_list.front();							// get the token
					token_list.pop_front();										// pop is from the list
					cur_token = type.token_Type;								// cur_token here is TK_VAR
					flag = match(cur_token, TK_INT);							// match the first token with PROGRAM 

					if (flag) {
						cout << type.token_Name << " | TK_INT" << endl;

						Token semi_colon_1 = token_list.front();							// next token should be the name of the program
						token_list.pop_front();												// pop that from the list
				
						cur_token = semi_colon_1.token_Type;								
						flag = match(cur_token, TK_SEMICOLON);								// match it token	
						if (flag) {
							cout << semi_colon_1.token_Name << " | TK_SEMICOLON" << endl;

							cout << "Program declaration looks good" << endl;					// 
						} else {
							cout << "error 7" << endl;										// error 3 display
						}

					}

				} else {
					cout << "error 5"<<endl;
				}
			}

		} else {
			cout << "error 4";
		}
	}

}



