#include "statmodelchecker.h"
#include "markov_chain.h"
#include "pctl_parser.h"








 resultt tracecheck(pctlformula f, tracet)
{
	allstates = get_all_states();
	
	switch (f.t.kind)
	{
	 case IDENTIFIER: return tracecheckIdentifier(f); break;
     case UNTIL: return tracecheckUNTIL(tracecheck(f.children[0]), tracecheck(f.children[1]) ); break;
	 case AND: return tracecheckAND(check(f.children[0]), tracecheck(f.children[1])); break;
 	 case OR:  return tracecheckOR(check(f.children[0]), tracecheck(f.children[1])); break;
// 	 case PROB: ;break;
	 case NOT: return tracecheckNOT(check(f.children[0])); break;

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