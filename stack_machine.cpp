#include <iostream>
#include <string>
#include <iomanip>
#include <list>
#include <stack>
#include <iterator>
#include <algorithm>

void stackMachine(std::list<decoraded_nodes> instruction_list, std::list<sym_table> lst_of_identifiers) {
	int instruction_pointer = 0;

	// decoraded_nodes cur_instruc;

	std::stack<string> instruc_stack;
	std::list<sym_table>::iterator itt;
				
	int i_size = instruction_list.size();
	int l_i_size = lst_of_identifiers.size();

	for (std::list<decoraded_nodes>::iterator cur_instruc = instruction_list.begin(), 
		end = instruction_list.end(); 
		cur_instruc != end; ++cur_instruc) {

		if (cur_instruc->instruction == "op_push") {
			if (cur_instruc->token == TK_ID) {
			
				std::list<sym_table> copy_sym_tbl = lst_of_identifiers;									// copy of the original
				
				lst_of_identifiers.clear();

				itt = lst_of_identifiers.begin();

				for (int j = 0; j < l_i_size; j++) {
					sym_table a = copy_sym_tbl.front();
					copy_sym_tbl.pop_front();

					if (a.Name == cur_instruc->value) {
						instruc_stack.push(a.Value);
						lst_of_identifiers.insert(itt, a);
					} else {
						lst_of_identifiers.insert(itt, a);
					}
				}
			
			} else {
				instruc_stack.push(cur_instruc->value);
			}
		}else if (cur_instruc->instruction == "op_pop") {

			string poped = instruc_stack.top();
			instruc_stack.pop();

			std::list<sym_table> copy_sym_tbl = lst_of_identifiers;									// copy of the original
			lst_of_identifiers.clear();
			itt = lst_of_identifiers.begin();

			for (int j = 0; j < l_i_size; j++) {
				sym_table a = copy_sym_tbl.front();
				copy_sym_tbl.pop_front();
					
				if (a.Name == cur_instruc->value) {
					a.Value = poped;
					lst_of_identifiers.insert(itt, a);

				} else {
					lst_of_identifiers.insert(itt, a);
				}
			}
		} else if (cur_instruc->instruction == "op_add") {
			int op1 = std::stoi(instruc_stack.top());
			instruc_stack.pop();
			int op2 = std::stoi(instruc_stack.top());
			instruc_stack.pop();

			int sum = op1 + op2;

			instruc_stack.push(std::to_string(sum));
		} else if (cur_instruc->instruction == "op_sub") {
			int op1 = std::stoi(instruc_stack.top());
			instruc_stack.pop();
			int op2 = std::stoi(instruc_stack.top());
			instruc_stack.pop();

			int sub = op2 - op1;
	
			instruc_stack.push(std::to_string(sub));
		} else if (cur_instruc->instruction == "op_multi") {
			int op1 = std::stoi(instruc_stack.top());
			instruc_stack.pop();
			int op2 = std::stoi(instruc_stack.top());
			instruc_stack.pop();

			int sub = op2 * op1;
	
			instruc_stack.push(std::to_string(sub));
		} else if (cur_instruc->instruction == "op_greater") {
			int op1 = std::stoi(instruc_stack.top());
			instruc_stack.pop();
			int op2 = std::stoi(instruc_stack.top());
			instruc_stack.pop();

			int op_g = (op2 > op1);
	
			instruc_stack.push(std::to_string(op_g));
		} else if (cur_instruc->instruction == "op_jfalse") {
	        int flag = std::stoi(instruc_stack.top());
			instruc_stack.pop();
			if (flag == 0) {
				int go_to = std::stoi(cur_instruc->value);
				cout << go_to;
				cout << cur_instruc->instruction_ptr;
				int a = cur_instruc->instruction_ptr - go_to;
				cout << a;
				
				while (a > 0) {
					cur_instruc--;
					a -= 1;
				} 
				// std::advance(cur_instruc, a);
			}

		}


	}

	// for (int i = 0; i < i_size; i++) {
	// 	cur_instruc = instruction_list.front();
	// 	instruction_list.pop_front();

	// 	// cout << cur_instruc->instruction_ptr <<" ";
	// 	// cout << cur_instruc->value <<" ";
	// 	// cout << cur_instruc->token <<" ";
	// 	// cout << cur_instruc->instruction <<endl;
	// 	// address, type, name, value

	// 	if (cur_instruc->instruction == "op_push") {
	// 		if (cur_instruc->token == TK_ID) {
			
	// 			std::list<sym_table> copy_sym_tbl = lst_of_identifiers;									// copy of the original
				
	// 			lst_of_identifiers.clear();

	// 			itt = lst_of_identifiers.begin();

	// 			for (int j = 0; j < l_i_size; j++) {
	// 				sym_table a = copy_sym_tbl.front();
	// 				copy_sym_tbl.pop_front();

	// 				if (a.Name == cur_instruc->value) {
	// 					instruc_stack.push(a.Value);
	// 					lst_of_identifiers.insert(itt, a);
	// 				} else {
	// 					lst_of_identifiers.insert(itt, a);
	// 				}
	// 			}
			
	// 		} else {
	// 			instruc_stack.push(cur_instruc->value);
	// 		}
	// 	} else if (cur_instruc->instruction == "op_pop") {

	// 		string poped = instruc_stack.top();
	// 		instruc_stack.pop();

	// 		std::list<sym_table> copy_sym_tbl = lst_of_identifiers;									// copy of the original
	// 		lst_of_identifiers.clear();
	// 		itt = lst_of_identifiers.begin();

	// 		for (int j = 0; j < l_i_size; j++) {
	// 			sym_table a = copy_sym_tbl.front();
	// 			copy_sym_tbl.pop_front();
					
	// 			if (a.Name == cur_instruc->value) {
	// 				a.Value = poped;
	// 				lst_of_identifiers.insert(itt, a);

	// 			} else {
	// 				lst_of_identifiers.insert(itt, a);
	// 			}
	// 		}
	// 	} else if (cur_instruc->instruction == "op_add") {
	// 		int op1 = std::stoi(instruc_stack.top());
	// 		instruc_stack.pop();
	// 		int op2 = std::stoi(instruc_stack.top());
	// 		instruc_stack.pop();

	// 		int sum = op1 + op2;

	// 		instruc_stack.push(std::to_string(sum));
	// 	} else if (cur_instruc->instruction == "op_sub") {
	// 		int op1 = std::stoi(instruc_stack.top());
	// 		instruc_stack.pop();
	// 		int op2 = std::stoi(instruc_stack.top());
	// 		instruc_stack.pop();

	// 		int sub = op2 - op1;
	
	// 		instruc_stack.push(std::to_string(sub));
	// 	} else if (cur_instruc->instruction == "op_multi") {
	// 		int op1 = std::stoi(instruc_stack.top());
	// 		instruc_stack.pop();
	// 		int op2 = std::stoi(instruc_stack.top());
	// 		instruc_stack.pop();

	// 		int sub = op2 * op1;
	
	// 		instruc_stack.push(std::to_string(sub));
	// 	} else if (cur_instruc->instruction == "op_greater") {
	// 		int op1 = std::stoi(instruc_stack.top());
	// 		instruc_stack.pop();
	// 		int op2 = std::stoi(instruc_stack.top());
	// 		instruc_stack.pop();

	// 		int sub = (op2 > op1);
	
	// 		instruc_stack.push(std::to_string(sub));
	// 	} else if (cur_instruc->instruction == "op_jfalse") {
	//         int flag = std::stoi(instruc_stack.top());
	// 		instruc_stack.pop();
	// 		if (flag == 0) {
	// 			cout << "you've gotta go back";
	// 		}

	// 	}
	// }

	// for (int i = 0; i < instruc_stack.size(); ++i)
	// {
	// 	cout << instruc_stack.top();
	// 	instruc_stack.pop();
	// }

	print_symbol_table(lst_of_identifiers);

}














