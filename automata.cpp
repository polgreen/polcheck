#include <vector>
#include <set>
#include "statmodelchecker.h"

struct automata_state{
	std::vector<std::set <unsigned> > successors; //successor vector indexed by label numbers
	bool accepting;}; 
typedef std::vector<automata_state> automata;


automata get_automata()
{	
	automata A;
	automata_state a0, a1;
	a0.successors.resize(2);
	a1.successors.resize(2);
	a0.successors[0].insert(1);
	a0.successors[1].insert(0);
	a1.successors[0].insert(1);
	a1.successors[1].insert(0);
	a1.successors[1].insert(1);
	A.push_back(a0);
	A.push_back(a1);
}


bool checkautomata(tracet trace, automata A)
{
	std::set<unsigned> current, next;
	current.insert(0);

	for(const auto & st: trace)
	{
	  for(const auto & sa: current)
	  {
	  	for(const auto & l: st.label)
	  	{
	  	 next.insert(A[sa].successors.at(l));
	  	}	
	  }
	current=next;
	}

 	for (const auto & sa: current)
 	{
 		if (A[sa].accepting)
 		{
 			return true;
 		}
 	}

return false;
}






