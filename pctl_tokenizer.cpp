#include <string>
#include "pctl_tokenizer.h"
#include <iostream>
enum tokenkindt {PROB, UNTIL, IDENTIFIER, NOT, AND, OR};
struct tokent {tokenkindt kind;};

void token(tokent token)
{
	switch(token.kind){
	case PROB: std::cout<<"prob \n";
	case UNTIL: std::cout<<"until \n";
	case IDENTIFIER: std::cout<<"IDENTIFIER \n";
	case NOT: std::cout<<"NOT\n";
	case AND: std::cout<<"AND\n";
	case OR: std::cout<<"OR\n";
	default:;

	}
}

void pctl_tokenizer(std::string input)
{
	tokent t;
	std::string::iterator pos =input.begin();
	while(pos!=input.end())
	{
		switch(*pos)
		{
			case '!': t.kind = NOT; token(t);
			case '&': t.kind = AND; token(t);
			case '|': t.kind = OR; token(t);
			default:;


		}
	}
}