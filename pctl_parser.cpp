#include "pctl_parser.h"
#include <vector>
#include <iostream>


void output(pctlformula f)
{
 switch(f.t.kind)
 {
 case IDENTIFIER: std::cout<< f.t.label; break;
 case UNTIL: output(f.children[0]); std::cout<< " U "; output(f.children[1]); break;
 case AND:  output(f.children[0]); std::cout<< " & "; output(f.children[1]); break;
 case OR:  output(f.children[0]); std::cout<< " | "; output(f.children[1]); break;
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
			//error
		} 

	}	

}

pctlformula parseconjunction(std::vector<tokent> &tokenseq)
{
	pctlformula f0;
	f0 = parseprimary(tokenseq);
	if(tokenseq.front().kind==AND)
	{
	pctlformula f1;
	tokenseq.erase(tokenseq.begin());
	f1 = parseconjunction(tokenseq);
	pctlformula f;
	f.t.kind = AND;
	f.children.resize(2);
	f.children[0] = f0;
	f.children[1] = f1;
	return f;
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
	f1 = parsedisjunction(tokenseq);
	pctlformula f;
	f.t.kind = OR;
	f.children.resize(2);
	f.children[0] = f0;
	f.children[1] = f1;
	return f;
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
	f1 = parsedisjunction(tokenseq);
	pctlformula f;
	f.t.kind = UNTIL;
	f.children.resize(2);
	f.children[0] = f0;
	f.children[1] = f1;
	return f;
	}
	else
	{
		return f0;
	}
}


pctlformula parseparenthesis(std::vector<tokent> &tokenseq)
{
	pctlformula f0;
	f0 = parseuntil(tokenseq);
	if(tokenseq.front().kind==LP)
	{
	pctlformula f1;
	tokenseq.erase(tokenseq.begin());
	f1 = parseconjunction(tokenseq);
	pctlformula f;
	f.t.kind = LP;
	f.children.resize(2);
	f.children[0] = f0;
	f.children[1] = f1;
	return f;
	}
	else
	{
		return f0;
	}

}

pctlformula parse (std::vector<tokent> &tokenseq)
{
return parseuntil(tokenseq);

}