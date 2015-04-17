/*  Symbol Table Data structure 
	Each identifier in a program's source code is associated with information relating to its declaration.
	Symbol Table contains all the identifiers in the source code.
*/

#include <iostream>
#include <string>

using namespace std;

class SymbolTable
{
public:
	// constructor
	SymbolTable(	SymbolTable *LF = NULL,
				std::string NM = "",
				std::string TP = "", 
				int TT = 0,
				int ADDR = 0) {
		link_field = LF;						
		name = NM;
		type = TP;
		token_type = TT;
		address = ADDR;
	}										

	// SETTER FUNCTIONS
	void set_link(SymbolTable *link){ link_field = link; }
	void set_name(std::string NM) 	{ name = NM; 		 }
	void set_type(std::string TP) 	{ type = TP; 		 }
	void set_token_type(int TT) 	{ token_type = TT;   }
	void set_addr(int ADDR)	 		{ address = ADDR; 	 }

	// GETTER FUNCTIONS
	SymbolTable * get_link(){ return link_field; }
	std::string get_name() 	{ return name; 		 }
	std::string get_type() 	{ return type; 		 }
	int get_token_type()  	{ return token_type; }
	int get_address() 		{ return address; 	 }

private:
	SymbolTable *link_field;											// link to the next field
	std::string name;													// KEY - name of the identifier
	std::string type;													// type of the identifier
	int token_type;														// token of the identifier
	int address;														// address of the identifier
};

// Symbol Table Toolkit
void table_head_insert(SymbolTable*& head_ptr, std::string NM, std::string TY, int T_TY, int addr);
void table_insert(SymbolTable* previous_ptr, std::string NM, std::string TY, int T_TY, int addr);






