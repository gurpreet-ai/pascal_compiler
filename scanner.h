/* 	The Scanner
	
	The scanner's job is to read the source file one character at a time. 
	For each character, it keeps track of the line and character position 
	where the character was found. Each time the scanner is called, it reads 
	the next character from the file and returns it.

*/

#include <fstream>
#include <String>

class Scanner
{

private:
	std::string file_name;
	std::ofstream raw_source_file;
	

public:
	Scanner(std::string f_n);
	~Scanner();
	
	void read_next();
	void print();

};