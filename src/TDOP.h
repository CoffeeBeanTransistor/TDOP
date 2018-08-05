#ifndef _TDOP_H
#define _TDOP_H
#include "Tokenizer.h"

extern Token *thistoken;
Token *TDOP(Tokenizer *expression);
Token *evaluate(Tokenizer *expression, int rightBindingPower);





#endif // _TDOP_H
