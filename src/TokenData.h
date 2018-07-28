#ifndef _TokenData_H
#define _TokenData_H

#include "Token.h"
#include "Tokenizer.h"
#include <stdint.h>





typedef struct TokenInfo TokenInfo;
struct TokenInfo {
  Token *(*nud)(Token *currToken, Tokenizer *tokenizer);
  Token *(*led)(Token *currToken, Tokenizer *tokenizer, Token *leftToken, uint32_t bindingPower);
  uint32_t bindingPower;
};


TokenInfo *getTokenInfo(Token *token);

Token *nudInt (Token *currToken, Tokenizer *expression);
Token *nudFloat (Token *currToken, Tokenizer *expression);

#endif // _TokenData_H
