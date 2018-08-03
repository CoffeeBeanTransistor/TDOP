#ifndef _TokenData_H
#define _TokenData_H

#include "Token.h"
#include "Tokenizer.h"
#include <stdint.h>





typedef struct TokenInfo TokenInfo;
struct TokenInfo {
  Token *(*nud)(Token *currToken, Tokenizer *tokenizer, uint32_t leftBindingPower);
  Token *(*led)(Token *leftToken, Tokenizer *tokenizer);
  uint32_t bindingPower;
};
TokenInfo *getTokenInfo(Token *thisToken);
Token *getTokenType(Token *thisToken);
Token *getTokenSymbol(Token *thisToken);
Token *getNextToken(Tokenizer *expression);
int verifyTokensBackToBack(Token *token1, Token *token2);
Token *modifyToken(Token *token, int symbol);

#endif // _TokenData_H
