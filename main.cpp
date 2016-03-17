#include <vector>
#include <cassert>
#include <random>
typedef std::vector<unsigned> tracet; 
enum resultt {UNKNOWN, PASS, FAIL};
tracet gettrace(std::default_random_engine &);
resultt checkproperty(tracet);
unsigned N = 100;
unsigned tracelength = 10;


void statmodelcheck()
{
	std::default_random_engine generator;
	
	unsigned n=0, p=0, f=0;
	tracet sigma;
	while(n<N)
	{
		sigma = gettrace(generator);
		n = n + 1;
		switch (checkproperty(sigma))
		{
			case UNKNOWN: break;
			case PASS: p = p + 1; break;
			case FAIL: f = f + 1; break;
		}

	}



}

tracet gettrace(std::default_random_engine &generator)
{
	tracet trace;
	unsigned state;
	state =0; // initial state = 0


	while (trace.size() < tracelength)
	{
		std::uniform_int_distribution<int> distribution(0,1);
		switch(state)
		{	
			case 0: state  = distribution(generator); break;
			case 1: break;
			default: assert(0); //unexpected state
		}
		trace.push_back(state);
	}
	return trace;
}

resultt checkproperty(tracet trace)
{
	return FAIL;
}


int main()
{
	statmodelcheck();
}