#include <iostream.h>
#include <conio.h>
#include <fstream.h>
#include <stdlib.h>

char ch;
ifstream rrr("data.txt"); // create a file data.txt and save any expression to read from e.g  a=b+c
int flag=0;

void expression(void);
void term(void);
void primary(void);
void variable(void);
void sublist(void);
void letter(void);
void assignment(void);
void number(void);
void identifier(void);

void main ()
{

	clrscr();
	assignment();

	if (flag==1)
		cout<<"\nREJECTED";
	else
		cout<<"ACCEPTED";
	getch();

}

//-----------------------------------------------------//

void assignment(void)
{
	rrr.get(ch);
	variable();

     //	rrr.get(ch);
	if (ch != '=')
	{
		cout<<"Error";
		flag=0;
	}
	else
		rrr.get(ch);
		expression();
}

/////////////////////////////////////////////////
void expression(void)
{
	term();

	while(ch=='+' || ch=='-')
	{
		rrr.get(ch);
		term();
	}

}

//////////////////////////////////////////////////////
void term(void)
{

	primary();
      //rrr.get(ch);
	while(ch=='*' || ch=='/')
	{
		rrr.get(ch);
		primary();
	}


}

//////////////////////////////////////////////////////
void primary(void)
{


	if (ch>=65 && ch<=116)

		variable();

	else if(ch>=48 && ch<=57)

		number();

	else if (ch=='(')

	{
		rrr.get(ch);
		expression();

	      //	rrr.get(ch);
		if (ch==')')
			rrr.get(ch);
		else
		{
			cout<<"Missing )";
			flag=1;
		}
	}

	else
	{
		cout<<"Missing (";
		flag=1;
	}
}

////////////////////////////////////////////////////

void variable(void)
{

	identifier();
	rrr.get(ch);
	if (ch=='[')
	{
		rrr.get(ch);
		sublist();
	      //	rrr.get(ch);
		if (ch==']')
		{
			rrr.get(ch);
			return;
		}
		else
		{
			cout<<"Missing ]";
			flag=1;
		}
	}

}

////////////////////////////////////////////////////

void sublist(void)
{

	expression();

	while(ch==',')
	{
		rrr.get(ch);
		expression();
	}

}

////////////////////////////////////////////////////

void identifier(void)
{
	letter();
}

///////////////////////////////////////////////////
void letter(void)
{

	if(ch>=65 && ch<=116)
		return;
	else
	{
		cout<<"Error";
		flag=1;
	}
}

///////////////////////////////////////////////////

void number(void)
{
	if(ch>=48 && ch<=57)
	{
		rrr.get(ch);
		return;
	}
	else
	{
		cout<<"Error";
		flag=1;
	}
}