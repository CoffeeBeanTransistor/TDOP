#ifndef _Operator_H
#define _Operator_H
#include "Operator.h"
#include "Tokenizer.h"
#include "TokenData.h"
#include "TDOP.h"
#include "Token.h"



Token *nudInt (Token *currToken, Tokenizer *expression);
Token *ledInt (Token *leftToken, Tokenizer *expression);
Token *nudFloat (Token *currToken, Tokenizer *expression);
Token *nudPlus(Token *currToken, Tokenizer *expression);
Token *ledPlus (Token *leftToken, Tokenizer *expression);
Token *nudMinus(Token *thisToken, Tokenizer *expression);
Token *ledMinus (Token *leftToken, Tokenizer *expression);
Token *nudAsterisk(Token *thisToken, Tokenizer *expression);
Token *ledAsterisk (Token *leftToken, Tokenizer *expression);
Token *ledSlash(Token *leftToken, Tokenizer *expression);
Token *ledPercent(Token *leftToken, Tokenizer *expression);
Token *nudExclamation(Token *thisToken, Tokenizer *expression);


#endif // _TDOP_H
