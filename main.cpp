#include <vector>
#include <cassert>
#include <random>
#include <algorithm>
#include <iostream>
#include "pctl_tokenizer.h"
#include "pctl_parser.h"


typedef std::vector<unsigned> tracet; 
enum resultt {UNKNOWN, PASS, FAIL};
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
	unsigned state;
	state =0; // initial state = 0


	while (trace.size() < tracelength)
	{
		std::uniform_int_distribution<int> distribution(0,1);
		switch(state)
		{	
           /* case 0: state  = distribution(generator)?0:1; break;
            case 1: state = distribution(generator)?1:2; break;
            case 2: state = distribution(generator)?3:4; break;
            case 3: state = 0; break;
            case 4: break;*/
                
            case 999999: break;
            default: state = distribution(generator)?state:state+1; break; //unexpected state
		}
		trace.push_back(state);
	}
	return trace;
}

resultt checkproperty(tracet trace)
{
    //property = (true U<4 "state3"), i.e., reach state 3 within 4 steps.
   /* std::vector<unsigned>::iterator it = std::find(trace.begin(), trace.end(), 3);
    if(it == trace.end())
    {
        std::cout << "Property not satisfied, did not reach state 2 \n";
        return FAIL;
    }
    else if (*it<4)
    {
        std::cout << "Satisfies property, reached state 2 in position " << *it << "\n";
        return PASS;
    }
    else
    {
        std::cout<<"Property not satisfied, reached state 2 in position "<< *it << "\n";
        return FAIL;
    }
    */
    
    //property = (!s4 U s3)
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
  
    return UNKNOWN;
	
}


int main(int argc, const char *argv[])
{
        std::vector<tokent> tokenseq;
	std::cout<< "Number of strings: "<<argc<<"\n";
    if (argc==2)
    {
        tokenseq = pctl_tokenizer(argv[1]);
        pctlformula f = parse(tokenseq);
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