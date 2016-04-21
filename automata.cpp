#include <vector>
#include <set>
#include "statmodelchecker.h"
#include "automata.h"
#include <iostream>
#include "markov_chain.h"
#include <string>
#include <sstream>
#include <fstream>
#include <cstdlib>


std::string ssystem (const char *command) {
    char tmpname [L_tmpnam];
    std::tmpnam ( tmpname );
    std::string scommand = command;
    std::string cmd = scommand + " >> " + tmpname;
    std::system(cmd.c_str());
    std::ifstream file(tmpname, std::ios::in );
    std::string result;
        if (file) {
      while (!file.eof()) result.push_back(file.get());
          file.close();
    }
    remove(tmpname);
    return result;
}

void ltlstring (pctlformula f, std::string& output)
{

 switch(f.t.kind)
 {
 case IDENTIFIER: output+=" ";
 		output+= f.t.label; output+=" ";  break;
 case UNTIL: output+="("; 
 			ltlstring(f.children[0], output); 
 			output+=" U ";
 			ltlstring(f.children[1], output);
 			output+=")";
 			break;

 case BUNTIL:std::cout<<"LTL2BA does not do bounded until \n"; break;
 case AND:  output+="("; ltlstring(f.children[0], output); output+=" && "; ltlstring(f.children[1], output); output+=")";break;
 case OR:    output+= "("; ltlstring(f.children[0],output); output+= " || "; ltlstring(f.children[1],output); output+= ")"; break;
 case PROB: ;break;
 case NOT: output+="!"; ltlstring(f.children[0],output); break;
 case LP: output+="("; break;
 case RP: output+=")"; break;
 case SP: output+=" "; break;	
 case FI: output+="<> "; ltlstring(f.children[0],output); break;
 case GL: output+="[] "; ltlstring(f.children[0],output); break;
 case X: output+="X"; ltlstring(f.children[0],output); break;
 case IMPLIES: output+="->"; break;

 default:;
 }

}


void parsepctlformula(pctlformula f)
{
	std::string output;
	std::string result;
	std::string command ("./ltl2ba-1.2b1/ltl2ba -f \"");
	ltlstring(f, output);
	command+=output;
	command+="\"";
	//system(command.c_str());
	result = ssystem(command.c_str());
	std::cout<<result;

}


automata parseautomata(std::string A)
{
	std::string accept = "accept_";
	std::string state = "T0_";






}





//witness automata for Fa, where a=label 0
automata get_automata()
{	
	automata A;
	automata_state a0, a1;
	a0.successors.resize(2);
	a1.successors.resize(2);
	a0.successors[0].insert(1);
	a0.successors[1].insert(0);
	a0.accepting=false;
	a1.successors[0].insert(1);
	a1.successors[1].insert(1);
	a1.accepting=true;
	A.push_back(a0);
	A.push_back(a1);
return A;
}

//get counterexample automata, i.e. automata for G!a
automata get_Cautomata()
{	
	automata A;
	automata_state a0, a1;
	a0.successors.resize(2);
	a1.successors.resize(2);
	a0.successors[0].insert(1);
	a0.successors[1].insert(0);
	a0.accepting=true;
	a1.successors[0].insert(1);
	a1.successors[1].insert(1);
	a1.accepting=false;
	A.push_back(a0);
	A.push_back(a1);
return A;
}



resultt checkautomata(tracet trace)
{
	automata A, C;
	A = get_automata();
	C = get_Cautomata();
	
	std::set<unsigned> current, next, currentC, nextC;
	current.insert(0);
	currentC.insert(0);


	for(const auto& st: trace)
	{	
		
		for(const auto & l: st.label)
		{
			//take one step in witness automata
			for(const auto & sa : current)
			{
				if(l<A[sa].successors.size()){
				std::set<unsigned> suc = A[sa].successors[l];
				next.insert(suc.begin(), suc.end());
				}
				else
				{std::cout<<"error, label is bigger than size of successor set";
				return UNKNOWN;}
			}
			//take one step in counterexample automata
			for(const auto & saC : currentC)
			{
				if(l<C[saC].successors.size()){
				std::set<unsigned> sucC = C[saC].successors[l];
				nextC.insert(sucC.begin(), sucC.end());
				}
				else
				{std::cout<<"error, label is bigger than size of successor set";
				return UNKNOWN;}
			}
		}
		current=next;
		currentC=nextC;
	}

//check if traces finish in accepting states
	for(const auto & scC: currentC)
	{
		if(C[scC].accepting)
		{return FAIL;}
	}

	for(const auto & sc: current)
	{
		if(A[sc].accepting)
		{return PASS;}
	}


return UNKNOWN;
}






