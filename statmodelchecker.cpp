#include "markov_chain.h"
#include "pctl_parser.h"
satset allstates;




satset allstatesexcept(satset s, satset allstates)
{
	std::vector<statet>::iterator i;
	for( i = allstates.begin(); i!=allstates.end(); i++)
	{
	 if(std::find(s.begin(),s.end(),*i)!=s.end())
		{allstates.erase(i);}	
	}
	return allstates;
}

satset checkIdentifier(pctlformula f)
{
	satset s;
	if(f.t.kind!= IDENTIFIER)
	{std::cout<<"ERROR: checkIdentifier called with a pctlformula that is not an IDENTIFIER \n";}
	return s;
}

satset checkUntil (satset f1, satset f2)
{	
	satset s;
	satset s_no;
	satset s_yes;
	bool done = false;
	while(done==false)
	{

	}
	return s;
}

satset checkAnd(satset f1, satset f2)
{	
	satset s;
	std::vector<statet>::iterator i;
	for(i=f2.begin(); i!=f2.end(); i++)
	{
	 if(std::find(f1.begin(),f1.end(),*i)!=f1.end())
	 {	s.push_back(*i);}
	}
	return s;
}

satset checkOr(satset f1, satset f2)
{
	f1.insert(f1.end(),f2.begin(),f2.end());
	
	return f1;
}


satset check(pctlformula f)
{
	switch (f.t.kind)
	{
	 case IDENTIFIER: return checkIdentifier(f); break;
     case UNTIL: return checkUntil(check(f.children[0]), check(f.children[1]) ); break;
	 case AND: return checkAnd(check(f.children[0]), check(f.children[1])); break;
 	 case OR:  return checkOr(check(f.children[0]), check(f.children[1])); break;
  	 case PROB: ;break;
 	 case NOT: return allstatesexcept(check(f.children[0]), allstates); break;

 	 case GT: ;break;
 	 case LT: ;break;
 	 case EQ: ;break;
 	 case LP: ; break;
 	 case RP: ; break;
 	 case SP: ; break;	
 	 case FI: ; break;
 	 case GL: ; break;
 	 case X: ; break;
 	 case MIN: ; break;
 	 case MAX: ; break;
 	 case QUE: ; break;
 	 case IMPLIES: ; break;
 	 case GE: ; break;
 	 case LE: ; break;
 	 default:;

	}

}