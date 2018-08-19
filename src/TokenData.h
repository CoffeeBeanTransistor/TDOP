#ifndef _TokenData_H
#define _TokenData_H

#include "Token.h"
#include "Tokenizer.h"
#include <stdint.h>

typedef struct TokenInfo TokenInfo;
struct TokenInfo {
  Token *(*nud)(Token *thisToken, Tokenizer *expression);
  Token *(*led)(Token *leftToken, Token *thisToken, Tokenizer *expression);
  uint32_t bindingPower;
};

TokenInfo *getTokenInfo(Token *token);
int getTokenType(Token *thisToken);
Token *getAdvanceToken(Tokenizer *expression);
int verifyTokensBackToBack(Token *token1, Token *token2);
double getTokenValue(Token *token);
int getTokenIntegerValue(Token *token);
Token *newFloatToken(double value, Token *leftToken, Token *rightToken);
int checkTokenIfItsNULL(Token *token);
Token *getNud(Token *thisToken, Tokenizer *expression);
Token *getLed(Token *thisToken, Token *leftToken, Tokenizer *expression);
Token *handleSignEqualAndRepeat(Tokenizer *expression, Token *token1);
int verifyTokensRepeated(Token *token1, Token *token2);
int verifyTokenIsEqualSign(Token *token2);
char* createString(char *ptr, int size);
int checkIfUndefined(OperatorIsotope *token1IsoInfo, int indexNum);
void checkIfNextTokenIsInteger(Tokenizer *expression);

#endif // _TokenData_H
