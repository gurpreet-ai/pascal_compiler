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

// symbol table will be a list of structs
// struct sym_table {
// 	int Address;
// 	string Type;
// 	string Name;
// 	string Value;
// };

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

	std::list<sym_table> symbol_Table;												// will con
	Token var_decl;
	Token var_name;
	Token semi_colon;
	Token comma_or_colon;
	Token type;

	while (true) {
		var_decl = token_list.front();												// get the token
		token_list.pop_front();														// pop is from the list
		cur_token = var_decl.token_Type;											// cur_token here is TK_VAR
		flag = match(cur_token, TK_VAR);											// match the first token with PROGRAM 
		
		std::list<sym_table> lst_of_identifiers;

		if (flag) {																	// variable declaration
			while (1) {
				var_name = token_list.front();										// next token should be the name of the variable/identifier
				token_list.pop_front();												// pop that from the list
				cur_token = var_name.token_Type;							
				flag = match(cur_token, TK_ID);										// match token with TK_Identifier

				if (flag) {
					cout << var_name.token_Name << " | TK_ID" << endl;

					comma_or_colon = token_list.front();							// next token should be comma or colon
					token_list.pop_front();											// pop that from the list
					cur_token = comma_or_colon.token_Type;							
					flag = match(cur_token, TK_COMMA);
					if (!flag)
						break;
				}
			}

			flag = match(cur_token, TK_COLON);

			if (flag) {
				type = token_list.front();											// get the token
				token_list.pop_front();												// pop is from the list
				cur_token = type.token_Type;										// cur_token here is TK_VAR
				flag = match(cur_token, TK_INT);									// match the first token with PROGRAM 
				if (flag) {

					semi_colon = token_list.front();								// next token should be the name of the program
					token_list.pop_front();											// pop that from the list
					cur_token = semi_colon.token_Type;								
					flag = match(cur_token, TK_SEMICOLON);
					if (flag) {
						var_decl = token_list.front();								// get the token
						cur_token = var_decl.token_Type;							// cur_token here is TK_VAR
						flag = match(cur_token, TK_VAR);							// match the first token with PROGRAM 

						if (!flag)
							break;

					} else {
						cout << "error 2";
					}
				}

			} else {
				cout << "error 1";
			}

		}
	}

}



