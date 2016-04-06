#ifndef pctl_tokenizer_h
#define pctl_tokenizer_h
#include <string>
#include <vector>
enum tokenkindt {PROB, UNTIL, IDENTIFIER, NOT, AND, OR, EQ, LT, GT, LP, RP, SP};
struct tokent {tokenkindt kind;std::string label;};
std::vector<tokent> pctl_tokenizer(std::string);
#endif
