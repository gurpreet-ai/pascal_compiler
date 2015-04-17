// http://www.codeproject.com/Articles/833206/Lexical-analyzer-an-example

#include <iostream>
#include <string>
#include "sym_table.h"
#include "token.h"
#include "node.h"

using namespace std;

int main () {
	// SymbolTable one;
	// int a = one.get_address();
	// cout << a;
	// cout << static_cast<Test>(1) <<endl;
	node a;
	a.m_data_field(10);
	cout << a.m_data_field;

	return 0;
}







