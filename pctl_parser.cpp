#include "pctl_parser.h"
#include <vector>
#include <iostream>
pctlformula parse (std::vector<tokent> &tokenseq);
pctlformula parseprimary(std::vector<tokent> &tokenseq);


void output(pctlformula f)
{
 switch(f.t.kind)
 {
 case IDENTIFIER: std::cout<< '"'<<f.t.label<<'"'; break;
 case UNTIL:std::cout<<"("; output(f.children[0]); std::cout<< " U "; output(f.children[1]);std::cout<<")"; break;
case AND:  std::cout<<"("; output(f.children[0]); std::cout<< " & "; output(f.children[1]); std::cout<<")";break;
 case OR:    std::cout << "("; output(f.children[0]); std::cout<< " | "; output(f.children[1]); std::cout << ")"; break;
 case PROB: std::cout<<"P "; output(f.children[0]); output(f.children[1]); 
 output(f.children[2]); std::cout<<"[";output(f.children[3]); std::cout<<"]";break;
 case NOT: std::cout<<"!"; output(f.children[0]); break;
 case GT: std::cout<<">";break;
 case LT: std::cout<<"<";break;
 case EQ:std::cout<<"=";break;
 case LP: std::cout<<"("; break;
 case RP: std::cout<<")"; break;
 case SP: std::cout<<" "; break;	
 case FI: std::cout<<"F "; output(f.children[0]); break;
 case GL: std::cout<<"G "; output(f.children[0]); break;
 case X: std::cout<<"X"; output(f.children[0]); break;
 case MIN: std::cout<<"min"; break;
 case MAX: std::cout<<"max"; break;
 case QUE: std::cout<<"?"; break;
 case IMPLIES: std::cout<<"implies"; break;
 case GE: std::cout<<">="; break;
 case LE: std::cout<<"<="; break;
 default:;
 }
}

void outputtoken(std::vector<tokent> &tokenseq)
{
	      for (unsigned i=0; i<tokenseq.size(); i++)
        {
            token(tokenseq.at(i));
        }
}

pctlformula parseprob(std::vector<tokent> &tokenseq)
{
	pctlformula f, f0, f1, f2, f3;
	f.t = tokenseq.front();
	tokenseq.erase(tokenseq.begin());
	if (tokenseq.empty())
	{
		std::cout<<"expected bounds after P \n";
	}
	else if (tokenseq.front().kind==GE || tokenseq.front().kind==LE)
	{
		f0.t.kind=tokenseq.front().kind;
		tokenseq.erase(tokenseq.begin());
		if(tokenseq.empty())
			{std::cout<<"expected identifier after P>= or P<=";}
		else{
			f1 = parseprimary(tokenseq);
			f.children.resize(4);
			f.children[0] = f0;
			f.children[1] = f1;
			f.children[2].t.kind=SP; 
			if(!tokenseq.empty() && tokenseq.front().kind==SLP)
			{
				tokenseq.erase(tokenseq.begin());
				f3 = parse(tokenseq);
				f.children[3]=f3;

				if(!tokenseq.empty() && tokenseq.front().kind==SRP)
				{
					tokenseq.erase(tokenseq.begin());
					return f;
				}
				else{std::cout<<"missing SRP";}
			}
			else{std::cout<<"missing SLP";}

		}
	}
	else if (tokenseq.front().kind==MIN || tokenseq.front().kind==MAX)
	{
		f0.t.kind=tokenseq.front().kind;
		tokenseq.erase(tokenseq.begin());
		if(tokenseq.empty() || tokenseq.front().kind!=EQ)
			{std::cout<<"expected = after P min or P max";}
		else{
			f1.t.kind=EQ;
			tokenseq.erase(tokenseq.begin());
			if(tokenseq.empty() || (tokenseq.front().kind!=QUE && tokenseq.front().kind!=IDENTIFIER))
			{std::cout<<"expected ? or identifier after P min or P max";}
			else{
			 f2.t=tokenseq.front();	
			 tokenseq.erase(tokenseq.begin());

			 f.children.resize(4);
			 f.children[0] = f0;
			 f.children[1] = f1;
			 f.children[2] = f2;
			 if(!tokenseq.empty() && tokenseq.front().kind==SLP)
			   {
				tokenseq.erase(tokenseq.begin());
				f3 = parse(tokenseq);
				f.children[3]=f3;

				if(!tokenseq.empty() && tokenseq.front().kind==SRP)
				 {
					tokenseq.erase(tokenseq.begin());
					return f;
				 }
				 else{std::cout<<"missing SRP";}
			   }
			  else{std::cout<<"missing SLP";}

		     } 

	       }
	 } 
	 else{std::cout<<"expecting MIN or MAX or > or < after PROB";}     

}

pctlformula parseprimary(std::vector<tokent> &tokenseq)
{
	pctlformula f;
	if(tokenseq.front().kind==IDENTIFIER)
	{
		f.t = tokenseq.front();
		tokenseq.erase(tokenseq.begin());
		return f;
	}
	else if(tokenseq.front().kind == NOT)
	{
		f.t =tokenseq.front();
		tokenseq.erase(tokenseq.begin());
		pctlformula f0 = parseprimary(tokenseq);
		f.t.kind = NOT;
		f.children.resize(1);
	 	f.children[0] = f0;
	 	return f;
	}

	else if (tokenseq.front().kind==LP)
	{
		tokenseq.erase(tokenseq.begin());
		f = parse(tokenseq);
		if (tokenseq.front().kind == RP)
		{
			tokenseq.erase(tokenseq.begin());
			return f;
		}
		else{
			std::cout<< "missing right parenthesis";
		}
	}

	else if (tokenseq.front().kind==PROB)
	{
		return parseprob(tokenseq);
	}

	else if (!tokenseq.empty()){
		switch(tokenseq.front().kind){
				case UNTIL: std::cout<<"UNTIL must be preceeded by an identifier"; break;
				case AND: std::cout<<"AND must be preceeded by an identifier"; break;
				case OR: std::cout<<"OR must be preceeded by an identifier"; break;
				default: ;
			}
			
	}	
	else
		{std::cout<<"empty tokenseq";}

}

pctlformula parseconjunction(std::vector<tokent> &tokenseq)
{
	pctlformula f0;
	f0 = parseprimary(tokenseq);
	if(tokenseq.front().kind==AND)
	{
	 pctlformula f1;
	 tokenseq.erase(tokenseq.begin());
	 if(tokenseq.empty())
	 {
		std::cout<<"error. Expected identifier after AND";
		return f0;
	 }
	 else{
	  f1 = parseconjunction(tokenseq);
	  pctlformula f;
	  f.t.kind = AND;
	  f.children.resize(2);
	  f.children[0] = f0;
	  f.children[1] = f1;
	  return f;
	 }
	}
	else
	{
		return f0;
	}


}

pctlformula parsedisjunction(std::vector<tokent> &tokenseq)
{

	pctlformula f0;
	f0 = parseconjunction(tokenseq);
	if(tokenseq.front().kind==OR)
	{
	pctlformula f1;
	tokenseq.erase(tokenseq.begin());
	if(tokenseq.empty())
	{
		std::cout<<"error. Expected identifier after OR";
	}
	else{
	 f1 = parsedisjunction(tokenseq);
     pctlformula f;
	 f.t.kind = OR;
	 f.children.resize(2);
	 f.children[0] = f0;
	 f.children[1] = f1;
	 return f;
		}
	} 
	else
	{
		return f0;
	}
}





pctlformula parseFG(std::vector<tokent> &tokenseq)
{

	pctlformula f0;
	pctlformula f1;
	pctlformula f;

	if(tokenseq.front().kind==FI)
	{
	 tokenseq.erase(tokenseq.begin());
	  if(tokenseq.empty())
	   {
		std::cout<<"error. Expected identifier after FINALLY \n";
	   }
	  else{

	   
		f1 = parseFG(tokenseq);
		f.t.kind = FI;
		f.children.resize(1);
	 	f.children[0] = f1;	

	   return f;
	   }
	}
	else if(tokenseq.front().kind==GL)
	{
	  tokenseq.erase(tokenseq.begin());
	  if(tokenseq.empty())
	   {
		std::cout<<"error. Expected identifier after GLOBALLY \n";
	   }
	  else
	  {
	   f1 = parseFG(tokenseq);
	   f.t.kind = GL;
	   f.children.resize(1);
	   f.children[0] = f1;	
	   return f;
	   }
	 } 
	else if(tokenseq.front().kind==X)
	{
	  tokenseq.erase(tokenseq.begin());
	  if(tokenseq.empty())
	   {
		std::cout<<"error. Expected identifier after X \n";
	   }
	  else
	  {
	   f1 = parseFG(tokenseq);
	   f.t.kind = X;
	   f.children.resize(1);
	   f.children[0] = f1;	
	   return f;
	   }
	 } 	
	else
	{
		f0 = parsedisjunction(tokenseq);
		return f0;
	}
}

pctlformula parseuntil(std::vector<tokent> &tokenseq)
{
	pctlformula f0;
	f0 = parseFG(tokenseq);
	if(tokenseq.front().kind==UNTIL)
	 {
	 pctlformula f1;
	 tokenseq.erase(tokenseq.begin());
	 if(tokenseq.empty())
	  {
		std::cout<<"error. Expected identifier after UNTIL";
	  }
	  else{
	   f1 = parseFG(tokenseq);
	   pctlformula f;
	   f.t.kind = UNTIL;
	   f.children.resize(2);
	   f.children[0] = f0;
	   f.children[1] = f1;
       return f;
	  }
	 }
	else
	{
		return f0;
	}
}




pctlformula parse (std::vector<tokent> &tokenseq)
{
pctlformula f;
if(tokenseq.empty())
{
	std::cout<<"parse error: empty tokenseq";
}
else{
 f =  parseuntil(tokenseq);

 return f;
}
}

pctlformula parse_top (std::vector<tokent> &tokenseq)
{
pctlformula f;

 f =  parse(tokenseq);
  if(!tokenseq.empty())
  {
	std::cout<<"parse error: tokens after end of expression \n";
	outputtoken(tokenseq);
	  }
 return f;

}