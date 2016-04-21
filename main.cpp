#include <vector>
#include <cassert>
#include <random>
#include <algorithm>
#include <iostream>
#include "pctl_tokenizer.h"
#include "pctl_parser.h"
#include "markov_chain.h"
#include "propcheck.h"
#include "statmodelchecker.h"
#include "automata.h"



tracet gettrace(std::default_random_engine &);
resultt checkproperty(tracet);
unsigned N = 100;
unsigned tracelength = 20;


void statmodelcheck()
{
	std::default_random_engine generator;
    float prob=0.5;
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
    prob = (float)p/((float)p+(float)f);
    std::cout<< "Property is satisfied with probability " << prob <<"\nNumber of strings satisfying property is " << p << "\nNumber of strings failing property is "<<f <<"\n";
    
}

tracet gettrace(std::default_random_engine &generator)
{
	tracet trace;
	statet state = get_init_state();

	while (trace.size() < tracelength)
	{
        std::vector<std::pair<statet,unsigned> > successors;
        successors = get_successors(state);

        unsigned sum = 0;
       
        for (const auto& p :successors)
        {   
            sum = sum + p.second;
            
        }  
       
		std::uniform_int_distribution<unsigned> distribution(0,sum-1);
        unsigned random = distribution(generator);
        unsigned mass =0;

        for(const auto& p : successors)
         {
          mass = mass + p.second;
          if(mass > random){ state = p.first; break;}   
         }

		trace.push_back(state);
	}
	return trace;
}

void printtrace(tracet trace)
{
    for(const auto &s: trace) 
    {
        printstate(s);

    }
    std::cout<<"\n";
}

resultt checkproperty(tracet trace)
{

}


int main(int argc, const char *argv[])
{
  resultt res;  
  tracet trace;
  std::default_random_engine generator;
  trace = gettrace(generator);
  printtrace(trace); 

  //system ("./ltl2ba-1.2b1/ltl2ba -f \"a U b\"");

  res=checkautomata(trace);
  switch(res)
  {
    case PASS: std::cout<<"PASS"; break;
    case FAIL: std::cout<<"FAIL"; break;
    case UNKNOWN: std::cout<<"UNKNOWN"; break;
  }


  std::vector<tokent> tokenseq;
  std::cout<< "Number of strings: "<<argc<<"\n";
    if (argc==2)
    {
        tokenseq = pctl_tokenizer(argv[1]);
        outputtoken(tokenseq);
        fflush(stdout);
        pctlformula f = parse_top(tokenseq);
        std::cout<<"\n";
        output(f);
        std::cout<<"\n";
         parsepctlformula(f);

      //  tracecheck(f,trace);


    }
    else
    {
        std::cout<<"wrong number of strings \n";
        for (int i=0;i<argc; i++)
        {
            std::cout<<"string: "<< argv[i]<<"\n";       
        }
 }



}