// http://www.codeproject.com/Articles/833206/Lexical-analyzer-an-example

#include <iostream>
#include <string>
#include <list>

using namespace std;

typedef struct {
    int instruction_ptr;
    int token;
    std::string instruction;
    std::string value;
} decoraded_nodes;

int main () {
	std::list<decoraded_nodes> instruction_list;
	std::list<decoraded_nodes>::iterator it;
	it = instruction_list.begin();

	decoraded_nodes a;
	a.instruction_ptr = 1;
	a.token = 1;
	a.instruction = "1";
	a.value = "2";

	decoraded_nodes b;
	b.instruction_ptr = 2;
	b.token = 1;
	b.instruction = "1";
	b.value = "1";

	decoraded_nodes c;
	c.instruction_ptr = 3;
	c.token = 1;
	c.instruction = "1";
	c.value = "3";

	decoraded_nodes cc;
	cc.instruction_ptr = 4;
	cc.token = 1;
	cc.instruction = "1";
	cc.value = "3";

	decoraded_nodes ccc;
	ccc.instruction_ptr = 5;
	ccc.token = 1;
	ccc.instruction = "1";
	ccc.value = "3";

	instruction_list.insert(it, a);
	instruction_list.insert(it, b);
	instruction_list.insert(it, c);
	instruction_list.insert(it, cc);
	instruction_list.insert(it, ccc);

	bool aa = false;
	int bb = 0;
	int x = 2;

	for (std::list<decoraded_nodes>::iterator cur_instruc = instruction_list.begin(), 
		end = instruction_list.end(); 
		cur_instruc != end; ++cur_instruc) {

		cout << "cur inst " << cur_instruc->instruction_ptr <<"\n";
		bb++;

		if (bb == 3) {
			while (x > 0) {
				cur_instruc--;
				cout << "cur inst " << cur_instruc->instruction_ptr <<" "; 
				x--;
			}
		}

		if (aa) {
			cur_instruc--;
			aa = false;
		} 
	}

	return 0;
}







