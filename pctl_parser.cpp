#include "pctl_parser.h"
#include <vector>
#include <iostream>


void output(pctlformula f)
{
 switch(f.t.kind)
 {
 case IDENTIFIER: std::cout<< f.t.label; break;
 case UNTIL:std::cout<<"("; output(f.children[0]); std::cout<< " U "; output(f.children[1]);std::cout<<")"; break;
case AND:  std::cout<<"("; output(f.children[0]); std::cout<< " & "; output(f.children[1]); std::cout<<")";break;
 case OR:    std::cout << "("; output(f.children[0]); std::cout<< " | "; output(f.children[1]); std::cout << ")"; break;
 case PROB: std::cout<<"P "; break;
 case NOT: std::cout<<"!"; break;
 case GT: std::cout<<">";break;
 case LT: std::cout<<"<";break;
 case EQ:std::cout<<"=";break;
 case LP: std::cout<<"("; break;
 case RP: std::cout<<")"; break;
 case SP: std::cout<<" "; break;	
 default:;
 }
}


pctlformula parseprimary(std::vector<tokent> &tokenseq)
{
	pctlformula f;
	if(tokenseq.front().kind==IDENTIFIER)
	{
		f.t = tokenseq.front();
		tokenseq.erase(tokenseq.begin());
		return f;
	}
	else if (tokenseq.front().kind==LP)
	{
		tokenseq.erase(tokenseq.begin());
		f = parse(tokenseq);
		if (tokenseq.front().kind == RP)
		{
			tokenseq.erase(tokenseq.begin());
			return f;
		}
		else{
			std::cout<< "missing right parenthesis";
		}
	}

	else if (!tokenseq.empty()){
		switch(tokenseq.front().kind){
				case UNTIL: std::cout<<"UNTIL must be preceeded by an identifier"; break;
				case AND: std::cout<<"AND must be preceeded by an identifier"; break;
				case OR: std::cout<<"OR must be preceeded by an identifier"; break;
				default: ;
			}
			
	}	
	else
		{std::cout<<"empty tokenseq";}

}

pctlformula parseconjunction(std::vector<tokent> &tokenseq)
{
	pctlformula f0;
	f0 = parseprimary(tokenseq);
	if(tokenseq.front().kind==AND)
	{
	 pctlformula f1;
	 tokenseq.erase(tokenseq.begin());
	 if(tokenseq.empty())
	 {
		std::cout<<"error. Expected identifier after AND";
	 }
	 else{
	  f1 = parseconjunction(tokenseq);
	  pctlformula f;
	  f.t.kind = AND;
	  f.children.resize(2);
	  f.children[0] = f0;
	  f.children[1] = f1;
	  return f;
	 }
	}
	else
	{
		return f0;
	}


}

pctlformula parsedisjunction(std::vector<tokent> &tokenseq)
{
	pctlformula f0;
	f0 = parseconjunction(tokenseq);
	if(tokenseq.front().kind==OR)
	{
	pctlformula f1;
	tokenseq.erase(tokenseq.begin());
	 if(tokenseq.empty())
	 {
		std::cout<<"error. Expected identifier after OR";
	 }
	 else{
	 f1 = parsedisjunction(tokenseq);
     pctlformula f;
	 f.t.kind = OR;
	 f.children.resize(2);
	 f.children[0] = f0;
	 f.children[1] = f1;
	 return f;
	 }
	} 
	else
	{
		return f0;
	}
}





pctlformula parseuntil(std::vector<tokent> &tokenseq)
{
	pctlformula f0;
	f0 = parsedisjunction(tokenseq);
	if(tokenseq.front().kind==UNTIL)
	{
	pctlformula f1;
	tokenseq.erase(tokenseq.begin());
	if(tokenseq.empty())
	 {
		std::cout<<"error. Expected identifier after UNTIL";
	 }
	else{
	 f1 = parsedisjunction(tokenseq);
	 pctlformula f;
	 f.t.kind = UNTIL;
	 f.children.resize(2);
	 f.children[0] = f0;
	 f.children[1] = f1;
	 return f;
	 }
	}
	else
	{
		return f0;
	}
}




pctlformula parse (std::vector<tokent> &tokenseq)
{
pctlformula f;
if(tokenseq.empty())
{
	std::cout<<"parse error: empty tokenseq";
}
else{
 f =  parseuntil(tokenseq);
  if(!tokenseq.empty())
  {
	std::cout<<"parse error: tokens after end of expression \n";
  }
 return f;
}
}