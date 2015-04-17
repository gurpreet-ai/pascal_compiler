/*
	Symbol table function definitions
*/ 

#include "sym_table.h"

void table_head_insert(SymbolTable*& head_ptr, std::string NM, std::string TP, int TK_TY, int addr) {
	head_ptr = new SymbolTable(head_ptr, NM, TP, TK_TY, addr);
}
l
void table_insert(SymbolTable* previous_ptr, std::string NM, std::string TY, int T_TY, int addr) {
	SymbolTable *insert_ptr;
	insert_ptr = new SymbolTable(previous_ptr->get_link(), NM, TY, T_TY, addr);
	previous_ptr->set_link(insert_ptr);
}
