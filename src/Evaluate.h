#ifndef _EVALUATE_H
#define _EVALUATE_H
#include "Tokenizer.h"

extern Token *thistoken;
Token *evaluate(Tokenizer *expression);
Token *_evaluate(Tokenizer *expression, int rightBindingPower);




#endif // _TDOP_H
