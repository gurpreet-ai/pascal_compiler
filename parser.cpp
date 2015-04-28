#include <iostream>
#include <string>
#include <iomanip>
#include "token.h"
#include <list>

using namespace std;

bool match(int t, int cur_token) {
	return (t == cur_token);
}

// symbol table will be a list of structs
typedef struct {
	int Address;
	int Type;
	std::string Name;
	std::string Value;
} sym_table;

typedef struct {
	int instruction_ptr;
	int token;
	std::string instruction;
	std::string value;
} decoraded_nodes;

// 'ip': 0, 'token': 'TK_INTEGER', 'instruction': 'op_push', 'value': '8'

void print_symbol_table(std::list<sym_table> sym_table);
void print_parser_output(std::list<decoraded_nodes> instruction_list);
// void statements(std::list<Token> token_list);

void E(int & cur_token, Token & new_tk, std::list<Token>& token_list, std::list<decoraded_nodes>& instruction_list, std::list<decoraded_nodes>::iterator & ittt, int & instruction_pointer);
void T(int & cur_token, Token & new_tk, std::list<Token>& token_list, std::list<decoraded_nodes>& instruction_list, std::list<decoraded_nodes>::iterator & ittt, int & instruction_pointer);
void E_prime(int & cur_token, Token & new_tk, std::list<Token>& token_list, std::list<decoraded_nodes>& instruction_list, std::list<decoraded_nodes>::iterator & ittt, int & instruction_pointer);
void F(int & cur_token, Token & new_tk, std::list<Token>& token_list, std::list<decoraded_nodes>& instruction_list, std::list<decoraded_nodes>::iterator & ittt, int & instruction_pointer);
void T_prime(int & cur_token, Token & new_tk, std::list<Token>& token_list, std::list<decoraded_nodes>& instruction_list, std::list<decoraded_nodes>::iterator & ittt, int & instruction_pointer);

void parser (std::list<Token> token_list, std::list<decoraded_nodes>& instruction_list, std::list<sym_table>& symbol_Table) {	
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
	/* 									PARSE The variable Declarations	 						      	*/
	/* ---------------------------------				----------------------------------------------	*/
	/* ------------------------------------------------------------------------------------------------ */

	// std::list<sym_table> symbol_Table;												// will con
	
	Token var_decl;
	Token var_name;
	Token semi_colon;
	Token comma_or_colon;
	Token type;
	sym_table id;
	int addr = 0;

	while (true) {
		var_decl = token_list.front();												// get the token
		token_list.pop_front();														// pop is from the list
		cur_token = var_decl.token_Type;											// cur_token here is TK_VAR
		flag = match(cur_token, TK_VAR);											// match the first token with PROGRAM 
		
		std::list<sym_table> lst_of_identifiers;
		std::list<sym_table>::iterator itt;
		itt = lst_of_identifiers.begin();

		if (flag) {																	// variable declaration
			while (1) {
				var_name = token_list.front();										// next token should be the name of the variable/identifier
				token_list.pop_front();												// pop that from the list
				cur_token = var_name.token_Type;							
				flag = match(cur_token, TK_ID);										// match token with TK_Identifier

				if (flag) {

					++itt;
					
					id.Name = var_name.token_Name;
					id.Value = '0';

					lst_of_identifiers.insert(itt, id);

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

					for (std::list<sym_table>::iterator it=lst_of_identifiers.begin(); it != lst_of_identifiers.end(); ++it) {
	    				it->Address = addr;
	    				it->Type = TK_INT;
	    				addr += 4;
	    			}

					semi_colon = token_list.front();								// next token should be the name of the program
					token_list.pop_front();											// pop that from the list
					cur_token = semi_colon.token_Type;								
					flag = match(cur_token, TK_SEMICOLON);
					if (flag) {
						var_decl = token_list.front();								// get the token
						cur_token = var_decl.token_Type;							// cur_token here is TK_VAR
						flag = match(cur_token, TK_VAR);							// match the first token with PROGRAM 

						symbol_Table.insert(symbol_Table.end(), lst_of_identifiers.begin(), lst_of_identifiers.end());

						if (!flag)
							break;													// must be a begin statement here

					} else {
						cout << "error 2";
					}
				}
			} else {
				cout << "error 1";
			}

		}
	}

	print_symbol_table(symbol_Table);

	/* ---------------------------------				----------------------------------------------- */
	/* 									PARSE The Statements	 						      			*/
	/* ---------------------------------				----------------------------------------------	*/
	/* ------------------------------------------------------------------------------------------------ */

	/* <begin-statement> ->
        	<statements> 
        <end> */
	
	Token begin = token_list.front();
	token_list.pop_front();
	cur_token = begin.token_Type;
	flag = match(cur_token, TK_BEGIN);
	if (!flag)
		cout << "error at begin";

	// std::list<decoraded_nodes> instruction_list;
	std::list<decoraded_nodes>::iterator ittt;
	ittt = instruction_list.begin();

	int instruction_pointer = 0;

	while (cur_token != TK_END) {
		Token new_tk = token_list.front();
		token_list.pop_front();
		cur_token = new_tk.token_Type;
		flag = match(cur_token, TK_ID);																		// matched an identifier
		string left_hand_side = new_tk.token_Name;
		if (flag) {
			new_tk = token_list.front();
			token_list.pop_front();
			cur_token = new_tk.token_Type;
			flag = match(cur_token, TK_ASSIGNMENT);															// match an assignment statement
			if (flag) {

				// while (cur_token != TK_SEMICOLON) {															// until we find the semicolon
				// 	new_tk = token_list.front();
				// 	token_list.pop_front();
				// 	cur_token = new_tk.token_Type;
				// 	flag = match(cur_token, TK_INTEGER_LIT);												// integer literal
				// 	if (flag) {
				// 		decoraded_nodes I;
				// 		I.instruction_ptr = instruction_pointer;
				// 		I.instruction = "op_push";
				// 		I.value = new_tk.token_Name;
				// 		I.token = cur_token;
				// 		instruction_list.insert(ittt, I);
				// 		instruction_pointer += 1;
				// 	}

				// 	flag = match(cur_token, TK_PLUS);
				// 	if (flag) {
				// 		decoraded_nodes A;
				// 		A.instruction_ptr = instruction_pointer;
				// 		A.instruction = "op_add";
				// 		A.value = new_tk.token_Name;
				// 		A.token = cur_token;
				// 		instruction_list.insert(ittt, A);
				// 		instruction_pointer += 1;
				// 	}
				// }


				// recursive decent parser
				new_tk = token_list.front();
				token_list.pop_front();
				cur_token = new_tk.token_Type;

				cout << "Begin with Integer: " << new_tk.token_Type << endl;

				E(cur_token, new_tk, token_list, instruction_list, ittt, instruction_pointer);

				// new_tk = token_list.front();
				// token_list.pop_front();
				// cur_token = new_tk.token_Type;				
				
				cout << "End with semicolon: " << new_tk.token_Type << endl;

				flag = match(cur_token, TK_SEMICOLON);
				if (flag) {
					decoraded_nodes B;
					B.instruction_ptr = instruction_pointer;
					B.instruction = "op_pop";
					B.value = left_hand_side;
					instruction_list.insert(ittt, B);
					instruction_pointer += 1;
				}
			}
		}
	}

}

void E(int & cur_token, Token & new_tk, std::list<Token>& token_list, std::list<decoraded_nodes>& instruction_list, std::list<decoraded_nodes>::iterator & ittt, int & instruction_pointer) {
	T(cur_token, new_tk, token_list, instruction_list, ittt, instruction_pointer);
	E_prime(cur_token, new_tk, token_list, instruction_list, ittt, instruction_pointer);
}

void T(int & cur_token, Token & new_tk, std::list<Token>& token_list, std::list<decoraded_nodes>& instruction_list, std::list<decoraded_nodes>::iterator & ittt, int & instruction_pointer) {
	F(cur_token, new_tk, token_list, instruction_list, ittt, instruction_pointer);
	T_prime(cur_token, new_tk, token_list, instruction_list, ittt, instruction_pointer);
}

void E_prime(int & cur_token, Token & new_tk, std::list<Token>& token_list, std::list<decoraded_nodes>& instruction_list, std::list<decoraded_nodes>::iterator & ittt, int & instruction_pointer) {

	cout << "cur token in E': " << cur_token <<endl;

	int save = cur_token;
	Token save_token = new_tk;
	
	if (match(cur_token, TK_PLUS) ) {

		new_tk = token_list.front();
		token_list.pop_front();
		cur_token = new_tk.token_Type;

		if (match(cur_token, TK_SEMICOLON)) {
			T(cur_token, new_tk, token_list, instruction_list, ittt, instruction_pointer);
			decoraded_nodes A;
			A.instruction_ptr = instruction_pointer;
			A.instruction = "op_add";
			A.value = new_tk.token_Name;
			A.token = cur_token;
			instruction_list.insert(ittt, A);
			instruction_pointer += 1;
		} else {
			T(cur_token, new_tk, token_list, instruction_list, ittt, instruction_pointer);
			decoraded_nodes A;
			A.instruction_ptr = instruction_pointer;
			A.instruction = "op_add";
			A.value = save_token.token_Name;
			A.token = save;
			instruction_list.insert(ittt, A);
			instruction_pointer += 1;
		}
		E_prime(cur_token, new_tk, token_list, instruction_list, ittt, instruction_pointer);

	} else if (match(cur_token, TK_MINUS)) {

		decoraded_nodes B;
		B.instruction_ptr = instruction_pointer;
		B.instruction = "op_sub";
		B.value = new_tk.token_Name;
		B.token = cur_token;
		instruction_list.insert(ittt, B);
		instruction_pointer += 1;

		T(cur_token, new_tk, token_list, instruction_list, ittt, instruction_pointer);
		E_prime(cur_token, new_tk, token_list, instruction_list, ittt, instruction_pointer);

	} else {
		return;
	}
}

void F(int & cur_token, Token & new_tk, std::list<Token>& token_list, std::list<decoraded_nodes>& instruction_list, std::list<decoraded_nodes>::iterator & ittt, int & instruction_pointer) {

	if (match(cur_token, TK_ID)) {
		decoraded_nodes I;
		I.instruction_ptr = instruction_pointer;
		I.instruction = "op_pop";
		I.value = new_tk.token_Name;
		I.token = cur_token;
		instruction_list.insert(ittt, I);
		instruction_pointer += 1;

		new_tk = token_list.front();
		token_list.pop_front();
		cur_token = new_tk.token_Type;				

		return;

	} else if (match(cur_token, TK_INTEGER_LIT)) {
		
		decoraded_nodes I;
		I.instruction_ptr = instruction_pointer;
		I.instruction = "op_push";
		I.value = new_tk.token_Name;
		I.token = cur_token;
		instruction_list.insert(ittt, I);
		instruction_pointer += 1;

		new_tk = token_list.front();
		token_list.pop_front();
		cur_token = new_tk.token_Type;				
	
		return;

	} else {
		return;
	}

}

void T_prime(int & cur_token, Token & new_tk, std::list<Token>& token_list, std::list<decoraded_nodes>& instruction_list, std::list<decoraded_nodes>::iterator & ittt, int & instruction_pointer) {
	return;
}

void print_parser_output(std::list<decoraded_nodes> instruction_list) {
	const char separator    = ' ';
    const int nameWidth     = 15;
	
	std::cout << left << std::setw(nameWidth) << std::setfill(separator) << std::setfill('-') << std::setw(85) << "-";
    std::cout << endl;
	std::cout << "Parser Output" <<endl;
   	std::cout << left << std::setw(nameWidth) << std::setfill(separator) << std::setfill('-') << std::setw(85) << "-";
    std::cout << endl;

	std::cout << left << std::setw(nameWidth) << std::setfill(separator) << "Instr PTR";
	std::cout << "| ";
    std::cout << left << std::setw(nameWidth) << std::setfill(separator) << "Token";
    std::cout << "| ";
    std::cout << left << std::setw(nameWidth) << std::setfill(separator) << "Instr";
    std::cout << "| ";
    std::cout << left << std::setw(nameWidth) << std::setfill(separator) << "Value";
    std::cout << endl;

   	std::cout << left << std::setw(nameWidth) << std::setfill(separator) << std::setfill('-') << std::setw(85) << "-";
    std::cout << endl;

    int i = 0;
    for (std::list<decoraded_nodes>::iterator it=instruction_list.begin(); it != instruction_list.end(); ++it) {
    	i += 1;
    	std::cout << left << std::setw(nameWidth) << std::setfill(separator) << it->instruction_ptr;
	    std::cout << "| ";
	    std::cout << left << std::setw(nameWidth) << std::setfill(separator) << it->token;
	    std::cout << "| ";
	    std::cout << left << std::setw(nameWidth) << std::setfill(separator) << it->instruction;
	    std::cout << "| ";
	    std::cout << left << std::setw(nameWidth) << std::setfill(separator) << it->value;

	    std::cout << endl;
    }

   	std::cout << left << std::setw(nameWidth) << std::setfill(separator) << std::setfill('-') << std::setw(85) << "-";
    std::cout << endl;
}

void print_symbol_table(std::list<sym_table> syma_table) {
	const char separator    = ' ';
    const int nameWidth     = 15;
	
	std::cout << left << std::setw(nameWidth) << std::setfill(separator) << std::setfill('-') << std::setw(85) << "-";
    std::cout << endl;
	std::cout << "Symbol Table" <<endl;
   	std::cout << left << std::setw(nameWidth) << std::setfill(separator) << std::setfill('-') << std::setw(85) << "-";
    std::cout << endl;

	std::cout << left << std::setw(nameWidth) << std::setfill(separator) << "Type";
	std::cout << "| ";
    std::cout << left << std::setw(nameWidth) << std::setfill(separator) << "Name";
    std::cout << "| ";
    std::cout << left << std::setw(nameWidth) << std::setfill(separator) << "Value";
    std::cout << "| ";
    std::cout << left << std::setw(nameWidth) << std::setfill(separator) << "Address";
    std::cout << endl;

   	std::cout << left << std::setw(nameWidth) << std::setfill(separator) << std::setfill('-') << std::setw(85) << "-";
    std::cout << endl;

    int i = 0;
    for (std::list<sym_table>::iterator it=syma_table.begin(); it != syma_table.end(); ++it) {
    	i += 1;
    	std::cout << left << std::setw(nameWidth) << std::setfill(separator) << it->Type;
	    std::cout << "| ";
	    std::cout << left << std::setw(nameWidth) << std::setfill(separator) << it->Name;
	    std::cout << "| ";
	    std::cout << left << std::setw(nameWidth) << std::setfill(separator) << it->Value;
	    std::cout << "| ";
	    std::cout << left << std::setw(nameWidth) << std::setfill(separator) << it->Address;

	    std::cout << endl;
    }

   	std::cout << left << std::setw(nameWidth) << std::setfill(separator) << std::setfill('-') << std::setw(85) << "-";
    std::cout << endl;
}



