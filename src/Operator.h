#ifndef _Operator_H
#define _Operator_H
#include "Operator.h"
#include "Tokenizer.h"
#include "TokenData.h"
#include "TDOP.h"
#include "Token.h"

Token *nudInt (Token *thisToken, Tokenizer *expression, uint32_t *leftBindingPower);
Token *ledInt (Token *leftToken, Tokenizer *expression);
Token *nudFloat (Token *thisToken, Tokenizer *expression, uint32_t *leftBindingPower);
Token *nudPlus(Token *thisToken, Tokenizer *expression, uint32_t *leftBindingPower);
Token *ledPlus (Token *leftToken, Tokenizer *expression);
Token *nudMinus(Token *thisToken, Tokenizer *expression, uint32_t *leftBindingPower);
Token *ledMinus (Token *leftToken, Tokenizer *expression);
Token *nudAsterisk(Token *thisToken, Tokenizer *expression, uint32_t *leftBindingPower);
Token *ledAsterisk (Token *leftToken, Tokenizer *expression);
Token *ledSlash(Token *leftToken, Tokenizer *expression);
Token *ledPercent(Token *leftToken, Tokenizer *expression);
Token *nudExclamation(Token *thisToken, Tokenizer *expression, uint32_t *leftBindingPower);
Token *nudLeftBracket(Token *thisToken, Tokenizer *expression, uint32_t *eftBindingPower);
//Token *nudRightBracket(Token *thisToken, Tokenizer *expression, uint32_t leftBindingPower);
int matchBracket(Tokenizer *expression, char closing, uint32_t *leftBindingPower);

#endif // _TDOP_H
