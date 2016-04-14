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



tracet gettrace(std::default_random_engine &);
resultt checkproperty(tracet);
unsigned N = 100;
unsigned tracelength = 10;


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
}

resultt checkproperty(tracet trace)
{
   /*
        std::vector<unsigned>::iterator s3 = std::find(trace.begin(), trace.end(), 3);
        std::vector<unsigned>::iterator s4 = std::find(trace.begin(), trace.end(), 4);
    
    if(s3 == trace.end() || s4== trace.end())
    {
        std::cout<< "String is neither a counterexample or a witness \n";
        return UNKNOWN;
    }
    else if (s3-trace.begin()>s4-trace.begin())
    {
        std::cout<<"Reached S3 in " <<s3 - trace.begin()<<" steps and s4 in " << s4 - trace.begin() << " steps , string is a counterexample \n";
        return FAIL;
    }
    else
    {
        std::cout<<"Reached S3 in " <<s3 - trace.begin()<<" steps and s4 in " << s4 - trace.begin() << " steps , string is a witness \n";
        return PASS;
    }
  
    return UNKNOWN;*/
	
}


int main(int argc, const char *argv[])
{
   /*
    satset s;
    satset result;
    statet state;
    
    set_all_states();
    state.hasbus = 1;
    state.clients=10;
    s.push_back(state);
    
    result = checkNOT(s);

*/

  tracet trace;
  std::default_random_engine generator;
  trace = gettrace(generator);
  printtrace(trace);
    
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