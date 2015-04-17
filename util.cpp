#include <iostream>
#include <string>
#include <iomanip>
#include <list>

void print_scanner_output(list<Token> token_List) {
	const char separator    = ' ';
    const int nameWidth     = 15;
	
	cout << left << setw(nameWidth) << setfill(separator) << setfill('-') << setw(85) << "-";
    cout << endl;
	cout << "SCANNER" <<endl;
   	cout << left << setw(nameWidth) << setfill(separator) << setfill('-') << setw(85) << "-";
    cout << endl;

	cout << left << setw(nameWidth) << setfill(separator) << "Count";
	cout << "| ";
    cout << left << setw(nameWidth) << setfill(separator) << "Token Type";
    cout << "| ";
    cout << left << setw(nameWidth) << setfill(separator) << "Token Name";
    cout << "| ";
    cout << left << setw(nameWidth) << setfill(separator) << "Line Number";
    cout << "| ";
    cout << left << setw(nameWidth) << setfill(separator) << "Column Number";
    cout << endl;

   	cout << left << setw(nameWidth) << setfill(separator) << setfill('-') << setw(85) << "-";
    cout << endl;

    int i = 0;
    for (std::list<Token>::iterator it=token_List.begin(); it != token_List.end(); ++it) {
    	i += 1;
    	cout << left << setw(nameWidth) << setfill(separator) << i;
	    cout << "| ";
	    cout << left << setw(nameWidth) << setfill(separator) << TokenType(it->token_Type);
	    cout << "| ";
	    cout << left << setw(nameWidth) << setfill(separator) << it->token_Name;
	    cout << "| ";
	    cout << left << setw(nameWidth) << setfill(separator) << it->line_num;
	    cout << "| ";
	    cout << left << setw(nameWidth) << setfill(separator) << it->col_num;

	    cout << endl;
    }

   	cout << left << setw(nameWidth) << setfill(separator) << setfill('-') << setw(85) << "-";
    cout << endl;

}