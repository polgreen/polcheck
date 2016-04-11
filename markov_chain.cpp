#include "markov_chain.h"
#include <iostream>
#include "pctl_parser.h"


statet get_init_state()
{
 statet init;
 init.hasbus = 1;
 init.clients=10;

return init;
}

std::vector<std::pair<statet,unsigned> > get_successors(statet current)
{
 std::vector<std::pair<statet,unsigned> > result;
 for (unsigned i=0; i<current.clients; i++)
 {
 	statet successor;
 	successor.clients=current.clients;
 	successor.hasbus = i;
 	std::pair<statet,unsigned> p;
 	p.first = successor;
 	p.second = 1;
 	result.push_back(p);
 }
return result;
}

void printstate(statet s)
{
	std::cout<<"bus: "<<s.hasbus<<"\n";
}


