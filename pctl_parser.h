#ifndef pctl_parser_h
#define pctl_parser_h

#include "pctl_tokenizer.h"
#include <vector>
#include <iostream>
struct pctlformula {tokent t; std::vector<pctlformula> children ; };
void output(pctlformula f);
pctlformula parse_top (std::vector<tokent> &tokenseq);
#endif