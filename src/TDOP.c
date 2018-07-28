#include "TDOP.h"
#include "Tokenizer.h"
#include "TokenData.h"



Token *TDOPStarter(Tokenizer *expression) {
  return TDOP(expression, 0);
}

Token *TDOP(Tokenizer *expression, int bindingPower) {
  Token *currToken, *nextToken;
  TokenInfo *tokenInfo;

  currToken = getToken(expression);
  tokenInfo = getTokenInfo(currToken);
  return tokenInfo->nud(currToken, expression);

}
