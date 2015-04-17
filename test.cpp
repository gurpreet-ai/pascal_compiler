// http://www.codeproject.com/Articles/833206/Lexical-analyzer-an-example

#include <iostream>
#include <string>
#include "sym_table.h"
#include "token.h"

using namespace std;
enum Test
{
    hi, //0
    bye, //1
    count //2
};

int main () {
	// SymbolTable one;
	// int a = one.get_address();
	// cout << a;
	cout << static_cast<Test>(1) <<endl;

	return 0;
}







