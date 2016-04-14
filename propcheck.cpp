#include "markov_chain.h"
#include "pctl_parser.h"
#include <algorithm>
#include <iostream>


typedef satset::iterator stateiterator;

bool operator==(const statet &s1, const statet &s2)
{
 return s1.hasbus==s2.hasbus &&
        s1.clients==s2.clients;
}

void output_satset(satset s)
{
	   for (unsigned i=0; i<s.size(); i++)
        {
        	printstate(s.at(i));           
        }
       
}	


satset checkIdentifier(pctlformula f)
{
	satset s;
	if(f.t.kind!= IDENTIFIER)
	{std::cout<<"ERROR: checkIdentifier called with a pctlformula that is not an IDENTIFIER \n";}
	return s;
}

satset checkAND(satset set1, satset set2)
{
	satset result;
	for(const auto & s1 : set1)
 {
   if(std::find(set2.begin(), set2.end(), s1)!=set2.end())
     result.push_back(s1);
 }
return result;
}

satset checkOR(satset set1, satset set2)
{
 for(const auto & s1 : set1)
 {
   if(std::find(set2.begin(), set2.end(), s1)==set2.end())
     set2.push_back(s1);
 }
return set2;
}

satset checkNOT(satset set1)
{
	satset allstates = g_allstates;
	satset result;
	for(const auto & s1 : set1)
 {
	auto it = std::find(allstates.begin(), allstates.end(), s1);
	if(it != allstates.end()){
		using std::swap;
		swap(*it, allstates.back());
		allstates.pop_back();
	}
 }
 output_satset(allstates);
 return allstates;
}

satset checkUNTIL(satset set1, satset set2)
{
	satset R, R2, successors;
	R = set2;
	R2=R;
	bool done=false;
	while(done==false)
	{
		for(const auto & s1: set1)
		{
			successors = get_successor_states(s1);
			
			for(const auto & succ: successors)
				{	
					if(std::find(R.begin(), R.end(), succ)==R.end())
					 R2.push_back(succ);
				}					
		}
		if(R2==R)
			{done=true;}
		R=R2;
	}

 return checkNOT(R);

}




satset check(pctlformula f)
{
	
	switch (f.t.kind)
	{
	 case IDENTIFIER: return checkIdentifier(f); break;
//   case UNTIL: return checkUntil(check(f.children[0]), check(f.children[1]) ); break;
	 case AND: return checkAND(check(f.children[0]), check(f.children[1])); break;
 	 case OR:  return checkOR(check(f.children[0]), check(f.children[1])); break;
// 	 case PROB: ;break;
	 case NOT: return checkNOT(check(f.children[0])); break;

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