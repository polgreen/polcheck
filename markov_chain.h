#ifndef markov_chain_h
#define markov_chain_h

#include <vector>

struct statet {unsigned hasbus; unsigned clients; };
statet get_init_state();
std::vector<std::pair<statet,unsigned> > get_successors(statet current);
void printstate(statet s);
typedef std::vector <statet> satset; 

#endif