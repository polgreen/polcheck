#include <vector>
#include <set>
#include "statmodelchecker.h"
#include "automata.h"
#include <iostream>
#include "markov_chain.h"



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



	for(const auto & sc: current)
	{
		if(A[sc].accepting)
		{return PASS;}
	}
		for(const auto & scC: currentC)
	{
		if(C[scC].accepting)
		{return FAIL;}
	}



	/*
	//take a step in the witness automata	
	  for(const auto & sa: current)
	  {
	  	for(const auto & l: st.label)
	  	{
	  	std::set<unsigned> suc = A[sa].successors[l];
	  	 next.insert(suc.begin(), suc.end());
	  	}	
	  }
	  //take a step in the counterexample automata
	  for(const auto & saC: currentC)
	  {
	  	for(const auto & l: st.label)
	  	{
	  	std::set<unsigned> sucC = C[saC].successors[l];
	  	 nextC.insert(sucC.begin(), sucC.end());
	  	}	
	  }
	current=next;
	currentC=nextC;
	
	}
/*
 	for (const auto & w: current)
 	{if (A[w].accepting){return PASS;}}
 	for(const auto & c: currentC)
 	{if (C[c].accepting){return FAIL;}}

*/
return UNKNOWN;
}






