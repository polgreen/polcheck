#include "pctl_tokenizer.h"
#include <vector>
#include <iostream>
struct pctlformula {tokent t; std::vector<pctlformula> children ; };
void output(pctlformula f);
pctlformula parse (std::vector<tokent> &tokenseq);
