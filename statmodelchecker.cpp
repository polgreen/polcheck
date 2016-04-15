#include "statmodelchecker.h"
#include "markov_chain.h"
#include "pctl_parser.h"
#include "propcheck.h"



void printtrace_index(trace_index trace)
{
	for(const auto &s: trace) 
    {
        std::cout<<s<<" ";
    }
    std::cout<<"\n";
}

trace_index tracecheckIDENTIFIER (tracet trace, pctlformula f)
{
	trace_index result;
	for(unsigned i=0; i<trace.size(); i++)
	{
		if(trace.at(i).label == f.t.label)
		{
			result.push_back(i);
		}
	} 
	std::cout<<"IDENTIFIER: ";
	printtrace_index(result);
	return result; 
}

trace_index tracecheckAND(trace_index set1, trace_index set2)
{
	trace_index result;
	for(const auto & s1 : set1)
     {
      if(std::find(set2.begin(), set2.end(), s1)!=set2.end())
         result.push_back(s1);
      }
     std::cout<<"AND: ";
	printtrace_index(result);
	 return result;
}

trace_index tracecheckOR(trace_index set1, trace_index set2)
{
 for(const auto & s1 : set1)
 {
   if(std::find(set2.begin(), set2.end(), s1)==set2.end())
     set2.push_back(s1);
 } 
	std::cout<<"OR: ";
	printtrace_index(set2);
 return set2;
}

trace_index tracecheckNOT(trace_index set1, tracet trace)
{
	bool found = false;
	trace_index result;
	for(unsigned i=0; i<trace.size(); i++)
	{
		for( const auto & s1: set1)
		{
			if (s1==i) 
				{found=true;}
		}
		if(found==false) 
			{result.push_back(i);}
	}
	std::cout<<"NOT: ";
	printtrace_index(result);
	return result;
}


trace_index tracecheckUNTIL(trace_index set1, trace_index set2)
{
	
}


trace_index tracecheck(pctlformula f, tracet t)
{

	
	switch (f.t.kind)
	{
	 case IDENTIFIER: return tracecheckIDENTIFIER(t, f); break;	
//     case UNTIL: return tracecheckUNTIL(tracecheck(f.children[0]), tracecheck(f.children[1]) ); break;
	 case AND: return tracecheckAND(tracecheck(f.children[0],t), tracecheck(f.children[1],t)); break;
 	 case OR:  return tracecheckOR(tracecheck(f.children[0],t), tracecheck(f.children[1],t)); break;
// 	 case PROB: ;break;
	 case NOT: return tracecheckNOT(tracecheck(f.children[0],t),t); break;
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