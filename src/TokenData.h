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

#endif // _TokenData_H
