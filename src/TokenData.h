#ifndef _TokenData_H
#define _TokenData_H

#include "Token.h"
#include "Tokenizer.h"
#include <stdint.h>





typedef struct TokenInfo TokenInfo;
struct TokenInfo {
  Token *(*nud)(Token *currToken, Tokenizer *tokenizer);
  Token *(*led)(Token *leftToken, Tokenizer *tokenizer);
  uint32_t bindingPower;
};


TokenInfo *getTokenInfo(Token *token);

Token *nudInt (Token *currToken, Tokenizer *expression);
Token *ledInt (Token *leftToken, Tokenizer *expression);
Token *nudFloat (Token *currToken, Tokenizer *expression);
Token *nudPlus(Token *currToken, Tokenizer *expression);
Token *ledPlus (Token *leftToken, Tokenizer *expression);
Token *nudMinus(Token *thisToken, Tokenizer *expression);
Token *ledMinus (Token *leftToken, Tokenizer *expression);

#endif // _TokenData_H
