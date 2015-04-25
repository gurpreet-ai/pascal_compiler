#include <iostream>
#include <string>
#include <iomanip>
#include <list>
#include "token.h"
#include "symbol_table.h"
using namespace std;

void print_scanner_output(list<Token> token_List) {
	const char separator    = ' ';
    const int nameWidth     = 15;
	
	std::cout << left << std::setw(nameWidth) << std::setfill(separator) << std::setfill('-') << std::setw(85) << "-";
    std::cout << endl;
	std::cout << "SCANNER" <<endl;
   	std::cout << left << std::setw(nameWidth) << std::setfill(separator) << std::setfill('-') << std::setw(85) << "-";
    std::cout << endl;

	std::cout << left << std::setw(nameWidth) << std::setfill(separator) << "Count";
	std::cout << "| ";
    std::cout << left << std::setw(nameWidth) << std::setfill(separator) << "Token Type";
    std::cout << "| ";
    std::cout << left << std::setw(nameWidth) << std::setfill(separator) << "Token Name";
    std::cout << "| ";
    std::cout << left << std::setw(nameWidth) << std::setfill(separator) << "Line Number";
    std::cout << "| ";
    std::cout << left << std::setw(nameWidth) << std::setfill(separator) << "Column Number";
    std::cout << endl;

   	std::cout << left << std::setw(nameWidth) << std::setfill(separator) << std::setfill('-') << std::setw(85) << "-";
    std::cout << endl;

    int i = 0;
    for (std::list<Token>::iterator it=token_List.begin(); it != token_List.end(); ++it) {
    	i += 1;
    	std::cout << left << std::setw(nameWidth) << std::setfill(separator) << i;
	    std::cout << "| ";
	    std::cout << left << std::setw(nameWidth) << std::setfill(separator) << TokenType(it->token_Type);
	    std::cout << "| ";
	    std::cout << left << std::setw(nameWidth) << std::setfill(separator) << it->token_Name;
	    std::cout << "| ";
	    std::cout << left << std::setw(nameWidth) << std::setfill(separator) << it->line_num;
	    std::cout << "| ";
	    std::cout << left << std::setw(nameWidth) << std::setfill(separator) << it->col_num;

	    std::cout << endl;
    }

   	std::cout << left << std::setw(nameWidth) << std::setfill(separator) << std::setfill('-') << std::setw(85) << "-";
    std::cout << endl;

}
